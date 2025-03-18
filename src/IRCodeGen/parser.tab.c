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

std::string whereWasILast;


#define LINE std::cerr<< "Production - " << __LINE__<<std::endl;
// #define LINE /**/
#define LINE1 std::cerr<< __LINE__<<std::endl;

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
    *output << "\U0001F6A8 * Input Program failed in the PARSE stage \U0001F6A8" << std::endl;
    *output << "Where was I Last: " << whereWasILast << std::endl;
    *output << std::endl;
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

#line 196 "parser.tab.c"

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
  YYSYMBOL_function_definition = 157       /* function_definition  */
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
#define YYLAST   1596

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  227
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  382

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
       0,   223,   223,   228,   237,   242,   251,   256,   265,   270,
     279,   284,   293,   298,   312,   318,   324,   330,   341,   347,
     356,   366,   375,   383,   391,   398,   408,   414,   425,   431,
     438,   445,   452,   459,   471,   477,   483,   489,   495,   501,
     510,   516,   529,   535,   543,   551,   562,   568,   576,   587,
     593,   601,   612,   618,   626,   634,   642,   653,   659,   667,
     678,   684,   695,   701,   712,   718,   729,   735,   746,   752,
     763,   769,   782,   788,   799,   805,   811,   817,   823,   829,
     835,   841,   847,   853,   859,   869,   875,   886,   895,   902,
     914,   920,   927,   933,   940,   946,   956,   962,   973,   979,
     990,   996,  1002,  1008,  1014,  1023,  1029,  1035,  1041,  1047,
    1053,  1059,  1065,  1071,  1077,  1083,  1089,  1098,  1109,  1118,
    1129,  1135,  1144,  1150,  1160,  1172,  1179,  1185,  1192,  1201,
    1207,  1218,  1224,  1231,  1242,  1252,  1263,  1276,  1282,  1293,
    1299,  1310,  1316,  1325,  1332,  1341,  1347,  1355,  1364,  1372,
    1381,  1390,  1401,  1407,  1414,  1421,  1432,  1438,  1448,  1454,
    1465,  1471,  1483,  1490,  1497,  1506,  1512,  1522,  1528,  1538,
    1544,  1550,  1560,  1568,  1575,  1583,  1590,  1598,  1605,  1613,
    1620,  1631,  1637,  1645,  1657,  1663,  1673,  1679,  1685,  1691,
    1697,  1703,  1709,  1718,  1726,  1735,  1746,  1753,  1761,  1769,
    1781,  1787,  1797,  1803,  1813,  1819,  1829,  1839,  1851,  1864,
    1874,  1884,  1896,  1907,  1919,  1934,  1942,  1949,  1956,  1963,
    1976,  1983,  1993,  1999,  2028,  2037,  2046,  2054
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

