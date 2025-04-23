#include "header.h"
#include "utility.h"

std::string NO_ARG_NAME = "NO_ARG_NAME";

//====================[ Declaration Handlers ]=========================================================================================

// ----- Main Declaration Handler
int declaration_H(ASTNode *node)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers SEMI_COLON";
    std::string P2 = "declaration_specifiers init_declarator_list SEMI_COLON";

    if (whichProduction != P1 && whichProduction != P2)
    {
        compilerError("Wrong Production in declaration_H");
        BUG_H;
        return BUG;
    }

    // Data on declaration - NO SYN or INH data of declaration [MIGHT be needed further down the line]

    // Code Common to P1 & P2
    //  1. Call the declaration_specifiers_H function to fetch syn_attr ⬆️ (P1 + P2)
    std::vector<std::string> valueVector; // syn_attr of declaration_specifiers 🟡
    int decl_check = declaration_specifiers_H(node->children[0], valueVector);
    PASS_THE_ERROR(decl_check);

    // 2. Prepare data to be sent down to next child
    // 2.1 Create a TypeExpression object
    TypeExpression inh_type;
    StorageClass inh_storageClass = StorageClass::NONE;
    int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
    if (check != OKAY)
    {
        if(check == WARNING){
            semanticWarning("Declaration Specifier - " + semanticMessage);
        }
        else{
        semanticError("Declaration Specifiers Combination is not valid - " + toString(valueVector));
        FAIL_H;
        return FAIL;
        }
    }

    if (whichProduction == P1)
    {
        // NOTHING to send
    }
    else if (whichProduction == P2)
    {
        // 3. inh_data ⬇️ | NO syn_data (init_declarator_list)
        int init_check = init_declarator_list_H(node->children[1], inh_type, inh_storageClass);
        PASS_THE_ERROR(init_check);
    }
    else
    {
        compilerError("Wrong Production in declaration_H");
        BUG_H;
        return BUG;
    }

    aptLOG("inh_type = " + toString(inh_type));

    EXIT_H

    return OKAY;
}

int declaration_list_H(ASTNode *node)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration";
    std::string P2 = "declaration_list declaration";

    if (whichProduction == P1)
    {
        // Call the declaration handler
        int d_check = declaration_H(node->children[0]);
        PASS_THE_ERROR(d_check);
    }
    else if (whichProduction == P2)
    {
        int dl_check = declaration_list_H(node->children[0]);
        PASS_THE_ERROR(dl_check);
        int dcl_check = declaration_H(node->children[1]);
        PASS_THE_ERROR(dcl_check);
    }
    else
    {
        // Wrong Production
        compilerError("Wrong production in declaration_list_H");
    }

    EXIT_H

    return OKAY;
}

// ----- Init Declarator Handler
int init_declarator_list_H(ASTNode *node, TypeExpression inh_type, StorageClass inh_storageClass)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "init_declarator";
    std::string P2 = "init_declarator_list COMMA init_declarator";

    aptLOG("inh_type = " + toString(inh_type));
    aptLOG("inh_storageClass = " + toString(inh_storageClass));

    if (whichProduction == P1)
    {
        // 1. We call the function again to fetch the next value
        int init_check = init_declarator_H(node->children[0], inh_type, inh_storageClass);
        PASS_THE_ERROR(init_check);
    }
    else if (whichProduction == P2)
    {
        // 1. We call the function again to fetch the next value
        int init_check = init_declarator_list_H(node->children[0], inh_type, inh_storageClass);
        PASS_THE_ERROR(init_check);

        // 2. We call the function again to fetch the next value
        int init_check2 = init_declarator_H(node->children[2], inh_type, inh_storageClass);
        PASS_THE_ERROR(init_check2);
    }
    else
    {
        // Wrong Production
        compilerError("Wrong production in init_declarator_list_H");
    }

    // No SYN data to add in A_PTree

    EXIT_H

    return OKAY;
}

