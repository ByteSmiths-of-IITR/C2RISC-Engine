#include "header.h"
#include "utility.h"

//=====================[ Error Handling ]=========================================================================================

std::vector<std::string> compilerLOG; // [extern declared in header.h]
std::vector<std::string> semanticLOG; // [extern declared in header.h]
std::string semanticMessage;          // [extern declared in header.h]
//====================[ Globally Accessible Variables ]=========================================================================================
SymbolTable SYM_TABLE; // Global Symbol Table
TAC IR_CODE;           // Global TAC Code Base

//====================[ Annotated Parse Tree ]=========================================================================================

int ANNOTATE = 1; // 0 - OFF | 1 - ON [extern declared in header.h]

//=====================[ toString Utilities ]=========================================================================================
std::string toString(int value)
{
    std::string str = std::to_string(value);
    return str;
}

std::string toString(bool flag)
{
    return flag ? "true" : "false";
}

std::string toString(std::vector<std::string> valueVector)
{
    std::string str = "[ ";
    for (size_t i = 0; i < valueVector.size(); ++i)
    {
        str += valueVector[i];
        if (i != valueVector.size() - 1)
        {
            str += ", ";
        }
    }
    str += " ]";
    return str;
}

std::string toString(StorageClass storageClass)
{
    switch (storageClass)
    {
    case StorageClass::AUTO:
        return "auto";
    case StorageClass::STATIC:
        return "static";
    case StorageClass::EXTERN:
        return "extern";
    case StorageClass::TYPEDEF:
        return "typedef";
    case StorageClass::NONE:
        return "";
    default:
        return "unknown-storage-class";
    }
}

std::string toString(TypeQualifier typeQualifier)
{
    switch (typeQualifier)
    {
    case TypeQualifier::CONST:
        return "const";
    case TypeQualifier::VOLATILE:
        return "volatile";
    case TypeQualifier::RESTRICT:
        return "restrict";
    default:
        return "UNKNOWN_TYPE_QUALIFIER";
    }
}

std::string toString(std::vector<TypeQualifier> typeQualifiers)
{
    std::string str = "{ ";
    for (size_t i = 0; i < typeQualifiers.size(); ++i)
    {
        str += toString(typeQualifiers[i]);
        if (i != typeQualifiers.size() - 1)
        {
            str += ", ";
        }
    }
    str += " }";
    return str;
}

std::string toString(std::map<std::string, TypeExpression> members)
{
    std::string str = "{ ";
    for (const auto &pair : members)
    {
        std::string unit = "( " + pair.first + " : " + toString(pair.second) + " )";
        str += unit;
        str += " ";
    }
    str += " }";
    return str;
}

std::string toString(std::vector<PointerInfo *> ptrInfo)
{
    std::string str = "[ ";
    for (size_t i = 0; i < ptrInfo.size(); ++i)
    {
        PointerInfo *unit = ptrInfo[i];
        str += " *";
        for (size_t j = 0; j < unit->typeQualifiers.size(); ++j)
        {
            str += toString(unit->typeQualifiers[j]) + " ";
        }
        if (i != ptrInfo.size() - 1)
        {
            str += ", ";
        }
    }
    str += " ]";
    return str;
}

std::string toString(std::vector<TypeExpression> &paramVector)
{
    std::string str = "(";
    for (size_t i = 0; i < paramVector.size(); ++i)
    {
        str += toString(paramVector[i]);
        if (i != paramVector.size() - 1)
        {
            str += ", ";
        }
    }
    str += ")";
    return str;
}

std::string toString(SPACE space)
{
    if (space == SPACE::VALUE_SPACE)
    {
        return "value_space";
    }
    else if (space == SPACE::ADDRESS_SPACE)
    {
        return "address_space";
    }
    else if (space == SPACE::UNKNOWN_SPACE)
    {
        return "unknown_space";
    }
    else
    {
        return "don't_know_space";
    }
}

std::string toString(std::vector<int> vecList)
{
    std::string str = "[ ";
    for (size_t i = 0; i < vecList.size(); ++i)
    {
        str += std::to_string(vecList[i]);
        if (i != vecList.size() - 1)
        {
            str += ", ";
        }
    }
    str += " ]";
    return str;
}

std::string toString(VALUE_TYPE valueType)
{
    if (valueType == VALUE_TYPE::NM_LVALUE)
    {
        return "NON-M_LVALUE";
    }
    else if (valueType == VALUE_TYPE::M_LVALUE)
    {
        return "M_LVALUE";
    }
    else if (valueType == VALUE_TYPE::RVALUE)
    {
        return "R-VALUE";
    }
    else
    {
        return "UNKNOWN_VALUE_TYPE";
    }
}

