#include "header.h"

//=====================[ Width Utilities ]=========================================================================================

int width(const UserDType &dtype)
{
    if (dtype.totalSize == -1)
    {
        // has not been calculated yet
        int size = 0;
        for (auto &pair : dtype.members)
        {
            std::string memberName = pair.first;
            TypeExpression memberType = pair.second;

            int memberSize = width(memberType);
            if (memberSize == -1)
            {
                CERR << "Error: Member \"" + memberName + "\" not found\n";
                return -1;
            }
            size += memberSize;
        }
    }
}

int width(const BaseInfo &info)
{
    TypeExpression typeExpr;
    typeExpr.levelStack.push((LevelInfo *)&info);
    Type topType = whatIsType(typeExpr);
    if (topType == Type::VARIABLE)
    {
        std::string baseType = info.baseType;
        int w = width(baseType);
        if (w == -1)
        {
            CERR << "Error: Base Type \"" + baseType + "\" not found\n";
            return -1;
        }
        return w;
    }
    else if (topType == Type::ENUM)
    {
        return WORD_SIZE; // Size of enum
    }
    else if (topType == Type::STRUCT_UNION)
    {
        // Need to check in symbol table & find
        std::string baseType = info.baseType;

        std::string recordType = baseType.substr(0, baseType.find(" "));
        std::string recordName = baseType.substr(baseType.find(" ") + 1, baseType.length());
        std::string lastPart = baseType.substr(baseType.find_last_of(" ") + 1, baseType.length());
        std::string scopeNoStr = lastPart.substr(1, lastPart.length() - 1);
        int scopeNo = std::stoi(scopeNoStr);

        GenericSymbol *recordSymbol = nullptr;
        int recordCheck = SYM_TABLE.lookupRecord(recordName, recordSymbol, scopeNo);
        if (recordCheck == LOOKUP_FAILURE)
        {
            std::cerr << "Error: Record \"" + recordName + "\" not found in symbol table\n";
            return -1;
        }
        else
        {
            // Find the width of the record
            UserDType *record = dynamic_cast<UserDType *>(recordSymbol);
            return width(*record);
        }
    }
    else if (topType == Type::ENUM_CONSTANT)
    {
        return WORD_SIZE; // Size of enum constant
    }

    return -10;
}

int width(const TypeExpression &typeExpr)
{
    TypeExpression temp = typeExpr;

    // First Remove top Parenthesis
    removeTopParenthesis(temp);

    if(isEmpty(temp))
    {
        CERR << "Error: TypeExpression is empty\n";
        return 1;
    }

    Type topType = whatIsType(temp);

    bool isbase = (topType == Type::VARIABLE);
    isbase = isbase || (topType == Type::ENUM_CONSTANT);
    isbase = isbase || (topType == Type::ENUM);
    isbase = isbase || (topType == Type::STRUCT_UNION);

    int size = 0;
    if (isbase)
    {
        BaseInfo *base = dynamic_cast<BaseInfo *>(temp.levelStack.top());
        size = width(*base);
    }
    else if (topType == Type::POINTER)
    {
        size = ADDRESS_SIZE;
    }
    else if (topType == Type::ARRAY)
    {
        ArrayInfo *array = dynamic_cast<ArrayInfo *>(temp.levelStack.top());
        TypeExpression element = temp;
        popALevel(element);
        size = array->dimSize * width(element);
    }
    else if (topType == Type::FUNCTION)
    {
        size = 1;
    }
    else
    {
        std::cerr << "Error : Something wrong in width(TypeExpression)\n";
        return -1;
    }

    // This will return the width of the type expression
    return size;
}

//=================[ TypeExpression ]================================================================================]

