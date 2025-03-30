#include "header.h"
#include "utility.h"
//=====================[ Forward Declaration of Declarations ]=========================================================================================

//====================[ Globally Accessible Variables ]=========================================================================================
extern SymbolTable SYM_TABLE; // Global Symbol Table
extern TAC CODE_BASE; // Global TAC Code Base

//====================[ Helper Functions ]=========================================================================================

std::string getProduction(ASTNode* node){
    std::string production = "";
    int numChildren = node->children.size();
    for (int i = 0; i < numChildren; i++) {
        if (i != 0) {
            production += " ";
        }
        production += node->children[i]->type;
    }
    return production;
}

int ProcessDecSpecifiers(std::vector<std::string> &valueVector, BaseInfo *&base, StorageClass &storageClass){
    // 1. Fill base

    // 2. Check for storage class

    return 0;
}

//====================[ Declaration Handlers ]=========================================================================================


void declaration_H(ASTNode *node){

    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers SEMI_COLON";
    std::string P2 = "declaration_specifiers init_declarator_list SEMI_COLON";

    // Code Common to P1 & P2
    //  1. Call the declaration_specifiers_H function to fetch syn_attr ⬆️
        std::vector<std::string> valueVector;
        declaration_specifiers_H(node->children[0], valueVector);

    // 2. Prepare data to be sent down to next child
        // 2.1 Create a BaseInfo object
            BaseInfo *base = new BaseInfo();
            StorageClass inh_storageClass = StorageClass::AUTO;
            int check = ProcessDecSpecifiers(valueVector, base, inh_storageClass);

        // 2.2 Create a TypeExpression object
            TypeExpression inh_type;
            inh_type.levelStack.push(base);

    // ##P1## - declaration_specifiers SEMI_COLON
    if(whichProduction == P1){
        
        // Nothing More to do here

    //## P2 ## - declaration_specifiers init_declarator_list SEMI_COLON
    }else if(whichProduction == P2){
        // 3. We send the inh_data ⬇️ | NOthing to fetch
        init_declarator_list_H(node->children[1], inh_type, inh_storageClass);
    }
    else{
        // Wrong Production
    }

    return;
}
/*

*/
void declaration_specifiers_H(ASTNode* node, std::vector<std::string> &valueVector){
    std::string whichProduction = getProduction(node);
    std::string P1 = "storage_class_specifier";
    std::string P2 = "storage_class_specifier declaration_specifiers";
    std::string P3 = "type_specifier";
    std::string P4 = "type_specifier declaration_specifiers";
    std::string P5 = "type_qualifier";
    std::string P6 = "type_qualifier declaration_specifiers";

    if(whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4 && whichProduction != P5 && whichProduction != P6){
        // Wrong Production
        return;
    }
    std::string value;
    // Code Common to all productions (P1 & P2)
    // 1. We call the function again to fetch the next value
    if(whichProduction == P1 || whichProduction == P2){
        storage_class_specifier_H(node->children[0], value);
        valueVector.push_back(value);
    }else if(whichProduction == P3 || whichProduction == P4){
        // 1. We call the function again to fetch the next value
        type_specifier_H(node->children[0], value);
        valueVector.push_back(value);
    }else if(whichProduction == P5 || whichProduction == P6){
        // 1. We call the function again to fetch the next value
        type_qualifier_H(node->children[0], value);
        valueVector.push_back(value);
    }

    // Code Common to (P2, P4, P6)
    if(whichProduction == P2 || whichProduction == P4 || whichProduction == P6){
        // 1. We call the function again to fetch the next value
        declaration_specifiers_H(node->children[1], valueVector);
    }

    return;
}
/*
*/
void init_declarator_list_H(ASTNode* node, TypeExpression inh_type, StorageClass inh_storageClass){
    std::string whichProduction = getProduction(node);
    std::string P1 = "init_declarator";
    std::string P2 = "init_declarator_list COMMA init_declarator";

    if(whichProduction == P1){
        // 1. We call the function again to fetch the next value
        init_declarator_H(node->children[0], inh_type, inh_storageClass);

    }else if(whichProduction == P2){
        // 1. We call the function again to fetch the next value
        init_declarator_list_H(node->children[0], inh_type, inh_storageClass);

        // 2. We call the function again to fetch the next value
        init_declarator_H(node->children[2], inh_type, inh_storageClass);
    }else{
        // Wrong Production
    }

    
    return;
}
/*
*/
void init_declarator_H(ASTNode* node, TypeExpression inh_type, StorageClass inh_storageClass){
    std::string whichProduction = getProduction(node);
    std::string P1 = "declarator";
    std::string P2 = "declarator ASSIGN initializer";

    // Code Common to (P1, P2)
    if(whichProduction == P1 || whichProduction == P2){
        // 0. Caryy inh_type ⬇️ 
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️
        declarator_H(node->children[0], inh_type, varName, type);

        // 1. Create Symbol (Variable or Function)
            Type whichType = whatIsType(type);
            GenericSymbol *symbol;

            if(whichType == Type::FUNCTION){
                // Function 
                Function *func = new Function();
                func->symbolName = varName;
                func->type = type;
                func->isDefined = false; // To be set to true when the function is defined

                if(inh_storageClass == StorageClass::AUTO){
                    // INVALID in NEW C99
                }
                else if(inh_storageClass == StorageClass::STATIC){
                    // ⚡️ Too Advance ⚡️
                }
                symbol = func;
            }
            else{
            // Variable
            Variable *var = new Variable();
            var->symbolName = varName;
            var->type = type;
            var->storageClass = inh_storageClass;
            // [📴 Offset to be filled]

            symbol = var;
        }

        // 2. Add the symbol to the symbol table
            int check = SYM_TABLE.insert(varName, symbol);
            if(check == INSERT_FAILURE){
                // SEMANTIC ERROR 🚨 : Variable already present in the current scope
            }

        // Done - NO 🔖IRCode
    }else if(whichProduction == P2){
        
        // 3. After Inserting it in Symbol Table
            // [ToThink about - Initializer 🧠]

    }else{
        // Wrong Production
    }
    return;
}
/*
*/
void storage_class_specifier_H(ASTNode* node, std::string &value){
    // Has only one Production
    int noOfChild = node->children.size();
    if(noOfChild != 1){
        // Wrong Production
        return;
    }

    // 1. Get the value
        value = node->children[0]->value;
    return;
}