int init_declarator_H(ASTNode *node, TypeExpression inh_type, StorageClass inh_storageClass)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "declarator";
    std::string P2 = "declarator ASSIGN initializer";

    aptLOG("inh_type = " + toString(inh_type));
    aptLOG("inh_storageClass = " + toString(inh_storageClass));

    std::string varName; // to be fetched ⬆️
    TypeExpression type; // to be fetched ⬆️

    std::string appendToName = "$"+std::to_string(SYM_TABLE.scopeNo);

    // Code Common to (P1, P2)
    if (whichProduction == P1 || whichProduction == P2)
    {
        // 0. Prepare syn_data to recieve

        int decl_check = declarator_H(node->children[0], inh_type, varName, type);
        PASS_THE_ERROR(decl_check);
        SYMBOL_TYPE symbolInsertedType = SYMBOL_TYPE::NONE;

        
        // At this point we have type of variable ready
        int varSize = width(type);
        CODE_BASE.addTAC(node, varName+appendToName, ALLOCATE, std::to_string(varSize), NO_ARG); // Allocate memory for the variable


        // 0 First we Handle Initializer
        if (whichProduction == P2)
        {
            // The inh_type must be INITIALIZABLE
            std::string inh_varName1 = varName;
            TypeExpression inh_type1 = type;

            Type topType = whatIsType(inh_type1);
            if (topType == Type::FUNCTION)
            {
                semanticError("Function cannot 🙂‍↔️ have initializer");
                FAIL_H;
                return FAIL;
            }
            else
            {
                TypeExpression initType;
                std::string initVarName;
                int initSize = -1;
                int initl_check = initializer_H(node->children[2], initType, initVarName, initSize);
                RECOVER_THE_ERROR(initl_check);
                if(initl_check == OKAY){
                    // Now we have got the initializer
                    // Check if it's a scalar initializer or not
                    Type whichType = whatIsType(inh_type1);
                    if (whichType == Type::ARRAY)
                    {
                        // TypeCheck - Initializer is not a scalar
                        Type initTopType = whatIsType(initType);
                        if (initTopType != Type::ARRAY && initTopType != Type::POINTER)
                        {
                            // SEMANTIC ERROR 🚨 : Initializer is not a scalar
                            semanticError("Initializer \"" + initVarName + "\" is a scalar but the variable is an array");
                            FAIL_H;
                            return FAIL;
                        }

                        // We send the initialization code to .data section
                        std::string initVarName2 = newTemp();

                        // TO adjust initVarName2 as per size of

                        std::string data = initVarName2 + " = " + initVarName;
                        CODE_BASE.data.push_back(data);                                      // Add to data section
                        CODE_BASE.addTAC(node, varName+appendToName, MEM_COPY, initVarName2, NO_ARG); // Assign it to the variable
                        // Change the name to the address
                    }
                    else
                {

                    // Check if the initializer is a scalar
                    Type topType = whatIsType(initType);
                    if (topType == Type::ARRAY)
                    {
                        // SEMANTIC ERROR 🚨 : Initializer is not a scalar
                        semanticError("Initializer \"" + initVarName + "\" is not a scalar");
                        FAIL_H;
                        return FAIL;
                    }

                    // Check if the types are resolvable
                    // 🆎 TypeCasting
                    TypeExpression source = initType;
                    TypeExpression dest = inh_type1;

                    bool isNum = isNumeric(source);
                    bool isNum2 = isNumeric(dest);
                    if (!(isNum && isNum2))
                    {
                        // Check if the types are same
                        int check = checkEquivalance(dest, source);
                        if (check != OKAY)
                        {
                            if (check == WARNING)
                            {
                                semanticWarning("Initialization type mismatch - Expected : \'" + toString(dest) + "\' Found : \'" + toString(source) + "\'");
                            }
                            else
                            {
                                semanticError("Initialization type mismatch - Expected : \'" + toString(dest) + "\' Found : \'" + toString(source) + "\'");
                                FAIL_H;
                                return FAIL;
                            }
                            
                        }
                        CODE_BASE.addTAC(node, varName+appendToName, ASSIGN_OP, initVarName, NO_ARG);
                    }
                    else
                    {
                        // Implicit Type Casting
                        int equal = ourEquivalent(source, dest);
                        if (equal != OKAY)
                        {
                            std::string castedVarNam = newTemp(); // ALLOCATED Added

                            // Allocate memory for the casted variable
                            int castedVarSize = width(dest);
                            CODE_BASE.addTAC(node, castedVarNam, ALLOCATE, std::to_string(castedVarSize), NO_ARG); // Allocate memory for the variable
                            
                            CODE_BASE.addTAC(node, castedVarNam, CAST, toString(dest), initVarName); // Cast it
                            initVarName = castedVarNam;                                              // Change the name to the address
                        }
                        CODE_BASE.addTAC(node, varName+appendToName, ASSIGN_OP, initVarName, NO_ARG); // Assign it to the variable
                    }
                }
                }
            }
        }

        /*


        */

        bool isValid = isValidTypeExpression(type);
        if (isValid == 0)
        {
            semanticError("😑 Invalid type expression ");
            FAIL_H;
            return FAIL;
        }

        // 1. Create Symbol (Variable or Function or typedef)
        Type whichType = whatIsType(type);
        if (inh_storageClass == StorageClass::TYPEDEF)
        {
            // This is a typedef definition
            TypeDefs *typedefDef = new TypeDefs();
            typedefDef->symbolName = varName;
            typedefDef->type = type;
            symbolInsertedType = SYMBOL_TYPE::TYPEDEF;

            
            if (whichProduction == P2)
            {
                semanticError("typedef cannot 🙂‍↔️ have initializer");
                FAIL_H;
                return FAIL;
            }

            // Add to symbol table
            GenericSymbol *sym = typedefDef;
            std::string typedefKey = TYPEDEF_PREFIX + varName;
            int insertCheck = SYM_TABLE.insert(symbolInsertedType, typedefKey, sym);
            if (insertCheck == INSERT_FAILURE)
            {
                semanticError("Symbol \"" + varName + "\" already 🫠 present in the current scope");
                FAIL_H;
                return FAIL;
            }
            else
            {
                // Okay
                aptLOG("typedef added ☞ \"" + varName + "\""); // 🌴 Adding syn_attr
            }
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
                semanticError("Function cannot 🙂‍↔️ be AUTO");
                // No need to exit
            }
            else if (inh_storageClass == StorageClass::STATIC)
            {
                semanticError(" ⚡️ TOO ADVANCED ⚡️ : static function not supported yet : It means that the function is only visible in the current file and not accessible outside");
            }
            // Add to symbol table
            GenericSymbol *sym = func;
            int insertCheck = SYM_TABLE.insert(symbolInsertedType, varName, sym);
            if (insertCheck == INSERT_FAILURE)
            {
                // Might be possilbe that function is declared again with same signature
                GenericSymbol *funcFound = nullptr;
                int lookupCheck = SYM_TABLE.lookup(varName, funcFound);
                // We check if their signature is same
                if (lookupCheck == LOOKUP_SUCCESS)
                {
                    // Function name already exists
                    Function *funcLocated = dynamic_cast<Function *>(funcFound);
                    bool sameSignature = true;

                    // Check if the function signature is same
                    LevelInfo *paramInfo = funcLocated->type.levelStack[0];
                    std::vector<TypeExpression> prevParamType = ((ParameterInfo *)paramInfo)->paramsType;
                    LevelInfo *currInfo = type.levelStack[0];
                    std::vector<TypeExpression> currParamType = ((ParameterInfo *)currInfo)->paramsType;

                    // We need a Exact match
                    if (prevParamType.size() != currParamType.size())
                    {
                        sameSignature = false;
                    }
                    else
                    {
                        for (int i = 0; i < prevParamType.size(); i++)
                        {
                            Type topType1 = whatIsType(prevParamType[i]);
                            Type topType2 = whatIsType(currParamType[i]);
                            bool exactMatch = checkEquivalance(prevParamType[i], currParamType[i]);
                            if(exactMatch != OKAY)
                            {
                                sameSignature = false;
                            }
                        }
                    }

                    if (!sameSignature)
                    {
                        semanticError("Function declaration \"" + varName + "\" signature mismatch with previous declaration");
                    }

                    aptLOG("Function \"" + varName + "\" already declared but with same signature");
                }
                else
                {
                    // BUG SHOULD NOT HAPPEN
                    compilerError("SYM_TABLE LookUp Failure : Function \"" + varName + "\" not found");
                    BUG_H;
                    return BUG;
                }
            }
            else
            {
                // Okay
                aptLOG("Function added ☞ \"" + varName + "\"");
            }
        }
        else // Variable [struct, union, primtive, enum, pointer, array]

        {
            Variable *var = new Variable();
            var->symbolName = varName;

            Type topType = whatIsType(type);

            if(isVoid(type) && topType == Type::VARIABLE){
                semanticError("Variable \"" + varName + "\" cannot be of type void");
                FAIL_H;
                return FAIL;
            }

            var->type = type;
            var->storageClass = inh_storageClass;
            symbolInsertedType = SYMBOL_TYPE::VARIABLE;
            // [📴 Offset to be filled]
            

            // Add to symbol table
            GenericSymbol *sym = var;
            int insertCheck = SYM_TABLE.insert(symbolInsertedType, varName, sym);
            if (insertCheck == INSERT_FAILURE)
            {
                semanticError("Symbol \"" + varName + "\" already 🫠 present in the current scope");
            }
            else
            {
                // Okay
                aptLOG("Variable added ☞ \"" + varName + "\""); // 🌴 Adding syn_attr
            }
        }

        
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in init_declarator_H");
        BUG_H;
        return BUG;
    }

    EXIT_H

    return OKAY;
}

