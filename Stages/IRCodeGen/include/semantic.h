#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "utility.h"
#include "sym.h"
#include "tac.h"

// Semantic Analysis Phase Requirement

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ TypeExpression Class ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* 1. A TypeExpression Class - which can handle things like 'int (*)(int, int)'

Change Variable Properties to TypeExpression from DType of returnType
👍 Written in sym.h
*/

//~~~~~~~~~~~~~~~~~~~~~~~[ 🅰️TypeCheck Utilities ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool isIntegral(const TypeExpression &typeExpr); 


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ TypeCasting Utilites ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TypeCasting Utilities - maxType(t1,t2) | widenType(s,t,var)

// MaxType will only work for primitive types

*/


BaseInfo* maxType(BaseInfo *t1, BaseInfo *t2);

std::string widenType(BaseInfo *s, BaseInfo *t, std::string varName);


//++++++++++++++++++++++[ Expressions OnData ]++++++++++++++++++++++++++++++++
enum class VALUE_TYPE
{
    RVALUE,    // Read Only Value
    M_LVALUE,  // Modifiable LValue
    NM_LVALUE, // Non Modifiable LValue
    UNKNOWN
};

enum class SPACE
{
    ADDRESS_SPACE, // Address Space
    VALUE_SPACE,   // Value Space
    UNKNOWN
};

enum class Expr_Type
{
    VARIABLE, // base is primitive
    ARRAY,
    POINTER,
    ENUM_CONSTANT, // this is the constant inside of enum definition
    FUNCTION,
    STURCT_UNION, // struct or union
    ENUM,         // this is object of enum
    EMPTY,
    UNKNOWN
};

#endif //!SEMANTIC_H