void type_qualifier_H(ASTNode* node, std::string &value){
    // Has only one Production
    int noOfChild = node->children.size();
    if(noOfChild != 1){
        // Wrong Production
        return;
    }

    // 1. Get the value
        value = node->children[0]->value;
    return;
}

void type_qualifier_list_H(ASTNode* node, std::vector<TypeQualifier> &typeQualifiers){
    std::string whichProduction = getProduction(node);
    std::string P1 = "type_qualifier";
    std::string P2 = "type_qualifier_list type_qualifier";



    if(whichProduction == P1){
        // 1. We call the function again to fetch the next value
        TypeQualifier typeQualifier;
        std::string typeQualifierStr;
        type_qualifier_H(node->children[0], typeQualifierStr);
        if(typeQualifierStr == "const"){
            typeQualifier = TypeQualifier::CONST;
        }else if(typeQualifierStr == "volatile"){
            typeQualifier = TypeQualifier::VOLATILE;
        }else if(typeQualifierStr == "restrict"){
            typeQualifier = TypeQualifier::RESTRICT;
        }else{
            // Wrong type of Type Qualifier
        }
        
        typeQualifiers.push_back(typeQualifier);
    }else if(whichProduction == P2){
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
    }else{
        // Wrong Production
    }
    return;
}

