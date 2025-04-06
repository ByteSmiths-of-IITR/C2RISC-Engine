#include "header.h"
#include "utility.h"

//====================[ Expressions Handler ]=========================================================================================

ASTNode *currentNode = nullptr;

//--- Constatn Expression Handler
std::string NOT_CONSTANT = "$NOT_CONSTANT$";
// 1. constant_expression 🟢
int constant_expression_H(ASTNode *node, std::string &value)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "conditional_expression";

    aptLOG("inh_value = " + value);

    if (whichProduction == P1)
    {
        // 0. syn_data to fetch ⬆️
        std::string value1 = ""; // to be fetched ⬆️
        TypeExpression type1;    // to be fetched ⬆️
        VALUE_TYPE valuetype1;
        SPACE valueSpace1;
        // 1. Call the function again to fetch the next value
        int c_check = conditional_expression_H(node->children[0], "NONE", value1, type1, valuetype1, valueSpace1);
        PASS_THE_ERROR(c_check);

        // 🅱️ TypeCheck for const [📍📍📍TODO]
        if(value1 == NOT_CONSTANT)
        {
            semanticError("Constant Expression is not a constant");
            FAIL_H;
            return FAIL;
        }

        // 2. Pass the data up
        value = value1; // send syn_attr ⬆️
    }
    else
    {
        compilerError("Wrong Production in constant_expression_H");
        BUG_H;
        return BUG;
    }

    EXIT_H;
    return OKAY;
}

//--- Expression Handler
int expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "assignment_expression";
    std::string P2 = "expression COMMA assignment_expression";

    if (!node)
    {
        compilerError("Expression Node is NULL");
        BUG_H;
        return BUG;
    }

    aptLOG("⏬ whereToSendString = " + inh_whereToSendString);
    // aptLOG("⏬ " + toString(type));
    // aptLOG("⏬ " + toString(valueType));
    // aptLOG("⏬  " + toString(valueSpace));
    // aptLOG("⏬  varName = " + varName);

    if (whichProduction == P1)
    {
        // Call the assignment_expression handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int a_check = assignment_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(a_check);

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

        int e_check = expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(e_check);

        // Call the assignment_expression handler
        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        int a_check = assignment_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(a_check);

        // Pass the data from expression1 up
        varName = varName2;
        type = type2;
        valueType = valueType2;
        valueSpace = valueSpace2;

        // Semantic Warning
        semanticWarning("Expression \'" + varName1 + "\''s result is not used");
    }
    else
    {
        compilerError("Wrong Production in expression_H");
        BUG_H;
        return BUG;
    }

    aptLOG("varName = " + varName + " ⬆️");
    aptLOG(toString(type) + " ⬆️");
    aptLOG(toString(valueType) + " ⬆️");
    aptLOG(toString(valueSpace) + " ⬆️");

    EXIT_H;
    return OKAY;
}

