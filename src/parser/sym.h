#ifndef SYM_H
#define SYM_H

#define MAX_SCOPE 1000
#define WORD_SIZE 4
#define BYTE_SIZE 1

// Here we will be designing the symbol table for the compiler

/*
Ideas:
- We have a general class node for basic information - Name, SymbolType+Pointer_toThatNodeOfSymbolNode, scope
- We have a class for each type of symbol - Variable, Function, [Later Struct, Enum, Union ]
- For variable, we have - Type, Size, Offset, pointerFlag, ArrayInfo, InitializationValue
- For function, we have - Return Type, parameterList(argType, argName), variadicFlag, recursiveFlag, FunctionAddress


*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Enum for symbol types
enum class SymbolType { VARIABLE, FUNCTION, ARRAY/*, STRUCT, ENUM, UNION*/ };

// Enum for data types
enum class DataType { 
    VOID, CHAR, INT, FLOAT, DOUBLE // for pointer we will use the same with ptrLevel > 0
}

// Enum for storage classes
enum class StorageClass { AUTO, STATIC, EXTERN };

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
    vector<bool> toWhichConst; // first for data, second for pointer, so on for multiple levels

    DTypeInfo(DataType dt=DataType::VOID, int ptr=0) : dataType(dt), ptrLevel(ptr) {
        toWhichConst.push_back(false);
    }

    DTypeInfo(string dtype){
        if(dtype.find("*") != string::npos){
            ptrLevel = count(dtype.begin(), dtype.end(), '*');
            dtype = dtype.substr(0, dtype.find("*"));
        }

        switch(dtype){
            case "int": dataType = DataType::INT; break;
            case "char": dataType = DataType::CHAR; break;
            case "float": dataType = DataType::FLOAT; break;
            case "double": dataType = DataType::DOUBLE; break;
            case "void": dataType = DataType::VOID; break;
            default: dataType = DataType::VOID;
        }
    }

    void setConst(bool isConst, int level=0){
        if(level >= toWhichConst.size()){
            toWhichConst.resize(level+1, false);
        }
        toWhichConst[level] = isConst;
    }

    int getSize(){
        if(ptrLevel == 0){
            if(dataType == DataType::INT || dataType == DataType::FLOAT){
                return WORD_SIZE;
            }else if(dataType == DataType::CHAR){
                return BYTE_SIZE;
            }else if(dataType == DataType::DOUBLE){
                return 2*WORD_SIZE;
            }
        } else if(ptrLevel > 0){
            return WORD_SIZE; // pointer size
        }
    }
}

// Derived class for variable information
class VariableInfo : public SymbolDetails {
public:
    DTypeInfo dataTypeInfo; // dataType and ptrLevel
    StorageClass storageClass; // AUTO by default
    int size; // Size of the variable in bytes
    int offset; //~~~~~ TODO in Code Generation Phase ~~~~~
    string initValue; //----TODO (what if it's not a literal)----

    VariableInfo( // Constructor with default values
        string dtype="void",
        StorageClass sc=StorageClass::AUTO,
        int sz=0,
        int off=0,
        string initVal=""
    )
    {
        // also check for pointer in string it can be anykind of pointer
        dataTypeInfo = DTypeInfo(dtype);
    }

    void setDataType(DataType dt) { dataType = dt; }
    void setStorageClass(StorageClass sc) { storageClass = sc; }
    void setSize(
        int sz = dataTypeInfo.getSize() // if size is not given, it will be calculated from dataType
    ) { size = sz; }
    void setOffset(int off) { offset = off; }
    void setConstant(string initVal) {
        dataTypeInfo.setConst(true);
        initValue = initVal; 
    }

