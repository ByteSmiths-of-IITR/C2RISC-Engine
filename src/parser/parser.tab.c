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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "utility.h"  

#define LINE std::cerr<<__LINE__<<std::endl;
// #define LINE /**/

#define NewToken(i) ASTNode *node = new ASTNode()

extern char *yytext;
void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;

#define YYDEBUG 1

std::ofstream PARSERlog("PARSER_debug.log", std::ios::trunc);

ASTNode *root;




#line 102 "parser.tab.c"

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
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 4,                   /* CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_SIZEOF = 6,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 7,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 8,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 9,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 10,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 11,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 12,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 13,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 14,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 15,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 16,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 17,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 18,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 19,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 20,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 21,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 22,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 23,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 24,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 25,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 26,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 27,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPE_NAME = 28,                 /* TYPE_NAME  */
  YYSYMBOL_LPAREN = 29,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 30,                    /* RPAREN  */
  YYSYMBOL_LCURLY = 31,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 32,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 33,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 34,                   /* RSQUARE  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_BIT_AND = 37,                   /* BIT_AND  */
  YYSYMBOL_STAR = 38,                      /* STAR  */
  YYSYMBOL_PLUS = 39,                      /* PLUS  */
  YYSYMBOL_MINUS = 40,                     /* MINUS  */
  YYSYMBOL_BIT_NOT = 41,                   /* BIT_NOT  */
  YYSYMBOL_NOT_OP = 42,                    /* NOT_OP  */
  YYSYMBOL_DIVIDE = 43,                    /* DIVIDE  */
  YYSYMBOL_MOD = 44,                       /* MOD  */
  YYSYMBOL_LESSER_OP = 45,                 /* LESSER_OP  */
  YYSYMBOL_GREATER_OP = 46,                /* GREATER_OP  */
  YYSYMBOL_XOR = 47,                       /* XOR  */
  YYSYMBOL_BIT_OR = 48,                    /* BIT_OR  */
  YYSYMBOL_QUESTION = 49,                  /* QUESTION  */
  YYSYMBOL_COLON = 50,                     /* COLON  */
  YYSYMBOL_SEMI_COLON = 51,                /* SEMI_COLON  */
  YYSYMBOL_ASSIGN = 52,                    /* ASSIGN  */
  YYSYMBOL_TYPEDEF = 53,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 54,                    /* EXTERN  */
  YYSYMBOL_STATIC = 55,                    /* STATIC  */
  YYSYMBOL_AUTO = 56,                      /* AUTO  */
  YYSYMBOL_REGISTER = 57,                  /* REGISTER  */
  YYSYMBOL_CHAR = 58,                      /* CHAR  */
  YYSYMBOL_SHORT = 59,                     /* SHORT  */
  YYSYMBOL_INT = 60,                       /* INT  */
  YYSYMBOL_LONG = 61,                      /* LONG  */
  YYSYMBOL_SIGNED = 62,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 63,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 65,                    /* DOUBLE  */
  YYSYMBOL_CONST = 66,                     /* CONST  */
  YYSYMBOL_VOLATILE = 67,                  /* VOLATILE  */
  YYSYMBOL_VOID = 68,                      /* VOID  */
  YYSYMBOL_STRUCT = 69,                    /* STRUCT  */
  YYSYMBOL_UNION = 70,                     /* UNION  */
  YYSYMBOL_ENUM = 71,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 72,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 73,                      /* CASE  */
  YYSYMBOL_DEFAULT = 74,                   /* DEFAULT  */
  YYSYMBOL_IF = 75,                        /* IF  */
  YYSYMBOL_ELSE = 76,                      /* ELSE  */
  YYSYMBOL_SWITCH = 77,                    /* SWITCH  */
  YYSYMBOL_WHILE = 78,                     /* WHILE  */
  YYSYMBOL_DO = 79,                        /* DO  */
  YYSYMBOL_FOR = 80,                       /* FOR  */
  YYSYMBOL_GOTO = 81,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 82,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 83,                     /* BREAK  */
  YYSYMBOL_RETURN = 84,                    /* RETURN  */
  YYSYMBOL_UNTIL = 85,                     /* UNTIL  */
  YYSYMBOL_INVALID_TOKEN = 86,             /* INVALID_TOKEN  */
  YYSYMBOL_UNKOWN_TOKEN = 87,              /* UNKOWN_TOKEN  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_primary_expression = 89,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 90,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 91,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 92,          /* unary_expression  */
  YYSYMBOL_unary_operator = 93,            /* unary_operator  */
  YYSYMBOL_cast_expression = 94,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 95, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 96,       /* additive_expression  */
  YYSYMBOL_shift_expression = 97,          /* shift_expression  */
  YYSYMBOL_relational_expression = 98,     /* relational_expression  */
  YYSYMBOL_equality_expression = 99,       /* equality_expression  */
  YYSYMBOL_and_expression = 100,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 101,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 102,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 103,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 104,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 105,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 106,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 107,      /* assignment_operator  */
  YYSYMBOL_expression = 108,               /* expression  */
  YYSYMBOL_constant_expression = 109,      /* constant_expression  */
  YYSYMBOL_declaration = 110,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 111,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 112,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 113,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 114,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 115,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 116, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 117,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 118,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 119,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 120, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 121,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 122,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 123,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 124,          /* enumerator_list  */
  YYSYMBOL_enumerator = 125,               /* enumerator  */
  YYSYMBOL_type_qualifier = 126,           /* type_qualifier  */
  YYSYMBOL_declarator = 127,               /* declarator  */
  YYSYMBOL_direct_declarator = 128,        /* direct_declarator  */
  YYSYMBOL_pointer = 129,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 130,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 131,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 132,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 133,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 134,          /* identifier_list  */
  YYSYMBOL_type_name = 135,                /* type_name  */
  YYSYMBOL_abstract_declarator = 136,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 137, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 138,              /* initializer  */
  YYSYMBOL_initializer_list = 139,         /* initializer_list  */
  YYSYMBOL_statement = 140,                /* statement  */
  YYSYMBOL_labeled_statement = 141,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 142,       /* compound_statement  */
  YYSYMBOL_declaration_list = 143,         /* declaration_list  */
  YYSYMBOL_statement_list = 144,           /* statement_list  */
  YYSYMBOL_expression_statement = 145,     /* expression_statement  */
  YYSYMBOL_selection_statement = 146,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 147,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 148,           /* jump_statement  */
  YYSYMBOL_translation_unit = 149,         /* translation_unit  */
  YYSYMBOL_external_declaration = 150,     /* external_declaration  */
  YYSYMBOL_function_declaration = 151,     /* function_declaration  */
  YYSYMBOL_function_definition = 152       /* function_definition  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  214
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  357

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   120,   120,   125,   131,   137,   145,   150,   157,   163,
     170,   177,   184,   190,   199,   205,   214,   219,   225,   231,
     237,   243,   253,   258,   263,   268,   273,   278,   286,   291,
     302,   307,   314,   321,   331,   336,   343,   353,   358,   365,
     375,   380,   387,   394,   401,   411,   416,   423,   433,   438,
     448,   453,   463,   468,   478,   483,   493,   498,   508,   513,
     524,   529,   539,   544,   549,   554,   559,   564,   569,   574,
     579,   584,   589,   597,   602,   612,   616,   622,   633,   638,
     644,   649,   655,   660,   669,   675,   684,   689,   699,   704,
     709,   714,   719,   727,   733,   739,   745,   751,   757,   763,
     769,   775,   781,   787,   793,   802,   811,   817,   828,   833,
     841,   847,   857,   868,   874,   879,   885,   893,   899,   909,
     914,   920,   930,   937,   945,   955,   961,   971,   976,   986,
     991,   999,  1005,  1012,  1018,  1023,  1030,  1036,  1042,  1048,
    1057,  1062,  1068,  1074,  1084,  1089,  1098,  1103,  1112,  1118,
    1127,  1134,  1141,  1150,  1156,  1165,  1170,  1179,  1184,  1189,
    1198,  1203,  1208,  1214,  1220,  1227,  1232,  1237,  1243,  1253,
    1258,  1263,  1272,  1277,  1286,  1291,  1296,  1301,  1306,  1311,
    1316,  1325,  1331,  1338,  1347,  1352,  1358,  1364,  1374,  1379,
    1388,  1394,  1403,  1408,  1416,  1423,  1431,  1441,  1448,  1455,
    1462,  1470,  1479,  1491,  1497,  1502,  1507,  1512,  1521,  1528,
    1537,  1542,  1547,  1555,  1576
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "CONSTANT", "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPE_NAME", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
  "LSQUARE", "RSQUARE", "DOT", "COMMA", "BIT_AND", "STAR", "PLUS", "MINUS",
  "BIT_NOT", "NOT_OP", "DIVIDE", "MOD", "LESSER_OP", "GREATER_OP", "XOR",
  "BIT_OR", "QUESTION", "COLON", "SEMI_COLON", "ASSIGN", "TYPEDEF",
  "EXTERN", "STATIC", "AUTO", "REGISTER", "CHAR", "SHORT", "INT", "LONG",
  "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID",
  "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE", "DEFAULT", "IF", "ELSE",
  "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "UNTIL", "INVALID_TOKEN", "UNKOWN_TOKEN", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_declaration", "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-177)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1049,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
      30,  -177,    15,  1049,  1049,  -177,    42,  -177,  1049,   646,
    -177,  -177,  -177,    81,    68,  -177,    19,    37,  -177,    45,
    -177,    55,    43,    17,  -177,  -177,    84,   667,  -177,  -177,
    -177,    68,   -12,   134,  -177,   101,  -177,  -177,    37,    19,
    -177,   270,  -177,  1092,  -177,   872,  1132,    43,   667,   667,
     152,  -177,    18,   667,   169,   360,  -177,    68,  -177,  -177,
    -177,  -177,    93,    35,  -177,  -177,   443,   526,   526,   784,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   360,   118,
     104,   142,   153,   602,   156,   189,   182,   190,   915,   174,
    -177,   287,   595,   360,  -177,    50,   274,   307,     4,   356,
     227,   205,   211,   245,     2,  -177,  -177,    83,  -177,    15,
    -177,  -177,  -177,   353,   436,  -177,  -177,  -177,  -177,  -177,
    1092,  -177,  -177,  -177,  -177,    29,   247,   261,  -177,   145,
    -177,  -177,  -177,   269,   222,  -177,  -177,  -177,   360,    87,
    -177,   255,  -177,  -177,  -177,  -177,   602,   784,  -177,   360,
    -177,  -177,   157,   103,   285,   292,   602,   360,   360,   360,
    -177,   241,   715,   295,  -177,  -177,  -177,    92,   360,   357,
    -177,  -177,  1146,   360,   364,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,   360,  -177,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,  -177,  -177,
    -177,   519,  -177,  -177,  -177,   172,   803,  1186,  -177,    31,
    -177,   224,  -177,   941,  -177,   371,  -177,  -177,  -177,    18,
    -177,   360,  -177,   349,  -177,   986,   271,  -177,   360,   602,
    -177,   159,   166,   170,   351,   942,   942,  -177,  -177,   199,
    -177,  -177,   202,  -177,    86,  -177,  -177,  -177,  -177,  -177,
      50,    50,   274,   274,   307,   307,   307,   307,     4,     4,
     356,   227,   205,   211,   245,    33,  -177,  -177,  -177,   874,
    -177,   358,   366,  -177,   352,   224,  1005,  1200,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,   602,   602,   602,   360,
     360,  1227,   602,  -177,   360,  -177,   360,  -177,  -177,  -177,
    -177,  -177,  -177,   373,  -177,   391,   311,  -177,  -177,   204,
     212,   602,   215,  -177,  -177,  -177,  -177,  -177,   602,   332,
     602,  -177,   602,  -177,  -177,  -177,  -177
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   104,    88,    89,    90,    91,    92,    94,    95,    96,
      97,   100,   101,    98,    99,   129,   130,    93,   108,   109,
       0,   211,     0,    78,    80,   102,     0,   103,    82,     0,
     208,   212,   210,   124,     0,   133,     0,   140,    76,     0,
      84,    86,   132,     0,    79,    81,   107,     0,    83,     1,
     209,     0,   127,     0,   125,     0,   144,   142,   141,     0,
      77,     0,   213,     0,   214,     0,     0,   131,     0,   114,
       0,   110,     0,   116,     0,     0,   122,     0,   134,   145,
     143,    85,    86,     2,     3,     4,     0,     0,     0,     0,
     184,    22,    23,    24,    25,    26,    27,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,    16,    28,     0,    30,    34,    37,    40,    45,    48,
      50,    52,    54,    56,    58,    60,    73,     0,   180,     0,
     190,   174,   175,     0,     0,   176,   177,   178,   179,     2,
       0,   169,    87,   153,   139,   152,     0,   146,   148,     0,
     136,    28,    75,     0,     0,   113,   106,   111,     0,     0,
     117,   119,   115,   123,   128,   126,     0,     0,    20,     0,
      17,    18,     0,   155,     0,     0,     0,     0,     0,     0,
     180,     0,     0,     0,   204,   205,   206,     0,     0,     0,
      12,    13,     0,     0,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    62,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,   186,
     180,     0,   185,   191,   172,     0,     0,     0,   150,   157,
     151,   158,   137,     0,   138,     0,   135,   105,   120,     0,
     112,     0,   181,     0,     5,     0,   157,   156,     0,     0,
     183,     0,     0,     0,     0,     0,     0,   203,   207,     0,
      11,     8,     0,    14,     0,    10,    61,    31,    32,    33,
      35,    36,    38,    39,    43,    44,    41,    42,    46,    47,
      49,    51,    53,    55,    57,     0,    74,   187,   170,     0,
     165,     0,     0,   161,     0,   159,     0,     0,   147,   149,
     154,   118,   121,    21,    29,   182,     0,     0,     0,     0,
       0,     0,     0,     9,     0,     7,     0,   171,   173,   166,
     160,   162,   167,     0,   163,     0,   194,   196,   197,     0,
       0,     0,     0,   198,    15,    59,   168,   164,     0,     0,
       0,   200,     0,   195,   199,   202,   201
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,  -177,  -177,   -61,  -177,   -31,   161,   162,    54,
     158,   184,   207,   220,   226,   228,  -177,   -63,   -62,  -177,
     -53,   -68,     9,     0,  -177,   395,  -177,    32,  -177,  -177,
     387,   -55,   -30,  -177,   208,  -177,   405,   381,    40,   -18,
     -41,   -27,  -177,   -59,  -177,   216,  -177,   293,   -56,  -176,
    -127,  -177,   -92,  -177,   420,  -177,   329,  -174,  -177,  -177,
    -177,  -177,   434,  -177,  -177
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   110,   111,   272,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   206,
     127,   153,   180,   129,    39,    40,    23,    24,    25,    26,
      70,    71,    72,   159,   160,    27,    53,    54,    28,    55,
      42,    43,    58,   301,   147,   148,   149,   174,   302,   241,
     142,   235,   130,   131,   132,   133,   134,   135,   136,   137,
     138,    29,    30,    31,    32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      22,   141,    67,   152,    41,   151,   146,   164,   266,    21,
      57,   181,   152,   234,   151,   157,   215,   216,    35,   225,
      35,    35,    35,    44,    45,   168,   170,   171,    48,    22,
     175,    80,    35,    33,    35,   152,   172,   151,    21,   155,
      75,    82,   233,   162,    36,    46,    36,    36,    36,   217,
     218,   226,   151,    37,   161,   187,    37,    37,   236,   173,
     236,    34,   237,   305,   237,   145,    38,    37,   158,   227,
     128,    52,    65,    47,   252,    37,    66,    56,   141,    69,
     305,    59,   207,   326,   260,   166,    61,    73,   208,   240,
     248,   320,   321,   209,   210,   152,    60,   151,    79,   157,
      69,    69,    69,    15,    16,    69,    62,    63,    73,    73,
      73,    82,    51,    73,   172,    68,   172,   257,   239,   227,
     325,    69,   227,   249,   261,   262,   263,   238,   227,    73,
     273,    78,   255,   177,   228,   269,   237,   173,   250,   233,
     274,    37,   230,   268,   276,    63,   256,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   296,    76,   315,   176,   304,
      77,   178,   328,   295,   152,   244,   151,   277,   278,   279,
       1,   245,   179,   312,   156,   182,    69,   254,   152,   316,
     151,   265,   183,   227,    73,   227,   317,   151,    67,    69,
     318,   163,   227,   188,   298,    77,   227,    73,   299,   239,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,   336,   337,   338,   314,   256,   322,
     343,   161,   323,   184,   349,   227,   145,   141,   324,   335,
     227,   185,   350,   145,   152,   352,   151,   333,   227,   351,
       1,   227,   222,   306,   247,   145,   353,   307,   355,   223,
     356,   224,   344,   345,   221,   151,   339,   340,   342,   284,
     285,   286,   287,    83,    84,    85,    86,   242,    87,    88,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,   189,   190,   191,   243,     1,    89,
     255,    61,    90,   246,   237,   251,   145,    91,    92,    93,
      94,    95,    96,   211,   212,   258,   192,   213,   214,   264,
     193,    97,   194,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   259,    98,    99,   100,   267,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    83,    84,    85,    86,
     270,    87,    88,   139,    84,    85,    86,   275,    87,    88,
     219,   220,   280,   281,   310,   282,   283,   288,   289,   313,
     319,     1,    89,   354,    61,   229,   331,   348,   329,    89,
      91,    92,    93,    94,    95,    96,   330,    91,    92,    93,
      94,    95,    96,   346,    97,   290,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,   347,    98,    99,   100,   291,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    83,
      84,    85,    86,   292,    87,    88,   139,    84,    85,    86,
     293,    87,    88,   294,    81,   154,    74,   311,   165,   309,
     253,    64,   231,    50,     1,    89,     0,    61,   232,     0,
       0,     0,   167,    91,    92,    93,    94,    95,    96,     0,
      91,    92,    93,    94,    95,    96,     0,    97,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     0,    98,
      99,   100,     0,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    83,    84,    85,    86,     0,    87,    88,   139,
      84,    85,    86,     0,    87,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,    89,     0,
      61,   297,     0,     0,     0,   169,    91,    92,    93,    94,
      95,    96,     0,    91,    92,    93,    94,    95,    96,     0,
      97,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     0,    98,    99,   100,     0,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    83,    84,    85,    86,     0,
      87,    88,     0,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,     0,     0,     0,     0,     0,     0,     0,
       1,    89,     0,    61,     0,     0,     0,     0,     0,    91,
      92,    93,    94,    95,    96,     0,    49,   205,     0,     0,
       0,     0,     0,    97,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     1,    98,    99,   100,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,   139,    84,
      85,    86,     0,    87,    88,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     0,
       0,     0,     0,     1,    89,     0,     0,     0,     0,     0,
       0,     0,    91,    92,    93,    94,    95,    96,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,   139,    84,    85,
      86,     0,    87,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     1,    89,     0,     0,     0,     0,     0,     0,
       0,    91,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     1,   236,   300,     0,     0,   237,     0,     0,     0,
       0,    37,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,   143,     0,   139,    84,    85,
      86,     0,    87,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,   144,    89,     0,   140,   327,     0,     0,     0,
       0,    91,    92,    93,    94,    95,    96,     0,   139,    84,
      85,    86,     0,    87,    88,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    89,   139,    84,    85,    86,     0,
      87,    88,    91,    92,    93,    94,    95,    96,     0,     0,
       0,     0,     0,     0,     0,     0,   186,     0,     0,     1,
       0,    89,     0,     0,     0,     0,     0,     0,     0,    91,
      92,    93,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,    97,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,   308,     1,   255,   300,     0,     0,   237,
       0,     0,     0,     0,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,   332,     0,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   139,    84,    85,    86,     0,
      87,    88,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    89,     0,   140,     0,     0,     0,     0,     0,    91,
      92,    93,    94,    95,    96,   139,    84,    85,    86,     0,
      87,    88,     0,     0,     0,     0,     0,     0,     0,   139,
      84,    85,    86,     0,    87,    88,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     0,   150,     0,     0,    91,
      92,    93,    94,    95,    96,    89,   271,     0,     0,     0,
       0,     0,     0,    91,    92,    93,    94,    95,    96,   139,
      84,    85,    86,     0,    87,    88,     0,     0,     0,     0,
       0,     0,     0,   139,    84,    85,    86,     0,    87,    88,
       0,     0,     0,     0,     0,    89,     0,     0,     0,     0,
     303,     0,     0,    91,    92,    93,    94,    95,    96,    89,
     139,    84,    85,    86,   334,    87,    88,    91,    92,    93,
      94,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,   341,     0,     0,
       0,     0,     0,     0,    91,    92,    93,    94,    95,    96
};

static const yytype_int16 yycheck[] =
{
       0,    63,    43,    66,    22,    66,    65,    75,   182,     0,
      37,   103,    75,   140,    75,    70,    12,    13,     3,    17,
       3,     3,     3,    23,    24,    86,    87,    88,    28,    29,
      98,    58,     3,     3,     3,    98,    89,    98,    29,    69,
      52,    59,   134,    73,    29,     3,    29,    29,    29,    45,
      46,    49,   113,    38,    72,   108,    38,    38,    29,    89,
      29,    31,    33,   239,    33,    65,    51,    38,    50,    36,
      61,     3,    29,    31,   166,    38,    33,    37,   140,    47,
     256,    36,   113,    50,   176,    50,    31,    47,    38,   145,
     158,   265,   266,    43,    44,   158,    51,   158,    58,   154,
      68,    69,    70,    66,    67,    73,    51,    52,    68,    69,
      70,   129,    31,    73,   167,    31,   169,   173,   145,    36,
      34,    89,    36,    36,   177,   178,   179,   145,    36,    89,
     192,    30,    29,    29,    51,   188,    33,   167,    51,   231,
     193,    38,   133,    51,   206,    52,   173,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   227,    32,   259,    50,   237,
      36,    29,   299,   226,   237,    30,   237,   208,   209,   210,
      28,    36,    29,   251,    32,    29,   154,    30,   251,    30,
     251,   182,     3,    36,   154,    36,    30,   258,   239,   167,
      30,    32,    36,    29,    32,    36,    36,   167,    36,   236,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,   316,   317,   318,   258,   255,    30,
     322,   249,    30,    51,    30,    36,   236,   299,    36,   307,
      36,    51,    30,   243,   307,    30,   307,   306,    36,   341,
      28,    36,    47,    29,    32,   255,   348,    33,   350,    48,
     352,    16,   324,   326,    37,   326,   319,   320,   321,   215,
     216,   217,   218,     3,     4,     5,     6,    30,     8,     9,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,     7,     8,     9,    36,    28,    29,
      29,    31,    32,    34,    33,    50,   306,    37,    38,    39,
      40,    41,    42,    39,    40,    30,    29,    10,    11,    78,
      33,    51,    35,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    50,    73,    74,    75,    51,    77,    78,    79,
      80,    81,    82,    83,    84,    85,     3,     4,     5,     6,
       3,     8,     9,     3,     4,     5,     6,     3,     8,     9,
      14,    15,   211,   212,     3,   213,   214,   219,   220,    30,
      29,    28,    29,    51,    31,    32,    34,    76,    30,    29,
      37,    38,    39,    40,    41,    42,    30,    37,    38,    39,
      40,    41,    42,    30,    51,   221,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    34,    73,    74,    75,   222,
      77,    78,    79,    80,    81,    82,    83,    84,    85,     3,
       4,     5,     6,   223,     8,     9,     3,     4,     5,     6,
     224,     8,     9,   225,    59,    68,    51,   249,    77,   243,
     167,    41,   133,    29,    28,    29,    -1,    31,    32,    -1,
      -1,    -1,    29,    37,    38,    39,    40,    41,    42,    -1,
      37,    38,    39,    40,    41,    42,    -1,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    -1,    73,
      74,    75,    -1,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     3,     4,     5,     6,    -1,     8,     9,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,
      31,    32,    -1,    -1,    -1,    29,    37,    38,    39,    40,
      41,    42,    -1,    37,    38,    39,    40,    41,    42,    -1,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    -1,    73,    74,    75,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     3,     4,     5,     6,    -1,
       8,     9,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    -1,     0,    52,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    28,    73,    74,    75,    -1,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     3,     4,
       5,     6,    -1,     8,     9,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    38,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     3,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    29,    -1,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    -1,     3,     4,
       5,     6,    -1,     8,     9,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    29,     3,     4,     5,     6,    -1,
       8,     9,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    28,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,
      38,    39,    40,    41,    42,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    37,    38,    39,    40,    41,    42,    29,
       3,     4,     5,     6,    34,     8,     9,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,   110,   111,   114,   115,   116,   117,   123,   126,   149,
     150,   151,   152,     3,    31,     3,    29,    38,    51,   112,
     113,   127,   128,   129,   111,   111,     3,    31,   111,     0,
     150,    31,     3,   124,   125,   127,   126,   129,   130,    36,
      51,    31,    51,    52,   142,    29,    33,   128,    31,   115,
     118,   119,   120,   126,   124,    52,    32,    36,    30,   126,
     129,   113,   127,     3,     4,     5,     6,     8,     9,    29,
      32,    37,    38,    39,    40,    41,    42,    51,    73,    74,
      75,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      89,    90,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   108,   110,   111,
     140,   141,   142,   143,   144,   145,   146,   147,   148,     3,
      31,   106,   138,     3,    30,   111,   131,   132,   133,   134,
      34,    92,   105,   109,   118,   120,    32,   119,    50,   121,
     122,   127,   120,    32,   109,   125,    50,    29,    92,    29,
      92,    92,   108,   120,   135,   109,    50,    29,    29,    29,
     110,   140,    29,     3,    51,    51,    51,   108,    29,     7,
       8,     9,    29,    33,    35,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    52,   107,    94,    38,    43,
      44,    39,    40,    10,    11,    12,    13,    45,    46,    14,
      15,    37,    47,    48,    16,    17,    49,    36,    51,    32,
     110,   144,    32,   140,   138,   139,    29,    33,   127,   129,
     136,   137,    30,    36,    30,    36,    34,    32,   109,    36,
      51,    50,   140,   135,    30,    29,   129,   136,    30,    50,
     140,   108,   108,   108,    78,   110,   145,    51,    51,   108,
       3,    30,    91,   106,   108,     3,   106,    94,    94,    94,
      95,    95,    96,    96,    97,    97,    97,    97,    98,    98,
      99,   100,   101,   102,   103,   108,   106,    32,    32,    36,
      30,   131,   136,    34,   109,   137,    29,    33,    72,   133,
       3,   122,   109,    30,    94,   140,    30,    30,    30,    29,
     145,   145,    30,    30,    36,    34,    50,    32,   138,    30,
      30,    34,    30,   131,    34,   109,   140,   140,   140,   108,
     108,    30,   108,   140,   106,   105,    30,    34,    76,    30,
      30,   140,    30,   140,    51,   140,   140
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    89,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    90,    91,    91,    92,    92,    92,    92,
      92,    92,    93,    93,    93,    93,    93,    93,    94,    94,
      95,    95,    95,    95,    96,    96,    96,    97,    97,    97,
      98,    98,    98,    98,    98,    99,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   109,   110,   110,   111,   111,
     111,   111,   111,   111,   112,   112,   113,   113,   114,   114,
     114,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   116,   116,   116,   117,   117,
     118,   118,   119,   120,   120,   120,   120,   121,   121,   122,
     122,   122,   123,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     129,   129,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   133,   133,   134,   134,   135,   135,   136,   136,   136,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   138,
     138,   138,   139,   139,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   141,   142,   142,   142,   142,   143,   143,
     144,   144,   145,   145,   146,   146,   146,   147,   147,   147,
     147,   147,   147,   148,   148,   148,   148,   148,   149,   149,
     150,   150,   150,   151,   152
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     2,     3,     1,     2,
       1,     2,     1,     2,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     4,     2,     1,     1,
       1,     2,     3,     2,     1,     2,     1,     1,     3,     1,
       2,     3,     4,     5,     2,     1,     3,     1,     3,     1,
       1,     2,     1,     1,     3,     4,     3,     4,     4,     3,
       1,     2,     2,     3,     1,     2,     1,     3,     1,     3,
       2,     2,     1,     1,     3,     1,     2,     1,     1,     2,
       3,     2,     3,     3,     4,     2,     3,     3,     4,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     2,     3,     3,     4,     1,     2,
       1,     2,     1,     2,     5,     7,     5,     5,     5,     7,
       6,     7,     7,     3,     2,     2,     2,     3,     1,     2,
       1,     1,     1,     3,     3
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
  case 2: /* primary_expression: IDENTIFIER  */