bool topIsParenthesis(const TypeExpression &typeExpr)
{
    // This will check if the top is ParenthesisInfo
    if (typeExpr.levelStack.empty())
    {
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    if (!info)
    {
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    return isParenthesisInfo(*info);
}

void removeTopParenthesis(TypeExpression &typeExpr)
{
    // This will remove only the top parenthesis
    while (topIsParenthesis(typeExpr))
    {
        typeExpr.levelStack.pop(); // ignore top-parenthesis
    }
}

Type whatIsType(const TypeExpression &typeExpr)
{
    // First Remove top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    if (temp.levelStack.empty())
    {
        return Type::EMPTY;
    }
    LevelInfo *info = temp.levelStack.top();
    if (!info)
    {
        std::cerr << "Error: LevelInfo is nullptr\n";
        return Type::UNKNOWN;
    }

    int topLevel = whichLevelInfo(*info);
    if (topLevel == BASE_LEVEL)
    {
        // Check if it is a record
        BaseInfo *base = dynamic_cast<BaseInfo *>(info);
        std::string baseType = base->baseType;
        std::string recordType = baseType.substr(0, baseType.find(" "));
        if (recordType == TYPE_STRUCT || recordType == TYPE_UNION)
        {
            return Type::STRUCT_UNION;
        }
        if (recordType == TYPE_ENUM)
        {
            return Type::ENUM;
        }
        if (recordType == ENUM_CONSTANT)
        {
            return Type::ENUM_CONSTANT;
        }

        // Then it is a variable
        return Type::VARIABLE;
    }
    else if (topLevel == POINTER_LEVEL)
    {
        return Type::POINTER;
    }
    else if (topLevel == ARRAY_LEVEL)
    {
        return Type::ARRAY;
    }
    else if (topLevel == PARAMETER_LEVEL)
    {
        return Type::FUNCTION;
    }

    return Type::UNKNOWN;
}

std::string toString(const TypeExpression &typeExpr)
{
    //Clear topParenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    std::string result = "";
    std::stack<LevelInfo *> tempStack = temp.levelStack;
    while (!tempStack.empty())
    {
        LevelInfo *info = tempStack.top();
        tempStack.pop();
        if (isParenthesisInfo(*info))
        {
            result = "(" + result + ")";
        }
        else if (isBaseInfo(*info))
        {
            BaseInfo *base = dynamic_cast<BaseInfo *>(info);
            // Add qualifiers
            std::string baseadd = "";

            for (auto qualifier : base->typeQualifiers)
            {
                if (qualifier == TypeQualifier::CONST)
                {
                    baseadd = "const " + baseadd;
                }
                else if (qualifier == TypeQualifier::VOLATILE)
                {
                    baseadd = "volatile " + baseadd;
                }
            }
            baseadd = baseadd + base->baseType;
            result = baseadd + (result.empty() ? "" : " ") + result;
        }
        else if (isPointerInfo(*info))
        {
            PointerInfo *ptr = dynamic_cast<PointerInfo *>(info);
            // Add qualifiers
            for (auto qualifier : ptr->typeQualifiers)
            {
                if (qualifier == TypeQualifier::CONST)
                {
                    result = "const " + result;
                }
                else if (qualifier == TypeQualifier::VOLATILE)
                {
                    result = "volatile " + result;
                }
            }
            result = "*" + result;
        }
        else if (isArrayInfo(*info))
        {
            ArrayInfo *arr = dynamic_cast<ArrayInfo *>(info);
            result = result + "[" + std::to_string(arr->dimSize) + "]";
        }
        else if (isParameterInfo(*info))
        {
            ParameterInfo *param = dynamic_cast<ParameterInfo *>(info);
            std::string paramStr = "(";
            for (int i = 0; i < param->paramsType.size(); i++)
            {
                paramStr += toString(param->paramsType[i]);
                if (i != param->paramsType.size() - 1)
                {
                    paramStr += ", ";
                }
            }
            paramStr += ")";
            result = result + paramStr;
        }
    }
    return result;
}

int popALevel(TypeExpression &typeExpr)
{
    // This will pop a level from the type expression
    if (typeExpr.levelStack.empty())
    {
        return POP_FAILURE;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    typeExpr.levelStack.pop();

    delete info; // [ERROR PRONE ⚠️]

    return POP_SUCCESS;
}

bool isEmpty(const TypeExpression &typeExpr)
{
    // This will check if the type expression is empty
    return typeExpr.levelStack.empty();
}

// Needed During Symbol Entry Creation
TypeExpression createTypeExpression(GenericSymbol *symbol)
{
    TypeExpression typeExpr;

    if (!symbol)
    {
        std::cerr << "Error: Symbol is nullptr\n";
        return typeExpr;
    }

    // Check if it is a variable
    if (isVariable(*symbol))
    {
        Variable *var = dynamic_cast<Variable *>(symbol);
        return var->type;
    }
    else if (isFunction(*symbol))
    {
        Function *func = dynamic_cast<Function *>(symbol);
        return func->type;
    }
    else if (isEnumConstant(*symbol))
    {
        BaseInfo *base = new BaseInfo();
        base->baseType = ENUM_CONSTANT;
    }
    return typeExpr;
}

// Needed for TypeExpression Creation of Constants
TypeExpression TypeExpressionForConstants(std::string constant){
    // [📍ToDo]
    return TypeExpression();
}

// Needed during Space & ValueType Logics
SPACE getSpace(const TypeExpression &typeExpr)
{

    // First Remove top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    // Only ARRAY & STRUCT/UNION are in Address Space
    Type whichType = whatIsType(temp);
    if (whichType == Type::ARRAY)
    {
        return SPACE::ADDRESS_SPACE;
    }
    if (whichType == Type::STRUCT_UNION)
    {
        return SPACE::ADDRESS_SPACE;
    }

    return SPACE::VALUE_SPACE;
}

VALUE_TYPE getValueType(const TypeExpression &typeExpr)
{

    // First Remove top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    Type whichType = whatIsType(temp);

    if (whichType == Type::ENUM_CONSTANT)
    {
        // This is a constant
        return VALUE_TYPE::RVALUE;
    }

    int isModifiable = isModifiableLvalue(temp);
    if (!isModifiable)
    {
        // Non-modifiable Lvalue (array, function, const keyword)
        return VALUE_TYPE::NM_LVALUE;
    }

    return VALUE_TYPE::M_LVALUE;
}

bool isModifiableLvalue(const TypeExpression &type)
{
    // First Remove top Parenthesis
    TypeExpression temp = type;
    removeTopParenthesis(temp);

    Type topType = whatIsType(temp);

    // Logic - Array or Function
    if (topType == Type::ARRAY || topType == Type::FUNCTION)
    {
        return false;
    }

    // Logic - Pointer with const qualifier
    if (topType == Type::POINTER)
    {
        PointerInfo *ptr = dynamic_cast<PointerInfo *>(temp.levelStack.top());
        for (auto qualifier : ptr->typeQualifiers)
        {
            if (qualifier == TypeQualifier::CONST)
            {
                return false;
            }
        }
    }

    // Logic - Base with const qualifier
    if (topType == Type::VARIABLE || topType == Type::STRUCT_UNION || topType == Type::ENUM)
    {
        BaseInfo *base = dynamic_cast<BaseInfo *>(temp.levelStack.top());

        // Base with const qualifier
        for (auto qualifier : base->typeQualifiers)
        {
            if (qualifier == TypeQualifier::CONST)
            {
                return false;
            }
        }

        // Base with record type can be modified
        //     std::string baseType = base->baseType;
        //     // it can have 3parts seprated by space or just one
        //     std::string recordType = baseType.substr(0, baseType.find(" "));
        //     if(recordType == "struct" || recordType == "union"){
        //         return true;
        //     }
        //     if(recordType == "enum"){
        //         return true;
        //     }
    }

    if(topType == Type::ENUM_CONSTANT){
        return false; // It's a Rvalue [Not a Lvalue]
    }

    return true;
}

// Equivalence Check on Types
int checkEquivalance(const TypeExpression &typeExpr1, const TypeExpression &typeExpr2)
{

    TypeExpression temp1 = typeExpr1;
    TypeExpression temp2 = typeExpr2;

    // Use Recursion to check equivalance
    removeTopParenthesis(temp1);
    removeTopParenthesis(temp2);

    if (isEmpty(temp1) && isEmpty(temp2))
    {
        // Both are empty
        return EQUIVALENT;
    }
    if (isEmpty(temp1) ^ isEmpty(temp2))
    {
        // One is empty and other is not
        // Error
        return LOW_ERROR;
    }

    // Both are not empty

    // Check a level
    LevelInfo *info1 = temp1.levelStack.top();
    LevelInfo *info2 = temp2.levelStack.top();
    if (!info1 || !info2)
    {
        // Should not happen
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }

    int levelcheck = checkEquivalance(*info1, *info2);
    if (levelcheck != EQUIVALENT)
    {
        return levelcheck;
    }

    // Current level is OKAY

    // Pop a level
    popALevel(temp1);
    popALevel(temp2);
    // Recursion
    int res = checkEquivalance(temp1, temp2);

    if (res == EQUIVALENT || res == WARNING)
    {
        return res; // OKAY or WARNING
    }
    // res == LOW_ERROR [Error from below but can be reduced by higher levels as warning]
    // Depending on current level it will be Error or Warning
    int type1 = whichLevelInfo(*info1);
    int type2 = whichLevelInfo(*info2);
    if (type1 == POINTER_LEVEL && type2 == POINTER_LEVEL)
    {
        // Pointer's Reduce Error level
        if (res == LOW_ERROR)
        {
            return WARNING; // Pointer to pointer
        }
        if (res == HIGH_ERROR)
        {
            return LOW_ERROR; // Pointer to pointer
        }
    }

    // Only if this level is pointer we can reduce to warning else No Reduction
    return res;
}

/*

*/

//=====================[ SubLevel Type's Utilities ]=========================================================================================

int checkEquivalance(const LevelInfo &info1, const LevelInfo &info2)
{
    // This will depend on stding baseType

    int type1 = whichLevelInfo(info1);
    int type2 = whichLevelInfo(info2);
    if (type1 != type2)
    {
        return LOW_ERROR;
        // Different levelTypes is Low Error
    }

    if (type1 == BASE_LEVEL)
    {
        // BaseInfo
        const BaseInfo *base1 = dynamic_cast<const BaseInfo *>(&info1);
        const BaseInfo *base2 = dynamic_cast<const BaseInfo *>(&info2);
        return checkEquivalance(*base1, *base2);
    }
    else if (type1 == POINTER_LEVEL)
    {
        // PointerInfo
        const PointerInfo *ptr1 = dynamic_cast<const PointerInfo *>(&info1);
        const PointerInfo *ptr2 = dynamic_cast<const PointerInfo *>(&info2);
        return checkEquivalance(*ptr1, *ptr2);
    }
    else if (type1 == ARRAY_LEVEL)
    {
        // ArrayInfo
        const ArrayInfo *arr1 = dynamic_cast<const ArrayInfo *>(&info1);
        const ArrayInfo *arr2 = dynamic_cast<const ArrayInfo *>(&info2);
        return checkEquivalance(*arr1, *arr2);
    }
    else if (type1 == PARAMETER_LEVEL)
    {
        // ParameterInfo
        const ParameterInfo *param1 = dynamic_cast<const ParameterInfo *>(&info1);
        const ParameterInfo *param2 = dynamic_cast<const ParameterInfo *>(&info2);
        return checkEquivalance(*param1, *param2);
    }
    else if (type1 == PARENTHESIS_LEVEL)
    {
        // No need to check
        return EQUIVALENT;
    }
    else
    {
        // Unknown Level
        std::cerr << "Error: Unknown LevelInfo\n";
        return LOW_ERROR;
    }

    return false;
}

int checkEquivalance(const PointerInfo &info1, const PointerInfo &info2)
{
    // nothing to check
    return EQUIVALENT;
}

int checkEquivalance(const ArrayInfo &info1, const ArrayInfo &info2)
{
    if (info1.dimSize != info2.dimSize)
    {
        return LOW_ERROR;
    }

    return EQUIVALENT;
}

int checkEquivalance(const ParameterInfo &info1, const ParameterInfo &info2)
{
    if (info1.paramsType.size() != info2.paramsType.size())
    {
        return HIGH_ERROR;
    }

    for (int i = 0; i < info1.paramsType.size(); i++)
    {
        int res = checkEquivalance(info1.paramsType[i], info2.paramsType[i]);
        if (res != EQUIVALENT)
        {
            return res;
        }
    }

    return EQUIVALENT;
}

int checkEquivalance(const BaseInfo &info1, const BaseInfo &info2)
{
    // Convert to string and compare
    if (info1.baseType != info2.baseType)
    {
        return HIGH_ERROR;
    }

    return EQUIVALENT;
}

int whichLevelInfo(const LevelInfo &info)
{
    // This will return the level of the info
    if(dynamic_cast<const BaseInfo *>(&info)){
        return BASE_LEVEL;
    }
    else if(dynamic_cast<const PointerInfo *>(&info)){
        return POINTER_LEVEL;
    }
    else if(dynamic_cast<const ArrayInfo *>(&info)){
        return ARRAY_LEVEL;
    }
    else if(dynamic_cast<const ParameterInfo *>(&info)){
        return PARAMETER_LEVEL;
    }
    else if(dynamic_cast<const ParenthesisInfo *>(&info)){
        return PARENTHESIS_LEVEL;
    }
    else{
        return UNKNOWN_LEVEL;
    }
}

bool isParenthesisInfo(const LevelInfo &info)
{
    return dynamic_cast<const ParenthesisInfo *>(&info);
}

bool isArrayInfo(const LevelInfo &info)
{
    return dynamic_cast<const ArrayInfo *>(&info);
}

bool isPointerInfo(const LevelInfo &info)
{
    return dynamic_cast<const PointerInfo *>(&info);
}

bool isBaseInfo(const LevelInfo &info)
{
    return dynamic_cast<const BaseInfo *>(&info);
}

bool isParameterInfo(const LevelInfo &info)
{
    return dynamic_cast<const ParameterInfo *>(&info);
}

