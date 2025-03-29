#ifndef TAC_H
#define TAC_H

#include "utility.h"

extern int MEMORY_MONITORING;

// Custom TAC Arguments
const std::string RIGHT_ARRAY = "RIGHT_ARRAY";
const std::string LEFT_ARRAY = "LEFT_ARRAY";

const std::string NO_ARG = "";

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

#define CON_DES(clasName)                         \
    clasName() { MEM(#clasName " Constructor"); } \
    ~clasName() { MEM(#clasName " Destructor"); }
//~~~~~~~~~~~~~~~~~~~~~~~~~~[ Three Address Code Generation Helper Functions ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class TAC_Quadruple{
    public:
        std::string op;
        std::string arg1;
        std::string arg2;
        std::string result;

        CON_DES(TAC_Quadruple)

        TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result);
        
        std::string toString();
};

std::string newTemp(); // Generates a new temporary variable [compiler generated]
std::string newLabel(); // Generates a new label [compiler generated]

class TAC{
    public:
        std::vector<TAC_Quadruple> code;
        CON_DES(TAC)
        
        // void addTAC(std::string op, std::string arg1, std::string arg2, std::string result);
        void addTAC(std::string result, std::string op, std::string arg1, std::string arg2); // More readable
        void addTAC(TAC_Quadruple q);

        void printTAC();
};

#endif //!TAC_H