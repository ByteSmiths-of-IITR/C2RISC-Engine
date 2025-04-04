#include "header.h"
#include "utility.h"

std::string NO_ARG_NAME = "NO_ARG_NAME";

//====================[ Declaration Handlers ]=========================================================================================

// ----- Main Declaration Handler
void declaration_H(ASTNode *node)
{


    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers SEMI_COLON";
    std::string P2 = "declaration_specifiers init_declarator_list SEMI_COLON";

    if (whichProduction != P1 && whichProduction != P2)
    {
        // Wrong Production
        return;
    }

    // Data on declaration - NO SYN or INH data of declaration [MIGHT be needed further down the line]

    // Code Common to P1 & P2
    //  1. Call the declaration_specifiers_H function to fetch syn_attr ⬆️ (P1 + P2)
    std::vector<std::string> valueVector; // syn_attr of declaration_specifiers 🟡
    declaration_specifiers_H(node->children[0], valueVector);

    // 2. Prepare data to be sent down to next child
    // 2.1 Create a TypeExpression object
    TypeExpression inh_type;
    StorageClass inh_storageClass = StorageClass::NONE;
    int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
    if (check != OKAY)
    {
        // SEMANTIC ERROR 🚨 : Error in ProcessDecSpecifiers
    }

    if (whichProduction == P1)
    {
        // NOTHING to send
    }
    else if (whichProduction == P2)
    {
        // 3. inh_data ⬇️ | NO syn_data (init_declarator_list)
        init_declarator_list_H(node->children[1], inh_type, inh_storageClass);
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("inh_type = " + toString(inh_type)); // 🌳 Adding inh_attr

    return;
}

void declaration_list_H(ASTNode *node)
{

    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration";
    std::string P2 = "declaration_list declaration";

    if (whichProduction == P1)
    {
        // Call the declaration handler
        declaration_H(node->children[0]);
    }
    else if (whichProduction == P2)
    {
        declaration_list_H(node->children[0]);
        declaration_H(node->children[1]);
    }
    else
    {
        // Wrong Production
    }
    return;
}

// ----- Init Declarator Handler
void init_declarator_list_H(ASTNode *node, TypeExpression inh_type, StorageClass inh_storageClass)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "init_declarator";
    std::string P2 = "init_declarator_list COMMA init_declarator";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type));                 // 🌳 Adding inh_attr
    A_PTree node->addAttribute("inh_storageClass = " + toString(inh_storageClass)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 1. We call the function again to fetch the next value
        init_declarator_H(node->children[0], inh_type, inh_storageClass);
    }
    else if (whichProduction == P2)
    {
        // 1. We call the function again to fetch the next value
        init_declarator_list_H(node->children[0], inh_type, inh_storageClass);

        // 2. We call the function again to fetch the next value
        init_declarator_H(node->children[2], inh_type, inh_storageClass);
    }
    else
    {
        // Wrong Production
    }

    // No SYN data to add in A_PTree

    return;
}

void init_declarator_H(ASTNode *node, TypeExpression inh_type, StorageClass inh_storageClass)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "declarator";
    std::string P2 = "declarator ASSIGN initializer";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type));                 // 🌳 Adding inh_attr
    A_PTree node->addAttribute("inh_storageClass = " + toString(inh_storageClass)); // 🌳 Adding inh_attr

    std::string varName; // to be fetched ⬆️
    TypeExpression type; // to be fetched ⬆️

    // Code Common to (P1, P2)
    if (whichProduction == P1 || whichProduction == P2)
    {
        // 0. Prepare syn_data to recieve

        declarator_H(node->children[0], inh_type, varName, type);
        SYMBOL_TYPE symbolInsertedType = SYMBOL_TYPE::NONE;

        // 1. Create Symbol (Variable or Function or typedef)
        Type whichType = whatIsType(type);
        GenericSymbol *symbol;
        if (inh_storageClass == StorageClass::TYPEDEF)
        {
            // This is a typedef definition
            TypeDefs *typedefDef = new TypeDefs();
            typedefDef->symbolName = varName;
            typedefDef->type = type;
            symbol = typedefDef;
            symbolInsertedType = SYMBOL_TYPE::TYPEDEF;

            // SEMANTIC ERROR 🚨 : SHOULD NOT HAVE INITIALIZER
        }
        else if (whichType == Type::FUNCTION)
        {
            // Function
            Function *func = new Function();
            func->symbolName = varName;
            func->type = type;       // 🐛🐛🐛🐛🐛🐛 TO CHECK IF VALID FUNCTION TYPE [make a utility]
            func->isDefined = false; // To be set to true when the function is defined
            symbolInsertedType = SYMBOL_TYPE::FUNCTION;

            // SEMANTIC ERROR 🚨 : SHOULD NOT HAVE INITIALIZER

            if (inh_storageClass == StorageClass::AUTO)
            {
                // INVALID in NEW C99
            }
            else if (inh_storageClass == StorageClass::STATIC)
            {
                // ⚡️ Too Advance ⚡️
            }
            symbol = func;
        }
        else
        {
            // Variable
            Variable *var = new Variable();
            var->symbolName = varName;
            var->type = type;
            var->storageClass = inh_storageClass;
            symbolInsertedType = SYMBOL_TYPE::VARIABLE;
            // [📴 Offset to be filled]

            symbol = var;
        }

        // 2. Add the symbol to the symbol table
        int check = SYM_TABLE.insert(symbolInsertedType, varName, symbol);
        if (check == INSERT_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Variable already present in the current scope
            semanticLOG.push_back("Error: Variable \"" + varName + "\" already present in the current scope");
        }
        else
        {
            std::string symbolTypeStr = "";
            if (symbolInsertedType == SYMBOL_TYPE::VARIABLE)
            {
                symbolTypeStr = "Variable";
            }
            else if (symbolInsertedType == SYMBOL_TYPE::FUNCTION)
            {
                symbolTypeStr = "Function";
            }
            else if (symbolInsertedType == SYMBOL_TYPE::TYPEDEF)
            {
                symbolTypeStr = "Typedef";
            }
            else
            {
                symbolTypeStr = "Unknown";
            }
            A_PTree node->addAttribute("Symbol added ☞ \"" + varName + "\" as a " + symbolTypeStr); // 🌴 Adding syn_attr
        }
        // Done - NO 🔖IRCode
    }

    if (whichProduction == P2)
    {
        // The inh_type must be INITIALIZABLE
        std::string inh_varName1 = varName;
        TypeExpression inh_type1 = type;

        Type topType = whatIsType(inh_type1);
        if (topType == Type::FUNCTION)
        {
            // SEMANTIC ERROR 🚨 : Function cannot be initialized
            semanticLOG.push_back("Error: Function \"" + inh_varName1 + "\" cannot be initialized");
        }
        else
        {
            initializer_H(node->children[2], inh_type1, inh_varName1);
        }
    }

    else
    {
        // Wrong Production
    }
    return;
}

