#include "tac.h"
#include "utility.h"
#include "sym.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~[ Three Address Code Generation Helper Functions ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TAC_Quadruple::TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result){
    this->op = op;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->result = result;
}

std::string TAC_Quadruple::toString(){
    //[📍 ToWrite]
    return "NULL";
}

std::string newTemp(){
    static int tempCount = 0; // This will keep the count of the temporary variables
    return "*t" + std::to_string(tempCount++);
}

std::string newLabel(){
    static int labelCount = 0; // This will keep the count of the labels
    return "L" + std::to_string(labelCount++);
}

void TAC::addTAC(std::string op, std::string arg1, std::string arg2, std::string result){
    this->code.push_back(TAC_Quadruple(op, arg1, arg2, result));
}

void TAC::addTAC(TAC_Quadruple q){
    this->code.push_back(q);
}

void TAC::printTAC(){
    //[📍 ToWrite]
}