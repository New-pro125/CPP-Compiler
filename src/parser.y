%{
#include <cstdio>

// NOLINTBEGIN(readability-identifier-naming)
int yylex();
void yyerror(const char* s);
extern int yylineno;
// NOLINTEND(readability-identifier-naming)
%}

%define parse.error verbose
%glr-parser

%union {
    int ival;
    long long lval;
    double dval;
    char cval;
    char* sval;
}

%token INT FLOAT DOUBLE CHAR BOOL VOID STRING CONST
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
    : INT
    | FLOAT
    | DOUBLE
    | CHAR
    | BOOL
    | VOID
    | STRING
    ;

var_decl
    : type_spec declarator_list SEMICOLON
    | CONST type_spec declarator_list SEMICOLON
    ;

declarator_list
    : declarator_list COMMA declarator
    | declarator
    ;

declarator
    : IDENTIFIER
    | IDENTIFIER ASSIGN expr
    ;

func_decl
    : type_spec IDENTIFIER LPARENTHESIS param_list_opt RPARENTHESIS compound_stmt_body
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
    | CONST type_spec IDENTIFIER
    | type_spec IDENTIFIER ASSIGN literal
    | CONST type_spec IDENTIFIER ASSIGN literal
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
    : LBRACE stmt_list RBRACE
    ;

compound_stmt_body
    : LBRACE stmt_list RBRACE
    ;

if_stmt
    : IF LPARENTHESIS expr RPARENTHESIS stmt %prec LOWER_THAN_ELSE
    | IF LPARENTHESIS expr RPARENTHESIS stmt ELSE stmt
    ;

while_stmt
    : WHILE LPARENTHESIS expr RPARENTHESIS stmt
    ;

do_while_stmt
    : DO stmt WHILE LPARENTHESIS expr RPARENTHESIS SEMICOLON
    ;

for_stmt
    : FOR LPARENTHESIS for_init SEMICOLON expr_opt SEMICOLON for_update RPARENTHESIS stmt
    ;

for_init
    : for_var_decl
    | expr
    |
    ;

for_var_decl
    : type_spec declarator_list
    | CONST type_spec declarator_list
    ;

for_update
    : expr
    |
    ;

expr_opt
    : expr
    |
    ;

switch_stmt
    : SWITCH LPARENTHESIS expr RPARENTHESIS LBRACE case_list RBRACE
    ;

case_list
    : case_list case_item
    |
    ;

case_item
    : CASE literal COLON stmt_list
    | DEFAULT COLON stmt_list
    ;

break_stmt
    : BREAK SEMICOLON
    ;

continue_stmt
    : CONTINUE SEMICOLON
    ;

return_stmt
    : RETURN SEMICOLON
    | RETURN expr SEMICOLON
    ;

arg_list_opt
    : arg_list
    |
    ;

arg_list
    : arg_list COMMA expr
    | expr
    | error RPARENTHESIS { yyerrok; yyclearin; }
    ;

expr
    : assign_expr
    ;

assign_expr
    : logical_or_expr
    | IDENTIFIER ASSIGN assign_expr
    | IDENTIFIER PLUSASSIGN assign_expr
    | IDENTIFIER MINUSASSIGN assign_expr
    | IDENTIFIER STARASSIGN assign_expr
    | IDENTIFIER DIVASSIGN assign_expr
    | IDENTIFIER LSHIFTASSIGN assign_expr
    | IDENTIFIER RSHIFTASSIGN assign_expr
    | IDENTIFIER XORASSIGN assign_expr
    | IDENTIFIER ANDASSIGN assign_expr
    | IDENTIFIER ORASSIGN assign_expr
    | IDENTIFIER MODASSIGN assign_expr
    ;

logical_or_expr
    : logical_or_expr OR logical_and_expr
    | logical_and_expr
    ;

logical_and_expr
    : logical_and_expr AND bitwise_or_expr
    | bitwise_or_expr
    ;

bitwise_or_expr
    : bitwise_or_expr BITWISEOR bitwise_xor_expr
    | bitwise_xor_expr
    ;

bitwise_xor_expr
    : bitwise_xor_expr BITWISEXOR bitwise_and_expr
    | bitwise_and_expr
    ;

bitwise_and_expr
    : bitwise_and_expr BITWISEAND equality_expr
    | equality_expr
    ;

equality_expr
    : equality_expr EQ relational_expr
    | equality_expr NEQ relational_expr
    | relational_expr
    ;

relational_expr
    : relational_expr LT shift_expr
    | relational_expr GT shift_expr
    | relational_expr LEQ shift_expr
    | relational_expr GEQ shift_expr
    | shift_expr
    ;

shift_expr
    : shift_expr LSHIFT additive_expr
    | shift_expr RSHIFT additive_expr
    | additive_expr
    ;

additive_expr
    : additive_expr PLUS multiplicative_expr
    | additive_expr MINUS multiplicative_expr
    | multiplicative_expr
    ;

multiplicative_expr
    : multiplicative_expr STAR unary_expr
    | multiplicative_expr DIV unary_expr
    | multiplicative_expr MOD unary_expr
    | unary_expr
    ;

unary_expr
    : postfix_expr
    | INC IDENTIFIER
    | DEC IDENTIFIER
    | NOT unary_expr
    | BITWISENOT unary_expr
    | MINUS unary_expr %prec UMINUS
    ;

postfix_expr
    : primary_expr
    | IDENTIFIER INC
    | IDENTIFIER DEC
    ;

primary_expr
    : IDENTIFIER
    | IDENTIFIER LPARENTHESIS arg_list_opt RPARENTHESIS
    | literal
    | LPARENTHESIS expr RPARENTHESIS
    ;

literal
    : INT_LITERAL
    | FLOAT_LITERAL
    | CHAR_LITERAL
    | BOOL_LITERAL
    | STRING_LITERAL
    ;

%%

void yyerror(const char* s) {
    std::fprintf(stderr, "Syntax error [line %d]: %s\n", yylineno, s);
}

