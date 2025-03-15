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

#line 188 "parser.tab.c"

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
  YYSYMBOL_typedef_specifiers = 118,       /* typedef_specifiers  */
  YYSYMBOL_typedef_specifiersL2 = 119,     /* typedef_specifiersL2  */
  YYSYMBOL_init_declarator_list = 120,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 121,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 122,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 123,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 124, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 125,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 126,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 127,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 128, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 129,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 130,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 131,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 132,          /* enumerator_list  */
  YYSYMBOL_enumerator = 133,               /* enumerator  */
  YYSYMBOL_type_qualifier = 134,           /* type_qualifier  */
  YYSYMBOL_declarator = 135,               /* declarator  */
  YYSYMBOL_direct_declarator = 136,        /* direct_declarator  */
  YYSYMBOL_pointer = 137,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 138,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 139,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 140,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 141,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 142,          /* identifier_list  */
  YYSYMBOL_type_name = 143,                /* type_name  */
  YYSYMBOL_abstract_declarator = 144,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 145, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 146,              /* initializer  */
  YYSYMBOL_initializer_list = 147,         /* initializer_list  */
  YYSYMBOL_statement = 148,                /* statement  */
  YYSYMBOL_labeled_statement = 149,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 150,       /* compound_statement  */
  YYSYMBOL_declaration_list = 151,         /* declaration_list  */
  YYSYMBOL_statement_list = 152,           /* statement_list  */
  YYSYMBOL_expression_statement = 153,     /* expression_statement  */
  YYSYMBOL_selection_statement = 154,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 155,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 156,           /* jump_statement  */
  YYSYMBOL_translation_unit = 157,         /* translation_unit  */
  YYSYMBOL_external_declaration = 158,     /* external_declaration  */
  YYSYMBOL_function_declaration = 159,     /* function_declaration  */
  YYSYMBOL_function_definition = 160       /* function_definition  */
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
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1257

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  226
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  378

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
       0,   219,   219,   233,   247,   261,   275,   289,   308,   313,
     318,   323,   332,   337,   342,   349,   357,   364,   372,   378,
     387,   393,   402,   407,   413,   419,   425,   431,   441,   446,
     451,   456,   461,   466,   474,   479,   490,   495,   502,   509,
     519,   524,   531,   541,   546,   553,   563,   568,   575,   582,
     589,   599,   604,   611,   621,   626,   636,   641,   651,   656,
     666,   671,   681,   686,   696,   701,   712,   717,   727,   732,
     737,   742,   747,   752,   757,   762,   767,   772,   777,   786,
     791,   801,   808,   829,   849,   856,   864,   875,   880,   886,
     891,   897,   902,   913,   919,   927,   933,   944,   950,   960,
     965,   975,   980,   985,   990,   998,  1003,  1008,  1013,  1018,
    1023,  1028,  1033,  1038,  1043,  1048,  1053,  1067,  1077,  1084,
    1097,  1102,  1111,  1117,  1128,  1139,  1145,  1150,  1156,  1164,
    1170,  1180,  1185,  1191,  1201,  1208,  1216,  1226,  1232,  1242,
    1247,  1257,  1262,  1270,  1277,  1285,  1290,  1295,  1302,  1308,
    1314,  1320,  1331,  1336,  1342,  1348,  1358,  1363,  1372,  1377,
    1386,  1392,  1401,  1408,  1415,  1424,  1430,  1439,  1444,  1453,
    1458,  1463,  1472,  1477,  1482,  1488,  1494,  1501,  1506,  1511,
    1517,  1526,  1531,  1536,  1545,  1550,  1559,  1564,  1569,  1574,
    1579,  1584,  1589,  1598,  1604,  1611,  1620,  1625,  1631,  1637,
    1647,  1652,  1661,  1667,  1676,  1681,  1689,  1696,  1704,  1714,
    1721,  1728,  1735,  1743,  1752,  1764,  1770,  1775,  1780,  1785,
    1795,  1802,  1818,  1823,  1828,  1836,  1857
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
  "declaration_specifiers", "typedef_specifiers", "typedef_specifiersL2",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
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