#line 121 "parser.y"
        {   LINE
            NewToken(1, "Identifier");
            (yyval.astNode) = node;
        }
#line 1705 "parser.tab.c"
    break;

  case 3: /* primary_expression: CONSTANT  */
#line 126 "parser.y"
        { 
            LINE
            NewToken(1, "Constant");
            (yyval.astNode) = node;
        }
#line 1715 "parser.tab.c"
    break;

  case 4: /* primary_expression: STRING_LITERAL  */
#line 132 "parser.y"
        { 
            LINE
            NewToken(1, "StringLiteral");
            (yyval.astNode) = node;
        }
#line 1725 "parser.tab.c"
    break;

  case 5: /* primary_expression: LPAREN expression RPAREN  */
#line 138 "parser.y"
        {   // Prarenthesis are not part of the AST
            LINE
            (yyval.astNode) = (yyvsp[-1].astNode);
        }
#line 1734 "parser.tab.c"
    break;

  case 6: /* postfix_expression: primary_expression  */
#line 146 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 1743 "parser.tab.c"
    break;

  case 7: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 151 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("ArraySubscript");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 1754 "parser.tab.c"
    break;

  case 8: /* postfix_expression: postfix_expression LPAREN RPAREN  */
#line 158 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("FunctionCall");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
      }
