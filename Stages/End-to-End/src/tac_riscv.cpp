#include "header.h"

std::string NO_ARG = "#####";


// Special TAC Operators (OP)
std::string RIGHT_STAR = "right_star"; // result = *arg1
std::string LEFT_STAR = "left_star"; // *result = arg1
std::string AMPERSEND = "&"; // result = &arg1

std::string FUNCTION_ENTRY = "FUNCTION_ENTRY"; // function entry
std::string FUNCTION_EXIT = "FUNCTION_EXIT"; // function exit
// std::string BLANK = "blank";
std::string CAST = "cast"; // result = (arg1)arg2

std::string OFFSET_LOAD = ".offset"; // result = arg1.offset
std::string ALLOCATE = "alloca"; // allocate arg1, arg2
std::string GLOBAL_VAR = "isGlobal"; // This is used to identify the global variable
std::string ADDRESS_VAR = "SPACE::ADDRESS_SPACE";

std::string PARAM = "param"; // param arg1
std::string CALL = "call"; // result = call arg1, arg2
std::string RETURN_FUNCTION = "return"; // return arg1 

std::string ASSIGN_OP = "="; // result = arg1

std::string IF_FALSE = "if_false"; // if arg1 == 0 goto result
std::string IF_TRUE = "if"; // if arg1 != 0 goto result
std::string GOTO_LABEL = "goto"; // goto result
std::string GOTO_EQUAL = "goto_equal"; // if arg1 == arg2 goto result

std::string TO_BACKPATCH = "to_backpatch"; // This is used to backpatch the list with the label index


std::string RO_DATA = ".rodata";
std::string STACK_DATA = ".stack";
std::string DATA = ".data";
std::string BSS = ".bss";

// Type of Data in Data Section
std::string dataByte = ".byte";
std::string dataHalfByte = ".half";
std::string dataWord = ".word";
std::string dataDouble = ".double";
std::string dataString = ".string";
std::string dataFloat = ".float";
std::string dataZero = ".zero";

#include <iomanip>

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

    else if (op == FUNCTION_ENTRY)
    {
        str = result + ": Func ENTER"; // FUNCTION_ENTRY p
    }


    else if (op == FUNCTION_EXIT)
    {
        str = result + " ret(" + arg1 + "): EXIT"; // FUNCTION_EXIT p, n 
    }

    else if (op == ALLOCATE)
    {
        if(arg2 == GLOBAL_VAR)
        {
            str = "(global)alloca " + result + ", " + arg1; // allocate var, size
        }
        else
        {
            str = "alloca " + result + ", " + arg1; // allocate var, size
        }
        // str = result+" (" + arg1 + " bytes)"; // var (size bytes)
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
    else if(op == OFFSET_LOAD){
        str = result + " = " + arg1 + ".offset"; // result = arg1.offset
    }

    else if (op == AMPERSEND)
    {
        str = result + " = &" + arg1; // result = &arg1
    }
    
    else if (op == LEFT_STAR)
    {
        str = "("+arg2+")*" + result + " = " + arg1; // *result = arg1
    }

    else if (op == RIGHT_STAR)
    {
        str = result + " = ("+arg2+")*" + arg1; // result = *arg1
    }

    else if (op == CAST)
    {
        str = result + " = (" + arg1 + ")" + arg2; // result = (arg1)arg2
    }

    // else if (op == BLANK)
    // {
    //     str = "-------------------------------";
    // }

    else if (op == ASSIGN_OP)
    {
        str = result + " = " + arg1; // result = arg1
    }
    else if (op == IF_FALSE)
    {
        str = "ifFalse " + arg1 + " goto L(" + result + ")"; // if arg1 == 0 goto arg2
    }
    else if (op == IF_TRUE)
    {
        str = "if " + arg1 + " goto L(" + result + ")"; // if arg1 != 0 goto arg2
    }
    else if (op == GOTO_LABEL)
    {
        str = "goto L(" + result + ")"; // goto arg1
    }
    else if (op == GOTO_EQUAL)
    {
        str = "if " + arg1 + " == " + arg2 + " goto L(" + result + ")"; // if arg1 == arg2 goto arg3
    }
    else if (op == RETURN_FUNCTION)
    {
        str = "return " + (arg1 == NO_ARG ? "" : arg1); // return arg1
    }
    else
    {
        if (arg2 == NO_ARG)
        {
            str = result + " = " + op + " " + arg1; // result = op arg1
        }
        else
        {
            str = result + " = " + arg1 + " " + op + " " + arg2; // result = arg1 op arg2
        }
    }

    return str;
}