#define YYPACT_NINF (-196)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-97)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     857,  -196,  -196,  1050,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,    58,  -196,  -196,   120,   120,  -196,   944,  1050,  -196,
      83,  -196,  1050,    55,   632,  -196,  -196,  -196,   136,  1050,
    1050,    50,   -18,   136,    70,  -196,  -196,  -196,    11,  -196,
     148,   114,    20,  -196,    11,    24,  -196,  -196,  -196,   653,
      34,  -196,  -196,  -196,  -196,  -196,    11,    32,   149,  -196,
      50,    43,  -196,  -196,    70,   136,  -196,   504,  1133,  -196,
    -196,   875,  1147,   114,  -196,   653,  1064,  -196,    19,   653,
     653,  -196,   511,  -196,    50,  -196,   149,  -196,  -196,  -196,
    -196,  -196,  -196,  1188,  1215,  1215,   770,  -196,  -196,  -196,
    -196,  -196,  -196,   511,    92,    90,   125,   132,   588,   139,
      50,   119,   119,   414,   173,     9,  -196,  -196,  -196,  -196,
     325,   477,   511,  -196,   174,   200,   238,   184,   243,   168,
     166,   177,   217,    46,  -196,  -196,    77,  -196,   120,  -196,
    -196,  -196,   504,   504,  -196,  -196,  -196,  -196,  1133,  -196,
    -196,  -196,  -196,  -196,    69,    43,   180,  -196,   -19,  -196,
    -196,  -196,  -196,   207,  -196,  -196,  -196,   511,   115,  -196,
     224,  -196,  1064,  -196,  -196,  -196,   770,  -196,   511,  -196,
    -196,   190,   165,    43,   227,   588,   511,   511,   511,  -196,
     172,   701,   119,  -196,  -196,  -196,    77,   511,   588,    50,
    -196,  -196,  1174,   511,    50,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,   511,  -196,   511,   511,
     511,   511,   511,   511,   511,   511,   511,   511,   511,   511,
     511,   511,   511,   511,   511,   511,   511,   511,  -196,  -196,
    -196,   504,  -196,  -196,  -196,   199,   788,  1147,  -196,    13,
    -196,   203,  -196,   920,    50,  -196,  -196,  -196,    19,  -196,
     511,  -196,    43,  -196,   988,   205,  -196,   511,   588,  -196,
     190,   190,   190,   226,   264,   414,   414,  -196,  -196,   190,
    -196,  -196,  -196,   191,  -196,   -16,  -196,  -196,  -196,  -196,
    -196,   174,   174,   200,   200,   238,   238,   238,   238,   184,
     184,   243,   168,   166,   177,   217,    67,  -196,  -196,   858,
    -196,  -196,    43,    43,  -196,   207,   203,  1006,  1147,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,   588,   588,   588,
     511,   511,  1174,   588,   511,  -196,  -196,   511,  -196,  -196,
    -196,  -196,  -196,  -196,    43,  -196,   207,   204,  -196,  -196,
     190,   190,   588,   190,  -196,  -196,  -196,  -196,  -196,   588,
     119,   588,  -196,   588,  -196,  -196,  -196,  -196
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,   116,     0,   101,   102,   103,   104,   106,   107,
     108,   109,   112,   113,   110,   111,   141,   142,   105,   120,
     121,     0,    96,   223,     0,     0,    94,    87,    89,   114,
       0,   115,    91,     0,     0,   220,   224,   222,     0,    87,
      91,     0,   136,     0,   152,     4,   145,    82,     0,    97,
      99,   144,     0,    84,     0,    99,    88,    93,    90,     0,
     119,    92,    95,   157,     1,   221,     0,   139,     0,   137,
       0,     0,   156,   154,   153,     0,    83,     0,     0,   225,
     226,     0,     0,   143,    85,   126,     0,   122,     0,   128,
       0,    86,     0,     6,     0,   134,     0,     5,   146,   155,
      98,     3,    10,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     9,   204,   196,    12,
      22,    34,     0,    36,    40,    43,    46,    51,    54,    56,
      58,    60,    62,    64,    66,    79,     0,   192,     0,   202,
     186,   187,     0,     0,   188,   189,   190,   191,     0,     8,
     181,   100,   165,   151,   164,     0,   158,   160,     0,     7,
     148,    34,    81,     0,   125,   118,   123,     0,     0,   129,
     131,   127,     0,   140,   138,   135,     0,    26,     0,    23,
      24,     0,   167,     0,     0,     0,     0,     0,     0,   192,
       0,     0,     0,   216,   217,   218,     0,     0,     0,     0,
      18,    19,     0,     0,     0,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    68,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,   198,
     192,     0,   197,   203,   184,     0,     0,     0,   162,   169,
     163,   170,   149,     0,     0,   150,   147,   132,     0,   124,
       0,   117,     0,    11,     0,   169,   168,     0,     0,   195,
       0,     0,     0,     0,     8,     0,     0,   215,   219,     0,
     193,    17,    14,     0,    20,     0,    16,    67,    37,    38,
      39,    41,    42,    44,    45,    49,    50,    47,    48,    52,
      53,    55,    57,    59,    61,    63,     0,    80,   199,     0,
     182,   177,     0,     0,   173,     0,   171,     0,     0,   159,
     161,   166,   130,   133,    27,    35,   194,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    13,     0,   183,   185,
     178,   172,   174,   179,     0,   175,     0,   206,   208,   209,
       0,     0,     0,     0,   210,    21,    65,   180,   176,     0,
       0,     0,   212,     0,   207,   211,   214,   213
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,     0,  -196,   -22,   107,    10,   -35,  -196,  -196,  -196,
     248,  -196,  -118,    21,    29,     8,    31,    41,    47,    42,
      44,    49,  -196,   -42,   -43,  -196,   186,   -47,     5,    51,
    -196,   268,   106,   221,    28,    87,  -196,  -196,   209,   -77,
     -70,  -196,    35,  -196,   234,   212,   101,   -14,   -48,   -37,
     253,   -80,  -196,    45,  -196,   124,   -67,  -195,  -152,  -196,
      71,  -196,   261,  -196,   160,  -193,  -196,  -196,  -196,  -196,
     279,  -196,  -196
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   159,   126,   127,   321,    95,   170,   129,   130,   293,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   226,   146,   173,   199,   148,
      25,    26,    48,    49,    27,    28,    29,    30,    86,    87,
      88,   178,   179,    31,    68,    69,    32,    55,    51,    52,
      33,   322,   166,   167,   168,   193,   323,   261,   161,   255,
     149,   150,   151,   152,   153,   154,   155,   156,   157,    34,
      35,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      22,   165,    47,    53,    83,    23,   254,    73,   286,   176,
      50,    97,   -96,    70,   227,   174,     1,   264,   169,   181,
     247,    42,     1,     1,    46,    46,    76,    22,    79,    71,
      60,    39,    84,    62,    22,   160,   192,    99,    46,    23,
     172,    67,   256,    46,    91,   183,   257,    75,    43,    43,
     172,    24,    46,     1,    38,    39,    39,    44,     1,   208,
      39,     1,    45,   245,   326,    90,   194,    39,    39,   177,
      67,   172,     1,    97,   180,    46,    78,   125,    56,    58,
     326,   162,   147,    61,    92,    24,     1,   128,    46,    41,
      56,    61,   341,   342,    67,   246,   175,   260,   256,   203,
     204,   205,   257,   247,    40,   176,   185,    44,    44,    39,
     298,   299,   300,   247,    59,   160,   192,   347,   125,   196,
     202,    16,    17,     1,   248,   276,    47,   259,    45,    40,
     267,    54,   164,    40,    63,   172,    16,    17,   266,     1,
      40,    40,   195,    81,    66,    72,    85,    82,    46,    43,
     258,   268,   125,   125,   197,   275,   269,   250,    44,   335,
      89,   198,   249,   252,    46,    43,    45,   349,   201,   294,
      45,    45,    85,    85,    44,    63,    85,    85,    98,    77,
     287,    93,    40,   297,   288,    94,    89,    89,   163,   200,
      89,    89,   271,    85,   274,   125,   235,   236,   257,    45,
      78,   284,   207,    44,   317,   241,   285,    89,   125,   291,
     325,    83,   228,   242,   296,   172,   263,   229,   230,   259,
      97,    97,   324,   333,   253,   243,   247,   344,   172,   237,
     238,    93,   327,   244,   274,   319,   328,   275,   257,   231,
     232,   169,    71,   305,   306,   307,   308,   354,   233,   234,
     283,   125,   301,   302,   180,   340,    46,   239,   240,    46,
     346,   318,   303,   304,   331,   320,   279,   -96,    46,    85,
     309,   310,   262,    85,   270,   265,   160,   278,   125,   290,
     369,   356,   311,    89,    39,   313,   172,    89,   314,   312,
     352,    39,   191,   355,   315,    57,   100,    74,   273,   182,
     277,   365,    39,   332,    96,   366,   184,   164,   330,   206,
     272,    80,   251,    65,   164,     0,     0,     0,     0,   292,
       0,   368,   253,     0,     0,   164,     0,     0,     0,   348,
     171,     0,   209,   210,   211,     0,     0,   125,   125,   125,
     171,     0,     0,   125,     0,     0,     0,     0,   375,   336,
       0,   187,   189,   190,   212,    39,     0,    40,   213,     0,
     214,   171,   125,     0,    40,     0,     0,     0,     0,   125,
       0,   125,   191,   125,   191,    40,     0,     0,   164,   334,
     171,     0,   280,   281,   282,     0,     0,   337,   338,   339,
       0,     0,     0,   289,     0,     0,   343,     0,     0,   295,
     345,     0,     0,     0,     0,     0,     0,     0,   357,   358,
     359,     0,     0,     0,   364,     0,     0,     1,   101,   102,
     103,     0,   104,   105,     0,   171,     0,     0,    40,   350,
     351,     0,   316,   372,   353,     0,     0,     0,     0,     0,
     374,     0,   376,   106,   377,     0,     0,     0,     0,   362,
       0,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,   367,     0,     0,     0,    45,     0,   370,   371,     0,
     373,     0,     0,     0,     0,     0,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   171,     0,     1,   101,   102,
     103,     0,   104,   105,     1,   101,   102,   103,   171,   104,
     105,     0,     0,     0,     0,   171,   360,   361,   363,   225,
       0,     0,     2,   106,     0,    77,    93,     0,     0,     0,
     106,   107,   108,   109,   110,   111,   112,     0,   107,   108,
     109,   110,   111,   112,     0,    45,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   171,   113,   114,   115,
       0,   116,   117,   118,   119,   120,   121,   122,   123,   124,
       0,     1,   101,   102,   103,   171,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,   106,     0,    77,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,     0,    64,     0,     0,     1,     0,     0,     0,    45,
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       2,   113,   114,   115,     0,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,     0,     0,
       0,     2,     0,     0,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     1,   101,   102,   103,     0,   104,
     105,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     0,     0,     0,     0,     2,
     106,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     1,   101,   102,   103,     0,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     0,     0,     0,     2,   106,
       0,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,   111,   112,     0,     0,     0,     2,   256,    97,     0,
       0,   257,     0,     0,     0,     0,    44,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       1,     1,   101,   102,   103,     0,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,     0,     0,     2,     0,   106,     0,   158,
      93,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,     0,     0,     2,     0,    97,     0,     0,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     1,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   329,     0,     0,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     2,   274,    97,     0,
       0,   257,     0,     0,     0,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     2,     0,    97,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     0,     0,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     1,   101,   102,   103,
       0,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       1,   101,   102,   103,     0,   104,   105,     0,     0,     0,
       0,     0,   106,     0,   158,     0,     0,     0,     0,     0,
     107,   108,   109,   110,   111,   112,   106,     1,   101,   102,
     103,   169,   104,   105,   107,   108,   109,   110,   111,   112,
       0,     1,   101,   102,   103,     0,   104,   105,     0,     0,
       0,     0,     0,   106,    97,     0,     0,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,   186,     1,   101,
     102,   103,     0,   104,   105,   107,   108,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,     0,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112
};

