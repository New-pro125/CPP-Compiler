/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"

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

#line 115 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_CHAR = 5,                       /* CHAR  */
  YYSYMBOL_BOOL = 6,                       /* BOOL  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_CONST = 9,                      /* CONST  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_DO = 13,                        /* DO  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_SWITCH = 15,                    /* SWITCH  */
  YYSYMBOL_CASE = 16,                      /* CASE  */
  YYSYMBOL_DEFAULT = 17,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 18,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 19,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 20,                    /* RETURN  */
  YYSYMBOL_INC = 21,                       /* INC  */
  YYSYMBOL_DEC = 22,                       /* DEC  */
  YYSYMBOL_PLUSASSIGN = 23,                /* PLUSASSIGN  */
  YYSYMBOL_MINUSASSIGN = 24,               /* MINUSASSIGN  */
  YYSYMBOL_STARASSIGN = 25,                /* STARASSIGN  */
  YYSYMBOL_DIVASSIGN = 26,                 /* DIVASSIGN  */
  YYSYMBOL_MODASSIGN = 27,                 /* MODASSIGN  */
  YYSYMBOL_EQ = 28,                        /* EQ  */
  YYSYMBOL_NEQ = 29,                       /* NEQ  */
  YYSYMBOL_LEQ = 30,                       /* LEQ  */
  YYSYMBOL_GEQ = 31,                       /* GEQ  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_ASSIGN = 34,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 35,                      /* PLUS  */
  YYSYMBOL_MINUS = 36,                     /* MINUS  */
  YYSYMBOL_STAR = 37,                      /* STAR  */
  YYSYMBOL_DIV = 38,                       /* DIV  */
  YYSYMBOL_MOD = 39,                       /* MOD  */
  YYSYMBOL_NOT = 40,                       /* NOT  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LPARENTHESIS = 43,              /* LPARENTHESIS  */
  YYSYMBOL_RPARENTHESIS = 44,              /* RPARENTHESIS  */
  YYSYMBOL_LBRACE = 45,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 46,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 47,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 48,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 49,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 50,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 51,                     /* COLON  */
  YYSYMBOL_IDENTIFIER = 52,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 53,            /* STRING_LITERAL  */
  YYSYMBOL_INT_LITERAL = 54,               /* INT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 55,              /* BOOL_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 56,             /* FLOAT_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 57,              /* CHAR_LITERAL  */
  YYSYMBOL_BITWISEXOR = 58,                /* BITWISEXOR  */
  YYSYMBOL_BITWISEAND = 59,                /* BITWISEAND  */
  YYSYMBOL_BITWISEOR = 60,                 /* BITWISEOR  */
  YYSYMBOL_RSHIFT = 61,                    /* RSHIFT  */
  YYSYMBOL_LSHIFT = 62,                    /* LSHIFT  */
  YYSYMBOL_BITWISENOT = 63,                /* BITWISENOT  */
  YYSYMBOL_LSHIFTASSIGN = 64,              /* LSHIFTASSIGN  */
  YYSYMBOL_RSHIFTASSIGN = 65,              /* RSHIFTASSIGN  */
  YYSYMBOL_XORASSIGN = 66,                 /* XORASSIGN  */
  YYSYMBOL_ANDASSIGN = 67,                 /* ANDASSIGN  */
  YYSYMBOL_ORASSIGN = 68,                  /* ORASSIGN  */
  YYSYMBOL_LOWER_THAN_ELSE = 69,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 70,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_program = 72,                   /* program  */
  YYSYMBOL_decl_list = 73,                 /* decl_list  */
  YYSYMBOL_decl = 74,                      /* decl  */
  YYSYMBOL_type_spec = 75,                 /* type_spec  */
  YYSYMBOL_var_decl = 76,                  /* var_decl  */
  YYSYMBOL_77_1 = 77,                      /* $@1  */
  YYSYMBOL_declarator_list = 78,           /* declarator_list  */
  YYSYMBOL_declarator = 79,                /* declarator  */
  YYSYMBOL_func_decl = 80,                 /* func_decl  */
  YYSYMBOL_81_2 = 81,                      /* $@2  */
  YYSYMBOL_82_3 = 82,                      /* $@3  */
  YYSYMBOL_param_list_opt = 83,            /* param_list_opt  */
  YYSYMBOL_param_list = 84,                /* param_list  */
  YYSYMBOL_param_decl = 85,                /* param_decl  */
  YYSYMBOL_stmt = 86,                      /* stmt  */
  YYSYMBOL_stmt_guard = 87,                /* stmt_guard  */
  YYSYMBOL_stmt_core = 88,                 /* stmt_core  */
  YYSYMBOL_stmt_list = 89,                 /* stmt_list  */
  YYSYMBOL_block_item = 90,                /* block_item  */
  YYSYMBOL_expr_stmt = 91,                 /* expr_stmt  */
  YYSYMBOL_compound_stmt = 92,             /* compound_stmt  */
  YYSYMBOL_93_4 = 93,                      /* $@4  */
  YYSYMBOL_compound_stmt_func = 94,        /* compound_stmt_func  */
  YYSYMBOL_if_condition_prefix = 95,       /* if_condition_prefix  */
  YYSYMBOL_if_stmt = 96,                   /* if_stmt  */
  YYSYMBOL_97_5 = 97,                      /* @5  */
  YYSYMBOL_while_stmt = 98,                /* while_stmt  */
  YYSYMBOL_99_6 = 99,                      /* @6  */
  YYSYMBOL_100_7 = 100,                    /* $@7  */
  YYSYMBOL_do_while_stmt = 101,            /* do_while_stmt  */
  YYSYMBOL_102_8 = 102,                    /* @8  */
  YYSYMBOL_103_9 = 103,                    /* $@9  */
  YYSYMBOL_for_stmt = 104,                 /* for_stmt  */
  YYSYMBOL_105_10 = 105,                   /* $@10  */
  YYSYMBOL_106_11 = 106,                   /* @11  */
  YYSYMBOL_107_12 = 107,                   /* $@12  */
  YYSYMBOL_108_13 = 108,                   /* $@13  */
  YYSYMBOL_for_init = 109,                 /* for_init  */
  YYSYMBOL_for_var_decl = 110,             /* for_var_decl  */
  YYSYMBOL_111_14 = 111,                   /* $@14  */
  YYSYMBOL_112_15 = 112,                   /* $@15  */
  YYSYMBOL_for_update = 113,               /* for_update  */
  YYSYMBOL_expr_opt = 114,                 /* expr_opt  */
  YYSYMBOL_switch_stmt = 115,              /* switch_stmt  */
  YYSYMBOL_116_16 = 116,                   /* @16  */
  YYSYMBOL_case_list = 117,                /* case_list  */
  YYSYMBOL_case_item = 118,                /* case_item  */
  YYSYMBOL_119_17 = 119,                   /* $@17  */
  YYSYMBOL_120_18 = 120,                   /* $@18  */
  YYSYMBOL_121_19 = 121,                   /* $@19  */
  YYSYMBOL_break_stmt = 122,               /* break_stmt  */
  YYSYMBOL_continue_stmt = 123,            /* continue_stmt  */
  YYSYMBOL_return_stmt = 124,              /* return_stmt  */
  YYSYMBOL_arg_list_opt = 125,             /* arg_list_opt  */
  YYSYMBOL_arg_list = 126,                 /* arg_list  */
  YYSYMBOL_expr = 127,                     /* expr  */
  YYSYMBOL_assign_expr = 128,              /* assign_expr  */
  YYSYMBOL_logical_or_expr = 129,          /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 130,         /* logical_and_expr  */
  YYSYMBOL_bitwise_or_expr = 131,          /* bitwise_or_expr  */
  YYSYMBOL_bitwise_xor_expr = 132,         /* bitwise_xor_expr  */
  YYSYMBOL_bitwise_and_expr = 133,         /* bitwise_and_expr  */
  YYSYMBOL_equality_expr = 134,            /* equality_expr  */
  YYSYMBOL_relational_expr = 135,          /* relational_expr  */
  YYSYMBOL_shift_expr = 136,               /* shift_expr  */
  YYSYMBOL_additive_expr = 137,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 138,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 139,               /* unary_expr  */
  YYSYMBOL_postfix_expr = 140,             /* postfix_expr  */
  YYSYMBOL_primary_expr = 141,             /* primary_expr  */
  YYSYMBOL_142_20 = 142,                   /* $@20  */
  YYSYMBOL_literal = 143                   /* literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   559

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   111,   112,   116,   117,   118,   119,   124,
     125,   126,   127,   128,   129,   134,   136,   135,   138,   139,
     143,   144,   148,   153,   162,   166,   161,   177,   178,   182,
     183,   184,   185,   189,   194,   199,   206,   217,   224,   238,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     257,   258,   262,   263,   267,   268,   272,   272,   276,   284,
     292,   296,   305,   311,   310,   325,   329,   324,   342,   346,
     341,   359,   361,   365,   369,   358,   377,   384,   385,   386,
     391,   390,   394,   393,   399,   400,   404,   405,   411,   410,
     423,   424,   429,   428,   437,   436,   444,   443,   456,   465,
     474,   480,   495,   496,   500,   501,   502,   506,   510,   511,
     516,   521,   526,   531,   536,   541,   546,   551,   556,   561,
     569,   573,   577,   581,   585,   589,   593,   597,   601,   605,
     609,   613,   617,   621,   625,   629,   633,   637,   641,   645,
     649,   653,   657,   661,   665,   669,   673,   677,   681,   682,
     687,   692,   696,   700,   707,   708,   713,   721,   727,   726,
     733,   734,   735,   743,   747,   751,   755,   759
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "CHAR",
  "BOOL", "VOID", "STRING", "CONST", "IF", "ELSE", "WHILE", "DO", "FOR",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "INC", "DEC",
  "PLUSASSIGN", "MINUSASSIGN", "STARASSIGN", "DIVASSIGN", "MODASSIGN",
  "EQ", "NEQ", "LEQ", "GEQ", "AND", "OR", "ASSIGN", "PLUS", "MINUS",
  "STAR", "DIV", "MOD", "NOT", "LT", "GT", "LPARENTHESIS", "RPARENTHESIS",
  "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "SEMICOLON",
  "COLON", "IDENTIFIER", "STRING_LITERAL", "INT_LITERAL", "BOOL_LITERAL",
  "FLOAT_LITERAL", "CHAR_LITERAL", "BITWISEXOR", "BITWISEAND", "BITWISEOR",
  "RSHIFT", "LSHIFT", "BITWISENOT", "LSHIFTASSIGN", "RSHIFTASSIGN",
  "XORASSIGN", "ANDASSIGN", "ORASSIGN", "LOWER_THAN_ELSE", "UMINUS",
  "$accept", "program", "decl_list", "decl", "type_spec", "var_decl",
  "$@1", "declarator_list", "declarator", "func_decl", "$@2", "$@3",
  "param_list_opt", "param_list", "param_decl", "stmt", "stmt_guard",
  "stmt_core", "stmt_list", "block_item", "expr_stmt", "compound_stmt",
  "$@4", "compound_stmt_func", "if_condition_prefix", "if_stmt", "@5",
  "while_stmt", "@6", "$@7", "do_while_stmt", "@8", "$@9", "for_stmt",
  "$@10", "@11", "$@12", "$@13", "for_init", "for_var_decl", "$@14",
  "$@15", "for_update", "expr_opt", "switch_stmt", "@16", "case_list",
  "case_item", "$@17", "$@18", "$@19", "break_stmt", "continue_stmt",
  "return_stmt", "arg_list_opt", "arg_list", "expr", "assign_expr",
  "logical_or_expr", "logical_and_expr", "bitwise_or_expr",
  "bitwise_xor_expr", "bitwise_and_expr", "equality_expr",
  "relational_expr", "shift_expr", "additive_expr", "multiplicative_expr",
  "unary_expr", "postfix_expr", "primary_expr", "$@20", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-223)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-104)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -223,    30,    19,  -223,   -46,  -223,  -223,  -223,  -223,  -223,
    -223,   525,  -223,     8,  -223,  -223,  -223,    77,  -223,  -223,
      -5,     1,     4,  -223,    18,    27,  -223,  -223,    34,    43,
      38,    54,   436,    -9,    -1,   460,   460,   280,   230,  -223,
     158,  -223,  -223,  -223,  -223,  -223,   460,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,    60,
    -223,    78,    82,    63,    66,    67,   -12,   111,    23,    22,
      42,  -223,  -223,  -223,  -223,    73,  -223,   484,  -223,  -223,
      73,  -223,  -223,   304,    92,  -223,   256,   484,  -223,  -223,
    -223,    88,  -223,  -223,    -7,  -223,  -223,    99,   100,   101,
    -223,  -223,  -223,   484,   484,   484,   484,   484,   484,  -223,
     484,   484,   484,   484,   484,  -223,   134,  -223,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   114,    16,  -223,   426,
    -223,   106,   110,   484,   144,   113,   365,   116,  -223,  -223,
    -223,  -223,   434,  -223,  -223,  -223,  -223,  -223,  -223,   115,
    -223,  -223,  -223,  -223,  -223,  -223,    82,    63,    66,    67,
     -12,   111,   111,    23,    23,    23,    23,    22,    22,    42,
      42,  -223,  -223,  -223,  -223,   112,   525,   135,   118,   117,
    -223,  -223,  -223,   119,   122,  -223,   525,  -223,   138,  -223,
    -223,  -223,  -223,     9,  -223,  -223,  -223,   145,   146,   142,
    -223,  -223,   456,   148,   160,  -223,   374,  -223,  -223,  -223,
    -223,    73,  -223,   152,  -223,  -223,   484,  -223,  -223,   164,
     484,   157,  -223,  -223,  -223,   484,    73,   154,   484,  -223,
    -223,   484,  -223,  -223,  -223,  -223,   161,   154,   156,  -223,
      -4,  -223,   441,   163,  -223,   120,   166,  -223,  -223,  -223,
    -223,   484,   167,   168,  -223,   170,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,   346,  -223,   390,   407,  -223
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,     0,     9,    10,    11,    12,    13,
      14,     0,     3,     0,     5,     6,     7,     0,     8,    16,
       0,    22,     0,    21,     0,     0,    65,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
     157,   167,   163,   166,   164,   165,     0,    37,    40,    41,
      39,    42,    43,    44,    45,    46,    48,    49,    47,     0,
     107,   108,   121,   123,   125,   127,   129,   132,   137,   140,
     143,   147,   148,   154,   160,     0,    19,     0,    24,    18,
       0,    15,    38,     0,     0,    39,     0,     0,    98,    99,
     100,     0,   149,   150,   157,   153,   151,     0,     0,     0,
      51,   155,   156,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,     0,   152,    62,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,    23,     0,
      20,     0,     0,     0,     0,     0,    79,     0,   101,   162,
     161,    58,    39,   110,   111,   112,   113,   114,   109,     0,
     115,   116,   117,   118,   119,    63,   120,   122,   124,   126,
     128,   130,   131,   135,   136,   133,   134,   139,   138,   141,
     142,   144,   145,   146,    17,     0,     0,     0,     0,    27,
      30,    61,    60,     0,     0,    39,     0,    80,     0,    77,
      78,    88,    57,     0,    53,    52,    50,     0,     0,   102,
     105,    39,     0,     0,    33,    25,     0,    66,    69,    76,
      82,     0,    72,     0,   106,   159,     0,    64,    31,    34,
       0,     0,    32,    29,    39,     0,     0,    81,    87,    91,
     104,     0,    35,    51,    26,    67,     0,    83,     0,    86,
       0,    36,    39,     0,    73,     0,     0,    89,    90,    59,
      70,    85,     0,     0,    94,     0,    84,    96,    92,    51,
      74,    51,    51,    39,    39,    39,    39,    75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,  -223,  -223,     0,   206,  -223,   -72,   131,  -223,
    -223,  -223,  -223,  -223,  -149,    -2,  -223,  -223,  -222,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,   -31,   445,  -223,    97,
     102,   107,   108,    98,   -30,   -25,   -21,   -13,   -28,  -223,
    -223,  -223,   -27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    12,   203,   204,    75,    22,    23,    15,
     139,   231,   188,   189,   190,   205,    17,    47,   152,   206,
      48,    49,   100,   244,    50,    51,   211,    52,    84,   234,
      53,    85,   235,    54,   146,   238,   261,   274,   198,   199,
     221,   236,   265,   248,    55,   223,   250,   258,   272,   269,
     271,    56,    57,    58,   208,   209,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,   159,    74
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    91,    13,   137,    18,    79,    98,    95,    96,    20,
      20,    19,   255,   256,   101,   102,   123,   124,   115,    -2,
       4,   252,     5,     6,     7,     8,     9,    10,    11,   -39,
       3,   -39,   -39,   -39,   -39,    77,   109,   -39,   -39,   -39,
     -39,   -39,   257,    92,    78,    76,   138,   273,   116,   275,
     276,    93,   142,    80,    81,   -39,   147,   131,   132,   -39,
      21,   136,   -39,   228,   -39,    80,   184,   233,    82,   -39,
      83,   -39,   -39,   -39,   -39,   -39,   -39,    86,    24,   133,
     134,   135,   -39,   144,   129,   130,    87,    25,    88,    26,
      27,    28,    29,   171,   172,    30,    31,    32,    33,    34,
     173,   174,   175,   176,    89,   181,   182,   183,   177,   178,
     117,   118,   193,    35,   119,   200,   207,    36,   179,   180,
      37,   262,    38,   120,   121,   136,   122,    39,   210,    40,
      41,    42,    43,    44,    45,   143,    33,    34,   148,   187,
      46,   125,   126,   149,   150,   165,   197,   151,    77,   237,
     191,    35,   127,   128,   192,    36,   194,   195,    37,  -103,
     201,   212,   215,   217,   247,   218,   216,    40,    41,    42,
      43,    44,    45,    41,    42,    43,    44,    45,    46,   101,
     102,   103,   104,   105,   106,   107,   213,   214,   222,   224,
     225,   226,   108,   219,   230,   240,   220,   239,   241,   242,
     229,   109,   243,    80,   246,   253,   254,   249,    14,   227,
     251,   140,   187,   260,   270,   166,   187,   264,   267,   268,
     170,   167,   110,   111,   112,   113,   114,   168,   263,   169,
     266,    99,   245,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,     0,   -56,   -56,   -56,   -56,     0,     0,   -56,   -56,
     -56,   -56,   -56,     0,     0,     0,     0,   145,     0,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -56,     0,     0,     0,
     -56,     0,   277,   -56,     0,   -56,   -56,   -71,   -71,     0,
     -56,    97,   -56,   -56,   -56,   -56,   -56,   -56,     0,     0,
       0,     0,   -71,   -56,     0,     0,   -71,     0,     0,   -71,
       0,    33,    34,     0,     0,   141,   -71,     0,   -71,   -71,
     -71,   -71,   -71,   -71,     0,     0,    35,     0,     0,   -71,
      36,     0,     0,    37,     0,    33,    34,     0,     0,     0,
       0,     0,    40,    41,    42,    43,    44,    45,     0,     0,
      35,     0,     0,    46,    36,     0,     0,    37,     0,     5,
       6,     7,     8,     9,    10,    11,    40,    41,    42,    43,
      44,    45,   -95,   -95,     0,     0,     0,    46,     5,     6,
       7,     8,     9,    10,   196,   232,     0,     5,     6,     7,
       8,     9,    10,   186,     0,     0,    33,    34,     0,     0,
       0,     0,   -95,     5,     6,     7,     8,     9,    10,    11,
       0,    35,     0,     0,     0,    36,   -97,   -97,    37,     0,
       5,     6,     7,     8,     9,    10,    11,    40,    41,    42,
      43,    44,    45,   -93,   -93,     0,     0,   185,    46,     5,
       6,     7,     8,     9,    10,   186,   -97,     5,     6,     7,
       8,     9,    10,    11,     5,     6,     7,     8,     9,    10,
      11,     0,     0,   -93,     0,     0,     0,    33,    34,     5,
       6,     7,     8,     9,    10,   186,     0,     0,     0,     0,
     -28,     0,    35,     0,     0,     0,    36,     0,     0,    37,
     202,    33,    34,     0,     0,     0,    90,   259,    40,    41,
      42,    43,    44,    45,     0,     0,    35,     0,     0,    46,
      36,     0,     0,    37,     0,    33,    34,     0,     0,     0,
       0,     0,    94,    41,    42,    43,    44,    45,     0,     0,
      35,     0,     0,    46,    36,     0,     0,    37,     5,     6,
       7,     8,     9,    10,     0,     0,    40,    41,    42,    43,
      44,    45,     0,     0,     0,     0,     0,    46,   153,   154,
     155,   156,   157,   158,     0,   160,   161,   162,   163,   164
};

static const yytype_int16 yycheck[] =
{
       2,    32,     2,    75,    50,     1,    37,    35,    36,     1,
       1,    11,    16,    17,    21,    22,    28,    29,    46,     0,
       1,   243,     3,     4,     5,     6,     7,     8,     9,    10,
       0,    12,    13,    14,    15,    34,    43,    18,    19,    20,
      21,    22,    46,    52,    43,    50,    77,   269,    50,   271,
     272,    52,    83,    49,    50,    36,    87,    35,    36,    40,
      52,    52,    43,   212,    45,    49,    50,   216,    50,    50,
      43,    52,    53,    54,    55,    56,    57,    43,     1,    37,
      38,    39,    63,    85,    61,    62,    43,    10,    50,    12,
      13,    14,    15,   123,   124,    18,    19,    20,    21,    22,
     125,   126,   127,   128,    50,   133,   134,   135,   129,   130,
      50,    33,   143,    36,    32,   146,     1,    40,   131,   132,
      43,     1,    45,    60,    58,    52,    59,    50,   159,    52,
      53,    54,    55,    56,    57,    43,    21,    22,    50,   139,
      63,    30,    31,    44,    44,    11,   146,    46,    34,   221,
      44,    36,    41,    42,    44,    40,    12,    44,    43,    44,
      44,    49,    44,    44,   236,    43,    49,    52,    53,    54,
      55,    56,    57,    53,    54,    55,    56,    57,    63,    21,
      22,    23,    24,    25,    26,    27,   186,    52,    50,    44,
      44,    49,    34,   195,    34,   226,   196,    45,    34,   230,
      52,    43,    45,    49,   235,    44,    50,   238,     2,   211,
     241,    80,   212,    50,    44,   118,   216,    51,    51,    51,
     122,   119,    64,    65,    66,    67,    68,   120,   255,   121,
     261,     1,   234,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    -1,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    36,    -1,    -1,    -1,
      40,    -1,   274,    43,    -1,    45,    46,    21,    22,    -1,
      50,     1,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    36,    63,    -1,    -1,    40,    -1,    -1,    43,
      -1,    21,    22,    -1,    -1,     1,    50,    -1,    52,    53,
      54,    55,    56,    57,    -1,    -1,    36,    -1,    -1,    63,
      40,    -1,    -1,    43,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    -1,    -1,
      36,    -1,    -1,    63,    40,    -1,    -1,    43,    -1,     3,
       4,     5,     6,     7,     8,     9,    52,    53,    54,    55,
      56,    57,    16,    17,    -1,    -1,    -1,    63,     3,     4,
       5,     6,     7,     8,     9,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    21,    22,    -1,    -1,
      -1,    -1,    46,     3,     4,     5,     6,     7,     8,     9,
      -1,    36,    -1,    -1,    -1,    40,    16,    17,    43,    -1,
       3,     4,     5,     6,     7,     8,     9,    52,    53,    54,
      55,    56,    57,    16,    17,    -1,    -1,     1,    63,     3,
       4,     5,     6,     7,     8,     9,    46,     3,     4,     5,
       6,     7,     8,     9,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    46,    -1,    -1,    -1,    21,    22,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      44,    -1,    36,    -1,    -1,    -1,    40,    -1,    -1,    43,
      46,    21,    22,    -1,    -1,    -1,    50,    46,    52,    53,
      54,    55,    56,    57,    -1,    -1,    36,    -1,    -1,    63,
      40,    -1,    -1,    43,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    -1,    -1,
      36,    -1,    -1,    63,    40,    -1,    -1,    43,     3,     4,
       5,     6,     7,     8,    -1,    -1,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    63,   103,   104,
     105,   106,   107,   108,    -1,   110,   111,   112,   113,   114
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    74,    75,    76,    80,    86,    87,    50,    75,
       1,    52,    78,    79,     1,    10,    12,    13,    14,    15,
      18,    19,    20,    21,    22,    36,    40,    43,    45,    50,
      52,    53,    54,    55,    56,    57,    63,    88,    91,    92,
      95,    96,    98,   101,   104,   115,   122,   123,   124,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   143,    77,    50,    34,    43,     1,
      49,    50,    50,    43,    99,   102,    43,    43,    50,    50,
      50,   127,    52,    52,    52,   139,   139,     1,   127,     1,
      93,    21,    22,    23,    24,    25,    26,    27,    34,    43,
      64,    65,    66,    67,    68,   139,    86,    50,    33,    32,
      60,    58,    59,    28,    29,    30,    31,    41,    42,    61,
      62,    35,    36,    37,    38,    39,    52,    78,   127,    81,
      79,     1,   127,    43,    86,     1,   105,   127,    50,    44,
      44,    46,    89,   128,   128,   128,   128,   128,   128,   142,
     128,   128,   128,   128,   128,    11,   130,   131,   132,   133,
     134,   135,   135,   136,   136,   136,   136,   137,   137,   138,
     138,   139,   139,   139,    50,     1,     9,    75,    83,    84,
      85,    44,    44,   127,    12,    44,     9,    75,   109,   110,
     127,    44,    46,    75,    76,    86,    90,     1,   125,   126,
     127,    97,    49,    75,    52,    44,    49,    44,    43,    86,
      75,   111,    50,   116,    44,    44,    49,    86,    85,    52,
      34,    82,     1,    85,   100,   103,   112,    78,   106,    45,
     127,    34,   127,    45,    94,    86,   127,    78,   114,   127,
     117,   127,    89,    44,    50,    16,    17,    46,   118,    46,
      50,   107,     1,   143,    51,   113,   127,    51,    51,   120,
      44,   121,   119,    89,   108,    89,    89,    86
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    73,    74,    74,    74,    74,    75,
      75,    75,    75,    75,    75,    76,    77,    76,    76,    76,
      78,    78,    79,    79,    81,    82,    80,    83,    83,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    86,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      89,    89,    90,    90,    91,    91,    93,    92,    92,    94,
      95,    95,    96,    97,    96,    99,   100,    98,   102,   103,
     101,   105,   106,   107,   108,   104,   104,   109,   109,   109,
     111,   110,   112,   110,   113,   113,   114,   114,   116,   115,
     117,   117,   119,   118,   120,   118,   121,   118,   122,   123,
     124,   124,   125,   125,   126,   126,   126,   127,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
     134,   134,   134,   135,   135,   135,   135,   135,   136,   136,
     136,   137,   137,   137,   138,   138,   138,   138,   139,   139,
     139,   139,   139,   139,   140,   140,   140,   141,   142,   141,
     141,   141,   141,   143,   143,   143,   143,   143
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     5,     3,     3,
       3,     1,     1,     3,     0,     0,     8,     1,     0,     3,
       1,     3,     3,     2,     3,     4,     5,     2,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     1,     1,     2,     1,     0,     4,     3,     3,
       4,     4,     2,     0,     5,     0,     0,     7,     0,     0,
       9,     0,     0,     0,     0,    13,     5,     1,     1,     0,
       0,     3,     0,     4,     1,     0,     1,     0,     0,     8,
       2,     0,     0,     5,     0,     4,     0,     5,     2,     2,
       2,     3,     1,     0,     3,     1,     2,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     2,
       2,     2,     2,     2,     1,     2,     2,     1,     0,     5,
       1,     3,     3,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* decl: error SEMICOLON  */
