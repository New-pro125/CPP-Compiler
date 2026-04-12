%{
#include <cstdio>
#include <string>
#include <vector>
#include "types.h"
#include "parser_context.h"

int yylex();
void yyerror(const char* s);
extern int yylineno;

// Shorthand macros
#define CTX   parserContext
#define ST    CTX->symTable
#define SA    CTX->semAnalyzer
#define QG    CTX->quadGenerator
#define EH    CTX->errHandler
%}

%define parse.error verbose
%glr-parser

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
    | stmt
    ;


type_spec
    : INT       { $$ = Type::INT; }
    | FLOAT     { $$ = Type::FLOAT; }
    | CHAR      { $$ = Type::CHAR; }
    | BOOL      { $$ = Type::BOOL; }
    | VOID      { $$ = Type::VOID; }
    | STRING    { $$ = Type::STRING; }
    ;


var_decl
    : type_spec
      { CTX->currDeclType = $1; CTX->currDeclConst = false; }
      declarator_list SEMICOLON
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
          if (CTX->currDeclConst) {
              SA->checkConstInitialized($1, false, yylineno);
          }
          Symbol sym;
          sym.name = $1;
          sym.dataType = CTX->currDeclType;
          sym.isConst = CTX->currDeclConst;
          sym.isInitialized = false;
          sym.declaredLine = yylineno;
          if (!ST->insert($1, sym)) {
              EH->addSemanticError(yylineno,
                  "Redeclaration of variable '" + std::string($1) + "'");
          }
          free($1);
      }
    | IDENTIFIER ASSIGN expr
      {
          if (CTX->currDeclConst) {
              SA->checkConstInitialized($1, true, yylineno);
          }
          bool initOk = SA->validateAssignment(*$3, CTX->currDeclType, yylineno);
          ExprAttr rhs = *$3;
          if (initOk) {
              initOk = SA->coerce(rhs, CTX->currDeclType, yylineno);
          }
          free($3);

          Symbol sym;
          sym.name = $1;
          sym.dataType = CTX->currDeclType;
          sym.isConst = CTX->currDeclConst;
          sym.isInitialized = initOk;
          sym.declaredLine = yylineno;
          if (!ST->insert($1, sym)) {
              EH->addSemanticError(yylineno,
                  "Redeclaration of variable '" + std::string($1) + "'");
          }
          if (initOk) {
              QG->emit("ASSIGN", rhs.place, "-", ST->getIRName($1));
          }
          free($1);
      }
    ;

func_decl
    : type_spec IDENTIFIER LPARENTHESIS
      {
          CTX->currParam.clear();
          CTX->currParamNames.clear();
          CTX->currParamDefaults.clear();
      }
      param_list_opt RPARENTHESIS
      {
          Symbol sym;
          sym.name = $2;
          sym.dataType = $1;
          sym.returnType = $1;
          sym.isFunction = true;
          sym.paramTypes = CTX->currParam;
          sym.paramNames = CTX->currParamNames;
          sym.defaultValues = CTX->currParamDefaults;
          sym.declaredLine = yylineno;
          sym.isInitialized = true;
          if (!ST->insert($2, sym)) {
              EH->addSemanticError(yylineno,
                  "Redeclaration of function '" + std::string($2) + "'");
          }
          SA->setCurrentFunction($2, $1);
          QG->emit("FUNC_BEGIN", $2, "-", "-");
          ST->addScope();

          for (size_t i = 0; i < CTX->currParam.size(); i++) {
              Symbol paramSym;
              paramSym.name = CTX->currParamNames[i];
              paramSym.dataType = CTX->currParam[i];
              paramSym.isInitialized = true;
              paramSym.declaredLine = yylineno;
              ST->insert(CTX->currParamNames[i], paramSym);
          }
      }
      compound_stmt_func
      {
          QG->emit("FUNC_END", $2, "-", "-");
          SA->clearCurrentFunction();
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
          CTX->currParam.push_back($1);
          CTX->currParamNames.push_back($2);
          CTX->currParamDefaults.push_back("");
          free($2);
      }
    | CONST type_spec IDENTIFIER
      {
          CTX->currParam.push_back($2);
          CTX->currParamNames.push_back($3);
          CTX->currParamDefaults.push_back("");
          free($3);
      }
    | type_spec IDENTIFIER ASSIGN literal
      {
          CTX->currParam.push_back($1);
          CTX->currParamNames.push_back($2);
          CTX->currParamDefaults.push_back($4->place);
          free($4);
          free($2);
      }
    | CONST type_spec IDENTIFIER ASSIGN literal
      {
          CTX->currParam.push_back($2);
          CTX->currParamNames.push_back($3);
          CTX->currParamDefaults.push_back($5->place);
          free( $5);
          free($3);
      }
    ;


