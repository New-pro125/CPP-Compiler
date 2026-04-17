%{
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "types.h"
#include "parser_context.h"
#include "parser_action_helpers.h"

int yylex();
void yyerror(const char* s);
extern int yylineno;

// Shorthand macros
#define CTX   parserContext
#define ST    CTX->symTable
#define SA    CTX->semAnalyzer
#define QG    CTX->quadGenerator
#define EH    CTX->errHandler

static std::string serializeCharLiteral(char c){
    switch (c){
        case '\n':
        return "'\\n'";
        case '\t':
        return "'\\t'";
        case '\r':
        return "'\\r'";
        case '\0':
        return "'\\0'";
        case '\'':
        return "'\\\''";
        default:
        break;
    }
    if(std::isprint(c)) {
        return "'" + std::string(1,c) + "'";
    }
    char buf[8];
    std::snprintf(buf,sizeof(buf),"\\x%02X",c);
    return "'" + std::string(buf)+"'";
}
%}

%define parse.error verbose

%code requires {
    #include "types.h"
    #include "parser_context.h"
}

%union {
    int ival;
    float dval;
    char cval;
    char* sval;
    Type typeval;
    ExprAttr* exprval;
}

%token INT FLOAT CHAR BOOL VOID STRING CONST
%token IF ELSE WHILE DO FOR SWITCH CASE DEFAULT BREAK CONTINUE RETURN
%token INC DEC
%token PLUSASSIGN MINUSASSIGN STARASSIGN DIVASSIGN MODASSIGN
%token EQ NEQ LEQ GEQ AND OR
%token ASSIGN PLUS MINUS STAR DIV MOD NOT LT GT
%token LPARENTHESIS RPARENTHESIS LBRACE RBRACE LBRACKET RBRACKET COMMA SEMICOLON COLON
%token <sval> IDENTIFIER STRING_LITERAL
%token <ival> INT_LITERAL BOOL_LITERAL
%token <dval> FLOAT_LITERAL
%token <cval> CHAR_LITERAL

%token BITWISEXOR BITWISEAND BITWISEOR RSHIFT LSHIFT BITWISENOT
%token LSHIFTASSIGN RSHIFTASSIGN XORASSIGN ANDASSIGN ORASSIGN


%type <typeval> type_spec
%type <exprval> expr assign_expr logical_or_expr logical_and_expr
%type <exprval> bitwise_or_expr bitwise_xor_expr bitwise_and_expr
%type <exprval> equality_expr relational_expr shift_expr
%type <exprval> additive_expr multiplicative_expr unary_expr
%type <exprval> postfix_expr primary_expr literal
%type <exprval> expr_opt
%type <sval> if_condition_prefix

%left COMMA
%right ASSIGN PLUSASSIGN MINUSASSIGN STARASSIGN DIVASSIGN LSHIFTASSIGN RSHIFTASSIGN XORASSIGN ANDASSIGN ORASSIGN MODASSIGN
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left OR
%left AND
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NEQ
%left GT LT LEQ GEQ
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right UMINUS NOT BITWISENOT
%left INC DEC

%%

program
    : decl_list
    ;

decl_list
    : decl_list decl
    |
    ;

decl
    : var_decl
    | func_decl
    ;


type_spec
    : INT       { $$ = Type::INT; CTX->currDeclType = $$; CTX->currDeclConst = false; }
    | FLOAT     { $$ = Type::FLOAT; CTX->currDeclType = $$; CTX->currDeclConst = false; }
    | CHAR      { $$ = Type::CHAR; CTX->currDeclType = $$; CTX->currDeclConst = false; }
    | BOOL      { $$ = Type::BOOL; CTX->currDeclType = $$; CTX->currDeclConst = false; }
    | VOID      { $$ = Type::VOID; CTX->currDeclType = $$; CTX->currDeclConst = false; }
    | STRING    { $$ = Type::STRING; CTX->currDeclType = $$; CTX->currDeclConst = false; }
    ;


var_decl
        : type_spec declarator_list SEMICOLON
    | CONST type_spec
      { CTX->currDeclType = $2; CTX->currDeclConst = true; }
      declarator_list SEMICOLON
    ;

declarator_list
    : declarator_list COMMA declarator
    | declarator
    ;

declarator
    : IDENTIFIER
      {
      handleSimpleDeclarator(CTX, $1, yylineno);
          free($1);
      }
    | IDENTIFIER ASSIGN expr
      {
      handleInitializedDeclarator(CTX, $1, $3, yylineno);
          free($1);
      }
    ;

