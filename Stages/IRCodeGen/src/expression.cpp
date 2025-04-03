#include "header.h"
#include "utility.h"

//====================[ Expressions Handler ]=========================================================================================

ASTNode *currentNode = nullptr;

//--- Constatn Expression Handler

// 1. constant_expression
void constant_expression_H(ASTNode *node, std::string &value)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "conditional_expression";

    A_PTree node->addAttribute("inh_value = " + value);
    if (whichProduction == P1)
    {
        // 0. syn_data to fetch ⬆️
        std::string value1 = ""; // to be fetched ⬆️
        TypeExpression type1;    // to be fetched ⬆️
        VALUE_TYPE valuetype1;
        SPACE valueSpace1;
        // 1. Call the function again to fetch the next value
        conditional_expression_H(node->children[0], "NONE", value1, type1, valuetype1, valueSpace1);
        PASS_THE_ERROR(value1);

        // 🅱️ TypeCheck for const [📍📍📍TODO]

        // 2. Pass the data up
        value = value1; // send syn_attr ⬆️
    }
    else
    {
        ERROR_EXIT_H;
        // Setup Dummy Data
        value = "0"; // send syn_attr ⬆️
        return;
    }

    EXIT_H;
}

//--- Expression Handler
void expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "assignment_expression";
    std::string P2 = "expression COMMA assignment_expression";

    if (!node)
    {
        ERROR_EXIT_H;
        // Setup Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("😵‍💫 whereToSendString = " + inh_whereToSendString);
    // A_PTree node->addAttribute("⏬ " + toString(type));
    // A_PTree node->addAttribute("⏬ " + toString(valueType));
    // A_PTree node->addAttribute("⏬  " + toString(valueSpace));
    // A_PTree node->addAttribute("⏬  varName = " + varName);

    if (whichProduction == P1)
    {
        // Call the assignment_expression handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        assignment_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // Pass the data up
        varName = varName1;
        type = type1;
        valueType = valueType1;
        valueSpace = valueSpace1;
    }
    else if (whichProduction == P2)
    {
        // Call the expression handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // Call the assignment_expression handler
        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        assignment_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // Pass the data from expression1 up
        varName = varName2;
        type = type2;
        valueType = valueType2;
        valueSpace = valueSpace2;

        // Semantic Warning
        semanticLOG.push_back("Warning: Expression \"" + varName1 + "\"'s result is not used");
    }
    else
    {
        ERROR_EXIT_H;
        return;
    }

    A_PTree node->addAttribute("😵‍💫 varName    = " + varName);
    A_PTree node->addAttribute("😵‍💫 type       = " + toString(type));
    A_PTree node->addAttribute("😵‍💫 valueType  = " + toString(valueType));
    A_PTree node->addAttribute("😵‍💫 valueSpace = " + toString(valueSpace));
    // A_PTree node->addAttribute("😵‍💫 inh_whereToSendString = " + inh_whereToSendString);

    EXIT_H;
}