#line 119 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                     { yyerrok; }
#line 1784 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 9: /* type_spec: INT  */
#line 124 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.typeval) = Type::INT; CTX->currDeclType = (yyval.typeval); CTX->currDeclConst = false; }
#line 1790 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 10: /* type_spec: FLOAT  */
#line 125 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.typeval) = Type::FLOAT; CTX->currDeclType = (yyval.typeval); CTX->currDeclConst = false; }
#line 1796 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 11: /* type_spec: CHAR  */
#line 126 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.typeval) = Type::CHAR; CTX->currDeclType = (yyval.typeval); CTX->currDeclConst = false; }
#line 1802 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 12: /* type_spec: BOOL  */
#line 127 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.typeval) = Type::BOOL; CTX->currDeclType = (yyval.typeval); CTX->currDeclConst = false; }
#line 1808 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 13: /* type_spec: VOID  */
#line 128 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.typeval) = Type::VOID; CTX->currDeclType = (yyval.typeval); CTX->currDeclConst = false; }
#line 1814 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 14: /* type_spec: STRING  */
#line 129 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.typeval) = Type::STRING; CTX->currDeclType = (yyval.typeval); CTX->currDeclConst = false; }
#line 1820 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 16: /* $@1: %empty  */
#line 136 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      { CTX->currDeclType = (yyvsp[0].typeval); CTX->currDeclConst = true; }
#line 1826 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 18: /* var_decl: type_spec declarator_list error  */
#line 138 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                                                    { yyerrok; }
#line 1832 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 19: /* var_decl: type_spec error SEMICOLON  */
#line 139 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                                                    { yyerrok; }
#line 1838 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 22: /* declarator: IDENTIFIER  */
#line 149 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      handleSimpleDeclarator(CTX, (yyvsp[0].sval), yylineno);
          free((yyvsp[0].sval));
      }