#line 1764 "parser.tab.c"
    break;

  case 9: /* postfix_expression: postfix_expression LPAREN argument_expression_list RPAREN  */
#line 164 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("FunctionCall");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 1775 "parser.tab.c"
    break;

  case 10: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 171 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("MemberAccess");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, "Identifier", (yyvsp[0].tokenAtr)->value));
      }
#line 1786 "parser.tab.c"
    break;

  case 11: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 178 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("PointerMemberAccess");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, "Identifier", (yyvsp[0].tokenAtr)->value));
      }
#line 1797 "parser.tab.c"
    break;

  case 12: /* postfix_expression: postfix_expression INC_OP  */
#line 185 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("PostIncrement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 1807 "parser.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression DEC_OP  */
#line 191 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("PostDecrement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 1817 "parser.tab.c"
    break;

  case 14: /* argument_expression_list: assignment_expression  */
#line 200 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("ArgumentList");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1827 "parser.tab.c"
    break;

  case 15: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 206 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1837 "parser.tab.c"
    break;

  case 16: /* unary_expression: postfix_expression  */
#line 215 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 1846 "parser.tab.c"
    break;

  case 17: /* unary_expression: INC_OP unary_expression  */
#line 220 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("PreIncrement");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1856 "parser.tab.c"
    break;

  case 18: /* unary_expression: DEC_OP unary_expression  */