// ----- TypeSpecifier + TypeQualifier + StorageClass -----
void declaration_specifiers_H(ASTNode *node, std::vector<std::string> &valueVector)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "storage_class_specifier";
    std::string P2 = "storage_class_specifier declaration_specifiers";
    std::string P3 = "type_specifier";
    std::string P4 = "type_specifier declaration_specifiers";
    std::string P5 = "type_qualifier";
    std::string P6 = "type_qualifier declaration_specifiers";

    A_PTree node->addAttribute("inh_valueVector = " + toString(valueVector)); // 🌳 adding inh_attr

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4 && whichProduction != P5 && whichProduction != P6)
    {
        // Wrong Production
        return;
    }

    std::string value; // syn_attr from storage_class_specifier, type_specifier, type_qualifier 🟡
    // valueVector // syn_attr + inh_attr to/fro declaration_specifiers 🟡

    // Code Common to all productions (P1 & P2)
    // 1. We call the function again to fetch "value" from Last Productions
    if (whichProduction == P1 || whichProduction == P2)
    {

        storage_class_specifier_H(node->children[0], value);
        valueVector.push_back(value);
    }
    else if (whichProduction == P3 || whichProduction == P4)
    {

        type_specifier_H(node->children[0], value);
        valueVector.push_back(value);
    }
    else if (whichProduction == P5 || whichProduction == P6)
    {

        type_qualifier_H(node->children[0], value);
        valueVector.push_back(value);
    }

    // Code Common to (P2, P4, P6)
    if (whichProduction == P2 || whichProduction == P4 || whichProduction == P6)
    {
        // Pass is for recursive declaration_specifiers_H
        declaration_specifiers_H(node->children[1], valueVector);
    }

    A_PTree node->addAttribute("syn_valueVector = " + toString(valueVector)); // 🌴 Adding syn_attr
    return;
}

void storage_class_specifier_H(ASTNode *node, std::string &value)
{

        // Has only one Production
    int noOfChild = node->children.size();
    if (noOfChild != 1)
    {
        // Wrong Production
        return;
    }

    value = node->children[0]->value;

    A_PTree node->addAttribute("syn_value = " + value); // 🌴 Adding syn_attr

    return;
}

void type_qualifier_H(ASTNode *node, std::string &value)
{

        // Has only one Production
    int noOfChild = node->children.size();
    if (noOfChild != 1)
    {
        // Wrong Production
        return;
    }
    value = node->children[0]->value;

    A_PTree node->addAttribute("syn_value = " + value); // 🌴 Adding syn_attr
    return;
}

void type_qualifier_list_H(ASTNode *node, std::vector<TypeQualifier> &typeQualifiers)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "type_qualifier";
    std::string P2 = "type_qualifier_list type_qualifier";

    A_PTree node->addAttribute("inh_typeQualifiers = " + toString(typeQualifiers)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 1. We call the function again to fetch the next value
        TypeQualifier typeQualifier;
        std::string typeQualifierStr;
        type_qualifier_H(node->children[0], typeQualifierStr);
        if (typeQualifierStr == "const")
        {
            typeQualifier = TypeQualifier::CONST;
        }
        else if (typeQualifierStr == "volatile")
        {
            typeQualifier = TypeQualifier::VOLATILE;
        }
        else if (typeQualifierStr == "restrict")
        {
            typeQualifier = TypeQualifier::RESTRICT;
        }
        else
        {
            // Wrong type of Type Qualifier
        }

        typeQualifiers.push_back(typeQualifier);
    }
    else if (whichProduction == P2)
    {
        // 1. We call the function again to fetch the next value
        type_qualifier_list_H(node->children[0], typeQualifiers);

        // 2. We call the function again to fetch the next value
        TypeQualifier typeQualifier;
        std::string typeQualifierStr;
        type_qualifier_H(node->children[0], typeQualifierStr);
        if (typeQualifierStr == "const")
        {
            typeQualifier = TypeQualifier::CONST;
        }
        else if (typeQualifierStr == "volatile")
        {
            typeQualifier = TypeQualifier::VOLATILE;
        }
        else if (typeQualifierStr == "restrict")
        {
            typeQualifier = TypeQualifier::RESTRICT;
        }
        else
        {
            // Wrong type of Type Qualifier
        }

        type_qualifier_H(node->children[2], typeQualifierStr);
        typeQualifiers.push_back(typeQualifier);
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_typeQualifiers = " + toString(typeQualifiers)); // 🌴 Adding syn_attr

    return;
}

