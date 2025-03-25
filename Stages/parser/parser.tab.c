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
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utility.h"  

#define EMPTY_VAL "!!EMPTY!!"

#define LINE std::cerr<<__LINE__<<std::endl;
// #define LINE /**/

// #define LINE std::cerr<<__LINE__<<std::endl;
#define LINE /**/

#define PARSERLOGHEADER "----------------------------------- PARSER LOG -----------------------------------"
#define LOGFOOTER       "----------------------------------- END OF LOG -----------------------------------"
#define LEXERLOGHEADER  "----------------------------------- LEXER LOG ------------------------------------"

// Global DS 
std::vector<std::pair<std::pair<int,int>, std::pair<std::string, std::string>> > PARSER_TABLE;


// Handler Functions
void Struct_Union_Declaration_Handler(ASTNode* specifierQualifierList, ASTNode* declaratorList);
void Enum_Declaration_Handler(ASTNode* enumSpecifier);
void Function_Def_Handler(ASTNode* declarator);
void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList);
void printParserTable(std::ostream& out);
void writeLatexTable(std::ostream& out);


// Extern Variables
extern int yylineno;
extern char *yytext;
void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;

extern std::vector<std::string> lexerLOG;
std::vector<std::string> parserLOG;

extern std::string lastToken;


bool bisonError = false;
bool customError = false;

std::ofstream* output = nullptr;  // Global pointer

#define YYDEBUG 1

// std::ofstream PARSERlog("parser.log", std::ios::trunc); // [[NOt in use]]

std::string getPosition(TokenAttribute* token){
    return std::to_string(token->position.first) + ":" + std::to_string(token->position.second);
}

std::string getPosition(ASTNode* node){
    return std::to_string(node->position.first) + ":" + std::to_string(node->position.second);
}


void ourError(const std::string& msg) {
    std::string error = "Syntax Error at line " + std::to_string(yylineno) + " near token: " + lastToken;
    error += " | Error Description: " + msg;
    parserLOG.push_back(error);
    customError = true;
}

void initOutputFile(const std::string& filename) {
    output = new std::ofstream(filename);
    if (!output->is_open()) {
        delete output;
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        output = nullptr;
    }
}

void closeOutputFile() {
    if (output) {
        output->close();
        delete output;
        output = nullptr;
    }
}

void signalHandler(int signum) {
    *output << "\U0001F6A8 * Input Program failed in the PARSE stage \U0001F6A8\n" << std::endl;
    // cerr the log
    *output << PARSERLOGHEADER << std::endl;
    for (auto& log : parserLOG) {
        *output << log << std::endl;
        // TODO ------------ Handle this [ Not printing the logs of parser ]
        if(parserLOG.size()==0){
            *output << "$ Syntax Error at line " << yylineno << " near token: " << lastToken << std::endl;
        }
    }
    *output << LOGFOOTER << std::endl;
    *output << std::endl;

    *output << "--- No Further Processing will be done ---" << std::endl;
    closeOutputFile();
    exit(0); // Clean Exit
}


ASTNode *root;

#line 190 "parser.tab.c"

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
  YYSYMBOL_UNKNOWN_TOKEN = 87,             /* UNKNOWN_TOKEN  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_identifier = 89,                /* identifier  */
  YYSYMBOL_constant = 90,                  /* constant  */
  YYSYMBOL_semi_colon = 91,                /* semi_colon  */
  YYSYMBOL_rparen = 92,                    /* rparen  */
  YYSYMBOL_rcurly = 93,                    /* rcurly  */
  YYSYMBOL_rsquare = 94,                   /* rsquare  */
  YYSYMBOL_primary_expression = 95,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 96,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 97,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 98,          /* unary_expression  */
  YYSYMBOL_unary_operator = 99,            /* unary_operator  */
  YYSYMBOL_cast_expression = 100,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 101, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 102,      /* additive_expression  */
  YYSYMBOL_shift_expression = 103,         /* shift_expression  */
  YYSYMBOL_relational_expression = 104,    /* relational_expression  */
  YYSYMBOL_equality_expression = 105,      /* equality_expression  */
  YYSYMBOL_and_expression = 106,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 107,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 108,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 109,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 110,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 111,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 112,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 113,      /* assignment_operator  */
  YYSYMBOL_expression = 114,               /* expression  */
  YYSYMBOL_constant_expression = 115,      /* constant_expression  */
  YYSYMBOL_declaration = 116,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 117,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 118,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 119,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 120,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 121,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 122, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 123,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 124,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 125,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 126, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 127,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 128,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 129,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 130,          /* enumerator_list  */
  YYSYMBOL_enumerator = 131,               /* enumerator  */
  YYSYMBOL_type_qualifier = 132,           /* type_qualifier  */
  YYSYMBOL_declarator = 133,               /* declarator  */
  YYSYMBOL_direct_declarator = 134,        /* direct_declarator  */
  YYSYMBOL_pointer = 135,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 136,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 137,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 138,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 139,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 140,          /* identifier_list  */
  YYSYMBOL_type_name = 141,                /* type_name  */
  YYSYMBOL_abstract_declarator = 142,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 143, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 144,              /* initializer  */
  YYSYMBOL_initializer_list = 145,         /* initializer_list  */
  YYSYMBOL_statement = 146,                /* statement  */
  YYSYMBOL_labeled_statement = 147,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 148,       /* compound_statement  */
  YYSYMBOL_declaration_list = 149,         /* declaration_list  */
  YYSYMBOL_statement_list = 150,           /* statement_list  */
  YYSYMBOL_expression_statement = 151,     /* expression_statement  */
  YYSYMBOL_selection_statement = 152,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 153,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 154,           /* jump_statement  */
  YYSYMBOL_translation_unit = 155,         /* translation_unit  */
  YYSYMBOL_external_declaration = 156,     /* external_declaration  */
  YYSYMBOL_function_declaration = 157,     /* function_declaration  */
  YYSYMBOL_function_definition = 158       /* function_definition  */
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
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1352

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  226
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  376

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
       0,   217,   217,   222,   231,   236,   245,   250,   259,   264,
     273,   278,   287,   292,   306,   311,   316,   321,   330,   335,
     340,   347,   355,   362,   370,   376,   385,   391,   400,   405,
     411,   417,   423,   429,   439,   444,   449,   454,   459,   464,
     472,   477,   488,   493,   500,   507,   517,   522,   529,   539,
     544,   551,   561,   566,   573,   580,   587,   597,   602,   609,
     619,   624,   634,   639,   649,   654,   664,   669,   679,   684,
     694,   699,   710,   715,   725,   730,   735,   740,   745,   750,
     755,   760,   765,   770,   775,   784,   789,   799,   806,   812,
     823,   828,   834,   839,   845,   850,   861,   867,   877,   882,
     892,   897,   902,   907,   912,   920,   925,   930,   935,   940,
     945,   950,   955,   960,   965,   970,   975,   983,   992,   998,
    1010,  1015,  1024,  1030,  1041,  1052,  1058,  1063,  1069,  1077,
    1083,  1093,  1098,  1104,  1114,  1121,  1129,  1139,  1145,  1155,
    1160,  1170,  1175,  1183,  1190,  1198,  1203,  1208,  1215,  1221,
    1227,  1233,  1244,  1249,  1255,  1261,  1271,  1276,  1285,  1290,
    1299,  1305,  1314,  1321,  1328,  1337,  1343,  1352,  1357,  1366,
    1371,  1376,  1385,  1390,  1395,  1401,  1407,  1414,  1419,  1424,
    1430,  1439,  1444,  1449,  1458,  1463,  1472,  1477,  1482,  1487,
    1492,  1497,  1502,  1511,  1517,  1524,  1533,  1538,  1544,  1550,
    1560,  1565,  1574,  1580,  1589,  1594,  1602,  1609,  1617,  1627,
    1634,  1641,  1648,  1656,  1665,  1677,  1683,  1688,  1693,  1698,
    1708,  1715,  1731,  1736,  1741,  1749,  1770
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
  "UNTIL", "INVALID_TOKEN", "UNKNOWN_TOKEN", "$accept", "identifier",
  "constant", "semi_colon", "rparen", "rcurly", "rsquare",
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