std::string toString(RecordType recordType)
{
    if (recordType == RecordType::STRUCT)
    {
        return "struct";
    }
    else if (recordType == RecordType::UNION)
    {
        return "union";
    }
    else if (recordType == RecordType::ENUM)
    {
        return "enum";
    }
    else
    {
        return "UNKNOWN_RECORD_TYPE";
    }
}

//====================[ Helper Functions ]=========================================================================================

StorageClass getStorageClass(const std::string &value)
{
    if (value == "auto")
        return StorageClass::AUTO;
    else if (value == "static")
        return StorageClass::STATIC;
    else if (value == "extern")
        return StorageClass::EXTERN;
    else if (value == "typedef")
        return StorageClass::TYPEDEF;
    else
        return StorageClass::NONE;
}

TypeQualifier getTypeQualifier(const std::string &value)
{
    if (value == "const")
        return TypeQualifier::CONST;
    else if (value == "volatile")
        return TypeQualifier::VOLATILE;
    else if (value == "restrict")
        return TypeQualifier::RESTRICT;
    else
        return TypeQualifier::NONE;
}

std::string getProduction(ASTNode *node)
{
    // lastFuncCalled = "getProduction";
    std::string production = "";
    int numChildren = node->children.size();
    for (int i = 0; i < numChildren; i++)
    {
        if (i != 0)
        {
            production += " ";
        }
        production += node->children[i]->type;
    }
    return production;
}

