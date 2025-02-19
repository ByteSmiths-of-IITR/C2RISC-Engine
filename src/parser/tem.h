#ifndef SYM_H
#define SYM_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <initializer_list>

#define WORD_SIZE 4
#define BYTE_SIZE 1


// Enum for symbol types
enum class SymbolType { VARIABLE, FUNCTION, ARRAY/*, STRUCT, ENUM, UNION*/ };

std::string getSymbolTypeString(SymbolType st){
    switch(st){
        case SymbolType::VARIABLE: return "Variable";
        case SymbolType::FUNCTION: return "Function";
        case SymbolType::ARRAY: return "Array";
        // case SymbolType::STRUCT: return "Struct";
        // case SymbolType::ENUM: return "Enum";
        // case SymbolType::UNION: return "Union";
        default: return "UNKNOWN";
    }
}

// Enum for data types
enum class DataType { 
    VOID, CHAR, INT, FLOAT, DOUBLE // for pointer we will use the same with ptrLevel > 0
};

std::string dTypeString(DataType dt){
    switch(dt){
        case DataType::VOID: return "void";
        case DataType::CHAR: return "char";
        case DataType::INT: return "int";
        case DataType::FLOAT: return "float";
        case DataType::DOUBLE: return "double";
        default: return "UNKNOWN";
    }
}

// Enum for storage classes
enum class StorageClass { AUTO, STATIC, EXTERN };

std::string getStorageClassString(StorageClass sc){
    switch(sc){
        case StorageClass::AUTO: return "auto";
        case StorageClass::STATIC: return "static";
        case StorageClass::EXTERN: return "extern";
        default: return "UNKNOWN";
    }
}


// Base class for symbol-specific details (to be extended)
class SymbolDetails {
    int lineNo;
public:
    virtual ~SymbolDetails() = default;  // making it virtual to allow dynamic_cast
};

class DTypeInfo {
public:
    DataType dataType;
    int ptrLevel;
    std::vector<bool> toWhichConst; // first for data, second for pointer, so on for multiple levels

    DTypeInfo(DataType dt=DataType::VOID, int ptr=0) : dataType(dt), ptrLevel(ptr) {
        toWhichConst.push_back(false);
    }

    DTypeInfo(const std::string& dtype){

        //---ToDo for multiple levels of pointers and const---
        ptrLevel = count(dtype.begin(), dtype.end(), '*');
        toWhichConst.resize(ptrLevel + 1, false);
        std::string baseType = dtype.substr(0, dtype.find_first_of("* ") ); // Correct base type extraction

        if(baseType == "void") dataType = DataType::VOID;
        else if(baseType == "char") dataType = DataType::CHAR;
        else if(baseType == "int") dataType = DataType::INT;
        else if(baseType == "float") dataType = DataType::FLOAT;
        else if(baseType == "double") dataType = DataType::DOUBLE;
        else std::cout << "Unknown Data Type: " << baseType << std::endl;
    }

    void setConst(bool isConst, int level=0){
        if(level >= toWhichConst.size()){
            toWhichConst.resize(level+1, false);
        }
        toWhichConst[level] = isConst;
    }

    int getSize() const {
        if(ptrLevel > 0) return WORD_SIZE;

        switch(dataType){
            case DataType::VOID: return 0;
            case DataType::CHAR: return BYTE_SIZE;
            case DataType::INT: return WORD_SIZE;
            case DataType::FLOAT: return WORD_SIZE;
            case DataType::DOUBLE: return 2*WORD_SIZE;
        }
    }

    void display(std::ostream& out = std::cout) const {
        out << "~~~~~~~~~~ Data Type Information ~~~~~~~~~~~\n";
        out << "Data Type     : " << dTypeString(dataType) << "\n";
        out << "Size          : " << getSize() << "\n";
        out << "Pointer Level : " << ptrLevel << "\n";
        out << "Const Levels  : ";
        for(bool c : toWhichConst){
            out << (c ? "const " : "non-const ") << " ";
        }
        out << "\n";
        out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
};

// Derived class for variable information
class VariableInfo : public SymbolDetails {
public:
    DTypeInfo dataTypeInfo; // dataType and ptrLevel
    StorageClass storageClass; // AUTO by default
    int offset; //~~~~~ TODO in Code Generation Phase ~~~~~
    std::string initValue; //----TODO (what if it's not a literal)----
    // int size // this is a dynamic value, so we will calculate it in the code generation phase

    VariableInfo( // Constructor with default values
        const std::string& dtype="void",
        StorageClass sc=StorageClass::AUTO,
        int off=0,
        std::string initVal=""
    )
    {
        dataTypeInfo = DTypeInfo(dtype);
    }

    void setDataType(DTypeInfo dt) { dataTypeInfo = dt; }
    void setInitialValue(const std::string& initVal) { initValue = initVal; }
    void setStorageClass(StorageClass sc) { storageClass = sc; }
    // void setSize(int sz = dt.getSize()) { size = sz; }
    void setOffset(int off) { offset = off; }
    void setConstant(const std::string& initVal) {
        initValue = initVal;
        dataTypeInfo.setConst(true);
    }

    void display(
        std::ostream& out=std::cout // default output stream is std::cout
    ) const {
        out << "-------------- Variable Information --------------\n";
        dataTypeInfo.display(out);
        out << "Storage Class : " << getStorageClassString(storageClass) << "\n";
        out << "Size          : " << dataTypeInfo.getSize() << "\n";
        out << "Offset        : " << offset << "\n";
        // ----ToDo for multiple levels of const----
        out << "Init Value    : " << initValue << "\n";
        out << "------------------------------------------------\n";
    }
};

// Derived class for array information
class ArrayInfo : public SymbolDetails {
public:
    DTypeInfo elementTypeInfo; // dataType and ptrLevel of elements
    StorageClass storageClass; // AUTO by default
    std::vector<int> dimensions; // Dimensions of the array
    int totalSize; // Total size of the array in bytes
    int offset; //~~~~~ TODO in Code Generation Phase ~~~~~
    