// ----- TypeSpecifier + TypeQualifier + StorageClass -----
int declaration_specifiers_H(ASTNode *node, std::vector<std::string> &valueVector)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "storage_class_specifier";
    std::string P2 = "storage_class_specifier declaration_specifiers";
    std::string P3 = "type_specifier";
    std::string P4 = "type_specifier declaration_specifiers";
    std::string P5 = "type_qualifier";
    std::string P6 = "type_qualifier declaration_specifiers";

    aptLOG("inh_valueVector = " + toString(valueVector)); // 🌳 adding inh_attr

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4 && whichProduction != P5 && whichProduction != P6)
    {
        // Wrong Production
        compilerError("Wrong Production in declaration_specifiers_H");
        BUG_H;
        return BUG;
    }

    std::string value; // syn_attr from storage_class_specifier, type_specifier, type_qualifier 🟡
    // valueVector // syn_attr + inh_attr to/fro declaration_specifiers 🟡

    // Code Common to all productions (P1 & P2)
    // 1. We call the function again to fetch "value" from Last Productions
    if (whichProduction == P1 || whichProduction == P2)
    {

        int str_check = storage_class_specifier_H(node->children[0], value);
        PASS_THE_ERROR(str_check);
        valueVector.push_back(value);
    }
    else if (whichProduction == P3 || whichProduction == P4)
    {

        int ty_check = type_specifier_H(node->children[0], value);
        PASS_THE_ERROR(ty_check);
        valueVector.push_back(value);
    }
    else if (whichProduction == P5 || whichProduction == P6)
    {
        int tyq_check = type_qualifier_H(node->children[0], value);
        PASS_THE_ERROR(tyq_check);
        valueVector.push_back(value);
    }

    // Code Common to (P2, P4, P6)
    if (whichProduction == P2 || whichProduction == P4 || whichProduction == P6)
    {
        // Pass is for recursive declaration_specifiers_H
        int dclsp_check = declaration_specifiers_H(node->children[1], valueVector);
        PASS_THE_ERROR(dclsp_check);
    }

    aptLOG("syn_valueVector = " + toString(valueVector)); // 🌴 Adding syn_attr
    
    EXIT_H
    
    return OKAY;
}

int storage_class_specifier_H(ASTNode *node, std::string &value)
{
    ENTRY_H

    // Has only one Production
    int noOfChild = node->children.size();
    if (noOfChild != 1)
    {
        compilerError("Wrong Production in storage_class_specifier_H");
        BUG_H;
        return BUG;
    }

    value = node->children[0]->value;

    aptLOG("syn_value = " + value); // 🌴 Adding syn_attr

    EXIT_H

    return OKAY;
}

int type_qualifier_H(ASTNode *node, std::string &value)
{
    ENTRY_H

    // Has only one Production
    int noOfChild = node->children.size();
    if (noOfChild != 1)
    {
        compilerError("Wrong Production in type_qualifier_H");
        BUG_H;
        return BUG;
    }
    value = node->children[0]->value;

    aptLOG("syn_value = " + value); // 🌴 Adding syn_attr

    EXIT_H

    return OKAY;
}

int type_qualifier_list_H(ASTNode *node, std::vector<TypeQualifier> &typeQualifiers)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "type_qualifier";
    std::string P2 = "type_qualifier_list type_qualifier";

    aptLOG("inh_typeQualifiers = " + toString(typeQualifiers));

    if (whichProduction == P1)
    {
        // 1. We call the function again to fetch the next value
        TypeQualifier typeQualifier;
        std::string typeQualifierStr;
        int tyq_check = type_qualifier_H(node->children[0], typeQualifierStr);
        PASS_THE_ERROR(tyq_check);
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
            compilerError("Wrong Type qualifier");
            BUG_H;
            return BUG;
        }

        typeQualifiers.push_back(typeQualifier);
    }
    else if (whichProduction == P2)
    {
        // 1. We call the function again to fetch the next value
        int tyql_check = type_qualifier_list_H(node->children[0], typeQualifiers);
        PASS_THE_ERROR(tyql_check);

        // 2. We call the function again to fetch the next value
        TypeQualifier typeQualifier;
        std::string typeQualifierStr;
        int tyq_check = type_qualifier_H(node->children[0], typeQualifierStr);
        PASS_THE_ERROR(tyq_check);
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
            compilerError("Wrong Type qualifier");
            BUG_H;
            return BUG;
        }

        int tyq_check2 = type_qualifier_H(node->children[2], typeQualifierStr);
        PASS_THE_ERROR(tyq_check2);
        typeQualifiers.push_back(typeQualifier);
    }
    else
    {
        // Wrong Production
        compilerError("Wrong production in type_qualifier_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_typeQualifiers = " + toString(typeQualifiers)); // 🌴 Adding syn_attr

    EXIT_H

    return OKAY;
}

int type_specifier_H(ASTNode *node, std::string &value)
{
    ENTRY_H

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
            compilerError("Wrong Production in type_specifier_H");
            BUG_H;
            return BUG; 
        }
        value = node->children[0]->value;
    }

    // Struct or Union
    else if (whichProduction == P10)
    {
        // 1. Call the function again to fetch the next value
        int su_check = struct_or_union_specifier_H(node->children[0], value);
        PASS_THE_ERROR(su_check);
    }

    // Enum
    else if (whichProduction == P11)
    {
        // 1. Call the function again to fetch the next value
        int e_check = enum_specifier_H(node->children[0], value);
        PASS_THE_ERROR(e_check);
    }
    // Type Name
    else if (whichProduction == P12)
    {
        value = node->children[0]->value;
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG; 
    }

    aptLOG("syn_typeSpecifier = " + value); // 🌴 Adding syn_attr

    EXIT_H

    return OKAY;
}