int ProcessDecSpecifiers(std::vector<std::string> &valueVector, TypeExpression &type, StorageClass &storageClass)
{
    // 1. Initialize the base and storageClass
    int check = OKAY;

    // Check if the valueVector is empty
    if (valueVector.empty())
    {
        return LOW_ERROR; // ERROR
    }

    // Print the valueVector
    std::string args = "";
    for (size_t i = 0; i < valueVector.size(); ++i)
    {
        args += "|" + valueVector[i] + "|" + (i == valueVector.size() - 1 ? "" : ", ");
    }

    std::vector<StorageClass> storageClassVector;
    std::vector<TypeQualifier> typeQualifierVector;
    std::vector<std::string> typeSpecifierVector;

    TypeExpression resultType;

    // Put all values in respective vectors
    for (size_t i = 0; i < valueVector.size(); ++i)
    {
        std::string value = valueVector[i];
        if (value == "auto" || value == "static" || value == "extern" || value == "typedef")
        {
            StorageClass sc = getStorageClass(value);
            storageClassVector.push_back(sc);
        }
        else if (value == "const" || value == "volatile" || value == "restrict")
        {
            TypeQualifier tq = getTypeQualifier(value);
            typeQualifierVector.push_back(tq);
        }
        else
        {
            typeSpecifierVector.push_back(value);
        }
    }

    // 2. Process the storageClass
    if (storageClassVector.size() > 1)
    {
        semanticMessage = "Multiple Storage Classes in declaration specifiers";
        check = LOW_ERROR; // ERROR
    }
    else if (storageClassVector.size() == 1)
    {
        storageClass = storageClassVector[0];
    }
    else
    {
        storageClass = StorageClass::NONE;
    }

    BaseInfo *base = new BaseInfo();

    // 3. Process the typeQualifier
    std::vector<bool> isPresent(3, false);
    bool duplicate = false;
    for (size_t i = 0; i < typeQualifierVector.size(); ++i)
    {
        TypeQualifier tq = typeQualifierVector[i];
        if (tq == TypeQualifier::CONST)
        {
            if (!isPresent[0])
            {
                base->typeQualifiers.push_back(TypeQualifier::CONST);
                isPresent[0] = true;
            }
            else
            {
                duplicate = true;
            }
        }
        else if (tq == TypeQualifier::VOLATILE)
        {
            if (!isPresent[1])
            {
                base->typeQualifiers.push_back(TypeQualifier::VOLATILE);
                isPresent[1] = true;
            }
            else
            {
                duplicate = true;
            }
        }
        else if (tq == TypeQualifier::RESTRICT)
        {
            if (!isPresent[2])
            {
                base->typeQualifiers.push_back(TypeQualifier::RESTRICT);
                isPresent[2] = true;
            }
            else
            {
                duplicate = true;
            }
        }
    }

    if (duplicate)
    {
        semanticMessage = "Duplicate Type Qualifiers in declaration specifiers";
        check = WARNING;
    }

    // 4. Process "typedef"
    if (storageClass == StorageClass::TYPEDEF)
    {
        // This is a definition of a typedef // Should give back a type
        // Move On
    }

    // 5. Process the type specifiers [Two case - all Are a C InbuiltType or only one TypeDef Defined TYPE_NAME]
    // 5.1 First we check if the values are only primiteve types
    bool allAreInbuiltType = true;
    for (size_t i = 0; i < typeSpecifierVector.size(); ++i)
    {
        std::string value = typeSpecifierVector[i];
        if (!isA_InbuiltType(value))
        {
            allAreInbuiltType = false;
            break;
        }
    }

    // std::cerr << LOC << "😇 All are inbuilt types: " << allAreInbuiltType << std::endl;
    // std::cerr << LOC << "😇 Type Specifier Vector: " << toString(typeSpecifierVector) << std::endl;

    if (!allAreInbuiltType)
    {
        // Are are not Primtive
        // Then there must be only one typedef defined type
        if (typeSpecifierVector.size() != 1)
        {
            semanticMessage = "More than one TypeSpecifier with User Defined TypeSpecifier";
            check = LOW_ERROR; // ERROR
        }
        else
        {
            std::string firstPart = typeSpecifierVector[0].substr(0, typeSpecifierVector[0].find(" "));
            if (firstPart == TYPE_STRUCT || firstPart == TYPE_UNION || firstPart == TYPE_ENUM)
            {
                // This is a struct or union or enum
                base->baseType = typeSpecifierVector[0];
                resultType.levelStack.push_back(base);
            }
            else
            {
                // TypeSpecifier must be a TYPE_NAME
                // Check in Symbol Table if present
                std::string typeName = typeSpecifierVector[0];
                std::string typeDefkey = TYPEDEF_PREFIX + typeName;
                GenericSymbol *sym = nullptr;
                int lookupCheck = SYM_TABLE.lookup(typeDefkey, sym);
                if (lookupCheck == LOOKUP_FAILURE)
                {
                    semanticMessage = "TypeSpecifier \"" + typeName + "\" not found in symbol table";
                    check = LOW_ERROR; // ERROR
                }
                else
                {
                    ;
                    // Type name found
                    if (sym->symbolType == SYMBOL_TYPE::TYPEDEF)
                    {
                        resultType = ((TypeDefs *)sym)->type;
                    }
                    else
                    {
                        semanticMessage = "TypeSpecifier \"" + typeName + "\" is not a typedef nor a record type";
                        check = LOW_ERROR; // ERROR
                    }
                }
            }
        }
    }
    else
    {
        // All are inbuilt types

        std::string finalBase = combineType(typeSpecifierVector);
        if (finalBase == INVALID_COMBINATION)
        {
            semanticMessage = "Invalid Type Combination of inbuild typeSpecifiers in declaration specifiers";
            check = LOW_ERROR; // ERROR
        }
        else
        {
            base->baseType = finalBase;
            resultType.levelStack.push_back(base);
        }
    }

    type = resultType;

    std::string output = "|" + toString(storageClass) + "|" + toString(type) + "| CHECK: " + toString(check) + "";
    return check;
}

int add_printf_scanf(ASTNode *node)
{
    TypeExpression printfType;
    TypeExpression scanfType;
    ParameterInfo *paramInfo = new ParameterInfo();

    // Create first ArgType (const char *)
    TypeExpression intArg;
    BaseInfo *base = new BaseInfo();
    base->baseType = TYPE_CHAR;
    base->typeQualifiers.push_back(TypeQualifier::CONST);
    intArg.levelStack.push_back(base);
    PointerInfo *ptrInfo = new PointerInfo();
    intArg.levelStack.push_back(ptrInfo);

    paramInfo->paramsType.push_back(intArg);
    paramInfo->isVariadic = true;
    paramInfo->isVaradic = true;

    // Create the Return Type (void)
    BaseInfo *intBase = new BaseInfo();
    intBase->baseType = TYPE_VOID;

    printfType.levelStack.push_back(intBase);
    printfType.levelStack.push_back(paramInfo);

    scanfType.levelStack.push_back(intBase);
    scanfType.levelStack.push_back(paramInfo);

    // Add these to the symbol table
    Function *printfFunc = new Function();
    printfFunc->symbolName = "printf";
    printfFunc->type = printfType;
    printfFunc->isDefined = true;
    printfFunc->location = std::make_pair(-1, -1);
    printfFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    printfFunc->isDefined = true;

    // Create scanf function
    Function *scanfFunc = new Function();
    scanfFunc->symbolName = "scanf";
    scanfFunc->type = scanfType;
    scanfFunc->isDefined = true;
    scanfFunc->location = std::make_pair(-1, -1);
    scanfFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    scanfFunc->isDefined = true;

    // Add these to the symbol table
    int insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "printf", printfFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "scanf", scanfFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }


    // aptLOG("Added 🤫 printf and scanf to symbol table 🖨️ due to lib <stdio.h>");

    return INSERT_SUCCESS;
}

