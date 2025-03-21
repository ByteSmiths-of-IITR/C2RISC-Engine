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
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>

#include "utility.h"  

#define EMPTY_VAL "!!EMPTY!!"


std::string whereWasILast;

#define TERMINAL_MESSAGE true // if you wish to check if successful parsing from terminal itself

bool TURN_OFF = true; // Turn off the custom error messages

int noOfyyerrorCalls = 0; 

// #define LINE std::cerr<< "Production - " << __LINE__<<std::endl;
#define LINE /**/
// #define LINE1 std::cerr<< __LINE__<<std::endl;
#define LINE1 /**/

#define PARSERLOGHEADER "----------------------------------- PARSER LOG -----------------------------------"
#define LOGFOOTER       "----------------------------------- END OF LOG -----------------------------------"
#define LEXERLOGHEADER  "----------------------------------- LEXER LOG ------------------------------------"
#define BISONLOGHEADER  "----------------------------------- BISON LOG ------------------------------------"

// Global DS 
std::vector<std::pair<std::pair<int,int>, std::pair<std::string, std::string>> > PARSER_TABLE;


// Handler Functions [Removed]
// void Struct_Union_Declaration_Handler(ASTNode* specifierQualifierList, ASTNode* declaratorList);
// void Enum_Declaration_Handler(ASTNode* enumSpecifier);
// void Function_Def_Handler(ASTNode* declarator);
// void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList);


// Utility Functions
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
std::vector<std::string> bisonLOG;

extern std::string lastToken;

bool stopYYERROR = false;

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

    if(TURN_OFF){
        return;
    }

    std::string error = "Syntax Error at line " + std::to_string(yylineno) + " near token: " + lastToken;
    error += " | Error Description: " + msg;
    parserLOG.push_back(error);
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

    // Don't Think will be needed anymore [since we removed the handlerFunctions, which were cause of segFaults]


    *output << "\U0001F6A8 * Input Program failed in the PARSE stage \U0001F6A8" << std::endl;
    *output << "Where was I Last: " << whereWasILast << std::endl;
    *output << std::endl;
    // cerr the log
    *output << ((parserLOG.size() > 0) ? PARSERLOGHEADER : BISONLOGHEADER) << std::endl;
    for (auto& log : parserLOG) {
        *output << log << std::endl;
        // TODO ------------ Handle this [ Not printing the logs of parser ]
        if(parserLOG.size()==0){
            *output << "$(SignalHandler) Syntax Error at line " << yylineno << " near token: " << lastToken << std::endl;
        }
    }
    *output << LOGFOOTER << std::endl;
    *output << std::endl;

    *output << "--- No Further Processing will be done ---" << std::endl;
    closeOutputFile();
    exit(0); // Clean Exit
}


ASTNode *root;