#line 1847 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 23: /* declarator: IDENTIFIER ASSIGN expr  */
#line 154 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      handleInitializedDeclarator(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), yylineno);
          free((yyvsp[-2].sval));
      }
#line 1856 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 24: /* $@2: %empty  */
#line 162 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      resetFunctionParamContext(CTX);
      }
#line 1864 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 25: /* $@3: %empty  */
#line 166 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      beginFunctionDefinition(CTX, (yyvsp[-4].sval), (yyvsp[-5].typeval), yylineno);
      }
#line 1872 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 26: /* func_decl: type_spec IDENTIFIER LPARENTHESIS $@2 param_list_opt RPARENTHESIS $@3 compound_stmt_func  */
#line 170 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      endFunctionDefinition(CTX, (yyvsp[-6].sval));
          free((yyvsp[-6].sval));
      }
#line 1881 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 31: /* param_list: error COMMA param_decl  */
#line 184 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                             { yyerrok; }
#line 1887 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 32: /* param_list: param_list COMMA error  */
#line 185 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                             { yyerrok; }
#line 1893 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 33: /* param_decl: type_spec IDENTIFIER  */
#line 190 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          addFunctionParam(CTX, (yyvsp[-1].typeval), (yyvsp[0].sval), "", false, yylineno);
          free((yyvsp[0].sval));
      }