static const yytype_int16 yycheck[] =
{
       0,    81,    24,    25,    52,     0,   158,    44,   201,    86,
      24,    30,     3,    31,   132,    85,     3,    36,    34,    89,
      36,    21,     3,     3,    24,    25,    48,    27,    50,    43,
      30,     3,    54,    33,    34,    78,   106,    74,    38,    34,
      82,    41,    29,    43,    66,    92,    33,    36,    29,    29,
      92,     0,    52,     3,     3,    27,    28,    38,     3,    50,
      32,     3,    51,    17,   259,    31,   113,    39,    40,    50,
      70,   113,     3,    30,    88,    75,    52,    77,    27,    28,
     275,    81,    77,    32,    52,    34,     3,    77,    88,    31,
      39,    40,   285,   286,    94,    49,    86,   164,    29,   121,
     122,   123,    33,    36,     3,   182,    96,    38,    38,    81,
     228,   229,   230,    36,    31,   158,   186,    50,   118,    29,
     120,    66,    67,     3,   146,   192,   148,   164,    51,    28,
     177,    25,    81,    32,    33,   177,    66,    67,   173,     3,
      39,    40,    50,    29,    38,    44,    59,    33,   148,    29,
     164,    36,   152,   153,    29,   192,   178,   152,    38,   277,
      59,    29,   152,   153,   164,    29,    51,   319,    29,   212,
      51,    51,    85,    86,    38,    74,    89,    90,    71,    31,
     202,    32,    81,   226,   206,    36,    85,    86,    81,   118,
      89,    90,   182,   106,    29,   195,    12,    13,    33,    51,
      52,   201,    29,    38,   247,    37,   201,   106,   208,   209,
     257,   259,    38,    47,   214,   257,    36,    43,    44,   256,
      30,    30,   257,   270,   153,    48,    36,    36,   270,    45,
      46,    32,    29,    16,    29,    36,    33,   274,    33,    39,
      40,    34,   256,   235,   236,   237,   238,   327,    10,    11,
      78,   251,   231,   232,   268,    29,   256,    14,    15,   259,
     295,   251,   233,   234,   264,   255,   195,     3,   268,   182,
     239,   240,   165,   186,    50,   168,   319,    50,   278,   208,
      76,   328,   241,   182,   256,   243,   328,   186,   244,   242,
     325,   263,   106,   328,   245,    27,    75,    44,   191,    90,
     193,   344,   274,   268,    70,   347,    94,   256,   263,   123,
     186,    50,   152,    34,   263,    -1,    -1,    -1,    -1,   212,
      -1,   356,   251,    -1,    -1,   274,    -1,    -1,    -1,   319,
      82,    -1,     7,     8,     9,    -1,    -1,   337,   338,   339,
      92,    -1,    -1,   343,    -1,    -1,    -1,    -1,   370,   278,
      -1,   103,   104,   105,    29,   327,    -1,   256,    33,    -1,
      35,   113,   362,    -1,   263,    -1,    -1,    -1,    -1,   369,
      -1,   371,   186,   373,   188,   274,    -1,    -1,   327,   272,
     132,    -1,   196,   197,   198,    -1,    -1,   280,   281,   282,
      -1,    -1,    -1,   207,    -1,    -1,   289,    -1,    -1,   213,
     293,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,
     339,    -1,    -1,    -1,   343,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,   177,    -1,    -1,   327,   322,
     323,    -1,   246,   362,   327,    -1,    -1,    -1,    -1,    -1,
     369,    -1,   371,    29,   373,    -1,    -1,    -1,    -1,   342,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,   354,    -1,    -1,    -1,    51,    -1,   360,   361,    -1,
     363,    -1,    -1,    -1,    -1,    -1,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,   257,    -1,     3,     4,     5,
       6,    -1,     8,     9,     3,     4,     5,     6,   270,     8,
       9,    -1,    -1,    -1,    -1,   277,   340,   341,   342,    52,
      -1,    -1,    28,    29,    -1,    31,    32,    -1,    -1,    -1,
      29,    37,    38,    39,    40,    41,    42,    -1,    37,    38,
      39,    40,    41,    42,    -1,    51,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,   328,    73,    74,    75,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,     3,     4,     5,     6,   347,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    -1,     0,    -1,    -1,     3,    -1,    -1,    -1,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      28,    73,    74,    75,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,     3,     4,     5,     6,    -1,     8,
       9,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    38,    -1,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
       3,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    29,    -1,    31,
      32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,     3,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    29,     3,     4,     5,
       6,    34,     8,     9,    37,    38,    39,    40,    41,    42,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    29,     3,     4,
       5,     6,    -1,     8,     9,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    89,   116,   117,   118,   119,   122,   123,   124,
     125,   131,   134,   138,   157,   158,   159,   160,   117,   122,
     134,    31,    89,    29,    38,    51,    89,    91,   120,   121,
     135,   136,   137,    91,   120,   135,   117,   119,   117,    31,
      89,   117,    89,   134,     0,   158,   120,    89,   132,   133,
      31,   135,   134,   137,   138,    36,    91,    31,    52,    91,
     150,    29,    33,   136,    91,   123,   126,   127,   128,   134,
      31,    91,    52,    32,    36,    93,   132,    30,    92,   137,
     121,     4,     5,     6,     8,     9,    29,    37,    38,    39,
      40,    41,    42,    73,    74,    75,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    89,    90,    91,    93,    95,
      96,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   114,   116,   117,   148,
     149,   150,   151,   152,   153,   154,   155,   156,    31,    89,
     112,   146,    89,    92,   117,   139,   140,   141,   142,    34,
      94,    98,   111,   115,   128,    93,   127,    50,   129,   130,
     135,   128,   126,   115,   133,    93,    29,    98,    29,    98,
      98,   114,   128,   143,   115,    50,    29,    29,    29,   116,
     148,    29,    89,    91,    91,    91,   114,    29,    50,     7,
       8,     9,    29,    33,    35,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    52,   113,   100,    38,    43,
      44,    39,    40,    10,    11,    12,    13,    45,    46,    14,
      15,    37,    47,    48,    16,    17,    49,    36,    91,    93,
     116,   152,    93,   148,   146,   147,    29,    33,   135,   137,
     144,   145,    92,    36,    36,    92,    94,   115,    36,    91,
      50,    93,   143,    92,    29,   137,   144,    92,    50,   148,
     114,   114,   114,    78,    89,   116,   153,    91,    91,   114,
     148,    89,    92,    97,   112,   114,    89,   112,   100,   100,
     100,   101,   101,   102,   102,   103,   103,   103,   103,   104,
     104,   105,   106,   107,   108,   109,   114,   112,    93,    36,
      93,    92,   139,   144,    94,   115,   145,    29,    33,    72,
     141,    89,   130,   115,    92,   100,   148,    92,    92,    92,
      29,   153,   153,    92,    36,    92,    94,    50,    93,   146,
      92,    92,    94,    92,   139,    94,   115,   148,   148,   148,
     114,   114,    92,   114,   148,   112,   111,    92,    94,    76,
      92,    92,   148,    92,   148,    91,   148,   148
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    91,    92,    93,    94,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    98,    98,    99,    99,
      99,    99,    99,    99,   100,   100,   101,   101,   101,   101,
     102,   102,   102,   103,   103,   103,   104,   104,   104,   104,
     104,   105,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   114,
     114,   115,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   122,   122,   122,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   124,
     125,   125,   126,   126,   127,   128,   128,   128,   128,   129,
     129,   130,   130,   130,   131,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   141,   142,   142,   143,   143,   144,
     144,   144,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   146,   146,   146,   147,   147,   148,   148,   148,   148,
     148,   148,   148,   149,   149,   149,   150,   150,   150,   150,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   155,
     155,   155,   155,   155,   155,   156,   156,   156,   156,   156,
     157,   157,   158,   158,   158,   159,   160
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     4,     3,     4,     3,     3,     2,     2,
       1,     3,     1,     2,     2,     2,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     3,     2,     3,     4,     1,     2,     1,
       2,     1,     2,     2,     1,     2,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
#line 220 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1810 "parser.tab.c"
    break;

  case 3: /* constant: CONSTANT  */
#line 234 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1819 "parser.tab.c"
    break;

  case 4: /* semi_colon: SEMI_COLON  */
#line 248 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1828 "parser.tab.c"
    break;

  case 5: /* rparen: RPAREN  */
#line 262 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1837 "parser.tab.c"
    break;

  case 6: /* rcurly: RCURLY  */
#line 276 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1846 "parser.tab.c"
    break;

  case 7: /* rsquare: RSQUARE  */
#line 290 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1855 "parser.tab.c"
    break;

  case 8: /* primary_expression: identifier  */
#line 309 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].astNode));
        }