#define YYTABLE_NINF (-170)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     971,  -186,  -186,  -186,   248,   131,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,    16,  -186,  -186,    25,  1399,  1399,
    -186,   123,  -186,  1399,  1355,   158,   275,   695,  -186,  -186,
     142,  -186,  -186,   131,    68,     1,   466,  -186,  -186,    17,
    -186,  1336,  -186,  -186,   676,    73,  -186,   524,  -186,    25,
    -186,  1355,  1015,   929,   158,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,   -45,    98,  -186,    68,  -186,   248,  -186,  1295,
    -186,  1355,   676,  1103,  -186,   135,   676,   676,   380,  -186,
    -186,  1498,  1540,  1540,   837,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  1554,   -30,    96,   145,   155,   609,   182,    68,
       7,     7,  1276,   203,   129,  -186,  -186,  -186,  -186,   314,
     458,  1554,  -186,   281,   252,   325,    10,   324,    91,   190,
     195,   238,    74,  -186,  -186,    81,  -186,  -186,  -186,  -186,
     524,   524,  -186,  -186,  -186,  -186,   227,  -186,  -186,   269,
    -186,  -186,   209,   142,   265,  -186,   132,  1292,  -186,  -186,
    -186,  -186,  -186,    38,  1554,  -186,    68,  -186,    98,  -186,
    -186,  1295,  -186,  -186,  -186,  -186,  -186,  -186,  1554,    99,
    -186,   213,  -186,  1103,   837,  -186,  1554,  -186,  -186,   156,
     277,   142,   234,   609,  1554,  1554,  1554,  1174,  -186,   210,
     766,     7,  -186,  -186,  -186,    81,  1554,   609,    68,  -186,
    -186,  1484,  1554,    68,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  1554,  -186,  1554,  1554,  1554,
    1554,  1554,  1554,  1554,  1554,  1554,  1554,  1554,  1554,  1554,
    1554,  1554,  1554,  1554,  1554,  1554,  1554,  -186,  -186,  -186,
     524,  -186,  -186,   856,   929,  -186,   364,  -186,   211,  -186,
    1083,    68,  -186,  -186,  -186,  -186,  -186,  -186,  -186,   261,
    -186,   135,  -186,  1554,  -186,   142,  -186,   927,   219,  -186,
    1554,   609,  -186,   156,   156,   156,   274,  1276,  1276,  -186,
    -186,   156,  -186,  -186,  1226,  -186,   169,  -186,    47,  -186,
    -186,  -186,  -186,  -186,   281,   281,   252,   252,   325,   325,
     325,   325,    10,    10,   324,    91,   190,   195,   238,   140,
    -186,  -186,  -186,   142,   142,  -186,    38,   211,  1059,   929,
    -186,  -186,  -186,  1442,  -186,  -186,  -186,  -186,  -186,  -186,
     609,   609,   609,  1554,  1554,  1484,   609,  1554,  -186,  -186,
    1554,  -186,  -186,  -186,  -186,   142,  -186,    38,   256,  -186,
    -186,   233,  -186,  -186,   156,   156,   609,   156,  -186,  -186,
    -186,  -186,  -186,   609,     7,   609,  -186,   609,  -186,  -186,
    -186,  -186
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     2,   116,     0,   152,   100,   101,   102,   103,
     104,   106,   107,   108,   109,   112,   113,   110,   111,   141,
     142,   105,   120,   121,     0,   145,   223,     0,    90,    92,
     114,     0,   115,    94,     0,   144,     0,     0,   220,   222,
       0,   156,   154,   153,     0,   136,     3,     6,    88,     0,
      96,    98,    91,    93,     0,   119,    95,     0,   200,     0,
     227,     0,     0,     0,   143,     1,   221,     9,     8,   146,
     157,   155,   139,     0,   137,     0,     7,     0,    89,     0,
     225,     0,   126,     0,   122,     0,   128,     0,     3,     4,
      16,     0,     0,     0,     0,    10,    34,    35,    36,    37,
      38,    39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,    15,   204,   196,    18,    28,
      40,     0,    42,    46,    49,    52,    57,    60,    62,    64,
      66,    68,    70,    72,    85,     0,   192,   202,   186,   187,
       0,     0,   188,   189,   190,   191,    98,   201,   226,     9,
     165,   151,     0,     0,   158,   160,     0,     3,    12,    14,
     148,    40,    87,     0,     0,    11,     0,   134,     0,    97,
       3,     0,   181,    99,   224,   125,   118,   123,     0,     0,
     129,   131,   127,     0,     0,    32,     0,    29,    30,     0,
     167,     0,     0,     0,     0,     0,     0,     7,   192,     0,
       0,     0,   216,   217,   218,     0,     0,     0,     0,    24,
      25,     0,     0,     0,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    74,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,   198,   192,
       0,   197,   203,     0,     0,   162,     0,   163,   170,   149,
       0,     0,   150,    13,   147,   140,   138,   135,   184,     0,
     132,     0,   124,     0,   117,     0,    17,     0,   169,   168,
       0,     0,   195,     0,     0,     0,     0,     0,     0,   215,
     219,     0,   193,    23,     9,    20,     0,    26,     0,    22,
      73,    43,    44,    45,    47,    48,    50,    51,    55,    56,
      53,    54,    58,    59,    61,    63,    65,    67,    69,     0,
      86,   199,   177,     0,     0,   173,     0,   171,     0,     0,
     159,   161,   166,     0,   182,   130,   133,    33,    41,   194,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    19,
       0,   178,   172,   174,   179,     0,   175,     0,     3,   183,
     185,   206,   208,   209,     0,     0,     0,     0,   210,    27,
      71,   180,   176,     0,     0,     0,   212,     0,   207,   211,
     214,   213
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,     0,  -186,   -24,   -11,   -67,  -123,  -186,  -186,  -186,
     -13,  -186,  -109,   127,   146,   170,   150,    86,    77,    88,
      85,   101,  -186,   -18,   -58,  -186,   175,   -72,     9,     5,
    -186,   271,  -186,    11,  -186,  -186,   264,   -73,    62,  -186,
      84,  -186,   285,   196,   309,    37,   -23,     6,  -186,   -60,
    -186,   104,  -186,   184,  -138,  -141,  -170,  -186,   -46,  -186,
      78,    70,   232,  -185,  -186,  -186,  -186,  -186,   337,  -186
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   159,   115,   116,   322,   117,   160,   118,   119,   296,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   225,   135,   163,   198,    59,
      49,    50,    28,    29,    30,    31,    83,    84,    85,   179,
     180,    32,    73,    74,    33,    34,    35,    36,    43,   323,
     154,   155,   156,   191,   324,   258,   173,   269,   137,   138,
     139,    61,   141,   142,   143,   144,   145,    37,    38,    39
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,   268,   153,    48,    25,    27,   167,   164,    76,    26,
     177,    42,   226,    64,   257,   288,   176,     1,    76,     2,
     193,   172,   234,   235,    45,    78,    46,    25,     2,    69,
     192,    55,    75,    52,    53,    48,    25,    25,    56,   263,
     264,    40,    27,    58,    72,   162,    26,    44,   263,    71,
     161,   151,   279,    77,     4,   236,   237,   114,    47,    25,
      58,   199,   150,     5,    51,    82,   136,   152,    47,     1,
     147,     2,   158,   248,   251,    72,    47,    25,   185,   187,
     188,   158,    76,   246,   162,    25,   202,   203,   204,   161,
     147,   244,   265,    82,    82,   252,   146,    82,    82,   165,
      76,   267,   344,   345,    87,    82,   270,   114,   161,   201,
     177,   247,    60,   172,   146,   327,   274,   246,   301,   302,
     303,    81,   181,   245,     1,   194,     2,   140,   240,    80,
      95,   325,    47,    67,   166,   271,     1,   327,     2,   148,
     114,   114,   259,    67,   175,   262,   162,   282,   182,   249,
      47,   161,    25,   297,    54,   272,   190,    67,   256,   174,
     162,   292,    68,   360,     4,   161,    72,   300,   261,     5,
      67,   338,    68,     5,   195,   349,   246,   289,   276,   207,
     280,   290,   326,   321,   196,   178,    68,    62,   320,   255,
     350,    63,   246,   114,    82,    82,   278,    19,    20,    68,
     295,   336,   334,   353,   252,   347,   356,   114,   293,   287,
       1,   200,     2,   299,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   206,    64,   372,   339,   162,   241,   253,  -164,
     328,   161,   254,   242,   329,  -164,   190,     5,   277,     1,
     114,     2,   254,    25,   243,   162,    25,   357,   152,   256,
     161,   332,   165,   273,   337,   152,   359,   161,   355,   189,
      -3,    25,   340,   341,   342,   172,     1,     4,     2,    79,
     346,   114,   152,   278,   281,   348,     5,   205,   286,   369,
      40,   230,   231,    95,   361,   362,   363,   333,    -3,    -3,
     368,   260,    -3,   343,     4,    -3,   277,   -11,   181,   373,
     254,   162,   351,   352,    41,     5,   161,   354,   315,   227,
     376,   208,   209,   210,   228,   229,   314,   378,   317,   380,
     316,   381,   370,   152,   366,   232,   233,   161,   238,   239,
     114,   114,   114,   211,   371,   318,   114,   212,   169,   213,
     379,   183,    70,   374,   375,   335,   377,   304,   305,   189,
     168,   189,   266,    86,   331,     1,   114,     2,   275,   283,
     284,   285,   250,   114,    66,   114,     0,   114,   306,   307,
     -11,   291,     0,    -7,    -7,    -7,    -7,   298,   312,   313,
       0,    86,    86,   253,  -169,    86,    86,   254,     0,     0,
    -169,     0,     0,    86,   308,   309,   310,   311,    -7,     0,
       0,    -7,    -7,     0,     0,     0,     0,     0,     0,     0,
     319,    -7,    -7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,     0,    -7,    -7,    -7,   -11,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,     0,     0,    -7,
      -7,    -7,    -7,     0,    -7,    -7,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,     0,     0,     0,     0,
       0,     0,    86,    86,     0,     0,     0,     0,    -7,     0,
       0,     0,     0,    -7,    -7,    -7,    -7,    -7,    -7,     0,
     224,     0,     0,     0,     0,     0,     0,     0,   364,   365,
     367,     0,     0,     0,     0,    88,     0,     2,    89,    90,
      91,     0,    92,    93,     0,     0,     0,     0,     0,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,     3,    94,     0,    57,    95,     0,     0,     0,
       0,    96,    97,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,    47,     0,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,   102,   103,   104,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     197,     0,     2,    89,    90,    91,     0,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,    94,     0,
      57,     0,     0,     0,     0,     0,    96,    97,    98,    99,
     100,   101,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,   102,   103,   104,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    65,     1,     0,     2,     0,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     5,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   197,     0,     2,
      89,    90,    91,     0,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,    94,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,   100,   101,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   170,     0,
       2,    89,    90,    91,     0,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   149,     0,     2,
       0,     0,     0,     0,     0,     3,    94,     0,     0,     0,
       0,     0,     0,     0,    96,    97,    98,    99,   100,   101,
       0,     0,     0,     0,     3,   253,    68,     0,     0,   254,
       0,     0,     0,     0,     5,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    67,     0,
     157,     0,     2,    89,    90,    91,     0,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,   277,    68,    94,     0,
     254,     0,     0,   158,     0,     5,    96,    97,    98,    99,
     100,   101,     1,     0,     2,     0,     0,     0,     0,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     3,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     0,     0,     0,     0,   149,     0,     2,     0,
       0,     0,     0,     0,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     3,     0,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     3,     0,    68,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165,     0,     0,     0,     0,     0,
       0,     3,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     3,     0,     0,     0,    95,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   330,     0,     0,     0,     0,
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    -3,     0,     0,     0,     0,
       0,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,     0,    -3,     0,     0,     0,    -3,     0,    -3,
      -3,    -3,    -3,    -3,    -3,     0,     0,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,     0,     0,
       0,     0,     0,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,     0,    -3,    -3,     0,     0,    -3,
       0,    -3,    -3,    -3,    -3,    -3,    -3,     0,     0,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,     0,   197,    -3,     2,
      89,    90,    91,     0,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,     0,     2,    89,
      90,    91,     0,    92,    93,    94,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,   100,   101,     0,
     -13,     0,   -13,   -13,    94,     0,   171,    47,   -13,     0,
       0,     0,    96,    97,    98,    99,   100,   101,     0,     0,
       0,     0,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,   -13,   -13,     3,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,    57,     0,    79,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   358,     0,     2,    89,    90,    91,     0,
      92,    93,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    94,     0,   171,    95,     0,     0,     0,     0,    96,
      97,    98,    99,   100,   101,   294,     0,     2,    89,    90,
      91,     0,    92,    93,     0,     0,     0,     0,     0,   170,
       0,     2,    89,    90,    91,     0,    92,    93,     0,     0,
       0,     0,     0,    94,    68,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,   100,   101,   184,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,   100,
     101,   170,     0,     2,    89,    90,    91,     0,    92,    93,
       0,     0,     0,     0,     0,   170,     0,     2,    89,    90,
      91,     0,    92,    93,     0,     0,     0,     0,     0,   186,
       0,     0,     0,     0,     0,     0,     0,    96,    97,    98,
      99,   100,   101,    94,     0,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
       0,   171,    62,    27,     4,     0,    73,    52,     1,     0,
      83,     5,   121,    36,   152,   200,    83,     1,     1,     3,
      50,    79,    12,    13,    24,    49,     1,    27,     3,    40,
     102,    31,    31,    28,    29,    59,    36,    37,    33,     1,
     163,     4,    37,    34,    44,    63,    37,    31,     1,    43,
      63,    62,   190,    36,    29,    45,    46,    57,    51,    59,
      51,   107,    62,    38,    27,    54,    57,    62,    51,     1,
      61,     3,    34,   140,   141,    75,    51,    77,    91,    92,
      93,    34,     1,    36,   102,    85,   110,   111,   112,   102,
      81,    17,   164,    82,    83,   141,    59,    86,    87,     1,
       1,   168,   287,   288,    31,    94,   178,   107,   121,   109,
     183,   135,    34,   171,    77,   256,   183,    36,   227,   228,
     229,    51,    85,    49,     1,    29,     3,    57,    37,    51,
      32,   254,    51,     1,    36,    36,     1,   278,     3,    61,
     140,   141,   153,     1,    82,   156,   164,   193,    86,   140,
      51,   164,   152,   211,    31,   179,    94,     1,   152,    81,
     178,   207,    30,   333,    29,   178,   166,   225,    36,    38,
       1,   280,    30,    38,    29,   298,    36,   201,   189,    50,
     191,   205,   254,   250,    29,    50,    30,    29,   246,   152,
      50,    33,    36,   193,   183,   184,   190,    66,    67,    30,
     211,   273,   269,   326,   250,    36,   329,   207,   208,   200,
       1,    29,     3,   213,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,    29,   256,   357,   281,   254,    47,    29,    30,
      29,   254,    33,    48,    33,    36,   184,    38,    29,     1,
     250,     3,    33,   253,    16,   273,   256,   329,   253,   253,
     273,   261,     1,    50,   275,   260,   333,   280,   328,    94,
       1,   271,   283,   284,   285,   333,     1,    29,     3,    52,
     291,   281,   277,   277,    50,   296,    38,   112,    78,   347,
     253,    39,    40,    32,   340,   341,   342,    36,    29,    30,
     346,    36,    33,    29,    29,    36,    29,    51,   271,    76,
      33,   329,   323,   324,     5,    38,   329,   328,   241,    38,
     366,     7,     8,     9,    43,    44,   240,   373,   243,   375,
     242,   377,   350,   328,   345,    10,    11,   350,    14,    15,
     340,   341,   342,    29,   355,   244,   346,    33,    77,    35,
     374,    87,    43,   364,   365,   271,   367,   230,   231,   184,
      75,   186,   166,    54,   260,     1,   366,     3,   184,   194,
     195,   196,   140,   373,    37,   375,    -1,   377,   232,   233,
       0,   206,    -1,     3,     4,     5,     6,   212,   238,   239,
      -1,    82,    83,    29,    30,    86,    87,    33,    -1,    -1,
      36,    -1,    -1,    94,   234,   235,   236,   237,    28,    -1,
      -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     245,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,     0,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,   183,   184,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   343,   344,
     345,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    28,    29,    -1,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    85,
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    -1,    73,    74,    75,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     0,     1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    29,    -1,
      33,    -1,    -1,    34,    -1,    38,    37,    38,    39,    40,
      41,    42,     1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    28,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    28,    -1,    -1,    -1,    32,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     1,    -1,    -1,    -1,    -1,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    29,    -1,    -1,    -1,    33,    -1,    35,
      36,    37,    38,    39,    40,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     1,    -1,    -1,
      -1,    -1,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    29,    30,    -1,    -1,    33,
      -1,    35,    36,    37,    38,    39,    40,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,     1,    52,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    -1,
      28,    -1,    30,    31,    29,    -1,    31,    51,    36,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    28,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    31,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    29,    -1,    31,    32,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,     1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    28,    29,    38,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    89,   116,   117,   120,   121,
     122,   123,   129,   132,   133,   134,   135,   155,   156,   157,
     133,   132,   135,   136,    31,    89,     1,    51,    91,   118,
     119,   133,   117,   117,    31,    89,   117,    31,   116,   117,
     148,   149,    29,    33,   134,     0,   156,     1,    30,    92,
     132,   135,    89,   130,   131,    31,     1,    36,    91,    52,
     148,   149,   121,   124,   125,   126,   132,    31,     1,     4,
       5,     6,     8,     9,    29,    32,    37,    38,    39,    40,
      41,    42,    73,    74,    75,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    89,    90,    91,    93,    95,    96,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   114,   116,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   133,   116,   148,     1,
      89,    92,   117,   137,   138,   139,   140,     1,    34,    89,
      94,    98,   111,   115,    52,     1,    36,    93,   130,   119,
       1,    31,   112,   144,   148,   126,    93,   125,    50,   127,
     128,   133,   126,   124,    29,    98,    29,    98,    98,   114,
     126,   141,   115,    50,    29,    29,    29,     1,   116,   146,
      29,    89,    91,    91,    91,   114,    29,    50,     7,     8,
       9,    29,    33,    35,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    52,   113,   100,    38,    43,    44,
      39,    40,    10,    11,    12,    13,    45,    46,    14,    15,
      37,    47,    48,    16,    17,    49,    36,    91,    93,   116,
     150,    93,   146,    29,    33,   133,   135,   142,   143,    92,
      36,    36,    92,     1,    94,   115,   131,    93,   144,   145,
     115,    36,    91,    50,    93,   141,    92,    29,   135,   142,
      92,    50,   146,   114,   114,   114,    78,   116,   151,    91,
      91,   114,   146,    89,     1,    92,    97,   112,   114,    89,
     112,   100,   100,   100,   101,   101,   102,   102,   103,   103,
     103,   103,   104,   104,   105,   106,   107,   108,   109,   114,
     112,    93,    92,   137,   142,    94,   115,   143,    29,    33,
      72,   139,    89,    36,    93,   128,   115,    92,   100,   146,
      92,    92,    92,    29,   151,   151,    92,    36,    92,    94,
      50,    92,    92,    94,    92,   137,    94,   115,     1,    93,
     144,   146,   146,   146,   114,   114,    92,   114,   146,   112,
     111,    92,    94,    76,    92,    92,   146,    92,   146,    91,
     146,   146
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
     155,   155,   156,   156,   157,   157,   157,   157
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
       1,     2,     1,     1,     4,     3,     3,     2
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
#line 224 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1883 "parser.tab.c"
    break;

  case 3: /* identifier: error  */