/*
*/
void type_specifier_H(ASTNode* node, std::string &value){
    std::string whichProduction = getProduction(node);
    std::string P10 = "struct_or_union_specifier";
    std::string P11 = "enum_specifier";
    std::string P12 = "TYPE_NAME";

    if(whichProduction != P10 && whichProduction != P11 && whichProduction != P12){
        // Primitive Types
        if(node->children.size() != 1){
            // Wrong Production
            return;
        }
        value = node->children[0]->value;
    }

    // Struct or Union
    else if(whichProduction == P10){
        // 1. Call the function again to fetch the next value
        struct_or_union_specifier_H(node->children[0], value);
    }

    // Enum
    else if(whichProduction == P11){
        // 1. Call the function again to fetch the next value
        enum_specifier_H(node->children[0], value);
    }
    // Type Name
    else if(whichProduction == P12){
        // IGNORED
    }else{
        // Wrong Production
    }
    return;
}
/*
*/
void struct_or_union_specifier_H(ASTNode* node, std::string &value){
    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY";
    std::string P2 = "struct_or_union LCURLY struct_declaration_list RCURLY";
    std::string P3 = "struct_or_union IDENTIFIER";

    std::string recordStr = (node->children.size() > 0) ? node->children[0]->value : "";

    // Code Commong to P1 & P2
    if(whichProduction == P1 || whichProduction == P2){

        // 0. Call struct_declaration_list_H to fill the members
            std::map<std::string, TypeExpression> members; // fetch syn_attr ⬆️
            int position = (whichProduction == P1) ? 3 : 2;
            struct_declaration_list_H(node->children[position], members);

        // 1. Create a UserDType Unit
        UserDType* userDType = new UserDType();
        RecordType recordType = (recordStr == "struct") ? RecordType::STRUCT : RecordType::UNION;

        userDType->recordType = recordType;
        userDType->members = members;
        

        // 2. Add it to the symbol table
            std::string recordID = (whichProduction == P1) ? node->children[1]->value : newRecordName();

            int check = SYM_TABLE.insertRecord(recordID, userDType);
            if(check == INSERT_FAILURE){
                // SEMANTIC ERROR 🚨 : Record already present in the current scope
            }
        
        // 3. Pass a String up
            std::string scope = std::to_string(SYM_TABLE.scopeNo);
            std::string typeSpecifier = recordStr + " " + recordID + " " + scope;

            value = typeSpecifier; // send syn_attr ⬆️
    }
    else if(whichProduction == P3){
        // 1. Check if UserDType is there in symbol table
            std::string recordID = node->children[1]->value;
            GenericSymbol *symbol;
            int check = SYM_TABLE.lookupRecord(recordID, symbol);
            if(check == LOOKUP_FAILURE){
                // SEMANTIC ERROR 🚨 : Record not found
            }
            else{
                RecordType neededType = (recordStr == "struct") ? RecordType::STRUCT : RecordType::UNION;
                RecordType foundType = ((UserDType*)symbol)->recordType;
                if(neededType != foundType){
                    // SEMANTIC ERROR 🚨 : Type Mismatch
                }
            }

        // 2. Pass a String up
            std::string scope = std::to_string(symbol->scopeNo);
            std::string typeSpecifier = recordStr + " " + recordID + " " + scope;

            value = typeSpecifier; // send syn_attr ⬆️
    }
    else {
        // Wrong Production
    }
    return;
}


// struct_or_union_H is not needed

void struct_declaration_list_H(ASTNode* node, std::map<std::string, TypeExpression> &members){
    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_declaration";
    std::string P2 = "struct_declaration_list struct_declaration";
    

    if(whichProduction == P1){
        std::map<std::string, TypeExpression> members1;
        // 1. Last Production will just exactly pass syn_attr(members) ⬆️
            struct_declaration_H(node->children[0], members1);
        
        // 2. Add the members to the map
            members = members1; // Since Last Production
    }
    else if(whichProduction == P2){
        // 1. Call the function again to fetch the next value
            std::map<std::string, TypeExpression> members1;
            struct_declaration_list_H(node->children[0], members1);

        // 2. Call the function again to fetch the next value
            std::map<std::string, TypeExpression> members2;
            struct_declaration_H(node->children[1], members2);
        
        // 3. Add the members to the map
            // Copy all from members2 to members1
            for(auto &unit : members2){
                if(members1.count(unit.first)){
                    // SEMANTIC ERROR 🚨 : Member already present
                }
                members1[unit.first] = unit.second;
            }
        // 4. Pass the members up
            members = members1; // send syn_attr ⬆️
    }else{
        // Wrong Production
    }
    return;
}

/*
*/

void struct_declaration_H(ASTNode* node, std::map<std::string, TypeExpression> &members){
    std::string whichProduction = getProduction(node);
    std::string P1 = "specifier_qualifier_list struct_declarator_list SEMI_COLON";

    if(whichProduction != P1){
        // Wrong Production
        return;
    }
    std::vector<std::string> valueVector;
    // 0. Call the function again to fetch the next value
        specifier_qualifier_list_H(node->children[0], valueVector);
    
    // 1. Create a BaseInfo object
        BaseInfo* base = new BaseInfo();
        StorageClass inh_storageClass; // NOT ALLOWED ❌ [Will be syntax checked]
        int check = ProcessDecSpecifiers(valueVector, base, inh_storageClass);
        if(check == -1){
            // SEMANTIC ERROR 🚨 : Invalid TypeSpecifier
        }

    // 2. Create a TypeExpression object
        TypeExpression inh_type;
        inh_type.levelStack.push(base);

    // Pass the inh_data ⬇️ & fetch the syn_attr(members) ⬆️
        std::map<std::string, TypeExpression> syn_members;
        struct_declarator_list_H(node->children[1], inh_type, syn_members);
    
    // Pass the members up
        members = syn_members; // send syn_attr ⬆️
    return;
}