int add_our_print_scan(ASTNode *node){

    /* Function signatures
    -> void printVar(int var);
    -> void printString(char *str);
    -> int scanVar();
    -> char *scanString(int size);
    */

    TypeExpression printVarType;
    TypeExpression printStringType;
    TypeExpression scanVarType;
    TypeExpression scanStringType;


    // Create int
    TypeExpression intArg;
    BaseInfo *intBase = new BaseInfo();
    intBase->baseType = TYPE_INT;
    intArg.levelStack.push_back(intBase);

    // Create char *
    TypeExpression charPtrArg;
    BaseInfo *charBase = new BaseInfo();
    charBase->baseType = TYPE_CHAR;
    charPtrArg.levelStack.push_back(charBase);
    PointerInfo *ptrInfo = new PointerInfo();
    charPtrArg.levelStack.push_back(ptrInfo);

    // Create void
    TypeExpression voidType;
    BaseInfo *voidBase = new BaseInfo();
    voidBase->baseType = TYPE_VOID;
    voidType.levelStack.push_back(voidBase);

    // Creating all the function signatures
    printVarType.levelStack.push_back(voidBase);
        // Create argument type
    ParameterInfo *printVarParam = new ParameterInfo();
    printVarParam->paramsType.push_back(intArg);
    printVarParam->isVariadic = false;

    printVarType.levelStack.push_back(printVarParam);

    // Add these to the symbol table
    Function *printVarFunc = new Function();
    printVarFunc->symbolName = "printVar";
    printVarFunc->type = printVarType;
    printVarFunc->isDefined = true;
    printVarFunc->location = std::make_pair(-1, -1);
    printVarFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    int insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "printVar", printVarFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }

    // Create printString function
    printStringType.levelStack.push_back(voidBase);
    // Create argument type
    ParameterInfo *printStringParam = new ParameterInfo();
    printStringParam->paramsType.push_back(charPtrArg);
    printStringParam->isVariadic = false;

    printStringType.levelStack.push_back(printStringParam);

    // Add these to the symbol table
    Function *printStringFunc = new Function();
    printStringFunc->symbolName = "printString";
    printStringFunc->type = printStringType;
    printStringFunc->isDefined = true;
    printStringFunc->location = std::make_pair(-1, -1);
    printStringFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "printString", printStringFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }

    // Create scanVar function
    scanVarType.levelStack.push_back(intBase);
    // Create argument type
    ParameterInfo *scanVarParam = new ParameterInfo();
    // No arguments
    
    scanVarParam->isVariadic = false;
    scanVarType.levelStack.push_back(scanVarParam);

    // Add these to the symbol table
    Function *scanVarFunc = new Function();
    scanVarFunc->symbolName = "scanVar";
    scanVarFunc->type = scanVarType;
    scanVarFunc->isDefined = true;
    scanVarFunc->location = std::make_pair(-1, -1);
    scanVarFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "scanVar", scanVarFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }

    // Create scanString function
    scanStringType.levelStack.push_back(charBase);
    // Create argument type
    ParameterInfo *scanStringParam = new ParameterInfo();
    scanStringParam->paramsType.push_back(intArg);
    scanStringParam->isVariadic = false;
    scanStringType.levelStack.push_back(scanStringParam);

    // Add these to the symbol table
    Function *scanStringFunc = new Function();
    scanStringFunc->symbolName = "scanString";
    scanStringFunc->type = scanStringType;
    scanStringFunc->isDefined = true;
    scanStringFunc->location = std::make_pair(-1, -1);
    scanStringFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "scanString", scanStringFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }

    // aptLOG("Added 🤫 our print and scan to symbol table 🖨️ due to lib <stdio.h>");

    return INSERT_SUCCESS;
}