#line 1902 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 34: /* param_decl: CONST type_spec IDENTIFIER  */
#line 195 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          addFunctionParam(CTX, (yyvsp[-1].typeval), (yyvsp[0].sval), "", true, yylineno);
          free((yyvsp[0].sval));
      }
#line 1911 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 35: /* param_decl: type_spec IDENTIFIER ASSIGN expr  */
#line 200 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          bool defaultOk = SA->validateAssignment(*(yyvsp[0].exprval), (yyvsp[-3].typeval), yylineno);
          addFunctionParam(CTX, (yyvsp[-3].typeval), (yyvsp[-2].sval), defaultOk ? (yyvsp[0].exprval)->place : "", false, yylineno);
          free((yyvsp[0].exprval));
          free((yyvsp[-2].sval));
      }
#line 1922 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 36: /* param_decl: CONST type_spec IDENTIFIER ASSIGN expr  */
#line 207 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          bool defaultOk = SA->validateAssignment(*(yyvsp[0].exprval), (yyvsp[-3].typeval), yylineno);
          addFunctionParam(CTX, (yyvsp[-3].typeval), (yyvsp[-2].sval), defaultOk ? (yyvsp[0].exprval)->place : "", true, yylineno);
          free((yyvsp[0].exprval));
          free((yyvsp[-2].sval));
      }