void specifier_qualifier_list_H(ASTNode* node, std::vector<std::string> &valueVector){
    std::string whichProduction = getProduction(node);
    std::string P1 = "type_specifier specifier_qualifier_list";
    std::string P2 = "type_specifier";
    std::string P3 = "type_qualifier specifier_qualifier_list";
    std::string P4 = "type_qualifier";

    if(whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4){
        // Wrong Production
        return;
    }

    // Code Common to all 
    std::string value = node->children[0]->value; 

    if(whichProduction == P1 || whichProduction == P3){
        // 1. We call the function again to fetch the next value
        specifier_qualifier_list_H(node->children[1], valueVector);
    }

    return;
}

void struct_declarator_list_H(ASTNode* node, TypeExpression inh_type, std::map<std::string, TypeExpression> &members){
    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_declarator";
    std::string P2 = "struct_declarator_list COMMA struct_declarator";

    if(whichProduction == P1){
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️

        // 0. Call the child's Handler
        struct_declarator_H(node->children[0], inh_type, varName, type);

        // 1. Last Production for "members" variable
        std::map<std::string, TypeExpression> members1;

        // 2. Check if the varName is already present
        if(members.count(varName)){
            // SEMANTIC ERROR 🚨 : Member already present
        }
        members1[varName] = type;
        // 3. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else if(whichProduction == P2){
        // 0. First child syn_data + inh_data passed ⬇️
        std::map<std::string, TypeExpression> members1;
        struct_declarator_list_H(node->children[0], inh_type, members1);
    
        // 1. Second child syn_data to be fetched ⬆️ + inh_data passed ⬇️
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️
        struct_declarator_H(node->children[2], inh_type, varName, type);
        
        // 2. Check if the varName is already present
        if(members1.count(varName)){
            // SEMANTIC ERROR 🚨 : Member already present
        }

        members1[varName] = type; // Add the new member ➕
        // 3. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else{
        // Wrong Production
    }
    return;
}
/*
*/
void struct_declarator_H(ASTNode* node, TypeExpression inh_type, std::string &varName, TypeExpression &type){
    std::string whichProduction = getProduction(node);
    std::string P1 = "declarator";
    std::string P2 = "COLON constant_expression declarator";
    std::string P3 = "COLON constant_expression";

    if(whichProduction == P1){
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the child's Handler
        declarator_H(node->children[0], inh_type, varName1, type1);

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    
    }else if(whichProduction == P2){ // ⚡️ Advance Feature ⚡️ - BitFields
        
        // No Handler to call
        varName = "";
        type = inh_type; // Pass the inh_type as it is

    }else if(whichProduction == P3){ // ⚡️ Advance Feature ⚡️ - BitFields
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the child's Handler
        declarator_H(node->children[1], inh_type, varName1, type1);        

        // [IGNORED] - Constant Expression - BitField Size

        // 2. Pass the data up
        varName = varName1;
        type = type1;

    }else{
        // Wrong Production
    }
    return;
}