int specifier_qualifier_list_H(ASTNode *node, std::vector<std::string> &valueVector)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "type_specifier specifier_qualifier_list";
    std::string P2 = "type_specifier";
    std::string P3 = "type_qualifier specifier_qualifier_list";
    std::string P4 = "type_qualifier";

    aptLOG("inh_valueVector = " + toString(valueVector));

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4)
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    // Code Common to all
    std::string value;                          // syn_attr from type_specifier or type_qualifier 🟡
    int typ_check = type_specifier_H(node->children[0], value); // syn_attr from type_specifier or type_qualifier
    PASS_THE_ERROR(typ_check);

    if (whichProduction == P1 || whichProduction == P3)
    {
        // 1. We call the function again to fetch the next value
        int spq_check = specifier_qualifier_list_H(node->children[1], valueVector);
        PASS_THE_ERROR(spq_check);
    }

    valueVector.push_back(value); // syn_attr from type_specifier or type_qualifier

    aptLOG("syn_value = " + toString(valueVector)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

// ----- STURCT & UNION -----
int struct_or_union_specifier_H(ASTNode *node, std::string &value)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY";
    std::string P2 = "struct_or_union LCURLY struct_declaration_list RCURLY";
    std::string P3 = "struct_or_union IDENTIFIER";

    aptLOG("inh_value = " + value);

    std::string recordStr = (node->children.size() > 0) ? node->children[0]->value : "";

    // Code Commong to P1 & P2
    if (whichProduction == P1 || whichProduction == P2)
    {
        // 0. Create a UserDType Unit [Incomplete Type]
        UserDType *userDType = new UserDType();
        RecordType recordType = (recordStr == "struct") ? RecordType::STRUCT : RecordType::UNION;
        userDType->isComplete = false;
        // 2. Add it to the symbol table [Incomplete Type]
        std::string recordID = (whichProduction == P1) ? node->children[1]->value : newRecordName();

        int check = SYM_TABLE.insertRecord(recordID, userDType);
        if (check == INSERT_FAILURE)
        {
            semanticError("RecordID \"" + recordID + "\" already 🫠 present in the current scope");
            FAIL_H;
            return FAIL;
        }
        else
        {
            // Okay
            aptLOG("RecordID \"" + recordID + "\" added to symbol table");
        }

        // 3. Call struct_declaration_list_H to fill the members
        std::map<std::string, TypeExpression> members; // fetch syn_attr ⬆️
        int position = (whichProduction == P1) ? 3 : 2;
        int strdl_check = struct_declaration_list_H(node->children[position], members);
        PASS_THE_ERROR(strdl_check);


        userDType->recordType = recordType;
        userDType->members = members;
        userDType->isComplete = true;
        
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
            semanticError("RecordID \"" + recordID + "\" not found");
            FAIL_H;
            return FAIL;
        }
        else
        {
            RecordType neededType = (recordStr == "struct") ? RecordType::STRUCT : RecordType::UNION;
            RecordType foundType = ((UserDType *)symbol)->recordType;
            if (neededType != foundType)
            {
                semanticError("RecordID \"" + recordID + "\" is not of type " + recordStr);
                FAIL_H;
                return FAIL;
            }
        }

        // 2. Pass a String up
        std::string scope = std::to_string(symbol->scopeNo);
        std::string typeSpecifier = recordStr + " " + recordID + " S" + scope;

        value = typeSpecifier; // send syn_attr ⬆️
    }
    else
    {
        compilerError("struct_or_union_specifier_H: Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_record = " + value); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

// struct_or_union_H is not needed

int struct_declaration_list_H(ASTNode *node, std::map<std::string, TypeExpression> &members)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_declaration";
    std::string P2 = "struct_declaration_list struct_declaration";

    aptLOG("inh_members = " + toString(members));

    if (whichProduction == P1)
    {
        std::map<std::string, TypeExpression> members1;
        // 1. Last Production will just exactly pass syn_attr(members) ⬆️
        int strd_check = struct_declaration_H(node->children[0], members1);
        PASS_THE_ERROR(strd_check);

        // 2. Add the members to the map
        members = members1; // Since Last Production
    }
    else if (whichProduction == P2)
    {
        // 1. Call the function again to fetch the next value
        std::map<std::string, TypeExpression> members1;
        int strdl_check = struct_declaration_list_H(node->children[0], members1);
        PASS_THE_ERROR(strdl_check);

        // 2. Call the function again to fetch the next value
        std::map<std::string, TypeExpression> members2;
        int strd_check = struct_declaration_H(node->children[1], members2);
        PASS_THE_ERROR(strd_check);

        // 3. Add the members to the map
        // Copy all from members2 to members1
        for (auto &unit : members2)
        {
            if (members1.count(unit.first))
            {
                semanticError("Member \"" + unit.first + "\" already present");
                FAIL_H;
                return FAIL;
            }
            members1[unit.first] = unit.second;
        }
        // 4. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else
    {
        compilerError("Wrong Production in struct_declaration_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_members = " + toString(members)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

int struct_declaration_H(ASTNode *node, std::map<std::string, TypeExpression> &members)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "specifier_qualifier_list struct_declarator_list SEMI_COLON";

    aptLOG("inh_members = " + toString(members));

    if (whichProduction != P1)
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }
    std::vector<std::string> valueVector;
    // 0. Call the function again to fetch the next value
    int spql_check = specifier_qualifier_list_H(node->children[0], valueVector);
    PASS_THE_ERROR(spql_check);

    // 1. Create a TypeExpression object
    TypeExpression inh_type;
    StorageClass inh_storageClass = StorageClass::NONE; // NOT ALLOWED ❌ [Will be syntax checked]
    int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
    if (check != OKAY)
    {
        if (check == WARNING)
        {
            semanticWarning("Declaration Specifier - " + semanticMessage);
        }
        else
        {
            semanticError("Invalid type specifier in struct/union - " + toString(valueVector));
            FAIL_H;
            return FAIL;
        }
    }

    // Pass the inh_data ⬇️ & fetch the syn_attr(members) ⬆️
    std::map<std::string, TypeExpression> syn_members;
    int strdl_check = struct_declarator_list_H(node->children[1], inh_type, syn_members);
    PASS_THE_ERROR(strdl_check);


    

    // Pass the members up
    members = syn_members; // send syn_attr ⬆️

    aptLOG("syn_members = " + toString(members)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

int struct_declarator_list_H(ASTNode *node, TypeExpression inh_type, std::map<std::string, TypeExpression> &members)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "struct_declarator";
    std::string P2 = "struct_declarator_list COMMA struct_declarator";

    aptLOG("inh_type = " + toString(inh_type));
    aptLOG("inh_members = " + toString(members));

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️

        // 0. Call the child's Handler
        int strd_check = struct_declarator_H(node->children[0], inh_type, varName, type);
        PASS_THE_ERROR(strd_check);

        // 1. Last Production for "members" variable
        std::map<std::string, TypeExpression> members1;

        // 2. Check if the varName is already present
        if (members.count(varName))
        {
            // SEMANTIC ERROR 🚨 : Member already present
            semanticError("Member already present.");
            FAIL_H;
            // return FAIL;//not needed
        }
        else{
            members1[varName] = type;
        }
        // 3. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        // 0. First child syn_data + inh_data passed ⬇️
        std::map<std::string, TypeExpression> members1;
        int strdl_check = struct_declarator_list_H(node->children[0], inh_type, members1);
        PASS_THE_ERROR(strdl_check);

        // 1. Second child syn_data to be fetched ⬆️ + inh_data passed ⬇️
        std::string varName; // to be fetched ⬆️
        TypeExpression type; // to be fetched ⬆️
        int strd_check = struct_declarator_H(node->children[2], inh_type, varName, type);
        PASS_THE_ERROR(strd_check);

        // 2. Check if the varName is already present
        if (members1.count(varName))
        {
            // SEMANTIC ERROR 🚨 : Member already present
            semanticError("Member already present.");
            FAIL_H;
            // return FAIL;//not needed

        }
        else{
            members1[varName] = type; // Add the new member ➕
        }

        // 3. Pass the members up
        members = members1; // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in struct_declarator_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_members = " + toString(members)); // 🌴 Adding syn_attr

    EXIT_H

    return OKAY;
}

int struct_declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "declarator";
    std::string P2 = "COLON constant_expression declarator";
    std::string P3 = "COLON constant_expression";

    aptLOG("inh_type = " + toString(inh_type));

    TypeExpression type0;

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the child's Handler
        int dcl_check = declarator_H(node->children[0], inh_type, varName1, type1);
        PASS_THE_ERROR(dcl_check);

        // 2. Pass the data up
        varName = varName1;
        type0 = type1;
    }
    else if (whichProduction == P2)
    { // ⚡️ Advance Feature ⚡️ - BitFields
        semanticError("BitField not supported yet | Declarator not specified");
        // FAIL_H;
        // return FAIL;
        // No Handler to call
        varName = "JUST_A_BITFIELD"; // To be fetched ⬆️
        type0 = inh_type; // Pass the inh_type as it is
    }
    else if (whichProduction == P3)
    { // ⚡️ Advance Feature ⚡️ - BitFields
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the child's Handler
        int dcl_check = declarator_H(node->children[1], inh_type, varName1, type1);
        PASS_THE_ERROR(dcl_check);

        // [IGNORED] - Constant Expression - BitField Size
        semanticError("BitField not supported yet | Ignoring the size");

        // 2. Pass the data up
        varName = varName1;
        type0 = type1;
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in struct_declarator_H");
        BUG_H;
        return BUG;
    }

    // Check if such a variable type is allowed a struct member
    // Must be able to find width of member
    int wid = width(type0);
    if (wid == -1)
    {
        semanticError("Invalid type specifier (width can't be found) in struct_declaration : " + toString(type0));
        FAIL_H;
        return FAIL;
    }
    type = type0; // Pass the type up

    aptLOG("syn_varName = " + varName);     // 🌴 Adding syn_attr
    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

// ----- ENUM ----
int enum_specifier_H(ASTNode *node, std::string &value)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "ENUM LCURLY enumerator_list RCURLY";
    std::string P2 = "ENUM IDENTIFIER LCURLY enumerator_list RCURLY";
    std::string P3 = "ENUM IDENTIFIER";

    aptLOG("inh_value = " + value);

    // Code Common to P1 & P2
    if (whichProduction == P1 || whichProduction == P2)
    {
        // 1. Create a UserDType Entry
        UserDType *userDType = new UserDType();
        userDType->isComplete = true; // Incomplete Type
        userDType->recordType = RecordType::ENUM;
        userDType->members = std::map<std::string, TypeExpression>(); // Empty Map // Enum won't use this

        // We must call the enumerator_list_H function but it's don't need anything from parent,

        // 2. Find Name of Enum - RecordID
        std::string recordID = (whichProduction == P2) ? node->children[1]->value : newRecordName();
        int lastInitValue = 0; // To be passed to enumerator_list_H

        // 3. Call the child's handler
        int index = (whichProduction == P1) ? 2 : 3;
        int enl_check = enumerator_list_H(node->children[index], recordID, lastInitValue);
        PASS_THE_ERROR(enl_check);

        // 4. Add it to the symbol table
        int check = SYM_TABLE.insertRecord(recordID, userDType);
        if (check == INSERT_FAILURE)
        {
            semanticError("RecordID \"" + recordID + "\" already 🫠 present in the current scope");
            FAIL_H;
            return FAIL;
        }

        aptLOG("\"" + recordID + "\" enumID added"); // 🌴 Adding syn_attr
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
            semanticError("Record not found");
            FAIL_H;
            return FAIL;
        }
        else
        {
            RecordType neededType = RecordType::ENUM;
            RecordType foundType = ((UserDType *)symbol)->recordType;
            if (neededType != foundType)
            {
                // SEMANTIC ERROR 🚨 : Type Mismatch
                semanticError("Type mismatch between " + toString(neededType) + " and " + toString(foundType));
            }
            scope = std::to_string(symbol->scopeNo);
        };
        // 2. Pass a String up
        std::string typeSpecifier = "enum " + recordID + " S" + scope;

        value = typeSpecifier; // send syn_attr ⬆️
        ;
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in enum_specifier_H");
        BUG_H;
        return BUG;

    }

    aptLOG("syn_value = " + value); // 🌴 Adding syn_attr

    EXIT_H

    return OKAY;
}

