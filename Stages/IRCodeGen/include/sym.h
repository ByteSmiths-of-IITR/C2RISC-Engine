#ifndef SYM_H
#define SYM_H

#include "utility.h"

// System Constants
#define WORD_SIZE 4 // int, float
#define WORD_SIZEx2 8 // double
#define BYTE_SIZEx2 2 // short
#define BYTE_SIZE 1 // 8 bits
#define ADDRESS_SIZE 16 // 64 bit address

// int, float - WORD_SIZE | long - WORD_SIZEx2 | long long - WORD_SIZEx2 | short - BYTE_SIZEx2
// double - WORD_SIZEx2 | long double - WORD_SIZEx2
// char - BYTE_SIZE
// pointer - ADDRESS_SIZE




extern int MEMORY_MONITORING;

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
class VarSymbols;
class GenericSymbol;

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
        LevelInfo(){
            MEM("LevelInfo Constructor");
        }

        virtual ~LevelInfo(){
            MEM("LevelInfo Destructor");
        } // Making it polymorphic
};

class ArrayInfo : public LevelInfo{
    public:
        int dimSize;

        //Constructor & Destructor
        CON_DES(ArrayInfo)
};

class PointerInfo : public LevelInfo{
    public:
        std::vector<TypeQualifier> typeQualifiers;
        // This will have const, volatile, restrict

        //Constructor & Destructor
        CON_DES(PointerInfo)
};

class BaseInfo : public LevelInfo{
    public:
        std::string baseType;
        // This is either primitive or struct or union (Record)
        std::vector<TypeQualifier> typeQualifiers;
        // This will have const, volatile, restrict
        // StorageClass storageClass; // only one of these [🚨 It's a variable property]
        // This will have auto, static, extern

        // int size; // a dynamic value [no need to store can be calculated]

        CON_DES(BaseInfo)

        int size() const;
};

int width(const BaseInfo &info); // This will return the width of the base type
// int width(const BaseInfo *info); // This will return the width of the base type

class DType{
    public:
        // D-Type INFO
        // std::vector<std::string> levelType; // This 🧐 is redunant we can check type of LevelInfo itslelf by Function using dynamic_cast()
        std::stack<LevelInfo*> levels; // bottom of the stack is the base type

        //Constructor & Destructor
        CON_DES(DType)

};


int width(const DType &dtype); // This will return the width of the data type
std::string toString(const DType &dtype); // This will return the string representation of the data type
int popALevel(DType &dtype); // This will pop a level from the dtype and 
/*Return value | 🚨 It's passed by ref so change will effect the original
    0 - if successful
    -1 - if not successful
*/

class TypeExpression
{
public:
    DType dtype; // This will be used as returnType of the function
    std::vector<DType> paramType; // This will be used as parameterType of the function
    /* For simple types, the paramType will be empty */
    

    //Constructor & Destructor
    TypeExpression()
    {
        MEM("TypeExpression Constructor");
    }

    ~TypeExpression()
    {
        MEM("TypeExpression Destructor");
    }

    TypeExpression(const DType &dtype, const std::vector<DType> &paramType)
    {
        MEM("TypeExpression Constructor 2");
        this->dtype = dtype;
        this->paramType = paramType;
    }
};

std::string toString(const TypeExpression &typeExpr); // This will return the string representation of the type expression
int popALevel(TypeExpression &typeExpr); // This will pop a level from the typeExpr and return 1 if successful else 0
//🚨 It's passed by referance to change will affect original
int width(const TypeExpression &typeExpr); // This will return the width of the returnType of the function


bool isArrayInfo(const LevelInfo& info);
// bool isArrayInfo(const LevelInfo* info);
bool isPointerInfo(const LevelInfo &info);
// bool isPointerInfo(const LevelInfo* info);
bool isBaseInfo(const LevelInfo &info);
// bool isBaseInfo(const LevelInfo* info);

//--------------------- Generic Symbol and Node & ScopeEnabledSymbolTable --------------------------------------------------
class GenericSymbol
{
public:
    // General Info
    std::pair<int, int> location; // This will store the location of the symbol in the source code
    std::string symbolName;       // This will store the name of the symbol
    int scopeNo;                  // This will store the scope number in which the symbol is declared

    // Constructor & Destructor
    GenericSymbol()
    {
        MEM("GenericSymbol Constructor");
    }

    virtual ~GenericSymbol()
    {
        MEM("GenericSymbol Destructor");
    }
};

class SymbolNode
{
public:
    GenericSymbol *symbol;
    SymbolNode *next;
    SymbolNode *prev;

    // Constructor & Destructor
    SymbolNode()
    {
        this->next = nullptr;
        this->prev = nullptr;
        MEM("SymbolNode Constructor");
    }

    ~SymbolNode()
    {
        MEM("SymbolNode Destructor");
    }

    void deleteCurrent();

    void insertAfter(SymbolNode *node);

    void insertBefore(SymbolNode *node);
};

class SymbolTable
{
public:
    // This will be help in faster access to the symbol from it's key
    std::unordered_map<std::string, SymbolNode *> symTable;

    std::stack<SymbolNode *> listStack; // This will keep all symbols in order in definition
    std::stack<int> scopeBottom;        // This will keep the index of the bottom of the scope in the symbolStack