/*
*/
void enum_specifier_H(ASTNode* node, std::string &value){
    std::string whichProduction = getProduction(node);
    std::string P1 = "ENUM LCURLY enumerator_list RCURLY";
    std::string P2 = "ENUM IDENTIFIER LCURLY enumerator_list RCURLY";
    std::string P3 = "ENUM IDENTIFIER";

    // Code Common to P1 & P2
    if(whichProduction == P1 || whichProduction == P2){
    // 1. Create a UserDType Entry
        UserDType* userDType = new UserDType();
        userDType->recordType = RecordType::ENUM;
        userDType->members = std::map<std::string, TypeExpression>(); // Empty Map // Enum won't use this

    // We must call the enumerator_list_H function but it's don't need anything from parent,
    

    // 2. Find Name of Enum - RecordID
        std::string recordID = (whichProduction == P1) ? node->children[1]->value : newRecordName();
        int lastInitValue = 0; // To be passed to enumerator_list_H

    // 3. Call the child's handler
        int index = (whichProduction == P1) ? 2 : 3;
        enumerator_list_H(node->children[index], recordID, lastInitValue);

        // 4. Add it to the symbol table
        int check = SYM_TABLE.insertRecord(recordID, userDType);
        if(check == INSERT_FAILURE){
            // SEMANTIC ERROR 🚨 : Record already present in the current scope
        }
    // 5. Pass a String up
        std::string scope = std::to_string(SYM_TABLE.scopeNo);
        std::string typeSpecifier = "enum " + recordID + " " + scope;

        value = typeSpecifier; // send syn_attr ⬆️
    } else if(whichProduction == P3){
        // 1. Check if such a ENUM UserDType exists
        std::string recordID = node->children[1]->value;
        GenericSymbol *symbol;
        int check = SYM_TABLE.lookupRecord(recordID, symbol);
        if(check == LOOKUP_FAILURE){
            // SEMANTIC ERROR 🚨 : Record not found
        }
        else{
            RecordType neededType = RecordType::ENUM;
            RecordType foundType = ((UserDType*)symbol)->recordType;
            if(neededType != foundType){
                // SEMANTIC ERROR 🚨 : Type Mismatch
            }
        }
        // 2. Pass a String up
            std::string scope = std::to_string(symbol->scopeNo);
            std::string typeSpecifier = "enum " + recordID + " " + scope;

            value = typeSpecifier; // send syn_attr ⬆️
    }else{
        // Wrong Production
    }
    return;
}
/*
*/
void enumerator_list_H(ASTNode* node, std::string recordID, int &lastInitValue){
    std::string whichProduction = getProduction(node);
    std::string P1 = "enumerator";
    std::string P2 = "enumerator_list COMMA enumerator";

    if(whichProduction == P1){
        // last production effect
        int currInitValue;

        // 0. syn_data to fetch ⬆️
        int explicitInitValue = 0;
        bool isExplicityInit = false;
        std::string varName; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        enumerator_H(node->children[0], varName, explicitInitValue, isExplicityInit);

        if(isExplicityInit){
            currInitValue = explicitInitValue;
        }else{
            currInitValue = 0;
        }

        // 2. Add the enum constant to the symbol table
        EnumConstant *enumConst = new EnumConstant();
        enumConst->symbolName = varName;
        enumConst->value = currInitValue;

        int check = SYM_TABLE.insert(enumConst->symbolName, enumConst);
        if(check == INSERT_FAILURE){
            // SEMANTIC ERROR 🚨 : Enum Constant already present in the current scope
        }

        // Send lastInitValue up
        lastInitValue = currInitValue + 1; // Increment the value for next enumerator

    }else if(whichProduction == P2){
        // 0. First child syn_data + inh_data passed ⬇️
        int lastInitValue1;
        enumerator_list_H(node->children[0], recordID, lastInitValue1);

        int currInitValue;

        // 0. syn_data to fetch ⬆️
        int explicitInitValue;
        bool isExplicityInit = false;
        std::string varName; // to be fetched ⬆️
        // 1. Call the function again to fetch the next value
        enumerator_list_H(node->children[0], recordID, lastInitValue);

        if(isExplicityInit){
            currInitValue = explicitInitValue;
        }else{
            currInitValue = lastInitValue1;
        }

        // 2. Add the enum constant to the symbol table
        EnumConstant *enumConst = new EnumConstant();
        enumConst->symbolName = varName;
        enumConst->value = currInitValue;
        int check = SYM_TABLE.insert(enumConst->symbolName, enumConst);
        if(check == INSERT_FAILURE){
            // SEMANTIC ERROR 🚨 : Enum Constant already present in the current scope
        }

        // Send lastInitValue up
        lastInitValue = currInitValue + 1; // Increment the value for next enumerator
    }else{
        // Wrong Production
    }
}
/*
*/

void enumerator_H(ASTNode* node, std::string &varName, int &explicitInitValue, bool &isExplicityInit){
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "IDENTIFIER ASSIGN constant_expression";

    if(whichProduction == P1){
        // 0. syn_data to fetch ⬆️
        varName = node->children[0]->value;
        explicitInitValue = 0;
        isExplicityInit = false;

    }else if(whichProduction == P2){
        // 0. syn_data to fetch ⬆️
        varName = node->children[0]->value;

        // 1. syn_data to be fetched from constant_expression
        std::string varName1; // this will be a const-literal
        constant_expression_H(node->children[2],varName);

        int constValue = std::stoi(varName1);
        explicitInitValue = constValue;
        isExplicityInit = true;

        // 3. Pass the data up
        // All data is passed up already
    }else{
        // Wrong Production
    }
    return;
}