#line 226 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("PreDecrement");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1866 "parser.tab.c"
    break;

  case 19: /* unary_expression: unary_operator cast_expression  */
#line 232 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode((yyvsp[-1].astNode)->lineno, "UnaryOp", (yyvsp[-1].astNode)->value);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1876 "parser.tab.c"
    break;

  case 20: /* unary_expression: SIZEOF unary_expression  */
#line 238 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("SizeofExpr");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1886 "parser.tab.c"
    break;

  case 21: /* unary_expression: SIZEOF LPAREN type_name RPAREN  */
#line 244 "parser.y"
      { 
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("SizeofType");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 1896 "parser.tab.c"
    break;

  case 22: /* unary_operator: BIT_AND  */
#line 254 "parser.y"
    {
        cout<<__LINE__<<endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "UnaryOp", "&");
    }
#line 1905 "parser.tab.c"
    break;

  case 23: /* unary_operator: STAR  */
#line 259 "parser.y"
    {
        cout<<__LINE__<<endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "UnaryOp", "*");
    }
#line 1914 "parser.tab.c"
    break;

  case 24: /* unary_operator: PLUS  */
#line 264 "parser.y"
    {
        cout<<__LINE__<<endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "UnaryOp", "+");
    }
#line 1923 "parser.tab.c"
    break;

  case 25: /* unary_operator: MINUS  */
#line 269 "parser.y"
    {
        cout<<__LINE__<<endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "UnaryOp", "-");
    }
#line 1932 "parser.tab.c"
    break;

  case 26: /* unary_operator: BIT_NOT  */
#line 274 "parser.y"
    {
        cout<<__LINE__<<endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "UnaryOp", "~");
    }
#line 1941 "parser.tab.c"
    break;

  case 27: /* unary_operator: NOT_OP  */
#line 279 "parser.y"
    {
        cout<<__LINE__<<endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "UnaryOp", "!");
    }
#line 1950 "parser.tab.c"
    break;

  case 28: /* cast_expression: unary_expression  */
