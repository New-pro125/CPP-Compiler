/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_AHMED_DESKTOP_UNIVERSITY_COMPILER_PROJECT_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_AHMED_DESKTOP_UNIVERSITY_COMPILER_PROJECT_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 47 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"

    #include "types.h"
    #include "parser_context.h"

#line 54 "/home/ahmed/Desktop/University/compiler/Project/build/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    FLOAT = 259,                   /* FLOAT  */
    CHAR = 260,                    /* CHAR  */
    BOOL = 261,                    /* BOOL  */
    VOID = 262,                    /* VOID  */
    STRING = 263,                  /* STRING  */
    CONST = 264,                   /* CONST  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    WHILE = 267,                   /* WHILE  */
    DO = 268,                      /* DO  */
    FOR = 269,                     /* FOR  */
    SWITCH = 270,                  /* SWITCH  */
    CASE = 271,                    /* CASE  */
    DEFAULT = 272,                 /* DEFAULT  */
    BREAK = 273,                   /* BREAK  */
    CONTINUE = 274,                /* CONTINUE  */
    RETURN = 275,                  /* RETURN  */
    INC = 276,                     /* INC  */
    DEC = 277,                     /* DEC  */
    PLUSASSIGN = 278,              /* PLUSASSIGN  */
    MINUSASSIGN = 279,             /* MINUSASSIGN  */
    STARASSIGN = 280,              /* STARASSIGN  */
    DIVASSIGN = 281,               /* DIVASSIGN  */
    MODASSIGN = 282,               /* MODASSIGN  */
    EQ = 283,                      /* EQ  */
    NEQ = 284,                     /* NEQ  */
    LEQ = 285,                     /* LEQ  */
    GEQ = 286,                     /* GEQ  */
    AND = 287,                     /* AND  */
    OR = 288,                      /* OR  */
    ASSIGN = 289,                  /* ASSIGN  */
    PLUS = 290,                    /* PLUS  */
    MINUS = 291,                   /* MINUS  */
    STAR = 292,                    /* STAR  */
    DIV = 293,                     /* DIV  */
    MOD = 294,                     /* MOD  */
    NOT = 295,                     /* NOT  */
    LT = 296,                      /* LT  */
    GT = 297,                      /* GT  */
    LPARENTHESIS = 298,            /* LPARENTHESIS  */
    RPARENTHESIS = 299,            /* RPARENTHESIS  */
    LBRACE = 300,                  /* LBRACE  */
    RBRACE = 301,                  /* RBRACE  */
    LBRACKET = 302,                /* LBRACKET  */
    RBRACKET = 303,                /* RBRACKET  */
    COMMA = 304,                   /* COMMA  */
    SEMICOLON = 305,               /* SEMICOLON  */
    COLON = 306,                   /* COLON  */
    IDENTIFIER = 307,              /* IDENTIFIER  */
    STRING_LITERAL = 308,          /* STRING_LITERAL  */
    INT_LITERAL = 309,             /* INT_LITERAL  */
    BOOL_LITERAL = 310,            /* BOOL_LITERAL  */
    FLOAT_LITERAL = 311,           /* FLOAT_LITERAL  */
    CHAR_LITERAL = 312,            /* CHAR_LITERAL  */
    BITWISEXOR = 313,              /* BITWISEXOR  */
    BITWISEAND = 314,              /* BITWISEAND  */
    BITWISEOR = 315,               /* BITWISEOR  */
    RSHIFT = 316,                  /* RSHIFT  */
    LSHIFT = 317,                  /* LSHIFT  */
    BITWISENOT = 318,              /* BITWISENOT  */
    LSHIFTASSIGN = 319,            /* LSHIFTASSIGN  */
    RSHIFTASSIGN = 320,            /* RSHIFTASSIGN  */
    XORASSIGN = 321,               /* XORASSIGN  */
    ANDASSIGN = 322,               /* ANDASSIGN  */
    ORASSIGN = 323,                /* ORASSIGN  */
    LOWER_THAN_ELSE = 324,         /* LOWER_THAN_ELSE  */
    UMINUS = 325                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 52 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"

    int ival;
    float dval;
    char cval;
    char* sval;
    Type typeval;
    ExprAttr* exprval;

#line 150 "/home/ahmed/Desktop/University/compiler/Project/build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_AHMED_DESKTOP_UNIVERSITY_COMPILER_PROJECT_BUILD_PARSER_TAB_H_INCLUDED  */
