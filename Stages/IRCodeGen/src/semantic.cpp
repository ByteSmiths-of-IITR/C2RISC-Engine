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
        if(topType == Type::ENUM){
            return true; // Enum Objects are also INT_TYPE
        }
    }
    return false;
}

bool isValidTypeExpression(const TypeExpression &typeExpr) {
    // // Check if the type expression is valid
    // Type topType = whatIsType(typeExpr);
    // if(topType == Type::VARIABLE || topType == Type::ENUM_CONSTANT || topType == Type::ENUM) {
    //     return true; // Valid type expression
    // }
    return true;
}

bool isConstant(const TypeExpression &typeExpr) {
    // Check if the type expression is a constant type
    Type topType = whatIsType(typeExpr);
    if(topType == Type::ENUM_CONSTANT){
        return true; // Enum constant is treated as constant
    }
    else if(topType == Type::VARIABLE) {
        BaseInfo *baseInfo = dynamic_cast<BaseInfo *>(typeExpr.levelStack.top());
        // Check if "const" qualifier is present
        for(auto qualifier : baseInfo->typeQualifiers) {
            if(qualifier == TypeQualifier::CONST) {
                return true;
            }
        }
    }
}

bool isNumeric(const TypeExpression &typeExpr){
    // Must be base 
    Type topType = whatIsType(typeExpr);
    if(topType == Type::VARIABLE) {
        BaseInfo *baseInfo = dynamic_cast<BaseInfo *>(typeExpr.levelStack.top());
        std::string baseType = baseInfo->baseType;
        if(baseType == TYPE_INT || baseType == TYPE_CHAR || baseType == TYPE_SHORT || baseType == TYPE_LONG || baseType == TYPE_LONG_LONG ||
            baseType == TYPE_FLOAT || baseType == TYPE_DOUBLE || baseType == TYPE_LONG_DOUBLE) {
            return true;
        }
    }
    else if(topType == Type::ENUM_CONSTANT){
        return true; // Enum constant is treated as numeric
    }
    else if(topType == Type::ENUM){
        return true; // Enum is treated as numeric
    }
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

        // Can a combination of signed/unsigned and primitive types be a primitive type?
        std::string firstPart = baseType.substr(0, baseType.find(" "));
        std::string restPart = baseType.substr(baseType.find(" ") + 1);
        if(firstPart == TYPE_UNSIGNED){
            if(restPart == TYPE_INT || restPart == TYPE_CHAR || restPart == TYPE_SHORT || restPart == TYPE_LONG || restPart == TYPE_LONG_LONG){
                return baseType;
            }
        }
    }
    else if(topType == Type::ENUM_CONSTANT){
        return TYPE_INT; // Enum constant is treated as int
    }
    else if(topType == Type::ENUM){
        return TYPE_INT; // Enum is treated as int
    }

    return "NOT_PRIMITIVE";
}

bool isA_InbuiltType(std::string baseType){
    // Check if base type is primitive
    if(baseType == TYPE_INT || baseType == TYPE_CHAR || baseType == TYPE_SHORT || baseType == TYPE_LONG || baseType == TYPE_LONG_LONG ||
        baseType == TYPE_FLOAT || baseType == TYPE_DOUBLE || baseType == TYPE_LONG_DOUBLE || baseType == TYPE_VOID || baseType == TYPE_UNSIGNED ||
        baseType == TYPE_SIGNED){
        return true;
    }

    // get first part before space
    std::string firstPart = baseType.substr(0, baseType.find(" "));
    if(firstPart == TYPE_STRUCT || firstPart == TYPE_UNION || firstPart == TYPE_ENUM){
        return true;
    }

    return false;
}

bool isA_IntegralType(std::string baseType){
    // Check if base type is integral
    if(baseType == TYPE_INT || baseType == TYPE_CHAR || baseType == TYPE_SHORT || baseType == TYPE_LONG || baseType == TYPE_LONG_LONG ||
        baseType == ENUM_CONSTANT){
        return true;
    }
    return false;
}

bool isA_FloatingType(std::string baseType){
    // Check if base type is floating
    if(baseType == TYPE_FLOAT || baseType == TYPE_DOUBLE || baseType == TYPE_LONG_DOUBLE){
        return true;
    }
    return false;
}

