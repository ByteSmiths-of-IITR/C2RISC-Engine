#include "header.h"

std::string NO_ARG = "#####";
std::string RIGHT_STAR = "right_star";
std::string LEFT_STAR = "left_star";
std::string FUNCTION_LABEL = "function_label";
std::string BLANK = "blank";
std::string CAST = "cast";
std::string LABEL = "label";
std::string AMPERSEND = "&";
std::string RO_DATA = ".rodata";
std::string DATA = ".data";
std::string BSS = ".bss";
std::string PARAM = "param";
std::string CALL = "call";
std::string ASSIGN_OP = "=";
std::string IF_FALSE = "if_false";
std::string IF_TRUE = "if";
std::string GOTO_LABEL = "goto";

extern ASTNode *currentNode;

TAC_Quadruple::TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result)
{
    this->op = op;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->result = result;
}

std::string TAC_Quadruple::toString() {
    
    // std::string details = "";
    // details += "op: " + op + ", ";
    // details += "arg1: " + arg1 + ", ";
    // details += "arg2: " + arg2 + ", ";
    // details += "result: " + result;

    std::string str = "";

    if(op==CALL){
        if(result == NO_ARG){
            str = "call " + arg1 + ", " + arg2; // CALL p, n 
        }
        else{
            str = result + " = call " + arg1 + ", " + arg2 ; // res = CALL p, n 
        }
        return str;
    }

    if(op == PARAM){
        str = "param " + arg1; // PARAM p
        return str;
    }

    if(op == FUNCTION_LABEL){
        str = arg1 + ": "; // FUNCTION_LABEL p
        return str;
    }

    // if(op == RO_DATA){
    //     str = arg1 + ": " + arg2; // RO_DATA p, n
    //     return str;
    // }
    
    // if(op == DATA){
    //     str = arg1 + ": " + arg2; // DATA p, n
    //     return str;
    // }

    // if(op == BSS){
    //     str = arg1 + ": " + arg2; // BSS p, n
    //     return str;
    // }

    if(op == LABEL){
        str = arg1 + ": "; //Control Flow Labels
        if(arg2 != NO_ARG){
            str = result + ": " + arg1 + ": "; // LABEL : "string"
        }
        return str;
    }

    if(op == AMPERSEND){
        str = result + " = &" + arg1; // result = &arg1
        return str;
    }

    if(op == LEFT_STAR){
        str = "*" + result + " = " + arg1; // *result = arg1
        return str;
    }

    if(op == RIGHT_STAR){
        str = result + " = *"+ arg1; // result = *arg1
        return str;
    }

    if(op == CAST){
        str = result + " = (" + arg1 + ")" + arg2; // result = (arg1)arg2
        return str;
    }

    if(op == BLANK){
        str = "-------------------------------";
        return str;
    }

    if(op == ASSIGN_OP){
        str = result + " = " + arg1; // result = arg1
        return str;
    }
    
    str = result + " = " + arg1 + " " + op + " " + arg2; // result = arg1 op arg2
    return str;
}

std::string newTemp() {
    static int tempCount = 0; // This will keep the count of the temporary variables
    return "$" + std::to_string(tempCount++);
}



std::string newLabel() {
    static int labelCount = 0; // This will keep the count of the labels
    return "L" + std::to_string(labelCount++);
}

void TAC::addTAC(ASTNode* addedAt, std::string result, std::string op, std::string arg1, std::string arg2) {
    this->code.push_back(TAC_Quadruple(op, arg1, arg2, result));
    
    std::string details = this->code.back().toString();
    A_PTree addedAt->addAttribute("TAC: " + details); // 🌴 Adding syn_attr
}

void TAC::addTAC(TAC_Quadruple q) {
    this->code.push_back(q);
}

void TAC::printTAC(std::ofstream &file) {
    for ( auto &quad : code) {
        file << quad.toString() << std::endl;
    }
}

void TAC::printTAC() {
    for ( auto &quad : code) {
        std::cout << quad.toString() << std::endl;
    }
}