#define YYPACT_NINF (-188)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-170)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1113,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
     180,  -188,   142,  1113,  1113,  -188,   218,  -188,  1113,   665,
    -188,  -188,  -188,  -188,  -188,   201,   -17,    34,    51,   109,
    -188,  -188,  -188,    32,  -188,    97,    48,   258,  -188,  -188,
     688,     5,  -188,  -188,  -188,   -32,    52,  -188,   201,   134,
    -188,  -188,   109,  -188,    51,  -188,   536,  1184,  -188,  -188,
     916,  1198,    48,   688,   400,  -188,   191,   688,   688,  1254,
    -188,  -188,   201,  -188,    52,  -188,  -188,  -188,  -188,  -188,
    -188,   -10,   451,  -188,  -188,  1296,  1310,  1310,   807,  -188,
    -188,  -188,  -188,  -188,  -188,  1254,    -5,    94,   122,   132,
     621,   148,   201,    56,    56,   402,   159,    41,  -188,  -188,
    -188,  -188,   319,   614,  1254,  -188,   190,    60,   102,   161,
     236,    45,    84,   153,   197,    11,  -188,  -188,    42,  -188,
     142,  -188,  -188,  -188,   536,   536,  -188,  -188,  -188,  -188,
    -188,  1184,  -188,  -188,  -188,   187,  -188,  -188,   550,   134,
     206,  -188,    39,   383,  -188,  -188,  -188,  -188,    25,  -188,
    -188,  -188,  1254,    65,  -188,   176,  -188,   400,  -188,  -188,
    -188,   807,  -188,  1254,  -188,  -188,   110,   170,   134,   194,
     621,  1254,  1254,  1254,  1058,  -188,   179,   736,    56,  -188,
    -188,  -188,    42,  1254,   621,   201,  -188,  -188,  1240,  1254,
     201,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  1254,  -188,  1254,  1254,  1254,  1254,  1254,  1254,
    1254,  1254,  1254,  1254,  1254,  1254,  1254,  1254,  1254,  1254,
    1254,  1254,  1254,  1254,  -188,  -188,  -188,   536,  -188,  -188,
    -188,   121,   826,  1198,  -188,   309,  -188,   149,  -188,   965,
     201,  -188,  -188,  -188,  -188,   191,  -188,  1254,  -188,   134,
    -188,   897,   245,  -188,  1254,   621,  -188,   110,   110,   110,
     240,   402,   402,  -188,  -188,   110,  -188,  -188,  1110,  -188,
     120,  -188,   129,  -188,  -188,  -188,  -188,  -188,   190,   190,
      60,    60,   102,   102,   102,   102,   161,   161,   236,    45,
      84,   153,   197,    22,  -188,  -188,   900,  -188,  -188,   134,
     134,  -188,    25,   149,   987,  1198,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,   621,   621,   621,  1254,  1254,  1240,
     621,  1254,  -188,  -188,  1254,   225,  -188,  -188,  -188,  -188,
    -188,  -188,   134,  -188,    25,   203,  -188,  -188,   110,   110,
     621,   110,  -188,  -188,  -188,  -188,  -188,   621,    56,   621,
    -188,   621,  -188,  -188,  -188,  -188
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   116,   100,   101,   102,   103,   104,   106,   107,   108,
     109,   112,   113,   110,   111,   141,   142,   105,   120,   121,
       0,   223,     0,    90,    92,   114,     0,   115,    94,     0,
     220,   224,   222,     3,     2,     0,   136,     7,     0,   152,
       6,   145,    88,     0,    96,     0,   144,     0,    91,    93,
       0,   119,    95,     1,   221,   139,     0,   137,     0,     0,
     156,   154,   153,     7,     0,    89,     0,     0,   225,   226,
       0,     0,   143,   126,     0,   122,     0,   128,     0,     0,
      11,    10,     0,   134,     0,     9,     8,   146,   157,   155,
      97,    98,     3,     4,    16,     0,     0,     0,     0,    34,
      35,    36,    37,    38,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,   204,
     196,    18,    28,    40,     0,    42,    46,    49,    52,    57,
      60,    62,    64,    66,    68,    70,    72,    85,     0,   192,
       0,   202,   186,   187,     0,     0,   188,   189,   190,   191,
       3,     0,    14,   181,    99,     3,   165,   151,     0,     0,
     158,   160,     0,     3,    12,   148,    40,    87,     0,   125,
     118,   123,     0,     0,   129,   131,   127,     0,   140,   138,
     135,     0,    32,     0,    29,    30,     0,   167,     0,     0,
       0,     0,     0,     0,     7,   192,     0,     0,     0,   216,
     217,   218,     0,     0,     0,     0,    24,    25,     0,     0,
       0,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    74,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,   198,   192,     0,   197,   203,
     184,     0,     0,     0,   162,     0,   163,   170,   149,     0,
       0,   150,    13,   147,   132,     0,   124,     0,   117,     0,
      17,     0,   169,   168,     0,     0,   195,     0,     0,     0,
       0,     0,     0,   215,   219,     0,   193,    23,     9,    20,
       0,    26,     0,    22,    73,    43,    44,    45,    47,    48,
      50,    51,    55,    56,    53,    54,    58,    59,    61,    63,
      65,    67,    69,     0,    86,   199,     0,   182,   177,     0,
       0,   173,     0,   171,     0,     0,   159,   161,   166,   130,
     133,    33,    41,   194,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    19,     0,     3,   183,   185,   178,   172,
     174,   179,     0,   175,     0,   206,   208,   209,     0,     0,
       0,     0,   210,    27,    71,   180,   176,     0,     0,     0,
     212,     0,   207,   211,   214,   213
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,   -20,  -188,   -11,   -54,   -35,  -156,  -188,  -188,  -188,
     151,  -188,  -107,    36,    54,    62,    53,    63,    59,    64,
      61,    58,  -188,   -58,   -64,  -188,    99,   -57,     8,     1,
    -188,   242,  -188,   322,  -188,  -188,   231,   -51,   -22,  -188,
      46,  -188,   255,   235,   296,    -3,   -38,     2,  -188,   -66,
    -188,    70,  -188,   137,   -19,  -176,  -144,  -188,    -4,  -188,
     274,  -188,   177,  -187,  -188,  -188,  -188,  -188,   293,  -188,
    -188
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   152,   118,   119,   318,    83,   165,   121,   122,   290,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   222,   138,   168,   195,   140,
      43,    44,    23,    24,    25,    26,    74,    75,    76,   173,
     174,    27,    56,    57,    28,    59,    46,    47,    62,   319,
     160,   161,   162,   188,   320,   257,   154,   251,   141,   142,
     143,   144,   145,   146,   147,   148,   149,    29,    30,    31,
      32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    22,    41,   153,   159,    87,    51,   250,    21,    72,
     282,    42,   263,   167,    58,    55,   157,   223,    41,    45,
      79,   167,   178,   171,    48,    49,   262,    41,   241,    52,
      22,   120,    65,    63,    68,    -3,    78,    21,    55,   170,
      85,    61,    67,    63,    41,   190,   117,   167,   189,   180,
     156,   169,    33,    80,    34,   176,    41,    63,   243,   164,
     242,    91,    55,    -3,    89,    -3,    63,    -3,    64,    86,
      -3,   158,   344,   175,   139,   260,   187,    70,   243,   323,
      38,    71,   237,    40,    81,    -3,    -3,   153,    82,    39,
     117,   204,   198,    40,   338,   339,   323,   321,    63,   227,
     228,   265,   199,   200,   201,   258,   196,    40,   261,   245,
     248,    85,   229,   230,   167,   264,    40,   295,   296,   297,
      41,    85,    80,   191,   117,   117,   171,   244,    66,    42,
     262,   238,   270,   -98,   274,    85,   343,    91,    41,   256,
      86,   249,   268,    37,   291,    34,   243,    39,    40,    67,
      86,   192,   246,    81,   289,   254,   341,   316,   294,   187,
     255,   193,   266,   164,    86,   243,   350,   332,   273,   353,
     117,    38,   347,   231,   232,    15,    16,   197,   324,   314,
      39,    33,   325,    34,   117,   287,   276,   283,   203,   272,
     293,   284,    33,    40,    34,   167,   322,   186,   366,   271,
     286,   239,    33,   253,    34,   281,   233,   234,    39,   167,
     330,    35,   315,   240,   202,   331,   317,    72,    -9,    33,
      38,    34,   166,   334,   335,   336,   267,   117,   224,    39,
     166,   340,    41,   225,   226,    41,   342,    -9,    -9,    -9,
     328,   172,   259,   249,   275,    41,   182,   184,   185,    50,
     235,   236,   153,   158,   255,   117,   166,   280,   352,    33,
     158,    34,   175,   298,   299,   348,   349,   167,   354,   337,
     351,   333,   158,   272,   271,   166,   -11,   363,   253,   367,
     186,   346,   186,   300,   301,   360,   364,    38,   306,   307,
     277,   278,   279,   302,   303,   304,   305,   309,   365,   312,
     308,   311,   285,   310,   368,   369,    90,   371,   292,   177,
      33,   329,    34,    84,   117,   117,   117,   179,   269,    69,
     117,   247,    54,   166,     0,   158,   205,   206,   207,   327,
     355,   356,   357,     0,     0,    60,   362,     0,   252,  -169,
     117,   313,   253,     0,     0,  -169,    77,   117,   208,   117,
       0,   117,   209,     0,   210,     0,   370,   373,    88,     0,
       0,     0,     0,   372,     0,   374,     0,   375,     0,    77,
      77,     0,    73,    77,    77,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,     0,    77,    73,    73,     0,     0,    73,
      73,    80,     0,   194,   166,    34,    93,    94,    95,     0,
      96,    97,     0,   -13,   -13,     0,     0,     0,   166,   -13,
      73,     0,     0,     0,     0,   166,     0,     0,     1,     0,
       0,    98,    81,   -13,   -13,   -13,   358,   359,   361,    99,
     100,   101,   102,   103,   104,     0,     0,     0,     0,     0,
       0,   -11,     0,    40,    -7,    -7,    -7,    -7,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,    77,     0,     0,   166,    77,     0,    -7,
       0,     0,    -7,    -7,     0,     0,     0,     0,     0,     0,
       0,     0,    -7,    -7,     0,   166,     0,     0,     0,    73,
       0,     0,     0,    73,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,     0,    -7,    -7,    -7,   -11,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    92,     0,    34,
      93,    94,    95,     0,    96,    97,     0,     0,     0,     0,
       0,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    98,     0,    66,    81,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104,   252,
    -164,     0,     0,   253,     0,     0,  -164,    40,    39,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     0,   105,
     106,   107,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   194,     0,    34,    93,    94,    95,     0,    96,
      97,     0,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,     0,     0,     0,     0,     0,     0,     0,     1,
      98,     0,    66,     0,     0,     0,     0,     0,    99,   100,
     101,   102,   103,   104,     0,    53,   221,     0,     0,     0,
       0,     0,    40,     0,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     1,   105,   106,   107,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,   194,     0,    34,
      93,    94,    95,     0,    96,    97,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,     1,    98,     0,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,    40,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,   150,     0,
      34,    93,    94,    95,     0,    96,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   155,     0,    34,
       0,     0,     0,     0,     0,     1,    98,     0,     0,     0,
       0,     0,     0,     0,    99,   100,   101,   102,   103,   104,
       0,     0,     0,     0,     1,   252,    86,     0,     0,   253,
       0,     0,     0,     0,    39,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    85,     0,
       0,   345,     0,    34,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,     0,     0,   155,     0,    34,
       0,     0,     0,     0,     0,     1,   271,    86,     0,    98,
     253,   151,    81,     0,     0,    39,     0,    99,   100,   101,
     102,   103,   104,     0,     1,     0,    86,     0,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    85,     0,
       0,     0,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,    86,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,   326,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    -3,
       0,     0,     0,     0,     0,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,     0,    -3,     0,     0,
       0,    -3,     0,    -3,    -3,    -3,    -3,    -3,    -3,     0,
       0,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,     0,     0,     0,     0,     0,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,     0,    -3,
      -3,     1,     0,    -3,     0,    -3,    -3,    -3,    -3,    -3,
      -3,     0,     0,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
       0,     0,    -3,     0,     0,     0,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,   150,     0,    34,    93,    94,
      95,     0,    96,    97,     0,     0,     0,     0,     0,   163,
       0,    34,    93,    94,    95,     0,    96,    97,     0,     0,
       0,     0,     0,    98,     0,   151,     0,     0,     0,     0,
       0,    99,   100,   101,   102,   103,   104,    98,     0,     0,
       0,     0,   164,     0,     0,    99,   100,   101,   102,   103,
     104,   288,     0,    34,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,   150,     0,    34,    93,    94,
      95,     0,    96,    97,     0,     0,     0,     0,     0,    98,
      86,     0,     0,     0,     0,     0,     0,    99,   100,   101,
     102,   103,   104,    98,     0,     0,     0,     0,     0,     0,
       0,    99,   100,   101,   102,   103,   104,   150,     0,    34,
      93,    94,    95,     0,    96,    97,     0,     0,     0,     0,
       0,   150,     0,    34,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,   181,     0,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104,   183,
       0,     0,     0,     0,     0,     0,     0,    99,   100,   101,
     102,   103,   104
};