std::string combineType(std::vector<std::string> typeSpecifierVector){
    int size = typeSpecifierVector.size();

    //print checking
    for(int i = 0;i<size;i++){
        std::cerr << typeSpecifierVector[i] << " ";
    }
    std::cerr << std::endl;

    if(size == 0){
        return INVALID_COMBINATION;
    }
    std::string finalBase;

    if(size == 1){
        if(typeSpecifierVector[0] == TYPE_SIGNED){
            return TYPE_INT;
        }
        if(typeSpecifierVector[0] == TYPE_UNSIGNED){
            return "unsigned int";
        }
        return typeSpecifierVector[0];
    }

    if(size == 2){
        // INT + LONG | LONG + LONG | LONG + DOUBLE | SHORT + INT
        // SIGNED + INTEGRALS | UNSIGNED + INTEGRALS
        // Otherwise INVALID | order doesn't matter
        std::string type1 = typeSpecifierVector[0];
        std::string type2 = typeSpecifierVector[1];
        if(type1 == TYPE_INT && type2 == TYPE_LONG){
            return TYPE_LONG;
        }
        else if(type1 == TYPE_LONG && type2 == TYPE_INT){
            return TYPE_LONG;
        }
        else if(type1 == TYPE_LONG && type2 == TYPE_LONG){
            return TYPE_LONG_LONG;
        }
        else if(type1 == TYPE_LONG && type2 == TYPE_DOUBLE){
            return TYPE_LONG_DOUBLE;
        }
        else if(type1 == TYPE_DOUBLE && type2 == TYPE_LONG){
            return TYPE_LONG_DOUBLE;
        }
        else if (type1 == TYPE_SHORT && type2 == TYPE_INT)
        {
            return TYPE_SHORT;
        }
        else if (type1 == TYPE_INT && type2 == TYPE_SHORT)
        {
            return TYPE_SHORT;
        }
        else if(type1 == TYPE_SIGNED && isA_IntegralType(type2)){
            return type2;
        }
        else if(type2 == TYPE_SIGNED && isA_IntegralType(type1)){
            return type1;
        }
        else if(type1 == TYPE_UNSIGNED && isA_IntegralType(type2)){
            return "unsigned " + type2;
        }
        else if(type2 == TYPE_UNSIGNED && isA_IntegralType(type1)){
            return "unsigned " + type1;
        }
        
        
    }
    
    if(size == 3){
        // INT + LONG + LONG 
        // SIGNED/UNSIGNED + (LONG + LONG)/(LONG + INT)/(SHORT + INT)
        // Otherwise INVALID | order doesn't matter

        // Let's first sort the types
        std::sort(typeSpecifierVector.begin(), typeSpecifierVector.end());
        std::string type1 = typeSpecifierVector[0];
        std::string type2 = typeSpecifierVector[1];
        std::string type3 = typeSpecifierVector[2]; // signed/unsigned will be at the end

        //check
        for (int i = 1;i<4;i++){
            std::cerr << typeSpecifierVector[i] << " ";
        }

        if (type1 == TYPE_INT && type2 == TYPE_LONG && type3 == TYPE_LONG)
        {
            return TYPE_LONG_LONG; // since sorted
        }
        else if(type1 == TYPE_INT && type2 == TYPE_LONG){
            if(type3 == TYPE_UNSIGNED){
                return "unsigned long";
            }
            else if(type3 == TYPE_SIGNED){
                return TYPE_LONG;
            }
        }else if(type1 == TYPE_LONG && type2 == TYPE_LONG){
            if(type3 == TYPE_UNSIGNED){
                return "unsigned long long";
            }
            else if(type3 == TYPE_SIGNED){
                return TYPE_LONG_LONG;
            }
        }
        // type1 == INT
        else if(type1 == TYPE_INT && type2 == TYPE_SHORT){
            if(type3 == TYPE_UNSIGNED){
                return "unsigned short";
            }
            else if(type3 == TYPE_SIGNED){
                return TYPE_SHORT;
            }
        }
        else if(type1 == TYPE_INT && type3 == TYPE_SHORT){
            if(type2 == TYPE_UNSIGNED){
                return "unsigned short";
            }
            else if(type2 == TYPE_SIGNED){
                return TYPE_SHORT;
            }
        }
        
    }
    
    if(size == 4){
        // INT + LONG + LONG + SIGNED/UNSIGNED
        // Otherwise INVALID | order doesn't matter
        // Let's first sort the types
        std::sort(typeSpecifierVector.begin(), typeSpecifierVector.end());
        std::string type1 = typeSpecifierVector[0];
        std::string type2 = typeSpecifierVector[1];
        std::string type3 = typeSpecifierVector[2];
        std::string type4 = typeSpecifierVector[3]; // signed/unsigned will be at the end
        //check
        for (int i = 1;i<5;i++){
            std::cerr << typeSpecifierVector[i] << " ";
        }
        if (type1 == TYPE_INT && type2 == TYPE_LONG && type3 == TYPE_LONG)
        {
            if(type4 == TYPE_SIGNED){
                return TYPE_LONG_LONG;
            }
            else if(type4 == TYPE_UNSIGNED){
                return "unsigned long long";
            }
        }
    }
    return INVALID_COMBINATION;
}

bool isFloatingPoint(const TypeExpression &typeExpr) {
    // Check if the type expression is a floating point type
    Type topType = whatIsType(typeExpr);
    if(topType == Type::VARIABLE) {
        BaseInfo *baseInfo = dynamic_cast<BaseInfo *>(typeExpr.levelStack.top());
        std::string baseType = baseInfo->baseType;
        if(baseType == TYPE_FLOAT || baseType == TYPE_DOUBLE || baseType == TYPE_LONG_DOUBLE) {
            return true;
        }
    }
    return false;
}

std::string INVALID_COMBINATION = "#INVALID_COMBINATION#"; // This will be used for invalid combination of types

//=====================[ TypeCasting Utilites 🆎 ]========================================================================================

int width(std::string primType){
    std::map<std::string, int> widthMap;
    widthMap[TYPE_CHAR] = BYTE_SIZE;
    widthMap[TYPE_SHORT] = BYTE_SIZEx2;
    widthMap[TYPE_INT] = WORD_SIZE;
    widthMap[TYPE_LONG] = WORD_SIZEx2;
    widthMap[TYPE_LONG_LONG] = WORD_SIZEx4;
    widthMap[TYPE_FLOAT] = WORD_SIZE;
    widthMap[TYPE_DOUBLE] = WORD_SIZEx2;
    widthMap[TYPE_LONG_DOUBLE] = WORD_SIZEx4;

    // Check if the primitive type is present in the map
    if(widthMap.find(primType) == widthMap.end()){
        // SEMANTIC ERROR 🚨 : Not a primitive type
        return -1;
    }
    // Return the width of the primitive type
    return widthMap[primType];
}

std::string maxWidth(std::string primTyp1,std::string primType2){
    // [📍 ToDo]
    
    int width1 = width(primTyp1);
    int width2 = width(primType2);
    
    if(width1 == -1 || width2 == -1){
        // SEMANTIC ERROR 🚨 : Not a primitive type
        return "NOT_PRIMITIVE";
    }

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


