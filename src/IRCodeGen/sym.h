#ifndef SYM_H
#define SYM_H

#include <utility.h>

#define WORD_SIZE 4
#define BYTE_SIZE 1

// Include all the necessary headers
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <initializer_list>

const std::string levelArray = "Array";
const std::string levelPointer = "Pointer";
const std::string levelBase = "Base";

enum class TypeQualifier{
    CONST,
    VOLATILE,
    RESTRICT
};

enum class StorageClass{
    AUTO,
    STATIC,
    EXTERN
};

class LevelInfo{
};

class ArrayInfo : public LevelInfo{
    int dimSize;
};

class PointerInfo : public LevelInfo{
    std::vector<TypeQualifier> typeQualifiers;
    // This will have const, volatile, restrict
};



class BaseInfo : public LevelInfo{
    std::string baseType;
    // This is either primitive or struct or union (Record)
    std::vector<TypeQualifier> typeQualifiers;
    // This will have const, volatile, restrict
    StorageClass storageClass; // only one of these
    // This will have auto, static, extern

    // int size; // a dynamic value [no need to store can be calculated]
    
};



class Variable{

    // D-Type INFO
    std::vector<std::string> levelType;
    std::vector<LevelInfo> levelInfo;

    // Initialization info [for now just pass the initializer ASTNode itself]
    ASTNode *intiailizer; // This will point to the initializer expression of this variable

    // Assembly Info
    int offset; // Offset from the base pointer
    

}

#endif // !SYM_H