static const yytype_int16 yycheck[] =
{
      20,     0,    22,    67,    70,    59,    26,   151,     0,    47,
     197,    22,   168,    71,    31,    35,    70,   124,    38,    22,
      52,    79,    79,    74,    23,    24,     1,    47,    17,    28,
      29,    66,    43,     1,    45,     1,    31,    29,    58,    74,
       1,    39,    52,     1,    64,    50,    66,   105,   105,    84,
      70,    73,     1,     1,     3,    77,    76,     1,    36,    34,
      49,    64,    82,    29,    62,    31,     1,    33,    36,    30,
      36,    70,    50,    76,    66,    36,    98,    29,    36,   255,
      29,    33,    37,    51,    32,    51,    52,   151,    36,    38,
     110,    50,   112,    51,   281,   282,   272,   253,     1,    39,
      40,    36,   113,   114,   115,   159,   110,    51,   162,   144,
     145,     1,    10,    11,   172,   172,    51,   224,   225,   226,
     140,     1,     1,    29,   144,   145,   177,   138,    31,   140,
       1,    47,   186,    36,   188,     1,   292,   140,   158,   158,
      30,   145,   177,     1,   208,     3,    36,    38,    51,    52,
      30,    29,   144,    32,   208,   158,    36,    36,   222,   181,
     158,    29,   173,    34,    30,    36,   322,   274,   187,   325,
     190,    29,   316,    12,    13,    66,    67,    29,    29,   243,
      38,     1,    33,     3,   204,   205,   190,   198,    29,   187,
     210,   202,     1,    51,     3,   253,   253,    98,   354,    29,
     204,    48,     1,    33,     3,   197,    45,    46,    38,   267,
     267,    31,   247,    16,   115,   269,   251,   255,    31,     1,
      29,     3,    71,   277,   278,   279,    50,   247,    38,    38,
      79,   285,   252,    43,    44,   255,   290,    50,    51,    52,
     260,    50,    36,   247,    50,   265,    95,    96,    97,    31,
      14,    15,   316,   252,   252,   275,   105,    78,   324,     1,
     259,     3,   265,   227,   228,   319,   320,   325,   325,    29,
     324,   275,   271,   271,    29,   124,    51,   341,    33,    76,
     181,   316,   183,   229,   230,   339,   344,    29,   235,   236,
     191,   192,   193,   231,   232,   233,   234,   238,   352,   241,
     237,   240,   203,   239,   358,   359,    64,   361,   209,    78,
       1,   265,     3,    58,   334,   335,   336,    82,   181,    45,
     340,   144,    29,   172,    -1,   324,     7,     8,     9,   259,
     334,   335,   336,    -1,    -1,    39,   340,    -1,    29,    30,
     360,   242,    33,    -1,    -1,    36,    50,   367,    29,   369,
      -1,   371,    33,    -1,    35,    -1,   360,   368,    62,    -1,
      -1,    -1,    -1,   367,    -1,   369,    -1,   371,    -1,    73,
      74,    -1,    50,    77,    78,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,    -1,    98,    73,    74,    -1,    -1,    77,
      78,     1,    -1,     1,   253,     3,     4,     5,     6,    -1,
       8,     9,    -1,    30,    31,    -1,    -1,    -1,   267,    36,
      98,    -1,    -1,    -1,    -1,   274,    -1,    -1,    28,    -1,
      -1,    29,    32,    50,    51,    52,   337,   338,   339,    37,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,     0,    -1,    51,     3,     4,     5,     6,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    -1,   177,    -1,    -1,   325,   181,    -1,    28,
      -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,   344,    -1,    -1,    -1,   177,
      -1,    -1,    -1,   181,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    31,    32,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    29,
      30,    -1,    -1,    33,    -1,    -1,    36,    51,    38,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    -1,    73,
      74,    75,    -1,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    -1,     0,    52,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    28,    73,    74,    75,    -1,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    -1,    29,
      33,    31,    32,    -1,    -1,    38,    -1,    37,    38,    39,
      40,    41,    42,    -1,    28,    -1,    30,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,     1,
      -1,    -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    29,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     1,    -1,    -1,    -1,    -1,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    29,
      30,    28,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    52,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    29,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    37,    38,    39,    40,    41,
      42,     1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,   116,   117,   120,   121,   122,   123,   129,   132,   155,
     156,   157,   158,     1,     3,    31,    89,     1,    29,    38,
      51,    89,    91,   118,   119,   133,   134,   135,   117,   117,
      31,    89,   117,     0,   156,    89,   130,   131,    31,   133,
     132,   135,   136,     1,    36,    91,    31,    52,    91,   148,
      29,    33,   134,   121,   124,   125,   126,   132,    31,    52,
       1,    32,    36,    93,   130,     1,    30,    92,   132,   135,
     119,   133,     1,     4,     5,     6,     8,     9,    29,    37,
      38,    39,    40,    41,    42,    73,    74,    75,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    89,    90,    91,
      93,    95,    96,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   114,   116,
     117,   146,   147,   148,   149,   150,   151,   152,   153,   154,
       1,    31,    89,   112,   144,     1,    89,    92,   117,   137,
     138,   139,   140,     1,    34,    94,    98,   111,   115,   126,
      93,   125,    50,   127,   128,   133,   126,   124,   115,   131,
      93,    29,    98,    29,    98,    98,   114,   126,   141,   115,
      50,    29,    29,    29,     1,   116,   146,    29,    89,    91,
      91,    91,   114,    29,    50,     7,     8,     9,    29,    33,
      35,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    52,   113,   100,    38,    43,    44,    39,    40,    10,
      11,    12,    13,    45,    46,    14,    15,    37,    47,    48,
      16,    17,    49,    36,    91,    93,   116,   150,    93,   146,
     144,   145,    29,    33,   133,   135,   142,   143,    92,    36,
      36,    92,     1,    94,   115,    36,    91,    50,    93,   141,
      92,    29,   135,   142,    92,    50,   146,   114,   114,   114,
      78,   116,   151,    91,    91,   114,   146,    89,     1,    92,
      97,   112,   114,    89,   112,   100,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   104,   104,   105,   106,
     107,   108,   109,   114,   112,    93,    36,    93,    92,   137,
     142,    94,   115,   143,    29,    33,    72,   139,    89,   128,
     115,    92,   100,   146,    92,    92,    92,    29,   151,   151,
      92,    36,    92,    94,    50,     1,    93,   144,    92,    92,
      94,    92,   137,    94,   115,   146,   146,   146,   114,   114,
      92,   114,   146,   112,   111,    92,    94,    76,    92,    92,
     146,    92,   146,    91,   146,   146
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      93,    93,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    98,    99,    99,    99,    99,    99,    99,
     100,   100,   101,   101,   101,   101,   102,   102,   102,   103,
     103,   103,   104,   104,   104,   104,   104,   105,   105,   105,
     106,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   115,   116,   116,
     117,   117,   117,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   120,   120,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   122,
     123,   123,   124,   124,   125,   126,   126,   126,   126,   127,
     127,   128,   128,   128,   129,   129,   129,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   139,   139,   140,   140,   141,   141,   142,
     142,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   144,   144,   144,   145,   145,   146,   146,   146,   146,
     146,   146,   146,   147,   147,   147,   148,   148,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   152,   152,   153,
     153,   153,   153,   153,   153,   154,   154,   154,   154,   154,
     155,   155,   156,   156,   156,   157,   158
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     4,
       3,     4,     3,     3,     2,     2,     1,     3,     1,     2,
       2,     2,     2,     4,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     3,
       1,     2,     1,     2,     1,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     4,     2,
       1,     1,     1,     2,     3,     2,     1,     2,     1,     1,
       3,     1,     2,     3,     4,     5,     2,     1,     3,     1,
       3,     1,     1,     2,     1,     1,     3,     4,     3,     4,
       4,     3,     1,     2,     2,     3,     1,     2,     1,     3,
       1,     3,     2,     2,     1,     1,     3,     1,     2,     1,
       1,     2,     3,     2,     3,     3,     4,     2,     3,     3,
       4,     1,     3,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     2,     3,     3,     4,
       1,     2,     1,     2,     1,     2,     5,     7,     5,     5,
       5,     7,     6,     7,     7,     3,     2,     2,     2,     3,
       1,     2,     1,     1,     1,     3,     3
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
  case 2: /* identifier: IDENTIFIER  */
#line 218 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1829 "parser.tab.c"
    break;

  case 3: /* identifier: error  */
#line 223 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "Identifier");
            ourError("Expected an ID or Expression");
        }