#line 1933 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 37: /* stmt: stmt_guard stmt_core  */
#line 218 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
    {
      if ((yyvsp[-1].ival) >= 0)
      {
          QG->rollbackTo((yyvsp[-1].ival));
      }
    }
#line 1944 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 38: /* stmt: stmt_guard error SEMICOLON  */
#line 225 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
    {
      if ((yyvsp[-2].ival) >= 0)
      {
          QG->rollbackTo((yyvsp[-2].ival));
      }
      yyerrok;
      yyclearin;
    }
#line 1957 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 39: /* stmt_guard: %empty  */
#line 238 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
    {
      (yyval.ival) = validateStatementPlacement(CTX, yylineno) ? QG->nextQuad() : -1;
    }
#line 1965 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 56: /* $@4: %empty  */
#line 272 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
             { ST->addScope(); }
#line 1971 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 57: /* compound_stmt: LBRACE $@4 stmt_list RBRACE  */
#line 273 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      leaveScopeWithUnusedWarnings(CTX);
      }
#line 1979 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 58: /* compound_stmt: LBRACE error RBRACE  */
#line 277 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          yyerrok;
      }
#line 1987 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 59: /* compound_stmt_func: LBRACE stmt_list RBRACE  */
#line 285 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      leaveScopeWithUnusedWarnings(CTX);
      }