#line 1864 "parser.tab.c"
    break;

  case 9: /* primary_expression: constant  */
#line 314 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].astNode));
        }
#line 1873 "parser.tab.c"
    break;

  case 10: /* primary_expression: STRING_LITERAL  */
#line 319 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1882 "parser.tab.c"
    break;

  case 11: /* primary_expression: LPAREN expression rparen  */
#line 324 "parser.y"
        {   
            // Parenthesis are not part of the AST
            LINE
            (yyval.astNode) = (yyvsp[-1].astNode);
        }
#line 1892 "parser.tab.c"
    break;

  case 12: /* postfix_expression: primary_expression  */
#line 333 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 1901 "parser.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression LSQUARE expression rsquare  */
#line 338 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("ArrayAccess");
    }
#line 1910 "parser.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression LPAREN rparen  */
#line 343 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Call");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        PARSER_TABLE.push_back({(yyvsp[-2].astNode)->position, {(yyvsp[-2].astNode)->value, "function call"}});
    }
#line 1921 "parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LPAREN argument_expression_list rparen  */
#line 350 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Call");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        PARSER_TABLE.push_back({(yyvsp[-3].astNode)->position, {(yyvsp[-3].astNode)->value, "function call"}});
    }
#line 1933 "parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression DOT identifier  */
#line 358 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Member Access");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 1944 "parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression PTR_OP identifier  */
#line 365 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Pointer Member Access");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        // $$->addChild(new ASTNode($3->position, "Identifier", $3->value));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 1956 "parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression INC_OP  */
#line 373 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PostIncrement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 1966 "parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression DEC_OP  */
#line 379 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PostDecrement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 1976 "parser.tab.c"
    break;

  case 20: /* argument_expression_list: assignment_expression  */
#line 388 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Argument List");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 1986 "parser.tab.c"
    break;

  case 21: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 394 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 1996 "parser.tab.c"
    break;

  case 22: /* unary_expression: postfix_expression  */
#line 403 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2005 "parser.tab.c"
    break;

  case 23: /* unary_expression: INC_OP unary_expression  */
#line 408 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PreIncrement");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2015 "parser.tab.c"
    break;

  case 24: /* unary_expression: DEC_OP unary_expression  */
#line 414 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("PreDecrement");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2025 "parser.tab.c"
    break;

  case 25: /* unary_expression: unary_operator cast_expression  */
#line 420 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("UnaryOperation",(yyvsp[-1].astNode)->value,(yyvsp[-1].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2035 "parser.tab.c"
    break;

  case 26: /* unary_expression: SIZEOF unary_expression  */
#line 426 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("SizeofExpr");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2045 "parser.tab.c"
    break;

  case 27: /* unary_expression: SIZEOF LPAREN type_name rparen  */
#line 432 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("SizeofType");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2055 "parser.tab.c"
    break;

  case 28: /* unary_operator: BIT_AND  */
#line 442 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2064 "parser.tab.c"
    break;

  case 29: /* unary_operator: STAR  */
#line 447 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2073 "parser.tab.c"
    break;

  case 30: /* unary_operator: PLUS  */
#line 452 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2082 "parser.tab.c"
    break;

  case 31: /* unary_operator: MINUS  */
#line 457 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2091 "parser.tab.c"
    break;

  case 32: /* unary_operator: BIT_NOT  */
#line 462 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2100 "parser.tab.c"
    break;

  case 33: /* unary_operator: NOT_OP  */
#line 467 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr)); 
    }
#line 2109 "parser.tab.c"
    break;

  case 34: /* cast_expression: unary_expression  */
#line 475 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2118 "parser.tab.c"
    break;

  case 35: /* cast_expression: LPAREN type_name rparen cast_expression  */
#line 480 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("TypeCast");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2129 "parser.tab.c"
    break;

  case 36: /* multiplicative_expression: cast_expression  */
#line 491 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2138 "parser.tab.c"
    break;

  case 37: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 496 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Multiplication", "*", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2149 "parser.tab.c"
    break;

  case 38: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 503 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Division", "/", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2160 "parser.tab.c"
    break;

  case 39: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 510 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Modulus", "%", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2171 "parser.tab.c"
    break;

  case 40: /* additive_expression: multiplicative_expression  */
#line 520 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2180 "parser.tab.c"
    break;

  case 41: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 525 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Addition", "+", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2191 "parser.tab.c"
    break;

  case 42: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 532 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Subtraction", "-", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2202 "parser.tab.c"
    break;

  case 43: /* shift_expression: additive_expression  */
