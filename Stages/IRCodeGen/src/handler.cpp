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
    if (handlerLog)
    {
        handlerLog->close();
        delete handlerLog;
        handlerLog = nullptr;
    }
}

//====================[ Globally Accessible Variables ]=========================================================================================
SymbolTable SYM_TABLE; // Global Symbol Table
TAC CODE_BASE;         // Global TAC Code Base

//====================[ Annotated Parse Tree ]=========================================================================================

int ANNOTATE; // 0 - OFF | 1 - ON [extern declared in header.h]


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
        str += pair.first + " : " + toString(pair.second);
        str += " | ";
    }
    str += " }";
    return str;
}

std::string toString(std::vector<PointerInfo> ptrInfo)
{
    std::string str = "[ ";
    for (size_t i = 0; i < ptrInfo.size(); ++i)
    {
        PointerInfo unit = ptrInfo[i];
        str += " *";
        for (size_t j = 0; j < unit.typeQualifiers.size(); ++j)
        {
            str += toString(unit.typeQualifiers[j]) + " ";
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

//====================[ Helper Functions ]=========================================================================================

std::string getProduction(ASTNode *node)
{
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
//TODO : do error handling
int ProcessDecSpecifiers(std::vector<std::string> &valueVector, BaseInfo *&base, StorageClass &storageClass)
{
    // 1. Initialize the base and storageClass
    int check = 0;

    if (base == nullptr)
    {
        *handlerLog << "BaseInfo was NULL" << std::endl;
        base = new BaseInfo();
    }

    for (size_t i = 0; i < valueVector.size(); ++i)
    {
        std::string value = valueVector[i];
        // The TypeQualifier will be added to the base->typeQualifiers
        if (value == "const")
        {
            TypeQualifier typeQualifier = TypeQualifier::CONST;
            base->typeQualifiers.push_back(typeQualifier);
        }
        else if (value == "volatile")
        {
            TypeQualifier typeQualifier = TypeQualifier::VOLATILE;
            base->typeQualifiers.push_back(typeQualifier);
        }
        else if (value == "restrict")
        {
            TypeQualifier typeQualifier = TypeQualifier::RESTRICT;
            base->typeQualifiers.push_back(typeQualifier);
        }

        // The StorageClass will be added to the storageClass
        else if (value == "auto")
        {
            storageClass = StorageClass::AUTO;
        }
        else if (value == "static")
        {
            storageClass = StorageClass::STATIC;
        }
        else if (value == "extern")
        {
            storageClass = StorageClass::EXTERN;
        }

        // The TypeSpecifier will wil loaded as it is
        else
        {
            // Assuming rest is typeSpecifier
            base->baseType = value;
        }
    }

    return 0;
}

//=====================[ Main Semantic Pass Handler ]=========================================================================================

void semanticPass(ASTNode *node, std::string filename)
{
    lastFuncCalled = "semanticPass";
    openHandlerLog(filename);
    *handlerLog << "semanticPass" << std::endl;
    *handlerLog << "--==[ Semantic Pass ]==--" << std::endl;
    translation_unit_H(node);

    closeHandlerLog();
}
// SYM_TABLE - Will be Globaly available
// CODE_BASE - Will be Globaly available (TAC)

//====================[ Starting Handlers ]=========================================================================================

void translation_unit_H(ASTNode *node)
{
    *handlerLog << "translation_unit_H" << std::endl;
    lastFuncCalled = "translation_unit_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "external_declaration";
    std::string P2 = "translation_unit external_declaration";

    // CERR << "Production: " << whichProduction << std::endl;

    if (whichProduction == P1)
    {
        // HERE;
        // Call the external_declaration handler
        external_declaration_H(node->children[0]);
    }
    else if (whichProduction == P2)
    {
        // HERE;
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
    *handlerLog << "external_declaration_H" << std::endl;
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
    *handlerLog << "function_definition_H" << std::endl;
    lastFuncCalled = "function_definition_H";
    // This will be used to fetch the function name
    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers declarator compound_statement";

    if(whichProduction == P1){
        // Data to be fetched from declaration_specifiers
        std::vector<std::string> valueVector;
        BaseInfo *base = nullptr;
        StorageClass storageClass = StorageClass::NONE;
        // Call the declaration_specifiers handler
        declaration_specifiers_H(node->children[0], valueVector);

        // Process the declaration_specifiers
        int check = ProcessDecSpecifiers(valueVector, base, storageClass);
        if(check != 0){
            // SEMANTIC ERROR 🚨 : Error in ProcessDecSpecifiers
        }

        if(storageClass != StorageClass::NONE){
            // SEMANTIC ERROR 🚨 : [To Decide]
        }

        // Create a TypeExpression object
        TypeExpression inh_type;
        inh_type.levelStack.push(base);

        // Data to be fetched from declarator
        std::string varName;
        TypeExpression type1; // This type will contain information about the function along with names of parameters

        // Call the declarator handler
        declarator_H(node->children[1], inh_type, varName, type1);

        // Check if type1 is a function type
        Type type = whatIsType(type1);
        if(type != Type::FUNCTION){
            // SEMANTIC ERROR 🚨 : Function Definition is not a function type
        }

        // Check if the function is already defined
        GenericSymbol *sym = nullptr;
        int lookupCheck = SYM_TABLE.lookup(varName, sym);
        if(lookupCheck == LOOKUP_SUCCESS){
            // Function name already exists // check if declared or not
            Function *func = dynamic_cast<Function*>(sym);
            bool isDefined = func->isDefined;
            bool sameSignature = true;

            // Check if the function signature is same
            // To use CheckEquivalence function

            if(sameSignature){
                // Function is already defined
                if(isDefined){
                    // SEMANTIC ERROR 🚨 : Function already defined
                }
                else{
                    // Function is declared
                    func->isDefined = true;
                    A_PTree node->addAttribute("Function ☞ \"" + varName + "\"" + " defined"); // 🌴 Adding syn_attr
                }
            }
            else{
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
            func->type = type1;
            func->isDefined = true; // To be set to true when the function is defined

            // Add the symbol to the symbol table
            int insertCheck = SYM_TABLE.insert(varName, func);
            if(insertCheck == INSERT_FAILURE){
                // SEMANTIC ERROR 🚨 : Function already present in the current scope
            }
            else{
                // Okay
                A_PTree node->addAttribute("Function dec+def added ☞ \"" + varName + "\""); // 🌴 Adding syn_attr
            }
        }

        // Now we have list of all the prameters & their names

        TypeExpression funcType = type1;

        LevelInfo *levelInfo = funcType.levelStack.top();
        ParameterInfo *paramInfo = dynamic_cast<ParameterInfo*>(levelInfo);

        // Check if funtion definition is not abstract
        bool isAbstract = paramInfo->isAbstract;
        if(isAbstract){
            // SEMANTIC ERROR 🚨 : Function is abstract
        }
        else{
            // OKAY
            TypeExpression returnType = funcType;
            int check = popALevel(returnType);
            if(check != POP_SUCCESS){
                *handlerLog << "Error in popALevel" << std::endl;
            }
            
            // Now we have parameter list
            std::vector<TypeExpression> paramVector = paramInfo->paramsType;
            std::vector<std::string> paramNames = paramInfo->paramsName;

            // OPEN a NEW SCOPE
            int scopeNo = SYM_TABLE.enterScope();
            // Add the parameters to the symbol table

            int k = paramVector.size();
            for(int i = 0; i < k; i++){
                // Create a Symbol
                Variable *var = new Variable();
                var->symbolName = (!isAbstract) ? paramNames[i] : NO_ARG_NAME;
                var->type = paramVector[i];
                var->storageClass = StorageClass::NONE;

                // Add the symbol to the symbol table
                int insertCheck = SYM_TABLE.insert(paramNames[i], var);
                if(insertCheck == INSERT_FAILURE){
                    // SEMANTIC ERROR 🚨 : Parameter already present in the current scope
                }     
                else{
                    // Okay
                    A_PTree node->addAttribute("Parameter added ☞ \"" + paramNames[i] + "\""); // 🌴 Adding syn_attr
                }
            }
    }

    // 🔖IR Cdoe
    CODE_BASE.addTAC(NO_ARG, FUNCTION_LABEL, varName, NO_ARG);

    // Call the compound_statement handler
    bool earlyScopeEnter = true; // inh_attr to be passed to compound_statement
    compound_statement_H(node->children[2], earlyScopeEnter);

    // [ToDecide - HOW TO CHECK RETURN TYPE OF FUNCTION]

    // EXIT the SCOPE
    SYM_TABLE.exitScope();
    CODE_BASE.addTAC(NO_ARG,BLANK,NO_ARG,NO_ARG); // To be added

    }
    else{
        // Wrong Production
        *handlerLog << "Wrong Production in function_definition_H" << std::endl;
    }

    return;
}
