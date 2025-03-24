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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  234
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  382

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
     989,   995,  1005,  1011,  1021,  1027,  1038,  1044,  1050,  1056,
    1062,  1071,  1076,  1081,  1086,  1091,  1096,  1101,  1106,  1111,
    1116,  1121,  1127,  1133,  1142,  1153,  1162,  1173,  1178,  1186,
    1192,  1201,  1213,  1220,  1226,  1233,  1242,  1248,  1258,  1264,
    1271,  1282,  1292,  1303,  1316,  1322,  1332,  1338,  1349,  1355,
    1364,  1371,  1380,  1386,  1394,  1403,  1411,  1420,  1429,  1440,
    1446,  1453,  1460,  1471,  1477,  1486,  1492,  1503,  1509,  1520,
    1527,  1534,  1543,  1549,  1559,  1565,  1575,  1581,  1587,  1597,
    1605,  1612,  1620,  1627,  1635,  1642,  1650,  1657,  1668,  1674,
    1682,  1694,  1700,  1710,  1716,  1722,  1728,  1734,  1740,  1746,
    1755,  1763,  1772,  1783,  1790,  1798,  1806,  1818,  1824,  1834,
    1840,  1849,  1855,  1865,  1875,  1887,  1900,  1910,  1920,  1932,
    1943,  1955,  1970,  1978,  1985,  1992,  1999,  2012,  2019,  2030,
    2036,  2047,  2056,  2066,  2075
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