#line 1839 "parser.tab.c"
    break;

  case 4: /* constant: CONSTANT  */
#line 232 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1848 "parser.tab.c"
    break;

  case 5: /* constant: error  */
#line 237 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "Constant");
            ourError("Expected a Constant or Expression");
        }
#line 1858 "parser.tab.c"
    break;

  case 6: /* semi_colon: SEMI_COLON  */
#line 246 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1867 "parser.tab.c"
    break;

  case 7: /* semi_colon: error  */
#line 251 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "SemiColon");
            ourError("Expected a SemiColon");
        }
#line 1877 "parser.tab.c"
    break;

  case 8: /* rparen: RPAREN  */
#line 260 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1886 "parser.tab.c"
    break;

  case 9: /* rparen: error  */
#line 265 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "RParen");
            ourError("Expected a Right Parenthesis");
        }
#line 1896 "parser.tab.c"
    break;

  case 10: /* rcurly: RCURLY  */
#line 274 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1905 "parser.tab.c"
    break;

  case 11: /* rcurly: error  */
#line 279 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "RCurly");
            ourError("Expected a Right Curly Brace");
        }
#line 1915 "parser.tab.c"
    break;

  case 12: /* rsquare: RSQUARE  */
#line 288 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1924 "parser.tab.c"
    break;

  case 13: /* rsquare: error  */
#line 293 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "RSquare");
            ourError("Expected a Right Square Bracket");
        }
#line 1934 "parser.tab.c"
    break;

  case 14: /* primary_expression: identifier  */
#line 307 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].astNode));
        }
#line 1943 "parser.tab.c"
    break;

  case 15: /* primary_expression: constant  */
#line 312 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].astNode));
        }
#line 1952 "parser.tab.c"
    break;

  case 16: /* primary_expression: STRING_LITERAL  */
#line 317 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1961 "parser.tab.c"
    break;

  case 17: /* primary_expression: LPAREN expression rparen  */
#line 322 "parser.y"
        {   
            // Parenthesis are not part of the AST
            LINE
            (yyval.astNode) = (yyvsp[-1].astNode);
        }
#line 1971 "parser.tab.c"
    break;

  case 18: /* postfix_expression: primary_expression  */
#line 331 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 1980 "parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression LSQUARE expression rsquare  */
#line 336 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("ArrayAccess");
    }
#line 1989 "parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression LPAREN rparen  */
#line 341 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Call");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        PARSER_TABLE.push_back({(yyvsp[-2].astNode)->position, {(yyvsp[-2].astNode)->value, "function call"}});
    }
#line 2000 "parser.tab.c"
    break;

  case 21: /* postfix_expression: postfix_expression LPAREN argument_expression_list rparen  */
#line 348 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Call");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        PARSER_TABLE.push_back({(yyvsp[-3].astNode)->position, {(yyvsp[-3].astNode)->value, "function call"}});
    }
#line 2012 "parser.tab.c"
    break;

  case 22: /* postfix_expression: postfix_expression DOT identifier  */
#line 356 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Member Access");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2023 "parser.tab.c"
    break;

  case 23: /* postfix_expression: postfix_expression PTR_OP identifier  */
#line 363 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Pointer Member Access");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        // $$->addChild(new ASTNode($3->position, "Identifier", $3->value));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2035 "parser.tab.c"
    break;

  case 24: /* postfix_expression: postfix_expression INC_OP  */
#line 371 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PostIncrement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2045 "parser.tab.c"
    break;

  case 25: /* postfix_expression: postfix_expression DEC_OP  */
#line 377 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PostDecrement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2055 "parser.tab.c"
    break;

  case 26: /* argument_expression_list: assignment_expression  */
#line 386 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Argument List");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2065 "parser.tab.c"
    break;

  case 27: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 392 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2075 "parser.tab.c"
    break;

  case 28: /* unary_expression: postfix_expression  */
#line 401 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2084 "parser.tab.c"
    break;

  case 29: /* unary_expression: INC_OP unary_expression  */
#line 406 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PreIncrement");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2094 "parser.tab.c"
    break;

  case 30: /* unary_expression: DEC_OP unary_expression  */
#line 412 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PreDecrement");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2104 "parser.tab.c"
    break;

  case 31: /* unary_expression: unary_operator cast_expression  */
#line 418 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("UnaryOperation",(yyvsp[-1].astNode)->value,(yyvsp[-1].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2114 "parser.tab.c"
    break;

  case 32: /* unary_expression: SIZEOF unary_expression  */
#line 424 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("SizeofExpr");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2124 "parser.tab.c"
    break;

  case 33: /* unary_expression: SIZEOF LPAREN type_name rparen  */
#line 430 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("SizeofType");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2134 "parser.tab.c"
    break;

  case 34: /* unary_operator: BIT_AND  */
#line 440 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2143 "parser.tab.c"
    break;

  case 35: /* unary_operator: STAR  */
#line 445 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2152 "parser.tab.c"
    break;

  case 36: /* unary_operator: PLUS  */
#line 450 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2161 "parser.tab.c"
    break;

  case 37: /* unary_operator: MINUS  */
#line 455 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2170 "parser.tab.c"
    break;

  case 38: /* unary_operator: BIT_NOT  */
#line 460 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2179 "parser.tab.c"
    break;

  case 39: /* unary_operator: NOT_OP  */
#line 465 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2188 "parser.tab.c"
    break;

  case 40: /* cast_expression: unary_expression  */
#line 473 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2197 "parser.tab.c"
    break;

  case 41: /* cast_expression: LPAREN type_name rparen cast_expression  */
#line 478 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("TypeCast");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2208 "parser.tab.c"
    break;

  case 42: /* multiplicative_expression: cast_expression  */
#line 489 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2217 "parser.tab.c"
    break;

  case 43: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 494 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Multiplication", "*", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2228 "parser.tab.c"
    break;

  case 44: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 501 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Division", "/", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2239 "parser.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 508 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Modulus", "%", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2250 "parser.tab.c"
    break;

  case 46: /* additive_expression: multiplicative_expression  */
#line 518 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2259 "parser.tab.c"
    break;

  case 47: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 523 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Addition", "+", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2270 "parser.tab.c"
    break;

  case 48: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 530 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Subtraction", "-", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2281 "parser.tab.c"
    break;

  case 49: /* shift_expression: additive_expression  */