#line 287 "parser.y"
      { 
        // cout << __LINE__ << endl; 
        (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 1959 "parser.tab.c"
    break;

  case 29: /* cast_expression: LPAREN type_name RPAREN cast_expression  */
#line 292 "parser.y"
      { 
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode("TypeCast");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1970 "parser.tab.c"
    break;

  case 30: /* multiplicative_expression: cast_expression  */
#line 303 "parser.y"
      { 
        // cout << __LINE__ << endl; 
        (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 1979 "parser.tab.c"
    break;

  case 31: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 308 "parser.y"
      { 
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Multiplication", "*"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 1990 "parser.tab.c"
    break;

  case 32: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 315 "parser.y"
      { 
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Division", "/"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2001 "parser.tab.c"
    break;

  case 33: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 322 "parser.y"
      { 
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Modulus", "%"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2012 "parser.tab.c"
    break;

  case 34: /* additive_expression: multiplicative_expression  */
#line 332 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2021 "parser.tab.c"
    break;

  case 35: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 337 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Addition", "+"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2032 "parser.tab.c"
    break;

  case 36: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 344 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Subtraction", "-"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2043 "parser.tab.c"
    break;

  case 37: /* shift_expression: additive_expression  */
#line 354 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2052 "parser.tab.c"
    break;

  case 38: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 359 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "LeftShift", "<<"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2063 "parser.tab.c"
    break;

  case 39: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 366 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "RightShift", ">>"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2074 "parser.tab.c"
    break;

  case 40: /* relational_expression: shift_expression  */
#line 376 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2083 "parser.tab.c"
    break;

  case 41: /* relational_expression: relational_expression LESSER_OP shift_expression  */
#line 381 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Lesser", "<"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2094 "parser.tab.c"
    break;

  case 42: /* relational_expression: relational_expression GREATER_OP shift_expression  */
#line 388 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Greater", ">"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2105 "parser.tab.c"
    break;

  case 43: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 395 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "LesserEqual", "<="); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2116 "parser.tab.c"
    break;

  case 44: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 402 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "GreaterEqual", ">="); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2127 "parser.tab.c"
    break;

  case 45: /* equality_expression: relational_expression  */
#line 412 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2136 "parser.tab.c"
    break;

  case 46: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 417 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Equal", "=="); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2147 "parser.tab.c"
    break;

  case 47: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 424 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "NotEqual", "!="); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2158 "parser.tab.c"
    break;

  case 48: /* and_expression: equality_expression  */
#line 434 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2167 "parser.tab.c"
    break;

  case 49: /* and_expression: and_expression BIT_AND equality_expression  */
#line 439 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "BitwiseAnd", "&"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2178 "parser.tab.c"
    break;

  case 50: /* exclusive_or_expression: and_expression  */
#line 449 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2187 "parser.tab.c"
    break;

  case 51: /* exclusive_or_expression: exclusive_or_expression XOR and_expression  */
#line 454 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "BitwiseXor", "^"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2198 "parser.tab.c"
    break;

  case 52: /* inclusive_or_expression: exclusive_or_expression  */
#line 464 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2207 "parser.tab.c"
    break;

  case 53: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 469 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "BitwiseOr", "|"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2218 "parser.tab.c"
    break;

  case 54: /* logical_and_expression: inclusive_or_expression  */
#line 479 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2227 "parser.tab.c"
    break;

  case 55: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 484 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "LogicalAnd", "&&"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2238 "parser.tab.c"
    break;

  case 56: /* logical_or_expression: logical_and_expression  */
#line 494 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2247 "parser.tab.c"
    break;

  case 57: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 499 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "LogicalOr", "||"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2258 "parser.tab.c"
    break;

  case 58: /* conditional_expression: logical_or_expression  */
#line 509 "parser.y"
      { 
      // cout << __LINE__ << endl;  
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2267 "parser.tab.c"
    break;

  case 59: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 514 "parser.y"
      { 
      // cout << __LINE__ << endl;
      (yyval.astNode) = new ASTNode("ConditionalExpression"); 
      (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2279 "parser.tab.c"
    break;

  case 60: /* assignment_expression: conditional_expression  */
#line 525 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2288 "parser.tab.c"
    break;

  case 61: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 530 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[-1].astNode)->lineno, "AssignmentExpression", (yyvsp[-1].astNode)->value); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2299 "parser.tab.c"
    break;

  case 62: /* assignment_operator: ASSIGN  */
#line 540 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "=");
      }
#line 2308 "parser.tab.c"
    break;

  case 63: /* assignment_operator: MUL_ASSIGN  */
#line 545 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "*=");
      }
#line 2317 "parser.tab.c"
    break;

  case 64: /* assignment_operator: DIV_ASSIGN  */
#line 550 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "/=");
      }
#line 2326 "parser.tab.c"
    break;

  case 65: /* assignment_operator: MOD_ASSIGN  */
#line 555 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "%=");
      }
#line 2335 "parser.tab.c"
    break;

  case 66: /* assignment_operator: ADD_ASSIGN  */
#line 560 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "+=");
      }
#line 2344 "parser.tab.c"
    break;

  case 67: /* assignment_operator: SUB_ASSIGN  */
#line 565 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "-=");
      }
#line 2353 "parser.tab.c"
    break;

  case 68: /* assignment_operator: LEFT_ASSIGN  */
#line 570 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "<<=");
      }
#line 2362 "parser.tab.c"
    break;

  case 69: /* assignment_operator: RIGHT_ASSIGN  */
#line 575 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", ">>=");
      }
#line 2371 "parser.tab.c"
    break;

  case 70: /* assignment_operator: AND_ASSIGN  */
#line 580 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "&=");
      }
#line 2380 "parser.tab.c"
    break;

  case 71: /* assignment_operator: XOR_ASSIGN  */
#line 585 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "^=");
      }
#line 2389 "parser.tab.c"
    break;

  case 72: /* assignment_operator: OR_ASSIGN  */
#line 590 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "AssignmentOperator", "|=");
      }
#line 2398 "parser.tab.c"
    break;

  case 73: /* expression: assignment_expression  */
#line 598 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2407 "parser.tab.c"
    break;

  case 74: /* expression: expression COMMA assignment_expression  */
#line 603 "parser.y"
      { 
      // cout << __LINE__ << endl; 
      (yyval.astNode) = new ASTNode("Expression"); 
      (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2418 "parser.tab.c"
    break;

  case 75: /* constant_expression: conditional_expression  */
#line 612 "parser.y"
                             {cout<<__LINE__<<endl; (yyval.astNode) = (yyvsp[0].astNode);}
#line 2424 "parser.tab.c"
    break;

  case 76: /* declaration: declaration_specifiers SEMI_COLON  */
#line 617 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("Declaration"); 
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
      }
#line 2434 "parser.tab.c"
    break;

  case 77: /* declaration: declaration_specifiers init_declarator_list SEMI_COLON  */
#line 623 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("Declaration"); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode));  
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
          handleDeclaration((yyvsp[-2].astNode), (yyvsp[-1].astNode));
      }
#line 2446 "parser.tab.c"
    break;

  case 78: /* declaration_specifiers: storage_class_specifier  */
#line 634 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2455 "parser.tab.c"
    break;

  case 79: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 639 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) =  (yyvsp[-1].astNode);
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2465 "parser.tab.c"
    break;

  case 80: /* declaration_specifiers: type_specifier  */
#line 645 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2474 "parser.tab.c"
    break;

  case 81: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 650 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) =  (yyvsp[-1].astNode);
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2484 "parser.tab.c"
    break;

  case 82: /* declaration_specifiers: type_qualifier  */
#line 656 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2493 "parser.tab.c"
    break;

  case 83: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 661 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) =  (yyvsp[-1].astNode);
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2503 "parser.tab.c"
    break;

  case 84: /* init_declarator_list: init_declarator  */
#line 670 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].astNode)->lineno, "InitDeclaratorList", "initDeclaratorList");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2513 "parser.tab.c"
    break;

  case 85: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 676 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2523 "parser.tab.c"
    break;

  case 86: /* init_declarator: declarator  */
#line 685 "parser.y"
    {
        // cout << __LINE__ << endl;  
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 2532 "parser.tab.c"
    break;

  case 87: /* init_declarator: declarator ASSIGN initializer  */
#line 690 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Initializer", "="); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2543 "parser.tab.c"
    break;

  case 88: /* storage_class_specifier: TYPEDEF  */
#line 700 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "StorageClassSpecifier", "typedef");
    }
#line 2552 "parser.tab.c"
    break;

  case 89: /* storage_class_specifier: EXTERN  */
#line 705 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "StorageClassSpecifier", "extern");
    }
#line 2561 "parser.tab.c"
    break;

  case 90: /* storage_class_specifier: STATIC  */
#line 710 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "StorageClassSpecifier", "static");
    }
#line 2570 "parser.tab.c"
    break;

  case 91: /* storage_class_specifier: AUTO  */
#line 715 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "StorageClassSpecifier", "auto");
    }
#line 2579 "parser.tab.c"
    break;

  case 92: /* storage_class_specifier: REGISTER  */
#line 720 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "StorageClassSpecifier", "register");
    }
#line 2588 "parser.tab.c"
    break;

  case 93: /* type_specifier: VOID  */
#line 728 "parser.y"
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "void";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "void");
    }
#line 2598 "parser.tab.c"
    break;

  case 94: /* type_specifier: CHAR  */
#line 734 "parser.y"
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "char";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "char");
    }
#line 2608 "parser.tab.c"
    break;

  case 95: /* type_specifier: SHORT  */
#line 740 "parser.y"
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "short";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "short");
    }
#line 2618 "parser.tab.c"
    break;

  case 96: /* type_specifier: INT  */
#line 746 "parser.y"
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "int";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "int");
    }