#line 217 "parser.tab.c"

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
  YYSYMBOL_VA_LIST = 69,                   /* VA_LIST  */
  YYSYMBOL_STRUCT = 70,                    /* STRUCT  */
  YYSYMBOL_UNION = 71,                     /* UNION  */
  YYSYMBOL_ENUM = 72,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 73,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 74,                      /* CASE  */
  YYSYMBOL_DEFAULT = 75,                   /* DEFAULT  */
  YYSYMBOL_IF = 76,                        /* IF  */
  YYSYMBOL_ELSE = 77,                      /* ELSE  */
  YYSYMBOL_SWITCH = 78,                    /* SWITCH  */
  YYSYMBOL_WHILE = 79,                     /* WHILE  */
  YYSYMBOL_DO = 80,                        /* DO  */
  YYSYMBOL_FOR = 81,                       /* FOR  */
  YYSYMBOL_GOTO = 82,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 83,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 84,                     /* BREAK  */
  YYSYMBOL_RETURN = 85,                    /* RETURN  */
  YYSYMBOL_UNTIL = 86,                     /* UNTIL  */
  YYSYMBOL_INVALID_TOKEN = 87,             /* INVALID_TOKEN  */
  YYSYMBOL_UNKNOWN_TOKEN = 88,             /* UNKNOWN_TOKEN  */
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_identifier = 90,                /* identifier  */
  YYSYMBOL_91_1 = 91,                      /* $@1  */
  YYSYMBOL_constant = 92,                  /* constant  */
  YYSYMBOL_93_2 = 93,                      /* $@2  */
  YYSYMBOL_semi_colon = 94,                /* semi_colon  */
  YYSYMBOL_95_3 = 95,                      /* $@3  */
  YYSYMBOL_rparen = 96,                    /* rparen  */
  YYSYMBOL_97_4 = 97,                      /* $@4  */
  YYSYMBOL_rcurly = 98,                    /* rcurly  */
  YYSYMBOL_99_5 = 99,                      /* $@5  */
  YYSYMBOL_rsquare = 100,                  /* rsquare  */
  YYSYMBOL_101_6 = 101,                    /* $@6  */
  YYSYMBOL_primary_expression = 102,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 103,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 104, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 105,         /* unary_expression  */
  YYSYMBOL_unary_operator = 106,           /* unary_operator  */
  YYSYMBOL_cast_expression = 107,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 108, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 109,      /* additive_expression  */
  YYSYMBOL_shift_expression = 110,         /* shift_expression  */
  YYSYMBOL_relational_expression = 111,    /* relational_expression  */
  YYSYMBOL_equality_expression = 112,      /* equality_expression  */
  YYSYMBOL_and_expression = 113,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 114,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 115,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 116,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 117,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 118,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 119,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 120,      /* assignment_operator  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_constant_expression = 122,      /* constant_expression  */
  YYSYMBOL_declaration = 123,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 124,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 125,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 126,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 127,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 128,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 129, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 130,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 131,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 132,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 133, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 134,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 135,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 136,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 137,          /* enumerator_list  */
  YYSYMBOL_enumerator = 138,               /* enumerator  */
  YYSYMBOL_type_qualifier = 139,           /* type_qualifier  */
  YYSYMBOL_declarator = 140,               /* declarator  */
  YYSYMBOL_direct_declarator = 141,        /* direct_declarator  */
  YYSYMBOL_pointer = 142,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 143,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 144,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 145,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 146,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 147,          /* identifier_list  */
  YYSYMBOL_type_name = 148,                /* type_name  */
  YYSYMBOL_abstract_declarator = 149,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 150, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 151,              /* initializer  */
  YYSYMBOL_initializer_list = 152,         /* initializer_list  */
  YYSYMBOL_statement = 153,                /* statement  */
  YYSYMBOL_labeled_statement = 154,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 155,       /* compound_statement  */
  YYSYMBOL_declaration_list = 156,         /* declaration_list  */
  YYSYMBOL_statement_list = 157,           /* statement_list  */
  YYSYMBOL_expression_statement = 158,     /* expression_statement  */
  YYSYMBOL_selection_statement = 159,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 160,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 161,           /* jump_statement  */
  YYSYMBOL_translation_unit = 162,         /* translation_unit  */
  YYSYMBOL_external_declaration = 163,     /* external_declaration  */
  YYSYMBOL_function_definition = 164       /* function_definition  */
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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1258

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  233
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  381

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   343


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
      85,    86,    87,    88
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   246,   246,   251,   251,   260,   265,   265,   275,   280,
     280,   292,   297,   297,   307,   312,   312,   322,   327,   327,
     393,   399,   405,   411,   422,   427,   436,   446,   455,   463,
     471,   478,   488,   494,   504,   509,   516,   523,   530,   537,
     549,   554,   559,   564,   569,   574,   582,   587,   600,   605,
     613,   621,   632,   637,   645,   656,   661,   669,   680,   685,
     693,   701,   709,   720,   725,   733,   744,   749,   760,   765,
     776,   781,   792,   797,   808,   813,   824,   829,   842,   847,
     858,   863,   868,   873,   878,   883,   888,   893,   898,   903,
     908,   917,   922,   933,   944,   951,   963,   969,   976,   982,
     989,   995,  1005,  1011,  1021,  1027,  1044,  1050,  1056,  1062,
    1071,  1076,  1081,  1086,  1091,  1096,  1101,  1106,  1111,  1116,
    1121,  1127,  1133,  1142,  1153,  1162,  1173,  1178,  1186,  1192,
    1201,  1213,  1220,  1226,  1233,  1242,  1248,  1258,  1264,  1271,
    1282,  1292,  1303,  1316,  1322,  1332,  1338,  1349,  1355,  1364,
    1371,  1380,  1386,  1394,  1403,  1411,  1420,  1429,  1440,  1446,
    1453,  1460,  1471,  1477,  1486,  1492,  1503,  1509,  1520,  1527,
    1534,  1543,  1549,  1559,  1565,  1575,  1581,  1587,  1597,  1605,
    1612,  1620,  1627,  1635,  1642,  1650,  1657,  1668,  1674,  1682,
    1694,  1700,  1710,  1716,  1722,  1728,  1734,  1740,  1746,  1755,
    1763,  1772,  1783,  1790,  1798,  1806,  1818,  1824,  1834,  1840,
    1849,  1855,  1865,  1875,  1887,  1900,  1910,  1920,  1932,  1943,
    1955,  1970,  1978,  1985,  1992,  1999,  2012,  2019,  2030,  2036,
    2047,  2056,  2066,  2075
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
  "VA_LIST", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE", "DEFAULT",
  "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE",
  "BREAK", "RETURN", "UNTIL", "INVALID_TOKEN", "UNKNOWN_TOKEN", "$accept",
  "identifier", "$@1", "constant", "$@2", "semi_colon", "$@3", "rparen",
  "$@4", "rcurly", "$@5", "rsquare", "$@6", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
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
  "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-170)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     796,  -170,  -170,    62,   -12,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,    63,  -170,    23,  -170,    54,  1036,  1036,
    -170,    64,  -170,  1036,   972,    -8,    68,   397,  -170,  -170,
      32,  -170,  -170,   -12,    79,    80,  -170,  -170,  -170,   120,
     -19,  -170,   927,  -170,  -170,   378,   109,  -170,   469,  -170,
      54,  -170,   972,   815,  1135,    -8,  -170,  -170,  -170,  -170,
     128,  -170,  -170,   103,    66,  -170,    79,  -170,    62,  -170,
    1162,  -170,   972,   378,  1051,  -170,    58,   378,   378,  -170,
    -170,   560,   644,   644,   707,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  1216,   100,   134,   137,   166,   553,   173,    79,
     124,   124,   798,   191,   175,  -170,   226,  -170,  -170,   232,
    -170,   178,   461,  1216,  -170,   146,   198,   229,     7,   227,
     209,   201,   207,   240,    -1,  -170,  -170,    28,  -170,  -170,
    -170,  -170,   469,   469,  -170,  -170,  -170,  -170,   206,  -170,
    -170,  -170,  -170,   132,    32,   225,  -170,   102,  -170,  -170,
    -170,   263,  -170,  -170,   241,  -170,  1216,    79,  -170,    66,
    -170,  1162,  -170,  -170,  -170,  -170,  -170,  -170,  1216,    34,
    -170,   224,  -170,  1051,   707,  -170,  1216,  -170,  -170,   118,
      98,    32,   228,   553,  1216,  1216,  1216,  -170,   204,   637,
     124,  -170,  -170,  -170,    28,  1216,   553,  -170,  -170,    79,
    -170,  -170,  1176,  1216,    79,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  1216,  -170,  1216,  1216,
    1216,  1216,  1216,  1216,  1216,  1216,  1216,  1216,  1216,  1216,
    1216,  1216,  1216,  1216,  1216,  1216,  1216,  1216,  -170,  -170,
    -170,   469,  -170,  -170,   726,  1135,  -170,    48,  -170,   172,
    -170,   860,    79,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
     180,  -170,    58,  -170,  1216,  -170,    32,  -170,   906,   186,
    -170,  1216,   553,  -170,   118,   118,   118,   251,   798,   798,
    -170,  -170,   118,  -170,  -170,  -170,   161,  -170,   105,  -170,
    -170,  -170,  -170,  -170,   146,   146,   198,   198,   229,   229,
     229,   229,     7,     7,   227,   209,   201,   207,   240,    87,
    -170,  -170,  -170,    32,    32,  -170,   241,   172,   991,  1135,
    -170,  -170,  -170,  1121,  -170,  -170,  -170,  -170,  -170,  -170,
     553,   553,   553,  1216,  1216,  1176,   553,  1216,  -170,  -170,
    1216,  -170,  -170,  -170,  -170,    32,  -170,   241,  -170,  -170,
     208,  -170,  -170,   118,   118,   553,   118,  -170,  -170,  -170,
    -170,  -170,   553,   124,   553,  -170,   553,  -170,  -170,  -170,
    -170
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     2,   122,     3,   158,   106,   107,   108,   109,   112,
     113,   114,   115,   118,   119,   116,   117,   147,   148,   111,
     110,   126,   127,     3,   151,     0,   229,     3,    96,    98,
     120,     3,   121,   100,     0,   150,     3,     3,   226,   228,
      12,   162,   160,   159,     3,   142,     4,     8,    94,     0,
       9,   102,   104,    97,    99,     0,   125,   101,     3,   206,
       3,   233,     0,     3,     3,   149,     1,   227,    11,   152,
       0,   163,   161,   145,    15,   143,     3,    10,     3,    95,
       3,   231,     0,   132,    15,   128,     3,   134,     0,     5,
      22,     3,     3,     3,     3,    14,    40,    41,    42,    43,
      44,    45,     3,     0,     0,     0,     0,     3,     0,     3,
       9,     9,     3,     0,    20,    21,     0,   210,   202,     0,
      24,    34,    46,     3,    48,    52,    55,    58,    63,    66,
      68,    70,    72,    74,    76,    78,    91,     9,   198,   208,
     192,   193,     3,     3,   194,   195,   196,   197,   104,   207,
     232,   171,   157,   170,    12,   164,   166,    12,    17,    20,
     154,     0,    46,    93,    18,    13,     3,     3,   140,    15,
     103,     3,   187,   105,   230,   131,   124,   129,     3,     9,
     135,   137,   133,    15,     3,    38,     3,    35,    36,    12,
     173,    12,     0,     3,     3,     3,     3,   198,     0,     3,
       9,   222,   223,   224,     9,     3,     3,     7,    16,     3,
      30,    31,     3,     3,     3,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    80,     3,    37,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,   211,   204,
     198,     3,   203,   209,     3,     3,   168,   175,   169,   176,
     155,     0,     3,   156,    19,   153,   146,   144,   141,   190,
      15,   138,     3,   130,     3,   123,    12,    23,    12,   175,
     174,     3,     3,   201,    12,    12,    12,     0,     3,     3,
     221,   225,    12,   199,    29,    26,    12,    32,    18,    28,
      79,    49,    50,    51,    53,    54,    56,    57,    61,    62,
      59,    60,    64,    65,    67,    69,    71,    73,    75,     0,
      92,   205,   183,    12,    12,   179,    18,   177,    12,     3,
     165,   167,   172,     3,   188,   136,   139,    39,    47,   200,
       3,     3,     3,     3,     3,     3,     3,     3,    27,    25,
       3,   184,   178,   180,   185,    12,   181,    18,   189,   191,
     212,   214,   215,    12,    12,     3,    12,   216,    33,    77,
     186,   182,     3,     9,     3,   218,     3,   213,   217,   220,
     219
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,     0,  -170,  -170,  -170,   -22,  -170,     5,  -170,   -70,
    -170,  -149,  -170,  -170,  -170,  -170,    81,  -170,  -112,    12,
      16,    -6,    31,    47,    50,    52,    49,    51,  -170,   -56,
     -68,  -170,    40,   -52,    22,     6,  -170,   220,  -170,   311,
    -170,  -170,   212,   -71,   -54,  -170,    30,  -170,   230,   136,
     335,    15,   -29,    -2,  -170,   -62,  -170,    43,  -170,   121,
    -143,  -132,  -162,  -170,    17,  -170,    94,   140,   165,  -169,
    -170,  -170,  -170,  -170,   271,  -170
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   159,    25,   115,   116,   117,    49,   322,    70,   118,
     119,   160,   161,   120,   121,   296,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   226,   137,   164,   197,    60,    50,    51,    28,    29,
      30,    31,    84,    85,    86,   179,   180,    32,    74,    75,
      33,    34,    35,    36,    43,   323,   155,   156,   157,   191,
     324,   259,   173,   270,   139,   140,   141,    62,   143,   144,
     145,   146,   147,    37,    38,    39
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,   154,    42,    24,   168,    48,    27,    65,   163,   269,
     258,   227,   172,   177,   176,   265,   245,    78,    40,   235,
     236,    63,    26,    45,    46,    64,     4,    24,    79,   175,
     289,    56,    47,   182,    53,    54,    24,    24,    48,    57,
     190,    72,    52,    27,    73,    69,   163,   280,   246,    -3,
     192,     1,   237,   238,    17,    18,    59,     1,   114,    26,
      24,     1,    68,   151,   247,     1,     1,     1,   152,   153,
     272,     1,   249,   252,    59,   148,    73,   254,    24,    47,
     138,   255,     1,     3,   149,    47,    24,     3,   201,   202,
     203,     3,     4,   148,    44,    55,     4,     3,    95,   268,
       4,   181,   167,   172,   149,    47,   325,   114,   178,   200,
     163,    76,   177,   275,   266,   248,   301,   302,   303,   344,
     345,    77,   163,   247,   198,   327,   271,   278,    61,   165,
     190,   255,    68,    -3,   189,     1,     4,   350,   262,   158,
      88,   247,   114,   114,   297,   162,    81,   327,    68,   349,
     193,   257,   204,    24,   247,   166,   150,   273,   300,   260,
     253,   254,   263,   194,   250,   255,   195,    73,   256,   338,
       4,   359,   185,   187,   188,    47,   174,   353,   290,   320,
     356,   321,   291,   162,   228,   209,   210,   211,   279,   229,
     230,    68,    82,   114,   277,   196,   281,   347,   142,   163,
     334,   328,   199,   326,   162,   329,   114,   212,   371,   294,
     283,   213,    95,   214,   299,   278,   333,   295,   163,   255,
     205,   288,   336,   293,   189,   206,   189,   207,    65,   308,
     309,   310,   311,   208,   284,   285,   286,   231,   232,   233,
     234,   239,   240,   304,   305,   292,   241,   162,   242,   306,
     307,   114,   257,   298,    24,   243,   244,    24,    80,   162,
     153,   261,   332,   358,   264,   172,   355,   153,   253,    40,
     312,   313,    24,   163,   274,   158,   279,   357,   282,   368,
     343,   337,   114,   287,   153,   372,   319,   181,   314,   340,
     341,   342,   315,   317,   369,   316,   318,   346,   170,   339,
     183,   348,   335,   267,   331,   276,   169,   251,    67,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,     0,   351,   352,
       0,     0,     0,   354,   153,     0,   162,     0,     0,    41,
     114,   114,   114,     0,     0,     0,   114,     0,     0,     0,
     365,   378,     0,     0,     0,   162,     0,   360,   361,   362,
     370,     0,   162,   367,     0,   114,    83,     0,   373,   374,
       0,   376,   114,     0,   114,     0,   114,     0,    71,     0,
       0,     0,   375,   363,   364,   366,     0,     0,     0,   377,
      87,   379,     0,   380,    83,    83,     0,    66,    83,    83,
       1,     0,     0,     0,     0,    83,     2,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,    87,    87,
       0,     0,    87,    87,     0,     2,     3,     0,     0,    87,
       0,   162,     0,     0,     0,     4,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     0,     1,    89,    90,    91,     0,    92,    93,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
       0,     0,     0,     0,    83,    83,     0,     2,    94,     0,
      58,    95,     0,     0,     0,     0,    96,    97,    98,    99,
     100,   101,     0,   225,     0,     0,     0,     0,    87,    87,
      47,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,   102,   103,   104,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     1,    89,    90,    91,
       0,    92,    93,     1,    89,    90,    91,     0,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,    94,     0,    58,     0,     0,     0,     0,   184,
      96,    97,    98,    99,   100,   101,     0,    96,    97,    98,
      99,   100,   101,     0,    47,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,     0,   102,   103,   104,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       1,    89,    90,    91,     0,    92,    93,     1,    89,    90,
      91,     0,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,    94,     0,     0,     0,
       0,     0,     0,   186,    96,    97,    98,    99,   100,   101,
       0,    96,    97,    98,    99,   100,   101,     0,    47,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       1,    89,    90,    91,     0,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     0,     2,    94,     0,     0,     0,
       0,     0,     0,     0,    96,    97,    98,    99,   100,   101,
       0,     0,     0,     0,     2,   254,    68,     0,     0,   255,
       0,     0,     0,     0,     4,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     1,
       0,     1,    89,    90,    91,     0,    92,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,     0,     2,     3,     0,    94,     0,     0,
       0,     0,     0,     0,     4,    96,    97,    98,    99,   100,
     101,     0,     0,     2,     0,    68,     0,     0,     0,    47,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,   330,     2,   278,    68,     0,     0,   255,
       0,     0,     0,     0,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     0,     0,    58,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    80,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       2,     0,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,    68,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     1,    89,    90,    91,     0,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     1,    89,
      90,    91,     0,    92,    93,     0,     0,     0,     0,     0,
      94,     0,   171,    95,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,    94,     1,    89,    90,    91,   158,
      92,    93,    96,    97,    98,    99,   100,   101,     0,     1,
      89,    90,    91,     0,    92,    93,     0,     0,     0,     0,
       0,    94,     0,   171,     0,     0,     0,     0,     0,    96,
      97,    98,    99,   100,   101,    94,    68,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,   100,   101,     1,
      89,    90,    91,     0,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
       0,    63,     4,     3,    74,    27,     0,    36,    64,   171,
     153,   123,    80,    84,    84,   164,    17,    36,     3,    12,
      13,    29,     0,    23,     1,    33,    38,    27,    50,    83,
     199,    31,    51,    87,    28,    29,    36,    37,    60,    33,
      94,    43,    27,    37,    44,    40,   102,   190,    49,     1,
     102,     3,    45,    46,    66,    67,    34,     3,    58,    37,
      60,     3,    30,    63,    36,     3,     3,     3,    63,    63,
      36,     3,   142,   143,    52,    60,    76,    29,    78,    51,
      58,    33,     3,    29,    62,    51,    86,    29,   110,   111,
     112,    29,    38,    78,    31,    31,    38,    29,    32,   169,
      38,    86,    36,   171,    82,    51,   255,   107,    50,   109,
     166,    31,   183,   183,   166,   137,   228,   229,   230,   288,
     289,     1,   178,    36,   107,   257,   178,    29,    34,     1,
     184,    33,    30,     1,    94,     3,    38,    50,    36,    34,
      31,    36,   142,   143,   212,    64,    52,   279,    30,   298,
      50,   153,   112,   153,    36,    52,    62,   179,   226,   154,
     143,    29,   157,    29,   142,    33,    29,   167,   153,   281,
      38,   333,    91,    92,    93,    51,    82,   326,   200,   247,
     329,   251,   204,   102,    38,     7,     8,     9,   190,    43,
      44,    30,    52,   193,   189,    29,   191,    36,    58,   255,
     270,    29,    29,   255,   123,    33,   206,    29,   357,   209,
     193,    33,    32,    35,   214,    29,    36,   212,   274,    33,
      29,   199,   274,   206,   184,    50,   186,     1,   257,   235,
     236,   237,   238,     1,   194,   195,   196,    39,    40,    10,
      11,    14,    15,   231,   232,   205,    37,   166,    47,   233,
     234,   251,   254,   213,   254,    48,    16,   257,    52,   178,
     254,    36,   262,   333,     1,   333,   328,   261,   251,   254,
     239,   240,   272,   329,    50,    34,   278,   329,    50,   347,
      29,   276,   282,    79,   278,    77,   246,   272,   241,   284,
     285,   286,   242,   244,   350,   243,   245,   292,    78,   282,
      88,   296,   272,   167,   261,   184,    76,   142,    37,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,    -1,   323,   324,
      -1,    -1,    -1,   328,   328,    -1,   255,    -1,    -1,     4,
     340,   341,   342,    -1,    -1,    -1,   346,    -1,    -1,    -1,
     345,   373,    -1,    -1,    -1,   274,    -1,   340,   341,   342,
     355,    -1,   281,   346,    -1,   365,    55,    -1,   363,   364,
      -1,   366,   372,    -1,   374,    -1,   376,    -1,    43,    -1,
      -1,    -1,   365,   343,   344,   345,    -1,    -1,    -1,   372,
      55,   374,    -1,   376,    83,    84,    -1,     0,    87,    88,
       3,    -1,    -1,    -1,    -1,    94,    28,    -1,    -1,    -1,
     329,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    87,    88,    -1,    28,    29,    -1,    -1,    94,
      -1,   350,    -1,    -1,    -1,    38,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,     3,     4,     5,     6,    -1,     8,     9,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,   183,   184,    -1,    28,    29,    -1,
      31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    -1,    52,    -1,    -1,    -1,    -1,   183,   184,
      51,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    -1,    78,    79,    80,
      81,    82,    83,    84,    85,    86,     3,     4,     5,     6,
      -1,     8,     9,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,    29,
      37,    38,    39,    40,    41,    42,    -1,    37,    38,    39,
      40,    41,    42,    -1,    51,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      -1,    78,    79,    80,    81,    82,    83,    84,    85,    86,
       3,     4,     5,     6,    -1,     8,     9,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    37,    38,    39,    40,    41,    42,
      -1,    37,    38,    39,    40,    41,    42,    -1,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,     3,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    37,    38,    39,    40,    41,
      42,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    51,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    31,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      28,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    29,     3,     4,     5,     6,    34,
       8,     9,    37,    38,    39,    40,    41,    42,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    38,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    90,    91,   123,   124,   127,   128,
     129,   130,   136,   139,   140,   141,   142,   162,   163,   164,
     140,   139,   142,   143,    31,    90,     1,    51,    94,    95,
     125,   126,   140,   124,   124,    31,    90,   124,    31,   123,
     124,   155,   156,    29,    33,   141,     0,   163,    30,    96,
      97,   139,   142,    90,   137,   138,    31,     1,    36,    94,
      52,   155,   156,   128,   131,   132,   133,   139,    31,     4,
       5,     6,     8,     9,    29,    32,    37,    38,    39,    40,
      41,    42,    74,    75,    76,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    90,    92,    93,    94,    98,    99,
     102,   103,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   121,   123,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   140,   123,
     155,    90,    96,   124,   144,   145,   146,   147,    34,    90,
     100,   101,   105,   118,   122,     1,    52,    36,    98,   137,
     126,    31,   119,   151,   155,   133,    98,   132,    50,   134,
     135,   140,   133,   131,    29,   105,    29,   105,   105,   121,
     133,   148,   122,    50,    29,    29,    29,   123,   153,    29,
      90,    94,    94,    94,   121,    29,    50,     1,     1,     7,
       8,     9,    29,    33,    35,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    52,   120,   107,    38,    43,
      44,    39,    40,    10,    11,    12,    13,    45,    46,    14,
      15,    37,    47,    48,    16,    17,    49,    36,    94,    98,
     123,   157,    98,   153,    29,    33,   140,   142,   149,   150,
      96,    36,    36,    96,     1,   100,   122,   138,    98,   151,
     152,   122,    36,    94,    50,    98,   148,    96,    29,   142,
     149,    96,    50,   153,   121,   121,   121,    79,   123,   158,
      94,    94,   121,   153,    90,    96,   104,   119,   121,    90,
     119,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     110,   110,   111,   111,   112,   113,   114,   115,   116,   121,
     119,    98,    96,   144,   149,   100,   122,   150,    29,    33,
      73,   146,    90,    36,    98,   135,   122,    96,   107,   153,
      96,    96,    96,    29,   158,   158,    96,    36,    96,   100,
      50,    96,    96,   100,    96,   144,   100,   122,    98,   151,
     153,   153,   153,   121,   121,    96,   121,   153,   119,   118,
      96,   100,    77,    96,    96,   153,    96,   153,    94,   153,
     153
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    91,    90,    92,    93,    92,    94,    95,
      94,    96,    97,    96,    98,    99,    98,   100,   101,   100,
     102,   102,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   103,   104,   104,   105,   105,   105,   105,   105,   105,
     106,   106,   106,   106,   106,   106,   107,   107,   108,   108,
     108,   108,   109,   109,   109,   110,   110,   110,   111,   111,
     111,   111,   111,   112,   112,   112,   113,   113,   114,   114,
     115,   115,   116,   116,   117,   117,   118,   118,   119,   119,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   121,   121,   122,   123,   123,   124,   124,   124,   124,
     124,   124,   125,   125,   126,   126,   127,   127,   127,   127,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   129,   129,   129,   130,   130,   131,   131,
     132,   133,   133,   133,   133,   134,   134,   135,   135,   135,
     136,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   141,   141,   141,   141,   141,   141,   142,   142,
     142,   142,   143,   143,   144,   144,   145,   145,   146,   146,
     146,   147,   147,   148,   148,   149,   149,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   151,   151,   151,
     152,   152,   153,   153,   153,   153,   153,   153,   153,   154,
     154,   154,   155,   155,   155,   155,   156,   156,   157,   157,
     158,   158,   159,   159,   159,   160,   160,   160,   160,   160,
     160,   161,   161,   161,   161,   161,   162,   162,   163,   163,
     164,   164,   164,   164
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     0,     2,     1,     0,
       2,     1,     0,     2,     1,     0,     2,     1,     0,     2,
       1,     1,     1,     3,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     3,     1,     2,     1,     2,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     1,     1,     1,     2,
       3,     2,     1,     2,     1,     1,     3,     1,     2,     3,
       4,     5,     2,     1,     3,     1,     3,     1,     1,     2,
       1,     1,     3,     4,     3,     4,     4,     3,     1,     2,
       2,     3,     1,     2,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     2,     1,     1,     2,     3,     2,
       3,     3,     4,     2,     3,     3,     4,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     3,     4,     1,     2,     1,     2,
       1,     2,     5,     7,     5,     5,     5,     7,     6,     7,
       7,     3,     2,     2,     2,     3,     1,     2,     1,     1,
       4,     3,     3,     2
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
#line 247 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1849 "parser.tab.c"
    break;

  case 3: /* $@1: %empty  */