stmt
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
    | error SEMICOLON { yyerrok; yyclearin; }
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
          std::vector<Symbol> unused = ST->getUnusedSymbolsInCurrentScope();
          for (const auto &s : unused)
              EH->addWarning(s.declaredLine,
                  "Variable '" + s.name + "' declared but never used");
          ST->LeaveScope();
      }
    ;


compound_stmt_func
    : LBRACE stmt_list RBRACE
      {
          std::vector<Symbol> unused = ST->getUnusedSymbolsInCurrentScope();
          for (const auto &s : unused)
              EH->addWarning(s.declaredLine,
                  "Variable '" + s.name + "' declared but never used");
          ST->LeaveScope();
      }
    ;


if_stmt
    : IF LPARENTHESIS expr RPARENTHESIS
      {
          std::string falseLabel = QG->newLabel();
          QG->emit("JMP_FALSE", $3->place, "-", falseLabel);
          free($3);
          $<sval>$ = strdup(falseLabel.c_str());
      }
      stmt %prec LOWER_THAN_ELSE
      {
          std::string label($<sval>5);
          QG->emit("LABEL", label, "-", "-");
          free($<sval>5);
      }
    | IF LPARENTHESIS expr RPARENTHESIS
      {
          std::string falseLabel = QG->newLabel();
          QG->emit("JMP_FALSE", $3->place, "-", falseLabel);
          free($3);
          $<sval>$ = strdup(falseLabel.c_str());
      }
      stmt ELSE
      {
          std::string endLabel = QG->newLabel();
          QG->emit("JMP", "-", "-", endLabel);
          std::string falseLabel($<sval>5);
          QG->emit("LABEL", falseLabel, "-", "-");
          free($<sval>5);
          $<sval>$ = strdup(endLabel.c_str());
      }
      stmt
      {
          std::string endLabel($<sval>8);
          QG->emit("LABEL", endLabel, "-", "-");
          free($<sval>8);
      }
    ;


while_stmt
    : WHILE
      {
          std::string startLabel = QG->newLabel();
          std::string endLabel = QG->newLabel();
          QG->emit("LABEL", startLabel, "-", "-");
          CTX->continueLabels.push_back(startLabel);
          CTX->breakLabels.push_back(endLabel);
          SA->enterLoop();
          $<sval>$ = strdup(startLabel.c_str());
      }
      LPARENTHESIS expr RPARENTHESIS
      {
          QG->emit("JMP_FALSE", $4->place, "-", CTX->breakLabels.back());
          free($4);
      }
      stmt
      {
          std::string startLabel($<sval>2);
          QG->emit("JMP", "-", "-", startLabel);
          QG->emit("LABEL", CTX->breakLabels.back(), "-", "-");
          CTX->breakLabels.pop_back();
          CTX->continueLabels.pop_back();
          SA->exitLoop();
          free($<sval>2);
      }
    ;


