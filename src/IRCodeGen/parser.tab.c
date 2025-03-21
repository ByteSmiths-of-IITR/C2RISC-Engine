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
  YYSYMBOL_90_1 = 90,                      /* $@1  */
  YYSYMBOL_constant = 91,                  /* constant  */
  YYSYMBOL_92_2 = 92,                      /* $@2  */
  YYSYMBOL_semi_colon = 93,                /* semi_colon  */
  YYSYMBOL_94_3 = 94,                      /* $@3  */
  YYSYMBOL_rparen = 95,                    /* rparen  */
  YYSYMBOL_96_4 = 96,                      /* $@4  */
  YYSYMBOL_rcurly = 97,                    /* rcurly  */
  YYSYMBOL_98_5 = 98,                      /* $@5  */
  YYSYMBOL_rsquare = 99,                   /* rsquare  */
  YYSYMBOL_100_6 = 100,                    /* $@6  */
  YYSYMBOL_primary_expression = 101,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 102,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 103, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 104,         /* unary_expression  */
  YYSYMBOL_unary_operator = 105,           /* unary_operator  */
  YYSYMBOL_cast_expression = 106,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 107, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 108,      /* additive_expression  */
  YYSYMBOL_shift_expression = 109,         /* shift_expression  */
  YYSYMBOL_relational_expression = 110,    /* relational_expression  */
  YYSYMBOL_equality_expression = 111,      /* equality_expression  */
  YYSYMBOL_and_expression = 112,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 113,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 114,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 115,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 116,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 117,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 118,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 119,      /* assignment_operator  */
  YYSYMBOL_expression = 120,               /* expression  */
  YYSYMBOL_constant_expression = 121,      /* constant_expression  */
  YYSYMBOL_declaration = 122,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 123,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 124,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 125,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 126,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 127,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 128, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 129,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 130,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 131,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 132, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 133,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 134,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 135,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 136,          /* enumerator_list  */
  YYSYMBOL_enumerator = 137,               /* enumerator  */
  YYSYMBOL_type_qualifier = 138,           /* type_qualifier  */
  YYSYMBOL_declarator = 139,               /* declarator  */
  YYSYMBOL_direct_declarator = 140,        /* direct_declarator  */
  YYSYMBOL_pointer = 141,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 142,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 143,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 144,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 145,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 146,          /* identifier_list  */
  YYSYMBOL_type_name = 147,                /* type_name  */
  YYSYMBOL_abstract_declarator = 148,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 149, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 150,              /* initializer  */
  YYSYMBOL_initializer_list = 151,         /* initializer_list  */
  YYSYMBOL_statement = 152,                /* statement  */
  YYSYMBOL_labeled_statement = 153,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 154,       /* compound_statement  */
  YYSYMBOL_declaration_list = 155,         /* declaration_list  */
  YYSYMBOL_statement_list = 156,           /* statement_list  */
  YYSYMBOL_expression_statement = 157,     /* expression_statement  */
  YYSYMBOL_selection_statement = 158,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 159,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 160,           /* jump_statement  */
  YYSYMBOL_translation_unit = 161,         /* translation_unit  */
  YYSYMBOL_external_declaration = 162,     /* external_declaration  */
  YYSYMBOL_function_definition = 163       /* function_definition  */
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
#define YYFINAL  65
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  232
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  380

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
       0,   245,   245,   250,   250,   259,   264,   264,   274,   279,
     279,   291,   296,   296,   306,   311,   311,   321,   326,   326,
     392,   398,   404,   410,   421,   426,   435,   445,   454,   462,
     470,   477,   487,   493,   503,   508,   515,   522,   529,   536,
     548,   553,   558,   563,   568,   573,   581,   586,   599,   604,
     612,   620,   631,   636,   644,   655,   660,   668,   679,   684,
     692,   700,   708,   719,   724,   732,   743,   748,   759,   764,
     775,   780,   791,   796,   807,   812,   823,   828,   841,   846,
     857,   862,   867,   872,   877,   882,   887,   892,   897,   902,
     907,   916,   921,   932,   943,   950,   962,   968,   975,   981,
     988,   994,  1004,  1010,  1020,  1026,  1043,  1049,  1055,  1061,
    1070,  1075,  1080,  1085,  1090,  1095,  1100,  1105,  1110,  1115,
    1121,  1127,  1136,  1147,  1156,  1167,  1172,  1180,  1186,  1195,
    1207,  1214,  1220,  1227,  1236,  1242,  1252,  1258,  1265,  1276,
    1286,  1297,  1310,  1316,  1326,  1332,  1343,  1349,  1358,  1365,
    1374,  1380,  1388,  1397,  1405,  1414,  1423,  1434,  1440,  1447,
    1454,  1465,  1471,  1480,  1486,  1497,  1503,  1514,  1521,  1528,
    1537,  1543,  1553,  1559,  1569,  1575,  1581,  1591,  1599,  1606,
    1614,  1621,  1629,  1636,  1644,  1651,  1662,  1668,  1676,  1688,
    1694,  1704,  1710,  1716,  1722,  1728,  1734,  1740,  1749,  1757,
    1766,  1777,  1784,  1792,  1800,  1812,  1818,  1828,  1834,  1843,
    1849,  1859,  1869,  1881,  1894,  1904,  1914,  1926,  1937,  1949,
    1964,  1972,  1979,  1986,  1993,  2006,  2013,  2024,  2030,  2041,
    2050,  2059,  2067
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
  "$@1", "constant", "$@2", "semi_colon", "$@3", "rparen", "$@4", "rcurly",
  "$@5", "rsquare", "$@6", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
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
  "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-163)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     819,  -163,  -163,    53,    79,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,    80,  -163,    22,  -163,    41,  1033,  1033,  -163,
     119,  -163,  1033,   971,   102,    11,   643,  -163,  -163,    23,
    -163,  -163,    79,    75,    71,  -163,  -163,  -163,   138,   -27,
    -163,   927,  -163,  -163,  1047,   118,  -163,   474,  -163,    41,
    -163,   971,   863,   777,   102,  -163,  -163,  -163,  -163,   153,
    -163,  -163,   105,   140,  -163,    75,  -163,    53,  -163,  1116,
    -163,   971,  1047,   427,  -163,    43,  1047,  1047,  -163,  -163,
     564,  1170,  1170,   731,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  1177,   112,   146,   154,   157,   557,   164,    75,   116,
     116,   433,   177,   159,  -163,   211,  -163,  -163,   217,  -163,
     195,   637,  1177,  -163,   176,   160,   216,    88,   229,   199,
     185,   201,   239,    14,  -163,  -163,    25,  -163,  -163,  -163,
    -163,   474,   474,  -163,  -163,  -163,  -163,   205,  -163,  -163,
    -163,  -163,   135,    23,   231,  -163,    35,  -163,  -163,  -163,
     268,  -163,  -163,   242,  -163,  1177,    75,  -163,   140,  -163,
    1116,  -163,  -163,  -163,  -163,  -163,  -163,  1177,    33,  -163,
     228,  -163,   427,   731,  -163,  1177,  -163,  -163,    37,   178,
      23,   230,   557,  1177,  1177,  1177,  -163,   204,   687,   116,
    -163,  -163,  -163,    25,  1177,   557,  -163,  -163,    75,  -163,
    -163,  1130,  1177,    75,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  1177,  -163,  1177,  1177,  1177,
    1177,  1177,  1177,  1177,  1177,  1177,  1177,  1177,  1177,  1177,
    1177,  1177,  1177,  1177,  1177,  1177,  1177,  -163,  -163,  -163,
     474,  -163,  -163,   775,   777,  -163,   168,  -163,   151,  -163,
     840,    75,  -163,  -163,  -163,  -163,  -163,  -163,  -163,   155,
    -163,    43,  -163,  1177,  -163,    23,  -163,   907,   192,  -163,
    1177,   557,  -163,    37,    37,    37,   260,   433,   433,  -163,
    -163,    37,  -163,  -163,  -163,    60,  -163,   197,  -163,  -163,
    -163,  -163,  -163,   176,   176,   160,   160,   216,   216,   216,
     216,    88,    88,   229,   199,   185,   201,   239,   -21,  -163,
    -163,  -163,    23,    23,  -163,   242,   151,   989,   777,  -163,
    -163,  -163,   645,  -163,  -163,  -163,  -163,  -163,  -163,   557,
     557,   557,  1177,  1177,  1130,   557,  1177,  -163,  -163,  1177,
    -163,  -163,  -163,  -163,    23,  -163,   242,  -163,  -163,   219,
    -163,  -163,    37,    37,   557,    37,  -163,  -163,  -163,  -163,
    -163,   557,   116,   557,  -163,   557,  -163,  -163,  -163,  -163
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     2,   121,     3,   157,   106,   107,   108,   109,   111,
     112,   113,   114,   117,   118,   115,   116,   146,   147,   110,
     125,   126,     3,   150,     0,   228,     3,    96,    98,   119,
       3,   120,   100,     0,   149,     3,     3,   225,   227,    12,
     161,   159,   158,     3,   141,     4,     8,    94,     0,     9,
     102,   104,    97,    99,     0,   124,   101,     3,   205,     3,
     232,     0,     3,     3,   148,     1,   226,    11,   151,     0,
     162,   160,   144,    15,   142,     3,    10,     3,    95,     3,
     230,     0,   131,    15,   127,     3,   133,     0,     5,    22,
       3,     3,     3,     3,    14,    40,    41,    42,    43,    44,
      45,     3,     0,     0,     0,     0,     3,     0,     3,     9,
       9,     3,     0,    20,    21,     0,   209,   201,     0,    24,
      34,    46,     3,    48,    52,    55,    58,    63,    66,    68,
      70,    72,    74,    76,    78,    91,     9,   197,   207,   191,
     192,     3,     3,   193,   194,   195,   196,   104,   206,   231,
     170,   156,   169,    12,   163,   165,    12,    17,    20,   153,
       0,    46,    93,    18,    13,     3,     3,   139,    15,   103,
       3,   186,   105,   229,   130,   123,   128,     3,     9,   134,
     136,   132,    15,     3,    38,     3,    35,    36,    12,   172,
      12,     0,     3,     3,     3,     3,   197,     0,     3,     9,
     221,   222,   223,     9,     3,     3,     7,    16,     3,    30,
      31,     3,     3,     3,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    80,     3,    37,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,   210,   203,   197,
       3,   202,   208,     3,     3,   167,   174,   168,   175,   154,
       0,     3,   155,    19,   152,   145,   143,   140,   189,    15,
     137,     3,   129,     3,   122,    12,    23,    12,   174,   173,
       3,     3,   200,    12,    12,    12,     0,     3,     3,   220,
     224,    12,   198,    29,    26,    12,    32,    18,    28,    79,
      49,    50,    51,    53,    54,    56,    57,    61,    62,    59,
      60,    64,    65,    67,    69,    71,    73,    75,     0,    92,
     204,   182,    12,    12,   178,    18,   176,    12,     3,   164,
     166,   171,     3,   187,   135,   138,    39,    47,   199,     3,
       3,     3,     3,     3,     3,     3,     3,    27,    25,     3,
     183,   177,   179,   184,    12,   180,    18,   188,   190,   211,
     213,   214,    12,    12,     3,    12,   215,    33,    77,   185,
     181,     3,     9,     3,   217,     3,   212,   216,   219,   218
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -163,     0,  -163,  -163,  -163,   -22,  -163,   -37,  -163,    47,
    -163,   -20,  -163,  -163,  -163,  -163,   172,  -163,  -102,    21,
      42,     5,    49,    52,    55,    58,    61,    54,  -163,   -56,
     -67,  -163,   236,   -91,   104,     6,  -163,   224,  -163,   -35,
    -163,  -163,   223,   -70,   -65,  -163,    32,  -163,   237,   145,
      12,    38,   -34,     7,  -163,   -57,  -163,    46,  -163,   130,
    -134,  -146,  -162,  -163,    18,  -163,    -1,    56,   173,  -159,
    -163,  -163,  -163,  -163,   279,  -163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   158,    24,   114,   115,   116,    48,   321,    69,   117,
     118,   159,   160,   119,   120,   295,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   225,   136,   163,   196,    59,    49,    50,    27,    28,
      29,    30,    83,    84,    85,   178,   179,    31,    73,    74,
      32,    33,    34,    35,    42,   322,   154,   155,   156,   190,
     323,   258,   172,   269,   138,   139,   140,    61,   142,   143,
     144,   145,   146,    36,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    64,    68,    23,    47,   153,    26,   162,   268,    77,
     191,    41,   171,   176,     1,   246,    40,   174,   257,    82,
     226,   181,    44,    45,    46,   151,    23,    78,   189,   349,
      55,   244,    60,    52,    53,    23,    23,    47,    56,   288,
       3,    39,    26,    72,     1,   162,     1,    82,    82,    71,
      80,    82,    82,    67,    70,   279,     1,   113,    82,    23,
     149,   246,   150,   245,    51,    67,    86,    67,   152,   271,
       3,   261,     3,   246,   265,    72,    46,    23,     1,     4,
     173,     4,     3,     1,    46,    23,   270,   200,   201,   202,
      67,     4,    46,   177,    86,    86,   346,   147,    86,    86,
     234,   235,    75,   171,    25,    86,   113,    81,   199,   162,
     326,    43,   176,   141,   247,   147,   259,     4,   189,   262,
     167,   162,     1,   180,   197,   300,   301,   302,   343,   344,
     175,    62,   326,   236,   237,    63,    -3,    58,     1,    76,
      25,   113,   113,   264,   296,    17,    18,    82,    82,    87,
      54,   276,    23,   280,   164,    58,   272,   165,   299,   256,
     252,   137,   192,   325,   253,   148,    72,    46,   254,    -3,
     358,     1,    94,     4,   294,   193,   166,   289,   337,   319,
     327,   290,   335,   194,   328,   148,   195,    94,   248,   251,
     255,   332,   113,   198,    86,    86,   278,   253,   162,   230,
     231,   254,   208,   209,   210,   113,   204,   277,   293,   205,
     282,   254,   206,   298,   227,   267,     4,   162,   207,   228,
     229,   277,    64,   292,   211,   254,   232,   233,   212,   274,
     213,   157,   241,   246,   324,   161,   240,   356,   336,   307,
     308,   309,   310,   238,   239,   249,   339,   340,   341,   242,
     113,   303,   304,    23,   345,   243,    23,    79,   347,   152,
     256,   331,   184,   186,   187,   171,   152,   260,   252,   263,
     354,    23,   162,   161,   305,   306,   157,   348,   273,   367,
     281,   113,   286,   152,   278,   350,   351,   311,   312,   342,
     353,    39,   313,   368,   161,   371,   314,   320,   317,   338,
     315,   169,   287,   334,   316,   352,   330,   364,   355,   180,
     182,   266,   168,   275,   250,    66,   333,   369,     0,     0,
       0,     0,     0,     0,     0,   372,   373,     0,   375,   188,
       0,     0,     0,   152,     0,     0,   370,   161,     0,   113,
     113,   113,     0,     0,     0,   113,     0,   203,     0,   161,
     377,     0,     0,     0,     0,     0,     0,   359,   360,   361,
       0,     0,     0,   366,   113,     0,     0,     0,     0,     0,
       0,   113,     0,   113,     0,   113,     0,     0,     0,   357,
       0,     0,   374,     0,     0,     0,     0,     0,     0,   376,
       0,   378,     0,   379,     0,     0,     0,     0,     0,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,     0,     0,   188,
       0,   188,     0,     0,     0,     0,   161,     0,     0,   283,
     284,   285,     0,     0,     0,     0,     1,    88,    89,    90,
     291,    91,    92,     0,     0,   161,     0,     0,   297,     0,
       0,     0,   161,     0,     0,     2,     0,     0,     0,    94,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   100,     0,     1,    88,    89,
      90,   318,    91,    92,    46,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
     161,     0,     2,    93,     0,    57,    94,     0,     0,     0,
       0,    95,    96,    97,    98,    99,   100,     0,     0,     0,
       0,   161,     0,     0,     0,    46,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,   101,   102,   103,
       0,   104,   105,   106,   107,   108,   109,   110,   111,   112,
       1,    88,    89,    90,     0,    91,    92,     1,    88,    89,
      90,     0,    91,    92,     0,     0,     0,     0,   362,   363,
     365,     0,     0,     0,     0,     2,    93,     0,    57,     0,
       0,     0,     0,   183,    95,    96,    97,    98,    99,   100,
       0,    95,    96,    97,    98,    99,   100,     0,    46,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
     101,   102,   103,     0,   104,   105,   106,   107,   108,   109,
     110,   111,   112,    65,     0,     0,     1,     0,     1,    88,
      89,    90,     0,    91,    92,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,     0,     0,     0,     0,     0,
       0,     2,     3,     0,    93,     0,   170,    94,     0,     0,
       0,     4,    95,    96,    97,    98,    99,   100,     0,   224,
       1,    88,    89,    90,     0,    91,    92,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     2,    93,     0,     0,     0,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   100,
       0,     0,     0,     0,     1,    88,    89,    90,    46,    91,
      92,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     2,
      93,     0,     0,     0,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   100,     0,     0,     0,     0,     1,     0,
       1,    88,    89,    90,     0,    91,    92,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     2,   253,    67,    93,     0,   254,     0,
       0,   157,     0,     4,    95,    96,    97,    98,    99,   100,
       0,     0,     1,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,     2,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     0,     2,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     2,     0,    67,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,   329,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     2,   277,    67,     0,     0,
     254,     0,     0,     0,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     0,     0,    57,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    79,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     2,
       0,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     0,    67,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     1,
      88,    89,    90,     0,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     1,    88,    89,    90,     0,    91,    92,
       0,     0,     0,     0,     0,    93,     0,   170,     0,     0,
       0,     0,     0,    95,    96,    97,    98,    99,   100,    93,
      67,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   100,     1,    88,    89,    90,     0,    91,    92,
       1,    88,    89,    90,     0,    91,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   185,
       0,     0,     0,     0,     0,     0,    93,    95,    96,    97,
      98,    99,   100,     0,    95,    96,    97,    98,    99,   100
};