#line 251 "parser.y"
      {stopYYERROR=true;}
#line 1855 "parser.tab.c"
    break;

  case 4: /* identifier: $@1 error  */
#line 252 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 Identifier");
            ourError("Expected an ID or Expression");
        }
#line 1865 "parser.tab.c"
    break;

  case 5: /* constant: CONSTANT  */
#line 261 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1874 "parser.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 265 "parser.y"
     {stopYYERROR=true;}
#line 1880 "parser.tab.c"
    break;

  case 7: /* constant: $@2 error  */
#line 266 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 Constant");
            ourError("Expected a Constant or Expression");

        }
#line 1891 "parser.tab.c"
    break;

  case 8: /* semi_colon: SEMI_COLON  */
#line 276 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1900 "parser.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 280 "parser.y"
      {stopYYERROR=true;}
#line 1906 "parser.tab.c"
    break;

  case 10: /* semi_colon: $@3 error  */
#line 281 "parser.y"
        { 
            LINE
            // Program comes here after calling yy error()

            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 SemiColon");
            ourError("Expected a SemiColon");
            
        }
#line 1919 "parser.tab.c"
    break;

  case 11: /* rparen: RPAREN  */
#line 293 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1928 "parser.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 297 "parser.y"
     {stopYYERROR=true;}
