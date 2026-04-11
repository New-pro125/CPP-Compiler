%option noyywrap
%option yylineno

%{
    #include <cstdlib>
    #include <string>
    #include <cstring>
    #include "parser.tab.h"
%}

DIGIT        [0-9]
INTEGER      {DIGIT}+
EXPONENT     [Ee][+-]?{INTEGER}
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*
FLOATLITERAL ({INTEGER}"."{DIGIT}*{EXPONENT}?|{DIGIT}*"."{DIGIT}+{EXPONENT}?|{INTEGER}{EXPONENT})
CHARLITERAL  \'(\\.|[^\\\n\'])\'
STRINGLITERAL \"(\\.|[^"\\])*\"
%%

"int"                           {return INT;}
"float"                         {return FLOAT;}
"bool"                          {return BOOL;}
"true"                          {yylval.ival = 1;return BOOL_LITERAL;}
"false"                         {yylval.ival = 0;return BOOL_LITERAL;}
"char"                          {return CHAR;}
"string"                        {return STRING;}
"void"                          {return VOID;}
"const"                         {return CONST;}
"if"                            {return IF;}
"else"                          {return ELSE;}
"while"                         {return WHILE;}
"for"                           {return FOR;}
"do"                            {return DO;}
"continue"                      {return CONTINUE;}
"break"                         {return BREAK;}
"switch"                        {return SWITCH;}
"case"                          {return CASE;}
"default"                       {return DEFAULT;}
"return"                        {return RETURN;}
"+"                             {return PLUS;}
"-"                             {return MINUS;}
"*"                             {return STAR;}
"/"                             {return DIV;}
"%"                             {return MOD;}
"++"                            {return INC;}
"--"                            {return DEC;}
"+="                            {return PLUSASSIGN;}
"-="                            {return MINUSASSIGN;}
"*="                            {return STARASSIGN;}
"/="                            {return DIVASSIGN;}
"%="                            {return MODASSIGN;}
"<"                             {return LT;}
">"                             {return GT;}
"="                             {return ASSIGN;}
"<="                            {return LEQ;}
">="                            {return GEQ;}
"=="                            {return EQ;}
"!="                            {return NEQ;}
"!"                             {return NOT;}
"&&"                            {return AND;}
"||"                            {return OR;}
"~"                             {return BITWISENOT;}
"^"                             {return BITWISEXOR;}
"&"                             {return BITWISEAND;}
"|"                             {return BITWISEOR;}
">>"                            {return RSHIFT;}
"<<"                            {return LSHIFT;}
"^="                            {return XORASSIGN;}
"&="                            {return ANDASSIGN;}
"|="                            {return ORASSIGN;}
">>="                           {return RSHIFTASSIGN;}
"<<="                           {return LSHIFTASSIGN;}
"("                             {return LPARENTHESIS;}
")"                             {return RPARENTHESIS;}
"["                             {return LBRACKET;}
"]"                             {return RBRACKET;}
"{"                             {return LBRACE;}
"}"                             {return RBRACE;}
","                             {return COMMA;}
";"                             {return SEMICOLON;}
":"                             {return COLON;}

{FLOATLITERAL}                  {yylval.dval = atof(yytext); return FLOAT_LITERAL;}
{INTEGER}                       {yylval.ival = atoi(yytext); return INT_LITERAL;}
{CHARLITERAL}                   {
                                    if(yytext[1]== '\\') {
                                        switch(yytext[2]){
                                            case 'n': yylval.cval = '\n'; break;
                                            case 't': yylval.cval = '\t'; break;
                                            case 'r': yylval.cval = '\r'; break;
                                            case '\\': yylval.cval = '\\'; break;
                                            case '\'': yylval.cval = '\''; break;
                                            case '"': yylval.cval = '"'; break;
                                            default: yylval.cval = yytext[2]; break; 
                                        }
                                    } else {
                                        yylval.cval = yytext[1];
                                    }
                                    return CHAR_LITERAL;
                                }
{STRINGLITERAL}                 {yylval.sval = strdup(yytext); return STRING_LITERAL;}
{IDENTIFIER}                    {yylval.sval = strdup(yytext); return IDENTIFIER;}
"//"[^\n]*                      {/* Skip Comment*/}
"/*"([^*]|\*+[*/])*"*/"         {/* Skip block Comment*/}
[ \t\r]+                        {/* Skip spaces*/}
\n                              {/* Skip start new line characters*/}
.                               {fprintf(stderr,"Syntax Error: Unrecognized character '%s' at line %d \n",yytext,yylineno);}
%%