void type_specifier_H(ASTNode *node, std::string &value)
{

        std::string whichProduction = getProduction(node);
    // P1 - P9 are Terminals
    std::string P10 = "struct_or_union_specifier";
    std::string P11 = "enum_specifier";
    std::string P12 = "TYPE_NAME";

    if (whichProduction != P10 && whichProduction != P11 && whichProduction != P12)
    {
        // Primitive Types
        if (node->children.size() != 1)
        {
            // Wrong Production
            return;
        }
        value = node->children[0]->value;
    }

    // Struct or Union
    else if (whichProduction == P10)
    {
        // 1. Call the function again to fetch the next value
        struct_or_union_specifier_H(node->children[0], value);
    }

    // Enum
    else if (whichProduction == P11)
    {
        // 1. Call the function again to fetch the next value
        enum_specifier_H(node->children[0], value);
    }
    // Type Name
    else if (whichProduction == P12)
    {
        value = node->children[0]->value;
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_typeSpecifier = " + value); // 🌴 Adding syn_attr

    return;
}

void specifier_qualifier_list_H(ASTNode *node, std::vector<std::string> &valueVector)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "type_specifier specifier_qualifier_list";
    std::string P2 = "type_specifier";
    std::string P3 = "type_qualifier specifier_qualifier_list";
    std::string P4 = "type_qualifier";
 
    A_PTree node->addAttribute("inh_valueVector = " + toString(valueVector)); // 🌳 Adding inh_attr

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4)
    {
        // Wrong Production
        return;
    }

    // Code Common to all
    std::string value;                          // syn_attr from type_specifier or type_qualifier 🟡
    type_specifier_H(node->children[0], value); // syn_attr from type_specifier or type_qualifier

    if (whichProduction == P1 || whichProduction == P3)
    {
        // 1. We call the function again to fetch the next value
        specifier_qualifier_list_H(node->children[1], valueVector);
    }

    valueVector.push_back(value); // syn_attr from type_specifier or type_qualifier

    A_PTree node->addAttribute("syn_value = " + toString(valueVector)); // 🌴 Adding syn_attr

    return;
}

// ----- STURCT & UNION -----
void struct_or_union_specifier_H(ASTNode *node, std::string &value)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY";
    std::string P2 = "struct_or_union LCURLY struct_declaration_list RCURLY";
    std::string P3 = "struct_or_union IDENTIFIER";

    A_PTree node->addAttribute("inh_value = " + value); // 🌳 Adding inh_attr
 
    std::string recordStr = (node->children.size() > 0) ? node->children[0]->value : "";

    // Code Commong to P1 & P2
    if (whichProduction == P1 || whichProduction == P2)
    {

        // 0. Call struct_declaration_list_H to fill the members
        std::map<std::string, TypeExpression> members; // fetch syn_attr ⬆️
        int position = (whichProduction == P1) ? 3 : 2;
        struct_declaration_list_H(node->children[position], members);

        // 1. Create a UserDType Unit
        UserDType *userDType = new UserDType();
        RecordType recordType = (recordStr == "struct") ? RecordType::STRUCT : RecordType::UNION;

        userDType->recordType = recordType;
        userDType->members = members;

        // 2. Add it to the symbol table
        std::string recordID = (whichProduction == P1) ? node->children[1]->value : newRecordName();

        int check = SYM_TABLE.insertRecord(recordID, userDType);
        if (check == INSERT_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Record already present in the current scope
        }
        A_PTree node->addAttribute("\"" + recordID + "\" structID/unionID added"); // 🌴 Adding syn_attr

        // 3. Pass a String up
        std::string scope = std::to_string(SYM_TABLE.scopeNo);
        std::string typeSpecifier = recordStr + " " + recordID + " S" + scope;

        value = typeSpecifier; // send syn_attr ⬆️
    }
    else if (whichProduction == P3)
    {
        // 1. Check if UserDType is there in symbol table
        std::string recordID = node->children[1]->value;
        GenericSymbol *symbol;
        int check = SYM_TABLE.lookupRecord(recordID, symbol);
        if (check == LOOKUP_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Record not found
        }
        else
        {
            RecordType neededType = (recordStr == "struct") ? RecordType::STRUCT : RecordType::UNION;
            RecordType foundType = ((UserDType *)symbol)->recordType;
            if (neededType != foundType)
            {
                // SEMANTIC ERROR 🚨 : Type Mismatch
            }
        }

        // 2. Pass a String up
        std::string scope = std::to_string(symbol->scopeNo);
        std::string typeSpecifier = recordStr + " " + recordID + " S" + scope;

        value = typeSpecifier; // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_record = " + value); // 🌴 Adding syn_attr

    return;
}

// struct_or_union_H is not needed

void struct_declaration_list_H(ASTNode *node, std::map<std::string, TypeExpression> &members)
{

    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_declaration";
    std::string P2 = "struct_declaration_list struct_declaration";

    A_PTree node->addAttribute("inh_members = " + toString(members)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        std::map<std::string, TypeExpression> members1;
        // 1. Last Production will just exactly pass syn_attr(members) ⬆️
        struct_declaration_H(node->children[0], members1);

        // 2. Add the members to the map
        members = members1; // Since Last Production
    }
    else if (whichProduction == P2)
    {
        // 1. Call the function again to fetch the next value
        std::map<std::string, TypeExpression> members1;
        struct_declaration_list_H(node->children[0], members1);

        // 2. Call the function again to fetch the next value
        std::map<std::string, TypeExpression> members2;
        struct_declaration_H(node->children[1], members2);

        // 3. Add the members to the map
        // Copy all from members2 to members1
        for (auto &unit : members2)
        {
            if (members1.count(unit.first))
            {
                // SEMANTIC ERROR 🚨 : Member already present
            }
            members1[unit.first] = unit.second;
        }
        // 4. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_members = " + toString(members)); // 🌴 Adding syn_attr

    return;
}

void struct_declaration_H(ASTNode *node, std::map<std::string, TypeExpression> &members)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "specifier_qualifier_list struct_declarator_list SEMI_COLON";

    A_PTree node->addAttribute("inh_members = " + toString(members)); // 🌳 Adding inh_attr

    if (whichProduction != P1)
    {
        // Wrong Production
        return;
    }
    std::vector<std::string> valueVector;
    // 0. Call the function again to fetch the next value
    specifier_qualifier_list_H(node->children[0], valueVector);

    // 1. Create a TypeExpression object
    TypeExpression inh_type;
    StorageClass inh_storageClass = StorageClass::NONE; // NOT ALLOWED ❌ [Will be syntax checked]
    int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
    if (check != OKAY)
    {
        // SEMANTIC ERROR 🚨 : Invalid TypeSpecifier
    }

    // Pass the inh_data ⬇️ & fetch the syn_attr(members) ⬆️
    std::map<std::string, TypeExpression> syn_members;
    struct_declarator_list_H(node->children[1], inh_type, syn_members);

    // Pass the members up
    members = syn_members; // send syn_attr ⬆️

    A_PTree node->addAttribute("syn_members = " + toString(members)); // 🌴 Adding syn_attr

    return;
}

