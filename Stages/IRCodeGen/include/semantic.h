#ifndef SEMANTIC_H
#define SEMANTIC_H

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

DType maxType(DType t1, DType t2);

DType widenType(DType s, DType t, std::string varName);







#endif //!SEMANTIC_H