func_decl
    : type_spec IDENTIFIER LPARENTHESIS
      {
      resetFunctionParamContext(CTX);
      }
      param_list_opt RPARENTHESIS
      {
      beginFunctionDefinition(CTX, $2, $1, yylineno);
      }
      compound_stmt_func
      {
      endFunctionDefinition(CTX, $2);
          free($2);
      }
    ;

param_list_opt
    : param_list
    |
    ;

param_list
    : param_list COMMA param_decl
    | param_decl
    ;

param_decl
    : type_spec IDENTIFIER
      {
          addFunctionParam(CTX, $1, $2, "", false, yylineno);
          free($2);
      }
    | CONST type_spec IDENTIFIER
      {
          addFunctionParam(CTX, $2, $3, "", true, yylineno);
          free($3);
      }
    | type_spec IDENTIFIER ASSIGN literal
      {
          bool defaultOk = SA->validateAssignment(*$4, $1, yylineno);
          addFunctionParam(CTX, $1, $2, defaultOk ? $4->place : "", false, yylineno);
          free($4);
          free($2);
      }
    | CONST type_spec IDENTIFIER ASSIGN literal
      {
          bool defaultOk = SA->validateAssignment(*$5, $2, yylineno);
          addFunctionParam(CTX, $2, $3, defaultOk ? $5->place : "", true, yylineno);
          free($5);
          free($3);
      }
    ;


stmt
  :
    {
    validateStatementPlacement(CTX, yylineno);
    }
    stmt_core
  | error SEMICOLON { yyerrok; yyclearin; }
  ;

stmt_core
  : expr_stmt
    | compound_stmt
    | if_stmt
    | while_stmt
    | do_while_stmt
    | for_stmt
    | switch_stmt
    | return_stmt
    | break_stmt
    | continue_stmt
    ;

stmt_list
    : stmt_list block_item
    |
    ;

block_item
    : stmt
    | var_decl
    ;

expr_stmt
    : expr SEMICOLON
    | SEMICOLON
    ;

compound_stmt
    : LBRACE { ST->addScope(); } stmt_list RBRACE
      {
      leaveScopeWithUnusedWarnings(CTX);
      }
    ;


compound_stmt_func
    : LBRACE stmt_list RBRACE
      {
      leaveScopeWithUnusedWarnings(CTX);
      }
    ;


if_condition_prefix
    : IF LPARENTHESIS expr RPARENTHESIS
      {
          $$ = beginIfCondition(CTX, $3,yylineno);
      }
    ;


if_stmt
    : if_condition_prefix stmt %prec LOWER_THAN_ELSE
      {
          endIfWithoutElse(CTX, $1);
          free($1);
      }
    | if_condition_prefix stmt ELSE
      {
          $<sval>$ = beginElseBranch(CTX, $1);
          free($1);
      }
      stmt
      {
          endIfWithElse(CTX, $<sval>4);
          free($<sval>4);
      }
    ;


while_stmt
    : WHILE
      {
      $<sval>$ = beginWhileLoop(CTX);
      }
      LPARENTHESIS expr RPARENTHESIS
      {
      emitLoopConditionFalseJump(CTX, $4,yylineno);
      }
      stmt
      {
      endWhileLoop(CTX, $<sval>2);
          free($<sval>2);
      }
    ;


do_while_stmt
    : DO
      {
      $<sval>$ = beginDoWhileLoop(CTX);
      }
      stmt WHILE LPARENTHESIS
      {
      emitDoWhileConditionLabel(CTX, $<sval>2);
      }
      expr RPARENTHESIS SEMICOLON
      {
      endDoWhileLoop(CTX, $<sval>2, $7,yylineno);
          free($<sval>2);
      }
    ;


for_stmt
    : FOR LPARENTHESIS
      { ST->addScope(); }
      for_init SEMICOLON
      {
      $<sval>$ = beginForLoop(CTX);
      }
      expr_opt SEMICOLON
      {
      emitForConditionAndUpdateLabel(CTX, $<sval>6, $7,yylineno);
      }
      for_update RPARENTHESIS
      {
      emitForBackEdgeAndBodyLabel(CTX, $<sval>6);
      }
      stmt
      {
      endForLoop(CTX, $<sval>6);
          free($<sval>6);
      }
    ;

for_init
    : for_var_decl
    | expr
    |
    ;

for_var_decl
    : type_spec
      { CTX->currDeclType = $1; CTX->currDeclConst = false; }
      declarator_list
    | CONST type_spec
      { CTX->currDeclType = $2; CTX->currDeclConst = true; }
      declarator_list
    ;