int addVaradicLib(ASTNode *node)
{
    // We define two lib function of varadics
    // va_start & va_end | va_list

    TypeExpression va_startType;
    TypeExpression va_endType;

    // Create first ArgType (va_list)
    BaseInfo *vaBase = new BaseInfo();
    vaBase->baseType = TYPE_VA_LIST;
    TypeExpression vaListArg;
    vaListArg.levelStack.push_back(vaBase);

    // Create the Return Type (void)
    BaseInfo *voidBase = new BaseInfo();
    voidBase->baseType = TYPE_VOID;
    // TypeExpression returnType;
    // returnType.levelStack.push_back(voidBase);

    // Create second ArgType (int)
    BaseInfo *intBase = new BaseInfo();
    intBase->baseType = TYPE_INT;
    TypeExpression intArg;
    intArg.levelStack.push_back(intBase);

    BaseInfo *typeQBase = new BaseInfo();
    typeQBase->baseType = TYPE_QUALIFIERS;
    TypeExpression typeArg;
    typeArg.levelStack.push_back(typeQBase);

    ParameterInfo *vaStartParam = new ParameterInfo();
    ParameterInfo *vaEndParam = new ParameterInfo();

    vaStartParam->paramsType.push_back(vaListArg);
    vaStartParam->paramsType.push_back(intArg);

    vaEndParam->paramsType.push_back(vaListArg);

    vaStartParam->isVariadic = false;
    vaEndParam->isVariadic = false;

    va_startType.levelStack.push_back(voidBase);
    va_startType.levelStack.push_back(vaStartParam);

    va_endType.levelStack.push_back(voidBase);
    va_endType.levelStack.push_back(vaEndParam);

    // Add these to the symbol table
    Function *va_startFunc = new Function();
    va_startFunc->symbolName = "va_start";
    va_startFunc->type = va_startType;
    va_startFunc->isDefined = true;
    va_startFunc->location = std::make_pair(-1, -1);
    va_startFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    va_startFunc->isDefined = true;

    Function *va_endFunc = new Function();
    va_endFunc->symbolName = "va_end";
    va_endFunc->type = va_endType;
    va_endFunc->isDefined = true;
    va_endFunc->location = std::make_pair(-1, -1);
    va_endFunc->symbolType = SYMBOL_TYPE::FUNCTION;

    // Add these to the symbol table
    int insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "va_start", va_startFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "va_end", va_endFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }

    // Also adding va_arg or type - int (va_list, type_qualifier)
    TypeExpression va_argType;

    // BaseInfo *typeBase = new BaseInfo();
    // typeBase->baseType = TYPE_QUALIFIERS;
    ParameterInfo *vaArgParam = new ParameterInfo();
    vaArgParam->paramsType.push_back(vaListArg); // first arg - va_list
    vaArgParam->paramsType.push_back(typeArg);   // second arg - type_qualifier
    vaArgParam->isVariadic = false;

    va_argType.levelStack.push_back(intBase);    // return type
    va_argType.levelStack.push_back(vaArgParam); // arg type

    // Add these to the symbol table
    Function *va_argFunc = new Function();
    va_argFunc->symbolName = "va_arg";
    va_argFunc->type = va_argType;
    va_argFunc->isDefined = true;
    va_argFunc->location = std::make_pair(-1, -1);
    va_argFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    va_argFunc->isDefined = true;
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "va_arg", va_argFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }
    // Also adding va_copy or type - void (va_list, va_list)
    TypeExpression va_copyType;
    BaseInfo *voidBase1 = new BaseInfo();
    voidBase1->baseType = TYPE_VOID;
    ParameterInfo *vaCopyParam = new ParameterInfo();
    vaCopyParam->paramsType.push_back(vaListArg); // first arg - va_list
    vaCopyParam->paramsType.push_back(vaListArg); // second arg - va_list
    vaCopyParam->isVariadic = false;
    va_copyType.levelStack.push_back(voidBase1);   // return type
    va_copyType.levelStack.push_back(vaCopyParam); // arg type
    // Add these to the symbol table
    Function *va_copyFunc = new Function();
    va_copyFunc->symbolName = "va_copy";
    va_copyFunc->type = va_copyType;
    va_copyFunc->isDefined = true;
    va_copyFunc->location = std::make_pair(-1, -1);
    va_copyFunc->symbolType = SYMBOL_TYPE::FUNCTION;
    va_copyFunc->isDefined = true;
    insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, "va_copy", va_copyFunc);
    if (insertCheck == INSERT_FAILURE)
    {
        return insertCheck;
    }

    // aptLOG("Added 🤫 'va_start', 'va_end', 'va_arg' and 'va_copy' functions to symbol table due to lib <stdarg.h>");

    // aptLOG("Type of va_start : " + toString(va_startType));
    // aptLOG("Type of va_end : " + toString(va_endType));
    // aptLOG("Type of va_arg : " + toString(va_argType));
    // aptLOG("Type of va_copy : " + toString(va_copyType));

    return INSERT_SUCCESS;
}