void struct_declarator_list_H(ASTNode *node, TypeExpression inh_type, std::map<std::string, TypeExpression> &members)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "struct_declarator";
    std::string P2 = "struct_declarator_list COMMA struct_declarator";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type));   // 🌳 Adding inh_attr
    A_PTree node->addAttribute("inh_members = " + toString(members)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️

        // 0. Call the child's Handler
        struct_declarator_H(node->children[0], inh_type, varName, type);

        // 1. Last Production for "members" variable
        std::map<std::string, TypeExpression> members1;

        // 2. Check if the varName is already present
        if (members.count(varName))
        {
            // SEMANTIC ERROR 🚨 : Member already present
        }
        members1[varName] = type;
        // 3. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        // 0. First child syn_data + inh_data passed ⬇️
        std::map<std::string, TypeExpression> members1;
        struct_declarator_list_H(node->children[0], inh_type, members1);

        // 1. Second child syn_data to be fetched ⬆️ + inh_data passed ⬇️
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️
        struct_declarator_H(node->children[2], inh_type, varName, type);

        // 2. Check if the varName is already present
        if (members1.count(varName))
        {
            // SEMANTIC ERROR 🚨 : Member already present
        }

        members1[varName] = type; // Add the new member ➕
        // 3. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_members = " + toString(members)); // 🌴 Adding syn_attr

    return;
}

void struct_declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "declarator";
    std::string P2 = "COLON constant_expression declarator";
    std::string P3 = "COLON constant_expression";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the child's Handler
        declarator_H(node->children[0], inh_type, varName1, type1);

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    }
    else if (whichProduction == P2)
    { // ⚡️ Advance Feature ⚡️ - BitFields

        // No Handler to call
        varName = "";
        type = inh_type; // Pass the inh_type as it is
    }
    else if (whichProduction == P3)
    { // ⚡️ Advance Feature ⚡️ - BitFields
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the child's Handler
        declarator_H(node->children[1], inh_type, varName1, type1);

        // [IGNORED] - Constant Expression - BitField Size

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_varName = " + varName);     // 🌴 Adding syn_attr
    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    return;
}