#line 540 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2290 "parser.tab.c"
    break;

  case 50: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 545 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LeftShift", "<<", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2301 "parser.tab.c"
    break;

  case 51: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 552 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("RightShift", ">>", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2312 "parser.tab.c"
    break;

  case 52: /* relational_expression: shift_expression  */
#line 562 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2321 "parser.tab.c"
    break;

  case 53: /* relational_expression: relational_expression LESSER_OP shift_expression  */
#line 567 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Lesser", "<", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2332 "parser.tab.c"
    break;

  case 54: /* relational_expression: relational_expression GREATER_OP shift_expression  */
#line 574 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Greater", ">", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2343 "parser.tab.c"
    break;

  case 55: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 581 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LesserEqual", "<=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2354 "parser.tab.c"
    break;

  case 56: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 588 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("GreaterEqual", ">=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2365 "parser.tab.c"
    break;

  case 57: /* equality_expression: relational_expression  */
#line 598 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2374 "parser.tab.c"
    break;

  case 58: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 603 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Equal", "==", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2385 "parser.tab.c"
    break;

  case 59: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 610 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("NotEqual", "!=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2396 "parser.tab.c"
    break;

  case 60: /* and_expression: equality_expression  */
#line 620 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2405 "parser.tab.c"
    break;

  case 61: /* and_expression: and_expression BIT_AND equality_expression  */
#line 625 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("BitwiseAnd", "&", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2416 "parser.tab.c"
    break;

  case 62: /* exclusive_or_expression: and_expression  */
#line 635 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2425 "parser.tab.c"
    break;

  case 63: /* exclusive_or_expression: exclusive_or_expression XOR and_expression  */
#line 640 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("BitwiseXor", "^", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2436 "parser.tab.c"
    break;

  case 64: /* inclusive_or_expression: exclusive_or_expression  */
#line 650 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2445 "parser.tab.c"
    break;

  case 65: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 655 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("BitwiseOr", "|", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2456 "parser.tab.c"
    break;

  case 66: /* logical_and_expression: inclusive_or_expression  */
#line 665 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2465 "parser.tab.c"
    break;

  case 67: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 670 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LogicalAnd", "&&", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2476 "parser.tab.c"
    break;

  case 68: /* logical_or_expression: logical_and_expression  */
#line 680 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2485 "parser.tab.c"
    break;

  case 69: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 685 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LogicalOr", "||", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2496 "parser.tab.c"
    break;

  case 70: /* conditional_expression: logical_or_expression  */
#line 695 "parser.y"
    { 
        LINE  
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2505 "parser.tab.c"
    break;

  case 71: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 700 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Conditional_Expression"); 
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2517 "parser.tab.c"
    break;

  case 72: /* assignment_expression: conditional_expression  */
#line 711 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2526 "parser.tab.c"
    break;

  case 73: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 716 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("AssignmentExpression", (yyvsp[-1].astNode)->value, (yyvsp[-1].astNode)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2537 "parser.tab.c"
    break;

  case 74: /* assignment_operator: ASSIGN  */
#line 726 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2546 "parser.tab.c"
    break;

  case 75: /* assignment_operator: MUL_ASSIGN  */
#line 731 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2555 "parser.tab.c"
    break;

  case 76: /* assignment_operator: DIV_ASSIGN  */
#line 736 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2564 "parser.tab.c"
    break;

  case 77: /* assignment_operator: MOD_ASSIGN  */
#line 741 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2573 "parser.tab.c"
    break;

  case 78: /* assignment_operator: ADD_ASSIGN  */
#line 746 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2582 "parser.tab.c"
    break;

  case 79: /* assignment_operator: SUB_ASSIGN  */
#line 751 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2591 "parser.tab.c"
    break;

  case 80: /* assignment_operator: LEFT_ASSIGN  */
#line 756 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2600 "parser.tab.c"
    break;

  case 81: /* assignment_operator: RIGHT_ASSIGN  */
#line 761 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2609 "parser.tab.c"
    break;

  case 82: /* assignment_operator: AND_ASSIGN  */
#line 766 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2618 "parser.tab.c"
    break;

  case 83: /* assignment_operator: XOR_ASSIGN  */
#line 771 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2627 "parser.tab.c"
    break;

  case 84: /* assignment_operator: OR_ASSIGN  */
#line 776 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2636 "parser.tab.c"
    break;

  case 85: /* expression: assignment_expression  */
#line 785 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2645 "parser.tab.c"
    break;

  case 86: /* expression: expression COMMA assignment_expression  */
#line 790 "parser.y"
    { 
    LINE
        (yyval.astNode) = new ASTNode("Expression"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2656 "parser.tab.c"
    break;

  case 87: /* constant_expression: conditional_expression  */
#line 799 "parser.y"
                             {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2665 "parser.tab.c"
    break;

  case 88: /* declaration: declaration_specifiers semi_colon  */
#line 807 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Declaration"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 2675 "parser.tab.c"
    break;

  case 89: /* declaration: declaration_specifiers init_declarator_list semi_colon  */
#line 813 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Declaration"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Declaration_Handler((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 2687 "parser.tab.c"
    break;

  case 90: /* declaration_specifiers: storage_class_specifier  */
#line 824 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2696 "parser.tab.c"
    break;

  case 91: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 829 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2706 "parser.tab.c"
    break;

  case 92: /* declaration_specifiers: type_specifier  */
#line 835 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2715 "parser.tab.c"
    break;

  case 93: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 840 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2725 "parser.tab.c"
    break;

  case 94: /* declaration_specifiers: type_qualifier  */
#line 846 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2734 "parser.tab.c"
    break;

  case 95: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 851 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2744 "parser.tab.c"
    break;

  case 96: /* init_declarator_list: init_declarator  */
#line 862 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Initialization or Declaration List", EMPTY_VAL, (yyvsp[0].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2754 "parser.tab.c"
    break;

  case 97: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 868 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2764 "parser.tab.c"
    break;

  case 98: /* init_declarator: declarator  */
#line 878 "parser.y"
    {
        LINE  
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 2773 "parser.tab.c"
    break;

  case 99: /* init_declarator: declarator ASSIGN initializer  */
#line 883 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Initializer", "=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2784 "parser.tab.c"
    break;

  case 100: /* storage_class_specifier: TYPEDEF  */
#line 893 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "typedef", (yyvsp[0].tokenAtr)->position);
    }
#line 2793 "parser.tab.c"
    break;

  case 101: /* storage_class_specifier: EXTERN  */
#line 898 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "extern", (yyvsp[0].tokenAtr)->position);
    }
#line 2802 "parser.tab.c"
    break;

  case 102: /* storage_class_specifier: STATIC  */
#line 903 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "static", (yyvsp[0].tokenAtr)->position);
    }
#line 2811 "parser.tab.c"
    break;

  case 103: /* storage_class_specifier: AUTO  */
#line 908 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "auto", (yyvsp[0].tokenAtr)->position);
    }
#line 2820 "parser.tab.c"
    break;

  case 104: /* storage_class_specifier: REGISTER  */
#line 913 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "register", (yyvsp[0].tokenAtr)->position);
    }
#line 2829 "parser.tab.c"
    break;

  case 105: /* type_specifier: VOID  */
#line 921 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "void", (yyvsp[0].tokenAtr)->position);
    }
#line 2838 "parser.tab.c"
    break;

  case 106: /* type_specifier: CHAR  */
#line 926 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "char", (yyvsp[0].tokenAtr)->position);
    }
#line 2847 "parser.tab.c"
    break;

  case 107: /* type_specifier: SHORT  */
#line 931 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "short", (yyvsp[0].tokenAtr)->position);
    }
#line 2856 "parser.tab.c"
    break;

  case 108: /* type_specifier: INT  */
#line 936 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "int", (yyvsp[0].tokenAtr)->position);
    }
#line 2865 "parser.tab.c"
    break;

  case 109: /* type_specifier: LONG  */
#line 941 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "long", (yyvsp[0].tokenAtr)->position);
    }
#line 2874 "parser.tab.c"
    break;

  case 110: /* type_specifier: FLOAT  */
#line 946 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "float", (yyvsp[0].tokenAtr)->position);
    }
#line 2883 "parser.tab.c"
    break;

  case 111: /* type_specifier: DOUBLE  */
#line 951 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "double", (yyvsp[0].tokenAtr)->position);
    }
#line 2892 "parser.tab.c"
    break;

  case 112: /* type_specifier: SIGNED  */
#line 956 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "signed", (yyvsp[0].tokenAtr)->position);
    }
#line 2901 "parser.tab.c"
    break;

  case 113: /* type_specifier: UNSIGNED  */
#line 961 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "unsigned", (yyvsp[0].tokenAtr)->position);
    }
#line 2910 "parser.tab.c"
    break;

  case 114: /* type_specifier: struct_or_union_specifier  */
#line 966 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2919 "parser.tab.c"
    break;

  case 115: /* type_specifier: enum_specifier  */
#line 971 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2928 "parser.tab.c"
    break;

  case 116: /* type_specifier: TYPE_NAME  */
#line 976 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "TypeName", (yyvsp[0].tokenAtr)->position);
    }
#line 2937 "parser.tab.c"
    break;

  case 117: /* struct_or_union_specifier: struct_or_union identifier LCURLY struct_declaration_list rcurly  */
#line 984 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-4].astNode);
        std::string isStruct = (yyvsp[-4].astNode)->value == "struct" ? "structID" : "unionID";
        (yyval.astNode)->addChild(isStruct, (yyvsp[-3].astNode)->value,(yyvsp[-3].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        PARSER_TABLE.push_back({(yyvsp[-3].astNode)->position, {(yyvsp[-3].astNode)->value, (yyvsp[-4].astNode)->value}});
    }
#line 2950 "parser.tab.c"
    break;

  case 118: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list rcurly  */
#line 993 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
    }
#line 2960 "parser.tab.c"
    break;

  case 119: /* struct_or_union_specifier: struct_or_union identifier  */
#line 999 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        std::string isStruct = (yyvsp[-1].astNode)->value == "struct" ? "structID" : "unionID";
        (yyval.astNode)->addChild(isStruct, (yyvsp[0].astNode)->value,(yyvsp[0].astNode)->position);
        PARSER_TABLE.push_back({(yyvsp[0].astNode)->position, {(yyvsp[0].astNode)->value, (yyvsp[-1].astNode)->value}});
    }
#line 2972 "parser.tab.c"
    break;

  case 120: /* struct_or_union: STRUCT  */
#line 1011 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct", "struct", (yyvsp[0].tokenAtr)->position);
    }
#line 2981 "parser.tab.c"
    break;

  case 121: /* struct_or_union: UNION  */
#line 1016 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Union", "union", (yyvsp[0].tokenAtr)->position);
    }
#line 2990 "parser.tab.c"
    break;

  case 122: /* struct_declaration_list: struct_declaration  */
#line 1025 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declaration List");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3000 "parser.tab.c"
    break;

  case 123: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1031 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declaration List");
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3011 "parser.tab.c"
    break;

  case 124: /* struct_declaration: specifier_qualifier_list struct_declarator_list semi_colon  */
#line 1042 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Struct_Union_Declaration_Handler((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 3023 "parser.tab.c"
    break;

  case 125: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1053 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3033 "parser.tab.c"
    break;

  case 126: /* specifier_qualifier_list: type_specifier  */
#line 1059 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3042 "parser.tab.c"
    break;

  case 127: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1064 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3052 "parser.tab.c"
    break;

  case 128: /* specifier_qualifier_list: type_qualifier  */
#line 1070 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3061 "parser.tab.c"
    break;

  case 129: /* struct_declarator_list: struct_declarator  */
#line 1078 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator List");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3071 "parser.tab.c"
    break;

  case 130: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1084 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator List");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3082 "parser.tab.c"
    break;

  case 131: /* struct_declarator: declarator  */
#line 1094 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3091 "parser.tab.c"
    break;

  case 132: /* struct_declarator: COLON constant_expression  */
