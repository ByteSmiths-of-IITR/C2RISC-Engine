#ifndef SYM_H
#define SYM_H

#include <utility.h>

#define WORD_SIZE 4
#define BYTE_SIZE 1

const int MEMORY_MONITORING = 1;

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

#define CON_DES(clasName) clasName(){MEM(#clasName " Constructor");} ~clasName(){MEM(#clasName " Destructor");}
// We can define constructor and destructor in .h file itself since they get 


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

//Forward Declaration
class UserDType;
class SymbolDetails;

//--------------- TypeQualifier & StorageClassSpecifiers -----------------------------------------------------------
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

//---------------- Data Type [Level Supported] --------------------------------------------------------------------
class LevelInfo{
    public:
    
    //Constructor & Destructor
    CON_DES(LevelInfo)
};

class ArrayInfo : public LevelInfo{
    public:
        int dimSize;

        //Constructor & Destructor
};

class PointerInfo : public LevelInfo{
    public:
        std::vector<TypeQualifier> typeQualifiers;
        // This will have const, volatile, restrict

        //Constructor & Destructor
};

class BaseInfo : public LevelInfo{
    public:
        std::string baseType;
        // This is either primitive or struct or union (Record)
        std::vector<TypeQualifier> typeQualifiers;
        // This will have const, volatile, restrict
        StorageClass storageClass; // only one of these
        // This will have auto, static, extern

        // int size; // a dynamic value [no need to store can be calculated]

        // Constructor & Destructor
};

class DType{
    public:
        // D-Type INFO
        std::vector<std::string> levelType; // This 🧐 is redunant we can check type of LevelInfo itslelf by functions using dynamic_cast()
        std::vector<LevelInfo> levelInfo;

        //Constructor & Destructor
};

bool isArrayInfo(const LevelInfo& info);
bool isPointerInfo(const LevelInfo &info);
bool isBaseInfo(const LevelInfo &info);


//--------- Symbols Details & Their Derived Classes ☞ Stores [Variable,Function,EnumConstant] ---------------------
class SymbolDetails{
    public:
        // General Info
        // std::string symbolKey; Not needed
        std::pair<int,int> position; // line and column number [for error reporting]
        int scopeNo;                 // This will store the scope number

        // WE will use Inheritance to store specific info

        //Constructor & Destructor
};

class Variable : public SymbolDetails{
    public:
        // Variable Info
        std::string varName; // Name of the variable

        // DT Info
        DType dtype; // This will store the data type info of the variable

        // Initialization info [for now just pass the initializer ASTNode itself]
        ASTNode *intiailizer; //🚨 This will point to the initializer expression of this variable

        // Assembly Info
        int offset; // Offset from the base pointer

        //Constructor & Destructor
};

class EnumConstant : public SymbolDetails{
    public:
        // Enum Constant Info
        std::string enumConstName; // Name of the enum constant
        // The DType will be int by default
        UserDType* enumType; // This will store the user defined data type info of the enum constant

        // Value Info
        int value; // This will store the value of the enum constant

        //Constructor & Destructor

};

class Functions : public SymbolDetails{
    public:
        // Function Info
        std::string funcName; // Name of the function

        // Return Type Info
        DType returnType; // This will store the data type info of the return type
        // It can have storage class, type qualifiers, base type + level info

        // Parameter Info
        std::vector<Variable> parameters; // List of parameters
        // 🚨 These parameters are ❌ NOT allowed to have initializer(syntax checked), or stroage clas(semantic check)
        // clang uses `ParmVarDecl` for this [but we can use Variable]

        // Function Body
        // ASTNode *body; // This will point to the body of the function

        // Constructor & Destructor
};


//--------------------- Generic DBLinkedList & ScopeEnabledTable --------------------------------------------------
class DoublyLinkedList{
    public:
    DoublyLinkedList *next;
    DoublyLinkedList *prev;

    //Constructor & Destructor
    DoublyLinkedList(){
        this->next = nullptr;
        this->prev = nullptr;
        MEM("DoublyLinkedList Constructor");
    }

    ~DoublyLinkedList(){
        MEM("DoublyLinkedList Destructor");
    }

    void deleteCurrent(){
        if(this->prev){
            this->prev->next = this->next;
        }
        if(this->next){
            this->next->prev = this->prev;
        }
        delete this;
    }

    void insertAfter(DoublyLinkedList *node){
        node->next = this->next;
        node->prev = this;
        if(this->next){
            this->next->prev = node;
        }
        this->next = node;
    }