// ----- ENUM ----
void enum_specifier_H(ASTNode *node, std::string &value)
{

    std::string whichProduction = getProduction(node);
    std::string P1 = "ENUM LCURLY enumerator_list RCURLY";
    std::string P2 = "ENUM IDENTIFIER LCURLY enumerator_list RCURLY";
    std::string P3 = "ENUM IDENTIFIER";
 
    A_PTree node->addAttribute("inh_value = " + value); // 🌳 Adding inh_attr

    // Code Common to P1 & P2
    if (whichProduction == P1 || whichProduction == P2)
    {
        // 1. Create a UserDType Entry
        UserDType *userDType = new UserDType();
        userDType->recordType = RecordType::ENUM;
        userDType->members = std::map<std::string, TypeExpression>(); // Empty Map // Enum won't use this

        // We must call the enumerator_list_H function but it's don't need anything from parent,

        // 2. Find Name of Enum - RecordID
        std::string recordID = (whichProduction == P2) ? node->children[1]->value : newRecordName();
        int lastInitValue = 0; // To be passed to enumerator_list_H

        // 3. Call the child's handler
        int index = (whichProduction == P1) ? 2 : 3;
        enumerator_list_H(node->children[index], recordID, lastInitValue);

        // 4. Add it to the symbol table
        int check = SYM_TABLE.insertRecord(recordID, userDType);
        if (check == INSERT_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Record already present in the current scope
        }

        A_PTree node->addAttribute("\"" + recordID + "\" enumID added"); // 🌴 Adding syn_attr
                                                                         // 5. Pass a String up
        std::string scope = std::to_string(SYM_TABLE.scopeNo);
        std::string typeSpecifier = "enum " + recordID + " S" + scope;

        value = typeSpecifier; // send syn_attr ⬆️
    }
    else if (whichProduction == P3)
    {
        // 1. Check if such a ENUM UserDType exists
        std::string recordID = node->children[1]->value;
        GenericSymbol *symbol;
        int check = SYM_TABLE.lookupRecord(recordID, symbol);
        std::string scope = "-101";
        if (check == LOOKUP_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Record not found
            }
        else
        {
            RecordType neededType = RecordType::ENUM;
            RecordType foundType = ((UserDType *)symbol)->recordType;
            if (neededType != foundType)
            {
                // SEMANTIC ERROR 🚨 : Type Mismatch
            }
            scope = std::to_string(symbol->scopeNo);
        }
        ;
        // 2. Pass a String up
        std::string typeSpecifier = "enum " + recordID + " S" + scope;

        value = typeSpecifier; // send syn_attr ⬆️
        ;
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_value = " + value); // 🌴 Adding syn_attr

    return;
}

void enumerator_list_H(ASTNode *node, std::string recordID, int &lastInitValue)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "enumerator";
    std::string P2 = "enumerator_list COMMA enumerator";

    A_PTree node->addAttribute("inh_recordID = " + recordID);                     // 🌳 Adding inh_attr
    A_PTree node->addAttribute("inh_lastInitValue = " + toString(lastInitValue)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // last production effect
        int currInitValue;

        // 0. syn_data to fetch ⬆️
        int explicitInitValue = 0;
        bool isExplicityInit = false;
        std::string varName; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        enumerator_H(node->children[0], varName, explicitInitValue, isExplicityInit);

        if (isExplicityInit)
        {
            currInitValue = explicitInitValue;
        }
        else
        {
            currInitValue = 0;
        }

        // 2. Add the enum constant to the symbol table
        EnumConstant *enumConst = new EnumConstant();
        enumConst->symbolName = varName;
        enumConst->value = currInitValue;

        int check = SYM_TABLE.insert(SYMBOL_TYPE::ENUM_CONSTANT, enumConst->symbolName, enumConst);
        if (check == INSERT_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Enum Constant already present in the current scope
        }

        A_PTree node->addAttribute("EnumConstant added ☞ \"" + varName + " = " + std::to_string(currInitValue) + "\""); // 🌴 Adding syn_attr

        // Send lastInitValue up
        lastInitValue = currInitValue + 1; // Increment the value for next enumerator
    }
    else if (whichProduction == P2)
    {
        // 0. First child syn_data + inh_data passed ⬇️
        int lastInitValue1;
        enumerator_list_H(node->children[0], recordID, lastInitValue1);

        int currInitValue;

        // 0. syn_data to fetch ⬆️
        int explicitInitValue;
        bool isExplicityInit = false;
        std::string varName; // to be fetched ⬆️
        // 1. Call the function again to fetch the next value
        enumerator_H(node->children[2], varName, explicitInitValue, isExplicityInit);

        if (isExplicityInit)
        {
            currInitValue = explicitInitValue;
        }
        else
        {
            currInitValue = lastInitValue1;
        }

        // 2. Add the enum constant to the symbol table
        EnumConstant *enumConst = new EnumConstant();
        enumConst->symbolName = varName;
        enumConst->value = currInitValue;
        int check = SYM_TABLE.insert(SYMBOL_TYPE::ENUM_CONSTANT, enumConst->symbolName, enumConst);
        if (check == INSERT_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Enum Constant already present in the current scope
        }

        A_PTree node->addAttribute("EnumConstant added ☞ \"" + varName + " = " + std::to_string(currInitValue) + "\""); // 🌴 Adding syn_attr

        // Send lastInitValue up
        lastInitValue = currInitValue + 1; // Increment the value for next enumerator
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_lastInitValue = " + toString(lastInitValue)); // 🌴 Adding syn_attr

    return;
}

void enumerator_H(ASTNode *node, std::string &varName, int &explicitInitValue, bool &isExplicityInit)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "IDENTIFIER ASSIGN constant_expression";

    A_PTree node->addAttribute("inh_varName = " + varName);                               // 🌳 Adding inh_attr
    A_PTree node->addAttribute("inh_explicitInitValue = " + toString(explicitInitValue)); // 🌳 Adding inh_attr
    A_PTree node->addAttribute("inh_isExplicityInit = " + toString(isExplicityInit));     // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 0. syn_data to fetch ⬆️
        varName = node->children[0]->value;
        explicitInitValue = 0;
        isExplicityInit = false;
    }
    else if (whichProduction == P2)
    {
        // 0. syn_data to fetch ⬆️
        varName = node->children[0]->value;

        // 1. syn_data to be fetched from constant_expression
        std::string varName1 = "100"; // this will be a const-literal
        constant_expression_H(node->children[2], varName1);


        int constValue = std::stoi(varName1);
        explicitInitValue = constValue;
        isExplicityInit = true;

        // 3. Pass the data up
        // All data is passed up already
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_varName = " + varName);                               // 🌴 Adding syn_attr
    A_PTree node->addAttribute("syn_explicitInitValue = " + toString(explicitInitValue)); // 🌴 Adding syn_attr
    A_PTree node->addAttribute("syn_isExplicityInit = " + toString(isExplicityInit));     // 🌴 Adding syn_attr
    return;
}

// ----- Declarator Handlers -----
void declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "pointer direct_declarator";
    std::string P2 = "direct_declarator";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        //         // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo*> ptrInfo = std::vector<PointerInfo*>();
        pointer_H(node->children[0], ptrInfo, ptrInfo);

        // Update the inh_type
        for (auto &unit : ptrInfo)
        {
            PointerInfo *info = new PointerInfo(); // This will make a heap copy
            info->typeQualifiers = unit->typeQualifiers;
            inh_type.levelStack.push(info);
        }

        // 2. Call the function again to fetch the next value
        direct_declarator_H(node->children[1], inh_type, varName1, type1);

        // 3. Pass the data up
        varName = varName1;
        type = type1;
    }
    else if (whichProduction == P2)
    {
        //         // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        // 1. Call the function again to fetch the next value
        direct_declarator_H(node->children[0], inh_type, varName1, type1);

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_varName = " + varName);     // 🌴 Adding syn_attr
    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    return;
}