    ArrayInfo(
        const std::string& elementDType="void",
        StorageClass sc=StorageClass::AUTO,
        std::vector<int> dims={},
        int off=0
    )
    {
        elementTypeInfo = DTypeInfo(elementDType);
        dimensions = dims;
        offset = off;
        setTotalSize();
    }

    void setElementType(const std::string& dtype) { elementTypeInfo = DTypeInfo(dtype); }
    void setElementTypeInfo(DTypeInfo dt) { elementTypeInfo = dt; }
    void setStorageClass(StorageClass sc) { storageClass = sc; }
    void addDimension(int dim) { dimensions.push_back(dim); setTotalSize(); }
    void setDimensions(std::vector<int> dims) { dimensions = dims; setTotalSize(); }
    void setTotalSize() {
        totalSize = elementTypeInfo.getSize();
        for(int dim : dimensions){
            totalSize *= dim;
        }
    }
    void setOffset(int off) { offset = off; }


    void display(
        std::ostream& out=std::cout // default output stream is std::cout
    ) const {
        elementTypeInfo.display(out);
        out << "Storage Class : " << getStorageClassString(storageClass) << "\n";
        out << "Dimensions    : ";
        for(int dim : dimensions){
            out << dim << " ";
        }
        out << "\n";
        out << "Total Size    : " << totalSize << "\n";
        out << "Offset        : " << offset << "\n";
    }


};

// Derived class for function information
class FunctionInfo : public SymbolDetails {
public:
    DTypeInfo returnType; // dataType and ptrLevel & const of return type
    StorageClass storageClass; // AUTO by default
    bool isConst; // const flag for function [means no modification of any variable inside]
    bool variadic; // Variadic function flag
    bool recursive; // Recursive function flag
    std::vector<std::pair<std::string, DTypeInfo>> parameters; // List of parameters
    bool defined; // Function definition flag
    void* address; // Function address ------ In Code Generation Phase ------

    FunctionInfo(
        const std::string& dtype="void",
        bool isConst=false,
        bool var=false,
        bool rec=false,
        bool def=false,
        void* addr=nullptr
    ) : 
        returnType(DTypeInfo(dtype)),
        isConst(isConst),
        variadic(var),
        recursive(rec),
        defined(def),
        address(addr)
    {}

    void setReturnType(DataType dt) { returnType.dataType = dt; }
    void setConst(bool isConst) { isConst = isConst; }
    void setVariadic(bool var) { variadic = var; }
    void setRecursive(bool rec) { recursive = rec; }
    void setDefined(bool def) { defined = def; }
    void setAddress(void* addr) { address = addr; }

    void addParameter(std::string dtype, std::string name) {
        parameters.push_back({name, DTypeInfo(dtype)});
    }

    void display(
        std::ostream& out=std::cout // default output stream is std::cout
    ) const {
        out << "-------------- Function Information --------------\n";
        returnType.display(out);
        out << "Storage Class : " << getStorageClassString(storageClass) << "\n";
        out << "isConstant    : " << isConst << "\n";
        out << "Variadic      : " << variadic << "\n";
        out << "Recursive     : " << recursive << "\n";
        out << "Defined       : " << defined << "\n";
        out << "Address       : " << address << "\n";
        out << "--------Parameters--------\n";
        for(auto& param : parameters){
            out << param.first << " : ";
            param.second.display(out);
            out << "\n";
        }
        out << "--------------------------\n";
        out << "------------------------------------------------\n";
    }

};

// Symbol Table Entry (Contains symbolKey, type, and pointer to details)
class SymbolEntry {
public:
    std::string symbolKey;
    /* Symbol Key Rules
    - For variables, it's the variable name
    - For functions, it's the function name
        if variadic function, then name will be like "funcName_..."
        else functionName+parameterType1+parameterType2+...
    - For arrays, it's the array name
    
    // Scope will be handled by the indexed design of symbol table

    */

    SymbolType symbolType; // Type of the symbol
    SymbolDetails* details; // Pointer to the details

    SymbolEntry(
        const std::string& key,
        SymbolType type,
        SymbolDetails* det
    ) : symbolKey(key), symbolType(type), details(det) {}

    ~SymbolEntry() {
        delete details;
    }

    void display(
        std::ostream& out=std::cout // default output stream is std::cout
    ) const {
        out << "=========================== Symbol Entry ===========================\n";
        out << "Symbol Key : " << symbolKey << "\n";
        out << "Symbol Type: " << getSymbolTypeString(symbolType) << "\n";
        switch(symbolType) {
            case SymbolType::VARIABLE:
                static_cast<VariableInfo*>(details)->display(out);
                break;
            case SymbolType::ARRAY:
                static_cast<ArrayInfo*>(details)->display(out);
                break;
            case SymbolType::FUNCTION:
                static_cast<FunctionInfo*>(details)->display(out);
                break;
        }
        out << "====================================================================\n";
    }
};

// Symbol Table Class
class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry*> table;

public:
    ~SymbolTable() {
        for (auto& pair : table) delete pair.second;
    }

    void insert(SymbolEntry* entry) {
        table[entry->symbolKey] = entry;
    }

    SymbolEntry* lookup(const std::string& symbolKey) {
        return table.count(symbolKey) ? table[symbolKey] : nullptr;
    }

    void display(
        std::ostream& out=std::cout // default output stream is std::cout
    ) const {
        for (auto& pair : table) {
            pair.second->display(out);
        }
    }

};


#endif // SYM_H