#line 542 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2211 "parser.tab.c"
    break;

  case 44: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 547 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LeftShift", "<<", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2222 "parser.tab.c"
    break;

  case 45: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 554 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("RightShift", ">>", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2233 "parser.tab.c"
    break;

  case 46: /* relational_expression: shift_expression  */
#line 564 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2242 "parser.tab.c"
    break;

  case 47: /* relational_expression: relational_expression LESSER_OP shift_expression  */
#line 569 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Lesser", "<", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2253 "parser.tab.c"
    break;

  case 48: /* relational_expression: relational_expression GREATER_OP shift_expression  */
#line 576 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Greater", ">", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2264 "parser.tab.c"
    break;

  case 49: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 583 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LesserEqual", "<=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2275 "parser.tab.c"
    break;

  case 50: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 590 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("GreaterEqual", ">=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2286 "parser.tab.c"
    break;

  case 51: /* equality_expression: relational_expression  */
#line 600 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2295 "parser.tab.c"
    break;

  case 52: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 605 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Equal", "==", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2306 "parser.tab.c"
    break;

  case 53: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 612 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("NotEqual", "!=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2317 "parser.tab.c"
    break;

  case 54: /* and_expression: equality_expression  */
#line 622 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2326 "parser.tab.c"
    break;

  case 55: /* and_expression: and_expression BIT_AND equality_expression  */
#line 627 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("BitwiseAnd", "&", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2337 "parser.tab.c"
    break;

  case 56: /* exclusive_or_expression: and_expression  */
#line 637 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2346 "parser.tab.c"
    break;

  case 57: /* exclusive_or_expression: exclusive_or_expression XOR and_expression  */
#line 642 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("BitwiseXor", "^", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2357 "parser.tab.c"
    break;

  case 58: /* inclusive_or_expression: exclusive_or_expression  */
#line 652 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2366 "parser.tab.c"
    break;

  case 59: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 657 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("BitwiseOr", "|", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2377 "parser.tab.c"
    break;

  case 60: /* logical_and_expression: inclusive_or_expression  */
#line 667 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2386 "parser.tab.c"
    break;

  case 61: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 672 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LogicalAnd", "&&", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2397 "parser.tab.c"
    break;

  case 62: /* logical_or_expression: logical_and_expression  */
#line 682 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2406 "parser.tab.c"
    break;

  case 63: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 687 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("LogicalOr", "||", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2417 "parser.tab.c"
    break;

  case 64: /* conditional_expression: logical_or_expression  */
#line 697 "parser.y"
    { 
        LINE  
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2426 "parser.tab.c"
    break;

  case 65: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 702 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Conditional_Expression"); 
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2438 "parser.tab.c"
    break;

  case 66: /* assignment_expression: conditional_expression  */
#line 713 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2447 "parser.tab.c"
    break;

  case 67: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 718 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("AssignmentExpression", (yyvsp[-1].astNode)->value, (yyvsp[-1].astNode)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2458 "parser.tab.c"
    break;

  case 68: /* assignment_operator: ASSIGN  */
#line 728 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2467 "parser.tab.c"
    break;

  case 69: /* assignment_operator: MUL_ASSIGN  */
#line 733 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2476 "parser.tab.c"
    break;

  case 70: /* assignment_operator: DIV_ASSIGN  */
#line 738 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2485 "parser.tab.c"
    break;

  case 71: /* assignment_operator: MOD_ASSIGN  */
#line 743 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2494 "parser.tab.c"
    break;

  case 72: /* assignment_operator: ADD_ASSIGN  */
#line 748 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2503 "parser.tab.c"
    break;

  case 73: /* assignment_operator: SUB_ASSIGN  */
#line 753 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2512 "parser.tab.c"
    break;

  case 74: /* assignment_operator: LEFT_ASSIGN  */
#line 758 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2521 "parser.tab.c"
    break;

  case 75: /* assignment_operator: RIGHT_ASSIGN  */
#line 763 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2530 "parser.tab.c"
    break;

  case 76: /* assignment_operator: AND_ASSIGN  */
#line 768 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2539 "parser.tab.c"
    break;

  case 77: /* assignment_operator: XOR_ASSIGN  */
#line 773 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2548 "parser.tab.c"
    break;

  case 78: /* assignment_operator: OR_ASSIGN  */
#line 778 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
    }
#line 2557 "parser.tab.c"
    break;

  case 79: /* expression: assignment_expression  */
#line 787 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2566 "parser.tab.c"
    break;

  case 80: /* expression: expression COMMA assignment_expression  */
#line 792 "parser.y"
    { 
    LINE
        (yyval.astNode) = new ASTNode("Expression"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2577 "parser.tab.c"
    break;

  case 81: /* constant_expression: conditional_expression  */
#line 801 "parser.y"
                             {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2586 "parser.tab.c"
    break;

  case 82: /* declaration: declaration_specifiers semi_colon  */
#line 809 "parser.y"
    { 
        // This is a forward declaration of a type | 
        /* 
            Example: 
            struct Employee {
                int id;
                char name[20];
            };
            or 
            union Employee {
                int id;
                char name[20];
            };
            or
            struct Employee; // Forward Declaration | 
        */
        LINE 
        (yyval.astNode) = new ASTNode("Definition Of D-Type"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 2611 "parser.tab.c"
    break;

  case 83: /* declaration: declaration_specifiers init_declarator_list semi_colon  */
#line 830 "parser.y"
    {
        // This is a declaration of a variable, it can be on-spot or use of defined type(union/struct)

        /* 
            Example: 
            struct Employee {
                int id;
                char name[20];
            } emp; // On-spot Declaration | 
            or 
            struct Employee emp; // Already Defined structure's use | 
        */

        LINE
        (yyval.astNode) = new ASTNode("Declaration"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Declaration_Handler((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 2635 "parser.tab.c"
    break;

  case 84: /* declaration: typedef_specifiers semi_colon  */
#line 850 "parser.y"
    {
        // This is a typedef declaration
        LINE
        (yyval.astNode) = new ASTNode("Typedef Usage");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2646 "parser.tab.c"
    break;

  case 85: /* declaration: typedef_specifiers init_declarator_list semi_colon  */
#line 857 "parser.y"
    {
        // This is a typedef declaration
        LINE
        (yyval.astNode) = new ASTNode("Typedef Usage");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2658 "parser.tab.c"
    break;

  case 86: /* declaration: TYPEDEF declaration_specifiers init_declarator_list semi_colon  */
#line 865 "parser.y"
    {
        // This is a typedef declaration
        LINE
        (yyval.astNode) = new ASTNode("Typedef Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 2670 "parser.tab.c"
    break;

  case 87: /* declaration_specifiers: storage_class_specifier  */
#line 876 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2679 "parser.tab.c"
    break;

  case 88: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 881 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2689 "parser.tab.c"
    break;

  case 89: /* declaration_specifiers: type_specifier  */
#line 887 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2698 "parser.tab.c"
    break;

  case 90: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 892 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2708 "parser.tab.c"
    break;

  case 91: /* declaration_specifiers: type_qualifier  */
#line 898 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2717 "parser.tab.c"
    break;

  case 92: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 903 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2727 "parser.tab.c"
    break;

  case 93: /* typedef_specifiers: storage_class_specifier typedef_specifiersL2  */
#line 914 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2737 "parser.tab.c"
    break;

  case 94: /* typedef_specifiers: typedef_specifiersL2  */
#line 920 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2746 "parser.tab.c"
    break;

  case 95: /* typedef_specifiersL2: type_qualifier_list identifier  */
#line 928 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild("Typedef D-Type", (yyvsp[0].astNode)->value, (yyvsp[0].astNode)->position);
    }
#line 2756 "parser.tab.c"
    break;

  case 96: /* typedef_specifiersL2: identifier  */
#line 934 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Typedef D-Type", (yyvsp[0].astNode)->value, (yyvsp[0].astNode)->position);
    }
#line 2765 "parser.tab.c"
    break;

  case 97: /* init_declarator_list: init_declarator  */
#line 945 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Initialization or Declaration List", EMPTY_VAL, (yyvsp[0].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2775 "parser.tab.c"
    break;

  case 98: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 951 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2785 "parser.tab.c"
    break;

  case 99: /* init_declarator: declarator  */
#line 961 "parser.y"
    {
        LINE  
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 2794 "parser.tab.c"
    break;

  case 100: /* init_declarator: declarator ASSIGN initializer  */
#line 966 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Initializer", "=", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2805 "parser.tab.c"
    break;

  case 101: /* storage_class_specifier: EXTERN  */
#line 976 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "extern", (yyvsp[0].tokenAtr)->position);
    }
#line 2814 "parser.tab.c"
    break;

  case 102: /* storage_class_specifier: STATIC  */
#line 981 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "static", (yyvsp[0].tokenAtr)->position);
    }
#line 2823 "parser.tab.c"
    break;

  case 103: /* storage_class_specifier: AUTO  */
#line 986 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "auto", (yyvsp[0].tokenAtr)->position);
    }
#line 2832 "parser.tab.c"
    break;

  case 104: /* storage_class_specifier: REGISTER  */
#line 991 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Storage Class Specifier", "register", (yyvsp[0].tokenAtr)->position);
    }
#line 2841 "parser.tab.c"
    break;

  case 105: /* type_specifier: VOID  */
#line 999 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "void", (yyvsp[0].tokenAtr)->position);
    }
#line 2850 "parser.tab.c"
    break;

  case 106: /* type_specifier: CHAR  */
#line 1004 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "char", (yyvsp[0].tokenAtr)->position);
    }
#line 2859 "parser.tab.c"
    break;

  case 107: /* type_specifier: SHORT  */
#line 1009 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "short", (yyvsp[0].tokenAtr)->position);
    }
#line 2868 "parser.tab.c"
    break;

  case 108: /* type_specifier: INT  */
#line 1014 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "int", (yyvsp[0].tokenAtr)->position);
    }
#line 2877 "parser.tab.c"
    break;

  case 109: /* type_specifier: LONG  */
#line 1019 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "long", (yyvsp[0].tokenAtr)->position);
    }
#line 2886 "parser.tab.c"
    break;

  case 110: /* type_specifier: FLOAT  */
#line 1024 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "float", (yyvsp[0].tokenAtr)->position);
    }
#line 2895 "parser.tab.c"
    break;

  case 111: /* type_specifier: DOUBLE  */
#line 1029 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "double", (yyvsp[0].tokenAtr)->position);
    }
#line 2904 "parser.tab.c"
    break;

  case 112: /* type_specifier: SIGNED  */
#line 1034 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "signed", (yyvsp[0].tokenAtr)->position);
    }
#line 2913 "parser.tab.c"
    break;

  case 113: /* type_specifier: UNSIGNED  */
#line 1039 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Specifier", "unsigned", (yyvsp[0].tokenAtr)->position);
    }
#line 2922 "parser.tab.c"
    break;

  case 114: /* type_specifier: struct_or_union_specifier  */
#line 1044 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2931 "parser.tab.c"
    break;

  case 115: /* type_specifier: enum_specifier  */
#line 1049 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2940 "parser.tab.c"
    break;

  case 116: /* type_specifier: TYPE_NAME  */
#line 1054 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Type Specifier", "TypeName", (yyvsp[0].tokenAtr)->position);
    }
#line 2949 "parser.tab.c"
    break;

  case 117: /* struct_or_union_specifier: struct_or_union identifier LCURLY struct_declaration_list rcurly  */
#line 1068 "parser.y"
    {
        // Here the Struct or Union is a definition can be used on-spot or later
        LINE 
        (yyval.astNode) = (yyvsp[-4].astNode);
        std::string isStruct = (yyvsp[-4].astNode)->value == "struct" ? "structID" : "unionID";
        (yyval.astNode)->addChild(isStruct, (yyvsp[-3].astNode)->value,(yyvsp[-3].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        PARSER_TABLE.push_back({(yyvsp[-3].astNode)->position, {(yyvsp[-3].astNode)->value, (yyvsp[-4].astNode)->value}});
    }
#line 2963 "parser.tab.c"
    break;

  case 118: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list rcurly  */
#line 1078 "parser.y"
    {
        // Here the Struct or Union is a definition without a name, meant to be used on-spot
        LINE 
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
    }
#line 2974 "parser.tab.c"
    break;

  case 119: /* struct_or_union_specifier: struct_or_union identifier  */
#line 1085 "parser.y"
    {
        // This a D-Type
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        std::string isStruct = (yyvsp[-1].astNode)->value == "struct" ? "structID" : "unionID";
        (yyval.astNode)->addChild(isStruct, (yyvsp[0].astNode)->value,(yyvsp[0].astNode)->position);
        PARSER_TABLE.push_back({(yyvsp[0].astNode)->position, {(yyvsp[0].astNode)->value, (yyvsp[-1].astNode)->value}});
    }
#line 2987 "parser.tab.c"
    break;

  case 120: /* struct_or_union: STRUCT  */
#line 1098 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct", "struct", (yyvsp[0].tokenAtr)->position);
    }
#line 2996 "parser.tab.c"
    break;

  case 121: /* struct_or_union: UNION  */
#line 1103 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Union", "union", (yyvsp[0].tokenAtr)->position);
    }
#line 3005 "parser.tab.c"
    break;

  case 122: /* struct_declaration_list: struct_declaration  */
#line 1112 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declaration List");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3015 "parser.tab.c"
    break;

  case 123: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1118 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declaration List");
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3026 "parser.tab.c"
    break;

  case 124: /* struct_declaration: specifier_qualifier_list struct_declarator_list semi_colon  */
#line 1129 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Struct_Union_Declaration_Handler((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 3038 "parser.tab.c"
    break;

  case 125: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1140 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3048 "parser.tab.c"
    break;

  case 126: /* specifier_qualifier_list: type_specifier  */
#line 1146 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3057 "parser.tab.c"
    break;

  case 127: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1151 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3067 "parser.tab.c"
    break;

  case 128: /* specifier_qualifier_list: type_qualifier  */
#line 1157 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3076 "parser.tab.c"
    break;

  case 129: /* struct_declarator_list: struct_declarator  */
#line 1165 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator List");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3086 "parser.tab.c"
    break;

  case 130: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1171 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator List");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3097 "parser.tab.c"
    break;

  case 131: /* struct_declarator: declarator  */
#line 1181 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3106 "parser.tab.c"
    break;

  case 132: /* struct_declarator: COLON constant_expression  */
#line 1186 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator", ":", (yyvsp[-1].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3116 "parser.tab.c"
    break;

  case 133: /* struct_declarator: declarator COLON constant_expression  */
#line 1192 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Struct or Union Declarator", ":", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3127 "parser.tab.c"
    break;

  case 134: /* enum_specifier: ENUM LCURLY enumerator_list rcurly  */
#line 1202 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Specifier", EMPTY_VAL, (yyvsp[-3].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3138 "parser.tab.c"
    break;

  case 135: /* enum_specifier: ENUM identifier LCURLY enumerator_list rcurly  */
#line 1209 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Specifier", EMPTY_VAL, (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild("enumID", (yyvsp[-3].astNode)->value,(yyvsp[-3].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3150 "parser.tab.c"
    break;

  case 136: /* enum_specifier: ENUM identifier  */
#line 1217 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Specifier", EMPTY_VAL); 
        (yyval.astNode)->addChild("enumID", (yyvsp[0].astNode)->value,(yyvsp[0].astNode)->position);
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3161 "parser.tab.c"
    break;

  case 137: /* enumerator_list: enumerator  */
#line 1227 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Enum List");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3171 "parser.tab.c"
    break;

  case 138: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 1233 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Enum List");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3182 "parser.tab.c"
    break;

  case 139: /* enumerator: identifier  */
#line 1243 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Element", (yyvsp[0].astNode)->value, (yyvsp[0].astNode)->position);
    }
#line 3191 "parser.tab.c"
    break;

  case 140: /* enumerator: identifier ASSIGN constant_expression  */
#line 1248 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Enum Assignment",EMPTY_VAL , (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild("Enum Element", (yyvsp[-2].astNode)->value,(yyvsp[-2].astNode)->position); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3202 "parser.tab.c"
    break;

  case 141: /* type_qualifier: CONST  */
#line 1258 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Qualifier", "const", (yyvsp[0].tokenAtr)->position);
    }
#line 3211 "parser.tab.c"
    break;

  case 142: /* type_qualifier: VOLATILE  */
#line 1263 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Type Qualifier", "volatile", (yyvsp[0].tokenAtr)->position);
    }
#line 3220 "parser.tab.c"
    break;

  case 143: /* declarator: pointer direct_declarator  */
#line 1271 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer Declarator", EMPTY_VAL);
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3231 "parser.tab.c"
    break;

  case 144: /* declarator: direct_declarator  */
#line 1278 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3240 "parser.tab.c"
    break;

  case 145: /* direct_declarator: identifier  */
#line 1286 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode((yyvsp[0].astNode));
    }