static const yytype_int16 yycheck[] =
{
       0,    35,    39,     3,    26,    62,     0,    63,   170,    36,
     101,     4,    79,    83,     3,    36,     4,    82,   152,    54,
     122,    86,    22,     1,    51,    62,    26,    49,    93,    50,
      30,    17,    33,    27,    28,    35,    36,    59,    32,   198,
      29,     3,    36,    43,     3,   101,     3,    82,    83,    42,
      51,    86,    87,    30,    42,   189,     3,    57,    93,    59,
      61,    36,    62,    49,    26,    30,    54,    30,    62,    36,
      29,    36,    29,    36,   165,    75,    51,    77,     3,    38,
      81,    38,    29,     3,    51,    85,   177,   109,   110,   111,
      30,    38,    51,    50,    82,    83,    36,    59,    86,    87,
      12,    13,    31,   170,     0,    93,   106,    51,   108,   165,
     256,    31,   182,    57,   136,    77,   153,    38,   183,   156,
      73,   177,     3,    85,   106,   227,   228,   229,   287,   288,
      83,    29,   278,    45,    46,    33,     1,    33,     3,     1,
      36,   141,   142,   163,   211,    66,    67,   182,   183,    31,
      31,   188,   152,   190,     1,    51,   178,    52,   225,   152,
     142,    57,    50,   254,    29,    61,   166,    51,    33,     1,
     332,     3,    32,    38,   211,    29,    36,   199,   280,   246,
      29,   203,   273,    29,    33,    81,    29,    32,   141,   142,
     152,    36,   192,    29,   182,   183,   189,    29,   254,    39,
      40,    33,     7,     8,     9,   205,    29,    29,   208,    50,
     192,    33,     1,   213,    38,   168,    38,   273,     1,    43,
      44,    29,   256,   205,    29,    33,    10,    11,    33,   182,
      35,    34,    47,    36,   254,    63,    37,   328,   275,   234,
     235,   236,   237,    14,    15,   141,   283,   284,   285,    48,
     250,   230,   231,   253,   291,    16,   256,    52,   295,   253,
     253,   261,    90,    91,    92,   332,   260,    36,   250,     1,
     327,   271,   328,   101,   232,   233,    34,   297,    50,   346,
      50,   281,    78,   277,   277,   322,   323,   238,   239,    29,
     327,   253,   240,   349,   122,    76,   241,   250,   244,   281,
     242,    77,   198,   271,   243,   325,   260,   344,   328,   271,
      87,   166,    75,   183,   141,    36,   269,   354,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   362,   363,    -1,   365,    93,
      -1,    -1,    -1,   327,    -1,    -1,   356,   165,    -1,   339,
     340,   341,    -1,    -1,    -1,   345,    -1,   111,    -1,   177,
     372,    -1,    -1,    -1,    -1,    -1,    -1,   339,   340,   341,
      -1,    -1,    -1,   345,   364,    -1,    -1,    -1,    -1,    -1,
      -1,   371,    -1,   373,    -1,   375,    -1,    -1,    -1,   332,
      -1,    -1,   364,    -1,    -1,    -1,    -1,    -1,    -1,   371,
      -1,   373,    -1,   375,    -1,    -1,    -1,    -1,    -1,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,    -1,    -1,   183,
      -1,   185,    -1,    -1,    -1,    -1,   254,    -1,    -1,   193,
     194,   195,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
     204,     8,     9,    -1,    -1,   273,    -1,    -1,   212,    -1,
      -1,    -1,   280,    -1,    -1,    28,    -1,    -1,    -1,    32,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    -1,     3,     4,     5,
       6,   245,     8,     9,    51,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    -1,
     328,    -1,    28,    29,    -1,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,   349,    -1,    -1,    -1,    51,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    85,
       3,     4,     5,     6,    -1,     8,     9,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,   342,   343,
     344,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      -1,    -1,    -1,    29,    37,    38,    39,    40,    41,    42,
      -1,    37,    38,    39,    40,    41,    42,    -1,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    -1,
      73,    74,    75,    -1,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     0,    -1,    -1,     3,    -1,     3,     4,
       5,     6,    -1,     8,     9,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    -1,    29,    -1,    31,    32,    -1,    -1,
      -1,    38,    37,    38,    39,    40,    41,    42,    -1,    52,
       3,     4,     5,     6,    -1,     8,     9,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    51,     8,
       9,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,     3,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    28,    29,    30,    29,    -1,    33,    -1,
      -1,    34,    -1,    38,    37,    38,    39,    40,    41,    42,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    28,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    28,    -1,    30,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    28,    29,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    31,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    28,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,    -1,     8,     9,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    37,    38,    39,
      40,    41,    42,    -1,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    38,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    89,    90,   122,   123,   126,   127,   128,
     129,   135,   138,   139,   140,   141,   161,   162,   163,   139,
     138,   141,   142,    31,    89,     1,    51,    93,    94,   124,
     125,   139,   123,   123,    31,    89,   123,    31,   122,   123,
     154,   155,    29,    33,   140,     0,   162,    30,    95,    96,
     138,   141,    89,   136,   137,    31,     1,    36,    93,    52,
     154,   155,   127,   130,   131,   132,   138,    31,     4,     5,
       6,     8,     9,    29,    32,    37,    38,    39,    40,    41,
      42,    73,    74,    75,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    89,    91,    92,    93,    97,    98,   101,
     102,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   120,   122,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   139,   122,   154,
      89,    95,   123,   143,   144,   145,   146,    34,    89,    99,
     100,   104,   117,   121,     1,    52,    36,    97,   136,   125,
      31,   118,   150,   154,   132,    97,   131,    50,   133,   134,
     139,   132,   130,    29,   104,    29,   104,   104,   120,   132,
     147,   121,    50,    29,    29,    29,   122,   152,    29,    89,
      93,    93,    93,   120,    29,    50,     1,     1,     7,     8,
       9,    29,    33,    35,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    52,   119,   106,    38,    43,    44,
      39,    40,    10,    11,    12,    13,    45,    46,    14,    15,
      37,    47,    48,    16,    17,    49,    36,    93,    97,   122,
     156,    97,   152,    29,    33,   139,   141,   148,   149,    95,
      36,    36,    95,     1,    99,   121,   137,    97,   150,   151,
     121,    36,    93,    50,    97,   147,    95,    29,   141,   148,
      95,    50,   152,   120,   120,   120,    78,   122,   157,    93,
      93,   120,   152,    89,    95,   103,   118,   120,    89,   118,
     106,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   110,   110,   111,   112,   113,   114,   115,   120,   118,
      97,    95,   143,   148,    99,   121,   149,    29,    33,    72,
     145,    89,    36,    97,   134,   121,    95,   106,   152,    95,
      95,    95,    29,   157,   157,    95,    36,    95,    99,    50,
      95,    95,    99,    95,   143,    99,   121,    97,   150,   152,
     152,   152,   120,   120,    95,   120,   152,   118,   117,    95,
      99,    76,    95,    95,   152,    95,   152,    93,   152,   152
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    89,    91,    92,    91,    93,    94,
      93,    95,    96,    95,    97,    98,    97,    99,   100,    99,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   104,   104,   104,   104,   104,   104,
     105,   105,   105,   105,   105,   105,   106,   106,   107,   107,
     107,   107,   108,   108,   108,   109,   109,   109,   110,   110,
     110,   110,   110,   111,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   121,   122,   122,   123,   123,   123,   123,
     123,   123,   124,   124,   125,   125,   126,   126,   126,   126,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   128,   128,   128,   129,   129,   130,   130,   131,
     132,   132,   132,   132,   133,   133,   134,   134,   134,   135,
     135,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   140,   140,   140,   140,   140,   141,   141,   141,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   148,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   150,   150,   150,   151,
     151,   152,   152,   152,   152,   152,   152,   152,   153,   153,
     153,   154,   154,   154,   154,   155,   155,   156,   156,   157,
     157,   158,   158,   158,   159,   159,   159,   159,   159,   159,
     160,   160,   160,   160,   160,   161,   161,   162,   162,   163,
     163,   163,   163
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
       1,     1,     5,     4,     2,     1,     1,     1,     2,     3,
       2,     1,     2,     1,     1,     3,     1,     2,     3,     4,
       5,     2,     1,     3,     1,     3,     1,     1,     2,     1,
       1,     3,     4,     3,     4,     4,     3,     1,     2,     2,
       3,     1,     2,     1,     3,     1,     3,     2,     2,     1,
       1,     3,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     2,     3,     3,     4,     1,     3,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     2,     3,     3,     4,     1,     2,     1,     2,     1,
       2,     5,     7,     5,     5,     5,     7,     6,     7,     7,
       3,     2,     2,     2,     3,     1,     2,     1,     1,     4,
       3,     3,     2
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
#line 246 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1836 "parser.tab.c"
    break;

  case 3: /* $@1: %empty  */
#line 250 "parser.y"
      {stopYYERROR=true;}
#line 1842 "parser.tab.c"
    break;

  case 4: /* identifier: $@1 error  */
#line 251 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 Identifier");
            ourError("Expected an ID or Expression");
        }