//--- Primary Expression Handler
int primary_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER";
    std::string P2 = "CONSTANT";
    std::string P3 = "STRING_LITERAL";
    std::string P4 = "LPAREN expression RPAREN";

    // aptLOG("⏬  whereToSendString = " + inh_whereToSendString);
    // aptLOG("⏬  varName = " + varName);
    // aptLOG("⏬ " + toString(type));
    // aptLOG("⏬ "+ toString(valueType));
    // aptLOG("⏬  " + toString(valueSpace));

    // aptLOG("⬇️ Primary Expression - " + node->value);

    if (whichProduction == P1)
    {
        // aptLOG("P1 - IDENTIFIER");
        // Get Name of Identifier
        std::string varName1 = node->children[0]->value;

        TypeExpression type0; // Find Type of Identifier from Symbol Table
        bool wasFunctionDecayed = false; // To check if the function was decayed to pointer

        // Look into the SymbolTable and Find it's
        GenericSymbol *symbol = nullptr;
        int lookupCheck = SYM_TABLE.lookup(varName1, symbol);
        if (lookupCheck == LOOKUP_FAILURE)
        {
            semanticError("Identifier \"" + varName1 + "\" not 🫠 found in the current scope");
            FAIL_H;
            return FAIL;
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

                varName1 += "$" + std::to_string(symbol->scopeNo); // Change the name to the variable
            }
            else if (symbolType == SYMBOL_TYPE::ENUM_CONSTANT)
            {
                // Create a TypeExpression for Enum Constant
                TypeExpression tempType;
                BaseInfo *base = new BaseInfo();
                base->baseType = ENUM_CONSTANT;
                tempType.levelStack.push_back(base);
                type0 = tempType;
                varName1 += "$" + std::to_string(symbol->scopeNo); // Change the name to the value
            }
            else if (symbolType == SYMBOL_TYPE::FUNCTION)
            {
                type0 = ((Function *)symbol)->type;
                // If type is a variable cast it to a poniter

                // Add a new pointer level
                aptLOG("Funtion to Pointer Decay 🏴‍☠️");
                wasFunctionDecayed = true;
                PointerInfo *ptr = new PointerInfo();
                type0.levelStack.push_back(ptr);
            }
            else
            {
                semanticError("Identifier \"" + varName1 + "\" is not 😑 a variable or function");
                FAIL_H;
                return FAIL;
            }
        }

        // Now that we have type of symbol ready

        Type whichType = whatIsType(type0); // This tell me about TypeExpression

        SPACE val0Space = getSpace(type0); // struct/union or array 🤯

        VALUE_TYPE val0Type = (wasFunctionDecayed) ? VALUE_TYPE::NM_LVALUE : getValueType(type0); // Get the value type

        bool isConst = isConstant(type0); // [REDUANDANT CODE]
        if (isConst)
        {
            val0Type = VALUE_TYPE::NM_LVALUE; // Non Modifiable LValue
            // Check specialy for enum constant
            if (whichType == Type::ENUM_CONSTANT)
            {
                val0Type = VALUE_TYPE::RVALUE; // Read Only Value
            }
        }

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
                // If variable is Constant
                if (isConst)
                { // 🤯 MIGHT BE WRONG
                    // Change the name to the value [Feature TURNED OFF]
                    // varName1 = std::to_string(((Variable *)symbol)->compileTimeConstant);
                }
                else
                {
                    // Correct Name is loaded
                }
            }
        }
        else
        {
            compilerError("The Identifier \"" + varName1 + "\" is in Invalid Space");
            FAIL_H;
            return FAIL;
        }

        // Pass all syn_attribute to up
        varName = varName1;
        type = type0;
        valueType = val0Type;
        valueSpace = val0Space;
    }
    else if (whichProduction == P2)
    {
        // aptLOG("P2 - CONSTANT");
        varName = node->children[0]->value;

        // 🟡 type
        // [ToWrite a Function that takes a string constant and find it's type] & [string format number]
        TypeExpression type0;
        std::string finalValue = "ToBeFetched"; // To be fetched from constant_expression
        int check = ProcessConstants(varName, type0, finalValue);
        if (check != OKAY)
        {
            semanticError("Invalid Constant \"" + varName + "\"");
            FAIL_H;
            return FAIL;
        }
        type = type0;

        // 🟡 VarName is the constant's value itself
        varName = finalValue; // Change the name to the value

        // 🟡 valueType
        Type whichType = whatIsType(type0);

        // 🟡 valueSpace
        SPACE val0Space = getSpace(type0);

        VALUE_TYPE val0Type = VALUE_TYPE::RVALUE;

        // Pass the data up
        valueSpace = val0Space; // Set the value space
        valueType = val0Type;   // Set the value type
    }
    else if (whichProduction == P3)
    { // ⚡️ Advance Feature ⚡️
        aptLOG("P3 - STRING_LITERAL");
        std::string strValue = node->children[0]->value;

        // 🟡 type - Create a TypeExpression char *
        TypeExpression type0;
        BaseInfo *base = new BaseInfo();
        base->baseType = TYPE_CHAR;
        if (inh_whereToSendString != STACK_DATA)
        {
            base->typeQualifiers.push_back(TypeQualifier::CONST); // Char* are const
        }
        type0.levelStack.push_back(base);
        PointerInfo *ptr = new PointerInfo();
        type0.levelStack.push_back(ptr);

        type = type0;

        // 🟡 valueSpace -
        valueSpace = SPACE::VALUE_SPACE; // String literals are in address space

        // 🟡 valueType
        valueType = VALUE_TYPE::NM_LVALUE; // String literals are not modifiable lvalue

        // 🟡 varName + 🔖IRCode Gen

        // Check if string to be sent in .rodata or .data
        if (/*inh_whereToSendString != STACK_DATA*/ true) // FORCE it to be .rodata
        {
            std::string tempName = "@str" + newTemp();
            // Remove the quotes from the string
            std::string raw = strValue.substr(1, strValue.length() - 2);
            std::string data = tempName + " : c\"" +raw+ "\\00\"";
            CODE_BASE.roData.push_back(data); // Add to the rodata
            varName = tempName;
        }
        else
        {
            // Stack Data pass it as it is
            varName = strValue;
        }
    }
    else if (whichProduction == P4)
    {
        aptLOG("P4 - LPAREN expression RPAREN");
        // Prepare syn_data to be fetched ⬆️
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int e_check = expression_H(node->children[1], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(e_check);

        // Pass the data up
        varName = varName1;
        type = type1;
        valueType = valueType1;
        valueSpace = valueSpace1;
        // varName = "(" + varName1 + ")";
    }
    else
    {
        compilerError("Wrong Production in primary_expression_H");
        BUG_H;
        return BUG;
    }

    aptLOG("varName = " + varName + " ⬆️");
    aptLOG(toString(type) + " ⬆️");
    aptLOG(toString(valueType) + " ⬆️");
    aptLOG(toString(valueSpace) + " ⬆️");

    EXIT_H;
    return OKAY;
}