//=====================[ Main Semantic Pass Handler ]=========================================================================================

void semanticPass(ASTNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    std::string whichProduction = getProduction(node);

    std::string P1 = "translation_unit";

    if (whichProduction != P1)
    {
        return;
    }

    // We will openScope here
    int globalScope = SYM_TABLE.enterScope();                          // GlobalScope
    std::string scopeName = GLOBAL_SCOPE;                              // Global Scope Name
    SYM_TABLE.setScopeName(scopeName);                                 // Set the name of the scope
    aptLOG("Scope (Global) : S" + std::to_string(globalScope) + " ⤵️"); // 🌴 Adding syn_attr

    // Auto Detected Code addition of printf & scanf Definitions in SYM_TABLE 🖨️ 🖨️
    if(stdio_lib){
        int insertCheck = add_printf_scanf(node);
        if (insertCheck == INSERT_FAILURE)
        {
            semanticError("Failed to insert printf and scanf in symbol table");
            FAIL_H; // no need to return
        }
        else
        {
            aptLOG("Added 🤫 printf and scanf to symbol table 🖨️ due to lib <stdio.h>");
        }


        // Add our print and scan functions
        insertCheck = add_our_print_scan(node);
        if (insertCheck == INSERT_FAILURE)
        {
            semanticError("Failed to insert our print and scan in symbol table");
            FAIL_H; // no need to return
        }
        else
        {
            aptLOG("Added 🚀OUR🚀 print and scan to symbol table 🖨️ due to lib <stdio.h>");
        }
    }

    // Hard Code addition of va_start & va_end Definitions in SYM_TABLE
    if(stdarg_lib){
        int insertCheck = addVaradicLib(node);
        if (insertCheck == INSERT_FAILURE)
        {
            semanticError("Failed to insert va_start and va_end in symbol table");
            FAIL_H; // no need to return
        }
        else
        {
            aptLOG("Added 🤫 'va_start', 'va_end', 'va_arg' and 'va_copy' functions to symbol table due to lib <stdarg.h>");
        }
    }

    translation_unit_H(node->children[0]);

    // SCOPE EXIT
    globalScope = SYM_TABLE.exitScope();                                    // GlobalScope
    aptLOG("Scope (Global) S" + std::to_string(globalScope) + " Exited ↙️"); // 🌴 Adding syn_attr
}
// SYM_TABLE - Will be Globaly available
// IR_CODE - Will be Globaly available (TAC)

//====================[ Starting Handlers ]=========================================================================================

int translation_unit_H(ASTNode *node)
{
    ENTRY_H

    lastFuncCalled = "translation_unit_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "external_declaration";
    std::string P2 = "translation_unit external_declaration";

    if (whichProduction == P1)
    {
        // Call the external_declaration handler
        external_declaration_H(node->children[0]);
    }
    else if (whichProduction == P2)
    {
        // Call the translation_unit handler
        translation_unit_H(node->children[0]);
        // Call the external_declaration handler
        external_declaration_H(node->children[1]);
    }
    else
    {
        // Wrong Production
    }

    EXIT_H
    return OKAY;
}

int external_declaration_H(ASTNode *node)
{
    ENTRY_H

    lastFuncCalled = "external_declaration_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "function_definition";
    std::string P2 = "declaration";

    if (whichProduction == P1)
    {
        // Call the function_definition handler
        function_definition_H(node->children[0]);
    }
    else if (whichProduction == P2)
    {
        // Call the declaration handler
        declaration_H(node->children[0]);
    }
    else
    {
        // Wrong Production
    }

    EXIT_H
    return OKAY;
}

//====================[ Function Definition Handlers ]=========================================================================================