void direct_declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type)
{

    
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "LPAREN declarator RPAREN"; // More Levels

    std::string P3 = "direct_declarator LSQUARE constant_expression RSQUARE"; // Array
    std::string P4 = "direct_declarator LSQUARE RSQUARE";

    std::string P5 = "direct_declarator LPAREN parameter_type_list RPAREN"; // Function Signature
    std::string P6 = "direct_declarator LPAREN RPAREN";                     // Function call + Signature { Two Possibilities TO-THINK 🤨🤨🤨🤨 }
    std::string P7 = "direct_declarator LPAREN identifier_list RPAREN";     // Function Calls

    A_PTree node->addAttribute("inh_type = " + toString(inh_type)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 0. syn_data to fetch ⬆️
        varName = node->children[0]->value;
        type = inh_type; // Rotate the inh_type to syn_type ☯️
    }
    else if (whichProduction == P2)
    {
        // 1. Call the function again to fetch the next value
        TypeExpression type1;
        std::string varName1; // to be fetched ⬆️

        // Update the inh_type
        ParenthesisInfo *info = new ParenthesisInfo();
        inh_type.levelStack.push(info);

        declarator_H(node->children[1], inh_type, varName1, type1);

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    }
    else if (whichProduction == P3 || whichProduction == P4)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Update inh_type before passing

        std::string value = "-1"; // Either get's updated by constant_expression_H or remains -1
        if (whichProduction == P3)
        {
            constant_expression_H(node->children[2], value);
        }
        int size = std::stoi(value);

        ArrayInfo *info = new ArrayInfo();
        info->dimSize = size;
        inh_type.levelStack.push(info);

        // 2. Call the function again to fetch the next value
        direct_declarator_H(node->children[0], inh_type, varName1, type1);

        // 3. Pass the data up
        varName = varName1;
        type = type1;
    }
    else if (whichProduction == P5 || whichProduction == P6)
    {
        // Function signature

        // 0. Prepare syn_data to be fetched ⬆️
        std::vector<TypeExpression> paramVector;
        std::vector<std::string> varName_list;
        // 1. Call the function again to fetch the next value
        if (whichProduction == P5)
        {
                parameter_type_list_H(node->children[2], paramVector, varName_list);
        }
        else
        {
            // Argument List is Empty
        }
        // Update the inh_type
        ParameterInfo *info = new ParameterInfo();
        info->paramsType = paramVector;
        info->paramsName = varName_list;

        inh_type.levelStack.push(info);

        // 2. Call the function again to fetch the next value
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        direct_declarator_H(node->children[0], inh_type, varName1, type1);
        // 3. Pass the data up
        varName = varName1;
        type = type1;
    }
    else if (whichProduction == P7)
    {
        // What is this doing? [🧠 ToThink]
        // MOST LIKEY - ERROR: a parameter list without types is only allowed in a function definition
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_varName = " + varName); // 🌴 Adding syn_attr

    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    return;
}

// ----- Pointer Handlers -----
void pointer_H(ASTNode *node, std::vector<PointerInfo*> inh_ptrInfo, std::vector<PointerInfo*> &ptrInfo)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "STAR";
    std::string P2 = "STAR type_qualifier_list";
    std::string P3 = "STAR pointer";
    std::string P4 = "STAR type_qualifier_list pointer";

    A_PTree node->addAttribute("inh_ptrInfo = " + toString(inh_ptrInfo)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // Last Production 🚦 - Need to rotate
        PointerInfo* info = new PointerInfo(); // Create a new PointerInfo
        ptrInfo = inh_ptrInfo;   // rotate inh_PtrInfo to syn_PtrInfo ☯️
        ptrInfo.push_back(info); // Push the new info to inh_ptrInfo1 to pass
    }
    else if (whichProduction == P2)
    {
        //
        std::vector<TypeQualifier> typeQualifiers; // Recieve syn_attr ⬆️
        type_qualifier_list_H(node->children[1], typeQualifiers);

        // Last Production 🚦 - Need to rotate
        PointerInfo* info = new PointerInfo(); // Create a new PointerInfo
        info->typeQualifiers = typeQualifiers;

        ptrInfo = inh_ptrInfo; // rotate inh_PtrInfo to syn_PtrInfo ☯️
        ptrInfo.push_back(info);
    }
    else if (whichProduction == P3)
    {
        std::vector<PointerInfo*> ptrInfo1 = std::vector<PointerInfo*>();
        std::vector<PointerInfo*> inh_ptrInfo1 = inh_ptrInfo;

        PointerInfo* info = new PointerInfo();             // Create a new PointerInfo
        inh_ptrInfo1.push_back(info); // Push the new info to inh_ptrInfo1 to pass

        pointer_H(node->children[1], inh_ptrInfo1, ptrInfo1);

        ptrInfo = ptrInfo1; // Pass syn_attr ⬆️
    }
    else if (whichProduction == P4)
    {

        std::vector<PointerInfo*> ptrInfo1 = std::vector<PointerInfo*>();
        std::vector<PointerInfo*> inh_ptrInfo1 = inh_ptrInfo;

        std::vector<TypeQualifier> typeQualifiers; // Recieve syn_attr ⬆️
        type_qualifier_list_H(node->children[1], typeQualifiers);

        PointerInfo* info = new PointerInfo(); // Create a new PointerInfo
        info->typeQualifiers = typeQualifiers;
        inh_ptrInfo1.push_back(info); // Push the new info to inh_ptrInfo1 to pass

        pointer_H(node->children[1], inh_ptrInfo1, ptrInfo1);

        ptrInfo = ptrInfo1; // Pass syn_attr ⬆️
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        A_PTree node->addAttribute("Wrong Production in pointer_H");
        return;
    }

    A_PTree node->addAttribute("syn_ptrInfo = " + toString(ptrInfo)); // 🌴 Adding syn_attr

    EXIT_H;
    return;
}