void declarator_H(ASTNode* node, TypeExpression inh_type, std::string &varName, TypeExpression &type){
    std::string whichProduction = getProduction(node);
    std::string P1 = "pointer direct_declarator";
    std::string P2 = "direct_declarator";

    if(whichProduction == P1){
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo> ptrInfo;
        pointer_H(node->children[0], ptrInfo, ptrInfo);
        for(auto &info : ptrInfo){
            inh_type.levelStack.push(&info);
        }

        // 2. Call the function again to fetch the next value   
        direct_declarator_H(node->children[1], inh_type, varName1, type1);

        // 3. Pass the data up
        varName = varName1;
        type = type1;
    }else if(whichProduction == P2){
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        // 1. Call the function again to fetch the next value
        direct_declarator_H(node->children[0], inh_type, varName1, type1);

        // 2. Pass the data up
        varName = varName1;
        type = type1;

    }else{
        // Wrong Production
    }
    return;
}

/*
*/
void direct_declarator_H(ASTNode* node, TypeExpression inh_type, std::string &varName, TypeExpression &type){
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "LPAREN declarator RPAREN";
    std::string P3 = "IDENTIFIER LPAREN parameter_type_list RPAREN";
    std::string P4 = "IDENTIFIER LPAREN RPAREN";

    if(whichProduction == P1){
        // 0. syn_data to fetch ⬆️
        varName = node->children[0]->value;
        type = inh_type; // Pass the inh_type as it is

    }else if(whichProduction == P2){
        // 1. Call the function again to fetch the next value
        declarator_H(node->children[1], inh_type, varName, type);

    }else if(whichProduction == P3){
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // First we find parameters
        std::vector<TypeExpression> paramVector;
        parameter_type_list_H(node->children[2], paramVector);
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramsType = paramVector;

        // Update the type
        inh_type.levelStack.push(paramInfo);

        // 1. Call the function again to fetch the next value
        declarator_H(node->children[0], inh_type, varName1, type1);

        // 3. Pass the data up
        varName = varName1;
        type = type1;
    }else if(whichProduction == P4){
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // First we find parameters
        std::vector<TypeExpression> paramVector; // Empty
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramsType = paramVector;

        // Update the type
        inh_type.levelStack.push(paramInfo);

        // 1. Call the function again to fetch the next value
        declarator_H(node->children[0], inh_type, varName1, type1);

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    }else{
        // Wrong Production
    }
    return;
}

/*
*/

void pointer_H(ASTNode* node, std::vector<PointerInfo> inh_ptrInfo,std::vector<PointerInfo> &ptrInfo){
    std::string whichProduction = getProduction(node);
    std::string P1 = "STAR";
    std::string P2 = "STAR type_qualifier_list";
    std::string P3 = "STAR pointer";
    std::string P4 = "STAR type_qualifier_list pointer";

    if(whichProduction == P1){
        // Last Production 🚦 - Need to rotate
        PointerInfo info; // Create a new PointerInfo
        ptrInfo = inh_ptrInfo; // rotate inh_PtrInfo to syn_PtrInfo ☯️
        ptrInfo.push_back(info); // Push the new info to inh_ptrInfo1 to pass
    } else if(whichProduction == P2){
        // 
        std::vector<TypeQualifier> typeQualifiers; // Recieve syn_attr ⬆️
        type_qualifier_list_H(node->children[1], typeQualifiers);

        // Last Production 🚦 - Need to rotate
        PointerInfo info; // Create a new PointerInfo
        info.typeQualifiers = typeQualifiers;

        ptrInfo = inh_ptrInfo; // rotate inh_PtrInfo to syn_PtrInfo ☯️
        ptrInfo.push_back(info);
    } else if(whichProduction == P3){
        std::vector<PointerInfo> ptrInfo1;
        std::vector<PointerInfo> inh_ptrInfo1 = inh_ptrInfo;

        PointerInfo info; // Create a new PointerInfo
        inh_ptrInfo1.push_back(info); // Push the new info to inh_ptrInfo1 to pass

        pointer_H(node->children[1], inh_ptrInfo1, ptrInfo1);

        ptrInfo = ptrInfo1; // Pass syn_attr ⬆️
    } else if(whichProduction == P4){

        std::vector<PointerInfo> ptrInfo1;
        std::vector<PointerInfo> inh_ptrInfo1 = inh_ptrInfo;

        std::vector<TypeQualifier> typeQualifiers; // Recieve syn_attr ⬆️
        type_qualifier_list_H(node->children[1], typeQualifiers);

        PointerInfo info;        // Create a new PointerInfo
        info.typeQualifiers = typeQualifiers;
        inh_ptrInfo1.push_back(info); // Push the new info to inh_ptrInfo1 to pass

        pointer_H(node->children[1], inh_ptrInfo1, ptrInfo1);

        ptrInfo = ptrInfo1; // Pass syn_attr ⬆️
    } else {
        // Wrong Production
    }

    return;
}