do_while_stmt
    : DO
      {
          std::string startLabel = QG->newLabel();
          std::string endLabel = QG->newLabel();
          std::string condLabel = QG->newLabel();
          QG->emit("LABEL", startLabel, "-", "-");
          CTX->continueLabels.push_back(condLabel);
          CTX->breakLabels.push_back(endLabel);
          SA->enterLoop();
          $<sval>$ = strdup((startLabel + "," + condLabel + "," + endLabel).c_str());
      }
      stmt WHILE LPARENTHESIS
      {
          std::string labels($<sval>2);
          size_t p1 = labels.find(',');
          size_t p2 = labels.find(',', p1 + 1);
          std::string condLabel = labels.substr(p1 + 1, p2 - p1 - 1);
          QG->emit("LABEL", condLabel, "-", "-");
      }
      expr RPARENTHESIS SEMICOLON
      {
          std::string labels($<sval>2);
          size_t p1 = labels.find(',');
          size_t p2 = labels.find(',', p1 + 1);
          std::string startLabel = labels.substr(0, p1);
          std::string endLabel = labels.substr(p2 + 1);
          QG->emit("JMP_TRUE", $7->place, "-", startLabel);
          free($7);
          QG->emit("LABEL", endLabel, "-", "-");
          CTX->breakLabels.pop_back();
          CTX->continueLabels.pop_back();
          SA->exitLoop();
          free($<sval>2);
      }
    ;


for_stmt
    : FOR LPARENTHESIS
      { ST->addScope(); }
      for_init SEMICOLON
      {
          std::string condLabel = QG->newLabel();
          std::string bodyLabel = QG->newLabel();
          std::string updateLabel = QG->newLabel();
          std::string endLabel = QG->newLabel();
          QG->emit("LABEL", condLabel, "-", "-");
          CTX->continueLabels.push_back(updateLabel);
          CTX->breakLabels.push_back(endLabel);
          SA->enterLoop();
          $<sval>$ = strdup((condLabel + "," + bodyLabel + "," +
                             updateLabel + "," + endLabel).c_str());
      }
      expr_opt SEMICOLON
      {
          std::string labels($<sval>6);
          size_t p1 = labels.find(',');
          size_t p2 = labels.find(',', p1 + 1);
          size_t p3 = labels.find(',', p2 + 1);
          std::string bodyLabel = labels.substr(p1 + 1, p2 - p1 - 1);
          std::string endLabel = labels.substr(p3 + 1);
          if ($7->place != "") {
              QG->emit("JMP_FALSE", $7->place, "-", endLabel);
          }
          free($7);
          QG->emit("JMP", "-", "-", bodyLabel);
          std::string updateLabel = labels.substr(p2 + 1, p3 - p2 - 1);
          QG->emit("LABEL", updateLabel, "-", "-");
      }
      for_update RPARENTHESIS
      {
          std::string labels($<sval>6);
          size_t p1 = labels.find(',');
          size_t p2 = labels.find(',', p1 + 1);
          std::string condLabel = labels.substr(0, p1);
          std::string bodyLabel = labels.substr(p1 + 1, p2 - p1 - 1);
          QG->emit("JMP", "-", "-", condLabel);
          QG->emit("LABEL", bodyLabel, "-", "-");
      }
      stmt
      {
          std::string labels($<sval>6);
          size_t p1 = labels.find(',');
          size_t p2 = labels.find(',', p1 + 1);
          size_t p3 = labels.find(',', p2 + 1);
          std::string updateLabel = labels.substr(p2 + 1, p3 - p2 - 1);
          std::string endLabel = labels.substr(p3 + 1);
          QG->emit("JMP", "-", "-", updateLabel);
          QG->emit("LABEL", endLabel, "-", "-");
          CTX->breakLabels.pop_back();
          CTX->continueLabels.pop_back();
          SA->exitLoop();
          ST->LeaveScope();
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
    |           { $$ = new ExprAttr(); $$->place = ""; $$->type = Type::BOOL; }
    ;


switch_stmt
    : SWITCH LPARENTHESIS expr RPARENTHESIS
      {
          ST->addScope();
          SA->enterSwitch();
          std::string endLabel = QG->newLabel();
          CTX->breakLabels.push_back(endLabel);
          CTX->switchExprStack.push_back($3->place);
          $<sval>$ = strdup(($3->place + "," + endLabel).c_str());
          free($3);
      }
      LBRACE case_list RBRACE
      {
          std::string labels($<sval>5);
          size_t p = labels.find(',');
          std::string endLabel = labels.substr(p + 1);
          QG->emit("LABEL", endLabel, "-", "-");
          CTX->breakLabels.pop_back();
          if(!CTX->switchExprStack.empty()){
            CTX->switchExprStack.pop_back();
          }
          ST->LeaveScope();
          SA->exitSwitch();
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
          std::string caseLabel = QG->newLabel();
          std::string nextCase = QG->newLabel();
          
          std::string temp = QG->newTemp();
            std::string switchExpr = CTX->switchExprStack.back();
          QG->emit("EQ", switchExpr, $2->place, temp);

          free($2);
          QG->emit("JMP_FALSE", temp, "-", nextCase);
          QG->emit("LABEL", caseLabel, "-", "-");
          $<sval>$ = strdup(nextCase.c_str());
      }
      stmt_list
      {
          QG->emit("LABEL", std::string($<sval>4), "-", "-");
          free($<sval>4);
      }
    | DEFAULT COLON
      {
          std::string defLabel = QG->newLabel();
          QG->emit("LABEL", defLabel, "-", "-");
      }
      stmt_list
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
          SA->validateReturn(SA->getCurrentFunctionReturnType(), nullptr, yylineno);
          QG->emit("RETURN", "-", "-", "-");
      }
    | RETURN expr SEMICOLON
      {
          ExprAttr val = *$2;
          SA->validateReturn(SA->getCurrentFunctionReturnType(), &val, yylineno);
          QG->emit("RETURN", val.place, "-", "-");
          free($2);
      }
    ;