std::string newTemp()
{
    static int tempCount = 0; // This will keep the count of the temporary variables
    return ("$" + std::to_string(tempCount++) /* + "$"*/);
}

int TAC::addTAC(ASTNode *addedAt, std::string result, std::string op, std::string arg1, std::string arg2)
{
    this->code.push_back(TAC_Quadruple(op, arg1, arg2, result));

    std::string details = this->code.back().toString();
    details = "[" + std::to_string(code.size() - 1) + "] " + details;
    A_PTree addedAt->addAttribute(details);
    return (code.size() - 1); // this will give 0-based index
}

int TAC::addTAC(TAC_Quadruple q)
{
    this->code.push_back(q);
    int index = code.size() - 1;
    return index;
}

int TAC::getLastInserted()
{
    return (IR_CODE.code.size() - 1); // this will give 0-based index
}

int mergeList(std::vector<int> &target, int addition)
{
    target.push_back(addition);
    return 0;
}

int mergeList(std::vector<int> &target, const std::vector<int> &addition)
{
    // std::cerr << LOC << "Merging " << toString(addition) << " into " << toString(target) << std::endl;
    target.insert(target.end(), addition.begin(), addition.end());
    // std::cerr << LOC << "Merged List " << toString(target) << std::endl;
    return 0;
}

int TAC::backpatch(ASTNode *currNode, const std::vector<int> &list, std::string label)
{
    for (int i = 0; i < list.size(); i++)
    {
        // Check if it's a valid backpatch TAC
        // std::cerr << LOC  << "🩹 BackPatching TAC Code - [" << list[i] << "] with " << label << std::endl;
        std::string opCode = code[list[i]].op;
        bool isOkay = (opCode == IF_FALSE || opCode == IF_TRUE || opCode == GOTO_LABEL);
        if (!isOkay)
        {
            std::cerr << LOC << "🤕 Invalid backpatch TAC" << std::endl;
            return -1;
        }
        code[list[i]].result = label;
    }

    // if(list.size()>0){
    A_PTree currNode->addAttribute("Backpatching List : " + toString(list) + " with " + label); // 🌴 Adding syn_attr
    // }
    return 0;
}

int TAC::backpatch(ASTNode *currNode, const std::vector<int> &list, int labelIndex)
{
    // std::cerr << LOC  << "Calling backpath with -Label=" << labelIndex << std::endl;

    std::string labelStr = std::to_string(labelIndex);
    return backpatch(currNode, list, labelStr);
}



void TAC::printTAC(std::ofstream &file)
{

    file << "Function Turned OFF" << std::endl;
    return;

    file << std::setw(w) << "CodeLineNo" << " : " << std::setw(wcode) << std::left << "TAC" << std::endl;
    file << std::setw(w) << "----------" << " : " << std::setw(wcode) << std::left << "-------------------------------" << std::endl;
    for (int i = 0; i < code.size(); i++)
    {
        // Special Priting for labels
        if (code[i].op == FUNCTION_ENTRY)
        {
            file << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
            continue;
        }
        else if (code[i].op == FUNCTION_EXIT)
        {
            file << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
            continue;
        }

        file << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
    }
}

void TAC::printTAC(std::ostringstream &oss)
{
    // Print the .rodata section
    // oss << std::endl;
    if(dataSection.size()!=0){
        oss << std::left << std::setw(w) << ".data" << " : " << std::setw(wcode) << std::left << std::string(wcode, '-') << std::endl;
        // int gap = 2;
        for (auto it : dataSection)
        {
            auto unit = it.second;
            oss << std::left << std::setw(w) << " " << " : " << std::setw(10) << unit.name + ":" << std::setw(10) << std::left << unit.type << " " << std::setw(10) << std::left << unit.value << std::endl;
        }
    }

    // oss << std::endl;
    oss << std::left << std::setw(w) << ".text" << " : " << std::setw(wcode) << std::left << std::string(wcode, '-') << std::endl;
    for (int i = 0; i < code.size(); i++)
    {
        // Special Priting for labels
        if (code[i].op == FUNCTION_ENTRY)
        {
            // oss << std::endl;
            oss << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
        }
        else if (code[i].op == FUNCTION_EXIT)
        {
            oss << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
            oss << std::endl;
        }
        else if (code[i].op == RETURN_FUNCTION)
        {
            oss << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
        }
        else
        {
            oss << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
        }
    }

    oss << std::string(100, '-') << std::endl;

}