#line 3249 "parser.tab.c"
    break;

  case 146: /* direct_declarator: LPAREN declarator rparen  */
#line 1291 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 3258 "parser.tab.c"
    break;

  case 147: /* direct_declarator: direct_declarator LSQUARE constant_expression rsquare  */
#line 1296 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3269 "parser.tab.c"
    break;

  case 148: /* direct_declarator: direct_declarator LSQUARE rsquare  */
#line 1303 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
    }
#line 3279 "parser.tab.c"
    break;

  case 149: /* direct_declarator: direct_declarator LPAREN parameter_type_list rparen  */
#line 1309 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3289 "parser.tab.c"
    break;

  case 150: /* direct_declarator: direct_declarator LPAREN identifier_list rparen  */
#line 1315 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3299 "parser.tab.c"
    break;

  case 151: /* direct_declarator: direct_declarator LPAREN rparen  */
#line 1321 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyvsp[-2].astNode)->addChild("Empty Parameter List", EMPTY_VAL, (yyvsp[-2].astNode)->position);
    }
#line 3309 "parser.tab.c"
    break;

  case 152: /* pointer: STAR  */
#line 1332 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[0].tokenAtr)->position);
    }
#line 3318 "parser.tab.c"
    break;

  case 153: /* pointer: STAR type_qualifier_list  */