#define YYPACT_NINF (-186)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     835,  -186,  -186,    27,    -4,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,    40,  -186,    20,  -186,     6,  1096,
    1096,  -186,    57,  -186,  1096,  1031,    93,    51,   605,  -186,
    -186,    -7,  -186,  -186,    -4,    28,    44,  -186,  -186,  -186,
      47,    33,  -186,   986,  -186,  -186,   627,    54,  -186,   434,
    -186,     6,  -186,  1031,   880,   760,    93,  -186,  -186,  -186,
    -186,   103,  -186,  -186,    65,   182,  -186,    28,  -186,    27,
    -186,   968,  -186,  1031,   627,   332,  -186,   162,   627,   627,
    -186,  -186,   441,  1173,  1173,   745,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  1180,    46,    90,    98,   100,   518,   158,
      28,    87,    87,   950,   164,   116,  -186,   200,  -186,  -186,
     203,  -186,   291,   511,  1180,  -186,   119,    97,   137,     7,
     232,   159,   170,   174,   214,    19,  -186,  -186,    42,  -186,
    -186,  -186,  -186,   434,   434,  -186,  -186,  -186,  -186,   187,
    -186,  -186,  -186,  -186,   194,    -7,   198,  -186,   109,  -186,
    -186,  -186,   240,  -186,  -186,   210,  -186,  1180,    28,  -186,
     182,  -186,   968,  -186,  -186,  -186,  -186,  -186,  -186,  1180,
      61,  -186,   201,  -186,   332,   745,  -186,  1180,  -186,  -186,
     134,    95,    -7,   209,   518,  1180,  1180,  1180,  -186,   186,
     675,    87,  -186,  -186,  -186,    42,  1180,   518,  -186,  -186,
      28,  -186,  -186,  1166,  1180,    28,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  1180,  -186,  1180,
    1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,
    1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  -186,
    -186,  -186,   434,  -186,  -186,   790,   760,  -186,   228,  -186,
     153,  -186,   858,    28,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,   184,  -186,   162,  -186,  1180,  -186,    -7,  -186,   965,
     195,  -186,  1180,   518,  -186,   134,   134,   134,   249,   950,
     950,  -186,  -186,   134,  -186,  -186,  -186,   148,  -186,   -24,
    -186,  -186,  -186,  -186,  -186,   119,   119,    97,    97,   137,
     137,   137,   137,     7,     7,   232,   159,   170,   174,   214,
      36,  -186,  -186,  -186,    -7,    -7,  -186,   210,   153,  1051,
     760,  -186,  -186,  -186,   607,  -186,  -186,  -186,  -186,  -186,
    -186,   518,   518,   518,  1180,  1180,  1166,   518,  1180,  -186,
    -186,  1180,  -186,  -186,  -186,  -186,    -7,  -186,   210,  -186,
    -186,   205,  -186,  -186,   134,   134,   518,   134,  -186,  -186,
    -186,  -186,  -186,   518,    87,   518,  -186,   518,  -186,  -186,
    -186,  -186
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     2,   123,     3,   159,   106,   107,   108,   109,   110,
     113,   114,   115,   116,   119,   120,   117,   118,   148,   149,
     112,   111,   127,   128,     3,   152,     0,   230,     3,    96,
      98,   121,     3,   122,   100,     0,   151,     3,     3,   227,
     229,    12,   163,   161,   160,     3,   143,     4,     8,    94,
       0,     9,   102,   104,    97,    99,     0,   126,   101,     3,
     207,     3,   234,     0,     3,     3,   150,     1,   228,    11,
     153,     0,   164,   162,   146,    15,   144,     3,    10,     3,
      95,     3,   232,     0,   133,    15,   129,     3,   135,     0,
       5,    22,     3,     3,     3,     3,    14,    40,    41,    42,
      43,    44,    45,     3,     0,     0,     0,     0,     3,     0,
       3,     9,     9,     3,     0,    20,    21,     0,   211,   203,
       0,    24,    34,    46,     3,    48,    52,    55,    58,    63,
      66,    68,    70,    72,    74,    76,    78,    91,     9,   199,
     209,   193,   194,     3,     3,   195,   196,   197,   198,   104,
     208,   233,   172,   158,   171,    12,   165,   167,    12,    17,
      20,   155,     0,    46,    93,    18,    13,     3,     3,   141,
      15,   103,     3,   188,   105,   231,   132,   125,   130,     3,
       9,   136,   138,   134,    15,     3,    38,     3,    35,    36,
      12,   174,    12,     0,     3,     3,     3,     3,   199,     0,
       3,     9,   223,   224,   225,     9,     3,     3,     7,    16,
       3,    30,    31,     3,     3,     3,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    80,     3,    37,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,   212,
     205,   199,     3,   204,   210,     3,     3,   169,   176,   170,
     177,   156,     0,     3,   157,    19,   154,   147,   145,   142,
     191,    15,   139,     3,   131,     3,   124,    12,    23,    12,
     176,   175,     3,     3,   202,    12,    12,    12,     0,     3,
       3,   222,   226,    12,   200,    29,    26,    12,    32,    18,
      28,    79,    49,    50,    51,    53,    54,    56,    57,    61,
      62,    59,    60,    64,    65,    67,    69,    71,    73,    75,
       0,    92,   206,   184,    12,    12,   180,    18,   178,    12,
       3,   166,   168,   173,     3,   189,   137,   140,    39,    47,
     201,     3,     3,     3,     3,     3,     3,     3,     3,    27,
      25,     3,   185,   179,   181,   186,    12,   182,    18,   190,
     192,   213,   215,   216,    12,    12,     3,    12,   217,    33,
      77,   187,   183,     3,     9,     3,   219,     3,   214,   218,
     221,   220
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,     0,  -186,  -186,  -186,   -22,  -186,   -37,  -186,    -9,
    -186,  -150,  -186,  -186,  -186,  -186,   177,  -186,   -57,    52,
      68,    -1,    34,    62,    64,    66,    60,    67,  -186,   -54,
     -67,  -186,   -55,   -85,   150,    17,  -186,   229,  -186,    14,
    -186,  -186,   222,   -77,   -62,  -186,    39,  -186,   237,   147,
     250,    13,   -32,    -2,  -186,   -63,  -186,    55,  -186,   131,
    -141,  -185,  -165,  -186,    12,  -186,    48,   152,   175,  -175,
    -186,  -186,  -186,  -186,   283,  -186
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   160,    26,   116,   117,   118,    50,   323,    71,   119,
     120,   161,   162,   121,   122,   297,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   227,   138,   165,   198,    61,    51,    52,    29,    30,
      31,    32,    85,    86,    87,   180,   181,    33,    75,    76,
      34,    35,    36,    37,    44,   324,   156,   157,   158,   192,
     325,   260,   174,   271,   140,   141,   142,    63,   144,   145,
     146,   147,   148,    38,    39,    40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,   155,    43,    25,    70,    66,    49,   270,   178,     1,
     159,   164,   248,   259,   173,   266,    41,    28,   193,   236,
     237,    47,   176,    69,    46,   290,   183,   153,    25,    80,
       1,     1,    57,   191,     4,     3,   246,    25,    25,    49,
     190,    53,    73,     1,     4,    74,    54,    55,    78,   164,
     281,    58,   238,   239,     1,    28,     3,    48,   205,   115,
       1,    25,    18,    19,   152,     4,   169,   228,   247,    79,
      84,    45,   248,   328,   149,    77,   177,    74,   248,    25,
       3,   154,   267,    62,    48,    89,   351,    25,    56,   202,
     203,   204,   149,    48,   272,   328,   194,   273,    84,    84,
     182,    82,    84,    84,   166,   173,   326,   178,   115,    84,
     201,   151,    48,   164,   345,   346,   249,   167,   261,   195,
     199,   264,    64,   191,   279,   164,    65,   196,   256,   197,
     190,   175,   190,     4,   250,   253,   232,   233,    48,    69,
     285,   286,   287,   115,   115,   263,   298,   234,   235,   350,
      27,   293,   258,   278,    25,   282,   254,   229,   274,   299,
     301,   269,   230,   231,    69,     1,   207,   257,    74,   360,
     248,   327,   302,   303,   304,   276,   296,   354,    69,   291,
     357,   321,   329,   292,   348,    60,   330,   200,    27,   280,
     337,     3,   320,   206,   115,    -3,   242,     1,    84,    84,
       4,   208,   164,    60,   209,    83,   284,   115,   372,   139,
     295,   143,   179,   150,    96,   300,    96,   243,   168,   294,
     334,   164,   244,   255,   279,   339,    66,   256,   256,    -3,
     245,     1,     4,   150,   262,   309,   310,   311,   312,    81,
     338,   265,   163,   322,   159,   358,   240,   241,   341,   342,
     343,   275,   115,   258,    42,    25,   347,   255,    25,   283,
     349,   256,   335,   333,   254,   288,   356,   173,    41,   186,
     188,   189,   154,    25,   313,   314,   164,   280,   344,   154,
     163,   369,   373,   115,   305,   306,   182,   352,   353,   364,
     365,   367,   355,   251,    72,   340,   154,   370,   210,   211,
     212,   163,   307,   308,   315,   318,    88,   316,   171,   366,
     317,   184,   336,   319,   170,   268,   277,   332,   252,   371,
     213,    68,     0,     0,   214,   359,   215,   374,   375,     0,
     377,     0,     0,     0,    88,    88,     0,     0,    88,    88,
       0,   115,   115,   115,   163,    88,   154,   115,     0,     0,
     289,     0,   379,   361,   362,   363,   163,     0,     0,   368,
       2,     0,     0,     0,    96,     0,   115,     0,     0,     0,
       0,     0,     0,   115,     0,   115,     0,   115,   376,     0,
       0,     0,     0,     0,     0,   378,     0,   380,     0,   381,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   163,    88,    88,     0,     1,    90,    91,
      92,     0,    93,    94,     1,    90,    91,    92,     0,    93,
      94,     0,   163,     0,     0,     0,     0,     0,     0,   163,
       0,     0,     2,    95,     0,    59,    96,     0,     0,     0,
     185,    97,    98,    99,   100,   101,   102,     0,    97,    98,
      99,   100,   101,   102,     0,    48,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   163,   103,   104,
     105,     0,   106,   107,   108,   109,   110,   111,   112,   113,
     114,     1,    90,    91,    92,     0,    93,    94,   163,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
       0,     0,     0,     0,     0,     0,     2,    95,     0,    59,
       0,     0,     0,     0,     0,    97,    98,    99,   100,   101,
     102,     0,     0,   226,     0,     0,     0,     0,     0,    48,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,   103,   104,   105,     0,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    67,     0,     0,     1,     0,
       1,    90,    91,    92,     0,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     0,    95,     0,   172,    96,
       0,     0,     0,     4,    97,    98,    99,   100,   101,   102,
       0,     0,     0,     0,     0,     2,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     1,    90,
      91,    92,     0,    93,    94,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     2,    95,     0,     0,     0,     0,     0,
       0,     0,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     1,    90,
      91,    92,     0,    93,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     1,    90,    91,    92,     0,    93,    94,
       0,     0,     0,     2,    95,     0,     0,     0,     0,     0,
       0,     0,    97,    98,    99,   100,   101,   102,     0,    95,
       0,     0,     0,     1,   159,     0,     0,    97,    98,    99,
     100,   101,   102,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     2,   255,
      69,     0,     0,   256,     0,     0,     0,     0,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     2,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     2,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     2,     0,
      69,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,   331,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     1,    90,    91,    92,     0,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,    90,    91,    92,     0,    93,    94,     0,    95,
       0,     0,     0,     0,     0,     0,     0,    97,    98,    99,
     100,   101,   102,     2,   279,    69,     0,    95,   256,   172,
       0,    48,     0,     4,     0,    97,    98,    99,   100,   101,
     102,     0,     0,     0,     2,     0,     0,    59,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    81,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     2,
       0,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,    69,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     1,
      90,    91,    92,     0,    93,    94,     1,    90,    91,    92,
       0,    93,    94,     1,    90,    91,    92,     0,    93,    94,
       0,     0,     0,     0,     0,    95,    69,     0,     0,     0,
       0,     0,   187,    97,    98,    99,   100,   101,   102,    95,
      97,    98,    99,   100,   101,   102,     0,    97,    98,    99,
     100,   101,   102
};