#line 1995 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 60: /* if_condition_prefix: IF LPARENTHESIS expr RPARENTHESIS  */
#line 293 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.sval) = beginIfCondition(CTX, (yyvsp[-1].exprval),yylineno);
      }
#line 2003 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 61: /* if_condition_prefix: IF LPARENTHESIS error RPARENTHESIS  */
#line 297 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.sval) = beginIfCondition(CTX, new ExprAttr(Type::BOOL, "true"), yylineno);
          yyerrok;
      }
#line 2012 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 62: /* if_stmt: if_condition_prefix stmt  */
#line 306 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          endIfWithoutElse(CTX, (yyvsp[-1].sval));
          free((yyvsp[-1].sval));
      }
#line 2021 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 63: /* @5: %empty  */
#line 311 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.sval) = beginElseBranch(CTX, (yyvsp[-2].sval));
          free((yyvsp[-2].sval));
      }
#line 2030 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 64: /* if_stmt: if_condition_prefix stmt ELSE @5 stmt  */
#line 316 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          endIfWithElse(CTX, (yyvsp[-1].sval));
          free((yyvsp[-1].sval));
      }
#line 2039 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 65: /* @6: %empty  */
#line 325 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      (yyval.sval) = beginWhileLoop(CTX);
      }
#line 2047 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 66: /* $@7: %empty  */
#line 329 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      emitLoopConditionFalseJump(CTX, (yyvsp[-1].exprval),yylineno);
      }
#line 2055 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 67: /* while_stmt: WHILE @6 LPARENTHESIS expr RPARENTHESIS $@7 stmt  */
#line 333 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      endWhileLoop(CTX, (yyvsp[-5].sval));
          free((yyvsp[-5].sval));
      }
#line 2064 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 68: /* @8: %empty  */
#line 342 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      (yyval.sval) = beginDoWhileLoop(CTX);
      }
#line 2072 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 69: /* $@9: %empty  */
#line 346 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      emitDoWhileConditionLabel(CTX, (yyvsp[-3].sval));
      }
#line 2080 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 70: /* do_while_stmt: DO @8 stmt WHILE LPARENTHESIS $@9 expr RPARENTHESIS SEMICOLON  */
#line 350 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      endDoWhileLoop(CTX, (yyvsp[-7].sval), (yyvsp[-2].exprval),yylineno);
          free((yyvsp[-7].sval));
      }
#line 2089 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 71: /* $@10: %empty  */
#line 359 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      { ST->addScope(); }
#line 2095 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 72: /* @11: %empty  */
#line 361 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      (yyval.sval) = beginForLoop(CTX);
      }
#line 2103 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 73: /* $@12: %empty  */
#line 365 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      emitForConditionAndUpdateLabel(CTX, (yyvsp[-2].sval), (yyvsp[-1].exprval),yylineno);
      }
#line 2111 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 74: /* $@13: %empty  */
#line 369 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      emitForBackEdgeAndBodyLabel(CTX, (yyvsp[-5].sval));
      }
#line 2119 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 75: /* for_stmt: FOR LPARENTHESIS $@10 for_init SEMICOLON @11 expr_opt SEMICOLON $@12 for_update RPARENTHESIS $@13 stmt  */
#line 373 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      endForLoop(CTX, (yyvsp[-7].sval));
          free((yyvsp[-7].sval));
      }
#line 2128 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 76: /* for_stmt: FOR LPARENTHESIS error RPARENTHESIS stmt  */
#line 378 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          yyerrok;
      }
#line 2136 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 80: /* $@14: %empty  */
#line 391 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      { CTX->currDeclType = (yyvsp[0].typeval); CTX->currDeclConst = false; }
#line 2142 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 82: /* $@15: %empty  */
#line 394 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      { CTX->currDeclType = (yyvsp[0].typeval); CTX->currDeclConst = true; }
#line 2148 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 86: /* expr_opt: expr  */
#line 404 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2154 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 87: /* expr_opt: %empty  */
#line 405 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                { (yyval.exprval) = new ExprAttr(Type::BOOL,""); }
#line 2160 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 88: /* @16: %empty  */
#line 411 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.sval) = beginSwitchStatement(CTX, (yyvsp[-1].exprval),yylineno);
      }
#line 2168 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 89: /* switch_stmt: SWITCH LPARENTHESIS expr RPARENTHESIS @16 LBRACE case_list RBRACE  */
#line 415 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          endSwitchStatement(CTX, (yyvsp[-3].sval));
          free((yyvsp[-3].sval));
      }
#line 2177 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 92: /* $@17: %empty  */
#line 429 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          beginCaseClause(CTX, (yyvsp[-1].exprval), yylineno);
      }