#line 1099 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator", ":", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3101 "parser.tab.c"
    break;

  case 133: /* struct_declarator: declarator COLON constant_expression  */
#line 1105 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator", ":", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3112 "parser.tab.c"
    break;

  case 134: /* enum_specifier: ENUM LCURLY enumerator_list rcurly  */
#line 1115 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Specifier", EMPTY_VAL, (yyvsp[-3].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3123 "parser.tab.c"
    break;

  case 135: /* enum_specifier: ENUM identifier LCURLY enumerator_list rcurly  */
#line 1122 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Specifier", EMPTY_VAL, (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild("enumID", (yyvsp[-3].astNode)->value,(yyvsp[-3].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3135 "parser.tab.c"
    break;

  case 136: /* enum_specifier: ENUM identifier  */
#line 1130 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Specifier", EMPTY_VAL); 
        (yyval.astNode)->addChild("enumID", (yyvsp[0].astNode)->value,(yyvsp[0].astNode)->position);
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3146 "parser.tab.c"
    break;

  case 137: /* enumerator_list: enumerator  */
#line 1140 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Enum List");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3156 "parser.tab.c"
    break;

  case 138: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 1146 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Enum List");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3167 "parser.tab.c"
    break;

  case 139: /* enumerator: identifier  */
#line 1156 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Element", (yyvsp[0].astNode)->value, (yyvsp[0].astNode)->position);
    }
#line 3176 "parser.tab.c"
    break;

  case 140: /* enumerator: identifier ASSIGN constant_expression  */
#line 1161 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Assignment",EMPTY_VAL , (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild("Enum Element", (yyvsp[-2].astNode)->value,(yyvsp[-2].astNode)->position); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3187 "parser.tab.c"
    break;

  case 141: /* type_qualifier: CONST  */
#line 1171 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Qualifier", "const", (yyvsp[0].tokenAtr)->position);
    }
#line 3196 "parser.tab.c"
    break;

  case 142: /* type_qualifier: VOLATILE  */
#line 1176 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Qualifier", "volatile", (yyvsp[0].tokenAtr)->position);
    }
#line 3205 "parser.tab.c"
    break;

  case 143: /* declarator: pointer direct_declarator  */
#line 1184 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer Declarator", EMPTY_VAL);
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3216 "parser.tab.c"
    break;

  case 144: /* declarator: direct_declarator  */
#line 1191 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3225 "parser.tab.c"
    break;

  case 145: /* direct_declarator: identifier  */
#line 1199 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode((yyvsp[0].astNode));
    }
#line 3234 "parser.tab.c"
    break;

  case 146: /* direct_declarator: LPAREN declarator rparen  */
#line 1204 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 3243 "parser.tab.c"
    break;

  case 147: /* direct_declarator: direct_declarator LSQUARE constant_expression rsquare  */
#line 1209 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3254 "parser.tab.c"
    break;

  case 148: /* direct_declarator: direct_declarator LSQUARE rsquare  */
#line 1216 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
    }
#line 3264 "parser.tab.c"
    break;

  case 149: /* direct_declarator: direct_declarator LPAREN parameter_type_list rparen  */
#line 1222 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3274 "parser.tab.c"
    break;

  case 150: /* direct_declarator: direct_declarator LPAREN identifier_list rparen  */
#line 1228 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3284 "parser.tab.c"
    break;

  case 151: /* direct_declarator: direct_declarator LPAREN rparen  */
#line 1234 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyvsp[-2].astNode)->addChild("Empty Parameter List", EMPTY_VAL, (yyvsp[-2].astNode)->position);
    }
#line 3294 "parser.tab.c"
    break;

  case 152: /* pointer: STAR  */
#line 1245 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[0].tokenAtr)->position);
    }
#line 3303 "parser.tab.c"
    break;

  case 153: /* pointer: STAR type_qualifier_list  */
#line 1250 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3313 "parser.tab.c"
    break;

  case 154: /* pointer: STAR pointer  */
#line 1256 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3323 "parser.tab.c"
    break;

  case 155: /* pointer: STAR type_qualifier_list pointer  */
#line 1262 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[-2].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3334 "parser.tab.c"
    break;

  case 156: /* type_qualifier_list: type_qualifier  */
#line 1272 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3343 "parser.tab.c"
    break;

  case 157: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1277 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3353 "parser.tab.c"
    break;

  case 158: /* parameter_type_list: parameter_list  */
#line 1286 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3362 "parser.tab.c"
    break;

  case 159: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1291 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild("Ellipsis", "...", (yyvsp[0].tokenAtr)->position); 
    }
#line 3372 "parser.tab.c"
    break;

  case 160: /* parameter_list: parameter_declaration  */
#line 1300 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Parameter List", EMPTY_VAL);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3382 "parser.tab.c"
    break;

  case 161: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1306 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3392 "parser.tab.c"
    break;

  case 162: /* parameter_declaration: declaration_specifiers declarator  */
#line 1315 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter Declaration", "parameterDeclaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3403 "parser.tab.c"
    break;

  case 163: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1322 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter Declaration", "parameterDeclaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3414 "parser.tab.c"
    break;

  case 164: /* parameter_declaration: declaration_specifiers  */
#line 1329 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter Declaration", "parameterDeclaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3424 "parser.tab.c"
    break;

  case 165: /* identifier_list: identifier  */
#line 1338 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("IdentifierList", "identifierList");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3434 "parser.tab.c"
    break;

  case 166: /* identifier_list: identifier_list COMMA identifier  */
#line 1344 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3444 "parser.tab.c"
    break;

  case 167: /* type_name: specifier_qualifier_list  */
#line 1353 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3453 "parser.tab.c"
    break;

  case 168: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1358 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3463 "parser.tab.c"
    break;

  case 169: /* abstract_declarator: pointer  */
#line 1367 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3472 "parser.tab.c"
    break;

  case 170: /* abstract_declarator: direct_abstract_declarator  */
#line 1372 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3481 "parser.tab.c"
    break;

  case 171: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1377 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3491 "parser.tab.c"
    break;

  case 172: /* direct_abstract_declarator: LPAREN abstract_declarator rparen  */
#line 1386 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);  
    }
#line 3500 "parser.tab.c"
    break;

  case 173: /* direct_abstract_declarator: LSQUARE rsquare  */
#line 1391 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration"); 
    }
#line 3509 "parser.tab.c"
    break;

  case 174: /* direct_abstract_declarator: LSQUARE constant_expression rsquare  */
#line 1396 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration");  
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 3519 "parser.tab.c"
    break;

  case 175: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE rsquare  */
#line 1402 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
        (yyval.astNode)->addChild("Array Declaration");  
    }
#line 3529 "parser.tab.c"
    break;

  case 176: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression rsquare  */
#line 1408 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);  
        (yyval.astNode)->addChild(new ASTNode("Array Declaration"));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3540 "parser.tab.c"
    break;

  case 177: /* direct_abstract_declarator: LPAREN rparen  */
#line 1415 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter List", EMPTY_VAL); 
    }
#line 3549 "parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: LPAREN parameter_type_list rparen  */
#line 1420 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode); 
    }
#line 3558 "parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: direct_abstract_declarator LPAREN rparen  */
#line 1425 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild("Parameter List", EMPTY_VAL); 
    }
#line 3568 "parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list rparen  */
#line 1431 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 3578 "parser.tab.c"
    break;

  case 181: /* initializer: assignment_expression  */
#line 1440 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3587 "parser.tab.c"
    break;

  case 182: /* initializer: LCURLY initializer_list rcurly  */
#line 1445 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode); 
    }
#line 3596 "parser.tab.c"
    break;

  case 183: /* initializer: LCURLY initializer_list COMMA rcurly  */
#line 1450 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
    }
#line 3605 "parser.tab.c"
    break;

  case 184: /* initializer_list: initializer  */
#line 1459 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3614 "parser.tab.c"
    break;

  case 185: /* initializer_list: initializer_list COMMA initializer  */
#line 1464 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3624 "parser.tab.c"
    break;

  case 186: /* statement: labeled_statement  */
#line 1473 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3633 "parser.tab.c"
    break;

  case 187: /* statement: compound_statement  */
#line 1478 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3642 "parser.tab.c"
    break;

  case 188: /* statement: expression_statement  */
#line 1483 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3651 "parser.tab.c"
    break;

  case 189: /* statement: selection_statement  */
#line 1488 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3660 "parser.tab.c"
    break;

  case 190: /* statement: iteration_statement  */
#line 1493 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3669 "parser.tab.c"
    break;

  case 191: /* statement: jump_statement  */
#line 1498 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3678 "parser.tab.c"
    break;

  case 192: /* statement: declaration  */
#line 1503 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3687 "parser.tab.c"
    break;

  case 193: /* labeled_statement: identifier COLON statement  */
#line 1512 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Labeled Statement", (yyvsp[-2].astNode)->value, (yyvsp[-2].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3697 "parser.tab.c"
    break;

  case 194: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1518 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Case Statement", "Case", (yyvsp[-3].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3708 "parser.tab.c"
    break;

  case 195: /* labeled_statement: DEFAULT COLON statement  */
#line 1525 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Default Statement", "Default", (yyvsp[-2].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3718 "parser.tab.c"
    break;

  case 196: /* compound_statement: LCURLY rcurly  */
#line 1534 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
    }
#line 3727 "parser.tab.c"
    break;

  case 197: /* compound_statement: LCURLY statement_list rcurly  */
#line 1539 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
    }
#line 3737 "parser.tab.c"
    break;

  case 198: /* compound_statement: LCURLY declaration_list rcurly  */
#line 1545 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
    }