#line 229 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "Identifier");
            ourError("Expected an ID or Expression");
        }
#line 1893 "parser.tab.c"
    break;

  case 4: /* constant: CONSTANT  */
#line 238 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1902 "parser.tab.c"
    break;

  case 5: /* constant: error  */
#line 243 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "Constant");
            ourError("Expected a Constant or Expression");
        }
#line 1912 "parser.tab.c"
    break;

  case 6: /* semi_colon: SEMI_COLON  */
#line 252 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1921 "parser.tab.c"
    break;

  case 7: /* semi_colon: error  */
#line 257 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "SemiColon");
            ourError("Expected a SemiColon");
        }
#line 1931 "parser.tab.c"
    break;

  case 8: /* rparen: RPAREN  */
#line 266 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1940 "parser.tab.c"
    break;

  case 9: /* rparen: error  */
#line 271 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "RParen");
            ourError("Expected a Right Parenthesis");
        }
#line 1950 "parser.tab.c"
    break;

  case 10: /* rcurly: RCURLY  */
#line 280 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1959 "parser.tab.c"
    break;

  case 11: /* rcurly: error  */
#line 285 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "RCurly");
            ourError("Expected a Right Curly Brace");
        }
#line 1969 "parser.tab.c"
    break;

  case 12: /* rsquare: RSQUARE  */