#line 2628 "parser.tab.c"
    break;

  case 97: /* type_specifier: LONG  */
#line 752 "parser.y"
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "long";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "long");
    }
#line 2638 "parser.tab.c"
    break;

  case 98: /* type_specifier: FLOAT  */
#line 758 "parser.y"
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "float"; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "float");
    }
#line 2648 "parser.tab.c"
    break;

  case 99: /* type_specifier: DOUBLE  */
#line 764 "parser.y"
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "double"; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "double");
    }
#line 2658 "parser.tab.c"
    break;

  case 100: /* type_specifier: SIGNED  */
#line 770 "parser.y"
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "signed";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "signed");
    }
#line 2668 "parser.tab.c"
    break;

  case 101: /* type_specifier: UNSIGNED  */
#line 776 "parser.y"
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = "unsigned"; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "unsigned");
    }
#line 2678 "parser.tab.c"
    break;

  case 102: /* type_specifier: struct_or_union_specifier  */
#line 782 "parser.y"
    {
        // cout << __LINE__ << endl;
        // currentTypeSpecifier = $1->value; 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2688 "parser.tab.c"
    break;

  case 103: /* type_specifier: enum_specifier  */
#line 788 "parser.y"
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "enum";
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2698 "parser.tab.c"
    break;

  case 104: /* type_specifier: TYPE_NAME  */
#line 794 "parser.y"
    {
        // cout << __LINE__ << endl; 
        // currentTypeSpecifier = "typeName";
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeSpecifier", "TypeName");
    }
#line 2708 "parser.tab.c"
    break;

  case 105: /* struct_or_union_specifier: struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY  */
#line 803 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = (yyvsp[-4].astNode);
        string isStruct = (yyvsp[-4].astNode)->value == "struct" ? "structIdentifier" : "unionIdentifier";
        (yyval.astNode)->addChild(new ASTNode((yyvsp[-3].tokenAtr)->lineno, isStruct, (yyvsp[-3].tokenAtr)->value)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        identifierToType.push_back({(yyvsp[-3].tokenAtr)->lineno, {(yyvsp[-3].tokenAtr)->value, (yyvsp[-4].astNode)->value}});
    }
#line 2721 "parser.tab.c"
    break;

  case 106: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list RCURLY  */
#line 812 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
    }
#line 2731 "parser.tab.c"
    break;

  case 107: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 818 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = (yyvsp[-1].astNode);
        string isStruct = (yyvsp[-1].astNode)->value == "struct" ? "struct" : "union";
        (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, isStruct, (yyvsp[0].tokenAtr)->value));
        identifierToType.push_back({(yyvsp[0].tokenAtr)->lineno, {(yyvsp[0].tokenAtr)->value, (yyvsp[-1].astNode)->value}});
    }
#line 2743 "parser.tab.c"
    break;

  case 108: /* struct_or_union: STRUCT  */
#line 829 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "Struct", "struct");
    }
#line 2752 "parser.tab.c"
    break;

  case 109: /* struct_or_union: UNION  */
#line 834 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "Union", "union");
    }
#line 2761 "parser.tab.c"
    break;

  case 110: /* struct_declaration_list: struct_declaration  */
#line 842 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode("StructOrUnionDeclarationList");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2771 "parser.tab.c"
    break;

  case 111: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 848 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode("StructOrUnionDeclarationList");
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2782 "parser.tab.c"
    break;

  case 112: /* struct_declaration: specifier_qualifier_list struct_declarator_list SEMI_COLON  */
#line 858 "parser.y"
    {
        // cout << __LINE__ << endl; 
        (yyval.astNode) = new ASTNode("StructOrUnionDeclaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        handleStructUnionDeclaration((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 2794 "parser.tab.c"
    break;

  case 113: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 869 "parser.y"
    {
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2804 "parser.tab.c"
    break;

  case 114: /* specifier_qualifier_list: type_specifier  */
#line 875 "parser.y"
    {
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2813 "parser.tab.c"
    break;

  case 115: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 880 "parser.y"
    {
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2823 "parser.tab.c"
    break;

  case 116: /* specifier_qualifier_list: type_qualifier  */
#line 886 "parser.y"
    {
        // cout << __LINE__ << endl;
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2832 "parser.tab.c"
    break;

  case 117: /* struct_declarator_list: struct_declarator  */
#line 894 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("StructOrUnionDeclaratorList");
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 2842 "parser.tab.c"
    break;

  case 118: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 900 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("StructOrUnionDeclaratorList");
          (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2853 "parser.tab.c"
    break;

  case 119: /* struct_declarator: declarator  */
#line 910 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2862 "parser.tab.c"
    break;

  case 120: /* struct_declarator: COLON constant_expression  */
#line 915 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "StructOrUnionDeclarator", ":"); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 2872 "parser.tab.c"
    break;

  case 121: /* struct_declarator: declarator COLON constant_expression  */
#line 921 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "StructOrUnionDeclarator", ":");
          (yyval.astNode)->addChild((yyvsp[-2].astNode));
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 2883 "parser.tab.c"
    break;

  case 122: /* enum_specifier: ENUM LCURLY enumerator_list RCURLY  */
#line 931 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-3].tokenAtr)->lineno, "EnumSpecifier", "enumSpecifier"); 
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
          handleEnumDeclaration((yyval.astNode));
      }
#line 2894 "parser.tab.c"
    break;

  case 123: /* enum_specifier: ENUM IDENTIFIER LCURLY enumerator_list RCURLY  */
#line 938 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-4].tokenAtr)->lineno, "EnumSpecifier", "enumSpecifier"); 
          (yyval.astNode)->addChild(new ASTNode((yyvsp[-3].tokenAtr)->lineno, "enumIdentifier", (yyvsp[-3].tokenAtr)->value));
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
          handleEnumDeclaration((yyval.astNode));
      }
#line 2906 "parser.tab.c"
    break;

  case 124: /* enum_specifier: ENUM IDENTIFIER  */
#line 946 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("EnumSpecifier", "enumSpecifier"); 
          (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, "enumIdentifier", (yyvsp[0].tokenAtr)->value));
          handleEnumDeclaration((yyval.astNode));
      }
#line 2917 "parser.tab.c"
    break;

  case 125: /* enumerator_list: enumerator  */
#line 956 "parser.y"
    {
      cout<<__LINE__<<endl; 
      (yyval.astNode) = new ASTNode("EnumList");
      (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2927 "parser.tab.c"
    break;

  case 126: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 962 "parser.y"
    {
      cout<<__LINE__<<endl; 
      (yyval.astNode) = new ASTNode("EnumList");
      (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
      (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2938 "parser.tab.c"
    break;

  case 127: /* enumerator: IDENTIFIER  */
#line 972 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "EnumItem", (yyvsp[0].tokenAtr)->value);
      }
#line 2947 "parser.tab.c"
    break;

  case 128: /* enumerator: IDENTIFIER ASSIGN constant_expression  */
#line 977 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "EnumAssignment", "=");
          (yyval.astNode)->addChild(new ASTNode((yyvsp[-2].tokenAtr)->lineno, "EnumItem", (yyvsp[-2].tokenAtr)->value)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode));  
      }
#line 2958 "parser.tab.c"
    break;

  case 129: /* type_qualifier: CONST  */
#line 987 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeQualifier", "const");
      }
#line 2967 "parser.tab.c"
    break;

  case 130: /* type_qualifier: VOLATILE  */
#line 992 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "TypeQualifier", "volatile");
      }
#line 2976 "parser.tab.c"
    break;

  case 131: /* declarator: pointer direct_declarator  */
#line 1000 "parser.y"
      {
          (yyval.astNode) = new ASTNode("PointerDeclarator", "pointerDeclarator");
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 2986 "parser.tab.c"
    break;

  case 132: /* declarator: direct_declarator  */
#line 1006 "parser.y"
      {
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 2994 "parser.tab.c"
    break;

  case 133: /* direct_declarator: IDENTIFIER  */
#line 1013 "parser.y"
      {
          // cout << __LINE__ << endl;
          // identifierToType.push_back({$1->value, currentTypeSpecifier});
          (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "Identifier", (yyvsp[0].tokenAtr)->value);
      }
#line 3004 "parser.tab.c"
    break;

  case 134: /* direct_declarator: LPAREN declarator RPAREN  */
#line 1019 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-1].astNode);
      }
#line 3013 "parser.tab.c"
    break;

  case 135: /* direct_declarator: direct_declarator LSQUARE constant_expression RSQUARE  */
#line 1024 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ArrayDeclaration");
          (yyval.astNode)->addChild((yyvsp[-3].astNode));
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 3024 "parser.tab.c"
    break;

  case 136: /* direct_declarator: direct_declarator LSQUARE RSQUARE  */
#line 1031 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ArrayDeclaration");
          (yyval.astNode)->addChild((yyvsp[-2].astNode));
      }
#line 3034 "parser.tab.c"
    break;

  case 137: /* direct_declarator: direct_declarator LPAREN parameter_type_list RPAREN  */
#line 1037 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-3].astNode);
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 3044 "parser.tab.c"
    break;

  case 138: /* direct_declarator: direct_declarator LPAREN identifier_list RPAREN  */
#line 1043 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-3].astNode);
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 3054 "parser.tab.c"
    break;

  case 139: /* direct_declarator: direct_declarator LPAREN RPAREN  */
#line 1049 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-2].astNode);
          (yyvsp[-2].astNode)->addChild(new ASTNode((yyvsp[-1].tokenAtr)->lineno, "EmptyList", "emptyList"));
      }
#line 3064 "parser.tab.c"
    break;

  case 140: /* pointer: STAR  */
#line 1058 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)->lineno, "Pointer", "pointer");
      }
#line 3073 "parser.tab.c"
    break;

  case 141: /* pointer: STAR type_qualifier_list  */
#line 1063 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Pointer", "*");
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 3083 "parser.tab.c"
    break;

  case 142: /* pointer: STAR pointer  */
#line 1069 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "Pointer", "*");
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 3093 "parser.tab.c"
    break;

  case 143: /* pointer: STAR type_qualifier_list pointer  */
#line 1075 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[-2].tokenAtr)->lineno, "Pointer", "*");
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 3104 "parser.tab.c"
    break;

  case 144: /* type_qualifier_list: type_qualifier  */
#line 1085 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 3113 "parser.tab.c"
    break;

  case 145: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1090 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-1].astNode);
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 3123 "parser.tab.c"
    break;

  case 146: /* parameter_type_list: parameter_list  */
