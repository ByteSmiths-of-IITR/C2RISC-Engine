
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Enum for symbol types
enum class SymbolType { VARIABLE, FUNCTION, ARRAY, POINTER, STRUCT, ENUM, UNION };

// Enum for data types
enum class DataType { INT, CHAR, FLOAT, VOID, CUSTOM };

// Enum for storage classes
enum class StorageClass { AUTO, STATIC, EXTERN };

// Base class for symbol-specific details (to be extended)
class SymbolDetails {
public:
    virtual ~SymbolDetails() = default;
};

// Derived class for variable information
class VariableInfo : public SymbolDetails {
public:
    DataType dataType;
    StorageClass storageClass;
    int size;
    int offset;
    bool isPointer;

    VariableInfo(DataType dt, StorageClass sc, int sz, int off, bool ptr)
        : dataType(dt), storageClass(sc), size(sz), offset(off), isPointer(ptr) {}
};

// Derived class for array information
class ArrayInfo : public SymbolDetails {
public:
    DataType dataType;
    StorageClass storageClass;
    vector<int> dimensions;

    ArrayInfo(DataType dt, StorageClass sc, vector<int> dims)
        : dataType(dt), storageClass(sc), dimensions(dims) {}
};

// Derived class for function information
class FunctionInfo : public SymbolDetails {
public:
    DataType returnType;
    vector<pair<string, DataType>> parameters;
    bool isVariadic;
    bool isRecursive;
    bool isDefined;

    FunctionInfo(DataType retType, bool varArgs, bool rec)
        : returnType(retType), isVariadic(varArgs), isRecursive(rec), isDefined(false) {}

    void addParameter(string name, DataType type) {
        parameters.push_back({name, type});
    }
};

// Symbol Table Entry (Contains name, type, and pointer to details)
class SymbolEntry {
public:
    string name;
    SymbolType symbolType;
    SymbolDetails* details;

    SymbolEntry(string n, SymbolType sType, SymbolDetails* det)
        : name(n), symbolType(sType), details(det) {}

    ~SymbolEntry() { delete details; }  // Ensure memory cleanup
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
        table[entry->name] = entry;
    }

    SymbolEntry* lookup(const string& name) {
        return table.count(name) ? table[name] : nullptr;
    }

    void display() {
        cout << "Name\tType\n";
        for (const auto& pair : table) {
            cout << pair.first << "\t" << static_cast<int>(pair.second->symbolType) << "\n";
        }
    }
};