for_update
    : expr
    |
    ;

expr_opt
    : expr      { $$ = $1; }
    |           { $$ = new ExprAttr(Type::BOOL,""); }
    ;


switch_stmt
    : SWITCH LPARENTHESIS expr RPARENTHESIS
      {
          $<sval>$ = beginSwitchStatement(CTX, $3,yylineno);
      }
      LBRACE case_list RBRACE
      {
          endSwitchStatement(CTX, $<sval>5);
          free($<sval>5);
      }
    ;

case_list
    : case_list case_item
    |
    ;

case_item
    : CASE literal COLON
      {
          beginCaseClause(CTX, $2, yylineno);
      }
      stmt_list
      {
          endCaseOrDefaultClause(CTX);
      }
    | DEFAULT COLON
      {
          beginDefaultClause(CTX, yylineno);
      }
      stmt_list {
        endCaseOrDefaultClause(CTX);
      }
    ;


break_stmt
    : BREAK SEMICOLON
      {
          if (SA->validateBreak(yylineno)) {
              QG->emit("JMP", "-", "-", CTX->breakLabels.back());
          }
      }
    ;

continue_stmt
    : CONTINUE SEMICOLON
      {
          if (SA->validateContinue(yylineno)) {
              QG->emit("JMP", "-", "-", CTX->continueLabels.back());
          }
      }
    ;

return_stmt
    : RETURN SEMICOLON
      {
      if (SA->validateReturn(SA->getCurrentFunctionReturnType(), nullptr, yylineno)) {
        QG->emit("RETURN", "-", "-", "-");
      }
      }
    | RETURN expr SEMICOLON
      {
          ExprAttr val = *$2;
      if (SA->validateReturn(SA->getCurrentFunctionReturnType(), &val, yylineno)) {
        QG->emit("RETURN", val.place, "-", "-");
      }
        else if (CTX->currFunction.inFn && SA->getCurrentFunctionReturnType() != Type::VOID) {
          markCurrentFunctionInvalid(CTX);
      }
          free($2);
      }
    ;


arg_list_opt
    : arg_list
    |
    ;

arg_list
    : arg_list COMMA expr  { CTX->passedArgs.back().push_back(*$3); free($3); }
    | expr                 { CTX->passedArgs.back().push_back(*$1); free($1); }
    | error RPARENTHESIS   { yyerrok; yyclearin; }
    ;

expr
    : assign_expr { $$ = $1; }
    ;

assign_expr
    : logical_or_expr { $$ = $1; }
    | IDENTIFIER ASSIGN assign_expr
      {
          $$ = makeAssignExpr(CTX, $1, $3, yylineno);
          free($1);
      }
    | IDENTIFIER PLUSASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "PLUSASSIGN", "ADD", yylineno);
          free($1);
      }
    | IDENTIFIER MINUSASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "MINUSASSIGN", "SUB", yylineno);
          free($1);
      }
    | IDENTIFIER STARASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "STARASSIGN", "MUL", yylineno);
          free($1);
      }
    | IDENTIFIER DIVASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "DIVASSIGN", "DIV", yylineno);
          free($1);
      }
    | IDENTIFIER MODASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "MODASSIGN", "MOD", yylineno);
          free($1);
      }
    | IDENTIFIER LSHIFTASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "LSHIFTASSIGN", "SHL", yylineno);
          free($1);
      }
    | IDENTIFIER RSHIFTASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "RSHIFTASSIGN", "SHR", yylineno);
          free($1);
      }
    | IDENTIFIER XORASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "XORASSIGN", "BXOR", yylineno);
          free($1);
      }
    | IDENTIFIER ANDASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "ANDASSIGN", "BAND", yylineno);
          free($1);
      }
    | IDENTIFIER ORASSIGN assign_expr
      {
          $$ = makeCompoundAssignExpr(CTX, $1, $3, "ORASSIGN", "BOR", yylineno);
          free($1);
      }
    ;

logical_or_expr
    : logical_or_expr OR logical_and_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "OR", "OR", yylineno);
      }
    | logical_and_expr { $$ = $1; }
    ;

logical_and_expr
    : logical_and_expr AND bitwise_or_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "AND", "AND", yylineno);
      }
    | bitwise_or_expr { $$ = $1; }
    ;

bitwise_or_expr
    : bitwise_or_expr BITWISEOR bitwise_xor_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "BITWISEOR", "BOR", yylineno);
      }
    | bitwise_xor_expr { $$ = $1; }
    ;