void parameter_type_list_H(ASTNode* node, std::vector<TypeExpression> &paramVector){
    std::string whichProduction = getProduction(node);
    std::string P1 = "parameter_list";
    std::string P2 = "parameter_list COMMA ELLIPSIS";

    if(whichProduction == P1){
        // 1. Call the function again to fetch the next value
        parameter_list_H(node->children[0], paramVector);
    }else if(whichProduction == P2){
        // Feature NOT SUPPORTED
    }
    else{
        // Wrong Production
    }
    return;
}

void parameter_list_H(ASTNode* node, std::vector<TypeExpression> &paramVector){
    std::string whichProduction = getProduction(node);
    std::string P1 = "parameter_declaration";
    std::string P2 = "parameter_list COMMA parameter_declaration";

    if(whichProduction == P1){
        // Prepare syn_data to recieve
        TypeExpression type; // to be fetched ⬆️
        parameter_declaration_H(node->children[0], type);

        std::vector<TypeExpression> newParamVector;
        newParamVector.push_back(type);

        // 1. Pass the data up
        paramVector = newParamVector; // send syn_attr ⬆️

    }else if(whichProduction == P2){
        std::vector<TypeExpression> paramVector1;
        // 1. Call the function again to fetch the next value
        parameter_list_H(node->children[0], paramVector1);

        // 2. Call the function again to fetch the next value
        TypeExpression type; // to be fetched ⬆️
        parameter_declaration_H(node->children[2], type);

        // 3. Add the new parameter to the vector
        paramVector1.push_back(type);

        // 4. Pass the data up
        paramVector = paramVector1; // send syn_attr ⬆️
    }else{
        // Wrong Production
    }
    return;
}

/*
*/
void parameter_declaration_H(ASTNode* node, TypeExpression &type){
    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers declarator";
    std::string P2 = "declaration_specifiers abstract_declarator";
    std::string P3 = "declaration_specifiers";

    if(whichProduction != P1 || whichProduction != P2 || whichProduction != P3){
        // Wrong Production
        return;
    }

    // Code Common to all
    // 1. Call the function again to fetch the next value
    std::vector<std::string> valueVector;
    declaration_specifiers_H(node->children[0], valueVector);

    // Create a BaseInfo object
    BaseInfo *base = new BaseInfo();
    StorageClass inh_storageClass = StorageClass::UNKNOWN;
    int check = ProcessDecSpecifiers(valueVector, base, inh_storageClass);
    if (check == -1)
    {
        // SEMANTIC ERROR 🚨 : Invalid TypeSpecifier
    }
    if (inh_storageClass != StorageClass::UNKNOWN)
    {
        // SEMANTIC ERROR 🚨 : Storage Class NOT ALLOWED Here
    }

    // 2. Create a TypeExpression object
    TypeExpression inh_type;
    inh_type.levelStack.push(base);

    if(whichProduction == P1){

        // 3. Prepare syn_data to be fetched
        std::string varName; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        declarator_H(node->children[1], inh_type, varName, type1);


        // 3. Pass the data up
        type = type1; // send syn_attr ⬆️
        // varName is not used;
    }else if(whichProduction == P2){
        
        // 3. Prepare syn_data to be fetched
        TypeExpression type1; // to be fetched ⬆️

        abstract_declarator_H(node->children[1], inh_type, type1);


        // 3. Pass the data up
        type = type1; // send syn_attr ⬆️
    }else if(whichProduction == P3){
        // 3. Pass the data up
        type = inh_type; // send syn_attr ⬆️
    }
    
    else{
        // Wrong Production
    }
    return;
}

/*
*/