#line 2185 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 93: /* case_item: CASE literal COLON $@17 stmt_list  */
#line 433 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          endCaseOrDefaultClause(CTX);
      }
#line 2193 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 94: /* $@18: %empty  */
#line 437 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          beginDefaultClause(CTX, yylineno);
      }
#line 2201 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 95: /* case_item: DEFAULT COLON $@18 stmt_list  */
#line 440 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                {
        endCaseOrDefaultClause(CTX);
      }
#line 2209 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 96: /* $@19: %empty  */
#line 444 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          beginCaseClause(CTX, new ExprAttr(Type::INT, "0"), yylineno);
          yyerrok;
      }
#line 2218 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 97: /* case_item: CASE error COLON $@19 stmt_list  */
#line 449 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          endCaseOrDefaultClause(CTX);
      }
#line 2226 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 98: /* break_stmt: BREAK SEMICOLON  */
#line 457 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          if (SA->validateBreak(yylineno)) {
              QG->emit("JMP", "-", "-", CTX->breakLabels.back());
          }
      }
#line 2236 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 99: /* continue_stmt: CONTINUE SEMICOLON  */
#line 466 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          if (SA->validateContinue(yylineno)) {
              QG->emit("JMP", "-", "-", CTX->continueLabels.back());
          }
      }
#line 2246 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 100: /* return_stmt: RETURN SEMICOLON  */
#line 475 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      if (SA->validateReturn(SA->getCurrentFunctionReturnType(), nullptr, yylineno)) {
        QG->emit("RETURN", "-", "-", "-");
      }
      }
#line 2256 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 101: /* return_stmt: RETURN expr SEMICOLON  */
#line 481 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          ExprAttr val = *(yyvsp[-1].exprval);
      if (SA->validateReturn(SA->getCurrentFunctionReturnType(), &val, yylineno)) {
        QG->emit("RETURN", val.place, "-", "-");
      }
        else if (CTX->currFunction.inFn && SA->getCurrentFunctionReturnType() != Type::VOID) {
          markCurrentFunctionInvalid(CTX);
      }
          free((yyvsp[-1].exprval));
      }
#line 2271 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 104: /* arg_list: arg_list COMMA expr  */
#line 500 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                           { CTX->passedArgs.back().push_back(*(yyvsp[0].exprval)); free((yyvsp[0].exprval)); }
#line 2277 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 105: /* arg_list: expr  */
#line 501 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                           { CTX->passedArgs.back().push_back(*(yyvsp[0].exprval)); free((yyvsp[0].exprval)); }
#line 2283 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 106: /* arg_list: error RPARENTHESIS  */
#line 502 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                           { yyerrok; yyclearin; }
#line 2289 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 107: /* expr: assign_expr  */
#line 506 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                  { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2295 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 108: /* assign_expr: logical_or_expr  */
#line 510 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                      { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2301 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 109: /* assign_expr: IDENTIFIER ASSIGN assign_expr  */
#line 512 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), yylineno);
          free((yyvsp[-2].sval));
      }
#line 2310 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 110: /* assign_expr: IDENTIFIER PLUSASSIGN assign_expr  */
#line 517 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "PLUSASSIGN", "ADD", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2319 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 111: /* assign_expr: IDENTIFIER MINUSASSIGN assign_expr  */
#line 522 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "MINUSASSIGN", "SUB", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2328 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 112: /* assign_expr: IDENTIFIER STARASSIGN assign_expr  */
#line 527 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "STARASSIGN", "MUL", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2337 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 113: /* assign_expr: IDENTIFIER DIVASSIGN assign_expr  */
#line 532 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "DIVASSIGN", "DIV", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2346 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 114: /* assign_expr: IDENTIFIER MODASSIGN assign_expr  */
#line 537 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "MODASSIGN", "MOD", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2355 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 115: /* assign_expr: IDENTIFIER LSHIFTASSIGN assign_expr  */
#line 542 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "LSHIFTASSIGN", "SHL", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2364 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 116: /* assign_expr: IDENTIFIER RSHIFTASSIGN assign_expr  */
#line 547 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "RSHIFTASSIGN", "SHR", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2373 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 117: /* assign_expr: IDENTIFIER XORASSIGN assign_expr  */
#line 552 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "XORASSIGN", "BXOR", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2382 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 118: /* assign_expr: IDENTIFIER ANDASSIGN assign_expr  */
#line 557 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "ANDASSIGN", "BAND", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2391 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 119: /* assign_expr: IDENTIFIER ORASSIGN assign_expr  */
#line 562 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeCompoundAssignExpr(CTX, (yyvsp[-2].sval), (yyvsp[0].exprval), "ORASSIGN", "BOR", yylineno);
          free((yyvsp[-2].sval));
      }
#line 2400 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 120: /* logical_or_expr: logical_or_expr OR logical_and_expr  */
#line 570 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "OR", "OR", yylineno);
      }
#line 2408 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 121: /* logical_or_expr: logical_and_expr  */
#line 573 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                       { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2414 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 122: /* logical_and_expr: logical_and_expr AND bitwise_or_expr  */
#line 578 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "AND", "AND", yylineno);
      }
#line 2422 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 123: /* logical_and_expr: bitwise_or_expr  */
#line 581 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                      { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2428 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 124: /* bitwise_or_expr: bitwise_or_expr BITWISEOR bitwise_xor_expr  */
#line 586 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "BITWISEOR", "BOR", yylineno);
      }
#line 2436 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 125: /* bitwise_or_expr: bitwise_xor_expr  */
#line 589 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                       { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2442 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 126: /* bitwise_xor_expr: bitwise_xor_expr BITWISEXOR bitwise_and_expr  */
#line 594 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "BITWISEXOR", "BXOR", yylineno);
      }
#line 2450 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 127: /* bitwise_xor_expr: bitwise_and_expr  */
#line 597 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                       { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2456 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 128: /* bitwise_and_expr: bitwise_and_expr BITWISEAND equality_expr  */
#line 602 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "BITWISEAND", "BAND", yylineno);
      }
#line 2464 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 129: /* bitwise_and_expr: equality_expr  */
#line 605 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                    { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2470 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 130: /* equality_expr: equality_expr EQ relational_expr  */
#line 610 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "EQ", "EQ", yylineno);
      }
#line 2478 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 131: /* equality_expr: equality_expr NEQ relational_expr  */
#line 614 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "NEQ", "NEQ", yylineno);
      }
