#include "header.h"

//===================[ TypeChecking Utilites 🅰️ ] ============================================================================================

bool isIntegral(const TypeExpression &typeExpr) {
    // Check if the type expression is an integral type
    Type topType = whatIsType(typeExpr);
    if(topType == Type::ENUM_CONSTANT || topType == Type::VARIABLE) {
        // Check if the base type is integral
        BaseInfo *baseInfo = dynamic_cast<BaseInfo *>(typeExpr.levelStack.top());
        std::string baseType = baseInfo->baseType;
        if(baseType == INT || baseType == CHAR || baseType == SHORT || baseType == LONG || baseType == LONG_LONG) {
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