int enumerator_list_H(ASTNode *node, std::string recordID, int &lastInitValue)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "enumerator";
    std::string P2 = "enumerator_list COMMA enumerator";

    aptLOG("inh_recordID = " + recordID);
    aptLOG("inh_lastInitValue = " + toString(lastInitValue));

    if (whichProduction == P1)
    {
        // last production effect
        int currInitValue;

        // 0. syn_data to fetch ⬆️
        int explicitInitValue = 0;
        bool isExplicityInit = false;
        std::string varName; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        int en_check = enumerator_H(node->children[0], varName, explicitInitValue, isExplicityInit);
        PASS_THE_ERROR(en_check);

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
            semanticError("Enum Constant \"" + varName + "\" already present in the current scope");
            FAIL_H;
            return FAIL;
        }

        aptLOG("EnumConstant added ☞ \"" + varName + " = " + std::to_string(currInitValue) + "\""); // 🌴 Adding syn_attr

        // Send lastInitValue up
        lastInitValue = currInitValue + 1; // Increment the value for next enumerator
    }
    else if (whichProduction == P2)
    {
        // 0. First child syn_data + inh_data passed ⬇️
        int lastInitValue1;
        int enl_check = enumerator_list_H(node->children[0], recordID, lastInitValue1);
        PASS_THE_ERROR(enl_check);

        int currInitValue;

        // 0. syn_data to fetch ⬆️
        int explicitInitValue;
        bool isExplicityInit = false;
        std::string varName; // to be fetched ⬆️
        // 1. Call the function again to fetch the next value
        int en_check = enumerator_H(node->children[2], varName, explicitInitValue, isExplicityInit);
        PASS_THE_ERROR(en_check);

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
            semanticError("Enum Constant \"" + varName + "\" already present in the current scope");
            FAIL_H;
            return FAIL;
        }

        aptLOG("EnumConstant added ☞ \"" + varName + " = " + std::to_string(currInitValue) + "\""); // 🌴 Adding syn_attr

        // Send lastInitValue up
        lastInitValue = currInitValue + 1; // Increment the value for next enumerator
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in enumerator_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_lastInitValue = " + toString(lastInitValue)); // 🌴 Adding syn_attr

    EXIT_H;
    return OKAY;
}

int enumerator_H(ASTNode *node, std::string &varName, int &explicitInitValue, bool &isExplicityInit)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "IDENTIFIER ASSIGN constant_expression";

    aptLOG("inh_varName = " + varName);
    aptLOG("inh_explicitInitValue = " + toString(explicitInitValue));
    aptLOG("inh_isExplicityInit = " + toString(isExplicityInit));

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
        int c_check = constant_expression_H(node->children[2], varName1);
        PASS_THE_ERROR(c_check);

        int constValue = (varName1 != NOT_CONSTANT) ? std::stoi(varName1) : -1;
        if (varName1 == NOT_CONSTANT)
        {
            aptLOG("Constant Expression is not a constant");
        }
        explicitInitValue = constValue;
        isExplicityInit = true;

        // 3. Pass the data up
        // All data is passed up already
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in enumerator_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_varName = " + varName);                               // 🌴 Adding syn_attr
    aptLOG("syn_explicitInitValue = " + toString(explicitInitValue)); // 🌴 Adding syn_attr
    aptLOG("syn_isExplicityInit = " + toString(isExplicityInit));     // 🌴 Adding syn_attr
    
    EXIT_H;

    return OKAY;
}

// ----- Declarator Handlers -----
int declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "pointer direct_declarator";
    std::string P2 = "direct_declarator";

    aptLOG("inh_type = " + toString(inh_type));

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo *> ptrInfo = std::vector<PointerInfo *>();
        int ptr_check = pointer_H(node->children[0], ptrInfo, ptrInfo);
        PASS_THE_ERROR(ptr_check);

        // Update the inh_type
        for (auto &unit : ptrInfo)
        {
            PointerInfo *info = new PointerInfo(); // This will make a heap copy
            info->typeQualifiers = unit->typeQualifiers;
            inh_type.levelStack.push_back(info);
        }

        // 2. Call the function again to fetch the next value
        int ddcl_check = direct_declarator_H(node->children[1], inh_type, varName1, type1);
        PASS_THE_ERROR(ddcl_check);

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
        int ddcl_check = direct_declarator_H(node->children[0], inh_type, varName1, type1);
        PASS_THE_ERROR(ddcl_check);

        // 2. Pass the data up
        varName = varName1;
        type = type1;
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in declarator_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_varName = " + varName);     // 🌴 Adding syn_attr
    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