#line 1934 "parser.tab.c"
    break;

  case 13: /* rparen: $@4 error  */
#line 298 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RParen");
            ourError("Expected a Right Parenthesis");

        }
#line 1945 "parser.tab.c"
    break;

  case 14: /* rcurly: RCURLY  */
#line 308 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1954 "parser.tab.c"
    break;

  case 15: /* $@5: %empty  */
#line 312 "parser.y"
      {stopYYERROR=true;}
#line 1960 "parser.tab.c"
    break;

  case 16: /* rcurly: $@5 error  */
#line 313 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RCurly");
            ourError("Expected a Right Curly Brace");

        }
#line 1971 "parser.tab.c"
    break;

  case 17: /* rsquare: RSQUARE  */
#line 323 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1980 "parser.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 327 "parser.y"
     {stopYYERROR=true;}
#line 1986 "parser.tab.c"
    break;

  case 19: /* rsquare: $@6 error  */
#line 328 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RSquare");
            ourError("Expected a Right Square Bracket");

        }
#line 1997 "parser.tab.c"
    break;

  case 20: /* primary_expression: identifier  */
#line 394 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2007 "parser.tab.c"
    break;

  case 21: /* primary_expression: constant  */
#line 400 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2017 "parser.tab.c"
    break;

  case 22: /* primary_expression: STRING_LITERAL  */