#line 1099 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3132 "parser.tab.c"
    break;

  case 147: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1104 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-2].astNode); 
          (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, "Ellipsis", "...")); 
      }
#line 3142 "parser.tab.c"
    break;

  case 148: /* parameter_list: parameter_declaration  */
#line 1113 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("ParameterList", "parameterList");
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3152 "parser.tab.c"
    break;

  case 149: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1119 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-2].astNode);
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3162 "parser.tab.c"
    break;

  case 150: /* parameter_declaration: declaration_specifiers declarator  */
#line 1128 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ParameterDeclaration", "parameterDeclaration");
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode));  
      }
#line 3173 "parser.tab.c"
    break;

  case 151: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1135 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ParameterDeclaration", "parameterDeclaration");
          (yyval.astNode)->addChild((yyvsp[-1].astNode));  
          (yyval.astNode)->addChild((yyvsp[0].astNode));  
      }
#line 3184 "parser.tab.c"
    break;

  case 152: /* parameter_declaration: declaration_specifiers  */
#line 1142 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ParameterDeclaration", "parameterDeclaration");
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3194 "parser.tab.c"
    break;

  case 153: /* identifier_list: IDENTIFIER  */
#line 1151 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("IdentifierList", "identifierList");
          (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, "Identifier", (yyvsp[0].tokenAtr)->value)); 
      }
#line 3204 "parser.tab.c"
    break;

  case 154: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 1157 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-2].astNode); 
          (yyval.astNode)->addChild(new ASTNode((yyvsp[0].tokenAtr)->lineno, "Identifier", (yyvsp[0].tokenAtr)->value)); 
      }
#line 3214 "parser.tab.c"
    break;

  case 155: /* type_name: specifier_qualifier_list  */
#line 1166 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3223 "parser.tab.c"
    break;

  case 156: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1171 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-1].astNode); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3233 "parser.tab.c"
    break;

  case 157: /* abstract_declarator: pointer  */
#line 1180 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3242 "parser.tab.c"
    break;

  case 158: /* abstract_declarator: direct_abstract_declarator  */
#line 1185 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3251 "parser.tab.c"
    break;

  case 159: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1190 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-1].astNode); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3261 "parser.tab.c"
    break;

  case 160: /* direct_abstract_declarator: LPAREN abstract_declarator RPAREN  */
#line 1199 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-1].astNode);  
      }
#line 3270 "parser.tab.c"
    break;

  case 161: /* direct_abstract_declarator: LSQUARE RSQUARE  */
#line 1204 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ArrayDeclaration"); 
      }
#line 3279 "parser.tab.c"
    break;

  case 162: /* direct_abstract_declarator: LSQUARE constant_expression RSQUARE  */
#line 1209 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ArrayDeclaration");  
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
      }
#line 3289 "parser.tab.c"
    break;

  case 163: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE RSQUARE  */
#line 1215 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-2].astNode);  
          (yyval.astNode)->addChild(new ASTNode("ArrayDeclaration"));  
      }
#line 3299 "parser.tab.c"
    break;

  case 164: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression RSQUARE  */
#line 1221 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-3].astNode);  
          (yyval.astNode)->addChild(new ASTNode("ArrayDeclaration"));  
          (yyval.astNode)->addChild((yyvsp[-1].astNode));
      }
#line 3310 "parser.tab.c"
    break;

  case 165: /* direct_abstract_declarator: LPAREN RPAREN  */
#line 1228 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode("ParameterList", "parameterList"); 
      }
#line 3319 "parser.tab.c"
    break;

  case 166: /* direct_abstract_declarator: LPAREN parameter_type_list RPAREN  */
#line 1233 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-1].astNode); 
      }
#line 3328 "parser.tab.c"
    break;

  case 167: /* direct_abstract_declarator: direct_abstract_declarator LPAREN RPAREN  */
#line 1238 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-2].astNode); 
          (yyval.astNode)->addChild(new ASTNode("ParameterList", "parameterList")); 
      }
#line 3338 "parser.tab.c"
    break;

  case 168: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list RPAREN  */
#line 1244 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-3].astNode); 
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
      }
#line 3348 "parser.tab.c"
    break;

  case 169: /* initializer: assignment_expression  */
#line 1254 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 3357 "parser.tab.c"
    break;

  case 170: /* initializer: LCURLY initializer_list RCURLY  */
#line 1259 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-1].astNode); 
      }
#line 3366 "parser.tab.c"
    break;

  case 171: /* initializer: LCURLY initializer_list COMMA RCURLY  */
#line 1264 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[-2].astNode);  
      }
#line 3375 "parser.tab.c"
    break;

  case 172: /* initializer_list: initializer  */
#line 1273 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3384 "parser.tab.c"
    break;

  case 173: /* initializer_list: initializer_list COMMA initializer  */
#line 1278 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-2].astNode); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3394 "parser.tab.c"
    break;

  case 174: /* statement: labeled_statement  */
#line 1287 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3403 "parser.tab.c"
    break;

  case 175: /* statement: compound_statement  */
#line 1292 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3412 "parser.tab.c"
    break;

  case 176: /* statement: expression_statement  */
#line 1297 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3421 "parser.tab.c"
    break;

  case 177: /* statement: selection_statement  */
#line 1302 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3430 "parser.tab.c"
    break;

  case 178: /* statement: iteration_statement  */
#line 1307 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3439 "parser.tab.c"
    break;

  case 179: /* statement: jump_statement  */
#line 1312 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3448 "parser.tab.c"
    break;

  case 180: /* statement: declaration  */
#line 1317 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3457 "parser.tab.c"
    break;

  case 181: /* labeled_statement: IDENTIFIER COLON statement  */
#line 1326 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[-2].tokenAtr)->lineno, "LabeledStatement", (yyvsp[-2].tokenAtr)->value); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3467 "parser.tab.c"
    break;

  case 182: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1332 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[-3].tokenAtr)->lineno, "CaseStatement", "Case");
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode));
      }
#line 3478 "parser.tab.c"
    break;

  case 183: /* labeled_statement: DEFAULT COLON statement  */
#line 1339 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = new ASTNode((yyvsp[-2].tokenAtr)->lineno, "DefaultStatement", "Default"); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3488 "parser.tab.c"
    break;

  case 184: /* compound_statement: LCURLY RCURLY  */
#line 1348 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("CompoundStatement", "{}"); 
      }
#line 3497 "parser.tab.c"
    break;

  case 185: /* compound_statement: LCURLY statement_list RCURLY  */
#line 1353 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("CompoundStatement", "{}"); 
          (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
      }
#line 3507 "parser.tab.c"
    break;

  case 186: /* compound_statement: LCURLY declaration_list RCURLY  */
#line 1359 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("CompoundStatement", "{}"); 
          (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
      }
#line 3517 "parser.tab.c"
    break;

  case 187: /* compound_statement: LCURLY declaration_list statement_list RCURLY  */
#line 1365 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("CompoundStatement", "{}"); 
          (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children); 
          (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
      }