#line 294 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode((yyvsp[0].tokenAtr));
        }
#line 1978 "parser.tab.c"
    break;

  case 13: /* rsquare: error  */
#line 299 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("Error", "RSquare");
            ourError("Expected a Right Square Bracket");
        }
#line 1988 "parser.tab.c"
    break;

  case 14: /* primary_expression: identifier  */
#line 313 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 1998 "parser.tab.c"
    break;

  case 15: /* primary_expression: constant  */
#line 319 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2008 "parser.tab.c"
    break;

  case 16: /* primary_expression: STRING_LITERAL  */
#line 325 "parser.y"
        { 
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
        }
#line 2018 "parser.tab.c"
    break;

  case 17: /* primary_expression: LPAREN expression rparen  */
#line 331 "parser.y"
        {   
            LINE
            (yyval.astNode) = new ASTNode("primary_expression");
            (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
            (yyval.astNode)->addChild((yyvsp[-1].astNode));
            (yyval.astNode)->addChild((yyvsp[0].astNode));
        }
#line 2030 "parser.tab.c"
    break;

  case 18: /* postfix_expression: primary_expression  */
#line 342 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2040 "parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression LSQUARE expression rsquare  */
#line 348 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2053 "parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression LPAREN rparen  */
#line 357 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        //-
        //PARSER_TABLE.push_back({$1->position, {$1->value, "function call"}});
    }
#line 2067 "parser.tab.c"
    break;

  case 21: /* postfix_expression: postfix_expression LPAREN argument_expression_list rparen  */
#line 367 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2080 "parser.tab.c"
    break;

  case 22: /* postfix_expression: postfix_expression DOT identifier  */
#line 376 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2092 "parser.tab.c"
    break;

  case 23: /* postfix_expression: postfix_expression PTR_OP identifier  */
#line 384 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2104 "parser.tab.c"
    break;

  case 24: /* postfix_expression: postfix_expression INC_OP  */
#line 392 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2115 "parser.tab.c"
    break;

  case 25: /* postfix_expression: postfix_expression DEC_OP  */
#line 399 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("postfix_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2126 "parser.tab.c"
    break;

  case 26: /* argument_expression_list: assignment_expression  */
#line 409 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("argument_expression_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2136 "parser.tab.c"
    break;

  case 27: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 415 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("argument_expression_list");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2148 "parser.tab.c"
    break;

  case 28: /* unary_expression: postfix_expression  */
#line 426 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2158 "parser.tab.c"
    break;

  case 29: /* unary_expression: INC_OP unary_expression  */
#line 432 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2169 "parser.tab.c"
    break;

  case 30: /* unary_expression: DEC_OP unary_expression  */
#line 439 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2180 "parser.tab.c"
    break;

  case 31: /* unary_expression: unary_operator cast_expression  */
#line 446 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2191 "parser.tab.c"
    break;

  case 32: /* unary_expression: SIZEOF unary_expression  */
#line 453 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("unary_expression");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2202 "parser.tab.c"
    break;

  case 33: /* unary_expression: SIZEOF LPAREN type_name rparen  */
