#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "utility.h"
#include "sym.h"
#include "ast.h"

// Semantic Analysis Phase Requirement

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ TypeExpression Class ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* 1. A TypeExpression Class - which can handle things like 'int (*)(int, int)'

Change Variable Properties to TypeExpression from DType of returnType
👍 Written in sym.h
*/



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ TypeCasting Utilites ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TypeCasting Utilities - maxType(t1,t2) | widenType(s,t,var)

// MaxType will only work for primitive types

*/


BaseInfo* maxType(BaseInfo *t1, BaseInfo *t2);

std::string widenType(BaseInfo *s, BaseInfo *t, std::string varName);


//++++++++++++++++++++++[ Expressions OnData ]++++++++++++++++++++++++++++++++
enum class VALUE_TYPE{
    RVALUE, // Read Only Value
    M_LVALUE, // Modifiable LValue
    NM_LVALUE, // Non Modifiable LValue
    UNKNOWN
}

enum class VALUE_SPACE{
    ADDRESS,
    VALUE,
    UNKNOWN
}

#endif //!SEMANTIC_H