#line 3528 "parser.tab.c"
    break;

  case 188: /* declaration_list: declaration  */
#line 1375 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3537 "parser.tab.c"
    break;

  case 189: /* declaration_list: declaration_list declaration  */
#line 1380 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-1].astNode); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3547 "parser.tab.c"
    break;

  case 190: /* statement_list: statement  */
#line 1389 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("StatementList"); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3557 "parser.tab.c"
    break;

  case 191: /* statement_list: statement_list statement  */
#line 1395 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-1].astNode); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3567 "parser.tab.c"
    break;

  case 192: /* expression_statement: SEMI_COLON  */
#line 1404 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("ExpressionStatement", ";"); 
      }
#line 3576 "parser.tab.c"
    break;

  case 193: /* expression_statement: expression SEMI_COLON  */
#line 1409 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-1].astNode); 
      }
#line 3585 "parser.tab.c"
    break;

  case 194: /* selection_statement: IF LPAREN expression RPAREN statement  */
#line 1417 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-4].tokenAtr)->lineno, "IfStatement", "if"); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3596 "parser.tab.c"
    break;

  case 195: /* selection_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 1424 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-6].tokenAtr)->lineno, "IfElseStatement", "if-else"); 
          (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3608 "parser.tab.c"
    break;

  case 196: /* selection_statement: SWITCH LPAREN expression RPAREN statement  */
#line 1432 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-4].tokenAtr)->lineno, "SwitchStatement", "switch"); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3619 "parser.tab.c"
    break;

  case 197: /* iteration_statement: WHILE LPAREN expression RPAREN statement  */
#line 1442 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-4].tokenAtr)->lineno, "WhileLoop", "while"); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3630 "parser.tab.c"
    break;

  case 198: /* iteration_statement: UNTIL LPAREN expression RPAREN statement  */
#line 1449 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-4].tokenAtr)->lineno, "UntilLoop", "until"); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3641 "parser.tab.c"
    break;

  case 199: /* iteration_statement: DO statement WHILE LPAREN expression RPAREN SEMI_COLON  */
#line 1456 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-6].tokenAtr)->lineno, "DoWhileLoop", "do-while"); 
          (yyval.astNode)->addChild((yyvsp[-5].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
      }
#line 3652 "parser.tab.c"
    break;

  case 200: /* iteration_statement: FOR LPAREN expression_statement expression_statement RPAREN statement  */
#line 1463 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-5].tokenAtr)->lineno, "ForLoop", "for"); 
          (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3664 "parser.tab.c"
    break;

  case 201: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 1471 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-6].tokenAtr)->lineno, "ForLoop", "for"); 
          (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3677 "parser.tab.c"
    break;

  case 202: /* iteration_statement: FOR LPAREN declaration expression_statement expression RPAREN statement  */
#line 1480 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-6].tokenAtr)->lineno, "ForLoop", "for"); 
          (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
          (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3690 "parser.tab.c"
    break;

  case 203: /* jump_statement: GOTO IDENTIFIER SEMI_COLON  */
#line 1492 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-2].tokenAtr)->lineno, "GotoStatement", "goto"); 
          (yyval.astNode)->addChild(new ASTNode("Identifier", (yyvsp[-1].tokenAtr)->value)); 
      }
#line 3700 "parser.tab.c"
    break;

  case 204: /* jump_statement: CONTINUE SEMI_COLON  */
#line 1498 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "ContinueStatement", "continue"); 
      }
#line 3709 "parser.tab.c"
    break;

  case 205: /* jump_statement: BREAK SEMI_COLON  */
#line 1503 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "BreakStatement", "break"); 
      }
#line 3718 "parser.tab.c"
    break;

  case 206: /* jump_statement: RETURN SEMI_COLON  */
#line 1508 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-1].tokenAtr)->lineno, "ReturnStatement", "return"); 
      }
#line 3727 "parser.tab.c"
    break;

  case 207: /* jump_statement: RETURN expression SEMI_COLON  */
#line 1513 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode((yyvsp[-2].tokenAtr)->lineno, "ReturnStatement", "return"); 
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
      }
#line 3737 "parser.tab.c"
    break;

  case 208: /* translation_unit: external_declaration  */
#line 1522 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("TranslationUnit", "translationUnit");
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
          root = (yyval.astNode);
      }
#line 3748 "parser.tab.c"
    break;

  case 209: /* translation_unit: translation_unit external_declaration  */
#line 1529 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[-1].astNode); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
      }
#line 3758 "parser.tab.c"
    break;

  case 210: /* external_declaration: function_definition  */
#line 1538 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3767 "parser.tab.c"
    break;

  case 211: /* external_declaration: declaration  */
#line 1543 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = (yyvsp[0].astNode); 
      }
#line 3776 "parser.tab.c"
    break;

  case 212: /* external_declaration: function_declaration  */
#line 1548 "parser.y"
      {
          // cout << __LINE__ << endl;
          (yyval.astNode) = (yyvsp[0].astNode);
      }
#line 3785 "parser.tab.c"
    break;

  case 213: /* function_declaration: declaration_specifiers declarator SEMI_COLON  */
#line 1556 "parser.y"
    {
        // cout << __LINE__ << endl;
        (yyval.astNode) = new ASTNode("FunctionDeclaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        handleFunctionDefinition((yyvsp[-1].astNode));
    }
#line 3797 "parser.tab.c"
    break;

  case 214: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 1577 "parser.y"
      { 
          // cout << __LINE__ << endl; 
          (yyval.astNode) = new ASTNode("FunctionDefinition"); 
          (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
          (yyval.astNode)->addChild((yyvsp[0].astNode)); 
          handleFunctionDefinition((yyvsp[-1].astNode));
      }
#line 3809 "parser.tab.c"
    break;


#line 3813 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 1601 "parser.y"



void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}



// main function

int main(int argc, char **argv) {

    //------------------------ cmd line arguments handling ------------------------

        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [-d<debug_mode>] [-p [<DOTFileName>] ] [-r <recursiveOutputFile]\n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];
        std::string debug_mode;
        std::string dot_file;
        std::string recursive_output_file;
        std::string SExp_file;

        // Parse arguments
        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg[0] == '-' && arg[1] == 'd') {
                // Ignore
            } else if (arg == "-p") {
                // Check if there is another argument after "-p"
                if (i + 1 < argc) {
                    dot_file = argv[++i]; // Assign the next argument as the DOT file
                } else {
                    // If name is not provided after "-p"
                    // Create a default name for the DOT file
                    std::string base_name = input_file.substr(0, input_file.find_last_of("."));
                    dot_file = base_name + ".dot";
                }
            }else if(arg == "-r"){
                // Check if there is another argument after "-r"
                if (i + 1 < argc) {
                    recursive_output_file = argv[++i]; // Assign the next argument as the recursive output file
                } else {
                    std::cerr << "2Error: Invalid argument.\n";
                    return 1;
                }
            } else if(arg == "-s"){
                // Check if there is another argument after "-s"
                if (i + 1 < argc) {
                    SExp_file = argv[++i]; // Assign the next argument as the SExp output file
                }
                else {
                    std::cerr << "1Error: Invalid argument.\n";
                    return 1;
                }
            } else {
                std::cerr << "4Error: Invalid argument.\n";
                return 1;
            }
        }

    //------------------------ input file handling ------------------------
        yyin = fopen(input_file.c_str(), "r");
        if (!yyin) {
            std::cerr << "E12rror: Unable to open input file.\n";
            return 1;
        }

        freopen(output_file.c_str(), "w", stdout); // stdout will be redirected to output file
        
        //------ToDo[Later]: Redirect cerr to error.txt file------
        // cerr is not redirected to output file it will be printed to console 
        // When we need to show parser errors to the user, we can use cerr to a error.txt file (not now)

    // ------------------------ Symbol Table ------------------------
        // Create a new symbol table
        /* SymbolTable *symTable = new SymbolTable(); */


    //------------------------ Parsing ------------------------

        std::cout << "..........Starting parsing..........\n";
        yyparse();  // Call BISON's parser
        std::cout << "..........Parsing complete..........\n";




    // ------------------------- Printing Various Outputs ------------------------
    
        // Print AST as DOT file
            if(!dot_file.empty()){
                generateDOT(root, dot_file);
            }

        // Print Recursive Output
            if(!recursive_output_file.empty()){
                printASTToFile(root, recursive_output_file);
            }    

        // Print S-Expression
            if(!SExp_file.empty()){
                writeASTToSExpression(root, SExp_file);
            }

        // Print Normal AST
            if(true){
                printAST(root);
            }

    //------------------------- Cleanup ------------------------
        if (yyin) fclose(yyin);  // Close the input file if opened
        return 0;
}