#line 460 "parser.y"
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

  case 34: /* unary_operator: BIT_AND  */
#line 472 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2225 "parser.tab.c"
    break;

  case 35: /* unary_operator: STAR  */
#line 478 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr)); 
    }
#line 2235 "parser.tab.c"
    break;

  case 36: /* unary_operator: PLUS  */
#line 484 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr)); 
    }
#line 2245 "parser.tab.c"
    break;

  case 37: /* unary_operator: MINUS  */
#line 490 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr)); 
    }
#line 2255 "parser.tab.c"
    break;

  case 38: /* unary_operator: BIT_NOT  */
#line 496 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr)); 
    }
#line 2265 "parser.tab.c"
    break;

  case 39: /* unary_operator: NOT_OP  */
#line 502 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("unary_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr)); 
    }
#line 2275 "parser.tab.c"
    break;

  case 40: /* cast_expression: unary_expression  */
#line 511 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("cast_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2285 "parser.tab.c"
    break;

  case 41: /* cast_expression: LPAREN type_name rparen cast_expression  */
#line 517 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("cast_expression");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2298 "parser.tab.c"
    break;

  case 42: /* multiplicative_expression: cast_expression  */
#line 530 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2308 "parser.tab.c"
    break;

  case 43: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 536 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2320 "parser.tab.c"
    break;

  case 44: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 544 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2332 "parser.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 552 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("multiplicative_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2344 "parser.tab.c"
    break;

  case 46: /* additive_expression: multiplicative_expression  */
