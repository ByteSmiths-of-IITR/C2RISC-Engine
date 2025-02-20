#ifndef SYM_H
#define SYM_H

#define MAX_SCOPE 1000
#define WORD_SIZE 4
#define BYTE_SIZE 1

//Include all the necessary headers
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <initializer_list> 

// Enum class for symbols types, data types and storage classes

    enum class SymbolType {
        VARIABLE, FUNCTION, ARRAY
        /*,STRUCT, ENUM, UNION */
    };
    std::string getSymbolString(SymbolType st);

    enum class DataType {
        VOID, CHAR, INT, FLOAT, DOUBLE, INVALID
    };
    std::string dTypeString(DataType dt);
    DataType getDataType(const std::string& baseType);

    enum class StorageClass {
        AUTO, STATIC, EXTERN
    };
    std::string getStorageClassString(StorageClass sc);

// DType Information class
class DTypeInfo {
public:
    DataType dataType;
    int ptrLevel;
    std::vector<bool> toWhichConst; // first for data, second for pointer, so on for multiple levels


    DTypeInfo(DataType dt=DataType::VOID, int ptr=0);
    DTypeInfo(const std::string& dtype); 

    void setConst(int level=0, bool isConst=true); // level 0 means data is const
    int getSize() const; // returns size of the data type
    void isPointer(int level=1); // set ptrLevel to level [for multi-level pointers]
    bool isConst(int level=0); // check if data is const at level

    void display(std::ostream& out = std::cout) const;
};

// Base class for symbol-specific details (to be extended)
    class SymbolDetails {
    protected:
        std::string symbolName;
        int lineNo;
    public:
        SymbolDetails(const std::string &name, int line);
        virtual ~SymbolDetails() = default; // making it virtual to allow dynamic_cast
    };

// Variable Information class

class VariableInfo : public SymbolDetails {
    public:
    DTypeInfo variableType; // store dataType Info of the variable
    StorageClass storageClass; // how the variable is stored [AUTO by default, STATIC - global, EXTERN - external]
    int offset; // offset from the base pointer [will be calculated in Code Generation Phase]

    // ------ToDo (Initialization Value is not simple string, it can be a complex expression)--
    std::string initValue; // initial value of the variable [for initialization]


    VariableInfo( 
        const int lineNo,
        const std::string& VarName,
        const std::string& baseType="void",
        StorageClass sc=StorageClass::AUTO,
        int off=0,
        const std::string& initVal=""
    );

    // Setter Functions
    void setVarDType(DataType dt);
    void setVarStorage(StorageClass sc=StorageClass::AUTO);
    void setVarConst(int level=0, bool isConst=true);

    // Variable Specific Functions
    void setInitialValue(const std::string& initVal);
    void setOffset(int off); // [for Code Generation Phase]
    void setDataConst(const std::string& initVal); // set data as constant

    // Getter Functions
    bool isDataConst() const;
    bool isPtrConst() const ;
    bool isConst(int level=0) const;
    bool isPointer() const;
    bool isInited() const;

    void display(std::ostream& out = std::cout) const;

};

// ArrayInfo Class Declaration
    class ArrayInfo : public SymbolDetails {
        public:
        DTypeInfo elementTypeInfo; // store dataType Info of the elements
        StorageClass storageClass; // how the array is stored [AUTO by default, STATIC - global, EXTERN - external]
        std::vector<int> dimensions; // [for multi-dimensional arrays]
        int totalSize; 
        int offset; // offset from the base pointer [will be calculated in Code Generation Phase]
        bool isArrConst; // flag to check if array as a pointer is constant [not the data(that is stored in element's properties)]

    // Array get's initialized with the default values


    /* Few points about const havoc
    - if data element is const, then all dimensions are const [ ie - arr[0][0]++ is not allowed]
    - if isArrConst it's about the pointer to array is const [ ie - arr++ is not allowed]
    */

        ArrayInfo(
            const int lineNo,
            const std::string& arrayName,
            const std::string& elementDType="void",
            StorageClass sc=StorageClass::AUTO,
            std::vector<int> dims={},
            int off=0
        );

        // Setter Functions
        void setElementType(const std::string& dtype);
        void setElementTypeInfo(DTypeInfo dt);
        void setElementAsPointer(int level=1);
        void setElementAsConst(int level=0, bool isConst=true);
        void setArrConst(bool isConst=true);
        void setStorageClass(StorageClass sc=StorageClass::AUTO);
        void setDimensions(std::vector<int> dims);
        void addDimension(int dim);
        void setTotalSize();
        void setOffset(int off);

        // Getter Functions
        // bool isArrConst();
        bool isDataConst(int level=0);
        bool isDataPointer();
        std::vector<int> getDimensions();
        int getTotalSize();

        void display(std::ostream& out = std::cout) const;

};

class ArgumentInfo {
    public:
    std::string argName;
    bool isPassedByRef;
    DTypeInfo argType; // store baseType, ptrLevel, constLevel of the argument

    ArgumentInfo(
        const std::string& name,
        const std::string& dtype,
        bool isConst=false,
        bool isRef=false
    );

    void setArgDType(const std::string& dtype);
    void setArgAsPointer(int level);
    void setArgAsConst(int level, bool isConst);
    void setPassedByRef(bool isRef);

    void display(std::ostream& out = std::cout) const;
};

// Function Information class
class FunctionInfo : public SymbolDetails {
    public:
    DTypeInfo returnType; // store dataType Info of the return type
    StorageClass storageClass; // how the function is stored [AUTO by default, STATIC - global, EXTERN - external]
    bool isFuncConst; // const flag for function [means no modification of any variable inside]
    bool isVariadic; // flag to check if function is variadic [can take variable number of arguments]
    bool isRecursive; // flag to check if function is recursive
    bool isDefined; // flag to check if function is defined
    void* address; // Function address ------ In Code Generation Phase ------
    std::vector<ArgumentInfo> parameters; // List of parameters

    FunctionInfo(
        const int lineNo,
        const std::string& funcName,
        const std::string& dtype="void",
        bool isConst=false,
        bool isVar=false,
        bool isRec=false,
        bool isDef=false,
        void* addr=nullptr
    );

    // Setter Functions
    void setReturnType(DataType dt);
    void setFunctionAsConst(bool isConst=1);
    void setVariadic(bool isVar=1);
    void setRecursive(bool isRec=1);
    void setDefined(bool isDef=1);
    void setAddress(void* addr);
    void addParameter(const std::string& name, const std::string& dtype, bool isConst=false, bool isRef=false, int ptrLevel=0);
    void addParameter(const ArgumentInfo& arg);
    
    // Getter Functions
    // bool isFunctionConst();
    // bool isFunctionVariadic();
    // bool isFunctionRecursive();
    // bool isFunctionDefined();
    void* getAddress();
    std::vector<ArgumentInfo> getParameters();

    void display(std::ostream& out = std::cout) const;
};

// Symbol Entry class
    class SymbolEntry {
        public:
        std::string symbolKey; // Key of the symbol
        SymbolType symbolType; // Type of the symbol
        SymbolDetails* details; // Pointer to the details

        SymbolEntry(
            const std::string& key,
            SymbolType type,
            SymbolDetails* det
        );

        ~SymbolEntry();

        void display(std::ostream& out=std::cout) const;
    };
    
// Symbol Table Class

    class SymbolTable {
        private:
        std::unordered_map<std::string, SymbolEntry*> table;

        public:
        ~SymbolTable();

        void insert(SymbolEntry* entry);
        SymbolEntry* lookup(const std::string& symbolKey);

        void display(std::ostream& out=std::cout) const;
    };


#endif // SYM_H