static const yytype_int16 yycheck[] =
{
       0,    64,     4,     3,    41,    37,    28,   172,    85,     3,
      34,    65,    36,   154,    81,   165,     3,     0,   103,    12,
      13,     1,    84,    30,    24,   200,    88,    64,    28,    51,
       3,     3,    32,    95,    38,    29,    17,    37,    38,    61,
      95,    28,    44,     3,    38,    45,    29,    30,     1,   103,
     191,    34,    45,    46,     3,    38,    29,    51,   113,    59,
       3,    61,    66,    67,    64,    38,    75,   124,    49,    36,
      56,    31,    36,   258,    61,    31,    85,    77,    36,    79,
      29,    64,   167,    35,    51,    31,    50,    87,    31,   111,
     112,   113,    79,    51,   179,   280,    50,    36,    84,    85,
      87,    53,    88,    89,     1,   172,   256,   184,   108,    95,
     110,    63,    51,   167,   289,   290,   138,    52,   155,    29,
     108,   158,    29,   185,    29,   179,    33,    29,    33,    29,
     185,    83,   187,    38,   143,   144,    39,    40,    51,    30,
     195,   196,   197,   143,   144,    36,   213,    10,    11,   299,
       0,   206,   154,   190,   154,   192,   144,    38,   180,   214,
     227,   170,    43,    44,    30,     3,    50,   154,   168,   334,
      36,   256,   229,   230,   231,   184,   213,   327,    30,   201,
     330,   248,    29,   205,    36,    35,    33,    29,    38,   191,
     275,    29,   247,    29,   194,     1,    37,     3,   184,   185,
      38,     1,   256,    53,     1,    53,   194,   207,   358,    59,
     210,    59,    50,    63,    32,   215,    32,    47,    36,   207,
      36,   275,    48,    29,    29,   282,   258,    33,    33,     1,
      16,     3,    38,    83,    36,   236,   237,   238,   239,    52,
     277,     1,    65,   252,    34,   330,    14,    15,   285,   286,
     287,    50,   252,   255,     4,   255,   293,    29,   258,    50,
     297,    33,   271,   263,   252,    79,   329,   334,   255,    92,
      93,    94,   255,   273,   240,   241,   330,   279,    29,   262,
     103,   348,    77,   283,   232,   233,   273,   324,   325,   344,
     345,   346,   329,   143,    44,   283,   279,   351,     7,     8,
       9,   124,   234,   235,   242,   245,    56,   243,    79,   346,
     244,    89,   273,   246,    77,   168,   185,   262,   143,   356,
      29,    38,    -1,    -1,    33,   334,    35,   364,   365,    -1,
     367,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,
      -1,   341,   342,   343,   167,    95,   329,   347,    -1,    -1,
     200,    -1,   374,   341,   342,   343,   179,    -1,    -1,   347,
      28,    -1,    -1,    -1,    32,    -1,   366,    -1,    -1,    -1,
      -1,    -1,    -1,   373,    -1,   375,    -1,   377,   366,    -1,
      -1,    -1,    -1,    -1,    -1,   373,    -1,   375,    -1,   377,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   256,   184,   185,    -1,     3,     4,     5,
       6,    -1,     8,     9,     3,     4,     5,     6,    -1,     8,
       9,    -1,   275,    -1,    -1,    -1,    -1,    -1,    -1,   282,
      -1,    -1,    28,    29,    -1,    31,    32,    -1,    -1,    -1,
      29,    37,    38,    39,    40,    41,    42,    -1,    37,    38,
      39,    40,    41,    42,    -1,    51,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,   330,    74,    75,
      76,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
      86,     3,     4,     5,     6,    -1,     8,     9,   351,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    -1,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,    -1,    -1,     3,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    29,    -1,    31,    32,
      -1,    -1,    -1,    38,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,     3,     4,
       5,     6,    -1,     8,     9,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    -1,    29,
      -1,    -1,    -1,     3,    34,    -1,    -1,    37,    38,    39,
      40,    41,    42,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    28,    29,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    28,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    28,    -1,
      30,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    28,    29,    30,    -1,    29,    33,    31,
      -1,    51,    -1,    38,    -1,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    28,    -1,    -1,    31,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    28,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,    -1,     8,     9,     3,     4,     5,     6,
      -1,     8,     9,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    29,    37,    38,    39,    40,    41,    42,    29,
      37,    38,    39,    40,    41,    42,    -1,    37,    38,    39,
      40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    38,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    90,    91,   123,   124,   127,
     128,   129,   130,   136,   139,   140,   141,   142,   162,   163,
     164,   140,   139,   142,   143,    31,    90,     1,    51,    94,
      95,   125,   126,   140,   124,   124,    31,    90,   124,    31,
     123,   124,   155,   156,    29,    33,   141,     0,   163,    30,
      96,    97,   139,   142,    90,   137,   138,    31,     1,    36,
      94,    52,   155,   156,   128,   131,   132,   133,   139,    31,
       4,     5,     6,     8,     9,    29,    32,    37,    38,    39,
      40,    41,    42,    74,    75,    76,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    90,    92,    93,    94,    98,
      99,   102,   103,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   121,   123,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   140,
     123,   155,    90,    96,   124,   144,   145,   146,   147,    34,
      90,   100,   101,   105,   118,   122,     1,    52,    36,    98,
     137,   126,    31,   119,   151,   155,   133,    98,   132,    50,
     134,   135,   140,   133,   131,    29,   105,    29,   105,   105,
     121,   133,   148,   122,    50,    29,    29,    29,   123,   153,
      29,    90,    94,    94,    94,   121,    29,    50,     1,     1,
       7,     8,     9,    29,    33,    35,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    52,   120,   107,    38,
      43,    44,    39,    40,    10,    11,    12,    13,    45,    46,
      14,    15,    37,    47,    48,    16,    17,    49,    36,    94,
      98,   123,   157,    98,   153,    29,    33,   140,   142,   149,
     150,    96,    36,    36,    96,     1,   100,   122,   138,    98,
     151,   152,   122,    36,    94,    50,    98,   148,    96,    29,
     142,   149,    96,    50,   153,   121,   121,   121,    79,   123,
     158,    94,    94,   121,   153,    90,    96,   104,   119,   121,
      90,   119,   107,   107,   107,   108,   108,   109,   109,   110,
     110,   110,   110,   111,   111,   112,   113,   114,   115,   116,
     121,   119,    98,    96,   144,   149,   100,   122,   150,    29,
      33,    73,   146,    90,    36,    98,   135,   122,    96,   107,
     153,    96,    96,    96,    29,   158,   158,    96,    36,    96,
     100,    50,    96,    96,   100,    96,   144,   100,   122,    98,
     151,   153,   153,   153,   121,   121,    96,   121,   153,   119,
     118,    96,   100,    77,    96,    96,   153,    96,   153,    94,
     153,   153
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
     127,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   129,   129,   129,   130,   130,   131,
     131,   132,   133,   133,   133,   133,   134,   134,   135,   135,
     135,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   141,   141,   141,   141,   141,   142,
     142,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   146,   147,   147,   148,   148,   149,   149,   149,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   151,   151,
     151,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     154,   154,   154,   155,   155,   155,   155,   156,   156,   157,
     157,   158,   158,   159,   159,   159,   160,   160,   160,   160,
     160,   160,   161,   161,   161,   161,   161,   162,   162,   163,
     163,   164,   164,   164,   164
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
       1,     1,     1,     1,     5,     4,     2,     1,     1,     1,
       2,     3,     2,     1,     2,     1,     1,     3,     1,     2,
       3,     4,     5,     2,     1,     3,     1,     3,     1,     1,
       2,     1,     1,     3,     4,     3,     4,     4,     3,     1,
       2,     2,     3,     1,     2,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     2,     1,     1,     2,     3,
       2,     3,     3,     4,     2,     3,     3,     4,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     3,     3,     4,     1,     2,     1,
       2,     1,     2,     5,     7,     5,     5,     5,     7,     6,
       7,     7,     3,     2,     2,     2,     3,     1,     2,     1,
       1,     4,     3,     3,     2
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
#line 1843 "parser.tab.c"
    break;

  case 3: /* $@1: %empty  */
#line 251 "parser.y"
      {stopYYERROR=true;}
#line 1849 "parser.tab.c"
    break;

  case 4: /* identifier: $@1 error  */
#line 252 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 Identifier");
            ourError("Expected an ID or Expression");
        }