#line 1852 "parser.tab.c"
    break;

  case 5: /* constant: CONSTANT  */
#line 260 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1861 "parser.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 264 "parser.y"
     {stopYYERROR=true;}
#line 1867 "parser.tab.c"
    break;

  case 7: /* constant: $@2 error  */
#line 265 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 Constant");
            ourError("Expected a Constant or Expression");

        }
#line 1878 "parser.tab.c"
    break;

  case 8: /* semi_colon: SEMI_COLON  */
#line 275 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1887 "parser.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 279 "parser.y"
      {stopYYERROR=true;}
#line 1893 "parser.tab.c"
    break;

  case 10: /* semi_colon: $@3 error  */
#line 280 "parser.y"
        { 
            LINE
            // Program comes here after calling yy error()

            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 SemiColon");
            ourError("Expected a SemiColon");
            
        }
#line 1906 "parser.tab.c"
    break;

  case 11: /* rparen: RPAREN  */
#line 292 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1915 "parser.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 296 "parser.y"
     {stopYYERROR=true;}
#line 1921 "parser.tab.c"
    break;

  case 13: /* rparen: $@4 error  */
#line 297 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RParen");
            ourError("Expected a Right Parenthesis");

        }
#line 1932 "parser.tab.c"
    break;

  case 14: /* rcurly: RCURLY  */