    std::stack<int> lastScopeNo;
    int scopeNo; // This will keep the current scope number [unique to each scope] [not like level]
    int nextScopeNo;
    int NodeCount; // This will keep the count of the symbols in the SymbolTable

    // Constructor & Destructor
    SymbolTable()
    {
        this->scopeNo = -1;
        this->nextScopeNo = 0;
        this->NodeCount = 0;
        MEM("SymbolTable Constructor");
    }

    ~SymbolTable();

    int enterScope(); // This will create a new scope and return the scope number
    void exitScope(); // This will remove all the symbols of the current scope

    int insert(const std::string &key, GenericSymbol *symbol);
    // Returns 0 if the symbol is inserted successfully
    // Returns -1 if the symbol is already present in the current scope

    int lookup(const std::string &key, GenericSymbol *&sym);
    // Returns 0 if the symbol is found
    // Returns -1 if the symbol is not found

    int lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo); // This will lookinto the specific scope
    // Returns 0 if the symbol is found
    // Returns -1 if the symbol is not found

    int lookupNode(const std::string &key, SymbolNode *&node);
    // Return 0 on success and -1 on failure

    // Print the SymbolTable
    void printTable(std::ofstream &file);


};

bool isVarSymbols(const GenericSymbol &sym);
bool isUserDType(const GenericSymbol &sym);
//--
bool isVariable(const GenericSymbol &sym);
bool isEnumConstant(const GenericSymbol &sym);
bool isFunction(const GenericSymbol &sym);

//--------- Symbols Details & Their Derived Classes ☞ Stores [Variable,Function,EnumConstant] ---------------------
class VarSymbols : public GenericSymbol{
    public:
        // General Info [🚨 Not needed]

        // WE will use Inheritance to store specific info

        //Constructor & Destructor
        VarSymbols(){
            MEM("VarSymbols Constructor");
        }

        virtual ~VarSymbols(){
            MEM("VarSymbols Destructor");
        }
};

class Variable : public VarSymbols{
    public:
        // Variable Info [🚨 Not needed]

        // DT Info
        TypeExpression type; // This will store the data type info of the variable

        StorageClass storageClass; // It's a variable only property and not a property of the data type

        // Initialization info [for now just pass the initializer ASTNode itself]
        ASTNode *intiailizer; //🚨 This will point to the initializer expression of this variable

        // Assembly Info
        int offset; // Offset from the base pointer

        //Constructor & Destructor
        CON_DES(Variable)
};

class EnumConstant : public VarSymbols{
    public:
        // Enum Constant Info [🚨 Not needed]

        // The DType will be int by default
        UserDType* enumType; // This will store the user defined data type info of the enum constant

        // Value Info
        int value; // This will store the value of the enum constant

        //Constructor & Destructor
        CON_DES(EnumConstant)

};

class Function : public VarSymbols{
    public:
        // Function Info [🚨 Not needed]

        // DT Info
        TypeExpression type; // This will store the data type info of the function        

        // Parameters Info and Return Type are stored in TypeExpression itself
        // 🚨 These parameters are ❌ NOT allowed to have initializer(syntax checked), or stroage clas(syntax check)
        // clang uses `ParmVarDecl` for this [but we can use Variable]

        bool isDefined; // This will store whether the function is defined or not
        // TO handle forward declaration

        // Function Body
        // ASTNode *body; // This will point to the body of the function

        // Constructor & Destructor
        CON_DES(Function)
};



//--------------------- User Defined Data Type [Struct, Union, Enum] ----------------------------------------------

class UserDType : public GenericSymbol
{
public:
    // used for struct, union, enum
    std::string recordType; // struct, union, enum

    // Members of the recor
    std::unordered_map<std::string, TypeExpression> members;
    // 🚨 These Variables are NOT ❌ allowed to have storage class, as they are part of the record

    // Constructor & Destructor
    CON_DES(UserDType)
};

int width(const UserDType &dtype); // This will return the width of the user defined data type
std::string toString(const UserDType &dtype); // This will return the string representation of the user defined data type

//============================== [ Complete SymbolTable ]=====================================================

class AllSymbolTable {
    // This will have two instances of SymbolTable

    SymbolTable varTable;
    SymbolTable recordTable;

    //Constructor & Destructor
    AllSymbolTable(){
        MEM("AllSymbolTable Constructor");
    }

    ~AllSymbolTable(){
        MEM("AllSymbolTable Destructor");
    }

    // Member functions

    int enterScope(); // This will create a new scope and return the scope number
    void exitScope(); // This will remove all the symbols of the current scope

    int insert(const std::string &key, GenericSymbol*symbol);
    int insertRecord(const std::string &key, GenericSymbol*symbol);

    int lookup(const std::string &key, GenericSymbol *&sym);
    int lookupRecord(const std::string &key, GenericSymbol *&sym);

    int lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo);
    int lookupRecord(const std::string &key, GenericSymbol *&sym, int lookInScopeNo);

    void printVarTable(std::ofstream &file);
    void printRecordTable(std::ofstream &file);

    void printTable(std::ofstream &file);

    int lookupVarNode(const std::string &key, SymbolNode *&node);
    int lookupRecordNode(const std::string &key, SymbolNode *&node);
};

#endif // !SYM_H