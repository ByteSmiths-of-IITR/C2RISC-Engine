#include "header.h"
#include "utility.h"

//=====================[ Error Handling ]=========================================================================================

std::ofstream *handlerLog = nullptr;

void openHandlerLog(const std::string &filename)
{
    handlerLog = new std::ofstream(filename);
    if (!handlerLog->is_open())
    {
        delete handlerLog;
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        handlerLog = nullptr;
    }
}

void closeHandlerLog()
{
    if (handlerLog->is_open())
    {
        handlerLog->close();
        delete handlerLog;
        handlerLog = nullptr;
    }
    return;
}

std::vector<std::string> semanticLOG; // [extern declared in header.h]

//====================[ Globally Accessible Variables ]=========================================================================================
SymbolTable SYM_TABLE; // Global Symbol Table
TAC CODE_BASE;         // Global TAC Code Base

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

std::string toString(std::vector<PointerInfo*> ptrInfo)
{
    std::string str = "[ ";
    for (size_t i = 0; i < ptrInfo.size(); ++i)
    {
        PointerInfo* unit = ptrInfo[i];
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
    // TODO : Add error handling
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
// TODO : do error handling
int ProcessDecSpecifiers(std::vector<std::string> &valueVector, TypeExpression &type, StorageClass &storageClass)
{
    // 1. Initialize the base and storageClass
    int check = OKAY;

    // Check if the valueVector is empty
    if (valueVector.empty())
    {
        // return LOW_ERROR; // ERROR
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
        // SEMANTIC ERROR 🚨 : Multiple storage classes
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
        // SEMANTIC ERROR 🚨 : Duplicate Type Qualifier
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

    if (!allAreInbuiltType)
    {
        // Are are not Primtive
        // Then there must be only one typedef defined type
        if (typeSpecifierVector.size() != 1)
        {
            // SEMANTIC ERROR 🚨 : Multiple type specifiers
            check = LOW_ERROR; // ERROR
        }
        else
        {
            std::string firstPart = typeSpecifierVector[0].substr(0, typeSpecifierVector[0].find(" "));
            if (firstPart == TYPE_STRUCT || firstPart == TYPE_UNION || firstPart == TYPE_ENUM)
            {
                // This is a struct or union or enum
                base->baseType = typeSpecifierVector[0];
                resultType.levelStack.push(base);
            }
            else
            {
                // TypeSpecifier must be a TYPE_NAME
                // Check in Symbol Table if present
                std::string typeName = typeSpecifierVector[0];
                GenericSymbol *sym = nullptr;
                int lookupCheck = SYM_TABLE.lookup(typeName, sym);
                if (lookupCheck == LOOKUP_FAILURE)
                {
                    // SEMANTIC ERROR 🚨 : Type name not found
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
                        // SEMANTIC ERROR 🚨 : Not a typedef
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
            // SEMANTIC ERROR 🚨 : Invalid TypeSpecifier's Combination
            check = LOW_ERROR; // ERROR
        }
        else
        {
            base->baseType = finalBase;
            resultType.levelStack.push(base);
        }
    }

    type = resultType;

    std::string output = "|" + toString(storageClass) + "|" + toString(type) + "| CHECK: " + toString(check) + "";
    return check;
}

//=====================[ Main Semantic Pass Handler ]=========================================================================================

void semanticPass(ASTNode *node, std::string filename)
{
    openHandlerLog(filename); // 😵‍💫🤬 Critical CODE [MUST be AT START]
    if (node == nullptr)
    {
        return;
    }

    std::string whichProduction = getProduction(node);

    std::string P1 = "translation_unit";

    if (whichProduction != P1)
    {
        // SEMANTIC ERROR 🚨 : Invalid Production
        return;
    }

    // We will openScope here
    int globalScope = SYM_TABLE.enterScope();                                              // GlobalScope
    std::string scopeName = GLOBAL_SCOPE;                                                  // Global Scope Name
    SYM_TABLE.setScopeName(scopeName);                                                     // Set the name of the scope
    A_PTree node->addAttribute("Scope (Global) : S" + std::to_string(globalScope) + " ⤵️"); // 🌴 Adding syn_attr

    lastFuncCalled = "semanticPass";

    translation_unit_H(node->children[0]);

    // SCOPE EXIT
    globalScope = SYM_TABLE.exitScope();                                                        // GlobalScope
    A_PTree node->addAttribute("Scope (Global) S" + std::to_string(globalScope) + " Exited ↙️"); // 🌴 Adding syn_attr

    closeHandlerLog(); // 😵‍💫🤬 Critical CODE [MUST be at BOTTOM]
}
// SYM_TABLE - Will be Globaly available
// CODE_BASE - Will be Globaly available (TAC)

//====================[ Starting Handlers ]=========================================================================================

void translation_unit_H(ASTNode *node)
{
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
    return;
}

void external_declaration_H(ASTNode *node)
{
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
    return;
}

//====================[ Function Definition Handlers ]=========================================================================================

void function_definition_H(ASTNode *node)
{
    lastFuncCalled = "function_definition_H";
    // This will be used to fetch the function name
    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers declarator compound_statement";

    if (whichProduction == P1)
    {
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
            // SEMANTIC ERROR 🚨 : Error in ProcessDecSpecifiers
        }

        if (storageClass != StorageClass::NONE)
        {
            // SEMANTIC ERROR 🚨 : Functions don't have storage class
        }

        // Data to be fetched from declarator
        std::string varName;
        TypeExpression type1; // This type will contain information about the function along with names of parameters

        // Call the declarator handler
        declarator_H(node->children[1], inh_type, varName, type1);

        // Check if type1 is a function type
        Type type = whatIsType(type1);
        if (type != Type::FUNCTION)
        {
            // SEMANTIC ERROR 🚨 : Function Definition is not a function type
        }

        // Check if the function is already defined
        GenericSymbol *sym = nullptr;
        int lookupCheck = SYM_TABLE.lookup(varName, sym);
        if (lookupCheck == LOOKUP_SUCCESS)
        {
            // Function name already exists // check if declared or not
            Function *func = dynamic_cast<Function *>(sym);
            bool isDefined = func->isDefined;
            bool sameSignature = true;

            // Check if the function signature is same
            // To use CheckEquivalence function

            if (sameSignature)
            {
                // Function is already defined
                if (isDefined)
                {
                    // SEMANTIC ERROR 🚨 : Function already defined
                }
                else
                {
                    // Function is declared
                    func->isDefined = true;
                    A_PTree node->addAttribute("Function ☞ \"" + varName + "\"" + " defined"); // 🌴 Adding syn_attr
                }
            }
            else
            {
                // SEMANTIC ERROR 🚨 : Function signature mismatch
                // WE are not supporting overloading of functions
            }
        }
        else
        {
            // Function neither defined not declared

            // Create a Symbol Table Entry
            Function *func = new Function();
            func->symbolName = varName;
            func->type = type1;     // 🐛🐛🐛🐛🐛🐛 TO CHECK IF VALID FUNCTION TYPE [make a utility]
            func->isDefined = true; // To be set to true when the function is defined

            // Add the symbol to the symbol table
            int insertCheck = SYM_TABLE.insert(SYMBOL_TYPE::FUNCTION, varName, func);
            if (insertCheck == INSERT_FAILURE)
            {
                // SEMANTIC ERROR 🚨 : Function already present in the current scope
            }
            else
            {
                // Okay
                A_PTree node->addAttribute("Function dec+def added ☞ \"" + varName + "\""); // 🌴 Adding syn_attr
            }
        }

        // Now we have list of all the prameters & their names

        TypeExpression funcType = type1;

        LevelInfo *levelInfo = funcType.levelStack.top();
        ParameterInfo *paramInfo = dynamic_cast<ParameterInfo *>(levelInfo);

        // Check if funtion definition is not abstract
        bool isAbstract = paramInfo->isAbstract;
        if (isAbstract)
        {
            // SEMANTIC ERROR 🚨 : Function is abstract
        }
        else
        {
            // OKAY
            TypeExpression returnType = funcType;
            int check = popALevel(returnType);
            if (check != POP_SUCCESS)
            {
            }

            // Now we have parameter list
            std::vector<TypeExpression> paramVector = paramInfo->paramsType;
            std::vector<std::string> paramNames = paramInfo->paramsName;

            // OPEN a NEW SCOPE
            int scopeNo = SYM_TABLE.earlyEntry(); //  [☀️ EarlyScope Entry]

            std::string scopeName = varName + " S" + std::to_string(scopeNo);      // Function Scope Name
            SYM_TABLE.setScopeName(scopeName);                                     // Set the name of the scope
            A_PTree node->addAttribute("Early Scope Entry : " + scopeName + " ☀️"); // 🌴 Adding syn_attr

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
                if (insertCheck == INSERT_FAILURE)
                {
                    // SEMANTIC ERROR 🚨 : Parameter already present in the current scope
                }
                else
                {
                    // Okay
                    A_PTree node->addAttribute("Parameter added ☞ \"" + paramNames[i] + "\""); // 🌴 Adding syn_attr
                }
            }
        }

        // 🔖IR Cdoe

        CODE_BASE.addTAC(node, varName, FUNCTION_LABEL, NO_ARG, NO_ARG);

        // Call the compound_statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        compound_statement_H(node->children[2], S1_nextList);

        // Backpatch the next list
        int aLabel = CODE_BASE.nextIndex();
        CODE_BASE.backpatch(node, S1_nextList, aLabel);

        // [ToDecide - HOW TO CHECK RETURN TYPE OF FUNCTION]

        // SYM_TABLE.exitScope(); // [☀️ EarlyScope Entry's EXIT]
        // [Will be Handled by Compound Statments this is due to - ☀️ EarlyScope Entry]

        // CODE_BASE.addTAC(node, NO_ARG, BLANK, NO_ARG, NO_ARG); // To be added

        // Early Entry's Exit
        int exitedScope = SYM_TABLE.earlyExit();                                                       //  [☀️ EarlyScope Entry] [IT's POSSIBLE that the early scope entry was never used in here]
        if(exitedScope==NO_EXIT){
            int currScope = SYM_TABLE.scopeNo;
            A_PTree node->addAttribute("Already 😅 Exited | Now in S" + std::to_string(currScope) + " ☀️"); // 🌴 Adding syn_attr
        }else{
            A_PTree node->addAttribute("Exit due to EarlyEntry : S" + std::to_string(exitedScope) + " ☀️"); // 🌴 Adding syn_attr
        }
    }
    else
    {
        // Wrong Production
    }

    return;
}
