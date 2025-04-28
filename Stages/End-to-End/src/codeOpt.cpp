#include "utility.h"
#include "header.h"
#include <regex>

#define NOT_FOLDED "!!NOT_FOLDED!!"

// Check if the string is an integer
bool isInt(const std::string& s) {
    return regex_match(s, std::regex("[-+]?[0-9]+"));
}

// Check if the string is a float
bool isFloat(const std::string& s) {
    return regex_match(s, std::regex("[-+]?[0-9]*\\.[0-9]+([eE][-+]?[0-9]+)?"));
}

// Evaluate the expression
std::string evaluate(const std::string& op, const std::string& arg1, const std::string& arg2) {
    if (isInt(arg1) && isInt(arg2)) {
        int operand1 = stoi(arg1);
        int operand2 = stoi(arg2);
        int result = 0;

        // Evaluate expression here
        // Arithmetic operations
        if (op == "+") result = operand1 + operand2;
        else if (op == "-") result = operand1 - operand2;
        else if (op == "*") result = operand1 * operand2;
        else if (op == "/") result = operand2 != 0 ? operand1 / operand2 : 0; // prevent divide by zero
        else if (op == "%") result = operand2 != 0 ? operand1 % operand2 : 0;
        // Logical operations
        else if (op == "==") result = operand1 == operand2;
        else if (op == "!=") result = operand1 != operand2;
        else if (op == "<")  result = operand1 < operand2;
        else if (op == "<=") result = operand1 <= operand2;
        else if (op == ">")  result = operand1 > operand2;
        else if (op == ">=") result = operand1 >= operand2;
        else if (op == "&&") result = operand1 && operand2;
        else if (op == "||") result = operand1 || operand2;
        // Bitwise operations - only if both operands are integers
        else if (op == "&")  result = operand1 & operand2;
        else if (op == "|")  result = operand1 | operand2;
        else if (op == "^")  result = operand1 ^ operand2;
        else if (op == "<<") result = operand1 << operand2;
        else if (op == ">>") result = operand1 >> operand2;
        else return NOT_FOLDED; // Unsupported operation

        return std::to_string(result);
    } else {
        float operand1 = stof(arg1);
        float operand2 = stof(arg2);
        float result = 0.0;

        // Evaluate expression here
        // Arithmetic operations
        if (op == "+") result = operand1 + operand2;
        else if (op == "-") result = operand1 - operand2;
        else if (op == "*") result = operand1 * operand2;
        else if (op == "/") result = operand2 != 0.0f ? operand1 / operand2 : 0.0f;
        // Logical operations
        else if (op == "==") result = operand1 == operand2;
        else if (op == "!=") result = operand1 != operand2;
        else if (op == "<")  result = operand1 < operand2;
        else if (op == "<=") result = operand1 <= operand2;
        else if (op == ">")  result = operand1 > operand2;
        else if (op == ">=") result = operand1 >= operand2;
        else if (op == "&&") result = operand1 && operand2;
        else if (op == "||") result = operand1 || operand2;
        else return NOT_FOLDED; // Unsupported operation

        // strip trailing zeros (eg. 7.0000 -> 7 , 5.03400 -> 5.034)
        std::string val = std::to_string(result);
        val.erase(val.find_last_not_of('0') + 1, std::string::npos);
        if (val.back() == '.') val.pop_back();  // remove trailing '.'
        return val;
    }
}

int constantFolding(){ // TODO: unary operators left to implement
    int size = IR_CODE.code.size();

    TAC newIR;
    newIR.dataSection = IR_CODE.dataSection; // Copy the data section
    std::vector<bool> toBeRemoved(size, false);
    std::map<std::string, std::string> newValues;

    // Pass1: Identify and evaluate constant expressions
    for(int i=0;i<size;i++){
        std::string result = IR_CODE.code[i].result;
        std::string op = IR_CODE.code[i].op;
        std::string arg1 = IR_CODE.code[i].arg1;
        std::string arg2 = IR_CODE.code[i].arg2;

        // Check if either of operand is a compiler temporary which is evaluated constant folded earlier
        if(newValues.find(arg1) != newValues.end()){
            arg1 = newValues[arg1];
        }

        if ((isInt(arg1) || isFloat(arg1)) && (isInt(arg2) || isFloat(arg2))) {
            std::string val = evaluate(op, arg1, arg2);
            if(val == NOT_FOLDED){
                newIR.addTAC(IR_CODE.code[i]);
                continue;
            }
            newIR.addTAC(TAC_Quadruple(ASSIGN_OP,val,NO_ARG,result));
            if(result[0]=='$'){ // IR_CODE.code[i].result is a compiler generated temporary
                toBeRemoved[i] = true;
                newValues[result] = val;
            }
        } 
        else {
            newIR.addTAC(IR_CODE.code[i]);
        }
    }

    // Assign the new IR code
    IR_CODE = newIR;
    return OKAY;
}

int machineIndependentOptimization(){
    // This will perform the machine independent optimization
    int check = OKAY;
    
    // 1. Constant Folding
    check = constantFolding();
    if(check != OKAY){
        CERR << "Error in constant folding" << std::endl;
        return check;
    }

    // 2. Strength Reduction and Algebraic Simplification
    check = strengthReduction_al_simplification();
    if(check != OKAY){
        CERR << "Error in strength reduction and algebraic simplification" << std::endl;
        return check;
    }

    return OKAY;
}