#line 1337 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3328 "parser.tab.c"
    break;

  case 154: /* pointer: STAR pointer  */
#line 1343 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[-1].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3338 "parser.tab.c"
    break;

  case 155: /* pointer: STAR type_qualifier_list pointer  */
#line 1349 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Pointer", "*", (yyvsp[-2].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3349 "parser.tab.c"
    break;

  case 156: /* type_qualifier_list: type_qualifier  */
#line 1359 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3358 "parser.tab.c"
    break;

  case 157: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1364 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3368 "parser.tab.c"
    break;

  case 158: /* parameter_type_list: parameter_list  */
#line 1373 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3377 "parser.tab.c"
    break;

  case 159: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1378 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild("Ellipsis", "...", (yyvsp[0].tokenAtr)->position); 
    }
#line 3387 "parser.tab.c"
    break;

  case 160: /* parameter_list: parameter_declaration  */
#line 1387 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Parameter List", EMPTY_VAL);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3397 "parser.tab.c"
    break;

  case 161: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1393 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3407 "parser.tab.c"
    break;

  case 162: /* parameter_declaration: declaration_specifiers declarator  */
#line 1402 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter Declaration", "parameterDeclaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3418 "parser.tab.c"
    break;

  case 163: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1409 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter Declaration", "parameterDeclaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3429 "parser.tab.c"
    break;

  case 164: /* parameter_declaration: declaration_specifiers  */
#line 1416 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter Declaration", "parameterDeclaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3439 "parser.tab.c"
    break;

  case 165: /* identifier_list: identifier  */
#line 1425 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("IdentifierList", "identifierList");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3449 "parser.tab.c"
    break;

  case 166: /* identifier_list: identifier_list COMMA identifier  */
#line 1431 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3459 "parser.tab.c"
    break;

  case 167: /* type_name: specifier_qualifier_list  */
#line 1440 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3468 "parser.tab.c"
    break;

  case 168: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1445 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3478 "parser.tab.c"
    break;

  case 169: /* abstract_declarator: pointer  */
#line 1454 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3487 "parser.tab.c"
    break;

  case 170: /* abstract_declarator: direct_abstract_declarator  */
#line 1459 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3496 "parser.tab.c"
    break;

  case 171: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1464 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3506 "parser.tab.c"
    break;

  case 172: /* direct_abstract_declarator: LPAREN abstract_declarator rparen  */
#line 1473 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);  
    }
#line 3515 "parser.tab.c"
    break;

  case 173: /* direct_abstract_declarator: LSQUARE rsquare  */
#line 1478 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration"); 
    }
#line 3524 "parser.tab.c"
    break;

  case 174: /* direct_abstract_declarator: LSQUARE constant_expression rsquare  */
#line 1483 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Array Declaration");  
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 3534 "parser.tab.c"
    break;

  case 175: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE rsquare  */
#line 1489 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
        (yyval.astNode)->addChild("Array Declaration");  
    }
#line 3544 "parser.tab.c"
    break;

  case 176: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression rsquare  */
#line 1495 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);  
        (yyval.astNode)->addChild(new ASTNode("Array Declaration"));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3555 "parser.tab.c"
    break;

  case 177: /* direct_abstract_declarator: LPAREN rparen  */
#line 1502 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Parameter List", EMPTY_VAL); 
    }
#line 3564 "parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: LPAREN parameter_type_list rparen  */
#line 1507 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode); 
    }
#line 3573 "parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: direct_abstract_declarator LPAREN rparen  */
#line 1512 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild("Parameter List", EMPTY_VAL); 
    }
#line 3583 "parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list rparen  */
#line 1518 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 3593 "parser.tab.c"
    break;

  case 181: /* initializer: assignment_expression  */
#line 1527 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3602 "parser.tab.c"
    break;

  case 182: /* initializer: LCURLY initializer_list rcurly  */
#line 1532 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode); 
    }
#line 3611 "parser.tab.c"
    break;

  case 183: /* initializer: LCURLY initializer_list COMMA rcurly  */
#line 1537 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
    }
#line 3620 "parser.tab.c"
    break;

  case 184: /* initializer_list: initializer  */