#line 3747 "parser.tab.c"
    break;

  case 199: /* compound_statement: LCURLY declaration_list statement_list rcurly  */
#line 1551 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
    }
#line 3758 "parser.tab.c"
    break;

  case 200: /* declaration_list: declaration  */
#line 1561 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3767 "parser.tab.c"
    break;

  case 201: /* declaration_list: declaration_list declaration  */
#line 1566 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3777 "parser.tab.c"
    break;

  case 202: /* statement_list: statement  */
#line 1575 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Statement List"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3787 "parser.tab.c"
    break;

  case 203: /* statement_list: statement_list statement  */
#line 1581 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3797 "parser.tab.c"
    break;

  case 204: /* expression_statement: semi_colon  */
#line 1590 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Expression Statement", ";"); 
    }
#line 3806 "parser.tab.c"
    break;

  case 205: /* expression_statement: expression semi_colon  */
#line 1595 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
    }
#line 3815 "parser.tab.c"
    break;

  case 206: /* selection_statement: IF LPAREN expression rparen statement  */
#line 1603 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("If Statement", "if", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3826 "parser.tab.c"
    break;

  case 207: /* selection_statement: IF LPAREN expression rparen statement ELSE statement  */
#line 1610 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("If Else Statement", "if-else", (yyvsp[-6].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3838 "parser.tab.c"
    break;

  case 208: /* selection_statement: SWITCH LPAREN expression rparen statement  */
#line 1618 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Switch Statement", "switch", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3849 "parser.tab.c"
    break;

  case 209: /* iteration_statement: WHILE LPAREN expression rparen statement  */
#line 1628 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("While Loop", "while", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3860 "parser.tab.c"
    break;

  case 210: /* iteration_statement: UNTIL LPAREN expression rparen statement  */
#line 1635 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Until Loop", "until", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3871 "parser.tab.c"
    break;

  case 211: /* iteration_statement: DO statement WHILE LPAREN expression rparen semi_colon  */
#line 1642 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("DoWhile Loop", "do-while", (yyvsp[-6].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-5].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
    }
#line 3882 "parser.tab.c"
    break;

  case 212: /* iteration_statement: FOR LPAREN expression_statement expression_statement rparen statement  */
#line 1649 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("For Loop", "for", (yyvsp[-5].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3894 "parser.tab.c"
    break;

  case 213: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression rparen statement  */
#line 1657 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("For Loop", "for", (yyvsp[-6].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3907 "parser.tab.c"
    break;

  case 214: /* iteration_statement: FOR LPAREN declaration expression_statement expression rparen statement  */
#line 1666 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("For Loop", "for", (yyvsp[-6].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3920 "parser.tab.c"
    break;

  case 215: /* jump_statement: GOTO identifier semi_colon  */
#line 1678 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Goto Statement", "goto", (yyvsp[-2].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3930 "parser.tab.c"
    break;

  case 216: /* jump_statement: CONTINUE semi_colon  */
#line 1684 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Continue Statement", "continue", (yyvsp[-1].tokenAtr)->position);
    }
#line 3939 "parser.tab.c"
    break;

  case 217: /* jump_statement: BREAK semi_colon  */
#line 1689 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Break Statement", "break", (yyvsp[-1].tokenAtr)->position);
    }
#line 3948 "parser.tab.c"
    break;

  case 218: /* jump_statement: RETURN semi_colon  */
#line 1694 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Return Statement", "return", (yyvsp[-1].tokenAtr)->position);
    }
#line 3957 "parser.tab.c"
    break;

  case 219: /* jump_statement: RETURN expression semi_colon  */
#line 1699 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Return Statement", "return", (yyvsp[-2].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 3967 "parser.tab.c"
    break;

  case 220: /* translation_unit: external_declaration  */
#line 1709 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Translation Unit", EMPTY_VAL);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        root = (yyval.astNode);
    }
#line 3978 "parser.tab.c"
    break;

  case 221: /* translation_unit: translation_unit external_declaration  */
#line 1716 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3988 "parser.tab.c"
    break;

  case 222: /* external_declaration: function_definition  */
#line 1732 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3997 "parser.tab.c"
    break;

  case 223: /* external_declaration: declaration  */
#line 1737 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 4006 "parser.tab.c"
    break;

  case 224: /* external_declaration: function_declaration  */
#line 1742 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 4015 "parser.tab.c"
    break;

  case 225: /* function_declaration: declaration_specifiers declarator semi_colon  */
#line 1750 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Function Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Function_Def_Handler((yyvsp[-1].astNode));
    }
#line 4027 "parser.tab.c"
    break;

  case 226: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 1771 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Definition"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        Function_Def_Handler((yyvsp[-1].astNode));
    }
#line 4039 "parser.tab.c"
    break;


#line 4043 "parser.tab.c"

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

#line 1795 "parser.y"



// main function

int main(int argc, char **argv) {

    signal(SIGSEGV, signalHandler); // Catch segmentation fault

    //------------------------ cmd line arguments handling ------------------------

        std::string inputInstructions = "Usage: " + std::string(argv[0]) + " <input_file> <output_file> [-ast <dot_file>] [-r] [-pt] [-s] \n";
        inputInstructions += "Options: \n";
        inputInstructions += "[-ast <dot_file>] : Generate AST as DOT file\n";
        inputInstructions += "[-r] : Generate Recursive Output\n";
        inputInstructions += "[-pt <parser_table_file>] : Generate Parser Table\n";
        inputInstructions += "[-s <SExp_file>] : Generate S-Expression\n";

        /* std::cout << "argc: " << argc << std::endl; */
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [-ast <dot_file>] [-r] [-pt] [-s] \n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];
        std::string dot_file = "ast_graph.dot";
        std::string recursive_output_file = "recursive_output.txt";
        std::string parser_table_file = "parser_table.txt";
        std::string SExp_file = "SExp.txt";
        std::string LaTeXParserTable = "parser_table.tex";    

        bool ast_flag = false;
        bool recursive_flag = false;
        bool parser_table_flag = false;
        bool SExp_flag = false;

        // Open default output file
        yyin = fopen(input_file.c_str(), "r");
        if (!yyin) {
            std::cerr << "Error: Unable to open input file\n";
            return 1;
        }
        LINE
        initOutputFile(output_file); // open output file

        LINE

        // Parse command line arguments
        for (int i = 3; i < argc; i++) {
            if (std::string(argv[i]) == "-ast") {
                ast_flag = true;
                if (i + 1 < argc) {
                    dot_file = argv[i + 1];
                    i++;
                } else {
                    std::cerr << "Error: Missing argument for -ast\n";
                    std::cerr << inputInstructions;
                    return 1;
                }
            } else if (std::string(argv[i]) == "-r") {
                recursive_flag = true;
            } else if (std::string(argv[i]) == "-pt") {
                parser_table_flag = true;
                
            } else if (std::string(argv[i]) == "-s") {
                SExp_flag = true;
            } else {
                std::cerr << "Error: Invalid argument\n";
                std::cerr << inputInstructions;
                return 1;
            }
        }

    // ------------------------ Symbol Table ------------------------
        // Create a new symbol table
        /* SymbolTable *symTable = new SymbolTable(); */

    LINE
    //------------------------ Parsing ------------------------

    yyparse();  // Call BISON's parser
    
    LINE
    // ------------------------- Parser Phase Completion Checks ------------------------

    bool lexerFailed = (lexerLOG.size() > 0);
    bool parseError = (parserLOG.size() > 0);
    parseError = parseError || lexerFailed || bisonError;

    if(lexerFailed){
        *output << "\U0001F6A8 Input Program failed in Lexical Analysis Phase \U0001F6A8\n" << std::endl;
        *output << LEXERLOGHEADER << std::endl;
        for(auto log : lexerLOG){
            *output << log << std::endl;
        }
        *output << LOGFOOTER << std::endl;
        *output << std::endl;

        *output << "----No Further Processing----\n";
        // Clean Up
        fclose(yyin);
        closeOutputFile();
        return 0;
    }

    if(parseError){
        *output << "\U0001F6A8 Input Program failed in Syntax Analysis Phase \U0001F6A8\n" << std::endl;
        *output << PARSERLOGHEADER << std::endl;
        for(auto log : parserLOG){
            *output << log << std::endl;
        }

        if(!customError){
            // NO CUSTOM ERROR
            *output << "!!Syntax Error at Line: " << yylineno << " near tokne: " << yytext << "!!\n";
        }

        *output << LOGFOOTER << std::endl;
        *output << std::endl;

        *output << "----No Further Processing----\n";
        // Clean Up
        fclose(yyin);
        closeOutputFile();
        return 0;
    }
    LINE

    // Success message
    *output << "\U0001F44D Input Program passed Syntax Analysis Phase \U0001F44D\n" << std::endl;


    // ------------------------- Printing Various Outputs ------------------------

    if(ast_flag){
        // Print AST to DOT file
        generateDOT(root, dot_file);
        *output << "\U0001F53A AST generated as DOT file: " << dot_file << " can be visualized using Graphviz\n";
    }

    if(recursive_flag){
        // Print Recursive Output
        printASTToFile(root, recursive_output_file);
        *output << "\U0001F53A Recursive Output generated as: " << recursive_output_file << "\n";
    }

    if(SExp_flag){
        // Print S-Expression
        writeASTToSExpression(root, SExp_file);
        *output << "\U0001F53A S-Expression generated as: " << SExp_file << "\n";
    }

    if(parser_table_flag){
        // Print Parser Table
        std::ofstream parser_table;
        parser_table.open(parser_table_file);
        printParserTable(parser_table);
        parser_table.close();
        *output << "\U0001F53A Parser Table (TXT) generated as: " << parser_table_file << "\n";
    }
    LINE
    // MUST PRINT PARSER_LaTeX_TABLE
    std::ofstream LaTeXTable;
    LaTeXTable.open(LaTeXParserTable);
    writeLatexTable(LaTeXTable);
    LaTeXTable.close();
    *output << "\U00002B55 Parser Table (LaTeX) generated as: " << LaTeXParserTable << " can be visualized using LaTeX\n";

    LINE
    //------------------------- Cleanup ------------------------
    if (yyin) fclose(yyin);  // Close the input file if opened
    closeOutputFile();  // Close the output file
    return 0;
}