#line 1859 "parser.tab.c"
    break;

  case 5: /* constant: CONSTANT  */
#line 261 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1868 "parser.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 265 "parser.y"
     {stopYYERROR=true;}
#line 1874 "parser.tab.c"
    break;

  case 7: /* constant: $@2 error  */
#line 266 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 Constant");
            ourError("Expected a Constant or Expression");

        }
#line 1885 "parser.tab.c"
    break;

  case 8: /* semi_colon: SEMI_COLON  */
#line 276 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1894 "parser.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 280 "parser.y"
      {stopYYERROR=true;}
#line 1900 "parser.tab.c"
    break;

  case 10: /* semi_colon: $@3 error  */
#line 281 "parser.y"
        { 
            LINE
            // Program comes here after calling yy error()

            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 SemiColon");
            ourError("Expected a SemiColon");
            
        }
#line 1913 "parser.tab.c"
    break;

  case 11: /* rparen: RPAREN  */
#line 293 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1922 "parser.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 297 "parser.y"
     {stopYYERROR=true;}
#line 1928 "parser.tab.c"
    break;

  case 13: /* rparen: $@4 error  */
#line 298 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RParen");
            ourError("Expected a Right Parenthesis");

        }
#line 1939 "parser.tab.c"
    break;

  case 14: /* rcurly: RCURLY  */
#line 308 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1948 "parser.tab.c"
    break;

  case 15: /* $@5: %empty  */
#line 312 "parser.y"
      {stopYYERROR=true;}
#line 1954 "parser.tab.c"
    break;

  case 16: /* rcurly: $@5 error  */