void TAC::printTAC(std::vector<std::string> &list)
{
    // send the output to vector line by line
    std::ostringstream oss;
    oss << std::setw(w) << "CodeLineNo" << " : " << std::setw(wcode) << std::left << "Three Address Code" << std::endl;
    oss << std::setw(w) << "----------" << " : " << std::setw(wcode) << std::left << "-------------------------------" << std::endl;
    for (int i = 0; i < code.size(); i++)
    {
        // Special Priting for labels
        if (code[i].op == FUNCTION_ENTRY)
        {
            oss << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].result << std::endl;
            continue;
        }

        oss << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
    }
    // Now push the output to the vector
    std::string output = oss.str();
    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line))
    {
        list.push_back(line);
    }
    // std::cout << output;
}

std::string TAC::newLabel()
{
    int x = code.size();
    std::string label = "L(" + std::to_string(x) + ")";
    return label;
}

int TAC::nextIndex()
{
    int k = code.size();
    return k;
}

void TAC::printTAC()
{

    for (int i = 0; i < code.size(); i++)
    {
        // Special Priting for label
        if (code[i].op == FUNCTION_ENTRY)
        {
            std::cout << std::setw(w) << code[i].result << " : " << std::endl;
            continue;
        }
        std::cout << std::setw(w) << i << " : " << std::setw(wcode) << std::left << code[i].toString() << std::endl;
    }
}

//=====================[ NEW_TAC Quadraple Code ]=========================================================================================

int NEW_TAC_Quadruple::addVariable(const std::string &varName, bool islive, const std::set<int> &nextUsage)
{
    // Check if the variable is already present
    auto it = VarInfo.find(varName);
    if (it != VarInfo.end())
    {
        // Update the existing entry
        it->second.first = islive;
        it->second.second.insert(nextUsage.begin(), nextUsage.end());
    }
    else
    {
        // Add a new entry
        VarInfo[varName] = std::make_pair(islive, nextUsage);
    }
    return OKAY;
}


bool NEW_TAC_Quadruple::isAlive(const std::string &varName)
{
    auto it = VarInfo.find(varName);
    if (it != VarInfo.end())
    {
        return it->second.first;
    }

    // If variable is Not found, it means it's default answer;

    // If it's Compiler Temp - then notLive
    bool isCompilerTemp = varName[0] == '$';
    return ((isCompilerTemp) ? false : true);
}

int NEW_TAC_Quadruple::nextUse(const std::string &varName, std::set<int> &usage)
{
    auto it = VarInfo.find(varName);
    if (it != VarInfo.end())
    {
        usage = it->second.second;
        return OKAY;
    }
    
    // If variable is Not found, it means it's default answer;
    // If it's Compiler Temp - then notLive
    bool isCompilerTemp = varName[0] == '$';
    usage = (isCompilerTemp) ? std::set<int>() : std::set<int>{INT_MAX}; // Default value for not found
    return OKAY; // Variable not found - used default logic
}

int NEW_TAC_Quadruple::howManyNextUsage(const std::string &varName, int &total)
{
    auto it = VarInfo.find(varName);
    if (it != VarInfo.end())
    {
        total = it->second.second.size();
        return OKAY;
    }
    
    // If variable is Not found, it means it's default answer;
    // If it's Compiler Temp - then notLive
    bool isCompilerTemp = varName[0] == '$';
    total = (isCompilerTemp) ? 0 : 1; // Default value for not found
    return OKAY; // Variable not found - used default logic
}