// Error handling function
void yyerror(const char* s) {
    /* yyclearin; */

    // This Won't print anything
    
    bisonError = true; // Makes sure no Printing of any AST happens
}

//Handler Functions
int noOfPointers(ASTNode* node){
    if(node->children.size()==0) return 1;

    return 1+noOfPointers(node->children[0]);
}

void E_S_U_Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList,std::string s1,std::string s2){
    for(auto item : initDeclaratorList->children){
        if(item->type == "Initializer"){
            PARSER_TABLE.push_back({item->children[0]->position,{item->children[0]->value, s2}});
        } else {
            PARSER_TABLE.push_back({item->position,{item->value, s2}});
        }
    }
}

void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList){
    std::string type="";
    ASTNode* node = declarationSpecifiers;
    
    if(declarationSpecifiers->type == "Enum Specifier"){
        E_S_U_Declaration_Handler(declarationSpecifiers, initDeclaratorList, "enum", "enum Element");
        return;
    }

    if(declarationSpecifiers->type == "Struct"){
        E_S_U_Declaration_Handler(declarationSpecifiers, initDeclaratorList, "struct", "struct Instance"); 
        return;
    }

    if(declarationSpecifiers->type == "Union"){
        E_S_U_Declaration_Handler(declarationSpecifiers, initDeclaratorList, "union", "union Instance");
        return;
    }

    int typeSpec=0, typeQual=0, storageClass=0;
    while(node){
        if(node->type == "Type Specifier"){
            type = node->value;
            typeSpec++;
        }else if(node->type == "Storage Class Specifier") {
            storageClass++; 
        }
        node=(node->children.size())?node->children[0]:nullptr; //Move down the tree
    }
    if(storageClass>1){
        ourError("NOT-ALLOWED | Multiple type specifiers/qualifiers/storage classes in declaration");
        return;
    }
    if(type == "") type = "int"; // default type is int
    for(auto children : initDeclaratorList->children){
        int pointCount=0, arrayCount=0;
        ASTNode* tempNode = children;
        if(children->type == "Initializer") tempNode = children->children[0];
        if(tempNode->type == "Pointer Declarator"){
            pointCount=noOfPointers(tempNode->children[0]);
            /* std::cout<<pointCount<<std::endl; */
            tempNode=tempNode->children[1];
        }
        if(tempNode->type == "Array Declaration"){
            while(tempNode->type == "Array Declaration"){
            arrayCount++;
            tempNode = tempNode->children[0];
            }
        }
        PARSER_TABLE.push_back({tempNode->position,{tempNode->value, type+(pointCount?(" "+std::to_string(pointCount)+"-D ptr "):"")+(arrayCount?(" "+std::to_string(arrayCount)+"-D Arr "):"")}});
    }
}

void Function_Def_Handler(ASTNode* declarator){
    std::string functionName=declarator->value;
    PARSER_TABLE.push_back({declarator->position, {functionName, "function declaration"}});

    declarator = (declarator->children.size()) ?declarator->children[0] : nullptr;
    if(declarator==nullptr) return;
    if(declarator->type == "EmptyList") return;
    else if(declarator->type == "Parameter List"){
        for(auto parameter: declarator->children){
            std::string type="";
            ASTNode* tempInitDeclList = new ASTNode("Initialization or Declaration List", "initDeclaratorList");
            tempInitDeclList->addChild(parameter->children[1]);
            Declaration_Handler(parameter->children[0], tempInitDeclList);
        }
    }
}

void Struct_Union_Declaration_Handler(ASTNode* specifierQualifierList, ASTNode* structDeclaratorList){
    std::string type="";
    ASTNode* node = specifierQualifierList;
    int typeSpec=0, typeQual=0, storageClass=0;
    while(node){
        if(node->type == "Type Specifier"){
            type = node->value;
            typeSpec++;
        } else if(node->type == "Storage Class Specifier") storageClass++;

        node=(node->children.size())?node->children[0]:nullptr;
    }
    if(storageClass>1){
        ourError("Multiple storage classes in declaration");
        return;
    }
    if(type == "") type = "int";
    for(auto children : structDeclaratorList->children){
        if(children->type == "Struct or Union Declarator"){
            PARSER_TABLE.push_back({children->children[0]->position, {children->children[0]->value, type}});
        }else if(children->type == "Identifier"){
            PARSER_TABLE.push_back({children->position,{children->value, type}});
        }
    }
}

void Enum_Declaration_Handler(ASTNode* enumSpecifier){
    for(auto children : enumSpecifier->children){
        if(children->type == "enumID"){
            PARSER_TABLE.push_back({children->position, {children->value, "enum"}});
        } else if(children->type == "Enum List"){
            for(auto item : children->children){
                if(item->type == "Enum Assignment"){
                    PARSER_TABLE.push_back({item->children[0]->position, {item->children[0]->value, "enum Element"}});
                } else {
                    PARSER_TABLE.push_back({item->position, {item->value, "enum Element"}});
                }
            }
        }
    }
}

// PARSER_TABLE
void printParserTable(std::ostream& out) {
    // Sort by (lineNo, columnNo)
    std::sort(PARSER_TABLE.begin(), PARSER_TABLE.end(), 
        [](const auto& a, const auto& b) {
            return (a.first.first < b.first.first) || 
                   (a.first.first == b.first.first && a.first.second < b.first.second);
        });

    // Set dynamic column widths
    int positionWidth = 14;   // Width for "LineNo:Column"
    int idNameWidth = 20;     // Width for Identifier Name
    int idTypeWidth = 35;     // Width for Identifier Type

    // Print table header
    out << "+" << std::string(positionWidth + 2, '-') 
        << "+" << std::string(idNameWidth + 2, '-') 
        << "+" << std::string(idTypeWidth + 2, '-') 
        << "+" << std::endl;

    out << "| " << std::setw(positionWidth) << std::left << "Position"
        << " | " << std::setw(idNameWidth) << std::left << "Identifier Name"
        << " | " << std::setw(idTypeWidth) << std::left << "Identifier Type"
        << " |" << std::endl;

    out << "+" << std::string(positionWidth + 2, '-') 
        << "+" << std::string(idNameWidth + 2, '-') 
        << "+" << std::string(idTypeWidth + 2, '-') 
        << "+" << std::endl;

    // Print each entry
    for (const auto& entry : PARSER_TABLE) {
        int line = entry.first.first;
        int column = entry.first.second;
        std::string idName = entry.second.first;
        std::string idType = entry.second.second;

        out << "| " << std::setw(positionWidth) << std::left << (std::to_string(line) + ":" + std::to_string(column))
            << " | " << std::setw(idNameWidth) << std::left << idName
            << " | " << std::setw(idTypeWidth) << std::left << idType
            << " |" << std::endl;
    }

    // Print table footer
    out << "+" << std::string(positionWidth + 2, '-') 
        << "+" << std::string(idNameWidth + 2, '-') 
        << "+" << std::string(idTypeWidth + 2, '-') 
        << "+" << std::endl;
}

void writeLatexTable(std::ostream &out) {
    // LaTeX document header
    out << "\\documentclass{article}\n";
    out << "\\usepackage[a4paper,margin=1in]{geometry}\n";
    out << "\\usepackage{longtable}\n";
    out << "\\usepackage[table]{xcolor}\n";
    out << "\\definecolor{headercolor}{RGB}{79, 129, 189}\n";
    out << "\\definecolor{rowcolor}{RGB}{217, 225, 242}\n";
    out << "\\begin{document}\n\n";
    out << "\\begin{center}\n";
    out << "    {\\LARGE \\textbf{Parser Table of Input Program}} \\\\[10pt]\n";
    out << "\\end{center}\n\n";
    out << "\\renewcommand{\\arraystretch}{1.3}\n";
    out << "\\setlength{\\arrayrulewidth}{0.7mm}\n";
    out << "\\rowcolors{2}{rowcolor}{white}\n";

    
    // Begin table
    out << "\\begin{longtable}{|l|c|c|}\n";
    out << "    \\hline\n";
    out << "    \\rowcolor{headercolor} \\textbf{lineNo:columnNo} & \\textbf{Identifier Name} & \\textbf{Identifier Type} \\\\ \n";
    out << "    \\hline\n";
    out << "    \\endfirsthead\n";
    out << "    \\hline\n";
    out << "    \\rowcolor{headercolor} \\textbf{lineNo:columnNo} & \\textbf{Identifier Name} & \\textbf{Identifier Type} \\\\ \n";
    out << "    \\hline\n";
    out << "    \\endhead\n";
    // Populate table rows from PARSER_TABLE
    for (const auto &entry : PARSER_TABLE) {
        std::string correctTokenName;
        // Replace _ with \\_
        for (char c : entry.second.first) {
            if (c == '_') correctTokenName += "\\_";
            else correctTokenName += c;
        }
        out << "    " << entry.first.first << ":" << entry.first.second << " & "
            << correctTokenName << " & "
            << entry.second.second << " \\\\ \n";
        out << "    \\hline\n";
    }

    // End table and document
    out << "\\end{longtable}\n\n";
    out << "\\end{document}\n";
}