int direct_declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type)
{
    ENTRY_H

    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "LPAREN declarator RPAREN"; // More Levels

    std::string P3 = "direct_declarator LSQUARE constant_expression RSQUARE"; // Array
    std::string P4 = "direct_declarator LSQUARE RSQUARE";

    std::string P5 = "direct_declarator LPAREN parameter_type_list RPAREN"; // Function Signature
    std::string P6 = "direct_declarator LPAREN RPAREN";                     // Function call + Signature { Two Possibilities TO-THINK 🤨🤨🤨🤨 }
    std::string P7 = "direct_declarator LPAREN identifier_list RPAREN";     // Function Calls

    aptLOG("inh_type = " + toString(inh_type));

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
        inh_type.levelStack.push_back(info);

        int decl_check = declarator_H(node->children[1], inh_type, varName1, type1);
        PASS_THE_ERROR(decl_check);

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
            int c_check = constant_expression_H(node->children[2], value);
            PASS_THE_ERROR(c_check);
        }
        else{
            semanticError("Array width must be given during declaration.");
            FAIL_H;
            return FAIL;
        } 
        int size = (value == NOT_CONSTANT) ? -1 : std::stoi(value);
        if(value == NOT_CONSTANT)
        {
            aptLOG("Constant Expression is not a constant");
        }

        ArrayInfo *info = new ArrayInfo();
        info->dimSize = size;
        inh_type.levelStack.push_back(info);

        // 2. Call the function again to fetch the next value
        int ddcl_check = direct_declarator_H(node->children[0], inh_type, varName1, type1);
        PASS_THE_ERROR(ddcl_check);

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
            int ptl_check = parameter_type_list_H(node->children[2], paramVector, varName_list);
            PASS_THE_ERROR(ptl_check);
        }
        else
        {
            // Argument List is Empty
        }
        // Update the inh_type
        ParameterInfo *info = new ParameterInfo();

        if(!varName_list.empty()){
            if(varName_list[varName_list.size()-1] == VARADIC){
            // we have a varadic function
            info->isVaradic = true;
            varName_list.pop_back();
            // paramVector.pop_back();
            }
        }

        
        info->paramsType = paramVector;
        info->paramsName = varName_list;

        inh_type.levelStack.push_back(info);

        // 2. Call the function again to fetch the next value
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        int ddcl_check = direct_declarator_H(node->children[0], inh_type, varName1, type1);
        PASS_THE_ERROR(ddcl_check);

        // 3. Pass the data up
        varName = varName1;
        type = type1;
    }
    else if (whichProduction == P7)
    {
        // What is this doing? [🧠 ToThink]
        // MOST LIKEY - ERROR: a parameter list without types is only allowed in a function definition
        semanticError("a function definition without a prototype is deprecated in all versions of C and is not supported in C23[-Wdeprecated - non - prototype]")
        FAIL_H;
        return FAIL;
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in direct_declarator_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_varName = " + varName); // 🌴 Adding syn_attr

    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

// ----- Pointer Handlers -----
int pointer_H(ASTNode *node, std::vector<PointerInfo *> inh_ptrInfo, std::vector<PointerInfo *> &ptrInfo)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "STAR";
    std::string P2 = "STAR type_qualifier_list";
    std::string P3 = "STAR pointer";
    std::string P4 = "STAR type_qualifier_list pointer";

    aptLOG("inh_ptrInfo = " + toString(inh_ptrInfo));

    if (whichProduction == P1)
    {
        // Last Production 🚦 - Need to rotate
        PointerInfo *info = new PointerInfo(); // Create a new PointerInfo
        ptrInfo = inh_ptrInfo;                 // rotate inh_PtrInfo to syn_PtrInfo ☯️
        ptrInfo.push_back(info);               // Push the new info to inh_ptrInfo1 to pass
    }
    else if (whichProduction == P2)
    {
        //
        std::vector<TypeQualifier> typeQualifiers; // Recieve syn_attr ⬆️
        int tql_check = type_qualifier_list_H(node->children[1], typeQualifiers);
        PASS_THE_ERROR(tql_check);

        // Last Production 🚦 - Need to rotate
        PointerInfo *info = new PointerInfo(); // Create a new PointerInfo
        info->typeQualifiers = typeQualifiers;

        ptrInfo = inh_ptrInfo; // rotate inh_PtrInfo to syn_PtrInfo ☯️
        ptrInfo.push_back(info);
    }
    else if (whichProduction == P3)
    {
        std::vector<PointerInfo *> ptrInfo1 = std::vector<PointerInfo *>();
        std::vector<PointerInfo *> inh_ptrInfo1 = inh_ptrInfo;

        PointerInfo *info = new PointerInfo(); // Create a new PointerInfo
        inh_ptrInfo1.push_back(info);          // Push the new info to inh_ptrInfo1 to pass

        int p_check = pointer_H(node->children[1], inh_ptrInfo1, ptrInfo1);
        PASS_THE_ERROR(p_check);

        ptrInfo = ptrInfo1; // Pass syn_attr ⬆️
    }
    else if (whichProduction == P4)
    {

        std::vector<PointerInfo *> ptrInfo1 = std::vector<PointerInfo *>();
        std::vector<PointerInfo *> inh_ptrInfo1 = inh_ptrInfo;

        std::vector<TypeQualifier> typeQualifiers; // Recieve syn_attr ⬆️
        int tql_check = type_qualifier_list_H(node->children[1], typeQualifiers);
        PASS_THE_ERROR(tql_check);

        PointerInfo *info = new PointerInfo(); // Create a new PointerInfo
        info->typeQualifiers = typeQualifiers;
        inh_ptrInfo1.push_back(info); // Push the new info to inh_ptrInfo1 to pass

        int ptr_check = pointer_H(node->children[2], inh_ptrInfo1, ptrInfo1);
        PASS_THE_ERROR(ptr_check);

        ptrInfo = ptrInfo1; // Pass syn_attr ⬆️
    }
    else
    {
        compilerError("Wrong Production in pointer_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_ptrInfo = " + toString(ptrInfo)); // 🌴 Adding syn_attr

    EXIT_H;

    return OKAY;
}

// ----- Parameter Handlers -----
int parameter_type_list_H(ASTNode *node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "parameter_list";
    std::string P2 = "parameter_list COMMA ELLIPSIS";

    aptLOG("inh_paramVector = " + toString(paramVector));
    aptLOG("inh_varName_list = " + toString(varName_list));

    if (whichProduction == P1 || whichProduction == P2)
    {
        // 1. Call the function again to fetch the next value
        std::vector<TypeExpression> paramVector1;
        std::vector<std::string> varName_list1;

        int prml_check = parameter_list_H(node->children[0], paramVector1, varName_list1);
        PASS_THE_ERROR(prml_check);

        // 2. Check if the ELLIPSIS is present
        if (whichProduction == P2)
        {
            // 3. Add the ELLIPSIS to the paramVector
            TypeExpression ellipsisType = TypeExpression();
            varName_list1.push_back(VARADIC); // Add the ELLIPSIS to the varName_list
        }

        // 4. Pass the data up
        paramVector = paramVector1; // send syn_attr ⬆️
        varName_list = varName_list1; // send syn_attr ⬆️

    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in parameter_type_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_paramVector = " + toString(paramVector));
    aptLOG("syn_varName_list = " + toString(varName_list));

    EXIT_H;

    return OKAY;
}

int parameter_list_H(ASTNode *node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "parameter_declaration";
    std::string P2 = "parameter_list COMMA parameter_declaration";

    aptLOG("inh_paramVector = " + toString(paramVector));
    aptLOG("inh_varName_list = " + toString(varName_list));

    if (whichProduction == P1)
    {
        // Prepare syn_data to recieve
        TypeExpression type1; // to be fetched ⬆️
        std::string varName1;
        int prmd_check = parameter_declaration_H(node->children[0], type1, varName1);
        PASS_THE_ERROR(prmd_check);

        std::vector<TypeExpression> newParamVector;
        newParamVector.push_back(type1);
        std::vector<std::string> varName_list1 = std::vector<std::string>();
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
        int prml_check = parameter_list_H(node->children[0], paramVector1, varName_list1);
        PASS_THE_ERROR(prml_check);

        // 2. Call the function again to fetch the next value
        TypeExpression type;  // to be fetched ⬆️
        std::string varName1; // to be fetched ⬆️

        int prmd_check = parameter_declaration_H(node->children[2], type, varName1);
        PASS_THE_ERROR(prmd_check);

        // 3. Add the new parameter to the vector
        paramVector1.push_back(type);
        varName_list1.push_back(varName1);

        // 4. Pass the data up
        paramVector = paramVector1; // send syn_attr ⬆️
        varName_list = varName_list1;
    }
    else
    {
        compilerError("Wrong Production in parameter_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_type = " + toString(paramVector));          // 🌴 Adding syn_attr
    aptLOG("syn_varName_list = " + toString(varName_list)); // 🌴 Adding syn_attr

    EXIT_H;

    return  OKAY;
}

int parameter_declaration_H(ASTNode *node, TypeExpression &type, std::string &varName)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "declaration_specifiers declarator";
    std::string P2 = "declaration_specifiers abstract_declarator";
    std::string P3 = "declaration_specifiers";

    aptLOG("inh_type = " + toString(type));
    aptLOG("inh_varName = " + varName);

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3)
    {
        // Wrong Production
        compilerError("Wrong Production in parameter_declaration_H");
        BUG_H;
        return BUG;
    }

    // Code Common to all
    // 1. Call the function again to fetch the next value
    std::vector<std::string> valueVector;
    int dcls_check = declaration_specifiers_H(node->children[0], valueVector);
    PASS_THE_ERROR(dcls_check);

    // Create a BaseInfo object
    TypeExpression inh_type;
    StorageClass inh_storageClass = StorageClass::NONE;
    int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
    if (check != OKAY)
    {
        if (check == WARNING)
        {
            semanticWarning("Declaration Specifier - " + semanticMessage);
        }
        else
        {
            semanticError("Invalid TypeSpecifier for parameters - " + toString(valueVector));
            FAIL_H;
            return FAIL;
        }

    }
    if (inh_storageClass != StorageClass::NONE)
    {   
        semanticError("Invalid StorageClass ");
    }

    if (whichProduction == P1)
    {
        aptLOG("Production 1");
        // 3. Prepare syn_data to be fetched
        std::string varName1; // to be fetched ⬆️
        TypeExpression type1; // to be fetched ⬆️
        int dcl_check = declarator_H(node->children[1], inh_type, varName1, type1);
        PASS_THE_ERROR(dcl_check);

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
        int adcl_check = abstract_declarator_H(node->children[1], inh_type, type1);
        PASS_THE_ERROR(adcl_check);
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
        // aptLOG("Production WRONG");
        // Wrong Production
        compilerError("Wrong Production in parameter_declaration_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr
    aptLOG("syn_varName = " + varName);     // 🌴 Adding syn_attr

    EXIT_H;
    return OKAY;
}

// ----- Identifier List Handlers -----
int identifier_list_H(ASTNode *node, std::vector<std::string> &idList)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "identifier_list COMMA IDENTIFIER";

    aptLOG("inh_idList = " + toString(idList));

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
        int idl_check = identifier_list_H(node->children[0], idList);
        PASS_THE_ERROR(idl_check);

        // 1. Second child syn_data to be fetched ⬆️
        std::string idName = node->children[2]->value;

        // 2. Pass the data up
        idList.push_back(idName); // send syn_attr ⬆️
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in identifier_list_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_idList = " + toString(idList)); // 🌴 Adding syn_attr

    EXIT_H
    return OKAY;
}

//----- type name Handlers -----
int type_name_H(ASTNode *node, TypeExpression &type)
{
    ENTRY_H
    std::string whichProduction = getProduction(node);
    std::string P1 = "specifier_qualifier_list";
    std::string P2 = "specifier_qualifier_list abstract_declarator";

    aptLOG("inh_type = " + toString(type));

    if (whichProduction == P1)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::vector<std::string> valueVector;
        // 1. Call the function again to fetch the next value
        int sql_check = specifier_qualifier_list_H(node->children[0], valueVector);
        PASS_THE_ERROR(sql_check);

        // 2. Create a TypeExpression object
        TypeExpression inh_type;
        ;
        StorageClass inh_storageClass = StorageClass::NONE; // [Syntax Checked]
        int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
        if (check != OKAY)
        {
            if (check == WARNING)
            {
                semanticWarning("Declaration Specifier - " + semanticMessage);
            }
            else
            {
                semanticError("Invalid TypeSpecifier for TypeName - " + toString(valueVector));
                FAIL_H;
                return FAIL;
            }
        }
        if (inh_storageClass != StorageClass::NONE)
        {
            semanticError("StorageClass not allowed in TypeName");
            FAIL_H;
            return FAIL;
        }

        // Pass the data up
        type = inh_type; // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::vector<std::string> valueVector;
        // 1. Call the function again to fetch the next value
        int sql_check = specifier_qualifier_list_H(node->children[0], valueVector);
        PASS_THE_ERROR(sql_check);

        // 2. Create a TypeExpression object
        TypeExpression inh_type;
        StorageClass inh_storageClass = StorageClass::NONE;
        int check = ProcessDecSpecifiers(valueVector, inh_type, inh_storageClass);
        if (check != OKAY)
        {
            if (check == WARNING)
            {
                semanticWarning("Declaration Specifier - " + semanticMessage);
            }
            else
            {
                semanticError("Invalid TypeSpecifier for TypeName - " + toString(valueVector));
                FAIL_H;
                return FAIL;
            }
        }

        // 4. Call the function again to fetch the next value
        int adcl_check = abstract_declarator_H(node->children[1], inh_type, type);
        PASS_THE_ERROR(adcl_check);
    }
    else
    {
        // Wrong Production
        compilerError("Wrong Production in type_name_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H
    return OKAY;
}

// ----- Abstract Declarator Handlers -----
int abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "pointer";
    std::string P2 = "direct_abstract_declarator";
    std::string P3 = "pointer direct_abstract_declarator";

    aptLOG("inh_type = " + toString(inh_type));

    if (whichProduction == P1)
    {
        TypeExpression type1 = inh_type;
        aptLOG("Production 1");
        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo *> ptrInfo = std::vector<PointerInfo *>();
        int p_check = pointer_H(node->children[0], ptrInfo, ptrInfo);
        PASS_THE_ERROR(p_check);
        for (int i = 0; i < ptrInfo.size(); i++)
        {
            PointerInfo *info = ptrInfo[i];
            type1.levelStack.push_back(info);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else if (whichProduction == P2)
    {
        aptLOG("Production 2");
        // 1. Call the function again to fetch the next value
        TypeExpression type1;
        int dadcl_check = direct_abstract_declarator_H(node->children[0], inh_type, type1);
        PASS_THE_ERROR(dadcl_check);

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else if (whichProduction == P3)
    {
        TypeExpression type1 = inh_type;
        aptLOG("Production 3");
        // 1. Call the function again to fetch the next value
        std::vector<PointerInfo *> ptrInfo = std::vector<PointerInfo *>();
        int p_check = pointer_H(node->children[0], ptrInfo, ptrInfo);
        PASS_THE_ERROR(p_check);
        for (int i = 0; i < ptrInfo.size(); i++)
        {
            PointerInfo *info = ptrInfo[i];
            PointerInfo *infoPtr = info;
            type1.levelStack.push_back(infoPtr);
        }
        // 2. Call the function again to fetch the next value
        TypeExpression type2;
        int dadcl_check = direct_abstract_declarator_H(node->children[1], type1, type2);
        PASS_THE_ERROR(dadcl_check);

        // Pass the data up
        type = type2; // send syn_attr ⬆️
    }
    else
    {
        compilerError("Wrong Production in abstract_declarator_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;
    return OKAY;
}

int direct_abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type)
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

    aptLOG("inh_type = " + toString(inh_type));

    if (whichProduction == P1)
    {
        aptLOG("Production 1");
        // 1. Call the function again to fetch the next value
        TypeExpression type1 = inh_type;
        ParenthesisInfo *info = new ParenthesisInfo();
        inh_type.levelStack.push_back(info);
        int adcl_check = abstract_declarator_H(node->children[1], inh_type, type1);
        PASS_THE_ERROR(adcl_check);

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
            int cex_check = constant_expression_H(node->children[indexConstExpr], constValue);
            PASS_THE_ERROR(cex_check);
        }
        int constValue1 = (constValue == NOT_CONSTANT) ? -1 : std::stoi(constValue);
        if(constValue == NOT_CONSTANT)
        {
            aptLOG("Constant Expression is not a constant");
        }

        ArrayInfo *info = new ArrayInfo();
        info->dimSize = constValue1;

        inh_type.levelStack.push_back(info); // Push the new info to inh_type
        TypeExpression type1 = inh_type;
        if (whichProduction == P4 || whichProduction == P5)
        {
            // 1. Call the function again to fetch the next value
            int dadcl_check = direct_abstract_declarator_H(node->children[0], inh_type, type1);
            PASS_THE_ERROR(dadcl_check);
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
            int ptl_check = parameter_type_list_H(node->children[index], paramVector, varName_list);
            PASS_THE_ERROR(ptl_check);    
        }

        ParameterInfo *info = new ParameterInfo();
        info->paramsType = paramVector;
        info->paramsName = varName_list;

        if (varName_list.empty())
        {
            info->isAbstract = true;
        }

        inh_type.levelStack.push_back(info); // Push the new info to inh_type
        TypeExpression type1 = inh_type;
        if (whichProduction == P8 || whichProduction == P9)
        {
            // 1. Call the function again to fetch the next value
            int dadcl_check = direct_abstract_declarator_H(node->children[0], inh_type, type1);
            PASS_THE_ERROR(dadcl_check);
        }

        // Pass the data up
        type = type1; // send syn_attr ⬆️
    }
    else
    {
        compilerError("Wrong Production in direct_abstract_declarator_H");
        BUG_H;
        return BUG;
    }

    aptLOG("syn_type = " + toString(type)); // 🌴 Adding syn_attr

    EXIT_H;
    return OKAY;
}

//---- Initializers ---------
int initializer_H(ASTNode *node, TypeExpression &type, std::string &varName ,int &size)
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
        int aex_check = assignment_expression_H(node->children[0], "NONE", varName1, type1, valuetype1, valueSpace1);
        PASS_THE_ERROR(aex_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 🅱️ TypeChecking
        // Logic - If Base -> If both are numeric(+enum/enumConstats) -> typecast arg to resultType and assign (IRCode Needed)
        // Logic - If Base -> If both are Record(union/struct) Object -> MUST be EXACT match else ERROR
        // Logic - If both (POINTER,FUNCTION,ARRAY) -> IGNORE BELOW LEVEL -> just assign varName and returnType = resultType
        // 🆎 TypeCasting will be done by init-declarator

        std::string unitValue = varName1;

        // 🤮 Return Value 🤮
        varName = unitValue; // Pass the data up
        type = type1;        // Pass the data up
        size = 1;           // Pass the data up

    }
    else if (whichProduction == P2 || whichProduction == P3)
    {
        // 0. Prepare syn_data to be fetched ⬆️
        std::string varName1 = "NULL"; // to be fetched ⬆️
        TypeExpression type1;          // to be fetched ⬆️
        int size1 = -1;               // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        int initl_check = initializer_list_H(node->children[1], type1, varName1,size1);
        PASS_THE_ERROR(initl_check);

        std::string unitvalue = "[ " + varName1 + " ]";
        // 2. Pass the data up
        varName = unitvalue; // Pass the data up

        // For Type add a arrayLevel
        ArrayInfo *info = new ArrayInfo();
        info->dimSize = size1;
        type1.levelStack.push_back(info);
        type = type1; // Pass the data up
        size = 1;
    }
    else
    {
        compilerError("Wrong Production in initializer_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);   
    aptLOG("⏫ type = " + toString(type)); 
    aptLOG("⏫ size = " + toString(size)); 

    EXIT_H;
    return OKAY;
}

int initializer_list_H(ASTNode *node, TypeExpression &type, std::string &varName ,int &size)
{
    ENTRY_H;
    std::string P1 = "initializer";
    std::string P2 = "initializer_list COMMA initializer";

    std::string whichProduction = getProduction(node);

    if(whichProduction == P1)
    {
        // 0. syn_data to fetch ⬆️
        std::string varName1 = "NULL"; // to be fetched ⬆️
        TypeExpression type1;          // to be fetched ⬆️
        int size1 = -1; // to be fetched ⬆️

        // 1. Call the function again to fetch the next value
        int init_check = initializer_H(node->children[0], type1, varName1,size1);
        PASS_THE_ERROR(init_check);

        // last Name so no issue
        std::string unitValue = varName1;
        type = type1;
        varName = unitValue; // Pass the data up
        size = size1; // Pass the data up
    }
    else if (whichProduction == P2)
    {
        // 0. First child syn_data + inh_data passed ⬇️
        std::string varName1 = "NULL"; // to be fetched ⬆️
        TypeExpression type1;          // to be fetched ⬆️
        int size1 = -1; // to be fetched ⬆️
        int initl_check = initializer_list_H(node->children[0], type1, varName1,size1);
        PASS_THE_ERROR(initl_check);

        // 1. Second child syn_data to be fetched ⬆️
        std::string varName2 = "NULL"; // to be fetched ⬆️
        TypeExpression type2;          // to be fetched ⬆️

        // TYPE RESOLUTION based TypeChecking [TODO]

        // TypeChecking of Resolution
        int size2 = -1;
        int init_check = initializer_H(node->children[2], type2, varName2,size2);
        PASS_THE_ERROR(init_check);

        std::string unitValue = varName1 + "," + varName2;
        type = type1;
        varName = unitValue; // Pass the data up
        size = size1 + size2; // Pass the data up
    }
    else
    {
        compilerError("Wrong Production in initializer_list_H");
        BUG_H;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ size = " + toString(size));

    EXIT_H;
    return OKAY;
}