#line 313 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RCurly");
            ourError("Expected a Right Curly Brace");

        }
#line 1965 "parser.tab.c"
    break;

  case 17: /* rsquare: RSQUARE  */
#line 323 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1974 "parser.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 327 "parser.y"
     {stopYYERROR=true;}
#line 1980 "parser.tab.c"
    break;

  case 19: /* rsquare: $@6 error  */
#line 328 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RSquare");
            ourError("Expected a Right Square Bracket");

        }
#line 1991 "parser.tab.c"
    break;

  case 20: /* primary_expression: identifier  */
#line 394 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2001 "parser.tab.c"
    break;

  case 21: /* primary_expression: constant  */
#line 400 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2011 "parser.tab.c"
    break;

  case 22: /* primary_expression: STRING_LITERAL  */
#line 406 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
        }
#line 2021 "parser.tab.c"
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
#line 2033 "parser.tab.c"
    break;

  case 24: /* postfix_expression: primary_expression  */
#line 423 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2042 "parser.tab.c"
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
#line 2055 "parser.tab.c"
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
#line 2069 "parser.tab.c"
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
#line 2082 "parser.tab.c"
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
#line 2094 "parser.tab.c"
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
#line 2106 "parser.tab.c"
    break;

  case 30: /* postfix_expression: postfix_expression INC_OP  */
#line 472 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2117 "parser.tab.c"
    break;

  case 31: /* postfix_expression: postfix_expression DEC_OP  */
#line 479 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2128 "parser.tab.c"
    break;

  case 32: /* argument_expression_list: assignment_expression  */
#line 489 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("argument_expression_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2138 "parser.tab.c"
    break;

  case 33: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 495 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2149 "parser.tab.c"
    break;

  case 34: /* unary_expression: postfix_expression  */
#line 505 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2158 "parser.tab.c"
    break;

  case 35: /* unary_expression: INC_OP unary_expression  */
#line 510 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2169 "parser.tab.c"
    break;

  case 36: /* unary_expression: DEC_OP unary_expression  */
#line 517 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2180 "parser.tab.c"
    break;

  case 37: /* unary_expression: unary_operator cast_expression  */
#line 524 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2191 "parser.tab.c"
    break;

  case 38: /* unary_expression: SIZEOF unary_expression  */
#line 531 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2202 "parser.tab.c"
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
#line 2215 "parser.tab.c"
    break;

  case 40: /* unary_operator: BIT_AND  */
#line 550 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2224 "parser.tab.c"
    break;

  case 41: /* unary_operator: STAR  */
#line 555 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2233 "parser.tab.c"
    break;

  case 42: /* unary_operator: PLUS  */
#line 560 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2242 "parser.tab.c"
    break;

  case 43: /* unary_operator: MINUS  */
#line 565 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2251 "parser.tab.c"
    break;

  case 44: /* unary_operator: BIT_NOT  */
#line 570 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2260 "parser.tab.c"
    break;

  case 45: /* unary_operator: NOT_OP  */
#line 575 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2269 "parser.tab.c"
    break;

  case 46: /* cast_expression: unary_expression  */
#line 583 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2278 "parser.tab.c"
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
#line 2291 "parser.tab.c"
    break;

  case 48: /* multiplicative_expression: cast_expression  */
#line 601 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2300 "parser.tab.c"
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
#line 2312 "parser.tab.c"
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
#line 2324 "parser.tab.c"
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
#line 2336 "parser.tab.c"
    break;

  case 52: /* additive_expression: multiplicative_expression  */
#line 633 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2345 "parser.tab.c"
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
#line 2357 "parser.tab.c"
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
#line 2369 "parser.tab.c"
    break;

  case 55: /* shift_expression: additive_expression  */
#line 657 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2378 "parser.tab.c"
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
#line 2390 "parser.tab.c"
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
#line 2402 "parser.tab.c"
    break;

  case 58: /* relational_expression: shift_expression  */
#line 681 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2411 "parser.tab.c"
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
#line 2423 "parser.tab.c"
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
#line 2435 "parser.tab.c"
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
#line 2447 "parser.tab.c"
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
#line 2459 "parser.tab.c"
    break;

  case 63: /* equality_expression: relational_expression  */
#line 721 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2468 "parser.tab.c"
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
#line 2480 "parser.tab.c"
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
#line 2492 "parser.tab.c"
    break;

  case 66: /* and_expression: equality_expression  */
#line 745 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2501 "parser.tab.c"
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
#line 2513 "parser.tab.c"
    break;

  case 68: /* exclusive_or_expression: and_expression  */
#line 761 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2522 "parser.tab.c"
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
#line 2534 "parser.tab.c"
    break;

  case 70: /* inclusive_or_expression: exclusive_or_expression  */
#line 777 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2543 "parser.tab.c"
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
#line 2555 "parser.tab.c"
    break;

  case 72: /* logical_and_expression: inclusive_or_expression  */
#line 793 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2564 "parser.tab.c"
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
#line 2576 "parser.tab.c"
    break;

  case 74: /* logical_or_expression: logical_and_expression  */
#line 809 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2585 "parser.tab.c"
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
#line 2597 "parser.tab.c"
    break;

  case 76: /* conditional_expression: logical_or_expression  */
#line 825 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2606 "parser.tab.c"
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
#line 2620 "parser.tab.c"
    break;

  case 78: /* assignment_expression: conditional_expression  */
#line 843 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2629 "parser.tab.c"
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
#line 2641 "parser.tab.c"
    break;

  case 80: /* assignment_operator: ASSIGN  */
#line 859 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2650 "parser.tab.c"
    break;

  case 81: /* assignment_operator: MUL_ASSIGN  */
#line 864 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2659 "parser.tab.c"
    break;

  case 82: /* assignment_operator: DIV_ASSIGN  */
#line 869 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2668 "parser.tab.c"
    break;

  case 83: /* assignment_operator: MOD_ASSIGN  */
#line 874 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2677 "parser.tab.c"
    break;

  case 84: /* assignment_operator: ADD_ASSIGN  */
