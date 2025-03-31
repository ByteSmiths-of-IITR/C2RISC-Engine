#include "header.h"

int main(){
    TypeExpression typeExpr;
    BaseInfo *baseInfo = new BaseInfo();
    baseInfo->baseType = TYPE_INT;
    baseInfo->typeQualifiers.push_back(TypeQualifier::CONST);
    typeExpr.levelStack.push(baseInfo);
    TypeExpression tempExpr = typeExpr;

    PointerInfo *ptrInfo = new PointerInfo();
    ptrInfo->typeQualifiers.push_back(TypeQualifier::VOLATILE);
    typeExpr.levelStack.push(ptrInfo);

    ParameterInfo *paramInfo = new ParameterInfo();
    std::vector<TypeExpression> paramVector;
    paramVector.push_back(tempExpr);
    paramInfo->paramsType = paramVector;
    typeExpr.levelStack.push(paramInfo);

    ArrayInfo *arrInfo = new ArrayInfo();
    arrInfo->dimSize = 10;
    typeExpr.levelStack.push(arrInfo);
    // typeExpr.levelStack.push(new ParenthesisInfo());

    ArrayInfo *arrInfo2 = new ArrayInfo();
    arrInfo2->dimSize = 20;
    typeExpr.levelStack.push(arrInfo2);
    // typeExpr.levelStack.push(new ParenthesisInfo());

    typeExpr.levelStack.push(paramInfo);

    std::string result = toString(typeExpr);
    std::cout << "Type Expression: " << result << std::endl;
    // Output: Type Expression: const int
}