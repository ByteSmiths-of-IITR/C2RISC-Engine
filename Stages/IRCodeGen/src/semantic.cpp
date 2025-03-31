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

std::string isPrimitive(const TypeExpression &typeExpr){
    // Check if base type is primitive

    // HAVE NOT CHECKED FOR 

    Type topType = whatIsType(typeExpr);
    if(topType == Type::VARIABLE) {
        BaseInfo *baseInfo = dynamic_cast<BaseInfo *>(typeExpr.levelStack.top());
        std::string baseType = baseInfo->baseType;
        if(baseType == TYPE_INT || baseType == TYPE_CHAR || baseType == TYPE_SHORT || baseType == TYPE_LONG || baseType == TYPE_LONG_LONG ||
            baseType == TYPE_FLOAT || baseType == TYPE_DOUBLE || baseType == TYPE_LONG_DOUBLE) {
            return baseType;
        }
    }
    else if(topType == Type::ENUM_CONSTANT){
        return TYPE_INT; // Enum constant is treated as int
    }
    
    return "NOT_PRIMITIVE";
}

//=====================[ TypeCasting Utilites 🆎 ]========================================================================================

std::string maxWidth(std::string primTyp1,std::string primType2){
    // [📍 ToDo]
    std::map<std::string,int> widthMap;
    widthMap[TYPE_CHAR] = BYTE_SIZE;
    widthMap[TYPE_SHORT] = BYTE_SIZEx2;
    widthMap[TYPE_INT] = WORD_SIZE;
    widthMap[TYPE_LONG] = WORD_SIZEx2;
    widthMap[TYPE_LONG_LONG] = WORD_SIZEx4;
    widthMap[TYPE_FLOAT] = WORD_SIZE;
    widthMap[TYPE_DOUBLE] = WORD_SIZEx2;
    widthMap[TYPE_LONG_DOUBLE] = WORD_SIZEx4;

    // Check if arguments are primitive types
    if(widthMap.find(primTyp1) == widthMap.end() || widthMap.find(primType2) == widthMap.end()){
        // SEMANTIC ERROR 🚨 : Not a primitive type
        return "NOT_PRIMITIVE";
    }

    int width1 = widthMap[primTyp1];
    int width2 = widthMap[primType2];

    int finalWidth = std::max(width1, width2);
    finalWidth = (finalWidth < WORD_SIZE) ? WORD_SIZE : finalWidth;

    int format1 = (primTyp1 == TYPE_FLOAT || primTyp1 == TYPE_DOUBLE || primTyp1 == TYPE_LONG_DOUBLE) ? 1 : 0;
    int format2 = (primType2 == TYPE_FLOAT || primType2 == TYPE_DOUBLE || primType2 == TYPE_LONG_DOUBLE) ? 1 : 0;
    int finalFormat = (format1 || format2) ? 1 : 0;

    if(finalFormat == 1){
        // Floating Point Casting will happen
        if(format1 != 1){
            if(finalWidth == WORD_SIZE){
                return TYPE_FLOAT;
            }
            else if(finalWidth == WORD_SIZEx2){
                return TYPE_DOUBLE;
            }
            else if(finalWidth == WORD_SIZEx4){
                return TYPE_LONG_DOUBLE;
            }
        }
        if(format2 != 1){
            // Cast to finalWidth
            if(finalWidth == WORD_SIZE){
                return TYPE_FLOAT;
            }
            else if(finalWidth == WORD_SIZEx2){
                return TYPE_DOUBLE;
            }
            else if(finalWidth == WORD_SIZEx4){
                return TYPE_LONG_DOUBLE;
            }
        }
    }
    else{
        // Only Width Casting will happen
        if(finalWidth == WORD_SIZE){
            return TYPE_INT;
        }
        else if(finalWidth == WORD_SIZEx2){
            return TYPE_LONG;
        }
        else if(finalWidth == WORD_SIZEx4){
            return TYPE_LONG_LONG;
        }
    }

    return "SHOULD_NOT_HAPPEN";
}

// int widen(std::string address, std::string type, std::string result)
// This will be inline coded in logic as it involves IRCode Gen 


