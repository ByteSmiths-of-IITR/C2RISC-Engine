#include "header.h"

int main(){
    TypeExpression typeExpr;
    BaseInfo *baseInfo = new BaseInfo();
    baseInfo->baseType = TYPE_INT;
    baseInfo->typeQualifiers.push_back(TypeQualifier::CONST);
    typeExpr.levelStack.push(baseInfo);

    std::string result = toString(typeExpr);
    std::cout << "Type Expression: " << result << std::endl;
    // Output: Type Expression: const int
}