void abstract_declarator_H(ASTNode* node, TypeExpression inh_type, TypeExpression &type){
    std::string whichProduction = getProduction(node);
    std::string P1 = "pointer";
    std::string P2 = "direct_abstract_declarator";
    std::string P3 = "pointer direct_abstract_declarator";

    if(whichProduction == P1){
        TypeExpression type1 = inh_type;

        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo> ptrInfo;
        pointer_H(node->children[0], ptrInfo, ptrInfo);
        for(int i = 0; i < ptrInfo.size(); i++){
            PointerInfo info = ptrInfo[i];
            PointerInfo* infoPtr = &info;
            type1.levelStack.push(infoPtr);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }else if(whichProduction==P2){
        // 1. Call the function again to fetch the next value
        TypeExpression type1;
        direct_abstract_declarator_H(node->children[0], inh_type, type1);

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }else if(whichProduction==P3){
        TypeExpression type1 = inh_type;

        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo> ptrInfo;
        pointer_H(node->children[0], ptrInfo, ptrInfo);
        for(int i = 0; i < ptrInfo.size(); i++){
            PointerInfo info = ptrInfo[i];
            PointerInfo* infoPtr = &info;
            type1.levelStack.push(infoPtr);
        }
        // 2. Call the function again to fetch the next value
        TypeExpression type2;
        direct_abstract_declarator_H(node->children[1], type1, type2);

        // Pass the data up
        type = type2; // send syn_attr ⬆️
    }else{
        // Wrong Production
    }
    return;
}

void direct_abstract_declarator_H(ASTNode* node, TypeExpression inh_type, TypeExpression &type){
    std::string whichProduction = getProduction(node);
    std::string P1 = "LPAREN abstract_declarator RPAREN";

    if(whichProduction == P1){
        // 1. Call the function again to fetch the next value
        TypeExpression type1;
        abstract_declarator_H(node->children[1], inh_type, type1);

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }

    std::string P2 = "LSQUARE RSQUARE";
    std::string P3 = "LSQUARE constant_expression RSQUARE";
    std::string P4 = "direct_abstract_declarator LSQUARE RSQUARE";
    std::string P5 = "direct_abstract_declarator LSQUARE constant_expression RSQUARE";

    if(whichProduction == P2 || whichProduction == P3 || whichProduction == P4 || whichProduction == P5){

        int indexConstExpr = (whichProduction == P4) ? 1 : 2;
        std::string constValue = "NULL";
        if (whichProduction == P2 || whichProduction == P3)
        {
            // 1. Call the function again to fetch the next value
            constant_expression_H(node->children[indexConstExpr], constValue);
        }
        int constValue1 = (constValue == "NULL") ? 0 : std::stoi(constValue);

        ArrayInfo *info = new ArrayInfo();
        info->dimSize = constValue1;

        TypeExpression type1;
        inh_type.levelStack.push(info); // Push the new info to inh_type 
        if (whichProduction == P4 || whichProduction == P5)
        {
            // 1. Call the function again to fetch the next value
            TypeExpression type1;
            direct_abstract_declarator_H(node->children[0], inh_type, type1);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }

    std::string P6 = "LPAREN RPAREN";
    std::string P7 = "LPAREN parameter_type_list RPAREN";
    std::string P8 = "direct_abstract_declarator LPAREN RPAREN";
    std::string P9 = "direct_abstract_declarator LPAREN parameter_type_list RPAREN";

    if(whichProduction == P6 || whichProduction == P7 || whichProduction == P8 || whichProduction == P9){
        // 
        std::vector<TypeExpression> paramVector;
        if(whichProduction == P7 || whichProduction == P9){
            // 1. Call the function again to fetch the next value
            int index = (whichProduction == P7) ? 1 : 2;
            parameter_type_list_H(node->children[index], paramVector);
        }
        
        ParameterInfo *info = new ParameterInfo();
        info->paramsType = paramVector;

        TypeExpression type1;
        inh_type.levelStack.push(info); // Push the new info to inh_type
        if(whichProduction == P8 || whichProduction == P9){
            // 1. Call the function again to fetch the next value
            TypeExpression type1;
            direct_abstract_declarator_H(node->children[0], inh_type, type1);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else{
        // Wrong Production
    }
    return;
}

//=====================[ Expressions ]=========================================================================================

// 1. constant_expression
void constant_expression_H(ASTNode* node, std::string &value){
    value = "10";
    // [To be implemented] - Expression Evaluation
    return;
}

//=====================[ Control Flow ]=========================================================================================

// if else ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
// goto
// while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
// do while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
// for 
// switch case ✅(int char enum_const) ❌( float double   ptr function_name array_name struct_object union_object)
// until

// working principle
//1. check posiible types that can come in expression inside 
