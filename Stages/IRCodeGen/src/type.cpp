#include "header.h"

//=====================[ Width Utilities ]=========================================================================================

int width(const UserDType &dtype)
{
    if(dtype.isComplete == false)
    {
        std::cerr << LOC << "Error: User Defined Type is not complete\n";
        return -1;
    }

    std::map<std::string, TypeExpression> members = dtype.members;
    int totalSize = 0;
    RecordType recordType = dtype.recordType;
    if (recordType == RecordType::UNION)
    {
        for (auto &member : members)
        {
            totalSize = std::max(totalSize, width(member.second));
        }
    }
    else if (recordType == RecordType::STRUCT)
    {
        // For struct
        for (auto &member : members)
        {
            totalSize += width(member.second);
        }
    }
    else if (recordType == RecordType::ENUM)
    {
        // For enum
        totalSize = WORD_SIZE; // Size of enum
    }
    else
    {
        std::cerr << LOC << LOC << "Error: Unknown Record Type\n";
        return -1;
    }
    std::cerr << LOC << LOC << "Width of " << dtype.symbolName << " : " << totalSize << std::endl;
    return totalSize;
}

int width(const BaseInfo &info)
{
    TypeExpression typeExpr;
    typeExpr.levelStack.push_back((LevelInfo *)&info);
    Type topType = whatIsType(typeExpr);
    if (topType == Type::VARIABLE)
    {
        std::string baseType = info.baseType;
        int w = width(baseType);
        if (w == -1)
        {
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

        size_t a = baseType.find(' '), b = baseType.find(' ', a + 1);
        std::string recordName = baseType.substr(a + 1, b - a - 1);

        std::string lastPart = baseType.substr(baseType.find_last_of(" ") + 1, baseType.length());
        std::string scopeNoStr = lastPart.substr(1, lastPart.length() - 1);
        int scopeNo = std::stoi(scopeNoStr);

        GenericSymbol *recordSymbol = nullptr;
        int recordCheck = SYM_TABLE.lookupRecord(recordName, recordSymbol, scopeNo);
        if (recordCheck == LOOKUP_FAILURE)
        {
            std::cerr << LOC << "Error: Record \"" + recordName + "\" not found in symbol table\n";
            return -1;
        }
        else
        {
            std::cerr << LOC << "😆 Found Record \"" + recordName + "\" in symbol table\n";
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

    if (isEmpty(temp))
    {
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
        BaseInfo *base = dynamic_cast<BaseInfo *>(temp.levelStack.back());
        size = width(*base);
    }
    else if (topType == Type::POINTER)
    {
        size = ADDRESS_SIZE;
    }
    else if (topType == Type::ARRAY)
    {
        ArrayInfo *array = dynamic_cast<ArrayInfo *>(temp.levelStack.back());
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
        std::cerr << LOC << "Error : Something wrong in width(TypeExpression)\n";
        return -1;
    }

    // This will return the width of the type expression
    return size;
}

int elementWidth(const TypeExpression &typeExpr)
{
    // Remove Top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    if (isEmpty(temp))
    {
        return -1;
    }

    // If base type
    Type topType = whatIsType(temp);
    if (topType == Type::VARIABLE || topType == Type::ENUM_CONSTANT || topType == Type::ENUM || topType == Type::STRUCT_UNION)
    {
        return 1;
    }
    else if (topType == Type::FUNCTION)
    {
        return 1;
    }
    else if (topType == Type::POINTER || topType == Type::ARRAY)
    {
        // Find width of below level
        TypeExpression belowLevel = temp;
        popALevel(belowLevel);
        return width(belowLevel);
    }

    std::cerr << LOC << "Error: Something wrong in elementWidth(TypeExpression)\n";
    return -1;
}

//=================[ TypeExpression ]================================================================================]

bool topIsParenthesis(const TypeExpression &typeExpr)
{
    // This will check if the top is ParenthesisInfo
    if (typeExpr.levelStack.empty())
    {
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.back();
    // HERE;
    if (!info)
    {
        std::cerr << LOC << "Error: LevelInfo is nullptr\n";
        // HERE;
        return false;
    }
    return isParenthesisInfo(*info);
}

void removeTopParenthesis(TypeExpression &typeExpr)
{
    // This will remove only the top parenthesis
    while (topIsParenthesis(typeExpr))
    {
        typeExpr.levelStack.pop_back(); // ignore top-parenthesis
    }
    return;
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
    LevelInfo *info = temp.levelStack.back();
    if (!info)
    {
        std::cerr << LOC << "Error: LevelInfo is nullptr\n";
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

    std::cerr << LOC << "Error: Unknown LevelInfo type\n";

    return Type::UNKNOWN;
}

std::string toString(Type whichType)
{
    if (whichType == Type::VARIABLE)
    {
        return "VARIABLE";
    }
    else if (whichType == Type::POINTER)
    {
        return "POINTER";
    }
    else if (whichType == Type::ARRAY)
    {
        return "ARRAY";
    }
    else if (whichType == Type::FUNCTION)
    {
        return "FUNCTION";
    }
    else if (whichType == Type::ENUM_CONSTANT)
    {
        return "ENUM_CONSTANT";
    }
    else if (whichType == Type::STRUCT_UNION)
    {
        return "STRUCT_UNION";
    }
    else if (whichType == Type::ENUM)
    {
        return "ENUM";
    }
    else
    {
        return "UNKNOWN";
    }
}

std::string toString(const TypeExpression &typeExpr)
{
    // Clear topParenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);
    std::string result = "";
    for (int i = typeExpr.levelStack.size() - 1; i >= 0; i--)
    {
        int k = typeExpr.levelStack[i]->levelType;
        if (k == PARENTHESIS_LEVEL)
        {
            result = "(" + result + ")";
        }
        else if (k == BASE_LEVEL)
        {
            BaseInfo *base = dynamic_cast<BaseInfo *>(typeExpr.levelStack[i]);
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
        else if (k == POINTER_LEVEL)
        {
            PointerInfo *ptr = dynamic_cast<PointerInfo *>(typeExpr.levelStack[i]);
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
        else if (k == ARRAY_LEVEL)
        {
            ArrayInfo *arr = dynamic_cast<ArrayInfo *>(typeExpr.levelStack[i]);
            result = result + "[" + std::to_string(arr->dimSize) + "]";
        }
        else if (isParameterInfo(*typeExpr.levelStack[i]))
        {
            ParameterInfo *param = dynamic_cast<ParameterInfo *>(typeExpr.levelStack[i]);
            std::string paramStr = "(";
            for (int i = 0; i < param->paramsType.size(); i++)
            {
                paramStr += toString(param->paramsType[i]);
                if (i != param->paramsType.size() - 1)
                {
                    paramStr += ", ";
                }
            }
            if(param->isVaradic)
            {
                if (paramStr != "(")
                {
                    paramStr += ", ";
                }
                paramStr += "...";
            }
            paramStr += ")";
            result = result + paramStr;
        }
        else
        {
            std::cerr << LOC << "Error: Unknown LevelInfo type\n";
            return "";
        }
    }
    return result;
}

int popALevel(TypeExpression &typeExpr)
{
    // REMOVE TOP PARENTHESIS
    removeTopParenthesis(typeExpr);
    // This will pop a level from the type expression
    if (typeExpr.levelStack.empty())
    {
        return POP_FAILURE;
    }
    LevelInfo *info = typeExpr.levelStack.back();
    typeExpr.levelStack.pop_back();

    // Remove ParenthesisInfo
    removeTopParenthesis(typeExpr);
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
        std::cerr << LOC << "Error: Symbol is nullptr\n";
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

int ProcessConstants(std::string inputValue, TypeExpression &typeExpr, std::string &finalValue)
{
    // Allocate a new BaseInfo to record the type.
    BaseInfo *base = new BaseInfo();
    try
    {
        // ----- Character Literals -----
        // If input is enclosed in single quotes, assume it's a character literal.
        if (inputValue.size() >= 3 && inputValue.front() == '\'' && inputValue.back() == '\'')
        {
            // For now, only support single-character literal without escapes.
            if (inputValue.size() == 3)
            {
                char c = inputValue[1];
                base->baseType = TYPE_CHAR;
                finalValue = std::string(1, c);
                typeExpr.levelStack.push_back(base);
                return OKAY;
            }
            else
            {
                throw std::invalid_argument("Invalid character literal");
            }
        }

        // ----- Floating-Point Literals (with trailing 'f') -----
        if (!inputValue.empty() && inputValue.back() == 'f')
        {
            // Remove trailing 'f'
            std::string numPart = inputValue.substr(0, inputValue.size() - 1);
            float fval = std::stof(numPart);
            // (Could add an explicit range check using std::numeric_limits<float>::max())
            base->baseType = TYPE_FLOAT;
            finalValue = std::to_string(fval);
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }

        // ----- Floating-Point Literals (decimal point) -----
        if (inputValue.find('.') != std::string::npos)
        {
            double dval = std::stod(inputValue);
            base->baseType = TYPE_DOUBLE;
            finalValue = std::to_string(dval);
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }

        // ----- Exponent Notation -----
        if (inputValue.find('e') != std::string::npos ||
            inputValue.find('E') != std::string::npos)
        {
            double dval = std::stod(inputValue);
            // If the value is integral, choose an integer type.
            if (dval == static_cast<long long>(dval))
            {
                long long ival = static_cast<long long>(dval);
                if (ival >= std::numeric_limits<int>::min() &&
                    ival <= std::numeric_limits<int>::max())
                {
                    base->baseType = TYPE_INT;
                }
                else if (ival >= std::numeric_limits<long>::min() &&
                         ival <= std::numeric_limits<long>::max())
                {
                    base->baseType = TYPE_LONG;
                }
                else
                {
                    base->baseType = TYPE_LONG;
                }
                finalValue = std::to_string(ival);
            }
            else
            {
                base->baseType = TYPE_DOUBLE;
                finalValue = std::to_string(dval);
            }
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }

        // ----- Binary Literals -----
        if (inputValue.size() > 2 &&
            (inputValue.substr(0, 2) == "0b" || inputValue.substr(0, 2) == "0B"))
        {
            std::string binPart = inputValue.substr(2);
            // Validate that every character is '0' or '1'
            for (char ch : binPart)
            {
                if (ch != '0' && ch != '1')
                    throw std::invalid_argument("Invalid binary literal");
            }
            long long value = 0;
            for (char ch : binPart)
            {
                value = value * 2 + (ch - '0');
            }
            if (value >= std::numeric_limits<int>::min() &&
                value <= std::numeric_limits<int>::max())
            {
                base->baseType = TYPE_INT;
            }
            else if (value >= std::numeric_limits<long>::min() &&
                     value <= std::numeric_limits<long>::max())
            {
                base->baseType = TYPE_LONG;
            }
            else
            {
                base->baseType = TYPE_LONG;
            }
            finalValue = std::to_string(value);
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }

        // ----- Hexadecimal Literals -----
        if (inputValue.size() > 2 &&
            (inputValue.substr(0, 2) == "0x" || inputValue.substr(0, 2) == "0X"))
        {
            std::string hexPart = inputValue.substr(2);
            for (char ch : hexPart)
            {
                if (!std::isxdigit(ch))
                    throw std::invalid_argument("Invalid hexadecimal literal");
            }
            long long value = std::stoll(hexPart, nullptr, 16);
            if (value >= std::numeric_limits<int>::min() &&
                value <= std::numeric_limits<int>::max())
            {
                base->baseType = TYPE_INT;
            }
            else if (value >= std::numeric_limits<long>::min() &&
                     value <= std::numeric_limits<long>::max())
            {
                base->baseType = TYPE_LONG;
            }
            else
            {
                base->baseType = TYPE_LONG;
            }
            finalValue = std::to_string(value);
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }

        // ----- Octal Literals -----
        // If the number starts with '0' and is more than one digit.
        if (inputValue.size() > 1 && inputValue[0] == '0')
        {
            std::string octPart = inputValue.substr(1);
            for (char ch : octPart)
            {
                if (ch < '0' || ch > '7')
                    throw std::invalid_argument("Invalid octal literal");
            }
            long long value = std::stoll(inputValue, nullptr, 8);
            if (value >= std::numeric_limits<int>::min() &&
                value <= std::numeric_limits<int>::max())
            {
                base->baseType = TYPE_INT;
            }
            else if (value >= std::numeric_limits<long>::min() &&
                     value <= std::numeric_limits<long>::max())
            {
                base->baseType = TYPE_LONG;
            }
            else
            {
                base->baseType = TYPE_LONG;
            }
            finalValue = std::to_string(value);
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }

        // ----- Decimal Integer Literals -----
        {
            long long value = std::stoll(inputValue, nullptr, 10);
            if (value >= std::numeric_limits<int>::min() &&
                value <= std::numeric_limits<int>::max())
            {
                base->baseType = TYPE_INT;
            }
            else if (value >= std::numeric_limits<long>::min() &&
                     value <= std::numeric_limits<long>::max())
            {
                base->baseType = TYPE_LONG;
            }
            else
            {
                base->baseType = TYPE_LONG;
            }
            finalValue = std::to_string(value);
            typeExpr.levelStack.push_back(base);
            return OKAY;
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << LOC << "Error in ProcessConstants: " << ex.what() << "\n";
        delete base;
        return FAIL;
    }
    // Should not get here.
    delete base;
    return FAIL;
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
    // Modifiable Lvalue (variable, pointer, struct/union)
    return VALUE_TYPE::M_LVALUE;
}

bool isModifiableLvalue(const TypeExpression &type)
{
    // First Remove top Parenthesis
    TypeExpression temp = type;
    removeTopParenthesis(temp);

    Type topType = whatIsType(temp);
    std::cerr << LOC << " Top Type: " << toString(temp) << "\n";

    // Logic - Array or Function
    if (topType == Type::ARRAY || topType == Type::FUNCTION)
    {
        return false;
    }



    // Logic - Pointer with const qualifier
    if (topType == Type::POINTER)
    {
        PointerInfo *ptr = dynamic_cast<PointerInfo *>(temp.levelStack.back());
        for (auto qualifier : ptr->typeQualifiers)
        {
            if (qualifier == TypeQualifier::CONST)
            {
                return false;
            }
        }
        return true;
    }

    // Logic - Base with const qualifier
    if (topType == Type::VARIABLE || topType == Type::STRUCT_UNION || topType == Type::ENUM)
    {
        BaseInfo *base = dynamic_cast<BaseInfo *>(temp.levelStack.back());

        // Base with const qualifier
        for (auto qualifier : base->typeQualifiers)
        {
            if (qualifier == TypeQualifier::CONST)
            {
                return false;
            }
        }
        return true;
    }

    if (topType == Type::ENUM_CONSTANT)
    {
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
    LevelInfo *info1 = temp1.levelStack.back();
    LevelInfo *info2 = temp2.levelStack.back();
    if (!info1 || !info2)
    {
        // Should not happen
        std::cerr << LOC << "Error: LevelInfo is nullptr\n";
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

int ourEquivalent(const TypeExpression &type1, const TypeExpression &type2)
{
    // REmove Parenthesis
    TypeExpression temp1 = type1;
    TypeExpression temp2 = type2;
    removeTopParenthesis(temp1);
    removeTopParenthesis(temp2);
    // std::cerr << LOC  << "Type1: " << toString(temp1) << "\n";
    // std::cerr << LOC  << "Type2: " << toString(temp2) << "\n";
    // If top is pointer Type - POINTER, ARRAY
    // Then ignore lower levels
    Type topType1 = whatIsType(temp1);
    Type topType2 = whatIsType(temp2);

    // std::cerr << LOC  << "Top Type1: of Type1: " << toString(topType1) << "is " << toString(temp1) << "\n";
    // std::cerr << LOC  << "Top Type2: of Type2: " << toString(topType2) << "is " << toString(temp2) << "\n";

    bool isPtr1 = (topType1 == Type::POINTER || topType1 == Type::ARRAY);
    bool isPtr2 = (topType2 == Type::POINTER || topType2 == Type::ARRAY);
    if (isPtr1 && isPtr2)
    {
        return EQUIVALENT;
    }

    if (topType1 == Type::FUNCTION && topType2 == Type::FUNCTION)
    {
        // We check parameter types
        ParameterInfo *param1 = dynamic_cast<ParameterInfo *>(temp1.levelStack.back());
        ParameterInfo *param2 = dynamic_cast<ParameterInfo *>(temp2.levelStack.back());
        if (param1->paramsType.size() != param2->paramsType.size())
        {
            return LOW_ERROR;
        }
        for (int i = 0; i < param1->paramsType.size(); i++)
        {
            int res = ourEquivalent(param1->paramsType[i], param2->paramsType[i]);
            if (res != EQUIVALENT)
            {
                return res;
            }
        }
        // Okay

        // We recurse on return type
        TypeExpression returnType1 = temp1;
        TypeExpression returnType2 = temp2;
        popALevel(returnType1);
        popALevel(returnType2);
        int res = ourEquivalent(returnType1, returnType2);
        return res;
    }

    // Check equivalance of base level

    if(topType1 == Type::VARIABLE && topType2 == Type::VARIABLE)
    {
        // Both are variable
        BaseInfo *base1 = dynamic_cast<BaseInfo *>(temp1.levelStack.back());
        BaseInfo *base2 = dynamic_cast<BaseInfo *>(temp2.levelStack.back());
        if (base1->baseType == base2->baseType)
        {
            return EQUIVALENT;
        }
    }

    bool isNumeric1 = isNumeric(type1);
    bool isNumeric2 = isNumeric(type2);
    if (isNumeric1 && isNumeric2)
    {
        std::cerr << LOC << " Both are numeric\n";
        std::cerr << LOC << " 😅Type1: " << toString(type1) << "\n";
        std::cerr << LOC << " Type2: " << toString(type2) << "\n";
        // Both are numeric
        std::string base1 = isPrimitive(type1);
        std::string base2 = isPrimitive(type2);
        if (base1 == base2)
        {
            return EQUIVALENT;
        }
        else
        {
            return LOW_ERROR;
        }
    }

    // Then we need to check for custom types
    if (topType1 == Type::STRUCT_UNION && topType2 == Type::STRUCT_UNION)
    {
        // Both are struct/union
        // Check if they are same
        BaseInfo *base1 = dynamic_cast<BaseInfo *>(temp1.levelStack.back());
        BaseInfo *base2 = dynamic_cast<BaseInfo *>(temp2.levelStack.back());
        if (base1->baseType == base2->baseType)
        {
            return EQUIVALENT;
        }
    }

    return LOW_ERROR;
}

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
        std::cerr << LOC << "Error: Unknown LevelInfo\n";
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
    if (dynamic_cast<const BaseInfo *>(&info))
    {
        return BASE_LEVEL;
    }
    else if (dynamic_cast<const PointerInfo *>(&info))
    {
        return POINTER_LEVEL;
    }
    else if (dynamic_cast<const ArrayInfo *>(&info))
    {
        return ARRAY_LEVEL;
    }
    else if (dynamic_cast<const ParameterInfo *>(&info))
    {
        return PARAMETER_LEVEL;
    }
    else if (dynamic_cast<const ParenthesisInfo *>(&info))
    {
        return PARENTHESIS_LEVEL;
    }
    else
    {
        return UNKNOWN_LEVEL;
    }
}

bool isParenthesisInfo(const LevelInfo &info)
{
    return (info.levelType == PARENTHESIS_LEVEL);
}

bool isArrayInfo(const LevelInfo &info)
{
    return (info.levelType == ARRAY_LEVEL);
}

bool isPointerInfo(const LevelInfo &info)
{
    return (info.levelType == POINTER_LEVEL);
}

bool isBaseInfo(const LevelInfo &info)
{
    return (dynamic_cast<const BaseInfo *>(&info));
}

bool isParameterInfo(const LevelInfo &info)
{
    return (info.levelType == PARAMETER_LEVEL);
}