arg_list_opt
    : { CTX->passedArgs.clear(); }
      arg_list
    |   { CTX->passedArgs.clear(); }
    ;

arg_list
    : arg_list COMMA expr  { CTX->passedArgs.push_back(*$3); free($3); }
    | expr                 { CTX->passedArgs.push_back(*$1); free($1); }
    | error RPARENTHESIS   { yyerrok; yyclearin; }
    ;

expr
    : assign_expr { $$ = $1; }
    ;

assign_expr
    : logical_or_expr { $$ = $1; }
    | IDENTIFIER ASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Symbol *sym = ST->lookup($1);
          bool typeOk = false;
          if (isAssignable && sym) {
              typeOk = SA->validateAssignment(rhs, sym->dataType, yylineno);
          }
          if (isAssignable && sym && typeOk) {
              SA->coerce(rhs, sym->dataType, yylineno);
              sym->isInitialized = true;
              QG->emit("ASSIGN", rhs.place, "-", sym->irName);
          }
          $$ = new ExprAttr();
          $$->place = sym->irName;
          $$->type = (isAssignable && sym && typeOk) ? sym->dataType : Type::UNKNOWN;
          free($1);
      }
    | IDENTIFIER PLUSASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "PLUSASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("ADD", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER MINUSASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "MINUSASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("SUB", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER STARASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "STARASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("MUL", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER DIVASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "DIVASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("DIV", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER MODASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "MODASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("MOD", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER LSHIFTASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "LSHIFTASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("SHL", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER RSHIFTASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "RSHIFTASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("SHR", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER XORASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "XORASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("BXOR", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER ANDASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "ANDASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("BAND", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    | IDENTIFIER ORASSIGN assign_expr
      {
          bool isAssignable = SA->checkAssignable($1, yylineno);
          ExprAttr rhs = *$3;
          free($3);
          Type resultType = Type::UNKNOWN;
          if (isAssignable) {
              ExprAttr lhs = SA->resolveIdentifier($1, yylineno);
              resultType = SA->checkBinaryOper(lhs, rhs, "ORASSIGN", yylineno);
              if (resultType != Type::UNKNOWN) {
                  std::string temp = QG->newTemp();
                  QG->emit("BOR", lhs.place, rhs.place, temp);
                  QG->emit("ASSIGN", temp, "-", lhs.place);
              }
          }
          $$ = new ExprAttr();
          $$->place = ST->getIRName($1);
          $$->type = resultType;
          free($1);
      }
    ;

logical_or_expr
    : logical_or_expr OR logical_and_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "OR", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("OR", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | logical_and_expr { $$ = $1; }
    ;

logical_and_expr
    : logical_and_expr AND bitwise_or_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "AND", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("AND", $1->place, $3->place, temp);
          }
          free ($1);
          free ($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | bitwise_or_expr { $$ = $1; }
    ;

bitwise_or_expr
    : bitwise_or_expr BITWISEOR bitwise_xor_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "BITWISEOR", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("BOR", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | bitwise_xor_expr { $$ = $1; }
    ;

bitwise_xor_expr
    : bitwise_xor_expr BITWISEXOR bitwise_and_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "BITWISEXOR", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("BXOR", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | bitwise_and_expr { $$ = $1; }
    ;

bitwise_and_expr
    : bitwise_and_expr BITWISEAND equality_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "BITWISEAND", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("BAND", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | equality_expr { $$ = $1; }
    ;

equality_expr
    : equality_expr EQ relational_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "EQ", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("EQ", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | equality_expr NEQ relational_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "NEQ", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("NEQ", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | relational_expr { $$ = $1; }
    ;

relational_expr
    : relational_expr LT shift_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "LT", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("LT", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | relational_expr GT shift_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "GT", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("GT", $1->place, $3->place, temp);
          }
          free ($1);
          free ($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | relational_expr LEQ shift_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "LEQ", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("LEQ", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | relational_expr GEQ shift_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "GEQ", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("GEQ", $1->place, $3->place, temp);
          }
          free($1);
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | shift_expr { $$ = $1; }
    ;

shift_expr
    : shift_expr LSHIFT additive_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "LSHIFT", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("SHL", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | shift_expr RSHIFT additive_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "RSHIFT", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("SHR", $1->place, $3->place, temp);
          }
          free ($1); 
          free ($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | additive_expr { $$ = $1; }
    ;

additive_expr
    : additive_expr PLUS multiplicative_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "PLUS", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("ADD", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | additive_expr MINUS multiplicative_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "MINUS", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("SUB", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr
    : multiplicative_expr STAR unary_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "STAR", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("MUL", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | multiplicative_expr DIV unary_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "DIV", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("DIV", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | multiplicative_expr MOD unary_expr
      {
          Type t = SA->checkBinaryOper(*$1, *$3, "MOD", yylineno);
          std::string temp;
          if (t != Type::UNKNOWN) {
              temp = QG->newTemp();
              QG->emit("MOD", $1->place, $3->place, temp);
          }
          free($1); 
          free($3);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = t;
      }
    | unary_expr { $$ = $1; }
    ;

unary_expr
    : postfix_expr { $$ = $1; }
    | INC IDENTIFIER
      {
          $$ = new ExprAttr();
          bool isAssignable = SA->checkAssignable($2, yylineno);
          if (isAssignable) {
              ExprAttr id = SA->resolveIdentifier($2, yylineno);
              QG->emit("INC", id.place, "-", id.place);
              $$->place = id.place;
              $$->type = id.type;
          } else {
              $$->place = std::string($2);
              $$->type = Type::UNKNOWN;
          }
          free($2);
      }
    | DEC IDENTIFIER
      {
          $$ = new ExprAttr();
          bool isAssignable = SA->checkAssignable($2, yylineno);
          if (isAssignable) {
              ExprAttr id = SA->resolveIdentifier($2, yylineno);
              QG->emit("DEC", id.place, "-", id.place);
              $$->place = id.place;
              $$->type = id.type;
          } else {
              $$->place = std::string($2);
              $$->type = Type::UNKNOWN;
          }
          free($2);
      }
    | NOT unary_expr
      {
          std::string temp = QG->newTemp();
          QG->emit("NOT", $2->place, "-", temp);
          free($2);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = Type::BOOL;
      }
    | BITWISENOT unary_expr
      {
          Type t = SA->checkBinaryOper(*$2, *$2, "BITWISENOT", yylineno);
          $$ = new ExprAttr();
          if (t != Type::UNKNOWN) {
              std::string temp = QG->newTemp();
              QG->emit("BNOT", $2->place, "-", temp);
              $$->place = temp;
              $$->type = Type::INT;
          } else {
              $$->place = $2->place;
              $$->type = Type::UNKNOWN;
          }
          free($2);
      }
    | MINUS unary_expr %prec UMINUS
      {
          std::string temp = QG->newTemp();
          QG->emit("UMINUS", $2->place, "-", temp);
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = $2->type;
          free($2);
      }
    ;

postfix_expr
    : primary_expr { $$ = $1; }
    | IDENTIFIER INC
      {
          $$ = new ExprAttr();
          bool isAssignable = SA->checkAssignable($1, yylineno);
          if (isAssignable) {
              ExprAttr id = SA->resolveIdentifier($1, yylineno);
              std::string temp = QG->newTemp();
              QG->emit("ASSIGN", id.place, "-", temp);
              QG->emit("INC", id.place, "-", id.place);
              $$->place = temp;
              $$->type = id.type;
          } else {
              $$->place = std::string($1);
              $$->type = Type::UNKNOWN;
          }
          free($1);
      }
    | IDENTIFIER DEC
      {
          $$ = new ExprAttr();
          bool isAssignable = SA->checkAssignable($1, yylineno);
          if (isAssignable) {
              ExprAttr id = SA->resolveIdentifier($1, yylineno);
              std::string temp = QG->newTemp();
              QG->emit("ASSIGN", id.place, "-", temp);
              QG->emit("DEC", id.place, "-", id.place);
              $$->place = temp;
              $$->type = id.type;
          } else {
              $$->place = std::string($1);
              $$->type = Type::UNKNOWN;
          }
          free($1);
      }
    ;

primary_expr
    : IDENTIFIER
      {
          $$ = new ExprAttr(SA->resolveIdentifier($1, yylineno));
          free($1);
      }
    | IDENTIFIER LPARENTHESIS
      { CTX->passedArgs.clear(); }
      arg_list_opt RPARENTHESIS
      {
          Type retType = SA->validateFunctionCall(
              $1, CTX->passedArgs, yylineno);
          for (auto &arg : CTX->passedArgs) {
              QG->emit("PARAM", arg.place, "-", "-");
          }
          std::string temp = QG->newTemp();
          if(retType != Type::VOID)
            QG->emit("CALL", std::string($1),
                   std::to_string(CTX->passedArgs.size()), temp);
          else 
            QG->emit("CALL", std::string($1),
                   std::to_string(CTX->passedArgs.size()), "-");
          $$ = new ExprAttr();
          $$->place = temp;
          $$->type = retType;
          free($1);
      }
    | literal { $$ = $1; }
    | LPARENTHESIS expr RPARENTHESIS { $$ = $2; }
    ;

literal
    : INT_LITERAL
      {
          $$ = new ExprAttr();
          $$->place = std::to_string($1);
          $$->type = Type::INT;
      }
    | FLOAT_LITERAL
      {
          $$ = new ExprAttr();
          $$->place = std::to_string($1);
          $$->type = Type::FLOAT;
      }
    | CHAR_LITERAL
      {
          $$ = new ExprAttr();
          $$->place = "'" + std::string(1, $1) + "'";
          $$->type = Type::CHAR;
      }
    | BOOL_LITERAL
      {
          $$ = new ExprAttr();
          $$->place = $1 ? "true" : "false";
          $$->type = Type::BOOL;
      }
    | STRING_LITERAL
      {
          $$ = new ExprAttr();
          $$->place = std::string($1);
          $$->type = Type::STRING;
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