//--- Primary Expression Handler
void primary_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "CONSTANT";
    std::string P3 = "STRING_LITERAL";
    std::string P4 = "LPAREN expression RPAREN";

    // A_PTree node->addAttribute("⏬  whereToSendString = " + inh_whereToSendString);
    // A_PTree node->addAttribute("⏬  varName = " + varName);
    // A_PTree node->addAttribute("⏬ " + toString(type));
    // A_PTree node->addAttribute("⏬ "+ toString(valueType));
    // A_PTree node->addAttribute("⏬  " + toString(valueSpace));

    if (whichProduction == P1)
    {
        // Get Name of Identifier
        std::string varName1 = node->children[0]->value;

        TypeExpression type0; // Find Type of Identifier from Symbol Table

        // Look into the SymbolTable and Find it's
        GenericSymbol *symbol = nullptr;
        int lookupCheck = SYM_TABLE.lookup(varName1, symbol);
        if (lookupCheck == LOOKUP_FAILURE)
        {
            semanticLOG.push_back("Error: Identifier \"" + varName1 + "\" not found in symbol table");
            varName = varName1;
            type = type0;
            valueType = VALUE_TYPE::UNKNOWN;
            valueSpace = SPACE::UNKNOWN_SPACE;
            // SEMANTIC ERROR 🚨 : Identifier not found
            ERROR_EXIT_H; // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }
        else
        {
            // To Check what all possible symbols are allowed
            // - Variable + EnumConstant + Function ✅ | ToCheck 🔍 for + TypeDef + RecordType
            SYMBOL_TYPE symbolType = symbol->symbolType;
            if (symbolType == SYMBOL_TYPE::VARIABLE)
            {
                // It's a variable Symbol
                type0 = ((Variable *)symbol)->type;
            }
            else if (symbolType == SYMBOL_TYPE::ENUM_CONSTANT)
            {
                // Create a TypeExpression for Enum Constant
                TypeExpression tempType;
                BaseInfo *base = new BaseInfo();
                base->baseType = ENUM_CONSTANT;
                tempType.levelStack.push(base);
                type0 = tempType;
            }
            else if (symbolType == SYMBOL_TYPE::FUNCTION)
            {
                type0 = ((Function *)symbol)->type;
            }
            else
            {
                // SEMANTIC ERROR 🚨 : Not a variable or enum constant
                semanticLOG.push_back("Error: Identifier \"" + varName1 + "\" is not a variable or enum constant");
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }
        }

        // Now that we have type of symbol ready

        Type whichType = whatIsType(type0); // This tell me about TypeExpression

        SPACE val0Space = getSpace(type0); // struct/union or array 🤯

        VALUE_TYPE val0Type = getValueType(type0); // Set Correctly

        bool isConst = isConstant(type0);

        if (val0Space == SPACE::ADDRESS_SPACE)
        {
            // If in address space we need to deal with offset

            // Space 🚀Change 🔖IR Code
            std::string address = newTemp();
            // std::string id_offset = std::to_string(((Variable *)symbol)->offset);
            std::string id_offset = varName1 + ".offset";

            CODE_BASE.addTAC(node, address, "=", id_offset, NO_ARG);

            varName1 = address; // Change the name to the address
        }
        else if (val0Space == SPACE::VALUE_SPACE)
        {
            // handle special case of enum
            if (whichType == Type::ENUM_CONSTANT)
            {
                // Handling Special Case of VALUE_SPACE (compile time constant)
                EnumConstant *enumVar = dynamic_cast<EnumConstant *>(symbol);
                varName1 = std::to_string(enumVar->value);
            }
            else
            {
                varName1 = symbol->symbolName; // For Variable their name is same
                // For Function the label is same as the name
            }
        }
        else
        {
            // SEMANTIC ERROR 🚨 : Unknown Space
            semanticLOG.push_back("Error: Unknown Space for Identifier \"" + varName1 + "\"");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // Pass all syn_attribute to up
        varName = varName1;
        type = type0;
        valueType = val0Type;
        valueSpace = val0Space;
    }
    else if (whichProduction == P2)
    {

        varName = node->children[0]->value;

        // 🟡 type
        // [ToWrite a Function that takes a string constant and find it's type] & [string format number]
        TypeExpression type0;
        std::string finalValue = "ToBeFetched"; // To be fetched from constant_expression
        int check = ProcessConstants(varName, type0, finalValue);
        if (check != OKAY)
        {
            // SEMANTIC ERROR 🚨 : Error in ProcessContants
            semanticLOG.push_back("Error: Error in ProcessContants CONSTANT-\"" + varName + "\"");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }
        type = type0;

        // 🟡 VarName is the constant's value itself
        varName = finalValue; // Change the name to the value

        // 🟡 valueType
        Type whichType = whatIsType(type0);

        // 🟡 valueSpace
        SPACE val0Space = getSpace(type0);

        VALUE_TYPE val0Type = getValueType(type0); // Set Correctly

        // Pass the data up
        valueSpace = val0Space; // Set the value space
        valueType = val0Type;   // Set the value type
    }
    else if (whichProduction == P3)
    { // ⚡️ Advance Feature ⚡️
        std::string strValue = node->children[0]->value;

        // 🟡 type - Create a TypeExpression char *
        TypeExpression type0;
        BaseInfo *base = new BaseInfo();
        base->baseType = TYPE_CHAR;
        if (inh_whereToSendString == RO_DATA)
        {
            base->typeQualifiers.push_back(TypeQualifier::CONST); // Char* are const
        }
        type0.levelStack.push(base);
        PointerInfo *ptr = new PointerInfo();
        type0.levelStack.push(ptr);

        type = type0;

        // 🟡 valueSpace -
        valueSpace = SPACE::ADDRESS_SPACE; // String literals are in address space

        // 🟡 valueType
        valueType = VALUE_TYPE::NM_LVALUE; // String literals are not modifiable lvalue

        // 🟡 varName + 🔖IRCode Gen

        // Check if string to be sent in .rodata or .data
        if (inh_whereToSendString == RO_DATA)
        {
            // Add to .rodata
            std::string label = CODE_BASE.newLabel();

            CODE_BASE.addTAC(node, label, LABEL, strValue, NO_ARG);
            std::string address = newTemp();

            CODE_BASE.addTAC(node, address, AMPERSEND, label, NO_ARG);
            varName = label;
        }
        else
        {
            // To .data [ToThink]
        }
    }
    else if (whichProduction == P4)
    {
        // Prepare syn_data to be fetched ⬆️
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        expression_H(node->children[1], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // Pass the data up
        varName = varName1;
        type = type1;
        valueType = valueType1;
        valueSpace = valueSpace1;
        // varName = "(" + varName1 + ")";
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("varName = " + varName + " ⬆️");
    A_PTree node->addAttribute(toString(type) + " ⬆️");
    A_PTree node->addAttribute(toString(valueType) + " ⬆️");
    A_PTree node->addAttribute(toString(valueSpace) + " ⬆️");

    EXIT_H;
}

//--- Postfix Expression Handler
void postfix_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "primary_expression";
    std::string P2 = "postfix_expression LSQUARE expression RSQUARE";
    std::string P3 = "postfix_expression LPAREN RPAREN";
    std::string P4 = "postfix_expression LPAREN argument_expression_list RPAREN";
    std::string P5 = "postfix_expression DOT IDENTIFIER";
    std::string P6 = "postfix_expression PTR_OP IDENTIFIER";
    std::string P7 = "postfix_expression INC_OP";
    std::string P8 = "postfix_expression DEC_OP";

    // A_PTree node->addAttribute("⏬  whereToSendString = " + inh_whereToSendString);
    // A_PTree node->addAttribute("⏬ varName = " + varName);
    // A_PTree node->addAttribute("⏬ " + toString(type));
    // A_PTree node->addAttribute("⏬ "+ toString(valueType));
    // A_PTree node->addAttribute("⏬  " + toString(valueSpace));

    if (whichProduction == P1)
    {
        // Call the primary_expression handler
        primary_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        // This is Array Subscripting

        // Prepare data to be fetched ⬆️
        // From postfix_expression
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // From expression
        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🅰️ TypeChecking for Array Subscript - expresesioon

        if (!isIntegral(type2))
        {
            semanticLOG.push_back("Error: Array Subscript expression \"" + varName2 + "\" is not an integral type");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // 🚀 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        // 🅱️ TypeChecking for Array Itself - postfix_expression
        Type whichType1 = whatIsType(type1);
        // must be array or pointer
        if (whichType1 != Type::ARRAY && whichType1 != Type::POINTER)
        {
            semanticLOG.push_back("Error: Array Subscript expression \"" + varName1 + "\" is not an array or pointer type");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // We need SPACE CHANGE for postfix_expression [array - Address , pointer-Value]

        // Pop the top level
        TypeExpression elementType = type1;
        int check = popALevel(elementType);
        if (check != POP_SUCCESS)
        {
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // We have resulting type
        type = elementType;

        // 🟡varName + 🔖IRCode + 🟡valueSpace

        int element_width = width(elementType);
        std::string element_width_str = std::to_string(element_width);

        std::string baseAddress = varName1;

        std::string jump_amount = newTemp();

        CODE_BASE.addTAC(node, jump_amount, "*", varName2, element_width_str);

        std::string finalAddress = newTemp();

        CODE_BASE.addTAC(node, finalAddress, "+", baseAddress, jump_amount);
        varName = finalAddress; // Change the name to the address

        valueSpace = SPACE::ADDRESS_SPACE; // Array Subscript is in address space
        // 🤔🤔🤔🤔🤔🤔 IMP LOGIC 🤔🤔🤔🤔🤔

        // 🟡 valueType
        valueType = getValueType(type); // Set Correctly

        // inh_attribute already sent down
    }
    else if (whichProduction == P3 || whichProduction == P4)
    {
        // This is Function Call

        // Prepare data to be fetched ⬆️
        // From postfix_expression
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // From argument_expression_list
        std::vector<std::string> argName;
        std::vector<TypeExpression> argType;
        parameter_list_H(node->children[2], argType, argName);
        // Won't Faile

        // 🅰️ TypeChecking for Function Call

        Type whichType1 = whatIsType(type1);
        // must be function or function_pointer
        std::vector<TypeExpression> paramTypes;
        TypeExpression returnType = type1;

        if (whichType1 == Type::FUNCTION)
        {

            // Find ParameterInfo
            paramTypes = ((ParameterInfo *)type1.levelStack.top())->paramsType;

            // Find Return Type
            if (popALevel(returnType) != POP_SUCCESS)
            {
                // SEMANTIC ERROR 🚨 : Error in popALevel
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }

            // Will check function sign later
        }
        else if (whichType1 == Type::POINTER)
        {

            // First we remove the top level with is
            TypeExpression funcType = type1; // pop
            if (popALevel(funcType) != POP_SUCCESS)
            {
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }

            Type whichType = whatIsType(funcType);
            if (whichType != Type::FUNCTION)
            {
                // SEMANTIC ERROR 🚨 : Function Call expression \"" + varName1 + "\" is not a function or function pointer type
                semanticLOG.push_back("Error: Function Call expression \"" + varName1 + "\" is not a function pointer type");
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }

            // Find ParameterInfo
            paramTypes = ((ParameterInfo *)funcType.levelStack.top())->paramsType;

            // Find Return Type
            returnType = funcType;
            if (popALevel(returnType) != POP_SUCCESS)
            {
                // SEMANTIC ERROR 🚨 : Error in popALevel
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }

            // Will check function sign later
        }
        else
        {
            semanticLOG.push_back("Error: Function Call expression \"" + varName1 + "\" is not a function or function pointer type");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // We now have paramTypes & returnType of function form postfix_expression

        // 🅱️ Function call matches the signature
        // Check if the number of parameters is same
        if (paramTypes.size() != argType.size())
        {
            // SEMANTIC ERROR 🚨 : Function Call expression \"" + varName1 + "\" does not match the signature
            semanticLOG.push_back("Error: Function Call expression \"" + varName1 + "\" does not match the signature");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }
        else
        {
            // Check if the types of parameters are same
            for (int i = 0; i < paramTypes.size(); i++)
            {
                int check = checkEquivalance(paramTypes[i], argType[i]); // ⚠️⚠️⚠️⚠️ Vulnerable Code
                if (check != OKAY)
                {
                    // SEMANTIC ERROR 🚨 : Function Call expression \"" + varName1 + "\" does not match the signature
                    semanticLOG.push_back("Error: Function Call expression \"" + varName1 + "\" does not match the signature");
                    ERROR_EXIT_H;
                    // SetUp Dummy Data
                    varName = PASS_ERROR;
                    return;
                }
            }
        }

        // 🟡varName + 🔖IRCode + 🟡valueSpace

        // Write all Parameters to TAC
        for (int i = 0; i < argName.size(); i++)
        {
            CODE_BASE.addTAC(node, NO_ARG, PARAM, argName[i], NO_ARG);
        }

        std::string returnVal = newTemp();
        int no_args = argName.size();

        CODE_BASE.addTAC(node, returnVal, CALL, varName1, std::to_string(no_args));

        varName = returnVal;               // Change the name to the address
        valueSpace = getSpace(returnType); // Function Call is in address space

        // 🟡 valueType
        valueType = getValueType(returnType); // Set Correctly
        type = returnType;                    // Set Correctly

        // All syn_attribute already sent up & inh_attribute already sent down
    }
    else if (whichProduction == P5 || whichProduction == P6)
    {
        // This is Member Selection
        // Prepare data to be fetched ⬆️
        // From postfix_expression
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // From IDENTIFIER
        std::string varName2 = node->children[2]->value;

        // Data to find/calculate
        TypeExpression type0;
        int memberOffset = 0;
        std::string varName0;
        VALUE_TYPE valueType0;
        SPACE valueSpace0;

        // 🅰️ TypeChecking for Member Selection
        Type whichType1 = whatIsType(type1);
        // must be struct or union
        if (whichType1 != Type::STRUCT_UNION)
        {
            // SEMANTIC ERROR 🚨 : Member Selection expression \"" + varName1 + "\" is not a struct or union type
            semanticLOG.push_back("Error: Member Selection expression \"" + varName1 + "\" is not a struct or union type");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // Find postfix's varName in symbolTable
        GenericSymbol *symbol = nullptr;
        int lookupCheck = SYM_TABLE.lookup(varName1, symbol);
        if (lookupCheck == LOOKUP_FAILURE)
        {
            // SEMANTIC ERROR 🚨 : Member Selection expression \"" + varName1 + "\" not found in symbol table
            semanticLOG.push_back("Error: Member Selection expression \"" + varName1 + "\" not found in symbol table");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }
        else
        {
            bool isVar = isVariable(*symbol);
            if (!isVar)
            {
                // SEMANTIC ERROR 🚨 : Member Selection expression \"" + varName1 + "\" is not a variable
                semanticLOG.push_back("Error: Member Selection expression \"" + varName1 + "\" is not a variable");
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }

            TypeExpression varType = ((Variable *)symbol)->type;
            Type whichType = whatIsType(varType);
            if (whichType != Type::STRUCT_UNION)
            {
                // SEMANTIC ERROR 🚨 : Member Selection expression \"" + varName1 + "\" is not a struct or union type
                semanticLOG.push_back("Error: Member Selection expression \"" + varName1 + "\" is not a struct or union variable");
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }

            // Find the member in the struct or union
            BaseInfo *base = (BaseInfo *)varType.levelStack.top();
            std::string baseName = base->baseType;
            // It has three parts
            std::string recordType = baseName.substr(0, baseName.find(" "));
            std::string recordName = baseName.substr(baseName.find(" ") + 1, baseName.length());
            std::string lastPart = baseName.substr(baseName.find_last_of(" ") + 1, baseName.length());
            std::string scopeNoStr = lastPart.substr(1, lastPart.length() - 1);
            int scopeNo = std::stoi(scopeNoStr);

            // Find the record in the symbol table
            GenericSymbol *recordSymbol = nullptr;
            int recordCheck = SYM_TABLE.lookupRecord(recordName, recordSymbol, scopeNo);
            if (recordCheck == LOOKUP_FAILURE)
            {
                // SEMANTIC ERROR 🚨 : Record not found
                semanticLOG.push_back("Error: Record \"" + recordName + "\" not found in symbol table");
                ERROR_EXIT_H;
                // SetUp Dummy Data
                varName = PASS_ERROR;
                return;
            }
            else
            {
                // Find the member in the record
                std::map<std::string, TypeExpression> members = ((UserDType *)recordSymbol)->members;
                auto it = members.find(varName2);
                if (it == members.end())
                {
                    // SEMANTIC ERROR 🚨 : Member \"" + varName2 + "\" not found in record \"" + recordName + "\"
                    semanticLOG.push_back("Error: Member \"" + varName2 + "\" not found in record \"" + recordName + "\"");
                }
                else
                {
                    // We have found the member
                    type0 = it->second;
                    // memberOffset = it->offset //[ToDo] 🅾️🅾️🅾️🅾️
                    memberOffset = 10;
                }
            }
        }

        // 🔖 IRCode Gen

        // valueSpace must be address space
        if (valueSpace1 != SPACE::ADDRESS_SPACE)
        {
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // Get the offset of the member
        std::string offset = std::to_string(memberOffset);
        std::string baseAddress = varName1;
        std::string memberAddress = newTemp();

        CODE_BASE.addTAC(node, memberAddress, "+", baseAddress, offset);
        varName = memberAddress;           // Change the name to the address 🟡
        valueSpace = SPACE::ADDRESS_SPACE; // Member Selection is in address space 🟡
        // 🟡 valueType
        valueType = getValueType(type0); // Set Correctly 🟡
        type = type0;                    // Set Correctly
        // All syn_attribute already sent up & inh_attribute already sent down 🟡
    }
    else if (whichProduction == P7 || whichProduction == P8)
    {
        // This is Inc or Dec

        // Prepare data to be fetched ⬆️
        std::string varName1 = "Just a Dummy", varName0;
        TypeExpression type1, type0;
        VALUE_TYPE valueType1, valueType0;
        SPACE valueSpace1, valueSpace0;

        postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        // aptLOG("p1 okay");

        // 🅰️ TypeChecking for Inc or Dec
        Type whichType1 = whatIsType(type1);
        // Must be a Pointer or Variable
        if (whichType1 != Type::POINTER && whichType1 != Type::VARIABLE)
        {
            // SEMANTIC ERsROR 🚨 : Inc or Dec expression \"" + varName1 + "\" is not a pointer or variable type
            semanticLOG.push_back("Error: Inc or Dec expression \"" + varName1 + "\" is not a pointer or variable type");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        SPACE reqSpace = getSpace(type1); // most likey is VALUE_SPACE

        // aptLOG("Semantic Check Okay");

        std::string op = node->children[1]->value;
        if (op == "++")
        {
            op = "+";
        }
        else if (op == "--")
        {
            op = "-";
        }
        else
        {
            aptLOG("OPERATOR NOT FOUND");
            // SEMANTIC ERROR 🚨 : Inc or Dec expression \"" + varName1 + "\" is not a pointer or variable type
            semanticLOG.push_back("Error: Inc or Dec expression \"" + varName1 + "\" is not a pointer or variable type");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        std::string inc_decBY = "1";
        if (whichType1 == Type::POINTER)
        {
            // Get the size of the pointer
            TypeExpression belowLevel = type1;
            int check = popALevel(belowLevel);
            if (check != POP_SUCCESS)
            {
                // SEMANTIC ERROR 🚨 : Error in popALevel
                aptLOG("Error in popALevel");
            }
            int size = width(belowLevel);
            inc_decBY = std::to_string(size);
        }

        if (valueSpace1 == SPACE::ADDRESS_SPACE && reqSpace == SPACE::VALUE_SPACE)
        {
            // 🔖 IR Code
            std::string valNew = newTemp();

            CODE_BASE.addTAC(node, valNew, RIGHT_STAR, varName1, NO_ARG); // Load it
            std::string valNew2 = newTemp();

            CODE_BASE.addTAC(node, valNew2, op, valNew, inc_decBY); // Increment it

            CODE_BASE.addTAC(node, varName1, LEFT_STAR, valNew2, NO_ARG); // Store it

            varName0 = valNew; // Old varName before inc/dec
        }
        else if (valueSpace1 == SPACE::VALUE_SPACE)
        {
            // 🔖 IR Code
            std::string valNew = newTemp();

            CODE_BASE.addTAC(node, valNew, "=", varName1, inc_decBY); // Store it

            CODE_BASE.addTAC(node, varName1, op, varName1, inc_decBY); // Increment it
            varName0 = valNew;                                         // Old varName before inc/dec
        }
        else
        {
            // Something Wrong
            aptLOG("Something Wrong in Space");
            ERROR_EXIT_H;
            A_PTree node->attributes.push_back("🌋 Something Wrong in Space 💥 Change Code [" + LOC + "]");
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        // valueSpace, valueType, type
        valueSpace0 = getSpace(type1);    // most likey is VALUE_SPACE
        valueType0 = getValueType(type1); // Set Correctly
        type0 = type1;                    // Set Correctly // NO change in type
        aptLOG("Type Okay");

        // Pass the data up
        varName = varName0; // Change the name to the address
        valueSpace = valueSpace0; // Inc or Dec is in address space
        valueType = valueType0;   // Set Correctly
        type = type0;             // Set Correctly
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("varName = " + varName + " ⬆️");
    A_PTree node->addAttribute(toString(type) + " ⬆️");
    A_PTree node->addAttribute(toString(valueType) + " ⬆️");
    A_PTree node->addAttribute(toString(valueSpace) + " ⬆️");

    EXIT_H;
}

void assignment_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "conditional_expression";
    std::string P2 = "unary_expression assignment_operator assignment_expression";

    // A_PTree node->addAttribute("⏬  whereToSendString = " + inh_whereToSendString);
    // A_PTree node->addAttribute("⏬ varName = " + varName);
    // A_PTree node->addAttribute("⏬ " + toString(type));
    // A_PTree node->addAttribute("⏬ "+ toString(valueType));
    // A_PTree node->addAttribute("⏬  " + toString(valueSpace));

    if (whichProduction == P1)
    {
        conditional_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        ;
        //-------------- Value Fetching 📥 -----------------------
        std::string varName1 = "", varName2 = "", varName0 = "";
        TypeExpression type1, type2, type0;
        VALUE_TYPE valueType1, valueType2, valueType0;
        SPACE valueSpace1, valueSpace2, valueSpace0;

        unary_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        assignment_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        //---------------------- Space 🚀Change 🔖IR Code for varName2 [🤫 General Space Before USAGE]
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        // 🅰️ TypeChecking for varName2
        // Rule - valueType - {M_LVALUE, NM_LVALUE, RVALUE} Allowed
        // Rule - type ❓
        ;

        // 🅱️ TypeChecking for varName1
        // Rule - valueType - {M_LVALUE} Allowed
        // Rule - type ❓

        // 🎉 SIDE EFFECTS 🎉
        int width1 = elementWidth(type1);
        if (width1 < 0)
        {
            // SEMANTIC ERROR 🚨 : Error in elementWidth
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }

        ;
        // Find which operation to perform
        std::string assignOp = node->children[1]->value;
        std::string op = (assignOp == "=") ? ("=") : assignOp.substr(0, assignOp.length() - 1);

        //---------------------- Space 🚀Change 🔖IR Code for varName1 [🤬 Custom - During ASSIGNMENT 🥶]
        SPACE reqSpace1 = getSpace(type1);
        if (reqSpace1 == SPACE::VALUE_SPACE && valueSpace1 == SPACE::ADDRESS_SPACE)
        {
            A_PTree node->addAttribute("🤬 ASSIGN Space🚀 Change for -" + varName1 + " Address->Value");

            if (op != "=")
            {
                std::string resName = newTemp();

                CODE_BASE.addTAC(node, resName, op, varName2, std::to_string(width1)); // resName = varName2 op width1

                CODE_BASE.addTAC(node, varName1, LEFT_STAR, resName, NO_ARG); // *varName1 = resName

                varName0 = resName;
            }
            else
            {
                // Simple Assignment

                CODE_BASE.addTAC(node, varName1, LEFT_STAR, varName2, NO_ARG); // *varName1 = varName2
                varName0 = varName2;                                           //
            }
        }
        else if (reqSpace1 == valueSpace1)
        {
            // No space change Code
            if (op != "=")
            {

                CODE_BASE.addTAC(node, varName1, op, varName2, std::to_string(width1)); // resName = varName2 op width1

                varName0 = varName1;
            }
            else
            {
                // Simple Assignment

                CODE_BASE.addTAC(node, varName1, ASSIGN_OP, varName2, NO_ARG); // *varName1 = varName2
                varName0 = varName1;                                           //
            }
        }
        else
        {
            // Something Wrong
            ERROR_EXIT_H;
            A_PTree node->attributes.push_back("🌋 Something Wrong in Space 💥 Change Code [" + LOC + "]");
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }
        //-------------------------------------------------------------------

        // 🤮 Return Value 🤮
        type0 = type1; // return type is of varName1
        valueType0 = VALUE_TYPE::RVALUE;
        valueSpace0 = reqSpace1; // return space is of varName1

        // Pass the Variables Up
        varName = varName0;
        type = type0;
        valueType = valueType0;
        valueSpace = valueSpace0;
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("varName = " + varName + " ⬆️");
    A_PTree node->addAttribute(toString(type) + " ⬆️");
    A_PTree node->addAttribute(toString(valueType) + " ⬆️");
    A_PTree node->addAttribute(toString(valueSpace) + " ⬆️");

    EXIT_H;
}

//--- Unary Expression Handler
void unary_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "postfix_expression";
    std::string P2 = "INC_OP unary_expression";
    std::string P3 = "DEC_OP unary_expression";
    std::string P4 = "unary_operator cast_expression";
    std::string P5 = "SIZEOF unary_expression";
    std::string P6 = "SIZEOF LPAREN type_name RPAREN";

    // A_PTree node->addAttribute("⏬  whereToSendString = " + inh_whereToSendString);
    // A_PTree node->addAttribute("⏬ varName = " + varName);
    // A_PTree node->addAttribute("⏬ " + toString(type));
    // A_PTree node->addAttribute("⏬ "+ toString(valueType));
    // A_PTree node->addAttribute("⏬ " + toString(valueSpace));

    if (whichProduction == P1)
    {
        // Call the postfix_expression handler
        postfix_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {
    }
    else if (whichProduction == P4)
    {
    }
    else if (whichProduction == P5)
    {
    }
    else if (whichProduction == P6)
    {
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("varName = " + varName + " ⬆️");
    A_PTree node->addAttribute(toString(type) + " ⬆️");
    A_PTree node->addAttribute(toString(valueType) + " ⬆️");
    A_PTree node->addAttribute(toString(valueSpace) + " ⬆️");

    EXIT_H;
}

//===================== By RAMAN ===========

//--- Cast Expression Handler

void cast_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "unary_expression";
    std::string P2 = "LPAREN type_name RPAREN cast_expression";

    if (whichProduction == P1)
    {
        unary_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {

        TypeExpression type1;
        type_name_H(node->children[1], type1);

        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        cast_expression_H(node->children[3], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // TODO: logic for possible casting and change in scope etc
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void multiplicative_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    // A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    // A_PTree node->addAttribute("🔻 type = " + toString(type));
    // A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    // A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "cast_expression";
    std::string P2 = "multiplicative_expression STAR cast_expression";
    std::string P3 = "multiplicative_expression DIVIDE cast_expression";
    std::string P4 = "multiplicative_expression MOD cast_expression";

    if (whichProduction == P1)
    {
        cast_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2 || whichProduction == P3 || whichProduction == P4)
    {

        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        multiplicative_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        cast_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // check all possible types that can come in type1 and type2

        //----------------------- Space 🚀Change 🔖IR Code ----------------------------

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // if either type is not BaseType then invalid operator for given type

        bool isNum1 = isNumeric(type1);
        bool isNum2 = isNumeric(type2);

        if (!isNum1 || !isNum2)
        {
            // SEMANTIC ERROR 🚨 : Invalid operator for given type
            semanticLOG.push_back("Error: Operand " + node->children[0]->value + "cannot work on types \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
            ERROR_EXIT_H;
            // SetUp Dummy Data
            varName = PASS_ERROR;
            return;
        }
        else
        {
            std::string primType1 = isPrimitive(type1);
            std::string primType2 = isPrimitive(type2);

            std::string widenType = maxWidth(primType1, primType2);

            if (primType1 != widenType)
            {

                CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
            }

            if (primType2 != widenType)
            {

                CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
            }

            // Now we have both the operands in same type
            // Now we can perform the operation
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, node->children[1]->value, varName1, varName2);

            // Sending syn_attr up
            varName = result; // Change the name to the result

            // Create a new TypeExpression
            BaseInfo *base = new BaseInfo();
            base->baseType = widenType;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0; // Change the type to the result type

            valueType = getValueType(type0);
            valueSpace = getSpace(type0);
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void additive_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "multiplicative_expression";
    std::string P2 = "additive_expression PLUS multiplicative_expression";
    std::string P3 = "additive_expression MINUS multiplicative_expression";

    if (whichProduction == P1)
    {
        multiplicative_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {

        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        additive_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        multiplicative_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);

        // check all possible types that can come in type1 and type2

        // Logic for Addition
        // if both are either of pointer, function, array, struct_object, union_object then semantic error
        // if one is of integral type other cannot be struct_object, union_object
        // if one is float double type then other cannot be pointer, function, array, struct_object, union_object
        // if one is integral and other is pointer, function, array (use width and multiply with integral value and add)return tyype is pointer
        // now do same as mutiplication // return type depends on maxwidth

        // Logic for Subtraction
        // if both are either of pointer, function, array, struct_object, union_object then semantic error
        // if one is of integral type other cannot be struct_object, union_object
        // if one is float double type then other cannot be pointer, function, array, struct_object, union_object
        // if in left integral then in right we cannot have pointer, function, array
        // if in left pointer, function, array then in right integral type (use width and multiply with integral value and subtract)return tyype is pointer
        // now do same as mutiplication // return type depends on maxwidth

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // Step 1: if both are either of pointer, function, array, struct_object, union_object then semantic error
        if ((whichType1 == Type::POINTER || whichType1 == Type::FUNCTION || whichType1 == Type::ARRAY || whichType1 == Type::STRUCT_UNION) &&
            (whichType2 == Type::POINTER || whichType2 == Type::FUNCTION || whichType2 == Type::ARRAY || whichType2 == Type::STRUCT_UNION))
        {
            semanticLOG.push_back("Error: Invalid operation " + node->children[1]->value + " between incompatible types \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        // Step 2: if one is of integral type, the other cannot be struct_object or union_object
        else if ((isIntegral(type1) && (whichType2 == Type::STRUCT_UNION)) ||
                 (isIntegral(type2) && (whichType1 == Type::STRUCT_UNION)))
        {
            semanticLOG.push_back("Error: Invalid operation " + node->children[1]->value + " between integral type and struct/union type");
        }

        // Step 3: if one is float/double type, the other cannot be pointer, function, array, struct_object, or union_object
        else if ((isFloatingPoint(type1) && (whichType2 == Type::POINTER || whichType2 == Type::FUNCTION || whichType2 == Type::ARRAY || whichType2 == Type::STRUCT_UNION)) ||
                 (isFloatingPoint(type2) && (whichType1 == Type::POINTER || whichType1 == Type::FUNCTION || whichType1 == Type::ARRAY || whichType1 == Type::STRUCT_UNION)))
        {
            semanticLOG.push_back("Error: Invalid operation " + node->children[1]->value + " between floating-point type and incompatible type");
        }

        else if (whichProduction == P2)
        {

            // Step 4: if one is integral and the other is pointer, function, or array (use width and multiply with integral value and add)return type is pointer
            if ((isIntegral(type1) && (whichType2 == Type::POINTER || whichType2 == Type::FUNCTION || whichType2 == Type::ARRAY)) ||
                (isIntegral(type2) && (whichType1 == Type::POINTER || whichType1 == Type::FUNCTION || whichType1 == Type::ARRAY)))
            {
                // Handle pointer arithmetic
                std::string pointerVar = isIntegral(type1) ? varName2 : varName1;
                std::string integralVar = isIntegral(type1) ? varName1 : varName2;
                TypeExpression pointerType = isIntegral(type1) ? type2 : type1;

                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                // VINEET HANDLE width and check space too
                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                int elementWidth = width(pointerType);
                std::string elementWidthStr = std::to_string(elementWidth);

                std::string scaledIntegral = newTemp();

                CODE_BASE.addTAC(node, scaledIntegral, "*", integralVar, elementWidthStr);

                std::string result = newTemp();

                CODE_BASE.addTAC(node, result, node->children[1]->value, pointerVar, scaledIntegral);

                varName = result;
                type = pointerType;
                valueType = getValueType(pointerType);
                valueSpace = getSpace(pointerType);
            }

            // Step 5: Perform normal arithmetic for numeric types, i.e. do same as mutiplication // return type depends on maxwidth
            else if (isNumeric(type1) && isNumeric(type2))
            {
                std::string primType1 = isPrimitive(type1);
                std::string primType2 = isPrimitive(type2);

                std::string widenType = maxWidth(primType1, primType2);

                if (primType1 != widenType)
                {

                    CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
                }

                if (primType2 != widenType)
                {

                    CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
                }

                // Now we have both the operands in same type
                // Now we can perform the operation
                std::string result = newTemp();

                CODE_BASE.addTAC(node, result, node->children[1]->value, varName1, varName2);

                // Sending syn_attr up
                varName = result; // Change the name to the result

                // Create a new TypeExpression
                BaseInfo *base = new BaseInfo();
                base->baseType = widenType;
                TypeExpression type0;
                type0.levelStack.push(base);

                type = type0; // Change the type to the result type
                valueType = getValueType(type0);
                valueSpace = getSpace(type0);
            }

            // Step 6: If none of the above cases match, it's an invalid operation
            else
            {
                semanticLOG.push_back("Error: Invalid operation between types \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
            }
        }

        else if (whichProduction == P3)
        {

            // if in left integral then in right we cannot have pointer, function, array
            if (isIntegral(type1) && (whichType2 == Type::POINTER || whichType2 == Type::FUNCTION || whichType2 == Type::ARRAY))
            {
                semanticLOG.push_back("Error: Invalid operation " + node->children[1]->value + " between integral type and pointer/function/array type");
            }

            // if in left pointer, function, array then in right integral type (use width and multiply with integral value and subtract)return type is pointer
            else if ((whichType1 == Type::POINTER || whichType1 == Type::FUNCTION || whichType1 == Type::ARRAY) && isIntegral(type2))
            {
                // Handle pointer arithmetic
                int elementWid = elementWidth(type1);
                std::string elementWidthStr = std::to_string(elementWid);

                std::string scaledIntegral = newTemp();

                CODE_BASE.addTAC(node, scaledIntegral, "*", varName2, elementWidthStr);

                std::string result = newTemp();

                CODE_BASE.addTAC(node, result, node->children[1]->value, varName1, scaledIntegral);

                varName = result;
                type = type1;
                valueType = getValueType(type1);
                valueSpace = getSpace(type1);
            }

            // Perform normal arithmetic for numeric types, i.e. do same as multiplication // return type depends on maxwidth
            else if (isNumeric(type1) && isNumeric(type2))
            {
                std::string primType1 = isPrimitive(type1);
                std::string primType2 = isPrimitive(type2);

                std::string widenType = maxWidth(primType1, primType2);

                if (primType1 != widenType)
                {

                    CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
                }

                if (primType2 != widenType)
                {

                    CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
                }

                // Now we have both the operands in same type
                // Now we can perform the operation
                std::string result = newTemp();

                CODE_BASE.addTAC(node, result, node->children[1]->value, varName1, varName2);

                // Sending syn_attr up
                varName = result; // Change the name to the result

                // Create a new TypeExpression
                BaseInfo *base = new BaseInfo();
                base->baseType = widenType;
                TypeExpression type0;
                type0.levelStack.push(base);

                type = type0; // Change the type to the result type
                valueType = getValueType(type0);
                valueSpace = getSpace(type0);
            }

            // If none of the above cases match, it's an invalid operation
            else
            {
                semanticLOG.push_back("Error: Invalid operation between types \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
            }
        }
    }
    else
    {
        CERR << "Wrong Production in additive_expression_H" << std::endl;
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}
// DONE
void shift_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "additive_expression";
    std::string P2 = "shift_expression LEFT_OP additive_expression";
    std::string P3 = "shift_expression RIGHT_OP additive_expression";

    if (whichProduction == P1)
    {
        additive_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {

        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        shift_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        additive_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);
        // check all possible types that can come in type1 and type2

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        //  both types must be integral else semantic error
        //  if left one is char short enum_const enum_object then it will be of type casted to int else in it's type
        //  same do for right one
        //  do left shift/ right shift depending on production
        //  return type will current type of left type

        if (!isIntegral(type1) || !isIntegral(type2))
        {
            semanticLOG.push_back("Error: Shift operation requires integral types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        else
        {
            // if left one is char, short, enum_const, or enum_object then it will be casted to int
            std::string primType1 = isPrimitive(type1);
            if (primType1 == TYPE_CHAR || primType1 == TYPE_SHORT || primType1 == ENUM_CONSTANT || primType1 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_INT, varName1);
                primType1 = TYPE_INT;
            }

            // same logic for right one
            std::string primType2 = isPrimitive(type2);
            if (primType2 == TYPE_CHAR || primType2 == TYPE_SHORT || primType2 == ENUM_CONSTANT || primType2 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_INT, varName2);
                primType2 = TYPE_INT;
            }

            // do left shift
            std::string result = newTemp();
            if (whichProduction == P2)
            {

                CODE_BASE.addTAC(node, result, "<<", varName1, varName2);
            }
            else
            {

                CODE_BASE.addTAC(node, result, ">>", varName1, varName2);
            }
            // return type will be the current type of the left operand
            varName = result;
            type = type1;
            valueType = getValueType(type1);
            valueSpace = getSpace(type1);
        }
    }
    // else if (whichProduction == P3)//already incorporated in above case
    // {

    //     //same as left shift , only operator change

    // }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

//- NEW
void relational_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "shift_expression";
    std::string P2 = "relational_expression LESSER_OP shift_expression";
    std::string P3 = "relational_expression GREATER_OP shift_expression";
    std::string P4 = "relational_expression LE_OP shift_expression";
    std::string P5 = "relational_expression GE_OP shift_expression";

    if (whichProduction == P1)
    {
        shift_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2 || whichProduction == P3 || whichProduction == P4 || whichProduction == P5)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        relational_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        shift_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // both type must be either numeric or either pointer, function, array
        // for numeric widen both type to max width then do relational operation
        // for pointer, function, array, simply apply operator
        // final type of result will be INTEGER always

        // both type must be either numeric or either pointer, function, array
        if ((isNumeric(type1) && isNumeric(type2)) ||
            ((whichType1 == Type::POINTER || whichType1 == Type::FUNCTION || whichType1 == Type::ARRAY) &&
             (whichType2 == Type::POINTER || whichType2 == Type::FUNCTION || whichType2 == Type::ARRAY)))
        {

            // for numeric widen both type to max width then do relational operation
            if (isNumeric(type1) && isNumeric(type2))
            {
                // Widen both types to max width
                std::string primType1 = isPrimitive(type1);
                std::string primType2 = isPrimitive(type2);

                std::string widenType = maxWidth(primType1, primType2);

                if (primType1 != widenType)
                {

                    CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
                }

                if (primType2 != widenType)
                {

                    CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
                }
            }

            // Perform relational operation
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, node->children[1]->value, varName1, varName2);

            // Final type of result will be INTEGER
            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = TYPE_INT;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
        else
        {
            // SEMANTIC ERROR 🚨 : Invalid operation between incompatible types
            semanticLOG.push_back("Error: Relational operation requires numeric or pointer types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void equality_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "relational_expression";
    std::string P2 = "equality_expression EQ_OP relational_expression";
    std::string P3 = "equality_expression NE_OP relational_expression";

    if (whichProduction == P1)
    {
        relational_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        equality_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        relational_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        // same logic as relational_expression_H

        // Both types must be either numeric or pointer, function, array
        if ((isNumeric(type1) && isNumeric(type2)) ||
            ((whichType1 == Type::POINTER || whichType1 == Type::FUNCTION || whichType1 == Type::ARRAY) &&
             (whichType2 == Type::POINTER || whichType2 == Type::FUNCTION || whichType2 == Type::ARRAY)))
        {
            // For numeric types, widen both to max width
            if (isNumeric(type1) && isNumeric(type2))
            {
                std::string primType1 = isPrimitive(type1);
                std::string primType2 = isPrimitive(type2);

                std::string widenType = maxWidth(primType1, primType2);

                if (primType1 != widenType)
                {

                    CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
                }

                if (primType2 != widenType)
                {

                    CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
                }
            }

            // Perform equality operation
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, node->children[1]->value, varName1, varName2);

            // Final type of result will be INTEGER
            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = TYPE_INT;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
        else
        {
            // SEMANTIC ERROR 🚨 : Invalid operation between incompatible types
            semanticLOG.push_back("Error: Equality operation requires numeric or pointer types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void and_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "equality_expression";
    std::string P2 = "and_expression BIT_AND equality_expression";

    if (whichProduction == P1)
    {
        equality_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        and_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        equality_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        // both operands must be integral
        //  if both are either of char , short, enum_object, enum_const then cast to integer
        //  else cast both to then maxwidth
        //  Ensure both operands are integral
        if (!isIntegral(type1) || !isIntegral(type2))
        {
            semanticLOG.push_back("Error: BIT_AND operation requires integral types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        else
        {
            std::string primType1 = isPrimitive(type1);
            std::string primType2 = isPrimitive(type2);

            // Cast to integer if both are char, short, enum_object, or enum_const
            if (primType1 == TYPE_CHAR || primType1 == TYPE_SHORT || primType1 == ENUM_CONSTANT || primType1 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_INT, varName1);
                primType1 = TYPE_INT;
            }

            if (primType2 == TYPE_CHAR || primType2 == TYPE_SHORT || primType2 == ENUM_CONSTANT || primType2 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_INT, varName2);
                primType2 = TYPE_INT;
            }

            // Cast both to max width type
            std::string widenType = maxWidth(primType1, primType2);

            if (primType1 != widenType)
            {

                CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
            }

            if (primType2 != widenType)
            {

                CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
            }

            // Perform BIT_AND operation
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, "&", varName1, varName2);

            // Set the result attributes
            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = widenType;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void exclusive_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "and_expression";
    std::string P2 = "exclusive_or_expression XOR and_expression";

    if (whichProduction == P1)
    {
        and_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        exclusive_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        and_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        // both operands must be integral
        //  if both are either of char , short, enum_object, enum_const then cast to integer
        //  else cast both to then maxwidth
        //  Ensure both operands are integral
        if (!isIntegral(type1) || !isIntegral(type2))
        {
            semanticLOG.push_back("Error: BIT_XOR operation requires integral types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        else
        {
            std::string primType1 = isPrimitive(type1);
            std::string primType2 = isPrimitive(type2);

            // Cast to integer if both are char, short, enum_object, or enum_const
            if (primType1 == TYPE_CHAR || primType1 == TYPE_SHORT || primType1 == ENUM_CONSTANT || primType1 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_INT, varName1);
                primType1 = TYPE_INT;
            }

            if (primType2 == TYPE_CHAR || primType2 == TYPE_SHORT || primType2 == ENUM_CONSTANT || primType2 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_INT, varName2);
                primType2 = TYPE_INT;
            }

            // Cast both to max width type
            std::string widenType = maxWidth(primType1, primType2);

            if (primType1 != widenType)
            {

                CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
            }

            if (primType2 != widenType)
            {

                CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
            }

            // Perform BIT_AND operation
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, "^", varName1, varName2);

            // Set the result attributes
            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = widenType;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void inclusive_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "exclusive_or_expression";
    std::string P2 = "inclusive_or_expression BIT_OR exclusive_or_expression";

    if (whichProduction == P1)
    {
        exclusive_or_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        inclusive_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        exclusive_or_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        // both operands must be integral
        //  if both are either of char , short, enum_object, enum_const then cast to integer
        //  else cast both to then maxwidth
        //  Ensure both operands are integral
        if (!isIntegral(type1) || !isIntegral(type2))
        {
            semanticLOG.push_back("Error: BIT_OR operation requires integral types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        else
        {
            std::string primType1 = isPrimitive(type1);
            std::string primType2 = isPrimitive(type2);

            // Cast to integer if both are char, short, enum_object, or enum_const
            if (primType1 == TYPE_CHAR || primType1 == TYPE_SHORT || primType1 == ENUM_CONSTANT || primType1 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_INT, varName1);
                primType1 = TYPE_INT;
            }

            if (primType2 == TYPE_CHAR || primType2 == TYPE_SHORT || primType2 == ENUM_CONSTANT || primType2 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_INT, varName2);
                primType2 = TYPE_INT;
            }

            // Cast both to max width type
            std::string widenType = maxWidth(primType1, primType2);

            if (primType1 != widenType)
            {

                CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
            }

            if (primType2 != widenType)
            {

                CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
            }

            // Perform BIT_AND operation
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, "|", varName1, varName2);

            // Set the result attributes
            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = widenType;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void logical_and_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "inclusive_or_expression";
    std::string P2 = "logical_and_expression AND_OP inclusive_or_expression";

    if (whichProduction == P1)
    {
        inclusive_or_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        logical_and_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        inclusive_or_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        // both operands must be either of numeric or pointer type(pointer, array, function_name) , not struct_obj or union_obj
        // convert the pointer type to long long
        // convert chart short enum_const enum_obj to int
        // convert both to max type
        // apply && operator
        // result type in int

        // Ensure both operands are either numeric or pointer type
        if ((!isNumeric(type1) && !(whichType1 == Type::POINTER || whichType1 == Type::ARRAY || whichType1 == Type::FUNCTION)) ||
            (!isNumeric(type2) && !(whichType2 == Type::POINTER || whichType2 == Type::ARRAY || whichType2 == Type::FUNCTION)))
        {
            semanticLOG.push_back("Error: Logical AND operation requires numeric or pointer types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        else
        {
            // Convert pointer types to long long
            if (whichType1 == Type::POINTER || whichType1 == Type::ARRAY || whichType1 == Type::FUNCTION)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_LONG_LONG, varName1);
            }

            if (whichType2 == Type::POINTER || whichType2 == Type::ARRAY || whichType2 == Type::FUNCTION)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_LONG_LONG, varName2);
            }

            // Convert char, short, enum_const, enum_obj to int
            std::string primType1 = isPrimitive(type1);
            std::string primType2 = isPrimitive(type2);

            if (primType1 == TYPE_CHAR || primType1 == TYPE_SHORT || primType1 == ENUM_CONSTANT || primType1 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_INT, varName1);
                primType1 = TYPE_INT;
            }

            if (primType2 == TYPE_CHAR || primType2 == TYPE_SHORT || primType2 == ENUM_CONSTANT || primType2 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_INT, varName2);
                primType2 = TYPE_INT;
            }

            // Convert both to max type
            std::string widenType = maxWidth(primType1, primType2);

            if (primType1 != widenType)
            {

                CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
            }

            if (primType2 != widenType)
            {

                CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
            }

            // Apply AND_OP operator
            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, "&&", varName1, varName2);

            // Result type is int
            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = TYPE_INT;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void logical_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "logical_and_expression";
    std::string P2 = "logical_or_expression OR_OP logical_and_expression";

    if (whichProduction == P1)
    {
        logical_and_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        logical_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        logical_and_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(varName2);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // logic:
        // both operands must be either of numeric or pointer type(pointer, array, function_name) , not struct_obj or union_obj
        // convert the pointer type to long long
        // convert char, short, enum_const, enum_obj to int
        // convert both to max type
        // apply || operator
        // result type in int

        if ((!isNumeric(type1) && !(whichType1 == Type::POINTER || whichType1 == Type::ARRAY || whichType1 == Type::FUNCTION)) ||
            (!isNumeric(type2) && !(whichType2 == Type::POINTER || whichType2 == Type::ARRAY || whichType2 == Type::FUNCTION)))
        {
            semanticLOG.push_back("Error: Logical OR operation requires numeric or pointer types, but found \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
        }
        else
        {
            if (whichType1 == Type::POINTER || whichType1 == Type::ARRAY || whichType1 == Type::FUNCTION)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_LONG_LONG, varName1);
            }

            if (whichType2 == Type::POINTER || whichType2 == Type::ARRAY || whichType2 == Type::FUNCTION)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_LONG_LONG, varName2);
            }

            std::string primType1 = isPrimitive(type1);
            std::string primType2 = isPrimitive(type2);

            if (primType1 == TYPE_CHAR || primType1 == TYPE_SHORT || primType1 == ENUM_CONSTANT || primType1 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName1, CAST, TYPE_INT, varName1);
                primType1 = TYPE_INT;
            }

            if (primType2 == TYPE_CHAR || primType2 == TYPE_SHORT || primType2 == ENUM_CONSTANT || primType2 == TYPE_ENUM)
            {

                CODE_BASE.addTAC(node, varName2, CAST, TYPE_INT, varName2);
                primType2 = TYPE_INT;
            }

            std::string widenType = maxWidth(primType1, primType2);

            if (primType1 != widenType)
            {

                CODE_BASE.addTAC(node, varName1, CAST, widenType, varName1);
            }

            if (primType2 != widenType)
            {

                CODE_BASE.addTAC(node, varName2, CAST, widenType, varName2);
            }

            std::string result = newTemp();

            CODE_BASE.addTAC(node, result, "||", varName1, varName2);

            varName = result;
            BaseInfo *base = new BaseInfo();
            base->baseType = TYPE_INT;
            TypeExpression type0;
            type0.levelStack.push(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}

void conditional_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    A_PTree node->addAttribute("🔻 whereToSendString = " + inh_whereToSendString);
    //    A_PTree node->addAttribute("🔻 type = " + toString(type));
    //    A_PTree node->addAttribute("🔻 valueType = " + toString(valueType));
    //    A_PTree node->addAttribute("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "logical_or_expression";
    std::string P2 = "logical_or_expression QUESTION expression COLON conditional_expression";

    if (whichProduction == P1)
    {
        logical_or_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(varName);
    }
    else
    {
        ERROR_EXIT_H;
        // SetUp Dummy Data
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("⏫ varName = " + varName);
    A_PTree node->addAttribute("⏫ type = " + toString(type));
    A_PTree node->addAttribute("⏫ valueType = " + toString(valueType));
    A_PTree node->addAttribute("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
}