//--Argument Expression List Handler
int argument_expression_list_H(ASTNode *node, std::vector<TypeExpression> &argType, std::vector<std::string> &argName)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "assignment_expression";
    std::string P2 = "argument_expression_list COMMA assignment_expression";

    aptLOG("⏬  " + toString(argType));
    aptLOG("⏬  " + toString(argName));

    if (whichProduction == P1)
    {
        // Call the assignment_expression handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        int a_check = assignment_expression_H(node->children[0], NO_ARG, varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(a_check);

        // Pass the data up
        argType.push_back(type1);
        argName.push_back(varName1);
    }
    else if (whichProduction == P2)
    {
        // Call the argument_expression_list handler
        std::vector<TypeExpression> argType1;
        std::vector<std::string> argName1;

        int a_check = argument_expression_list_H(node->children[0], argType1, argName1);
        RECOVER_THE_ERROR(a_check);

        // Call the assignment_expression handler
        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        int a1_check = assignment_expression_H(node->children[2], NO_ARG, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(a1_check);

        // Pass the data up
        argType1.push_back(type2);
        argName1.push_back(varName2);
        argType = argType1;
        argName = argName1;
    }
    else
    {
        compilerError("argument_expression_list_H - Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("argName = " + toString(argName) + " ⬆️");
    aptLOG("argType = " + toString(argType) + " ⬆️");

    EXIT_H;
    return OKAY;
}

//--- Postfix Expression Handler
int postfix_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
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

    // aptLOG("⏬  whereToSendString = " + inh_whereToSendString);
    // aptLOG("⏬ varName = " + varName);
    // aptLOG("⏬ " + toString(type));
    // aptLOG("⏬ "+ toString(valueType));
    // aptLOG("⏬  " + toString(valueSpace));

    if (whichProduction == P1)
    {
        // Call the primary_expression handler
        int p_check = primary_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(p_check);
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

        int p_check = postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(p_check);

        // 🅱️ TypeChecking for Array Itself - postfix_expression
        Type whichType1 = whatIsType(type1);
        // must be array or pointer
        if (whichType1 != Type::ARRAY && whichType1 != Type::POINTER)
        {
            semanticError("Subscript expression \"" + varName1 + "\" is not an array or pointer type");
            FAIL_H;
            return FAIL;
        }


        // From expression
        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        int e_check = expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(e_check);

        // 🅰️ TypeChecking for Array Subscript - expresesioon

        if (!isIntegral(type2))
        {
            semanticError("Array Subscript expression \"" + varName2 + "\" is not 😱 an integral type");
            FAIL_H;
            return FAIL;
        }

        // 🚀 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        // We need SPACE CHANGE for postfix_expression [array - Address , pointer-Value]

        // Pop the top level
        TypeExpression elementType = type1;
        int check = popALevel(elementType);
        if (check != POP_SUCCESS)
        {
            compilerError("Error in popALevel");
            FAIL_H;
            return FAIL;
        }

        // 🟡varName + 🔖IRCode + 🟡valueSpace
        // aptHERE;
        int element_width = width(elementType);
        std::string element_width_str = std::to_string(element_width);

        std::string baseAddress = varName1;

        std::string jump_amount = newTemp();

        CODE_BASE.addTAC(node, jump_amount, "*", varName2, element_width_str);

        std::string finalAddress = newTemp();

        CODE_BASE.addTAC(node, finalAddress, "+", baseAddress, jump_amount);
        varName = finalAddress;            // Change the name to the address
        valueSpace = SPACE::ADDRESS_SPACE; // Array Subscript is in address space
        // 🤔🤔🤔🤔🤔🤔 IMP LOGIC 🤔🤔🤔🤔🤔
        type = elementType; // Set Correctly
        valueType = getValueType(type); // Set Correctly
        std::cerr << LOC << "Type : " << toString(type) << std::endl;
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
        int p_check = postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(p_check);

        // From argument_expression_list
        std::vector<std::string> argName = {};    // to be fetched ⬆️
        std::vector<TypeExpression> argType = {}; // to be fetched ⬆️

        if (whichProduction == P4)
        {
            int a_check = argument_expression_list_H(node->children[2], argType, argName);
            PASS_THE_ERROR(a_check);
        }
        // 🅰️ TypeChecking for Function Call

        Type whichType1 = whatIsType(type1);
        // must be function or function_pointer
        std::vector<TypeExpression> paramTypes;
        TypeExpression returnType = type1;

        if (whichType1 == Type::POINTER)
        {
            aptHERE;
            // First we remove the top level with is
            if (popALevel(type1) != POP_SUCCESS)
            {
                compilerError("Error in popALevel");
                BUG_H;
                return BUG;
            }
            aptHERE;
            returnType = type1; // reset the returnType
            Type isFunctionPtr = whatIsType(type1);
            if (isFunctionPtr != Type::FUNCTION)
            {
                semanticError("Function Call expression \"" + varName1 + "\" is not a function pointer type");
                FAIL_H;
                return FAIL;
            }

            aptHERE;
            // Find ParameterInfo
            aptLOG("Type : " + toString(type1));
            paramTypes = ((ParameterInfo *)type1.levelStack[type1.levelStack.size() - 1])->paramsType;
            aptHERE;
            // Find Return Type
            aptLOG("Return Type : " + toString(returnType));
            if (popALevel(returnType) != POP_SUCCESS)
            {
                compilerError("Error in popALevel");
                BUG_H;
                return BUG;
            }

            // Will check function sign later
        }
        else
        {
            semanticError("Function Call expression \"" + varName1 + "\" is not a function or function pointer type");
            FAIL_H;
            return FAIL;
        }

        // We now have paramTypes & returnType of function form postfix_expression
        // aptHERE;
        // 🅱️ Function call matches the signature
        // Check if the number of parameters is same
        if (paramTypes.size() != argType.size())
        {
            // SEMANTIC ERROR 🚨 : Function Call expression \"" + varName1 + "\" does not match the signature
            semanticError("Function Call expression \"" + varName1 + "\" does not match the signature");
            FAIL_H;
            return FAIL;
        }
        else
        {
            // Check if the types of parameters are same
            for (int i = 0; i < paramTypes.size(); i++)
            {
                // 🆎 TypeCasting
                TypeExpression source = argType[i];
                TypeExpression dest = paramTypes[i];

                bool isNum = isNumeric(source);
                bool isNum2 = isNumeric(dest);
                if (!(isNum && isNum2))
                {
                    // Check if the types are same
                    int check = ourEquivalent(dest, source);
                    if (check != OKAY)
                    {
                        // SEMANTIC ERROR 🚨 : Assignment expression's operand \"" + varName1 + "\" and \"" + varName2 + "\" are not compatible
                        semanticError("Function Call argument \'" + argName[i] + "\' of type \'" + toString(source) + "\' is not compatible with \'" + toString(dest) + "\'");
                        FAIL_H;
                        return FAIL;
                    }
                }
                else
                {
                    // Implicit Type Casting
                    int equal = ourEquivalent(source, dest);
                    if (equal != OKAY)
                    {
                        std::string castedVarNam = newTemp();
                        CODE_BASE.addTAC(node, castedVarNam, CAST, toString(dest), argName[i]); // Cast it
                        argName[i] = castedVarNam;                                              // Change the name to the address
                    }
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

        int p_check = postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(p_check);

        // From IDENTIFIER
        std::string varName2 = node->children[2]->value;

        // If we are using -> operator remove the top pointer level
        if (whichProduction == P6)
        {
            // We need SPACE CHANGE for postfix_expression [array - Address , pointer-Value]
            // TypeExpression tempType = type1;
            Type whichType = whatIsType(type1);
            if (whichType == Type::POINTER || whichType == Type::ARRAY)
            {
                // First we remove the top level with is
                if (popALevel(type1) != POP_SUCCESS)
                {
                    compilerError("Error in popALevel");
                    FAIL_H;
                    return FAIL;
                }
            }
            else
            {
                semanticError("Member Selection operator \'" + node->children[1]->value + "\' used on \"" + varName1 + "\" which is not a pointer/array type of Struc/Union");
                FAIL_H;
                return FAIL;
            }
        }

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
            semanticError("Member Selection operator \'" + node->children[1]->value + "\' used on \"" + varName1 + "\" which is not a Struc/Union object");
            FAIL_H;
            return FAIL;
        }

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 👻 Existance Check on member of record
        BaseInfo *base = (BaseInfo *)type1.levelStack[type1.levelStack.size() - 1];
        std::string baseName = base->baseType;
        // It has three parts
        std::string recordType = baseName.substr(0, baseName.find(" "));
        RecordType recordIDType = (recordType == "struct") ? RecordType::STRUCT : RecordType::UNION;

        size_t a = baseName.find(' '), b = baseName.find(' ', a + 1);
        std::string recordName = baseName.substr(a + 1, b - a - 1);

        std::string lastPart = baseName.substr(baseName.find_last_of(" ") + 1, baseName.length());
        std::string scopeNoStr = lastPart.substr(1, lastPart.length() - 1);
        int scopeNo = std::stoi(scopeNoStr);

        // Find the record in the symbol table
        GenericSymbol *recordSymbol = nullptr;
        int recordCheck = SYM_TABLE.lookupRecord(recordName, recordSymbol, scopeNo);
        if (recordCheck == LOOKUP_FAILURE)
        {

            // SEMANTIC ERROR 🚨 : Record not found
            semanticError("Record ID (struct/union definition) \"" + recordName + "\" not found in symbol table");
            FAIL_H;
            return FAIL;
        }
        else
        {
            // Check if the record matches the type_record
            if (recordIDType != ((UserDType *)recordSymbol)->recordType)
            {
                // SEMANTIC ERROR 🚨 : Record \"" + recordName + "\" is not a struct or union type
                semanticError("Record \"" + recordName + "\" is not a " + recordType + " type");
                FAIL_H;
                return FAIL;
            }

            // Find the member in the record
            std::map<std::string, TypeExpression> members = ((UserDType *)recordSymbol)->members;
            auto it = members.find(varName2);
            if (it == members.end())
            {
                // SEMANTIC ERROR 🚨 : Member \"" + varName2 + "\" not found in record \"" + recordName + "\"
                semanticError("Member \"" + varName2 + "\" not found in record \"" + recordName + "\"");
                FAIL_H;
                return FAIL;
            }
            else
            {
                // We have found the member calculate the offset
                type0 = it->second;
                for (auto &member : members)
                {
                    if (member.first == varName2)
                    {
                        break;
                    }
                    memberOffset += width(member.second);
                }
                if (recordIDType == RecordType::UNION)
                {
                    memberOffset = 0;
                }
            }
        }

        // 🔖 IRCode Gen

        // valueSpace must be address space
        if (valueSpace1 != SPACE::ADDRESS_SPACE)
        {
            FAIL_H;
            return FAIL;
        }

        // Get the offset of the member
        std::string offset = std::to_string(memberOffset);
        std::string baseAddress = varName1;
        std::string memberAddress = newTemp();

        CODE_BASE.addTAC(node, memberAddress, "+", baseAddress, offset);
        varName = memberAddress;           // Change the name to the address 🟡
        valueSpace = SPACE::ADDRESS_SPACE; // Member Selection is in address space 🟡
        // 🟡 valueType
        valueType = getValueType(type0); // Set Correctly
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

        int p_check = postfix_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(p_check);
        // aptLOG("p1 okay");

        // 🅰️ TypeChecking for Inc or Dec
        // We will check if valueType is M_LVALUE;
        if (valueType1 != VALUE_TYPE::M_LVALUE)
        {
            // SEMANTIC ERROR 🚨 : Inc or Dec expression \"" + varName1 + "\" is not a modifiable lvalue
            semanticError("Inc or Dec expression \"" + varName1 + "\" is not a modifiable lvalue");
            FAIL_H;
            return FAIL;
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
            compilerError("Something wrong with operator");
            BUG_H;
            return BUG;
        }

        // 🅱️ TypeChecking for Inc or Dec
        Type whichType1 = whatIsType(type1);
        std::string inc_decBY = "1";
        if (whichType1 == Type::POINTER)
        {
            // Get the size of the pointer
            TypeExpression belowLevel = type1;
            int check = popALevel(belowLevel);
            if (check != POP_SUCCESS)
            {
                compilerError("Error in popALevel");
                BUG_H;
                return BUG; // SetUp Dummy Data
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
            BUG_H;
            return BUG; // SetUp Dummy Data
        }

        // valueSpace, valueType, type
        valueSpace0 = getSpace(type1);    // most likey is VALUE_SPACE
        valueType0 = getValueType(type1); // Set Correctly
        type0 = type1;                    // Set Correctly // NO change in type
        aptLOG("Type Okay");

        // Pass the data up
        varName = varName0;       // Change the name to the address
        valueSpace = valueSpace0; // Inc or Dec is in address space
        valueType = valueType0;   // Set Correctly
        type = type0;             // Set Correctly
    }
    else
    {
        compilerError("The Postfix Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("varName = " + varName + " ⬆️");
    aptLOG(toString(type) + " ⬆️");
    aptLOG(toString(valueType) + " ⬆️");
    aptLOG(toString(valueSpace) + " ⬆️");

    EXIT_H;
    return OKAY;
}

int assignment_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "conditional_expression";
    std::string P2 = "unary_expression assignment_operator assignment_expression";

    // aptLOG("⏬  whereToSendString = " + inh_whereToSendString);
    // aptLOG("⏬ varName = " + varName);
    // aptLOG("⏬ " + toString(type));
    // aptLOG("⏬ "+ toString(valueType));
    // aptLOG("⏬  " + toString(valueSpace));

    if (whichProduction == P1)
    {
        int c_check = conditional_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(c_check);
    }
    else if (whichProduction == P2)
    {
        //-------------- Value Fetching 📥 -----------------------
        std::string varName1 = "", varName2 = "", varName0 = "";
        TypeExpression type1, type2, type0;
        VALUE_TYPE valueType1, valueType2, valueType0;
        SPACE valueSpace1, valueSpace2, valueSpace0;

        int u_check = unary_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(u_check);

        int a_check = assignment_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(a_check);

        //---------------------- Space 🚀Change 🔖IR Code for varName2 [🤫 General Space Before USAGE]
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        // 🅰️ TypeChecking for varName2
        // Rule - valueType - {M_LVALUE, NM_LVALUE, RVALUE} Allowed
        
        if (valueType2 == VALUE_TYPE::UNKNOWN)
        {
            semanticError("Assignment expression's operand \"" + varName1 + "\" has unknown value type");
            FAIL_H;
            return FAIL;
        }

        // 🅱️ TypeChecking for varName1
        // Rule - valueType - {M_LVALUE} Allowed

        if (valueType1 != VALUE_TYPE::M_LVALUE)
        {
            semanticError("Assignment expression's operand \"" + varName1 + "\" is not a modifiable lvalue");
            FAIL_H;
            return FAIL;
        }

        //🆎 TypeCasting 
        TypeExpression source = type2;
        TypeExpression dest = type1;

        bool isNum = isNumeric(source);
        bool isNum2 = isNumeric(dest);
        if(!(isNum && isNum2)){
            // Check if the types are same
            int check = ourEquivalent(source, dest);
            if (check != OKAY)
            {
                // SEMANTIC ERROR 🚨 : Assignment expression's operand \"" + varName1 + "\" and \"" + varName2 + "\" are not compatible
                semanticError("Assignment expression's operand \"" + varName1 + "\" and \"" + varName2 + "\" are not compatible");
                FAIL_H;
                return FAIL;
            }
        }else{
            // Implicit Type Casting
            int equal = ourEquivalent(source, dest);
            if (equal != OKAY)
            {
                std::string castedVarNam = newTemp();
                CODE_BASE.addTAC(node, castedVarNam, CAST, toString(dest), varName2); // Cast it
                varName2 = castedVarNam; // Change the name to the address
            }
        }

        





        // 🎉 SIDE EFFECTS 🎉
        int width1 = elementWidth(dest);
        if (width1 < 0)
        {
            compilerError("Error in elementWidth");
            BUG_H;
            return BUG;
        }

        // Find which operation to perform
        std::string assignOp = node->children[1]->value;
        std::string op = (assignOp == "=") ? ("=") : assignOp.substr(0, assignOp.length() - 1);

        //---------------------- Space 🚀Change 🔖IR Code for varName1 [🤬 Custom - During ASSIGNMENT 🥶]
        SPACE reqSpace1 = getSpace(dest);
        if (reqSpace1 == SPACE::VALUE_SPACE && valueSpace1 == SPACE::ADDRESS_SPACE)
        {
            aptLOG("🤬 ASSIGN Space🚀 Change for -" + varName1 + " Address->Value");

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
            compilerError("Something Wrong in Space Change");
            BUG_H;
            return BUG; // SetUp Dummy Data
        }
        //-------------------------------------------------------------------

        // 🤮 Return Value 🤮
        type0 = dest; // return type is of varName1
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
        compilerError("Wrong Production in assignment_expression_H");
        BUG_H;
        return BUG;
    }

    aptLOG("varName = " + varName + " ⬆️");
    aptLOG(toString(type) + " ⬆️");
    aptLOG(toString(valueType) + " ⬆️");
    aptLOG(toString(valueSpace) + " ⬆️");

    EXIT_H;
    return OKAY;
}

//--- Unary Expression Handler
int unary_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "postfix_expression";
    std::string P2 = "INC_OP unary_expression";
    std::string P3 = "DEC_OP unary_expression";
    std::string P4 = "unary_operator cast_expression";
    std::string P5 = "SIZEOF unary_expression";
    std::string P6 = "SIZEOF LPAREN type_name RPAREN";

    // aptLOG("⏬  whereToSendString = " + inh_whereToSendString);
    // aptLOG("⏬ varName = " + varName);
    // aptLOG("⏬ " + toString(type));
    // aptLOG("⏬ "+ toString(valueType));
    // aptLOG("⏬ " + toString(valueSpace));

    if (whichProduction == P1)
    {
        // Call the postfix_expression handler
        int p_check = postfix_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(p_check);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {
        std::string op = node->children[0]->value;

        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int u_check = unary_expression_H(node->children[1], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(u_check);
        // aptLOG("u_check okay");
        // 🅰️ TypeChecking for Inc or Dec
        // We will check if valueType is M_LVALUE;
        if (valueType1 != VALUE_TYPE::M_LVALUE)
        {
            semanticError("Unary expression \"" + varName1 + "\" is not a modifiable lvalue");
            FAIL_H;
            return FAIL;
        }

        // SIDE EFFECTS
        int width1 = elementWidth(type1);
        if (width1 < 0)
        {
            compilerError("Error in elementWidth");
            BUG_H;
            return BUG;
        }
        // Find which operation to perform

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
            compilerError("Something wrong with operator");
            BUG_H;
            return BUG;
        }

        // IRCode Generation
        std::string resName = newTemp();
        if (valueSpace1 == SPACE::ADDRESS_SPACE)
        {
            // Load the value from address
            CODE_BASE.addTAC(node, resName, RIGHT_STAR, varName1, NO_ARG); // resName = *varName1

            // Perform the operation
            CODE_BASE.addTAC(node, resName, op, resName, std::to_string(width1)); // resName = resName op width1

            // Store the value back to address
            CODE_BASE.addTAC(node, varName1, LEFT_STAR, resName, NO_ARG); // *varName1 = resName

            varName = resName; // Change the name to the address
        }
        else if (valueSpace1 == SPACE::VALUE_SPACE)
        {
            CODE_BASE.addTAC(node, resName, op, varName1, std::to_string(width1)); // resName = varName2 op width1
            varName = resName;                                                     // Change the name to the address
        }
        else
        {
            compilerError("Something Wrong in Space");
            BUG_H;
            return BUG; // SetUp Dummy Data
        }

        // Return Value
        type = type1; // return type is of varName1
        valueType = VALUE_TYPE::RVALUE;
        valueSpace = getSpace(type1); // return space is of varName1
        // All syn_attribute already sent up & inh_attribute already sent down
    }
    else if (whichProduction == P4)
    {
        // Call the cast_expression handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int c_check = cast_expression_H(node->children[1], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(c_check);

        std::string varName0 = "Just a Dummy";
        TypeExpression type0;
        VALUE_TYPE valueType0;
        SPACE valueSpace0;

        // Operator Dependent
        std::string op = node->children[0]->value;
        if (op == "&")
        {
            // Value Type - {M_LVALUE, NM_LVALUE} Allowed
            if (valueType1 != VALUE_TYPE::M_LVALUE && valueType1 != VALUE_TYPE::NM_LVALUE)
            {
                semanticError("Unary expression \"" + varName1 + "\" is not a lvalue");
                FAIL_H;
                return FAIL;
            }
            valueType0 = VALUE_TYPE::M_LVALUE;

            // Type will be type1+Pointer
            type0 = type1;
            PointerInfo *ptrInfo = new PointerInfo();
            type0.levelStack.push_back(ptrInfo);

            std::string temp = newTemp();
            if (valueSpace1 == SPACE::ADDRESS_SPACE)
            {
                // Load the value from address
                CODE_BASE.addTAC(node, temp, ASSIGN_OP, varName1, NO_ARG); // varName = *varName1
            }
            else if (valueSpace1 == SPACE::VALUE_SPACE)
            {
                CODE_BASE.addTAC(node, temp, AMPERSEND, varName1, NO_ARG); // varName = varName1
            }
            else
            {
                compilerError("Something Wrong in Space");
                BUG_H;
                return BUG; // SetUp Dummy Data
            }

            varName0 = temp;                  // Change the name to the address
            valueSpace0 = SPACE::VALUE_SPACE; // return space is of varName1
            varName = varName0;               // Change the name to the address
        }
        else if (op == "*")
        {
            // Usage Space Change should how happen but let's check
            USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

            // The type of cast_expression must be pointer or array
            Type whichType1 = whatIsType(type1);
            if (whichType1 != Type::POINTER && whichType1 != Type::ARRAY)
            {
                semanticError("In Unary expression \"" + varName1 + "\" is not a pointer or array type");
                FAIL_H;
                return FAIL;
            }
            valueType0 = VALUE_TYPE::M_LVALUE;
            valueSpace0 = SPACE::ADDRESS_SPACE; // return space is of varName1
            type0 = type1;                      // return type is of varName1
            // Pop the top level
            int check = popALevel(type0);
            if (check != POP_SUCCESS)
            {
                compilerError("Error in popALevel");
                BUG_H;
                return BUG;
            }

            // There is no need to deref Now - will be de-referenced in the USAGE_SPACE_CHANGE
            varName0 = varName1; // Change the name to the address
        }
        else if (op == "+")
        {
            // The type of cast_expression must be numeric

            USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

            if (!isNumeric(type1))
            {
                semanticError("In Unary expression \"" + varName1 + "\" is not a numeric type");
                FAIL_H;
                return FAIL;
            }
            valueType0 = VALUE_TYPE::RVALUE;
            type0 = type1;                    // return type is of varName1
            valueSpace0 = SPACE::VALUE_SPACE; // return space is of varName1
            varName0 = varName1;              // Change the name to the address
        }
        else if (op == "-")
        {
            aptLOG("Unary Minus");
            USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

            if (!isNumeric(type1))
            {
                semanticError("In Unary expression \"" + varName1 + "\" is not a numeric type");
                FAIL_H;
                return FAIL;
            }

            // IRCode Gen
            std::string resName = newTemp();
            CODE_BASE.addTAC(node, resName, "-", "0", varName1); // resName = 0 - varName1
            varName0 = resName;                                  // Change the name to the address
            valueSpace0 = SPACE::VALUE_SPACE;                    // return space is of varName1
            type0 = type1;                                       // return type is of varName1
            valueType0 = VALUE_TYPE::RVALUE;
            // varName = varName0; // Change the name to the address
        }
        else if (op == "~")
        {
            // The type of cast_expression must be integral

            USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

            if (!isIntegral(type1))
            {
                semanticError("In Unary expression \"" + varName1 + "\" is not an integral type");
                FAIL_H;
                return FAIL;
            }

            // IRCode Gen
            std::string resName = newTemp();
            CODE_BASE.addTAC(node, resName, "~", varName1, NO_ARG); // resName = ~varName1

            valueType0 = VALUE_TYPE::RVALUE;
            type0 = type1;                    // return type is of varName1
            valueSpace0 = SPACE::VALUE_SPACE; // return space is of varName1
            varName0 = resName;               // Change the name to the address
        }
        else if (op == "!")
        {
            // The type of cast_expression must be integral

            USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

            if (!isIntegral(type1))
            {
                semanticError("In Unary expression \"" + varName1 + "\" is not an integral type");
                FAIL_H;
                return FAIL;
            }

            // IRCode Gen
            std::string resName = newTemp();
            CODE_BASE.addTAC(node, resName, "!", varName1, NO_ARG); // resName = !varName1

            valueType0 = VALUE_TYPE::RVALUE;
            type0 = type1;                    // return type is of varName1
            valueSpace0 = SPACE::VALUE_SPACE; // return space is of varName1
            varName0 = resName;               // Change the name to the address
        }
        else
        {
            compilerError("Something wrong with operator");
            BUG_H;
            return BUG;
        }

        varName = varName0;       // Change the name to the address
        valueSpace = valueSpace0; // return space is of varName1
        valueType = valueType0;   // Set Correctly
        type = type0;             // Set Correctly
    }
    else if (whichProduction == P5)
    {
        // Call the unary_expression handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int u_check = unary_expression_H(node->children[1], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(u_check);

        std::string resName = std::to_string(width(type1));

        varName = resName;               // Change the name to the address
        valueSpace = SPACE::VALUE_SPACE; // return space is of varName1
        valueType = VALUE_TYPE::RVALUE;  // Set Correctly

        TypeExpression type0;
        BaseInfo *base = new BaseInfo();
        base->baseType = TYPE_LONG;
        type0.levelStack.push_back(base);
        type = type0; // Set Correctly
    }
    else if(whichProduction == P6)
    {
        // Call the type_name handler
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int tn_check = type_name_H(node->children[2], type1);
        PASS_THE_ERROR(tn_check);

        std::string resName = std::to_string(width(type1));

        varName = resName;               // Change the name to the address
        valueSpace = SPACE::VALUE_SPACE; // return space is of varName1
        valueType = VALUE_TYPE::RVALUE;  // Set Correctly

        TypeExpression type0;
        BaseInfo *base = new BaseInfo();
        base->baseType = TYPE_LONG;
        type0.levelStack.push_back(base);
        type = type0; // Set Correctly
    }
    else
    {
        compilerError("The Unary Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("varName = " + varName + " ⬆️");
    aptLOG(toString(type) + " ⬆️");
    aptLOG(toString(valueType) + " ⬆️");
    aptLOG(toString(valueSpace) + " ⬆️");

    EXIT_H;
    return OKAY;
}

//===================== By RAMAN ===========

//--- Cast Expression Handler

int cast_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "unary_expression";
    std::string P2 = "LPAREN type_name RPAREN cast_expression";

    if (whichProduction == P1)
    {
        int uex_check = unary_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(uex_check);
    }
    else if (whichProduction == P2)
    {

        TypeExpression type1;
        int tn_check = type_name_H(node->children[1], type1);
        PASS_THE_ERROR(tn_check);


        std::string varName2;
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;

        int cex_check = cast_expression_H(node->children[3], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(cex_check);

        // Call Usage Space Change
        // TODO - Check if it is needed

        // Check if cast-able 
        Type srcType = whatIsType(type2);
        Type destType = whatIsType(type1);

        if(srcType == Type::STRUCT_UNION || destType == Type::STRUCT_UNION){
            // Check if the types are same
            int check = ourEquivalent(type2, type1);
            if (check != OKAY)
            {
                // SEMANTIC ERROR 🚨 : Assignment expression's operand \"" + varName1 + "\" and \"" + varName2 + "\" are not compatible
                semanticError("Explicit cast from \"" + toString(type2) + "\" to \"" + toString(type1) + "\" is not allowed");
                FAIL_H;
                return FAIL;
            }
        }else{
            bool isAllowed = isNumeric(type2) && isNumeric(type1);
            isAllowed = isAllowed || ((srcType == Type::POINTER || srcType == Type::ARRAY) && (destType == Type::POINTER || destType == Type::ARRAY));
            isAllowed = isAllowed || (srcType == Type::FUNCTION && destType == Type::FUNCTION);

            if(!isAllowed){
                // SEMANTIC ERROR 🚨 : Assignment expression's operand \"" + varName1 + "\" and \"" + varName2 + "\" are not compatible
                semanticError("Explicit cast from \"" + toString(type2) + "\" to \"" + toString(type1) + "\" is not allowed");
                FAIL_H;
                return FAIL;
            }
            // Implicit Type Casting
            // NO CODE NEEDED
        }
        
        varName = varName2; // Change the name to the address
        valueSpace = getSpace(type1); // return space is of varName1
        valueType = getValueType(type1); // Set Correctly
        type = type1; // Set Correctly
    }
    else
    {
        compilerError("The Cast Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int multiplicative_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    // aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    // aptLOG("🔻 type = " + toString(type));
    // aptLOG("🔻 valueType = " + toString(valueType));
    // aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "cast_expression";
    std::string P2 = "multiplicative_expression STAR cast_expression";
    std::string P3 = "multiplicative_expression DIVIDE cast_expression";
    std::string P4 = "multiplicative_expression MOD cast_expression";

    if (whichProduction == P1)
    {
        int cex_check = cast_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(cex_check);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {

        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int mex_check = multiplicative_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(mex_check);

        int cex_check = cast_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(cex_check);

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
            semanticError("Operand " + node->children[1]->value + " cannot work on types \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
            FAIL_H;
            return FAIL;
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
            type0.levelStack.push_back(base);

            type = type0; // Change the type to the result type

            valueType = getValueType(type0);
            valueSpace = getSpace(type0);
        }
    }
    else if (whichProduction == P4)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int mex_check = multiplicative_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(mex_check);

        int cex_check = cast_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(cex_check);

        // check all possible types that can come in type1 and type2

        //----------------------- Space 🚀Change 🔖IR Code ----------------------------

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        Type whichType1 = whatIsType(type1);
        Type whichType2 = whatIsType(type2);

        // if either type is not BaseType then invalid operator for given type

        bool isNum1 = isIntegral(type1);
        bool isNum2 = isIntegral(type2);

        if (!isNum1 || !isNum2)
        {
            // SEMANTIC ERROR 🚨 : Invalid operator for given type
            semanticError("Operand " + node->children[1]->value + " cannot work on types \"" + toString(type1) + "\" and \"" + toString(type2) + "\"");
            FAIL_H;
            return FAIL;
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
            type0.levelStack.push_back(base);

            type = type0; // Change the type to the result type

            valueType = getValueType(type0);
            valueSpace = getSpace(type0);
        }
    }
    else
    {
        compilerError("The Multiplicative Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int additive_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "multiplicative_expression";
    std::string P2 = "additive_expression PLUS multiplicative_expression";
    std::string P3 = "additive_expression MINUS multiplicative_expression";

    if (whichProduction == P1)
    {
        int mex_check = multiplicative_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(mex_check);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {

        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int aex_check = additive_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(aex_check);
        int mex_check = multiplicative_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(mex_check);

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

                int eleWidth = elementWidth(pointerType);
                std::string elementWidthStr = std::to_string(eleWidth);

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
                type0.levelStack.push_back(base);

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
                type0.levelStack.push_back(base);

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
        compilerError("The Additive Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}
// DONE
int shift_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "additive_expression";
    std::string P2 = "shift_expression LEFT_OP additive_expression";
    std::string P3 = "shift_expression RIGHT_OP additive_expression";

    if (whichProduction == P1)
    {
        int aex_check = additive_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(aex_check);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {

        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int shex_check = shift_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(shex_check);
        int aex_check = additive_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(aex_check);
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
        compilerError("The Shift Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

//- NEW
int relational_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "shift_expression";
    std::string P2 = "relational_expression LESSER_OP shift_expression";
    std::string P3 = "relational_expression GREATER_OP shift_expression";
    std::string P4 = "relational_expression LE_OP shift_expression";
    std::string P5 = "relational_expression GE_OP shift_expression";

    if (whichProduction == P1)
    {
        int shex_check = shift_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(shex_check);
    }
    else if (whichProduction == P2 || whichProduction == P3 || whichProduction == P4 || whichProduction == P5)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int rex_check = relational_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(rex_check);
        int shex_check = shift_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(shex_check);

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
            type0.levelStack.push_back(base);

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
        compilerError("The Relational Expression Entered Wrong Production");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int equality_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "relational_expression";
    std::string P2 = "equality_expression EQ_OP relational_expression";
    std::string P3 = "equality_expression NE_OP relational_expression";

    if (whichProduction == P1)
    {
        int rex_check = relational_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(rex_check);
    }
    else if (whichProduction == P2 || whichProduction == P3)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int eqex_check = equality_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(eqex_check);
        int rex_check = relational_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(rex_check);

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
            type0.levelStack.push_back(base);

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
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int and_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "equality_expression";
    std::string P2 = "and_expression BIT_AND equality_expression";

    if (whichProduction == P1)
    {
        int eqex_check = equality_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(eqex_check);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int aex_check = and_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(aex_check);
        int eqex_check = equality_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(eqex_check);

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
            type0.levelStack.push_back(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int exclusive_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "and_expression";
    std::string P2 = "exclusive_or_expression XOR and_expression";

    if (whichProduction == P1)
    {
        int aex_check = and_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(aex_check);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int eoex_check = exclusive_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(eoex_check);
        int aex_check = and_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(aex_check);

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
            type0.levelStack.push_back(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int inclusive_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "exclusive_or_expression";
    std::string P2 = "inclusive_or_expression BIT_OR exclusive_or_expression";

    if (whichProduction == P1)
    {
        int eoex_check = exclusive_or_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(eoex_check);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int ioex_check = inclusive_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(ioex_check);
        int eoex_check = exclusive_or_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(eoex_check);

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
            type0.levelStack.push_back(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int logical_and_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "inclusive_or_expression";
    std::string P2 = "logical_and_expression AND_OP inclusive_or_expression";

    if (whichProduction == P1)
    {
        int ioex_check = inclusive_or_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(ioex_check);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int laex_check = logical_and_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(laex_check);
        int ioex_check = inclusive_or_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(ioex_check);

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
            type0.levelStack.push_back(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int logical_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "logical_and_expression";
    std::string P2 = "logical_or_expression OR_OP logical_and_expression";

    if (whichProduction == P1)
    {
        int laex_check = logical_and_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(laex_check);
    }
    else if (whichProduction == P2)
    {
        std::string varName1, varName2;
        TypeExpression type1, type2;
        VALUE_TYPE valueType1, valueType2;
        SPACE valueSpace1, valueSpace2;

        int loex_check = logical_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(loex_check);
        int laex_check = logical_and_expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(laex_check);

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
            type0.levelStack.push_back(base);

            type = type0;
            valueType = VALUE_TYPE::RVALUE;
            valueSpace = SPACE::VALUE_SPACE;
        }
    }
    else
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

int conditional_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{

    ENTRY_H;

    //    aptLOG("🔻 whereToSendString = " + inh_whereToSendString);
    //    aptLOG("🔻 type = " + toString(type));
    //    aptLOG("🔻 valueType = " + toString(valueType));
    //    aptLOG("🔻 valueSpace = " + toString(valueSpace));

    std::string whichProduction = getProduction(node);
    std::string P1 = "logical_or_expression";
    std::string P2 = "logical_or_expression QUESTION expression COLON conditional_expression";

    if (whichProduction == P1)
    {
        int loex_check = logical_or_expression_H(node->children[0], inh_whereToSendString, varName, type, valueType, valueSpace);
        PASS_THE_ERROR(loex_check);
    }
    else if(whichProduction == P2){
        // Call logical_or_expression_H for the first part
        std::string varName1, varName2, varName3;
        TypeExpression type1, type2, type3;
        VALUE_TYPE valueType1, valueType2, valueType3;
        SPACE valueSpace1, valueSpace2, valueSpace3;
        int loex_check = logical_or_expression_H(node->children[0], inh_whereToSendString, varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(loex_check);

        std::string varName0 = newTemp();

        int falseJump = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_FALSE, varName1, NO_ARG);

        // Call expression_H for the second part
        int expr_check = expression_H(node->children[2], inh_whereToSendString, varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(expr_check);
        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);
        CODE_BASE.addTAC(node, varName0, ASSIGN_OP, varName2, NO_ARG);



        int trueExit = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG);

        int falseStart = CODE_BASE.nextIndex();

        CODE_BASE.backpatch(node,{falseJump}, falseStart);

        // Call conditional_expression_H for the third part
        int cond_check = conditional_expression_H(node->children[4], inh_whereToSendString, varName3, type3, valueType3, valueSpace3);
        PASS_THE_ERROR(cond_check);
        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName3, type3, valueSpace3, node);
        CODE_BASE.addTAC(node, varName0, ASSIGN_OP, varName3, NO_ARG);

        int endOf = CODE_BASE.nextIndex();
        CODE_BASE.backpatch(node,{trueExit}, endOf);

        // 🆎 Type Checking
        // If in baseType -> widen to max width | else both must be same
        int isSame = checkEquivalance(type2, type3);
        aptLOG("isSame = " + std::to_string(isSame));
        if(isSame != EQUIVALENT){
            // we check for baseType
            std::string primType1 = isPrimitive(type2);
            std::string primType2 = isPrimitive(type3);

            if (primType1 != "NOT_PRIMITIVE" && primType2 != "NOT_PRIMITIVE"){
                std::string widenType = maxWidth(primType1, primType2);
                // We cast the varName0 to the max width type
                CODE_BASE.addTAC(node, varName0, CAST, widenType, varName0);

                // Assign 
                BaseInfo *base = new BaseInfo();
                base->baseType = widenType;
                TypeExpression type0;
                type0.levelStack.push_back(base);
                type = type0;
            }
            else{
                // NOT PRIMITIVE & not same
                semanticError("Conditional expression requires compatible types, but found \"" + toString(type2) + "\" and \"" + toString(type3) + "\"");
                FAIL_H;
                return FAIL;
            }
        }
        else{
            // If same Okay
            type = type2;
        }


        // Set the result attributes
        varName = varName0;
        
        valueType = VALUE_TYPE::RVALUE;
        valueSpace = SPACE::VALUE_SPACE;
    }
    else
    {
        compilerError("Wrong Production in type_specifier_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⏫ varName = " + varName);
    aptLOG("⏫ type = " + toString(type));
    aptLOG("⏫ valueType = " + toString(valueType));
    aptLOG("⏫ valueSpace = " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}