#line 406 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
        }
#line 2027 "parser.tab.c"
    break;

  case 23: /* primary_expression: LPAREN expression rparen  */
#line 412 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
            (yyval.astNode)->addChild((yyvsp[-1].astNode));
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2039 "parser.tab.c"
    break;

  case 24: /* postfix_expression: primary_expression  */
#line 423 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2048 "parser.tab.c"
    break;

  case 25: /* postfix_expression: postfix_expression LSQUARE expression rsquare  */
#line 428 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2061 "parser.tab.c"
    break;

  case 26: /* postfix_expression: postfix_expression LPAREN rparen  */
#line 437 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        //-
        //PARSER_TABLE.push_back({$1->position, {$1->value, "function call"}});
    }
#line 2075 "parser.tab.c"
    break;

  case 27: /* postfix_expression: postfix_expression LPAREN argument_expression_list rparen  */
#line 447 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2088 "parser.tab.c"
    break;

  case 28: /* postfix_expression: postfix_expression DOT identifier  */
#line 456 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2100 "parser.tab.c"
    break;

  case 29: /* postfix_expression: postfix_expression PTR_OP identifier  */
#line 464 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2112 "parser.tab.c"
    break;

  case 30: /* postfix_expression: postfix_expression INC_OP  */
#line 472 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2123 "parser.tab.c"
    break;

  case 31: /* postfix_expression: postfix_expression DEC_OP  */
#line 479 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2134 "parser.tab.c"
    break;

  case 32: /* argument_expression_list: assignment_expression  */
#line 489 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("argument_expression_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2144 "parser.tab.c"
    break;

  case 33: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 495 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2155 "parser.tab.c"
    break;

  case 34: /* unary_expression: postfix_expression  */
#line 505 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2164 "parser.tab.c"
    break;

  case 35: /* unary_expression: INC_OP unary_expression  */
#line 510 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2175 "parser.tab.c"
    break;

  case 36: /* unary_expression: DEC_OP unary_expression  */
#line 517 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2186 "parser.tab.c"
    break;

  case 37: /* unary_expression: unary_operator cast_expression  */
#line 524 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2197 "parser.tab.c"
    break;

  case 38: /* unary_expression: SIZEOF unary_expression  */
#line 531 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2208 "parser.tab.c"
    break;

  case 39: /* unary_expression: SIZEOF LPAREN type_name rparen  */
#line 538 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2221 "parser.tab.c"
    break;

  case 40: /* unary_operator: BIT_AND  */
#line 550 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2230 "parser.tab.c"
    break;

  case 41: /* unary_operator: STAR  */
#line 555 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2239 "parser.tab.c"
    break;

  case 42: /* unary_operator: PLUS  */
#line 560 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2248 "parser.tab.c"
    break;

  case 43: /* unary_operator: MINUS  */
#line 565 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2257 "parser.tab.c"
    break;

  case 44: /* unary_operator: BIT_NOT  */
#line 570 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2266 "parser.tab.c"
    break;

  case 45: /* unary_operator: NOT_OP  */
#line 575 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2275 "parser.tab.c"
    break;

  case 46: /* cast_expression: unary_expression  */
#line 583 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2284 "parser.tab.c"
    break;

  case 47: /* cast_expression: LPAREN type_name rparen cast_expression  */
#line 588 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("cast_expression");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2297 "parser.tab.c"
    break;

  case 48: /* multiplicative_expression: cast_expression  */
#line 601 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2306 "parser.tab.c"
    break;

  case 49: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 606 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2318 "parser.tab.c"
    break;

  case 50: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 614 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2330 "parser.tab.c"
    break;

  case 51: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 622 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2342 "parser.tab.c"
    break;

  case 52: /* additive_expression: multiplicative_expression  */
#line 633 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2351 "parser.tab.c"
    break;

  case 53: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 638 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2363 "parser.tab.c"
    break;

  case 54: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 646 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2375 "parser.tab.c"
    break;

  case 55: /* shift_expression: additive_expression  */
#line 657 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2384 "parser.tab.c"
    break;

  case 56: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 662 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2396 "parser.tab.c"
    break;

  case 57: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 670 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2408 "parser.tab.c"
    break;

  case 58: /* relational_expression: shift_expression  */
#line 681 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2417 "parser.tab.c"
    break;

  case 59: /* relational_expression: relational_expression LESSER_OP shift_expression  */
#line 686 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2429 "parser.tab.c"
    break;

  case 60: /* relational_expression: relational_expression GREATER_OP shift_expression  */
#line 694 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2441 "parser.tab.c"
    break;

  case 61: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 702 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2453 "parser.tab.c"
    break;

  case 62: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 710 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2465 "parser.tab.c"
    break;

  case 63: /* equality_expression: relational_expression  */
#line 721 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2474 "parser.tab.c"
    break;

  case 64: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 726 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2486 "parser.tab.c"
    break;

  case 65: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 734 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2498 "parser.tab.c"
    break;

  case 66: /* and_expression: equality_expression  */
#line 745 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2507 "parser.tab.c"
    break;

  case 67: /* and_expression: and_expression BIT_AND equality_expression  */
#line 750 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("and_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2519 "parser.tab.c"
    break;

  case 68: /* exclusive_or_expression: and_expression  */
#line 761 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2528 "parser.tab.c"
    break;

  case 69: /* exclusive_or_expression: exclusive_or_expression XOR and_expression  */
#line 766 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("exclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2540 "parser.tab.c"
    break;

  case 70: /* inclusive_or_expression: exclusive_or_expression  */
