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

#include <iomanip>

extern ASTNode *currentNode;

TAC_Quadruple::TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result)
{
    this->op = op;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->result = result;
}

std::string TAC_Quadruple::toString()
{

    // std::string details = "";
    // details += "op: " + op + ", ";
    // details += "arg1: " + arg1 + ", ";
    // details += "arg2: " + arg2 + ", ";
    // details += "result: " + result;

    std::string str = "";

    if (op == CALL)
    {
        if (result == NO_ARG)
        {
            str = "call " + arg1 + ", " + arg2; // CALL p, n
        }
        else
        {
            str = result + " = call " + arg1 + ", " + arg2; // res = CALL p, n
        }
    }
    else if (op == PARAM)
    {
        str = "param " + arg1; // PARAM p
    }

    else if (op == FUNCTION_LABEL)
    {
        str = result + ": "; // FUNCTION_LABEL p
    }

    // if(op == RO_DATA){
    //     str = arg1 + ": " + arg2; // RO_DATA p, n
    // }

    // if(op == DATA){
    //     str = arg1 + ": " + arg2; // DATA p, n
    // }

    // if(op == BSS){
    //     str = arg1 + ": " + arg2; // BSS p, n
    // }

    else if (op == LABEL)
    {
        str = "L-" + result + ": "; // LABEL p
        if(arg1 != NO_ARG)
        {
            str += arg1;
        }
    }

    else if (op == AMPERSEND)
    {
        str = result + " = &" + arg1; // result = &arg1
    }

    else if (op == LEFT_STAR)
    {
        str = "*" + result + " = " + arg1; // *result = arg1
    }

    else if (op == RIGHT_STAR)
    {
        str = result + " = *" + arg1; // result = *arg1
    }

    else if (op == CAST)
    {
        str = result + " = (" + arg1 + ")" + arg2; // result = (arg1)arg2
    }

    else if (op == BLANK)
    {
        str = "-------------------------------";
    }

    else if (op == ASSIGN_OP)
    {
        str = result + " = " + arg1; // result = arg1
    }
    else if(op == IF_FALSE)
    {
        str = "ifFalse " + arg1 + " goto " + result; // if arg1 goto arg2
    }
    else if(op == IF_TRUE)
    {
        str = "if " + arg1 + " goto " + result; // if arg1 goto arg2
    }
    else if(op == GOTO_LABEL)
    {
        str = "goto " + result; // goto arg1
    }


    else
    {
        str = result + " = " + arg1 + " " + op + " " + arg2; // result = arg1 op arg2
    }

    return str;
}

std::string newTemp()
{
    static int tempCount = 0; // This will keep the count of the temporary variables
    return "$" + std::to_string(tempCount++);
}

std::string newLabel()
{
    static int labelCount = 0; // This will keep the count of the labels
    return "L" + std::to_string(labelCount++);
}

void TAC::addTAC(ASTNode *addedAt, std::string result, std::string op, std::string arg1, std::string arg2)
{
    this->code.push_back(TAC_Quadruple(op, arg1, arg2, result));

    std::string details = this->code.back().toString();
    A_PTree addedAt->addAttribute("TAC: " + details); // 🌴 Adding syn_attr
}

void TAC::addTAC(TAC_Quadruple q)
{
    this->code.push_back(q);
}

void TAC::printTAC(std::ofstream &file)
{
    file << std::setw(w) << "CodeLineNo" << " : " << std::setw(wcode) << std::left << "TAC" << std::endl;
    file << std::setw(w) << "----------" << " : " << std::setw(wcode) << std::left << "-------------------------------" << std::endl;
    for (int i = 0; i < code.size(); i++)
    {
        // Special Priting for labels
        if(code[i].op == LABEL)
        {
            file << std::setw(w) << code[i].result << " : " << std::setw(wcode) << std::left << code[++i].toString() << std::endl;
            continue;
        }
        else if(code[i].op == FUNCTION_LABEL)
        {
            file << std::setw(w) << code[i].result << " : " << std::endl;
            continue;
        } else if(code[i].op == BLANK)
        {
            file << std::endl;
        }

        file << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
    }
}

std::string TAC::newLabel()
{
    int lastInserted = code.size();
    std::string label = "L" + std::to_string(lastInserted);
    return label;
}

void TAC::printTAC()
{

    for (int i = 0; i < code.size(); i++)
    {
        // Special Priting for labels
        if (code[i].op == LABEL )
        {
            std::cout << std::setw(w) << code[i].result << " : " << std::setw(wcode) << std::left << code[i++].toString() << std::endl;
            continue;
        }
        if (code[i].op == FUNCTION_LABEL)
        {
            std::cout << std::setw(w) << code[i].result << " : " << std::endl;
            continue;
        }
        std::cout << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
    }
}