#line 1546 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3629 "parser.tab.c"
    break;

  case 185: /* initializer_list: initializer_list COMMA initializer  */
#line 1551 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3639 "parser.tab.c"
    break;

  case 186: /* statement: labeled_statement  */
#line 1560 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3648 "parser.tab.c"
    break;

  case 187: /* statement: compound_statement  */
#line 1565 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3657 "parser.tab.c"
    break;

  case 188: /* statement: expression_statement  */
#line 1570 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3666 "parser.tab.c"
    break;

  case 189: /* statement: selection_statement  */
#line 1575 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3675 "parser.tab.c"
    break;

  case 190: /* statement: iteration_statement  */
#line 1580 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3684 "parser.tab.c"
    break;

  case 191: /* statement: jump_statement  */
#line 1585 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3693 "parser.tab.c"
    break;

  case 192: /* statement: declaration  */
#line 1590 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3702 "parser.tab.c"
    break;

  case 193: /* labeled_statement: identifier COLON statement  */
#line 1599 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Labeled Statement", (yyvsp[-2].astNode)->value, (yyvsp[-2].astNode)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3712 "parser.tab.c"
    break;

  case 194: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1605 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Case Statement", "Case", (yyvsp[-3].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3723 "parser.tab.c"
    break;

  case 195: /* labeled_statement: DEFAULT COLON statement  */
#line 1612 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Default Statement", "Default", (yyvsp[-2].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3733 "parser.tab.c"
    break;

  case 196: /* compound_statement: LCURLY rcurly  */
#line 1621 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
    }
#line 3742 "parser.tab.c"
    break;

  case 197: /* compound_statement: LCURLY statement_list rcurly  */
#line 1626 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
    }
#line 3752 "parser.tab.c"
    break;

  case 198: /* compound_statement: LCURLY declaration_list rcurly  */
#line 1632 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
    }
#line 3762 "parser.tab.c"
    break;

  case 199: /* compound_statement: LCURLY declaration_list statement_list rcurly  */
#line 1638 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Compound Statement", "{  }"); 
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
    }
#line 3773 "parser.tab.c"
    break;

  case 200: /* declaration_list: declaration  */
#line 1648 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 3782 "parser.tab.c"
    break;

  case 201: /* declaration_list: declaration_list declaration  */
#line 1653 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3792 "parser.tab.c"
    break;

  case 202: /* statement_list: statement  */
#line 1662 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Statement List"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3802 "parser.tab.c"
    break;

  case 203: /* statement_list: statement_list statement  */
#line 1668 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3812 "parser.tab.c"
    break;

  case 204: /* expression_statement: semi_colon  */
#line 1677 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Expression Statement", ";"); 
    }
#line 3821 "parser.tab.c"
    break;

  case 205: /* expression_statement: expression semi_colon  */
#line 1682 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
    }
#line 3830 "parser.tab.c"
    break;

  case 206: /* selection_statement: IF LPAREN expression rparen statement  */
#line 1690 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("If Statement", "if", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3841 "parser.tab.c"
    break;

  case 207: /* selection_statement: IF LPAREN expression rparen statement ELSE statement  */
#line 1697 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("If Else Statement", "if-else", (yyvsp[-6].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3853 "parser.tab.c"
    break;

  case 208: /* selection_statement: SWITCH LPAREN expression rparen statement  */
#line 1705 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Switch Statement", "switch", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3864 "parser.tab.c"
    break;

  case 209: /* iteration_statement: WHILE LPAREN expression rparen statement  */
#line 1715 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("While Loop", "while", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3875 "parser.tab.c"
    break;

  case 210: /* iteration_statement: UNTIL LPAREN expression rparen statement  */
#line 1722 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Until Loop", "until", (yyvsp[-4].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3886 "parser.tab.c"
    break;

  case 211: /* iteration_statement: DO statement WHILE LPAREN expression rparen semi_colon  */
#line 1729 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("DoWhile Loop", "do-while", (yyvsp[-6].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-5].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
    }
#line 3897 "parser.tab.c"
    break;

  case 212: /* iteration_statement: FOR LPAREN expression_statement expression_statement rparen statement  */
#line 1736 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("For Loop", "for", (yyvsp[-5].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3909 "parser.tab.c"
    break;

  case 213: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression rparen statement  */
#line 1744 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("For Loop", "for", (yyvsp[-6].tokenAtr)->position);
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3922 "parser.tab.c"
    break;

  case 214: /* iteration_statement: FOR LPAREN declaration expression_statement expression rparen statement  */
#line 1753 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("For Loop", "for", (yyvsp[-6].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3935 "parser.tab.c"
    break;

  case 215: /* jump_statement: GOTO identifier semi_colon  */
#line 1765 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Goto Statement", "goto", (yyvsp[-2].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
    }
#line 3945 "parser.tab.c"
    break;

  case 216: /* jump_statement: CONTINUE semi_colon  */
#line 1771 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Continue Statement", "continue", (yyvsp[-1].tokenAtr)->position);
    }
#line 3954 "parser.tab.c"
    break;

  case 217: /* jump_statement: BREAK semi_colon  */
#line 1776 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Break Statement", "break", (yyvsp[-1].tokenAtr)->position);
    }
#line 3963 "parser.tab.c"
    break;

  case 218: /* jump_statement: RETURN semi_colon  */
#line 1781 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Return Statement", "return", (yyvsp[-1].tokenAtr)->position);
    }
#line 3972 "parser.tab.c"
    break;

  case 219: /* jump_statement: RETURN expression semi_colon  */
#line 1786 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Return Statement", "return", (yyvsp[-2].tokenAtr)->position); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
    }
#line 3982 "parser.tab.c"
    break;

  case 220: /* translation_unit: external_declaration  */
#line 1796 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("Translation Unit", EMPTY_VAL);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        root = (yyval.astNode);
    }
#line 3993 "parser.tab.c"
    break;

  case 221: /* translation_unit: translation_unit external_declaration  */
#line 1803 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4003 "parser.tab.c"
    break;

  case 222: /* external_declaration: function_definition  */
#line 1819 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 4012 "parser.tab.c"
    break;

  case 223: /* external_declaration: declaration  */
#line 1824 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 4021 "parser.tab.c"
    break;

  case 224: /* external_declaration: function_declaration  */
#line 1829 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 4030 "parser.tab.c"
    break;

  case 225: /* function_declaration: declaration_specifiers declarator semi_colon  */
#line 1837 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("Function Declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        Function_Def_Handler((yyvsp[-1].astNode));
    }
#line 4042 "parser.tab.c"
    break;

  case 226: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 1858 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Definition"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        Function_Def_Handler((yyvsp[-1].astNode));
    }
#line 4054 "parser.tab.c"
    break;


#line 4058 "parser.tab.c"

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

#line 1882 "parser.y"



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
        initOutputFile(output_file); // open output file


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

    /* LINE */
    //------------------------ Parsing ------------------------

    yyparse();  // Call BISON's parser
    
    /* LINE */
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
    /* LINE */

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
    /* LINE */
    // MUST PRINT PARSER_LaTeX_TABLE
    std::ofstream LaTeXTable;
    LaTeXTable.open(LaTeXParserTable);
    writeLatexTable(LaTeXTable);
    LaTeXTable.close();
    *output << "\U00002B55 Parser Table (LaTeX) generated as: " << LaTeXParserTable << " can be visualized using LaTeX\n";

    /* LINE */
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
    declarator = declarator->children[0];
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