    void display(
        ofstream& out=cout // default output stream is cout
    ) {
        out << "Data Type     : " << dataTypeInfo.dataType << "\n";
        out << "Pointer Level : " << dataTypeInfo.ptrLevel << "\n";
        out << "Storage Class : " << static_cast<int>(storageClass) << "\n";
        out << "Size          : " << size << "\n";
        out << "Offset        : " << offset << "\n";

        // ----ToDo for multiple levels of const----
        out << "isConstant    : " << (dataTypeInfo.toWhichConst[0]) ? "YES" : "NO" << "\n";
        out << "Init Value    : " << initValue << "\n";
    }
};

// Derived class for array information
class ArrayInfo : public SymbolDetails {
public:
    DTypeInfo elementTypeInfo; // dataType and ptrLevel of elements
    StorageClass storageClass; // AUTO by default
    vector<int> dimensions; // Dimensions of the array
    int totalSize; // Total size of the array in bytes
    int offset; //~~~~~ TODO in Code Generation Phase ~~~~~
    
    ArrayInfo(
        string dtype="void",
        StorageClass sc=StorageClass::AUTO,
        vector<int> dims={},
        int off=0
    )
    {
        elementTypeInfo = DTypeInfo(dtype);
        dimensions = dims;
        offset = off;
        setTotalSize();
    }

    void setDataType(DataType dt) { dataType = dt; }
    void setStorageClass(StorageClass sc) { storageClass = sc; }
    void setDimensions(vector<int> dims) { dimensions = dims; }
    void setTotalSize() {
        totalSize = elementTypeInfo.getSize();
        for(int dim : dimensions){
            totalSize *= dim;
        }
    }
    void setOffset(int off) { offset = off; }


    void display(
        ofstream& out=cout // default output stream is cout
    ) {
        out << "Data Type     : " << elementTypeInfo.dataType << "\n";
        out << "Pointer Level : " << elementTypeInfo.ptrLevel << "\n";
        out << "Storage Class : " << static_cast<int>(storageClass) << "\n";
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
    bool variadic; // Variadic function flag
    bool recursive; // Recursive function flag
    vector<pair<string, DTypeInfo>> parameters; // List of parameters
    bool defined; // Function definition flag
    void* address; // Function address ------ In Code Generation Phase ------

    FunctionInfo(
        string dtype="void",
        bool var=false,
        bool rec=false,
        bool def=false
    ) : 
        returnType(DTypeInfo(dtype)),
        variadic(var),
        recursive(rec),
        defined(def)
    {}

    void setReturnType(DataType dt) { returnType.dataType = dt; }
    void setVariadic(bool var) { variadic = var; }
    void setRecursive(bool rec) { recursive = rec; }
    void setDefined(bool def) { defined = def; }
    void setAddress(void* addr) { address = addr; }

    void addParameter(string name, string dtype) {
        parameters.push_back({name, DTypeInfo(dtype)});
    }

};

// Symbol Table Entry (Contains symbolKey, type, and pointer to details)
class SymbolEntry {
public:
    string symbolKey;
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
        string key,
        SymbolType type,
        SymbolDetails* det
    ) : symbolKey(key), symbolType(type), details(det) {}

    ~SymbolEntry() {
        delete details;
    }

    void display(
        ofstream& out=cout // default output stream is cout
    ) {
        out << "Symbol Key : " << symbolKey << "\n";
        out << "Symbol Type: " << static_cast<int>(symbolType) << "\n";
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
    }
};

// Symbol Table Class
class SymbolTable {
private:
    unordered_map<string, SymbolEntry*> table;

public:
    ~SymbolTable() {
        for (auto& pair : table) delete pair.second;
    }

    void insert(SymbolEntry* entry) {
        table[entry->symbolKey] = entry;
    }

    SymbolEntry* lookup(const string& symbolKey) {
        return table.count(symbolKey) ? table[symbolKey] : nullptr;
    }

    void display(
        ofstream& out=cout // default output stream is cout
    ) {
        for (auto& pair : table) {
            pair.second->display(out);
        }
    }
};

















#endif // SYM_H