#line 2486 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 132: /* equality_expr: relational_expr  */
#line 617 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                      { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2492 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 133: /* relational_expr: relational_expr LT shift_expr  */
#line 622 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "LT", "LT", yylineno);
      }
#line 2500 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 134: /* relational_expr: relational_expr GT shift_expr  */
#line 626 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "GT", "GT", yylineno);
      }
#line 2508 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 135: /* relational_expr: relational_expr LEQ shift_expr  */
#line 630 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "LEQ", "LEQ", yylineno);
      }
#line 2516 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 136: /* relational_expr: relational_expr GEQ shift_expr  */
#line 634 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "GEQ", "GEQ", yylineno);
      }
#line 2524 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 137: /* relational_expr: shift_expr  */
#line 637 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                 { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2530 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 138: /* shift_expr: shift_expr LSHIFT additive_expr  */
#line 642 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "LSHIFT", "SHL", yylineno);
      }
#line 2538 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 139: /* shift_expr: shift_expr RSHIFT additive_expr  */
#line 646 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "RSHIFT", "SHR", yylineno);
      }
#line 2546 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 140: /* shift_expr: additive_expr  */
#line 649 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                    { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2552 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 141: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 654 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "PLUS", "ADD", yylineno);
      }
#line 2560 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 142: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 658 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "MINUS", "SUB", yylineno);
      }
#line 2568 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 143: /* additive_expr: multiplicative_expr  */
#line 661 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                          { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2574 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 144: /* multiplicative_expr: multiplicative_expr STAR unary_expr  */
#line 666 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "STAR", "MUL", yylineno);
      }
#line 2582 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 145: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 670 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "DIV", "DIV", yylineno);
      }
#line 2590 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 146: /* multiplicative_expr: multiplicative_expr MOD unary_expr  */
#line 674 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeBinaryExpr(CTX, (yyvsp[-2].exprval), (yyvsp[0].exprval), "MOD", "MOD", yylineno);
      }
#line 2598 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 147: /* multiplicative_expr: unary_expr  */
#line 677 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                 { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2604 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 148: /* unary_expr: postfix_expr  */
#line 681 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                   { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2610 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 149: /* unary_expr: INC IDENTIFIER  */
#line 683 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeIncDecExpr(CTX, (yyvsp[0].sval), "INC", yylineno,false);
          free((yyvsp[0].sval));
      }
#line 2619 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 150: /* unary_expr: DEC IDENTIFIER  */
#line 688 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeIncDecExpr(CTX, (yyvsp[0].sval), "DEC", yylineno,false);
          free((yyvsp[0].sval));
      }
#line 2628 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 151: /* unary_expr: NOT unary_expr  */
#line 693 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeUnaryExpr(CTX, (yyvsp[0].exprval), "NOT", "NOT", yylineno);
      }
#line 2636 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 152: /* unary_expr: BITWISENOT unary_expr  */
#line 697 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeUnaryExpr(CTX, (yyvsp[0].exprval), "BITWISENOT", "BNOT", yylineno);
      }
#line 2644 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 153: /* unary_expr: MINUS unary_expr  */
#line 701 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeUnaryExpr(CTX, (yyvsp[0].exprval), "UMINUS", "UMINUS", yylineno);
      }
#line 2652 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 154: /* postfix_expr: primary_expr  */
#line 707 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                   { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2658 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 155: /* postfix_expr: IDENTIFIER INC  */
#line 709 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeIncDecExpr(CTX, (yyvsp[-1].sval), "INC", yylineno);
          free((yyvsp[-1].sval));
      }
#line 2667 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 156: /* postfix_expr: IDENTIFIER DEC  */
#line 714 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = makeIncDecExpr(CTX, (yyvsp[-1].sval), "DEC", yylineno);
          free((yyvsp[-1].sval));
      }
#line 2676 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 157: /* primary_expr: IDENTIFIER  */
#line 722 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
      (yyval.exprval) = makeIdentifierExpr(CTX, (yyvsp[0].sval), yylineno);
          free((yyvsp[0].sval));
      }
#line 2685 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 158: /* $@20: %empty  */
#line 727 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      { CTX->passedArgs.push_back(std::vector<ExprAttr>()); }
#line 2691 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 159: /* primary_expr: IDENTIFIER LPARENTHESIS $@20 arg_list_opt RPARENTHESIS  */
#line 729 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
                    (yyval.exprval) = makeFunctionCallExpr(CTX, (yyvsp[-4].sval), yylineno);
          free((yyvsp[-4].sval));
      }
#line 2700 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 160: /* primary_expr: literal  */
#line 733 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
              { (yyval.exprval) = (yyvsp[0].exprval); }
#line 2706 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 161: /* primary_expr: LPARENTHESIS expr RPARENTHESIS  */
#line 734 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
                                     { (yyval.exprval) = (yyvsp[-1].exprval); }
#line 2712 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 162: /* primary_expr: LPARENTHESIS error RPARENTHESIS  */
#line 736 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = new ExprAttr(Type::UNKNOWN, "0");
          yyerrok;
      }
#line 2721 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 163: /* literal: INT_LITERAL  */
#line 744 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = new ExprAttr(Type::INT,std::to_string((yyvsp[0].ival)));
      }
#line 2729 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 164: /* literal: FLOAT_LITERAL  */
#line 748 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = new ExprAttr(Type::FLOAT,std::to_string((yyvsp[0].dval)));
      }
#line 2737 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 165: /* literal: CHAR_LITERAL  */
#line 752 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = new ExprAttr(Type::CHAR,serializeCharLiteral((yyvsp[0].cval)));
      }
#line 2745 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 166: /* literal: BOOL_LITERAL  */
#line 756 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = new ExprAttr(Type::BOOL,(yyvsp[0].ival) ? "true" : "false");
      }
#line 2753 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;

  case 167: /* literal: STRING_LITERAL  */
#line 760 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"
      {
          (yyval.exprval) = new ExprAttr(Type::STRING,std::string((yyvsp[0].sval)));
          free((yyvsp[0].sval));
      }
#line 2762 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"
    break;


#line 2766 "/home/ahmed/Desktop/University/compiler/Project/build/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 766 "/home/ahmed/Desktop/University/compiler/Project/src/parser.y"


void yyerror(const char* s) {
    if (parserContext && parserContext->errHandler) {
        parserContext->errHandler->addSyntaxError(yylineno, s);
    } else {
        std::fprintf(stderr, "Syntax error [line %d]: %s\n", yylineno, s);
    }
}