#line 879 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2686 "parser.tab.c"
    break;

  case 85: /* assignment_operator: SUB_ASSIGN  */
#line 884 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2695 "parser.tab.c"
    break;

  case 86: /* assignment_operator: LEFT_ASSIGN  */
#line 889 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2704 "parser.tab.c"
    break;

  case 87: /* assignment_operator: RIGHT_ASSIGN  */
#line 894 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2713 "parser.tab.c"
    break;

  case 88: /* assignment_operator: AND_ASSIGN  */
#line 899 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2722 "parser.tab.c"
    break;

  case 89: /* assignment_operator: XOR_ASSIGN  */
#line 904 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2731 "parser.tab.c"
    break;

  case 90: /* assignment_operator: OR_ASSIGN  */
#line 909 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2740 "parser.tab.c"
    break;

  case 91: /* expression: assignment_expression  */
#line 918 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2749 "parser.tab.c"
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
#line 2761 "parser.tab.c"
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
#line 2773 "parser.tab.c"
    break;

  case 94: /* declaration: declaration_specifiers semi_colon  */
#line 945 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2784 "parser.tab.c"
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
#line 2797 "parser.tab.c"
    break;

  case 96: /* declaration_specifiers: storage_class_specifier  */
#line 964 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2807 "parser.tab.c"
    break;

  case 97: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 970 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2818 "parser.tab.c"
    break;

  case 98: /* declaration_specifiers: type_specifier  */
#line 977 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2828 "parser.tab.c"
    break;

  case 99: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 983 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2839 "parser.tab.c"
    break;

  case 100: /* declaration_specifiers: type_qualifier  */
#line 990 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2849 "parser.tab.c"
    break;

  case 101: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 996 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2860 "parser.tab.c"
    break;

  case 102: /* init_declarator_list: init_declarator  */
#line 1006 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("init_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2870 "parser.tab.c"
    break;

  case 103: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1012 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2881 "parser.tab.c"
    break;

  case 104: /* init_declarator: declarator  */
#line 1022 "parser.y"
    {
        LINE  
        (yyval.astNode) = new ASTNode("init_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2891 "parser.tab.c"
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
#line 2903 "parser.tab.c"
    break;

  case 106: /* storage_class_specifier: TYPEDEF  */
#line 1039 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2913 "parser.tab.c"
    break;

  case 107: /* storage_class_specifier: EXTERN  */
#line 1045 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2923 "parser.tab.c"
    break;

  case 108: /* storage_class_specifier: STATIC  */
#line 1051 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2933 "parser.tab.c"
    break;

  case 109: /* storage_class_specifier: AUTO  */
#line 1057 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2943 "parser.tab.c"
    break;

  case 110: /* storage_class_specifier: REGISTER  */
#line 1063 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2953 "parser.tab.c"
    break;

  case 111: /* type_specifier: VA_LIST  */
#line 1072 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2962 "parser.tab.c"
    break;

  case 112: /* type_specifier: VOID  */
#line 1077 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2971 "parser.tab.c"
    break;

  case 113: /* type_specifier: CHAR  */
#line 1082 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2980 "parser.tab.c"
    break;

  case 114: /* type_specifier: SHORT  */
#line 1087 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2989 "parser.tab.c"
    break;

  case 115: /* type_specifier: INT  */
#line 1092 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2998 "parser.tab.c"
    break;

  case 116: /* type_specifier: LONG  */
#line 1097 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3007 "parser.tab.c"
    break;

  case 117: /* type_specifier: FLOAT  */
#line 1102 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3016 "parser.tab.c"
    break;

  case 118: /* type_specifier: DOUBLE  */
#line 1107 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3025 "parser.tab.c"
    break;

  case 119: /* type_specifier: SIGNED  */
#line 1112 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3034 "parser.tab.c"
    break;

  case 120: /* type_specifier: UNSIGNED  */
#line 1117 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3043 "parser.tab.c"
    break;

  case 121: /* type_specifier: struct_or_union_specifier  */
#line 1122 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3053 "parser.tab.c"
    break;

  case 122: /* type_specifier: enum_specifier  */
#line 1128 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3063 "parser.tab.c"
    break;

  case 123: /* type_specifier: TYPE_NAME  */
#line 1134 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3073 "parser.tab.c"
    break;

  case 124: /* struct_or_union_specifier: struct_or_union identifier LCURLY struct_declaration_list rcurly  */
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
#line 3088 "parser.tab.c"
    break;

  case 125: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list rcurly  */
#line 1154 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3101 "parser.tab.c"
    break;

  case 126: /* struct_or_union_specifier: struct_or_union identifier  */
#line 1163 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild(new ASTNode("struct_UnionID", (yyvsp[0].astNode)->value));
        PARSER_TABLE.push_back({(yyvsp[0].astNode)->position, {(yyvsp[0].astNode)->value, (yyvsp[-1].astNode)->value}});
    }
#line 3113 "parser.tab.c"
    break;

  case 127: /* struct_or_union: STRUCT  */
#line 1174 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct", "struct");
    }
#line 3122 "parser.tab.c"
    break;

  case 128: /* struct_or_union: UNION  */
#line 1179 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Union", "union");
    }
#line 3131 "parser.tab.c"
    break;

  case 129: /* struct_declaration_list: struct_declaration  */
#line 1187 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3141 "parser.tab.c"
    break;

  case 130: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1193 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3151 "parser.tab.c"
    break;

  case 131: /* struct_declaration: specifier_qualifier_list struct_declarator_list semi_colon  */
#line 1202 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Struct_Union_Declaration_Handler($1, $2);
    }
#line 3164 "parser.tab.c"
    break;

  case 132: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1214 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 3175 "parser.tab.c"
    break;

  case 133: /* specifier_qualifier_list: type_specifier  */
#line 1221 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3185 "parser.tab.c"
    break;

  case 134: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1227 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 3196 "parser.tab.c"
    break;

  case 135: /* specifier_qualifier_list: type_qualifier  */