#line 307 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1941 "parser.tab.c"
    break;

  case 15: /* $@5: %empty  */
#line 311 "parser.y"
      {stopYYERROR=true;}
#line 1947 "parser.tab.c"
    break;

  case 16: /* rcurly: $@5 error  */
#line 312 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RCurly");
            ourError("Expected a Right Curly Brace");

        }
#line 1958 "parser.tab.c"
    break;

  case 17: /* rsquare: RSQUARE  */
#line 322 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1967 "parser.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 326 "parser.y"
     {stopYYERROR=true;}
#line 1973 "parser.tab.c"
    break;

  case 19: /* rsquare: $@6 error  */
#line 327 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "\U0001F6A8 RSquare");
            ourError("Expected a Right Square Bracket");

        }
#line 1984 "parser.tab.c"
    break;

  case 20: /* primary_expression: identifier  */
#line 393 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 1994 "parser.tab.c"
    break;

  case 21: /* primary_expression: constant  */
#line 399 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2004 "parser.tab.c"
    break;

  case 22: /* primary_expression: STRING_LITERAL  */
#line 405 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
        }
#line 2014 "parser.tab.c"
    break;

  case 23: /* primary_expression: LPAREN expression rparen  */
#line 411 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
            (yyval.astNode)->addChild((yyvsp[-1].astNode));
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2026 "parser.tab.c"
    break;

  case 24: /* postfix_expression: primary_expression  */