    void insertBefore(DoublyLinkedList *node){
        node->prev = this->prev;
        node->next = this;
        if(this->prev){
            this->prev->next = node;
        }
        this->prev = node;
    }
};

class Table{
    public:

    // This will be help in faster access to the symbol from it's key
    std::unordered_map<std::string, DoublyLinkedList*> table;

    std::vector<DoublyLinkedList *> listStack; // This will keep all symbols in order in definition
    std::vector<int> scopeBottom; // This will keep the index of the bottom of the scope in the symbolStack

    int scopeNo; // This will keep the current scope number [unique to each scope] [not like level]
    int NodeCount; // This will keep the count of the symbols in the table
    
    //Constructor & Destructor
    Table(){
        this->scopeNo = 0;
        this->NodeCount = 0;
        MEM("Table Constructor");
    }

    ~Table(){
        // CleanUp Code [📍 ToDo]
        // for(auto &pair : table){
        //     DoublyLinkedList *node = pair.second;
        //     while(node){
        //         DoublyLinkedList *temp = node;
        //         node = node->next;
        //         delete temp;
        //     }
        // }
        MEM("Table Destructor");
    }

    int enterScope(); // This will create a new scope and return the scope number
    void exitScope(); // This will remove all the symbols of the current scope

    // insert functions will be implemented in the derived classes
    // lookup functions will be implemented in the derived classes
};

// ------- SymbolList & ScopeEnbledTable ☞ Stores [Variable,Function,EnumConstant] --------------------------------
class SymbolList : public DoublyLinkedList{
    public:
    SymbolDetails *symbol;
    // This will store the symbol details

    //Constructor & Destructor
    SymbolList(SymbolDetails *sym){
        this->symbol = sym;
        MEM("SymbolList Constructor");
    }

    ~SymbolList(){
        delete this->symbol;
        MEM("SymbolList Destructor");
    }
};

class SymbolTable : public Table{
    public:
    // This will store the symbol table

    //Constructor & Destructor
    SymbolTable(){
        MEM("SymbolTable Constructor");
    }

    ~SymbolTable(){
        MEM("SymbolTable Destructor");
    }

    int insert(SymbolDetails *sym); // This will insert the symbol in the table
    /* Return 0 if symbol already exists
    Return 1 if symbol is inserted successfully
    */

    int insertVariable(Variable *var); // This will insert the variable in the table
    int insertFunction(Functions *func); // This will insert the function in the table
    int insertEnumConstant(EnumConstant *enumConst); // This will insert the enum constant in the table

    int lookup(const std::string &key, SymbolDetails *&sym); // This will return the symbol
    /* Return 0 if symbol not found
    Return 1 if symbol is found and is variable
    Return 2 if symbol is found and is function
    Return 3 if symbol is found and is enum constant
    Return 4 if symbol is found and is Unknown [🚨 This should not happen]
    */

};

bool isVariable(const SymbolDetails &sym);
bool isFunction(const SymbolDetails &sym);
bool isEnumConstant(const SymbolDetails &sym);

// ---------------------- User Defined Data Types + it's List + it's Table ----------------------------------------
class UserDType
{
    public:
    // used for struct, union, enum
    std::string typeName;   // Name of the type
    std::string recordType; // struct, union, enum
    int scopeNo;            // This will store the scope number in which this type is defined

    // Members of the recor
    std::unordered_map<std::string, Variable> members;
    // 🚨 These Variables are NOT ❌ allowed to have storage class, as they are part of the record

    //Constructor & Destructor
};

class UserDTypeList : public DoublyLinkedList
{
    public:
    UserDType *dtype;

    //Constructor & Destructor
    UserDTypeList(UserDType *dtype){
        this->dtype = dtype;
        MEM("UserDTypeList Constructor");
    }

    ~UserDTypeList(){
        delete this->dtype;
        MEM("UserDTypeList Destructor");
    }
};

class UserDTypeTable : public Table
{
    public:
    // This will store the user defined data types

    //Constructor & Destructor
    UserDTypeTable(){
        MEM("UserDTypeTable Constructor");
    }

    ~UserDTypeTable(){
        MEM("UserDTypeTable Destructor");
    }

    int insertRecord(UserDType *dtype); // This will insert the record in the table
    /* Return 0 if record already exists
    Return 1 if record is inserted successfully
    */

    int lookupRecord(const std::string &key, UserDType *&dtype); // This will return the record
    /* Return 0 if record not found
    Return 1 if record is found
    */
};

#endif // !SYM_H