#line 777 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2549 "parser.tab.c"
    break;

  case 71: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 782 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("inclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2561 "parser.tab.c"
    break;

  case 72: /* logical_and_expression: inclusive_or_expression  */
#line 793 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2570 "parser.tab.c"
    break;

  case 73: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 798 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_and_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2582 "parser.tab.c"
    break;

  case 74: /* logical_or_expression: logical_and_expression  */
#line 809 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2591 "parser.tab.c"
    break;

  case 75: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 814 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2603 "parser.tab.c"
    break;

  case 76: /* conditional_expression: logical_or_expression  */
#line 825 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2612 "parser.tab.c"
    break;

  case 77: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 830 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("conditional_expression");
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2626 "parser.tab.c"
    break;

  case 78: /* assignment_expression: conditional_expression  */
#line 843 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2635 "parser.tab.c"
    break;

  case 79: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 848 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2647 "parser.tab.c"
    break;

  case 80: /* assignment_operator: ASSIGN  */
#line 859 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2656 "parser.tab.c"
    break;

  case 81: /* assignment_operator: MUL_ASSIGN  */
#line 864 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2665 "parser.tab.c"
    break;

  case 82: /* assignment_operator: DIV_ASSIGN  */
#line 869 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2674 "parser.tab.c"
    break;

  case 83: /* assignment_operator: MOD_ASSIGN  */
#line 874 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2683 "parser.tab.c"
    break;

  case 84: /* assignment_operator: ADD_ASSIGN  */
#line 879 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2692 "parser.tab.c"
    break;

  case 85: /* assignment_operator: SUB_ASSIGN  */
#line 884 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2701 "parser.tab.c"
    break;

  case 86: /* assignment_operator: LEFT_ASSIGN  */
#line 889 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2710 "parser.tab.c"
    break;

  case 87: /* assignment_operator: RIGHT_ASSIGN  */
#line 894 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2719 "parser.tab.c"
    break;

  case 88: /* assignment_operator: AND_ASSIGN  */
#line 899 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2728 "parser.tab.c"
    break;

  case 89: /* assignment_operator: XOR_ASSIGN  */
#line 904 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2737 "parser.tab.c"
    break;

  case 90: /* assignment_operator: OR_ASSIGN  */
#line 909 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2746 "parser.tab.c"
    break;

  case 91: /* expression: assignment_expression  */
#line 918 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2755 "parser.tab.c"
    break;

  case 92: /* expression: expression COMMA assignment_expression  */
#line 923 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("expression"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2767 "parser.tab.c"
    break;

  case 93: /* constant_expression: conditional_expression  */
#line 934 "parser.y"
    {
        LINE
        // $$ = new ASTNode("constant_expression");
        // $$->addChild($1);
        // ShortHand
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2779 "parser.tab.c"
    break;

  case 94: /* declaration: declaration_specifiers semi_colon  */
#line 945 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2790 "parser.tab.c"
    break;

  case 95: /* declaration: declaration_specifiers init_declarator_list semi_colon  */
#line 952 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Declaration_Handler($1, $2);
    }
#line 2803 "parser.tab.c"
    break;

  case 96: /* declaration_specifiers: storage_class_specifier  */
#line 964 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2813 "parser.tab.c"
    break;

  case 97: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 970 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2824 "parser.tab.c"
    break;

  case 98: /* declaration_specifiers: type_specifier  */
#line 977 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2834 "parser.tab.c"
    break;

  case 99: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 983 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2845 "parser.tab.c"
    break;

  case 100: /* declaration_specifiers: type_qualifier  */
#line 990 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2855 "parser.tab.c"
    break;

  case 101: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 996 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2866 "parser.tab.c"
    break;

  case 102: /* init_declarator_list: init_declarator  */
#line 1006 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("init_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2876 "parser.tab.c"
    break;

  case 103: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1012 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2887 "parser.tab.c"
    break;

  case 104: /* init_declarator: declarator  */
#line 1022 "parser.y"
    {
        LINE  
        (yyval.astNode) = new ASTNode("init_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2897 "parser.tab.c"
    break;

  case 105: /* init_declarator: declarator ASSIGN initializer  */
#line 1028 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("init_declarator"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2909 "parser.tab.c"
    break;

  case 106: /* storage_class_specifier: EXTERN  */
#line 1045 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2919 "parser.tab.c"
    break;

  case 107: /* storage_class_specifier: STATIC  */
#line 1051 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2929 "parser.tab.c"
    break;

  case 108: /* storage_class_specifier: AUTO  */
#line 1057 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2939 "parser.tab.c"
    break;

  case 109: /* storage_class_specifier: REGISTER  */
#line 1063 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2949 "parser.tab.c"
    break;

  case 110: /* type_specifier: VA_LIST  */
#line 1072 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2958 "parser.tab.c"
    break;

  case 111: /* type_specifier: VOID  */
#line 1077 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2967 "parser.tab.c"
    break;

  case 112: /* type_specifier: CHAR  */
#line 1082 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2976 "parser.tab.c"
    break;

  case 113: /* type_specifier: SHORT  */
#line 1087 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2985 "parser.tab.c"
    break;

  case 114: /* type_specifier: INT  */
#line 1092 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2994 "parser.tab.c"
    break;

  case 115: /* type_specifier: LONG  */
#line 1097 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3003 "parser.tab.c"
    break;

  case 116: /* type_specifier: FLOAT  */
#line 1102 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3012 "parser.tab.c"
    break;

  case 117: /* type_specifier: DOUBLE  */
#line 1107 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3021 "parser.tab.c"
    break;

  case 118: /* type_specifier: SIGNED  */
#line 1112 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3030 "parser.tab.c"
    break;

  case 119: /* type_specifier: UNSIGNED  */
#line 1117 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3039 "parser.tab.c"
    break;

  case 120: /* type_specifier: struct_or_union_specifier  */
#line 1122 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3049 "parser.tab.c"
    break;

  case 121: /* type_specifier: enum_specifier  */
#line 1128 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3059 "parser.tab.c"
    break;

  case 122: /* type_specifier: TYPE_NAME  */
#line 1134 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3069 "parser.tab.c"
    break;

  case 123: /* struct_or_union_specifier: struct_or_union identifier LCURLY struct_declaration_list rcurly  */
#line 1143 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-4].astNode));
        (yyval.astNode)->addChild(new ASTNode("struct_UnionID", (yyvsp[-3].astNode)->value));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        PARSER_TABLE.push_back({(yyvsp[-3].astNode)->position, {(yyvsp[-3].astNode)->value, (yyvsp[-4].astNode)->value}});
    }
#line 3084 "parser.tab.c"
    break;

  case 124: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list rcurly  */
#line 1154 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3097 "parser.tab.c"
    break;

  case 125: /* struct_or_union_specifier: struct_or_union identifier  */
#line 1163 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild(new ASTNode("struct_UnionID", (yyvsp[0].astNode)->value));
        PARSER_TABLE.push_back({(yyvsp[0].astNode)->position, {(yyvsp[0].astNode)->value, (yyvsp[-1].astNode)->value}});
    }
#line 3109 "parser.tab.c"
    break;

  case 126: /* struct_or_union: STRUCT  */
#line 1174 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct", "struct");
    }
#line 3118 "parser.tab.c"
    break;

  case 127: /* struct_or_union: UNION  */
#line 1179 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Union", "union");
    }
#line 3127 "parser.tab.c"
    break;

  case 128: /* struct_declaration_list: struct_declaration  */
#line 1187 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3137 "parser.tab.c"
    break;

  case 129: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1193 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3147 "parser.tab.c"
    break;

  case 130: /* struct_declaration: specifier_qualifier_list struct_declarator_list semi_colon  */
#line 1202 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Struct_Union_Declaration_Handler($1, $2);
    }
#line 3160 "parser.tab.c"
    break;

  case 131: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1214 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 3171 "parser.tab.c"
    break;

  case 132: /* specifier_qualifier_list: type_specifier  */