#line 563 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2354 "parser.tab.c"
    break;

  case 47: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 569 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2366 "parser.tab.c"
    break;

  case 48: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 577 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("additive_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2378 "parser.tab.c"
    break;

  case 49: /* shift_expression: additive_expression  */
#line 588 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2388 "parser.tab.c"
    break;

  case 50: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 594 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2400 "parser.tab.c"
    break;

  case 51: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 602 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("shift_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2412 "parser.tab.c"
    break;

  case 52: /* relational_expression: shift_expression  */
#line 613 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2422 "parser.tab.c"
    break;

  case 53: /* relational_expression: relational_expression LESSER_OP shift_expression  */
#line 619 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2434 "parser.tab.c"
    break;

  case 54: /* relational_expression: relational_expression GREATER_OP shift_expression  */
#line 627 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2446 "parser.tab.c"
    break;

  case 55: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 635 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2458 "parser.tab.c"
    break;

  case 56: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 643 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("relational_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2470 "parser.tab.c"
    break;

  case 57: /* equality_expression: relational_expression  */
#line 654 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2480 "parser.tab.c"
    break;

  case 58: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 660 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2492 "parser.tab.c"
    break;

  case 59: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 668 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("equality_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2504 "parser.tab.c"
    break;

  case 60: /* and_expression: equality_expression  */
#line 679 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("and_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2514 "parser.tab.c"
    break;

  case 61: /* and_expression: and_expression BIT_AND equality_expression  */
#line 685 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("and_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2526 "parser.tab.c"
    break;

  case 62: /* exclusive_or_expression: and_expression  */
#line 696 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("exclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2536 "parser.tab.c"
    break;

  case 63: /* exclusive_or_expression: exclusive_or_expression XOR and_expression  */
#line 702 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("exclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2548 "parser.tab.c"
    break;

  case 64: /* inclusive_or_expression: exclusive_or_expression  */
#line 713 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("inclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2558 "parser.tab.c"
    break;

  case 65: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 719 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("inclusive_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2570 "parser.tab.c"
    break;

  case 66: /* logical_and_expression: inclusive_or_expression  */
#line 730 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_and_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2580 "parser.tab.c"
    break;

  case 67: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 736 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_and_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2592 "parser.tab.c"
    break;

  case 68: /* logical_or_expression: logical_and_expression  */
#line 747 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_or_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2602 "parser.tab.c"
    break;

  case 69: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 753 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("logical_or_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2614 "parser.tab.c"
    break;

  case 70: /* conditional_expression: logical_or_expression  */
#line 764 "parser.y"
    { 
        LINE  
        (yyval.astNode) = new ASTNode("conditional_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2624 "parser.tab.c"
    break;

  case 71: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 770 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("conditional_expression");
        (yyval.astNode)->addChild((yyvsp[-4].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2638 "parser.tab.c"
    break;

  case 72: /* assignment_expression: conditional_expression  */
#line 783 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2648 "parser.tab.c"
    break;

  case 73: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 789 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_expression");
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2660 "parser.tab.c"
    break;

  case 74: /* assignment_operator: ASSIGN  */
#line 800 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2670 "parser.tab.c"
    break;

  case 75: /* assignment_operator: MUL_ASSIGN  */
#line 806 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2680 "parser.tab.c"
    break;

  case 76: /* assignment_operator: DIV_ASSIGN  */
#line 812 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2690 "parser.tab.c"
    break;

  case 77: /* assignment_operator: MOD_ASSIGN  */
#line 818 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2700 "parser.tab.c"
    break;

  case 78: /* assignment_operator: ADD_ASSIGN  */
#line 824 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2710 "parser.tab.c"
    break;

  case 79: /* assignment_operator: SUB_ASSIGN  */
#line 830 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2720 "parser.tab.c"
    break;

  case 80: /* assignment_operator: LEFT_ASSIGN  */
#line 836 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2730 "parser.tab.c"
    break;

  case 81: /* assignment_operator: RIGHT_ASSIGN  */
#line 842 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2740 "parser.tab.c"
    break;

  case 82: /* assignment_operator: AND_ASSIGN  */
#line 848 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2750 "parser.tab.c"
    break;

  case 83: /* assignment_operator: XOR_ASSIGN  */
#line 854 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2760 "parser.tab.c"
    break;

  case 84: /* assignment_operator: OR_ASSIGN  */
#line 860 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("assignment_operator");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2770 "parser.tab.c"
    break;

  case 85: /* expression: assignment_expression  */
#line 870 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2780 "parser.tab.c"
    break;

  case 86: /* expression: expression COMMA assignment_expression  */
#line 876 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("expression"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2792 "parser.tab.c"
    break;

  case 87: /* constant_expression: conditional_expression  */
#line 887 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("constant_expression");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2802 "parser.tab.c"
    break;

  case 88: /* declaration: declaration_specifiers semi_colon  */
#line 896 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2813 "parser.tab.c"
    break;

  case 89: /* declaration: declaration_specifiers init_declarator_list semi_colon  */
#line 903 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));  
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        Declaration_Handler((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 2826 "parser.tab.c"
    break;

  case 90: /* declaration_specifiers: storage_class_specifier  */
#line 915 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2836 "parser.tab.c"
    break;

  case 91: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 921 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2847 "parser.tab.c"
    break;

  case 92: /* declaration_specifiers: type_specifier  */
#line 928 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2857 "parser.tab.c"
    break;

  case 93: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 934 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2868 "parser.tab.c"
    break;

  case 94: /* declaration_specifiers: type_qualifier  */
#line 941 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2878 "parser.tab.c"
    break;

  case 95: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 947 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("declaration_specifiers");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2889 "parser.tab.c"
    break;

  case 96: /* init_declarator_list: init_declarator  */
#line 957 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("init_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2899 "parser.tab.c"
    break;

  case 97: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 963 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("init_declarator_list");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 2911 "parser.tab.c"
    break;

  case 98: /* init_declarator: declarator  */
#line 974 "parser.y"
    {
        LINE  
        (yyval.astNode) = new ASTNode("init_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2921 "parser.tab.c"
    break;

  case 99: /* init_declarator: declarator ASSIGN initializer  */
#line 980 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("init_declarator"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 2933 "parser.tab.c"
    break;

  case 100: /* storage_class_specifier: TYPEDEF  */
#line 991 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2943 "parser.tab.c"
    break;

  case 101: /* storage_class_specifier: EXTERN  */
#line 997 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2953 "parser.tab.c"
    break;

  case 102: /* storage_class_specifier: STATIC  */
#line 1003 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2963 "parser.tab.c"
    break;

  case 103: /* storage_class_specifier: AUTO  */
#line 1009 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2973 "parser.tab.c"
    break;

  case 104: /* storage_class_specifier: REGISTER  */
#line 1015 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("storage_class_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2983 "parser.tab.c"
    break;

  case 105: /* type_specifier: VOID  */
#line 1024 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 2993 "parser.tab.c"
    break;

  case 106: /* type_specifier: CHAR  */
#line 1030 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3003 "parser.tab.c"
    break;

  case 107: /* type_specifier: SHORT  */
#line 1036 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3013 "parser.tab.c"
    break;

  case 108: /* type_specifier: INT  */
#line 1042 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3023 "parser.tab.c"
    break;

  case 109: /* type_specifier: LONG  */
#line 1048 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3033 "parser.tab.c"
    break;

  case 110: /* type_specifier: FLOAT  */
#line 1054 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3043 "parser.tab.c"
    break;

  case 111: /* type_specifier: DOUBLE  */
#line 1060 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3053 "parser.tab.c"
    break;

  case 112: /* type_specifier: SIGNED  */
#line 1066 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3063 "parser.tab.c"
    break;

  case 113: /* type_specifier: UNSIGNED  */
#line 1072 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3073 "parser.tab.c"
    break;

  case 114: /* type_specifier: struct_or_union_specifier  */
#line 1078 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3083 "parser.tab.c"
    break;

  case 115: /* type_specifier: enum_specifier  */
#line 1084 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3093 "parser.tab.c"
    break;

  case 116: /* type_specifier: TYPE_NAME  */
#line 1090 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("type_specifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3103 "parser.tab.c"
    break;

  case 117: /* struct_or_union_specifier: struct_or_union identifier LCURLY struct_declaration_list rcurly  */
#line 1099 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-4].astNode));
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        PARSER_TABLE.push_back({(yyvsp[-3].astNode)->position, {(yyvsp[-3].astNode)->value, (yyvsp[-4].astNode)->value}});
    }
#line 3118 "parser.tab.c"
    break;

  case 118: /* struct_or_union_specifier: struct_or_union LCURLY struct_declaration_list rcurly  */
#line 1110 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3131 "parser.tab.c"
    break;

  case 119: /* struct_or_union_specifier: struct_or_union identifier  */
#line 1119 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        PARSER_TABLE.push_back({(yyvsp[0].astNode)->position, {(yyvsp[0].astNode)->value, (yyvsp[-1].astNode)->value}});
    }
#line 3143 "parser.tab.c"
    break;

  case 120: /* struct_or_union: STRUCT  */
#line 1130 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3153 "parser.tab.c"
    break;

  case 121: /* struct_or_union: UNION  */
#line 1136 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_or_union");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3163 "parser.tab.c"
    break;

  case 122: /* struct_declaration_list: struct_declaration  */
#line 1145 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3173 "parser.tab.c"
    break;

  case 123: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1151 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration_list");
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3184 "parser.tab.c"
    break;

  case 124: /* struct_declaration: specifier_qualifier_list struct_declarator_list semi_colon  */
#line 1161 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("struct_declaration");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        Struct_Union_Declaration_Handler((yyvsp[-2].astNode), (yyvsp[-1].astNode));
    }
#line 3197 "parser.tab.c"
    break;

  case 125: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1173 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3208 "parser.tab.c"
    break;

  case 126: /* specifier_qualifier_list: type_specifier  */
#line 1180 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3218 "parser.tab.c"
    break;

  case 127: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1186 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3229 "parser.tab.c"
    break;

  case 128: /* specifier_qualifier_list: type_qualifier  */
#line 1193 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("specifier_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3239 "parser.tab.c"
    break;

  case 129: /* struct_declarator_list: struct_declarator  */
#line 1202 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3249 "parser.tab.c"
    break;

  case 130: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1208 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator_list");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3261 "parser.tab.c"
    break;

  case 131: /* struct_declarator: declarator  */
#line 1219 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3271 "parser.tab.c"
    break;

  case 132: /* struct_declarator: COLON constant_expression  */
#line 1225 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3282 "parser.tab.c"
    break;

  case 133: /* struct_declarator: declarator COLON constant_expression  */
#line 1232 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("struct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3294 "parser.tab.c"
    break;

  case 134: /* enum_specifier: ENUM LCURLY enumerator_list rcurly  */
#line 1243 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3308 "parser.tab.c"
    break;

  case 135: /* enum_specifier: ENUM identifier LCURLY enumerator_list rcurly  */
#line 1253 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3323 "parser.tab.c"
    break;

  case 136: /* enum_specifier: ENUM identifier  */
#line 1264 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enum_specifier");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
        Enum_Declaration_Handler((yyval.astNode));
    }
#line 3335 "parser.tab.c"
    break;

  case 137: /* enumerator_list: enumerator  */
#line 1277 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("enumerator_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3345 "parser.tab.c"
    break;

  case 138: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 1283 "parser.y"
    {
        LINE 
        (yyval.astNode) = new ASTNode("enumerator_list");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3357 "parser.tab.c"
    break;

  case 139: /* enumerator: identifier  */
#line 1294 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3367 "parser.tab.c"
    break;

  case 140: /* enumerator: identifier ASSIGN constant_expression  */
#line 1300 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("enumerator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3379 "parser.tab.c"
    break;

  case 141: /* type_qualifier: CONST  */
#line 1311 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3389 "parser.tab.c"
    break;

  case 142: /* type_qualifier: VOLATILE  */
#line 1317 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3399 "parser.tab.c"
    break;

  case 143: /* declarator: pointer direct_declarator  */
#line 1326 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3410 "parser.tab.c"
    break;

  case 144: /* declarator: direct_declarator  */
#line 1333 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3420 "parser.tab.c"
    break;

  case 145: /* direct_declarator: identifier  */
#line 1342 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3430 "parser.tab.c"
    break;

  case 146: /* direct_declarator: LPAREN declarator rparen  */
#line 1348 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3442 "parser.tab.c"
    break;

  case 147: /* direct_declarator: direct_declarator LSQUARE constant_expression rsquare  */
#line 1356 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3455 "parser.tab.c"
    break;

  case 148: /* direct_declarator: direct_declarator LSQUARE rsquare  */
#line 1365 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3467 "parser.tab.c"
    break;

  case 149: /* direct_declarator: direct_declarator LPAREN parameter_type_list rparen  */
#line 1373 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3480 "parser.tab.c"
    break;

  case 150: /* direct_declarator: direct_declarator LPAREN identifier_list rparen  */
#line 1382 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-3].astNode));
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3493 "parser.tab.c"
    break;

  case 151: /* direct_declarator: direct_declarator LPAREN rparen  */
#line 1391 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3505 "parser.tab.c"
    break;

  case 152: /* pointer: STAR  */
#line 1402 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3515 "parser.tab.c"
    break;

  case 153: /* pointer: STAR type_qualifier_list  */
#line 1408 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3526 "parser.tab.c"
    break;

  case 154: /* pointer: STAR pointer  */
#line 1415 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3537 "parser.tab.c"
    break;

  case 155: /* pointer: STAR type_qualifier_list pointer  */
#line 1422 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("pointer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3549 "parser.tab.c"
    break;

  case 156: /* type_qualifier_list: type_qualifier  */
#line 1433 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3559 "parser.tab.c"
    break;

  case 157: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1439 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("type_qualifier_list");
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3570 "parser.tab.c"
    break;

  case 158: /* parameter_type_list: parameter_list  */
#line 1449 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3580 "parser.tab.c"
    break;

  case 159: /* parameter_type_list: parameter_list COMMA ELLIPSIS  */
#line 1455 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_type_list");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].tokenAtr));
    }
#line 3592 "parser.tab.c"
    break;

  case 160: /* parameter_list: parameter_declaration  */
#line 1466 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3602 "parser.tab.c"
    break;

  case 161: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1472 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("parameter_list");
        (yyval.astNode)->addChildren((yyvsp[-2].astNode)->children);
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3614 "parser.tab.c"
    break;

  case 162: /* parameter_declaration: declaration_specifiers declarator  */
#line 1484 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3625 "parser.tab.c"
    break;

  case 163: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1491 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));  
        (yyval.astNode)->addChild((yyvsp[0].astNode));  
    }
#line 3636 "parser.tab.c"
    break;

  case 164: /* parameter_declaration: declaration_specifiers  */
#line 1498 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("parameter_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3646 "parser.tab.c"
    break;

  case 165: /* identifier_list: identifier  */
#line 1507 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("identifier_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3656 "parser.tab.c"
    break;

  case 166: /* identifier_list: identifier_list COMMA identifier  */
#line 1513 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3667 "parser.tab.c"
    break;

  case 167: /* type_name: specifier_qualifier_list  */
#line 1523 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3677 "parser.tab.c"
    break;

  case 168: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1529 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("type_name");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3688 "parser.tab.c"
    break;

  case 169: /* abstract_declarator: pointer  */
#line 1539 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3698 "parser.tab.c"
    break;

  case 170: /* abstract_declarator: direct_abstract_declarator  */
#line 1545 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3708 "parser.tab.c"
    break;

  case 171: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1551 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3719 "parser.tab.c"
    break;

  case 172: /* direct_abstract_declarator: LPAREN abstract_declarator rparen  */
#line 1561 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3731 "parser.tab.c"
    break;

  case 173: /* direct_abstract_declarator: LSQUARE rsquare  */
#line 1569 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3742 "parser.tab.c"
    break;

  case 174: /* direct_abstract_declarator: LSQUARE constant_expression rsquare  */
#line 1576 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3754 "parser.tab.c"
    break;

  case 175: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE rsquare  */
#line 1584 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode);  
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3765 "parser.tab.c"
    break;

  case 176: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression rsquare  */
#line 1591 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode);  
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3777 "parser.tab.c"
    break;

  case 177: /* direct_abstract_declarator: LPAREN rparen  */
#line 1599 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3788 "parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: LPAREN parameter_type_list rparen  */
#line 1606 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("direct_abstract_declarator");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3800 "parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: direct_abstract_declarator LPAREN rparen  */
#line 1614 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3811 "parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_type_list rparen  */
#line 1621 "parser.y"
    {
        LINE
        (yyval.astNode) = (yyvsp[-3].astNode); 
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3823 "parser.tab.c"
    break;

  case 181: /* initializer: assignment_expression  */
#line 1632 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3833 "parser.tab.c"
    break;

  case 182: /* initializer: LCURLY initializer_list rcurly  */
#line 1638 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3845 "parser.tab.c"
    break;

  case 183: /* initializer: LCURLY initializer_list COMMA rcurly  */
#line 1646 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("initializer");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3858 "parser.tab.c"
    break;

  case 184: /* initializer_list: initializer  */
#line 1658 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("initializer_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3868 "parser.tab.c"
    break;

  case 185: /* initializer_list: initializer_list COMMA initializer  */
#line 1664 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-2].astNode); 
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3879 "parser.tab.c"
    break;

  case 186: /* statement: labeled_statement  */
#line 1674 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3889 "parser.tab.c"
    break;

  case 187: /* statement: compound_statement  */
#line 1680 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3899 "parser.tab.c"
    break;

  case 188: /* statement: expression_statement  */
#line 1686 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3909 "parser.tab.c"
    break;

  case 189: /* statement: selection_statement  */
#line 1692 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3919 "parser.tab.c"
    break;

  case 190: /* statement: iteration_statement  */
#line 1698 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3929 "parser.tab.c"
    break;

  case 191: /* statement: jump_statement  */
#line 1704 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3939 "parser.tab.c"
    break;

  case 192: /* statement: declaration  */
#line 1710 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 3949 "parser.tab.c"
    break;

  case 193: /* labeled_statement: identifier COLON statement  */
#line 1719 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3961 "parser.tab.c"
    break;

  case 194: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1727 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3974 "parser.tab.c"
    break;

  case 195: /* labeled_statement: DEFAULT COLON statement  */
#line 1736 "parser.y"
    {
        LINE
        (yyval.astNode) = new ASTNode("labeled_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3986 "parser.tab.c"
    break;

  case 196: /* compound_statement: LCURLY rcurly  */
#line 1747 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 3997 "parser.tab.c"
    break;

  case 197: /* compound_statement: LCURLY statement_list rcurly  */
#line 1754 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4009 "parser.tab.c"
    break;

  case 198: /* compound_statement: LCURLY declaration_list rcurly  */
#line 1762 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4021 "parser.tab.c"
    break;

  case 199: /* compound_statement: LCURLY declaration_list statement_list rcurly  */
#line 1770 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("compound_statement");
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4034 "parser.tab.c"
    break;

  case 200: /* declaration_list: declaration  */
#line 1782 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("declaration_list");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4044 "parser.tab.c"
    break;

  case 201: /* declaration_list: declaration_list declaration  */
#line 1788 "parser.y"
    { 
        LINE 
        (yyval.astNode) = (yyvsp[-1].astNode); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4054 "parser.tab.c"
    break;

  case 202: /* statement_list: statement  */
#line 1798 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement_list"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4064 "parser.tab.c"
    break;

  case 203: /* statement_list: statement_list statement  */
#line 1804 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("statement_list");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4075 "parser.tab.c"
    break;

  case 204: /* expression_statement: semi_colon  */
#line 1814 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement"); 
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4085 "parser.tab.c"
    break;

  case 205: /* expression_statement: expression semi_colon  */
#line 1820 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("expression_statement");
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4096 "parser.tab.c"
    break;

  case 206: /* selection_statement: IF LPAREN expression rparen statement  */
#line 1830 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4110 "parser.tab.c"
    break;

  case 207: /* selection_statement: IF LPAREN expression rparen statement ELSE statement  */
#line 1840 "parser.y"
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
#line 4126 "parser.tab.c"
    break;

  case 208: /* selection_statement: SWITCH LPAREN expression rparen statement  */
#line 1852 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("selection_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4140 "parser.tab.c"
    break;

  case 209: /* iteration_statement: WHILE LPAREN expression rparen statement  */
#line 1865 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4154 "parser.tab.c"
    break;

  case 210: /* iteration_statement: UNTIL LPAREN expression rparen statement  */
#line 1875 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("iteration_statement");
        (yyval.astNode)->addChild((yyvsp[-4].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-3].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4168 "parser.tab.c"
    break;

  case 211: /* iteration_statement: DO statement WHILE LPAREN expression rparen semi_colon  */
#line 1885 "parser.y"
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
#line 4184 "parser.tab.c"
    break;

  case 212: /* iteration_statement: FOR LPAREN expression_statement expression_statement rparen statement  */
#line 1897 "parser.y"
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
#line 4199 "parser.tab.c"
    break;

  case 213: /* iteration_statement: FOR LPAREN expression_statement expression_statement expression rparen statement  */
#line 1908 "parser.y"
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
#line 4215 "parser.tab.c"
    break;

  case 214: /* iteration_statement: FOR LPAREN declaration expression_statement expression rparen statement  */
#line 1920 "parser.y"
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
#line 4231 "parser.tab.c"
    break;

  case 215: /* jump_statement: GOTO identifier semi_colon  */
#line 1935 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4243 "parser.tab.c"
    break;

  case 216: /* jump_statement: CONTINUE semi_colon  */
#line 1943 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4254 "parser.tab.c"
    break;

  case 217: /* jump_statement: BREAK semi_colon  */
#line 1950 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4265 "parser.tab.c"
    break;

  case 218: /* jump_statement: RETURN semi_colon  */
#line 1957 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-1].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4276 "parser.tab.c"
    break;

  case 219: /* jump_statement: RETURN expression semi_colon  */
#line 1964 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("jump_statement");
        (yyval.astNode)->addChild((yyvsp[-2].tokenAtr));
        (yyval.astNode)->addChild((yyvsp[-1].astNode));
        (yyval.astNode)->addChild((yyvsp[0].astNode));
    }
#line 4288 "parser.tab.c"
    break;

  case 220: /* translation_unit: external_declaration  */
#line 1977 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("translation_unit");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        root = (yyval.astNode);
    }
#line 4299 "parser.tab.c"
    break;

  case 221: /* translation_unit: translation_unit external_declaration  */
#line 1984 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("translation_unit");
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4310 "parser.tab.c"
    break;

  case 222: /* external_declaration: function_definition  */
#line 1994 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4320 "parser.tab.c"
    break;

  case 223: /* external_declaration: declaration  */
#line 2000 "parser.y"
    { 
        LINE 
        (yyval.astNode) = new ASTNode("external_declaration");
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4330 "parser.tab.c"
    break;

  case 224: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 2029 "parser.y"
    { 
        LINE  
        (yyval.astNode) = new ASTNode("Function Definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4342 "parser.tab.c"
    break;

  case 225: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 2038 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("function_definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode));
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
        // Function_Def_Handler($2);
    }
#line 4355 "parser.tab.c"
    break;

  case 226: /* function_definition: declarator declaration_list compound_statement  */
#line 2047 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Definition"); 
        (yyval.astNode)->addChild((yyvsp[-2].astNode)); 
        (yyval.astNode)->addChildren((yyvsp[-1].astNode)->children); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4367 "parser.tab.c"
    break;

  case 227: /* function_definition: declarator compound_statement  */
#line 2055 "parser.y"
    { 
        LINE
        (yyval.astNode) = new ASTNode("Function Definition"); 
        (yyval.astNode)->addChild((yyvsp[-1].astNode)); 
        (yyval.astNode)->addChild((yyvsp[0].astNode)); 
    }
#line 4378 "parser.tab.c"
    break;


#line 4382 "parser.tab.c"

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

#line 2063 "parser.y"



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
    whereWasILast = "noOfPointers";
    if(node->children.size()==0) return 1;

    return 1+noOfPointers(node->children[0]);
}

void E_S_U_Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList,std::string s1,std::string s2){
    whereWasILast = "E_S_U_Declaration_Handler";
    for(auto item : initDeclaratorList->children){
        if(item->type == "Initializer"){
            PARSER_TABLE.push_back({item->children[0]->position,{item->children[0]->value, s2}});
        } else {
            PARSER_TABLE.push_back({item->position,{item->value, s2}});
        }
    }
}

void Declaration_Handler(ASTNode* declarationSpecifiers, ASTNode* initDeclaratorList){
    whereWasILast = "Declaration_Handler";
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
    return;
    whereWasILast = "Function_Def_Handler";
    LINE1
    std::string functionName=declarator->value;
    LINE1
    PARSER_TABLE.push_back({declarator->position, {functionName, "function declaration"}});
    LINE1
    declarator = declarator->children[0];
    LINE1
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
    whereWasILast = "Struct_Union_Declaration_Handler";
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
    whereWasILast = "Enum_Declaration_Handler";

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