// ----- Parameter Handlers -----
void parameter_type_list_H(ASTNode *node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "parameter_list";
    std::string P2 = "parameter_list COMMA ELLIPSIS";
 
    if (node->children.size() == 0)
    {

            // return;
    }

    A_PTree node->addAttribute("inh_paramVector = " + toString(paramVector)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 1. Call the function again to fetch the next value

        parameter_list_H(node->children[0], paramVector, varName_list);
    }
    else if (whichProduction == P2)
    {
        // Feature NOT SUPPORTED
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_paramVector = " + toString(paramVector)); // 🌴 Adding syn_attr

    return;
}

void parameter_list_H(ASTNode *node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "parameter_declaration";
    std::string P2 = "parameter_list COMMA parameter_declaration";

    A_PTree node->addAttribute("inh_paramVector = " + toString(paramVector)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // Prepare syn_data to recieve
        TypeExpression type; // to be fetched ⬆️
        std::string varName1;
        parameter_declaration_H(node->children[0], type, varName1);

        std::vector<TypeExpression> newParamVector;
        newParamVector.push_back(type);
        std::vector<std::string> varName_list1;
        varName_list1.push_back(varName1);

        // 1. Pass the data up
        paramVector = newParamVector; // send syn_attr ⬆️
        // it is last production so create the varName_list here
        varName_list = varName_list1;
    }
    else if (whichProduction == P2)
    {
        std::vector<TypeExpression> paramVector1;
        std::vector<std::string> varName_list1;
        // 1. Call the function again to fetch the next value
        parameter_list_H(node->children[0], paramVector1, varName_list1);

        // 2. Call the function again to fetch the next value
        TypeExpression type;  // to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️

        parameter_declaration_H(node->children[2], type, varName1);

        // 3. Add the new parameter to the vector
        paramVector1.push_back(type);
        varName_list1.push_back(varName1);

        // 4. Pass the data up
        paramVector = paramVector1; // send syn_attr ⬆️
        varName_list = varName_list1;
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        A_PTree node->addAttribute("Wrong Production in parameter_list_H");
        return;
    }

    A_PTree node->addAttribute("syn_type = " + toString(paramVector)); // 🌴 Adding syn_attr

    EXIT_H;
    return;
}

void parameter_declaration_H(ASTNode *node, TypeExpression &type, std::string varName)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers declarator";
    std::string P2 = "declaration_specifiers abstract_declarator";
    std::string P3 = "declaration_specifiers";

    A_PTree node->addAttribute("inh_type = " + toString(type)); // 🌳 Adding inh_attr

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3)
    {
        // Wrong Production
        ERROR_EXIT_H;
        A_PTree node->addAttribute("Wrong Production in parameter_declaration_H");
        return;
    }

    // Code Common to all
    // 1. Call the function again to fetch the next value
    std::vector<std::string> valueVector;
    declaration_specifiers_H(node->children[0], valueVector);

    // Create a BaseInfo object
    TypeExpression inh_type;
    StorageClass inh_storageClass = StorageClass::NONE;
    int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
    if (check != OKAY)
    {
        aptLOG("SEMANTIC ERROR 🚨 : Invalid TypeSpecifier");
    }
    if (inh_storageClass != StorageClass::NONE)
    {
        aptLOG("SEMANTIC ERROR 🚨 : TO Check if StorageClass Allowed Here or NOT");
    }

    if (whichProduction == P1)
    {
        aptLOG("Production 1");
        // 3. Prepare syn_data to be fetched
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        declarator_H(node->children[1], inh_type, varName1, type1);

        // 3. Pass the data up
        type = type1; // send syn_attr ⬆️
        varName = varName1;
    }
    else if (whichProduction == P2)
    {
        aptLOG("Production 2");
        // 3. Prepare syn_data to be fetched
        TypeExpression type1; // to be fetched ⬆️

        aptLOG("Calling abstract_declarator_H");
        abstract_declarator_H(node->children[1], inh_type, type1);
        aptLOG("Returned from abstract_declarator_H");

        

        // 3. Pass the data up
        type = type1; // send syn_attr ⬆️
        // No varname
        varName = NO_ARG_NAME;
    }
    else if (whichProduction == P3)
    {
        aptLOG("Production 3");
        // 3. Pass the data up
        type = inh_type; // send syn_attr ⬆️
    }

    else
    {   
        aptLOG("Production WRONG");
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;
    return;
}