int function_definition_H(ASTNode *node)
{
    ENTRY_H;
    // This will be used to fetch the function name
    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers declarator compound_statement";

    if (whichProduction == P1)
    {
        // TO RESET GOTOLABEL maps
        labelList.clear();
        labelMap.clear();

        // Data to be fetched from declaration_specifiers
        std::vector<std::string> valueVector;
        // Call the declaration_specifiers handler
        declaration_specifiers_H(node->children[0], valueVector);

        // Process the declaration_specifiers
        TypeExpression inh_type;
        StorageClass storageClass = StorageClass::NONE;
        int check = ProcessDecSpecifiers(valueVector, inh_type, storageClass);
        if (check != OKAY)
        {
            if (check == WARNING)
            {
                semanticWarning("Declaration Specifier - " + semanticMessage);
            }
            else
            {
                semanticError("Invalid Function's return type - " + toString(valueVector));
                FAIL_H;
                return FAIL;
            }
        }

        if (storageClass != StorageClass::NONE)
        {
            semanticError("Storage Class not allowed in function definition");
            FAIL_H;
            return FAIL;
        }

        TypeExpression returnTypeExpr = inh_type;

        // Data to be fetched from declarator
        std::string varName;
        TypeExpression type1; // This type will contain information about the function along with names of parameters

        // Call the declarator handler
        declarator_H(node->children[1], inh_type, varName, type1);

        // Check if type1 is a function type
        Type type = whatIsType(type1);
        if (type != Type::FUNCTION)
        {
            semanticError("Function definition must have a function type");
            FAIL_H;
            return FAIL;
        }

        TypeExpression funcType = type1;

        LevelInfo *levelInfo = funcType.levelStack[funcType.levelStack.size() - 1];
        ParameterInfo *paramInfo = dynamic_cast<ParameterInfo *>(levelInfo);

        // Check if funtion definition is not abstract
        bool isAbstract = paramInfo->isAbstract;

        if (isAbstract)
        {
            semanticError("Abstract function definition not allowed");
            FAIL_H;
            return FAIL;
        }

        // Check if the function is already defined
        GenericSymbol *sym = nullptr;
        aptHERE;
        int lookupCheck = SYM_TABLE.lookup(varName, sym);
        if (lookupCheck == LOOKUP_SUCCESS)
        {
            // Check if lookedUp symbol is a function
            if (sym->symbolType != SYMBOL_TYPE::FUNCTION)
            {
                semanticError("Function Definition \"" + varName + "\" collision with variable");
                FAIL_H;
                return FAIL;
            }
            // Function name already exists // check if declared or not
            Function *func = dynamic_cast<Function *>(sym);
            TypeExpression newFuncType = func->type;
            bool isDefined = func->isDefined;

            aptLOG("newFuncType : " + toString(newFuncType));
            aptLOG("type1 : " + toString(type1));
            bool sameSignature = (ourEquivalent(newFuncType, type1) == EQUIVALENT);

            if (sameSignature)
            {
                // Function is already defined
                if (isDefined)
                {
                    semanticError("Redefinition of function \"" + varName + "\"");
                    FAIL_H;
                    return FAIL;
                }
                else
                {
                    // Function is declared
                    func->isDefined = true;
                    aptLOG("Function ☞ \"" + varName + "\"" + " defined"); // 🌴 Adding syn_attr
                }
            }
            else
            {
                semanticError("Function Definition \"" + varName + "\" signature mismatch with previous declaration");
            }
        }
        else
        {
            // Create a Symbol Table Entry
            Function *func = new Function();
            func->symbolName = varName;
            func->type = type1;     // 🐛🐛🐛🐛🐛🐛 TO CHECK IF VALID FUNCTION TYPE [make a utility]
            func->isDefined = true; // To be set to true when the function is defined

            // Add the symbol to the symbol table
            int insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, varName, func);
            if (insertCheck == INSERT_FAILURE)
            {
                // Should not happen since we already checked for presence
                compilerError("Function Insertion failed but lookup was success");
                FAIL_H;
                return FAIL;
            }
            else
            {
                aptLOG("Function dec+def added ☞ \"" + varName + "\""); // 🌴 Adding syn_attr
            }
        }

        // 🔖IR Cdoe
        int noOfArgs = paramInfo->paramsType.size();
        std::string argCount = std::to_string(noOfArgs);
        IR_CODE.addTAC(node, varName, FUNCTION_ENTRY, argCount, NO_ARG);

        // Now we have list of all the prameters & their names
        if (!isAbstract)
        {
            // OKAY
            TypeExpression returnType = funcType;
            int check = popALevel(returnType);
            if (check != POP_SUCCESS)
            {
                compilerError("Function Definition - popALevel failed");
                BUG_H;
                return BUG;
            }

            // Now we have parameter list
            std::vector<TypeExpression> paramVector = paramInfo->paramsType;
            std::vector<std::string> paramNames = paramInfo->paramsName;

            // OPEN a NEW SCOPE
            int scopeNo = SYM_TABLE.earlyEntry(); //  [☀️ EarlyScope Entry]

            std::string scopeName = varName;                   // Function Scope Name
            SYM_TABLE.setScopeName(scopeName);                 // Set the name of the scope
            aptLOG("Early Scope Entry : " + scopeName + " ☀️"); // 🌴 Adding syn_attr

            // Add the parameters to the symbol table

            int k = paramVector.size();
            for (int i = 0; i < k; i++)
            {
                // Create a Symbol
                Variable *var = new Variable();
                var->symbolName = (!isAbstract) ? paramNames[i] : NO_ARG_NAME;
                var->type = paramVector[i];
                var->storageClass = StorageClass::NONE;

                // Add the symbol to the symbol table
                int insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::VARIABLE, paramNames[i], var);

                // Need a allocate Code
                int size = width(paramVector[i]);
                std::string isF = isFloatingPoint(paramVector[i]) ? "YES" : "NO";
                std::string suffix = "$" + std::to_string(SYM_TABLE.scopeNo);
                IR_CODE.addTAC(node, paramNames[i] + suffix, ALLOCATE, std::to_string(size), isF);

                if (insertCheck == INSERT_FAILURE)
                {
                    semanticError("Parameter \"" + paramNames[i] + "\" already declared in function scope");
                }
                else
                {
                    // Okay
                    aptLOG("Parameter added ☞ \"" + paramNames[i] + "\""); // 🌴 Adding syn_attr
                }
            }
        }

        // Call the compound_statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        std::vector<int> S1_breakList;
        std::vector<int> S1_continueList;
        std::map<std::string, int> caseMap;
        compound_statement_H(node->children[2], S1_nextList, S1_breakList, S1_continueList, caseMap);

        // Backpatch the next list
        int aLabel = IR_CODE.nextIndex();
        IR_CODE.backpatch(node, S1_nextList, aLabel);

        // TO BACKPATCH GOTO LABELS
        for (auto &pair : labelList)
        {
            std::string label = pair.first;
            std::vector<int> list = pair.second;
            if (labelMap.find(label) != labelMap.end())
            {
                int labelIndex = labelMap[label];
                IR_CODE.backpatch(node, list, labelIndex);
            }
            else
            {
                semanticError("Use of undeclared label \"" + label + "\"");
            }
        }

        // The last Code was supposed to be a return statement
        int returnIndex = IR_CODE.nextIndex();
        TAC_Quadruple code = IR_CODE.code[returnIndex - 1];

        bool returnAbsent = (code.op != RETURN_FUNCTION);

        // returnAbsent = false; // [TURNED ON] [ERROR SUPPRESSION]

        if (returnAbsent)
        {
            aptLOG("Return Statement not found in function \"" + varName + "\""); // 🌴 Adding syn_attr
            Type whichReturnType = whatIsType(returnTypeExpr);
            if (whichReturnType == Type::VARIABLE)
            {
                aptLOG("Return Type is Variable"); // 🌴 Adding syn_attr
                BaseInfo *base = (BaseInfo *)returnTypeExpr.levelStack[0];
                std::string ret = base->baseType;
                if (ret != TYPE_VOID)
                {

                    // Add a return statement
                    IR_CODE.addTAC(node, NO_ARG, RETURN_FUNCTION, NO_ARG, NO_ARG);

                    // semanticWarning("Function \'" + varName + "\'s return type is not void but no return statement found");
                    // FAIL_H;
                    // return FAIL;
                }
            }
            else
            {

                // Add a return statement
                IR_CODE.addTAC(node, NO_ARG, RETURN_FUNCTION, NO_ARG, NO_ARG);

                // semanticWarning("Function \'" + varName + "\'s return type is not void but no return statement found");
                // FAIL_H;
                // return FAIL;
            }
        }

        int returnSize = width(returnTypeExpr);

        // Adding Function Exit TAC
        IR_CODE.addTAC(node, varName, FUNCTION_EXIT, std::to_string(returnSize), NO_ARG);

        // Early Entry's Exit
        int exitedScope = SYM_TABLE.earlyExit(); //  [☀️ EarlyScope Entry] [IT's POSSIBLE that the early scope entry was never used in here]
        if (exitedScope == NO_EXIT)
        {
            int currScope = SYM_TABLE.scopeNo;
            aptLOG("Already 😅 Exited | Now in S" + std::to_string(currScope) + " ☀️"); // 🌴 Adding syn_attr
        }
        else
        {
            aptLOG("Exit due to EarlyEntry : S" + std::to_string(exitedScope) + " ☀️"); // 🌴 Adding syn_attr
        }
    }
    else
    {
        compilerError("Function Definition encountered wrong production");
        BUG_H;
        return BUG;
    }

    EXIT_H;
    return OKAY;
}
