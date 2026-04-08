/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

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

#ifndef YY_YY_HOME_AHMED_DESKTOP_UNIVERSITY_COMPILER_PROJECT_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_AHMED_DESKTOP_UNIVERSITY_COMPILER_PROJECT_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
    DOUBLE = 260,                  /* DOUBLE  */
    CHAR = 261,                    /* CHAR  */
    BOOL = 262,                    /* BOOL  */
    VOID = 263,                    /* VOID  */
    STRING = 264,                  /* STRING  */
    CONST = 265,                   /* CONST  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    WHILE = 268,                   /* WHILE  */
    DO = 269,                      /* DO  */
    FOR = 270,                     /* FOR  */
    SWITCH = 271,                  /* SWITCH  */
    CASE = 272,                    /* CASE  */
    DEFAULT = 273,                 /* DEFAULT  */
    BREAK = 274,                   /* BREAK  */
    CONTINUE = 275,                /* CONTINUE  */
    RETURN = 276,                  /* RETURN  */
    INC = 277,                     /* INC  */
    DEC = 278,                     /* DEC  */
    PLUSASSIGN = 279,              /* PLUSASSIGN  */
    MINUSASSIGN = 280,             /* MINUSASSIGN  */
    STARASSIGN = 281,              /* STARASSIGN  */
    DIVASSIGN = 282,               /* DIVASSIGN  */
    MODASSIGN = 283,               /* MODASSIGN  */
    EQ = 284,                      /* EQ  */
    NEQ = 285,                     /* NEQ  */
    LEQ = 286,                     /* LEQ  */
    GEQ = 287,                     /* GEQ  */
    AND = 288,                     /* AND  */
    OR = 289,                      /* OR  */
    ASSIGN = 290,                  /* ASSIGN  */
    PLUS = 291,                    /* PLUS  */
    MINUS = 292,                   /* MINUS  */
    STAR = 293,                    /* STAR  */
    DIV = 294,                     /* DIV  */
    MOD = 295,                     /* MOD  */
    NOT = 296,                     /* NOT  */
    LT = 297,                      /* LT  */
    GT = 298,                      /* GT  */
    LPARENTHESIS = 299,            /* LPARENTHESIS  */
    RPARENTHESIS = 300,            /* RPARENTHESIS  */
    LBRACE = 301,                  /* LBRACE  */
    RBRACE = 302,                  /* RBRACE  */
    LBRACKET = 303,                /* LBRACKET  */
    RBRACKET = 304,                /* RBRACKET  */
    COMMA = 305,                   /* COMMA  */
    SEMICOLON = 306,               /* SEMICOLON  */
    COLON = 307,                   /* COLON  */
    IDENTIFIER = 308,              /* IDENTIFIER  */
    STRING_LITERAL = 309,          /* STRING_LITERAL  */
    INT_LITERAL = 310,             /* INT_LITERAL  */
    BOOL_LITERAL = 311,            /* BOOL_LITERAL  */
    FLOAT_LITERAL = 312,           /* FLOAT_LITERAL  */
    CHAR_LITERAL = 313,            /* CHAR_LITERAL  */
    BITWISEXOR = 314,              /* BITWISEXOR  */
    BITWISEAND = 315,              /* BITWISEAND  */
    BITWISEOR = 316,               /* BITWISEOR  */
    RSHIFT = 317,                  /* RSHIFT  */
    LSHIFT = 318,                  /* LSHIFT  */
    BITWISENOT = 319,              /* BITWISENOT  */
    LSHIFTASSIGN = 320,            /* LSHIFTASSIGN  */
    RSHIFTASSIGN = 321,            /* RSHIFTASSIGN  */
    XORASSIGN = 322,               /* XORASSIGN  */
    ANDASSIGN = 323,               /* ANDASSIGN  */
    ORASSIGN = 324,                /* ORASSIGN  */
    LOWER_THAN_ELSE = 325,         /* LOWER_THAN_ELSE  */
    UMINUS = 326                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"

    int ival;
    long long lval;
    double dval;
    char cval;
    char* sval;

#line 138 "/home/ahmed/Desktop/University/compiler/Project/build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_AHMED_DESKTOP_UNIVERSITY_COMPILER_PROJECT_BUILD_PARSER_TAB_H_INCLUDED  */