// ----- Identifier List Handlers -----
void identifier_list_H(ASTNode *node, std::vector<std::string> &idList)
{

        std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "identifier_list COMMA IDENTIFIER";

    A_PTree node->addAttribute("inh_idList = " + toString(idList)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 0. syn_data to fetch ⬆️
        std::string idName = node->children[0]->value;

        // 1. Pass the data up
        idList.push_back(idName); // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        // 0. First child syn_data + inh_data passed ⬇️
        identifier_list_H(node->children[0], idList);

        // 1. Second child syn_data to be fetched ⬆️
        std::string idName = node->children[2]->value;

        // 2. Pass the data up
        idList.push_back(idName); // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_idList = " + toString(idList)); // 🌴 Adding syn_attr

    return;
}

//----- type name Handlers -----
void type_name_H(ASTNode *node, TypeExpression &type)
{

    
    std::string whichProduction = getProduction(node);
    std::string P1 = "specifier_qualifier_list";
    std::string P2 = "specifier_qualifier_list abstract_declarator";

    A_PTree node->addAttribute("inh_type = " + toString(type)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::vector<std::string> valueVector;
        // 1. Call the function again to fetch the next value
        specifier_qualifier_list_H(node->children[0], valueVector);

        // 2. Create a TypeExpression object
        TypeExpression inh_type;
        ;
        StorageClass inh_storageClass = StorageClass::NONE; // [Syntax Checked]
        int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
        if (check != OKAY)
        {
            // SEMANTIC ERROR 🚨 : Invalid TypeSpecifier
        }
        if (inh_storageClass != StorageClass::NONE)
        {
            // SEMANTIC ERROR 🚨 : TO Check if StorageClass Allowed Here or NOT
        }

        // Pass the data up
        type = inh_type; // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::vector<std::string> valueVector;
        // 1. Call the function again to fetch the next value
        specifier_qualifier_list_H(node->children[0], valueVector);

        // 2. Create a TypeExpression object
        TypeExpression inh_type;
        StorageClass inh_storageClass = StorageClass::NONE;
        int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
        if (check != OKAY)
        {
            // SEMANTIC ERROR 🚨 : Invalid TypeSpecifier
        }

        // 4. Call the function again to fetch the next value
        abstract_declarator_H(node->children[1], inh_type, type);
    }
    else
    {
        // Wrong Production
    }

    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr
    return;
}

// ----- Abstract Declarator Handlers -----
void abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "pointer";
    std::string P2 = "direct_abstract_declarator";
    std::string P3 = "pointer direct_abstract_declarator";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        TypeExpression type1 = inh_type;
        aptLOG("Production 1");
        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo*> ptrInfo = std::vector<PointerInfo*>();
        pointer_H(node->children[0], ptrInfo, ptrInfo);
        for (int i = 0; i < ptrInfo.size(); i++)
        {
            PointerInfo *info = ptrInfo[i];
            type1.levelStack.push(info);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        aptLOG("Production 2");
        // 1. Call the function again to fetch the next value
        TypeExpression type1;
        direct_abstract_declarator_H(node->children[0], inh_type, type1);

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else if (whichProduction == P3)
    {
        TypeExpression type1 = inh_type;
        aptLOG("Production 3");
        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo*> ptrInfo = std::vector<PointerInfo*>();
        pointer_H(node->children[0], ptrInfo, ptrInfo);
        for (int i = 0; i < ptrInfo.size(); i++)
        {
            PointerInfo *info = ptrInfo[i];
            PointerInfo *infoPtr = info;
            type1.levelStack.push(infoPtr);
        }
        // 2. Call the function again to fetch the next value
        TypeExpression type2;
        direct_abstract_declarator_H(node->children[1], type1, type2);

        // Pass the data up
        type = type2; // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        A_PTree node->addAttribute("Error in abstract_declarator_H"); // 🌴 Adding syn_attr
        return;
    }

    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;
    return;
}

void direct_abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type)
{

    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "LPAREN abstract_declarator RPAREN";

    std::string P2 = "LSQUARE RSQUARE";
    std::string P3 = "LSQUARE constant_expression RSQUARE";
    std::string P4 = "direct_abstract_declarator LSQUARE RSQUARE";
    std::string P5 = "direct_abstract_declarator LSQUARE constant_expression RSQUARE";

    std::string P6 = "LPAREN RPAREN";
    std::string P7 = "LPAREN parameter_type_list RPAREN";
    std::string P8 = "direct_abstract_declarator LPAREN RPAREN";
    std::string P9 = "direct_abstract_declarator LPAREN parameter_type_list RPAREN";

    A_PTree node->addAttribute("inh_type = " + toString(inh_type)); // 🌳 Adding inh_attr

    if (whichProduction == P1)
    {
        aptLOG("Production 1");
        // 1. Call the function again to fetch the next value
        TypeExpression type1 = inh_type;
        ParenthesisInfo *info = new ParenthesisInfo();
        inh_type.levelStack.push(info);
        abstract_declarator_H(node->children[1], inh_type, type1);

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }

    else if (whichProduction == P2 || whichProduction == P3 || whichProduction == P4 || whichProduction == P5)
    {

        int indexConstExpr = (whichProduction == P3) ? 1 : 2;
        std::string constValue = "NULL";
        if (whichProduction == P3 || whichProduction == P5)
        {
            // 1. Call the function again to fetch the next value
            constant_expression_H(node->children[indexConstExpr], constValue);
        }
        int constValue1 = (constValue == "NULL") ? 0 : std::stoi(constValue);

        ArrayInfo *info = new ArrayInfo();
        info->dimSize = constValue1;

        inh_type.levelStack.push(info); // Push the new info to inh_type
        TypeExpression type1 = inh_type;
        if (whichProduction == P4 || whichProduction == P5)
        {
            // 1. Call the function again to fetch the next value
            direct_abstract_declarator_H(node->children[0], inh_type, type1);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }

    else if (whichProduction == P6 || whichProduction == P7 || whichProduction == P8 || whichProduction == P9)
    {
        //
        std::vector<TypeExpression> paramVector;
        std::vector<std::string> varName_list;
        if (whichProduction == P7 || whichProduction == P9)
        {
            // 1. Call the function again to fetch the next value
            int index = (whichProduction == P7) ? 1 : 2;
            parameter_type_list_H(node->children[index], paramVector, varName_list);
        }

        ParameterInfo *info = new ParameterInfo();
        info->paramsType = paramVector;
        info->paramsName = varName_list;

        if (varName_list.empty())
        {
            info->isAbstract = true;
        }

        inh_type.levelStack.push(info); // Push the new info to inh_type
        TypeExpression type1 = inh_type;
        if (whichProduction == P8 || whichProduction == P9)
        {
            // 1. Call the function again to fetch the next value
            direct_abstract_declarator_H(node->children[0], inh_type, type1);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        A_PTree node->addAttribute("Error in direct_abstract_declarator_H"); // 🌴 Adding syn_attr
        return;
    }

    A_PTree node->addAttribute("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;
    return;
}

//---- Initializers ---------
void initializer_H(ASTNode *node, TypeExpression inh_type, std::string inh_varName)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "assignment_expression";
    std::string P2 = "LCURLY initializer_list RCURLY";
    std::string P3 = "LCURLY initializer_list COMMA RCURLY";

    if (whichProduction == P1)
    {
        // Prepare data to Fetch
        std::string varName1 = "NULL"; // to be fetched ⬆️
        TypeExpression type1;          // to be fetched ⬆️
        VALUE_TYPE valuetype1;
        SPACE valueSpace1;
        assignment_expression_H(node->children[0], "NONE", varName1, type1, valuetype1, valueSpace1);
        PASS_THE_ERROR(varName1);
        // 🅱️ TypeChecking
        // Logic - If Base -> If both are numeric(+enum/enumConstats) -> typecast arg to resultType and assign (IRCode Needed)
        // Logic - If Base -> If both are Record(union/struct) Object -> MUST be EXACT match else ERROR
        // Logic - If both (POINTER,FUNCTION,ARRAY) -> IGNORE BELOW LEVEL -> just assign varName and returnType = resultType
        bool isValid = ourEquivalent(inh_type, type1);
        if (isValid)
        {
            // SEMANTIC ERROR 🚨 : Type Mismatch
            semanticLOG.push_back("Initializer Type Mismatch ❌");
            ERROR_EXIT_H;
            return;
        }

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 🎉 SIDE EFFECTS 🎉

        CODE_BASE.addTAC(node, inh_varName, "=", varName1, NO_ARG); // Assign the value to the variable

        // 🤮 Return Value 🤮
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {
        semanticLOG.push_back("Initializer List ❌ NOT Supported");
        ERROR_EXIT_H;
        return;
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        return;
    }

    EXIT_H;
}

// void initializer_list_H(ASTNode *node)
// {
//      //    //     std::string whichProduction = getProduction(node);
//     std::string P1 = "initializer";
//     std::string P2 = "initializer_list COMMA initializer";

//     //[To be implemented] - Initializer Evaluation

//     return;
// }