#line 422 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2035 "parser.tab.c"
    break;

  case 25: /* postfix_expression: postfix_expression LSQUARE expression rsquare  */
#line 427 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2048 "parser.tab.c"
    break;

  case 26: /* postfix_expression: postfix_expression LPAREN rparen  */
#line 436 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        //-
        //PARSER_TABLE.push_back({$1->position, {$1->value, "function call"}});
    }
#line 2062 "parser.tab.c"
    break;

  case 27: /* postfix_expression: postfix_expression LPAREN argument_expression_list rparen  */
#line 446 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2075 "parser.tab.c"
    break;

  case 28: /* postfix_expression: postfix_expression DOT identifier  */
#line 455 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2087 "parser.tab.c"
    break;

  case 29: /* postfix_expression: postfix_expression PTR_OP identifier  */
#line 463 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2099 "parser.tab.c"
    break;

  case 30: /* postfix_expression: postfix_expression INC_OP  */
#line 471 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2110 "parser.tab.c"
    break;

  case 31: /* postfix_expression: postfix_expression DEC_OP  */
#line 478 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2121 "parser.tab.c"
    break;

  case 32: /* argument_expression_list: assignment_expression  */
#line 488 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("argument_expression_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2131 "parser.tab.c"
    break;

  case 33: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 494 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2142 "parser.tab.c"
    break;

  case 34: /* unary_expression: postfix_expression  */
#line 504 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2151 "parser.tab.c"
    break;

  case 35: /* unary_expression: INC_OP unary_expression  */
#line 509 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2162 "parser.tab.c"
    break;

  case 36: /* unary_expression: DEC_OP unary_expression  */
#line 516 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2173 "parser.tab.c"
    break;

  case 37: /* unary_expression: unary_operator cast_expression  */
#line 523 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2184 "parser.tab.c"
    break;

  case 38: /* unary_expression: SIZEOF unary_expression  */
#line 530 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2195 "parser.tab.c"
    break;

  case 39: /* unary_expression: SIZEOF LPAREN type_name rparen  */
#line 537 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2208 "parser.tab.c"
    break;

  case 40: /* unary_operator: BIT_AND  */
#line 549 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2217 "parser.tab.c"
    break;

  case 41: /* unary_operator: STAR  */
#line 554 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2226 "parser.tab.c"
    break;

  case 42: /* unary_operator: PLUS  */
#line 559 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2235 "parser.tab.c"
    break;

  case 43: /* unary_operator: MINUS  */
#line 564 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2244 "parser.tab.c"
    break;

  case 44: /* unary_operator: BIT_NOT  */
#line 569 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2253 "parser.tab.c"
    break;

  case 45: /* unary_operator: NOT_OP  */
#line 574 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator", (yyvsp[0].tokenAtr)->value); 
    }
#line 2262 "parser.tab.c"
    break;

  case 46: /* cast_expression: unary_expression  */
#line 582 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2271 "parser.tab.c"
    break;

  case 47: /* cast_expression: LPAREN type_name rparen cast_expression  */
#line 587 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("cast_expression");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2284 "parser.tab.c"
    break;

  case 48: /* multiplicative_expression: cast_expression  */
#line 600 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2293 "parser.tab.c"
    break;

  case 49: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 605 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2305 "parser.tab.c"
    break;

  case 50: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 613 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2317 "parser.tab.c"
    break;

  case 51: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 621 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2329 "parser.tab.c"
    break;

  case 52: /* additive_expression: multiplicative_expression  */
#line 632 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2338 "parser.tab.c"
    break;

  case 53: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 637 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2350 "parser.tab.c"
    break;

  case 54: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 645 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2362 "parser.tab.c"
    break;

  case 55: /* shift_expression: additive_expression  */
#line 656 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2371 "parser.tab.c"
    break;

  case 56: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 661 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2383 "parser.tab.c"
    break;

  case 57: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 669 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2395 "parser.tab.c"
    break;

  case 58: /* relational_expression: shift_expression  */
#line 680 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2404 "parser.tab.c"
    break;

  case 59: /* relational_expression: relational_expression LESSER_OP shift_expression  */
#line 685 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2416 "parser.tab.c"
    break;

  case 60: /* relational_expression: relational_expression GREATER_OP shift_expression  */
#line 693 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2428 "parser.tab.c"
    break;

  case 61: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 701 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2440 "parser.tab.c"
    break;

  case 62: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 709 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2452 "parser.tab.c"
    break;

  case 63: /* equality_expression: relational_expression  */
#line 720 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2461 "parser.tab.c"
    break;

  case 64: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 725 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2473 "parser.tab.c"
    break;

  case 65: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 733 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2485 "parser.tab.c"
    break;

  case 66: /* and_expression: equality_expression  */
