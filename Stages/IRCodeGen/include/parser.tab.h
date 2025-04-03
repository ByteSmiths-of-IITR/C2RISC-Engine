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

#ifndef YY_YY_INCLUDE_PARSER_TAB_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_TAB_H_INCLUDED
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
    IDENTIFIER = 258,              /* IDENTIFIER  */
    CONSTANT = 259,                /* CONSTANT  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    SIZEOF = 261,                  /* SIZEOF  */
    PTR_OP = 262,                  /* PTR_OP  */
    INC_OP = 263,                  /* INC_OP  */
    DEC_OP = 264,                  /* DEC_OP  */
    LEFT_OP = 265,                 /* LEFT_OP  */
    RIGHT_OP = 266,                /* RIGHT_OP  */
    LE_OP = 267,                   /* LE_OP  */
    GE_OP = 268,                   /* GE_OP  */
    EQ_OP = 269,                   /* EQ_OP  */
    NE_OP = 270,                   /* NE_OP  */
    AND_OP = 271,                  /* AND_OP  */
    OR_OP = 272,                   /* OR_OP  */
    MUL_ASSIGN = 273,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 274,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 275,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 276,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 277,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 278,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 279,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 280,              /* AND_ASSIGN  */
    XOR_ASSIGN = 281,              /* XOR_ASSIGN  */
    OR_ASSIGN = 282,               /* OR_ASSIGN  */
    TYPE_NAME = 283,               /* TYPE_NAME  */
    LPAREN = 284,                  /* LPAREN  */
    RPAREN = 285,                  /* RPAREN  */
    LCURLY = 286,                  /* LCURLY  */
    RCURLY = 287,                  /* RCURLY  */
    LSQUARE = 288,                 /* LSQUARE  */
    RSQUARE = 289,                 /* RSQUARE  */
    DOT = 290,                     /* DOT  */
    COMMA = 291,                   /* COMMA  */
    BIT_AND = 292,                 /* BIT_AND  */
    STAR = 293,                    /* STAR  */
    PLUS = 294,                    /* PLUS  */
    MINUS = 295,                   /* MINUS  */
    BIT_NOT = 296,                 /* BIT_NOT  */
    NOT_OP = 297,                  /* NOT_OP  */
    DIVIDE = 298,                  /* DIVIDE  */
    MOD = 299,                     /* MOD  */
    LESSER_OP = 300,               /* LESSER_OP  */
    GREATER_OP = 301,              /* GREATER_OP  */
    XOR = 302,                     /* XOR  */
    BIT_OR = 303,                  /* BIT_OR  */
    QUESTION = 304,                /* QUESTION  */
    COLON = 305,                   /* COLON  */
    SEMI_COLON = 306,              /* SEMI_COLON  */
    ASSIGN = 307,                  /* ASSIGN  */
    TYPEDEF = 308,                 /* TYPEDEF  */
    EXTERN = 309,                  /* EXTERN  */
    STATIC = 310,                  /* STATIC  */
    AUTO = 311,                    /* AUTO  */
    REGISTER = 312,                /* REGISTER  */
    CHAR = 313,                    /* CHAR  */
    SHORT = 314,                   /* SHORT  */
    INT = 315,                     /* INT  */
    LONG = 316,                    /* LONG  */
    SIGNED = 317,                  /* SIGNED  */
    UNSIGNED = 318,                /* UNSIGNED  */
    FLOAT = 319,                   /* FLOAT  */
    DOUBLE = 320,                  /* DOUBLE  */
    CONST = 321,                   /* CONST  */
    VOLATILE = 322,                /* VOLATILE  */
    VOID = 323,                    /* VOID  */
    VA_LIST = 324,                 /* VA_LIST  */
    STRUCT = 325,                  /* STRUCT  */
    UNION = 326,                   /* UNION  */
    ENUM = 327,                    /* ENUM  */
    ELLIPSIS = 328,                /* ELLIPSIS  */
    CASE = 329,                    /* CASE  */
    DEFAULT = 330,                 /* DEFAULT  */
    IF = 331,                      /* IF  */
    ELSE = 332,                    /* ELSE  */
    SWITCH = 333,                  /* SWITCH  */
    WHILE = 334,                   /* WHILE  */
    DO = 335,                      /* DO  */
    FOR = 336,                     /* FOR  */
    GOTO = 337,                    /* GOTO  */
    CONTINUE = 338,                /* CONTINUE  */
    BREAK = 339,                   /* BREAK  */
    RETURN = 340,                  /* RETURN  */
    UNTIL = 341,                   /* UNTIL  */
    INVALID_TOKEN = 342,           /* INVALID_TOKEN  */
    UNKNOWN_TOKEN = 343            /* UNKNOWN_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 201 "grammar/parser.y"

    struct TokenAttribute* tokenAtr;
    struct ASTNode* astNode;

#line 157 "include/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_TAB_H_INCLUDED  */
