#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "utility.h"
#include "sym.h"
#include "tac.h"

// Forward Declaration of Classes Needed from sym.h
    class UserDType;
    class VarSymbols;
    class GenericSymbol;
    enum class TypeQualifier;
    enum class RecordType;
    enum class StorageClass;
    class LevelInfo;
    class ParenthesisInfo;
    class ArrayInfo;
    class PointerInfo;
    class BaseInfo;
    class ParameterInfo;
    class TypeExpression;
    class GenericSymbol;
    class SymbolNode;
    class SymbolTable;
    class VarSymbols;
    class UserDType;
    class Variable;
    class EnumConstant;
    class Function;

// Forward declaration of Classes Needed from tac.h
    class TAC_Quadruple;
    class TAC;

// Forward declaration of Classes in this file
    class BaseData;
    class ExpressionData;
    class DeclarationData;






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


// BaseInfo* maxType(BaseInfo *t1, BaseInfo *t2);

// std::string widenType(BaseInfo *s, BaseInfo *t, std::string varName);


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

//---------------------[ DataStructure for Non-Terminal ]-------------------------------------------------

class BaseData{
    public:
        BaseData(){
            MEM("BaseData Constructor");
        }
        virtual ~BaseData(){
            MEM("BaseData Destructor");
        }
};


class ExpressionData : public BaseData{
    public:
        // syn_Attributes to be passed up ⬆️
        std::string varName;
        TypeExpression type;
        VALUE_TYPE valueType;
        SPACE valueSpace;

        // inh_Attributes to be passed down ⬇️
        std::string whereToSendString; //❓ Check if needed
};

class DeclarationData : public BaseData{
    public:
        // syn_Attributes to be passed up ⬆️
        TypeExpression type;
        std::string varName;

        // inh_Attributes to be passed down ⬇️
        TypeExpression inh_type;
        StorageClass inh_storageClass;
};

#endif //!SEMANTIC_H