#line 744 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2494 "parser.tab.c"
    break;

  case 67: /* and_expression: and_expression BIT_AND equality_expression  */
#line 749 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("and_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2506 "parser.tab.c"
    break;

  case 68: /* exclusive_or_expression: and_expression  */
#line 760 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2515 "parser.tab.c"
    break;

  case 69: /* exclusive_or_expression: exclusive_or_expression XOR and_expression  */
#line 765 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("exclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2527 "parser.tab.c"
    break;

  case 70: /* inclusive_or_expression: exclusive_or_expression  */
#line 776 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2536 "parser.tab.c"
    break;

  case 71: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 781 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("inclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2548 "parser.tab.c"
    break;

  case 72: /* logical_and_expression: inclusive_or_expression  */
#line 792 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2557 "parser.tab.c"
    break;

  case 73: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 797 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_and_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2569 "parser.tab.c"
    break;

  case 74: /* logical_or_expression: logical_and_expression  */
#line 808 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2578 "parser.tab.c"
    break;

  case 75: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 813 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2590 "parser.tab.c"
    break;

  case 76: /* conditional_expression: logical_or_expression  */
#line 824 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2599 "parser.tab.c"
    break;

  case 77: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 829 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("conditional_expression");
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2613 "parser.tab.c"
    break;

  case 78: /* assignment_expression: conditional_expression  */
#line 842 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2622 "parser.tab.c"
    break;

  case 79: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 847 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2634 "parser.tab.c"
    break;

  case 80: /* assignment_operator: ASSIGN  */
#line 858 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2643 "parser.tab.c"
    break;

  case 81: /* assignment_operator: MUL_ASSIGN  */
#line 863 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2652 "parser.tab.c"
    break;

  case 82: /* assignment_operator: DIV_ASSIGN  */
#line 868 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2661 "parser.tab.c"
    break;

  case 83: /* assignment_operator: MOD_ASSIGN  */
#line 873 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);;
    }
#line 2670 "parser.tab.c"
    break;

  case 84: /* assignment_operator: ADD_ASSIGN  */
#line 878 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2679 "parser.tab.c"
    break;

  case 85: /* assignment_operator: SUB_ASSIGN  */
#line 883 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2688 "parser.tab.c"
    break;

  case 86: /* assignment_operator: LEFT_ASSIGN  */
#line 888 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2697 "parser.tab.c"
    break;

  case 87: /* assignment_operator: RIGHT_ASSIGN  */
#line 893 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2706 "parser.tab.c"
    break;

  case 88: /* assignment_operator: AND_ASSIGN  */
#line 898 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2715 "parser.tab.c"
    break;

  case 89: /* assignment_operator: XOR_ASSIGN  */
#line 903 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2724 "parser.tab.c"
    break;

  case 90: /* assignment_operator: OR_ASSIGN  */
#line 908 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator", (yyvsp[0].tokenAtr)->value);
    }
#line 2733 "parser.tab.c"
    break;

  case 91: /* expression: assignment_expression  */
#line 917 "parser.y"
    { 
        LINE
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2742 "parser.tab.c"
    break;

  case 92: /* expression: expression COMMA assignment_expression  */
#line 922 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("expression"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2754 "parser.tab.c"
    break;

  case 93: /* constant_expression: conditional_expression  */
#line 933 "parser.y"
    {
        LINE
        // $$ = new ASTNode("constant_expression");
        // $$->addChild($1);
        // ShortHand
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 2766 "parser.tab.c"
    break;

  case 94: /* declaration: declaration_specifiers semi_colon  */
#line 944 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2777 "parser.tab.c"
    break;

  case 95: /* declaration: declaration_specifiers init_declarator_list semi_colon  */
#line 951 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Declaration_Handler($1, $2);
    }
#line 2790 "parser.tab.c"
    break;

  case 96: /* declaration_specifiers: storage_class_specifier  */
#line 963 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2800 "parser.tab.c"
    break;

  case 97: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 969 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2811 "parser.tab.c"
    break;

  case 98: /* declaration_specifiers: type_specifier  */
#line 976 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2821 "parser.tab.c"
    break;

  case 99: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 982 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2832 "parser.tab.c"
    break;

  case 100: /* declaration_specifiers: type_qualifier  */
#line 989 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2842 "parser.tab.c"
    break;

  case 101: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 995 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 2853 "parser.tab.c"
    break;

  case 102: /* init_declarator_list: init_declarator  */
#line 1005 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("init_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2863 "parser.tab.c"
    break;

  case 103: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1011 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2874 "parser.tab.c"
    break;

  case 104: /* init_declarator: declarator  */
#line 1021 "parser.y"
    {
        LINE  
        (yyval.astNode) = new ASTNode("init_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2884 "parser.tab.c"
    break;

  case 105: /* init_declarator: declarator ASSIGN initializer  */
#line 1027 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("init_declarator"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2896 "parser.tab.c"
    break;

  case 106: /* storage_class_specifier: EXTERN  */
#line 1044 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2906 "parser.tab.c"
    break;

  case 107: /* storage_class_specifier: STATIC  */
#line 1050 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2916 "parser.tab.c"
    break;

  case 108: /* storage_class_specifier: AUTO  */
#line 1056 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2926 "parser.tab.c"
    break;

  case 109: /* storage_class_specifier: REGISTER  */
#line 1062 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));    
    }
#line 2936 "parser.tab.c"
    break;

  case 110: /* type_specifier: VOID  */
#line 1071 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2945 "parser.tab.c"
    break;

  case 111: /* type_specifier: CHAR  */
#line 1076 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2954 "parser.tab.c"
    break;

  case 112: /* type_specifier: SHORT  */
#line 1081 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2963 "parser.tab.c"
    break;

  case 113: /* type_specifier: INT  */
#line 1086 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2972 "parser.tab.c"
    break;

  case 114: /* type_specifier: LONG  */
#line 1091 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2981 "parser.tab.c"
    break;

  case 115: /* type_specifier: FLOAT  */
#line 1096 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2990 "parser.tab.c"
    break;

  case 116: /* type_specifier: DOUBLE  */
#line 1101 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 2999 "parser.tab.c"
    break;

  case 117: /* type_specifier: SIGNED  */
#line 1106 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3008 "parser.tab.c"
    break;

  case 118: /* type_specifier: UNSIGNED  */
#line 1111 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier", (yyvsp[0].tokenAtr)->value);
    }
#line 3017 "parser.tab.c"
    break;

  case 119: /* type_specifier: struct_or_union_specifier  */
#line 1116 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3027 "parser.tab.c"
    break;

  case 120: /* type_specifier: enum_specifier  */
#line 1122 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3037 "parser.tab.c"
    break;

  case 121: /* type_specifier: TYPE_NAME  */
#line 1128 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3047 "parser.tab.c"
    break;

  case 122: /* struct_or_union_specifier: struct_or_union identifier LCURLY struct_declaration_list rcurly  */
#line 1137 "parser.y"
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
#line 3062 "parser.tab.c"
    break;

  case 123: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list rcurly  */
#line 1148 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3075 "parser.tab.c"
    break;

  case 124: /* struct_or_union_specifier: struct_or_union identifier  */
#line 1157 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild(new ASTNode("struct_UnionID", (yyvsp[0].astNode)->value));
        PARSER_TABLE.push_back({(yyvsp[0].astNode)->position, {(yyvsp[0].astNode)->value, (yyvsp[-1].astNode)->value}});
    }