#line 1234 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3206 "parser.tab.c"
    break;

  case 136: /* struct_declarator_list: struct_declarator  */
#line 1243 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3216 "parser.tab.c"
    break;

  case 137: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1249 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3227 "parser.tab.c"
    break;

  case 138: /* struct_declarator: declarator  */
#line 1259 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3237 "parser.tab.c"
    break;

  case 139: /* struct_declarator: COLON constant_expression  */
#line 1265 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3248 "parser.tab.c"
    break;

  case 140: /* struct_declarator: declarator COLON constant_expression  */
#line 1272 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3260 "parser.tab.c"
    break;

  case 141: /* enum_specifier: ENUM LCURLY enumerator_list rcurly  */
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
#line 3274 "parser.tab.c"
    break;

  case 142: /* enum_specifier: ENUM identifier LCURLY enumerator_list rcurly  */
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
#line 3289 "parser.tab.c"
    break;

  case 143: /* enum_specifier: ENUM identifier  */
#line 1304 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Enum_Declaration_Handler($$);
    }
#line 3301 "parser.tab.c"
    break;

  case 144: /* enumerator_list: enumerator  */
#line 1317 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("enumerator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3311 "parser.tab.c"
    break;

  case 145: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 1323 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3322 "parser.tab.c"
    break;

  case 146: /* enumerator: identifier  */
#line 1333 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3332 "parser.tab.c"
    break;

  case 147: /* enumerator: identifier ASSIGN constant_expression  */
#line 1339 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3344 "parser.tab.c"
    break;

  case 148: /* type_qualifier: CONST  */
#line 1350 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3354 "parser.tab.c"
    break;

  case 149: /* type_qualifier: VOLATILE  */
#line 1356 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3364 "parser.tab.c"
    break;

  case 150: /* declarator: pointer direct_declarator  */
#line 1365 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3375 "parser.tab.c"
    break;

  case 151: /* declarator: direct_declarator  */
#line 1372 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3385 "parser.tab.c"
    break;

  case 152: /* direct_declarator: identifier  */
#line 1381 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3395 "parser.tab.c"
    break;

  case 153: /* direct_declarator: LPAREN declarator rparen  */
#line 1387 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3407 "parser.tab.c"
    break;

  case 154: /* direct_declarator: direct_declarator LSQUARE constant_expression rsquare  */
#line 1395 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3420 "parser.tab.c"
    break;

  case 155: /* direct_declarator: direct_declarator LSQUARE rsquare  */
#line 1404 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3432 "parser.tab.c"
    break;

  case 156: /* direct_declarator: direct_declarator LPAREN parameter_type_list rparen  */
#line 1412 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3445 "parser.tab.c"
    break;

  case 157: /* direct_declarator: direct_declarator LPAREN identifier_list rparen  */
#line 1421 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3458 "parser.tab.c"
    break;

  case 158: /* direct_declarator: direct_declarator LPAREN rparen  */
#line 1430 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3470 "parser.tab.c"
    break;

  case 159: /* pointer: STAR  */
#line 1441 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3480 "parser.tab.c"
    break;

  case 160: /* pointer: STAR type_qualifier_list  */
#line 1447 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3491 "parser.tab.c"
    break;

  case 161: /* pointer: STAR pointer  */
#line 1454 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3502 "parser.tab.c"
    break;

  case 162: /* pointer: STAR type_qualifier_list pointer  */
#line 1461 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3514 "parser.tab.c"
    break;

  case 163: /* type_qualifier_list: type_qualifier  */
#line 1472 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3524 "parser.tab.c"
    break;

  case 164: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1478 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3534 "parser.tab.c"
    break;

  case 165: /* parameter_type_list: parameter_list  */
#line 1487 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3544 "parser.tab.c"
    break;

  case 166: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1493 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3556 "parser.tab.c"
    break;

  case 167: /* parameter_list: parameter_declaration  */
#line 1504 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3566 "parser.tab.c"
    break;

  case 168: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1510 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3577 "parser.tab.c"
    break;

  case 169: /* parameter_declaration: declaration_specifiers declarator  */
#line 1521 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3588 "parser.tab.c"
    break;

  case 170: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1528 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3599 "parser.tab.c"
    break;

  case 171: /* parameter_declaration: declaration_specifiers  */
#line 1535 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3609 "parser.tab.c"
    break;

  case 172: /* identifier_list: identifier  */
#line 1544 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("identifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3619 "parser.tab.c"
    break;

  case 173: /* identifier_list: identifier_list COMMA identifier  */
#line 1550 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3630 "parser.tab.c"
    break;

  case 174: /* type_name: specifier_qualifier_list  */
#line 1560 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3640 "parser.tab.c"
    break;

  case 175: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1566 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3651 "parser.tab.c"
    break;

  case 176: /* abstract_declarator: pointer  */
#line 1576 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3661 "parser.tab.c"
    break;

  case 177: /* abstract_declarator: direct_abstract_declarator  */
#line 1582 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3671 "parser.tab.c"
    break;

  case 178: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1588 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3682 "parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: LPAREN abstract_declarator rparen  */
#line 1598 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3694 "parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: LSQUARE rsquare  */
#line 1606 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3705 "parser.tab.c"
    break;

  case 181: /* direct_abstract_declarator: LSQUARE constant_expression rsquare  */
#line 1613 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3717 "parser.tab.c"
    break;

  case 182: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE rsquare  */
#line 1621 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3728 "parser.tab.c"
    break;

  case 183: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression rsquare  */
#line 1628 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);  
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3740 "parser.tab.c"
    break;

  case 184: /* direct_abstract_declarator: LPAREN rparen  */
#line 1636 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3751 "parser.tab.c"
    break;

  case 185: /* direct_abstract_declarator: LPAREN parameter_type_list rparen  */
#line 1643 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3763 "parser.tab.c"
    break;

  case 186: /* direct_abstract_declarator: direct_abstract_declarator LPAREN rparen  */