bitwise_xor_expr
    : bitwise_xor_expr BITWISEXOR bitwise_and_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "BITWISEXOR", "BXOR", yylineno);
      }
    | bitwise_and_expr { $$ = $1; }
    ;

bitwise_and_expr
    : bitwise_and_expr BITWISEAND equality_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "BITWISEAND", "BAND", yylineno);
      }
    | equality_expr { $$ = $1; }
    ;

equality_expr
    : equality_expr EQ relational_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "EQ", "EQ", yylineno);
      }
    | equality_expr NEQ relational_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "NEQ", "NEQ", yylineno);
      }
    | relational_expr { $$ = $1; }
    ;

relational_expr
    : relational_expr LT shift_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "LT", "LT", yylineno);
      }
    | relational_expr GT shift_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "GT", "GT", yylineno);
      }
    | relational_expr LEQ shift_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "LEQ", "LEQ", yylineno);
      }
    | relational_expr GEQ shift_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "GEQ", "GEQ", yylineno);
      }
    | shift_expr { $$ = $1; }
    ;

shift_expr
    : shift_expr LSHIFT additive_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "LSHIFT", "SHL", yylineno);
      }
    | shift_expr RSHIFT additive_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "RSHIFT", "SHR", yylineno);
      }
    | additive_expr { $$ = $1; }
    ;

additive_expr
    : additive_expr PLUS multiplicative_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "PLUS", "ADD", yylineno);
      }
    | additive_expr MINUS multiplicative_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "MINUS", "SUB", yylineno);
      }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr
    : multiplicative_expr STAR unary_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "STAR", "MUL", yylineno);
      }
    | multiplicative_expr DIV unary_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "DIV", "DIV", yylineno);
      }
    | multiplicative_expr MOD unary_expr
      {
          $$ = makeBinaryExpr(CTX, $1, $3, "MOD", "MOD", yylineno);
      }
    | unary_expr { $$ = $1; }
    ;

unary_expr
    : postfix_expr { $$ = $1; }
    | INC IDENTIFIER
      {
          $$ = makeIncDecExpr(CTX, $2, "INC", yylineno,false);
          free($2);
      }
    | DEC IDENTIFIER
      {
          $$ = makeIncDecExpr(CTX, $2, "DEC", yylineno,false);
          free($2);
      }
    | NOT unary_expr
      {
          $$ = makeUnaryExpr(CTX, $2, "NOT", "NOT", yylineno);
      }
    | BITWISENOT unary_expr
      {
          $$ = makeUnaryExpr(CTX, $2, "BITWISENOT", "BNOT", yylineno);
      }
    | MINUS unary_expr %prec UMINUS
      {
          $$ = makeUnaryExpr(CTX, $2, "UMINUS", "UMINUS", yylineno);
      }
    ;

postfix_expr
    : primary_expr { $$ = $1; }
    | IDENTIFIER INC
      {
          $$ = makeIncDecExpr(CTX, $1, "INC", yylineno);
          free($1);
      }
    | IDENTIFIER DEC
      {
          $$ = makeIncDecExpr(CTX, $1, "DEC", yylineno);
          free($1);
      }
    ;

primary_expr
    : IDENTIFIER
      {
      $$ = makeIdentifierExpr(CTX, $1, yylineno);
          free($1);
      }
    | IDENTIFIER LPARENTHESIS
      { CTX->passedArgs.push_back(std::vector<ExprAttr>()); }
      arg_list_opt RPARENTHESIS
      {
                    $$ = makeFunctionCallExpr(CTX, $1, yylineno);
          free($1);
      }
    | literal { $$ = $1; }
    | LPARENTHESIS expr RPARENTHESIS { $$ = $2; }
    ;

literal
    : INT_LITERAL
      {
          $$ = new ExprAttr(Type::INT,std::to_string($1));
      }
    | FLOAT_LITERAL
      {
          $$ = new ExprAttr(Type::FLOAT,std::to_string($1));
      }
    | CHAR_LITERAL
      {
          $$ = new ExprAttr(Type::CHAR,serializeCharLiteral($1));
      }
    | BOOL_LITERAL
      {
          $$ = new ExprAttr(Type::BOOL,$1 ? "true" : "false");
      }
    | STRING_LITERAL
      {
          $$ = new ExprAttr(Type::STRING,std::string($1));
          free($1);
      }
    ;

%%

void yyerror(const char* s) {
    if (parserContext && parserContext->errHandler) {
        parserContext->errHandler->addSyntaxError(yylineno, s);
    } else {
        std::fprintf(stderr, "Syntax error [line %d]: %s\n", yylineno, s);
    }
}