#line 3087 "parser.tab.c"
    break;

  case 125: /* struct_or_union: STRUCT  */
#line 1168 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Struct", "struct");
    }
#line 3096 "parser.tab.c"
    break;

  case 126: /* struct_or_union: UNION  */
#line 1173 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("Union", "union");
    }
#line 3105 "parser.tab.c"
    break;

  case 127: /* struct_declaration_list: struct_declaration  */
#line 1181 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3115 "parser.tab.c"
    break;

  case 128: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1187 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3125 "parser.tab.c"
    break;

  case 129: /* struct_declaration: specifier_qualifier_list struct_declarator_list semi_colon  */
#line 1196 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Struct_Union_Declaration_Handler($1, $2);
    }
#line 3138 "parser.tab.c"
    break;

  case 130: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1208 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 3149 "parser.tab.c"
    break;

  case 131: /* specifier_qualifier_list: type_specifier  */
#line 1215 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3159 "parser.tab.c"
    break;

  case 132: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1221 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChildren((yyvsp[0].astNode)->children);
    }
#line 3170 "parser.tab.c"
    break;

  case 133: /* specifier_qualifier_list: type_qualifier  */
#line 1228 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3180 "parser.tab.c"
    break;

  case 134: /* struct_declarator_list: struct_declarator  */
#line 1237 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3190 "parser.tab.c"
    break;

  case 135: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1243 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3201 "parser.tab.c"
    break;

  case 136: /* struct_declarator: declarator  */
#line 1253 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3211 "parser.tab.c"
    break;

  case 137: /* struct_declarator: COLON constant_expression  */
#line 1259 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3222 "parser.tab.c"
    break;

  case 138: /* struct_declarator: declarator COLON constant_expression  */
#line 1266 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3234 "parser.tab.c"
    break;

  case 139: /* enum_specifier: ENUM LCURLY enumerator_list rcurly  */
#line 1277 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Enum_Declaration_Handler($$);
    }
#line 3248 "parser.tab.c"
    break;

  case 140: /* enum_specifier: ENUM identifier LCURLY enumerator_list rcurly  */
#line 1287 "parser.y"
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
#line 3263 "parser.tab.c"
    break;

  case 141: /* enum_specifier: ENUM identifier  */
#line 1298 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        // Enum_Declaration_Handler($$);
    }
#line 3275 "parser.tab.c"
    break;

  case 142: /* enumerator_list: enumerator  */