std::string NEW_TAC_Quadruple::toString()
{
    std::string oldContent = TAC_Quadruple::toString();

    int maxWidthOld = 25;
    int leftWidth = maxWidthOld - oldContent.length();

    if (leftWidth > 0)
    {
        oldContent += std::string(leftWidth, ' ');
    }

    std::string newContent = "";
    newContent += " | ";
    std::string unitContent = "";
    for (auto it : VarInfo)
    {
        unitContent += it.first;
        unitContent += it.second.first ? "" : " ☠️";

        int totalNextUsage = it.second.second.size();
        unitContent += (totalNextUsage > 0) ? " ⬇️ (" : "";

        for (auto j : it.second.second)
        {
            unitContent += " " + std::to_string(j);
        }
        unitContent += (totalNextUsage > 0) ? " )" : "";
        
        // Adding padding
        int padding = 22 - unitContent.length();
        if (padding > 0)
        {
            unitContent += std::string(padding, ' ');
        }
        newContent += unitContent;
        newContent += " | ";
        unitContent = "";
    }

    if(VarInfo.size() == 0)
    {
        newContent += "Default ";
        int padding = 22 - newContent.length();
        if (padding > 0)
        {
            newContent += std::string(padding, ' ');
        }
        newContent += "| ";
    }
    std::string finalStr = oldContent + newContent;
    return finalStr;
}

std::string NEW_TAC_Quadruple::toBaseString()
{
    std::string oldContent = TAC_Quadruple::toString();
    return oldContent;
}

int NEW_TAC_Quadruple::addLivelinessInfo(const std::map<std::string, std::pair<bool, std::set<int>>> &info){
    // This will add the liveliness info to the variable
    for (auto it : info)
    {
        this->VarInfo[it.first] = it.second;
    }
    return OKAY;
}

//=====================[ NEW_TAC Code ]=========================================================================================

int NEW_TAC::addTAC(int atLineNo, NEW_TAC_Quadruple q)
{
    // This will add the new TAC code to the new TAC code
    this->code[atLineNo] = q;
    return OKAY;
}

int NEW_TAC::addOLD_TAC(int lineNo, TAC_Quadruple oldIrCode)
{
    // This will add the old TAC code to the new TAC code
    this->code[lineNo] = NEW_TAC_Quadruple(oldIrCode);
    return OKAY;
}

int NEW_TAC::addVarInfo(int lineNo, const std::string &varName, bool isAlive, const std::set<int> &nextUsage)
{
    // This will add the variable info to the new TAC code
    return this->code[lineNo].addVariable(varName, isAlive, nextUsage);
}

//=====================[ RISC-V Code ]=========================================================================================

void RISCV_CODE::addDataSection(const std::map<std::string, dataSegment> &dataSection)
{
    this->data = dataSection;
    return;
}

void RISCV_CODE::addCode(std::string code){
    code = std::string(4, ' ') + code;
    this->code.push_back(code);
    return;
}

void RISCV_CODE::addCode(std::string code, std::string info)
{
    code = std::string(4, ' ') + code;
    int padding = 26 - code.length();
    if (padding > 0)
    {
        code += std::string(padding, ' ');
    }
    code += " # " + info;
    this->code.push_back(code);
    return;
}

void RISCV_CODE::addLabel(std::string label)
{
    // label = std::string(4, ' ') + label;
    this->code.push_back(label);
    return;
}

void RISCV_CODE::addComment(std::string comment)
{
    comment = std::string(4, ' ') + "# " + comment;
    this->code.push_back(comment);
    return;
}


void RISCV_CODE::printCode(std::ostringstream &oss)
{

    oss << ".data" << std::endl;
    for (auto it : data)
    {
        dataSegment currData = it.second;
        oss << std::string(4, ' ') << currData.name << " : " << std::setw(20) << currData.type << " " << std::setw(20) << currData.value << std::endl;
    }
    oss << std::endl;

    oss << ".text" << std::endl;
    for (auto it : code)
    {
        oss << std::string(4, ' ') << it << std::endl;
    }
    oss << std::endl;
    
}   

//Utility Function for RISC-V Code

std::string indentOP(std::string op)
{
    int paddedsize = 6;
    op = op + std::string(paddedsize - op.size(), ' ');
    return op;
}