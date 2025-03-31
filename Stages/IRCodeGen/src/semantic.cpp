#include "header.h"

//===================[ TypeChecking Utilites 🅰️ ] ============================================================================================

bool isIntegral(const TypeExpression &typeExpr) {
    // Check if the type expression is an integral type
    Type topType = whatIsType(typeExpr);
    if(topType == Type::ENUM_CONSTANT || topType == Type::VARIABLE) {
        // Check if the base type is integral
        BaseInfo *baseInfo = dynamic_cast<BaseInfo *>(typeExpr.levelStack.top());
        std::string baseType = baseInfo->baseType;
        if(baseType == TYPE_INT || baseType == TYPE_CHAR || baseType == TYPE_SHORT || baseType == TYPE_LONG || baseType == TYPE_LONG_LONG) {
            return true;
        }
        if(baseType == ENUM_CONSTANT){
            return true;
        }
    }
    return false;
}

bool isConstant(){
    // [📍 ToDo]
    return true;
}

//=====================[ TypeCasting Utilites 🆎 ]=========================================================================================