#line 1651 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3774 "parser.tab.c"
    break;

  case 187: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list rparen  */
#line 1658 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3786 "parser.tab.c"
    break;

  case 188: /* initializer: assignment_expression  */
#line 1669 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3796 "parser.tab.c"
    break;

  case 189: /* initializer: LCURLY initializer_list rcurly  */
#line 1675 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3808 "parser.tab.c"
    break;

  case 190: /* initializer: LCURLY initializer_list COMMA rcurly  */
#line 1683 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3821 "parser.tab.c"
    break;

  case 191: /* initializer_list: initializer  */
#line 1695 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("initializer_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3831 "parser.tab.c"
    break;

  case 192: /* initializer_list: initializer_list COMMA initializer  */
#line 1701 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3842 "parser.tab.c"
    break;

  case 193: /* statement: labeled_statement  */
#line 1711 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3852 "parser.tab.c"
    break;

  case 194: /* statement: compound_statement  */
#line 1717 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3862 "parser.tab.c"
    break;

  case 195: /* statement: expression_statement  */
#line 1723 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3872 "parser.tab.c"
    break;

  case 196: /* statement: selection_statement  */
#line 1729 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3882 "parser.tab.c"
    break;

  case 197: /* statement: iteration_statement  */
#line 1735 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3892 "parser.tab.c"
    break;

  case 198: /* statement: jump_statement  */
#line 1741 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3902 "parser.tab.c"
    break;

  case 199: /* statement: declaration  */
#line 1747 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3912 "parser.tab.c"
    break;

  case 200: /* labeled_statement: identifier COLON statement  */
#line 1756 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3924 "parser.tab.c"
    break;

  case 201: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1764 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3937 "parser.tab.c"
    break;

  case 202: /* labeled_statement: DEFAULT COLON statement  */
#line 1773 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3949 "parser.tab.c"
    break;

  case 203: /* compound_statement: LCURLY rcurly  */
#line 1784 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3960 "parser.tab.c"
    break;

  case 204: /* compound_statement: LCURLY statement_list rcurly  */
#line 1791 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3972 "parser.tab.c"
    break;

  case 205: /* compound_statement: LCURLY declaration_list rcurly  */
#line 1799 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3984 "parser.tab.c"
    break;

  case 206: /* compound_statement: LCURLY declaration_list statement_list rcurly  */
#line 1807 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3997 "parser.tab.c"
    break;

  case 207: /* declaration_list: declaration  */
#line 1819 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4007 "parser.tab.c"
    break;

  case 208: /* declaration_list: declaration_list declaration  */
#line 1825 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4017 "parser.tab.c"
    break;

  case 209: /* statement_list: statement  */
#line 1835 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement_list"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4027 "parser.tab.c"
    break;

  case 210: /* statement_list: statement_list statement  */
#line 1841 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4037 "parser.tab.c"
    break;

  case 211: /* expression_statement: semi_colon  */
#line 1850 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4047 "parser.tab.c"
    break;

  case 212: /* expression_statement: expression semi_colon  */
#line 1856 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4058 "parser.tab.c"
    break;

  case 213: /* selection_statement: IF LPAREN expression rparen statement  */
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
#line 4072 "parser.tab.c"
    break;

  case 214: /* selection_statement: IF LPAREN expression rparen statement ELSE statement  */
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
#line 4088 "parser.tab.c"
    break;

  case 215: /* selection_statement: SWITCH LPAREN expression rparen statement  */
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
#line 4102 "parser.tab.c"
    break;

  case 216: /* iteration_statement: WHILE LPAREN expression rparen statement  */
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
#line 4116 "parser.tab.c"
    break;

  case 217: /* iteration_statement: UNTIL LPAREN expression rparen statement  */
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
#line 4130 "parser.tab.c"
    break;

  case 218: /* iteration_statement: DO statement WHILE LPAREN expression rparen semi_colon  */
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
#line 4146 "parser.tab.c"
    break;

  case 219: /* iteration_statement: FOR LPAREN expression_statement expression_statement rparen statement  */
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
#line 4161 "parser.tab.c"
    break;

  case 220: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression rparen statement  */
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
#line 4177 "parser.tab.c"
    break;

  case 221: /* iteration_statement: FOR LPAREN declaration expression_statement expression rparen statement  */
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
#line 4193 "parser.tab.c"
    break;

  case 222: /* jump_statement: GOTO identifier semi_colon  */
#line 1971 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4205 "parser.tab.c"
    break;

  case 223: /* jump_statement: CONTINUE semi_colon  */
#line 1979 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4216 "parser.tab.c"
    break;

  case 224: /* jump_statement: BREAK semi_colon  */
#line 1986 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4227 "parser.tab.c"
    break;

  case 225: /* jump_statement: RETURN semi_colon  */
#line 1993 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4238 "parser.tab.c"
    break;

  case 226: /* jump_statement: RETURN expression semi_colon  */
#line 2000 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4250 "parser.tab.c"
    break;

  case 227: /* translation_unit: external_declaration  */
#line 2013 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("translation_unit");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        root = (yyval.astNode);
    }
#line 4261 "parser.tab.c"
    break;

  case 228: /* translation_unit: translation_unit external_declaration  */
#line 2020 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        root = (yyval.astNode);
    }
#line 4272 "parser.tab.c"
    break;

  case 229: /* external_declaration: function_definition  */
#line 2031 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4282 "parser.tab.c"
    break;

  case 230: /* external_declaration: declaration  */
#line 2037 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4292 "parser.tab.c"
    break;

  case 231: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 2048 "parser.y"
    { 
        LINE  
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4304 "parser.tab.c"
    break;

  case 232: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 2057 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        // Function_Def_Handler($2);
    }
#line 4317 "parser.tab.c"
    break;

  case 233: /* function_definition: declarator declaration_list compound_statement  */
#line 2067 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4329 "parser.tab.c"
    break;

  case 234: /* function_definition: declarator compound_statement  */
#line 2076 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4340 "parser.tab.c"
    break;


#line 4344 "parser.tab.c"

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