#line 1221 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3181 "parser.tab.c"
    break;

  case 133: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1227 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 3192 "parser.tab.c"
    break;

  case 134: /* specifier_qualifier_list: type_qualifier  */
#line 1234 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3202 "parser.tab.c"
    break;

  case 135: /* struct_declarator_list: struct_declarator  */
#line 1243 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3212 "parser.tab.c"
    break;

  case 136: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1249 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3223 "parser.tab.c"
    break;

  case 137: /* struct_declarator: declarator  */
#line 1259 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3233 "parser.tab.c"
    break;

  case 138: /* struct_declarator: COLON constant_expression  */
#line 1265 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3244 "parser.tab.c"
    break;

  case 139: /* struct_declarator: declarator COLON constant_expression  */
#line 1272 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3256 "parser.tab.c"
    break;

  case 140: /* enum_specifier: ENUM LCURLY enumerator_list rcurly  */
#line 1283 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Enum_Declaration_Handler($$);
    }
#line 3270 "parser.tab.c"
    break;

  case 141: /* enum_specifier: ENUM identifier LCURLY enumerator_list rcurly  */
#line 1293 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Enum_Declaration_Handler($$);
    }
#line 3285 "parser.tab.c"
    break;

  case 142: /* enum_specifier: ENUM identifier  */
#line 1304 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Enum_Declaration_Handler($$);
    }
#line 3297 "parser.tab.c"
    break;

  case 143: /* enumerator_list: enumerator  */
#line 1317 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("enumerator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3307 "parser.tab.c"
    break;

  case 144: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 1323 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3318 "parser.tab.c"
    break;

  case 145: /* enumerator: identifier  */
#line 1333 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3328 "parser.tab.c"
    break;

  case 146: /* enumerator: identifier ASSIGN constant_expression  */
#line 1339 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3340 "parser.tab.c"
    break;

  case 147: /* type_qualifier: CONST  */
#line 1350 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3350 "parser.tab.c"
    break;

  case 148: /* type_qualifier: VOLATILE  */
#line 1356 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3360 "parser.tab.c"
    break;

  case 149: /* declarator: pointer direct_declarator  */
#line 1365 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3371 "parser.tab.c"
    break;

  case 150: /* declarator: direct_declarator  */
#line 1372 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3381 "parser.tab.c"
    break;

  case 151: /* direct_declarator: identifier  */
#line 1381 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3391 "parser.tab.c"
    break;

  case 152: /* direct_declarator: LPAREN declarator rparen  */
#line 1387 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3403 "parser.tab.c"
    break;

  case 153: /* direct_declarator: direct_declarator LSQUARE constant_expression rsquare  */
#line 1395 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3416 "parser.tab.c"
    break;

  case 154: /* direct_declarator: direct_declarator LSQUARE rsquare  */
#line 1404 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3428 "parser.tab.c"
    break;

  case 155: /* direct_declarator: direct_declarator LPAREN parameter_type_list rparen  */
#line 1412 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3441 "parser.tab.c"
    break;

  case 156: /* direct_declarator: direct_declarator LPAREN identifier_list rparen  */
#line 1421 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3454 "parser.tab.c"
    break;

  case 157: /* direct_declarator: direct_declarator LPAREN rparen  */
#line 1430 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3466 "parser.tab.c"
    break;

  case 158: /* pointer: STAR  */
#line 1441 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3476 "parser.tab.c"
    break;

  case 159: /* pointer: STAR type_qualifier_list  */
#line 1447 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3487 "parser.tab.c"
    break;

  case 160: /* pointer: STAR pointer  */
#line 1454 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3498 "parser.tab.c"
    break;

  case 161: /* pointer: STAR type_qualifier_list pointer  */
#line 1461 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3510 "parser.tab.c"
    break;

  case 162: /* type_qualifier_list: type_qualifier  */
#line 1472 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3520 "parser.tab.c"
    break;

  case 163: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1478 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3530 "parser.tab.c"
    break;

  case 164: /* parameter_type_list: parameter_list  */
#line 1487 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3540 "parser.tab.c"
    break;

  case 165: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1493 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3552 "parser.tab.c"
    break;

  case 166: /* parameter_list: parameter_declaration  */
#line 1504 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3562 "parser.tab.c"
    break;

  case 167: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1510 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3573 "parser.tab.c"
    break;

  case 168: /* parameter_declaration: declaration_specifiers declarator  */
#line 1521 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3584 "parser.tab.c"
    break;

  case 169: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1528 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3595 "parser.tab.c"
    break;

  case 170: /* parameter_declaration: declaration_specifiers  */
#line 1535 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3605 "parser.tab.c"
    break;

  case 171: /* identifier_list: identifier  */
#line 1544 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("identifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3615 "parser.tab.c"
    break;

  case 172: /* identifier_list: identifier_list COMMA identifier  */
#line 1550 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3626 "parser.tab.c"
    break;

  case 173: /* type_name: specifier_qualifier_list  */
#line 1560 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3636 "parser.tab.c"
    break;

  case 174: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1566 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3647 "parser.tab.c"
    break;

  case 175: /* abstract_declarator: pointer  */
#line 1576 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3657 "parser.tab.c"
    break;

  case 176: /* abstract_declarator: direct_abstract_declarator  */
#line 1582 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3667 "parser.tab.c"
    break;

  case 177: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1588 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3678 "parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: LPAREN abstract_declarator rparen  */
#line 1598 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3690 "parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: LSQUARE rsquare  */
#line 1606 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3701 "parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: LSQUARE constant_expression rsquare  */
#line 1613 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3713 "parser.tab.c"
    break;

  case 181: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE rsquare  */
#line 1621 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3724 "parser.tab.c"
    break;

  case 182: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression rsquare  */
#line 1628 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);  
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3736 "parser.tab.c"
    break;

  case 183: /* direct_abstract_declarator: LPAREN rparen  */
#line 1636 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3747 "parser.tab.c"
    break;

  case 184: /* direct_abstract_declarator: LPAREN parameter_type_list rparen  */
#line 1643 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3759 "parser.tab.c"
    break;

  case 185: /* direct_abstract_declarator: direct_abstract_declarator LPAREN rparen  */
#line 1651 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3770 "parser.tab.c"
    break;

  case 186: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list rparen  */
#line 1658 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3782 "parser.tab.c"
    break;

  case 187: /* initializer: assignment_expression  */
#line 1669 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3792 "parser.tab.c"
    break;

  case 188: /* initializer: LCURLY initializer_list rcurly  */
#line 1675 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3804 "parser.tab.c"
    break;

  case 189: /* initializer: LCURLY initializer_list COMMA rcurly  */
#line 1683 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3817 "parser.tab.c"
    break;

  case 190: /* initializer_list: initializer  */
#line 1695 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("initializer_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3827 "parser.tab.c"
    break;

  case 191: /* initializer_list: initializer_list COMMA initializer  */
#line 1701 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3838 "parser.tab.c"
    break;

  case 192: /* statement: labeled_statement  */
#line 1711 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3848 "parser.tab.c"
    break;

  case 193: /* statement: compound_statement  */
#line 1717 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3858 "parser.tab.c"
    break;

  case 194: /* statement: expression_statement  */
#line 1723 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3868 "parser.tab.c"
    break;

  case 195: /* statement: selection_statement  */
#line 1729 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3878 "parser.tab.c"
    break;

  case 196: /* statement: iteration_statement  */
#line 1735 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3888 "parser.tab.c"
    break;

  case 197: /* statement: jump_statement  */
#line 1741 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3898 "parser.tab.c"
    break;

  case 198: /* statement: declaration  */
#line 1747 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3908 "parser.tab.c"
    break;

  case 199: /* labeled_statement: identifier COLON statement  */
#line 1756 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3920 "parser.tab.c"
    break;

  case 200: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1764 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3933 "parser.tab.c"
    break;

  case 201: /* labeled_statement: DEFAULT COLON statement  */
