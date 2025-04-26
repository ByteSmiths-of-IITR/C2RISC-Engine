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

    
}

int machineIndependentOptimization(){
    // This will perform the machine independent optimization
    int check = OKAY;
    
    // 1. Constant Folding
    // check = constantFolding();
    if(check != OKAY){
        CERR << "Error in constant folding" << std::endl;
        return check;
    }



    return OKAY;
}