#line 1311 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("enumerator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3285 "parser.tab.c"
    break;

  case 143: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 1317 "parser.y"
    {
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3296 "parser.tab.c"
    break;

  case 144: /* enumerator: identifier  */
#line 1327 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3306 "parser.tab.c"
    break;

  case 145: /* enumerator: identifier ASSIGN constant_expression  */
#line 1333 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3318 "parser.tab.c"
    break;

  case 146: /* type_qualifier: CONST  */
#line 1344 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3328 "parser.tab.c"
    break;

  case 147: /* type_qualifier: VOLATILE  */
#line 1350 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3338 "parser.tab.c"
    break;

  case 148: /* declarator: pointer direct_declarator  */
#line 1359 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3349 "parser.tab.c"
    break;

  case 149: /* declarator: direct_declarator  */
#line 1366 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3359 "parser.tab.c"
    break;

  case 150: /* direct_declarator: identifier  */
#line 1375 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3369 "parser.tab.c"
    break;

  case 151: /* direct_declarator: LPAREN declarator rparen  */
#line 1381 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3381 "parser.tab.c"
    break;

  case 152: /* direct_declarator: direct_declarator LSQUARE constant_expression rsquare  */
#line 1389 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3394 "parser.tab.c"
    break;

  case 153: /* direct_declarator: direct_declarator LSQUARE rsquare  */
#line 1398 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3406 "parser.tab.c"
    break;

  case 154: /* direct_declarator: direct_declarator LPAREN parameter_type_list rparen  */
#line 1406 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3419 "parser.tab.c"
    break;

  case 155: /* direct_declarator: direct_declarator LPAREN identifier_list rparen  */
#line 1415 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3432 "parser.tab.c"
    break;

  case 156: /* direct_declarator: direct_declarator LPAREN rparen  */
#line 1424 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3444 "parser.tab.c"
    break;

  case 157: /* pointer: STAR  */
#line 1435 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3454 "parser.tab.c"
    break;

  case 158: /* pointer: STAR type_qualifier_list  */
#line 1441 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3465 "parser.tab.c"
    break;

  case 159: /* pointer: STAR pointer  */
#line 1448 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3476 "parser.tab.c"
    break;

  case 160: /* pointer: STAR type_qualifier_list pointer  */
#line 1455 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3488 "parser.tab.c"
    break;

  case 161: /* type_qualifier_list: type_qualifier  */
#line 1466 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3498 "parser.tab.c"
    break;

  case 162: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1472 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3508 "parser.tab.c"
    break;

  case 163: /* parameter_type_list: parameter_list  */
#line 1481 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3518 "parser.tab.c"
    break;

  case 164: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1487 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3530 "parser.tab.c"
    break;

  case 165: /* parameter_list: parameter_declaration  */
#line 1498 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3540 "parser.tab.c"
    break;

  case 166: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1504 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3551 "parser.tab.c"
    break;

  case 167: /* parameter_declaration: declaration_specifiers declarator  */
#line 1515 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3562 "parser.tab.c"
    break;

  case 168: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1522 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3573 "parser.tab.c"
    break;

  case 169: /* parameter_declaration: declaration_specifiers  */
#line 1529 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3583 "parser.tab.c"
    break;

  case 170: /* identifier_list: identifier  */
#line 1538 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("identifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3593 "parser.tab.c"
    break;

  case 171: /* identifier_list: identifier_list COMMA identifier  */
#line 1544 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3604 "parser.tab.c"
    break;

  case 172: /* type_name: specifier_qualifier_list  */
#line 1554 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3614 "parser.tab.c"
    break;

  case 173: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1560 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3625 "parser.tab.c"
    break;

  case 174: /* abstract_declarator: pointer  */
#line 1570 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3635 "parser.tab.c"
    break;

  case 175: /* abstract_declarator: direct_abstract_declarator  */
#line 1576 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3645 "parser.tab.c"
    break;

  case 176: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1582 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3656 "parser.tab.c"
    break;

  case 177: /* direct_abstract_declarator: LPAREN abstract_declarator rparen  */
#line 1592 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3668 "parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: LSQUARE rsquare  */
#line 1600 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3679 "parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: LSQUARE constant_expression rsquare  */
#line 1607 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3691 "parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE rsquare  */
#line 1615 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3702 "parser.tab.c"
    break;

  case 181: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression rsquare  */
#line 1622 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);  
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3714 "parser.tab.c"
    break;

  case 182: /* direct_abstract_declarator: LPAREN rparen  */
#line 1630 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3725 "parser.tab.c"
    break;

  case 183: /* direct_abstract_declarator: LPAREN parameter_type_list rparen  */
#line 1637 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3737 "parser.tab.c"
    break;

  case 184: /* direct_abstract_declarator: direct_abstract_declarator LPAREN rparen  */
#line 1645 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3748 "parser.tab.c"
    break;

  case 185: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list rparen  */
#line 1652 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3760 "parser.tab.c"
    break;

  case 186: /* initializer: assignment_expression  */
#line 1663 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3770 "parser.tab.c"
    break;

  case 187: /* initializer: LCURLY initializer_list rcurly  */
#line 1669 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3782 "parser.tab.c"
    break;

  case 188: /* initializer: LCURLY initializer_list COMMA rcurly  */
#line 1677 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3795 "parser.tab.c"
    break;

  case 189: /* initializer_list: initializer  */
#line 1689 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("initializer_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3805 "parser.tab.c"
    break;

  case 190: /* initializer_list: initializer_list COMMA initializer  */
#line 1695 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3816 "parser.tab.c"
    break;

  case 191: /* statement: labeled_statement  */
#line 1705 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3826 "parser.tab.c"
    break;

  case 192: /* statement: compound_statement  */
#line 1711 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3836 "parser.tab.c"
    break;

  case 193: /* statement: expression_statement  */
#line 1717 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3846 "parser.tab.c"
    break;

  case 194: /* statement: selection_statement  */
#line 1723 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3856 "parser.tab.c"
    break;

  case 195: /* statement: iteration_statement  */
#line 1729 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3866 "parser.tab.c"
    break;

  case 196: /* statement: jump_statement  */
#line 1735 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3876 "parser.tab.c"
    break;

  case 197: /* statement: declaration  */
#line 1741 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3886 "parser.tab.c"
    break;

  case 198: /* labeled_statement: identifier COLON statement  */
#line 1750 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3898 "parser.tab.c"
    break;

  case 199: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1758 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3911 "parser.tab.c"
    break;

  case 200: /* labeled_statement: DEFAULT COLON statement  */
#line 1767 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3923 "parser.tab.c"
    break;

  case 201: /* compound_statement: LCURLY rcurly  */
#line 1778 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3934 "parser.tab.c"
    break;

  case 202: /* compound_statement: LCURLY statement_list rcurly  */
#line 1785 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3946 "parser.tab.c"
    break;

  case 203: /* compound_statement: LCURLY declaration_list rcurly  */
#line 1793 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3958 "parser.tab.c"
    break;

  case 204: /* compound_statement: LCURLY declaration_list statement_list rcurly  */
#line 1801 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3971 "parser.tab.c"
    break;

  case 205: /* declaration_list: declaration  */
#line 1813 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3981 "parser.tab.c"
    break;

  case 206: /* declaration_list: declaration_list declaration  */
#line 1819 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3991 "parser.tab.c"
    break;

  case 207: /* statement_list: statement  */
#line 1829 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement_list"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4001 "parser.tab.c"
    break;

  case 208: /* statement_list: statement_list statement  */
#line 1835 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4011 "parser.tab.c"
    break;

  case 209: /* expression_statement: semi_colon  */
#line 1844 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4021 "parser.tab.c"
    break;

  case 210: /* expression_statement: expression semi_colon  */
#line 1850 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4032 "parser.tab.c"
    break;

  case 211: /* selection_statement: IF LPAREN expression rparen statement  */
#line 1860 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4046 "parser.tab.c"
    break;

  case 212: /* selection_statement: IF LPAREN expression rparen statement ELSE statement  */
#line 1870 "parser.y"
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
#line 4062 "parser.tab.c"
    break;

  case 213: /* selection_statement: SWITCH LPAREN expression rparen statement  */
#line 1882 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4076 "parser.tab.c"
    break;

  case 214: /* iteration_statement: WHILE LPAREN expression rparen statement  */
#line 1895 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4090 "parser.tab.c"
    break;

  case 215: /* iteration_statement: UNTIL LPAREN expression rparen statement  */
#line 1905 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4104 "parser.tab.c"
    break;

  case 216: /* iteration_statement: DO statement WHILE LPAREN expression rparen semi_colon  */
#line 1915 "parser.y"
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
#line 4120 "parser.tab.c"
    break;

  case 217: /* iteration_statement: FOR LPAREN expression_statement expression_statement rparen statement  */
#line 1927 "parser.y"
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
#line 4135 "parser.tab.c"
    break;

  case 218: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression rparen statement  */
#line 1938 "parser.y"
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
#line 4151 "parser.tab.c"
    break;

  case 219: /* iteration_statement: FOR LPAREN declaration expression_statement expression rparen statement  */
#line 1950 "parser.y"
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
#line 4167 "parser.tab.c"
    break;

  case 220: /* jump_statement: GOTO identifier semi_colon  */
#line 1965 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4179 "parser.tab.c"
    break;

  case 221: /* jump_statement: CONTINUE semi_colon  */
#line 1973 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4190 "parser.tab.c"
    break;

  case 222: /* jump_statement: BREAK semi_colon  */
#line 1980 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4201 "parser.tab.c"
    break;

  case 223: /* jump_statement: RETURN semi_colon  */
#line 1987 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4212 "parser.tab.c"
    break;

  case 224: /* jump_statement: RETURN expression semi_colon  */
#line 1994 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4224 "parser.tab.c"
    break;

  case 225: /* translation_unit: external_declaration  */
#line 2007 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("translation_unit");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        root = (yyval.astNode);
    }
#line 4235 "parser.tab.c"
    break;

  case 226: /* translation_unit: translation_unit external_declaration  */
#line 2014 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode);
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        root = (yyval.astNode);
    }
#line 4246 "parser.tab.c"
    break;

  case 227: /* external_declaration: function_definition  */
#line 2025 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4256 "parser.tab.c"
    break;

  case 228: /* external_declaration: declaration  */
#line 2031 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4266 "parser.tab.c"
    break;

  case 229: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 2042 "parser.y"
    { 
        LINE  
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4278 "parser.tab.c"
    break;

  case 230: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 2051 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        // Function_Def_Handler($2);
    }
#line 4291 "parser.tab.c"
    break;

  case 231: /* function_definition: declarator declaration_list compound_statement  */
#line 2060 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4303 "parser.tab.c"
    break;

  case 232: /* function_definition: declarator compound_statement  */
#line 2068 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4314 "parser.tab.c"
    break;


#line 4318 "parser.tab.c"

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

#line 2076 "parser.y"



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