//==============performing strength reductiona and algebraic expression simplification in IR code=================

// Helper to check if a string is an integer
bool isInt_(const std::string &s)
{
    if (s.empty())
        return false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (i == s.size())
        return false; // Only '+' or '-' is invalid
    for (; i < s.size(); ++i)
    {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

// Helper to check if a string is a float (simple version)
bool isFloat_(const std::string &s)
{
    bool seenDecimal = false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (i == s.size())
        return false;
    for (; i < s.size(); ++i)
    {
        if (s[i] == '.')
        {
            if (seenDecimal)
                return false;
            seenDecimal = true;
        }
        else if (!std::isdigit(s[i]))
        {
            return false;
        }
    }
    return seenDecimal; // must have one decimal point to be float
}

// Helper
int isConstant_isPowerOfTwo(const std::string &arg)
{
    if (arg.find('$') != std::string::npos)
    {
        return -1; // Use -1 to mean false/error
    }

    if (isInt_(arg))
    {
        int value = std::stoi(arg);
        if (value > 0 && (value & (value - 1)) == 0)
        {
            return static_cast<int>(std::log2(value));
        }
    }
    else if (isFloat(arg))
    {
        float value = std::stof(arg);
        if (std::floor(value) == value)
        { // Check if it is whole number
            int intValue = static_cast<int>(value);
            if (intValue > 0 && (intValue & (intValue - 1)) == 0)
            {
                return static_cast<int>(std::log2(intValue));
            }
        }
    }

    return -1; // Not constant or not a power of 2
}


int strengthReduction_al_simplification()
{
    int size = IR_CODE.code.size();
    TAC newIR;
    newIR.dataSection = IR_CODE.dataSection; // Copy the data section

    for (int i = 0; i < size; i++)
    {
        const std::string &op = IR_CODE.code[i].op;
        const std::string &arg1 = IR_CODE.code[i].arg1;
        const std::string &arg2 = IR_CODE.code[i].arg2;
        const std::string &result = IR_CODE.code[i].result;

        // Simplifications
        if (op == "*")
        {
            if (arg1 == "0" || arg2 == "0")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, "0", NO_ARG, result));
                continue;
            }
            if (arg1 == "1")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg2, NO_ARG, result));
                continue;
            }
            if (arg2 == "1")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg1, NO_ARG, result));
                continue;
            }
            // Strength reduction: multiplication by power of 2 → Left shift
            if (isConstant_isPowerOfTwo(arg2) != -1)
            {
                int shift = isConstant_isPowerOfTwo(arg2);
                newIR.addTAC(TAC_Quadruple("<<", arg1, std::to_string(shift), result));
                continue;
            }
            if (isConstant_isPowerOfTwo(arg1) != -1)
            {
                int shift = isConstant_isPowerOfTwo(arg1);
                newIR.addTAC(TAC_Quadruple("<<", arg2, std::to_string(shift), result));
                continue;
            }
        }

        else if (op == "/")
        {
            if (arg2 == "1")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg1, NO_ARG, result));
                continue;
            }
            if (isConstant_isPowerOfTwo(arg2) != -1)
            {
                int shift = isConstant_isPowerOfTwo(arg2);
                newIR.addTAC(TAC_Quadruple(">>", arg1, std::to_string(shift), result));
                continue;
            }
        }

        else if (op == "+")
        {
            if ((arg1 == "0"))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg2, NO_ARG, result));
                continue;
            }
            if ((arg2 == "0"))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg1, NO_ARG, result));
                continue;
            }
        }

        else if (op == "-")
        {
            if ((arg2 == "0"))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg1, NO_ARG, result));
                continue;
            }
        }

        else if (op == "&")
        {
            if ((arg1 == "0") || (arg2 == "0"))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, "0", NO_ARG, result));
                continue;
            }
        }

        else if (op == "^")
        {
            if (arg1 == arg2)
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, "0", NO_ARG, result));
                continue;
            }
        }

        else if (op == "|")
        {
            if (arg1 == "0")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg2, NO_ARG, result));
                continue;
            }
            if (arg2 == "0")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, arg1, NO_ARG, result));
                continue;
            }
        }

        else if (op == "&&")
        {
            if (arg1 == "0" || arg2 == "0")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, "0", NO_ARG, result));
                continue;
            }
        }

        else if (op == "||")
        {
            if (arg1 != "0")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, "1", NO_ARG, result));
                continue;
            }
            if (arg2 != "0")
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, "1", NO_ARG, result));
                continue;
            }
        }

        else if (op == "==")
        {
            if (isInt(arg1) && isInt(arg2))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, (arg1 == arg2) ? "1" : "0", NO_ARG, result));
                continue;
            }
            if (isFloat(arg1) && isFloat(arg2))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, (arg1 == arg2) ? "1" : "0", NO_ARG, result));
                continue;
            }
        }

        else if (op == "!=")
        {
            if (isInt(arg1) && isInt(arg2))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, (arg1 != arg2) ? "1" : "0", NO_ARG, result));
                continue;
            }
            if (isFloat(arg1) && isFloat(arg2))
            {
                newIR.addTAC(TAC_Quadruple(ASSIGN_OP, (arg1 != arg2) ? "1" : "0", NO_ARG, result));
                continue;
            }
        }

        // No simplification applied, add original instruction
        newIR.addTAC(IR_CODE.code[i]);
    }

    // Update IR
    IR_CODE = newIR;
    return OKAY;
}