#line 1773 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3945 "parser.tab.c"
    break;

  case 202: /* compound_statement: LCURLY rcurly  */
#line 1784 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3956 "parser.tab.c"
    break;

  case 203: /* compound_statement: LCURLY statement_list rcurly  */
#line 1791 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3968 "parser.tab.c"
    break;

  case 204: /* compound_statement: LCURLY declaration_list rcurly  */
#line 1799 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3980 "parser.tab.c"
    break;

  case 205: /* compound_statement: LCURLY declaration_list statement_list rcurly  */
#line 1807 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3993 "parser.tab.c"
    break;

  case 206: /* declaration_list: declaration  */
#line 1819 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4003 "parser.tab.c"
    break;

  case 207: /* declaration_list: declaration_list declaration  */
#line 1825 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4013 "parser.tab.c"
    break;

  case 208: /* statement_list: statement  */
#line 1835 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement_list"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4023 "parser.tab.c"
    break;

  case 209: /* statement_list: statement_list statement  */
#line 1841 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4033 "parser.tab.c"
    break;

  case 210: /* expression_statement: semi_colon  */
#line 1850 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4043 "parser.tab.c"
    break;

  case 211: /* expression_statement: expression semi_colon  */
#line 1856 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4054 "parser.tab.c"
    break;

  case 212: /* selection_statement: IF LPAREN expression rparen statement  */
#line 1866 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4068 "parser.tab.c"
    break;

  case 213: /* selection_statement: IF LPAREN expression rparen statement ELSE statement  */
#line 1876 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-6].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-5].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4084 "parser.tab.c"
    break;

  case 214: /* selection_statement: SWITCH LPAREN expression rparen statement  */
#line 1888 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4098 "parser.tab.c"
    break;

  case 215: /* iteration_statement: WHILE LPAREN expression rparen statement  */
#line 1901 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4112 "parser.tab.c"
    break;

  case 216: /* iteration_statement: UNTIL LPAREN expression rparen statement  */
#line 1911 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4126 "parser.tab.c"
    break;

  case 217: /* iteration_statement: DO statement WHILE LPAREN expression rparen semi_colon  */
#line 1921 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-6].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-5].astNode));
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr)); 
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4142 "parser.tab.c"
    break;

  case 218: /* iteration_statement: FOR LPAREN expression_statement expression_statement rparen statement  */
#line 1933 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-5].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4157 "parser.tab.c"
    break;

  case 219: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression rparen statement  */
#line 1944 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-6].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-5].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4173 "parser.tab.c"
    break;

  case 220: /* iteration_statement: FOR LPAREN declaration expression_statement expression rparen statement  */
#line 1956 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-6].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-5].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4189 "parser.tab.c"
    break;

  case 221: /* jump_statement: GOTO identifier semi_colon  */
#line 1971 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4201 "parser.tab.c"
    break;

  case 222: /* jump_statement: CONTINUE semi_colon  */
#line 1979 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4212 "parser.tab.c"
    break;

  case 223: /* jump_statement: BREAK semi_colon  */
#line 1986 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4223 "parser.tab.c"
    break;

  case 224: /* jump_statement: RETURN semi_colon  */
#line 1993 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4234 "parser.tab.c"
    break;

  case 225: /* jump_statement: RETURN expression semi_colon  */
#line 2000 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4246 "parser.tab.c"
    break;

  case 226: /* translation_unit: external_declaration  */
#line 2013 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("translation_unit");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        root = (yyval.astNode);
    }
#line 4257 "parser.tab.c"
    break;

  case 227: /* translation_unit: translation_unit external_declaration  */
#line 2020 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        root = (yyval.astNode);
    }
#line 4268 "parser.tab.c"
    break;

  case 228: /* external_declaration: function_definition  */
#line 2031 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4278 "parser.tab.c"
    break;

  case 229: /* external_declaration: declaration  */
#line 2037 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4288 "parser.tab.c"
    break;

  case 230: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 2048 "parser.y"
    { 
        LINE  
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4300 "parser.tab.c"
    break;

  case 231: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 2057 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        // Function_Def_Handler($2);
    }
#line 4313 "parser.tab.c"
    break;

  case 232: /* function_definition: declarator declaration_list compound_statement  */
#line 2067 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4325 "parser.tab.c"
    break;

  case 233: /* function_definition: declarator compound_statement  */
#line 2076 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4336 "parser.tab.c"
    break;


#line 4340 "parser.tab.c"

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

#line 2084 "parser.y"



// main function

int main(int argc, char **argv) {
    whereWasILast = "main";

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
                std::cerr << "This feature is Removed\n";
                return 0;
                /* parser_table_flag = true; */
                
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
    bool bisonError = (bisonLOG.size() > 0);

    bool syntaxError = parseError || lexerFailed || bisonError;

    if(lexerFailed){
        *output << "\U0001F6A8 Input Program failed in Lexical Analysis Phase \U0001F6A8\n" << std::endl;
        if(TERMINAL_MESSAGE){
            std::cout << "\U0001F6A8 Input Program failed in Lexical Analysis Phase \U0001F6A8" << std::endl;
        }
        
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

    if(syntaxError){
        *output << "\U0001F6A8 Input Program failed in Syntax Analysis Phase \U0001F6A8\n" << std::endl;
        
        *output << "\U0001F6A8 yyerror() was called " << noOfyyerrorCalls << " times \U0001F6A8\n" << std::endl;

        if(TERMINAL_MESSAGE){
            std::cout << "\U0001F6A8 Input Program failed in Syntax Analysis Phase \U0001F6A8" << std::endl;
        }

        // We print ourCustom Error Only if Bison-don't Report any Error

        if(parseError && !TURN_OFF){
            *output << PARSERLOGHEADER << std::endl;
            for(auto log : parserLOG){
                *output << log << std::endl;
            }

            *output << LOGFOOTER << std::endl;
            *output << std::endl;
        }
        
        if(bisonError){
            *output << BISONLOGHEADER << std::endl;
            for(auto log : bisonLOG){
                *output << log << std::endl;
            }
            *output << LOGFOOTER << std::endl;
        }
        
        *output << std::endl;

        if(!bisonError){
            *output << "----No Further Processing----\n";

        // If we only have custom error - i.e no bison error then we can print the AST
            // Clean Up
            fclose(yyin);
            closeOutputFile();
            return 0; // For now even if there is a syntax error, we will continue to print the AST
        }
    }
    LINE

    // Success message
    
    if(!syntaxError){
        *output << "\U0001F44D Input Program passed Syntax Analysis Phase \U0001F44D\n" << std::endl;

        if(TERMINAL_MESSAGE){
            std::cout << "\U0001F44D Input Program passed Syntax Analysis Phase \U0001F44D" << std::endl;
        }
    }
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

    // Removing PARSE_TABLE
    /* // MUST PRINT PARSER_LaTeX_TABLE
    std::ofstream LaTeXTable;
    LaTeXTable.open(LaTeXParserTable);
    writeLatexTable(LaTeXTable);
    LaTeXTable.close();
    *output << "\U00002B55 Parser Table (LaTeX) generated as: " << LaTeXParserTable << " can be visualized using LaTeX\n"; */

    LINE
    //------------------------- Cleanup ------------------------
    if (yyin) fclose(yyin);  // Close the input file if opened
    closeOutputFile();  // Close the output file
    return 0;
}

// Error handling function
void yyerror(const char* s) {
    // We stop Custom Error Handling 
    // add to bison LOG
    noOfyyerrorCalls++;
    if(!TURN_OFF && stopYYERROR) return;

    std::string error = "Syntax Error: " + std::string(s) + " at Line: " + std::to_string(yylineno) + " near Token: " + yytext;
    bisonLOG.push_back(error);
    yyclearin; // Clear the buffer
}

// Handler Functions Removed

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
