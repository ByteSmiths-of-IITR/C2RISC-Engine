#ifndef SYM_H
#define SYM_H

#include "utility.h"
#include "tac.h"
#include "semantic.h"

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

const std::string RECORD_PREFIX = "record "; // will be used for struct & union

extern int MEMORY_MONITORING;

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

#define CON_DES(clasName) clasName(){MEM(#clasName " Constructor");} ~clasName(){MEM(#clasName " Destructor");}
// We can define constructor and destructor in .h file itself since they get 


// String used in BaseInfo to show Record or Primitive
std::string STRUCT = "struct"; // used as prefix
std::string UNION = "union"; // used as prefix
std::string ENUM = "enum"; // used as prefix
std::string ENUM_CONSTANT = "enumConstant"; // used as exactName
std::string INT = "int"; // used as exactName
std::string FLOAT = "float"; // used as exactName
std::string DOUBLE = "double"; // used as exactName
std::string CHAR = "char"; // used as exactName
std::string SHORT = "short"; // used as exactName
std::string LONG = "long"; // used as exactName
std::string LONG_LONG = "long long"; // used as exactName
std::string VOID = "void"; // used as exactName

// Strings used in SymbolTable key
// For variable - exactName 
// For function - exactName
// For enum constants - exactName


// To Check which type it is - get UserDType and it's recordType
// For struct - "record" + " " + exactName + " " + scopeNo
// For union - "record" + " " + exactName + " " + scopeNo
// For enum objects - "record" + " " + exactName + " " + scopeNo





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
enum class TypeQualifier
{ // 👍
    CONST,
    VOLATILE,
    RESTRICT
};

enum class RecordType{ 
    STRUCT,
    UNION,
    ENUM,
    NONE
};

enum class StorageClass{ //👍
    AUTO,
    STATIC,
    EXTERN
};

//---------------- Sub-Level TypeExpression [Level Supported] --------------------------------------------------------------------
class LevelInfo{
    public:
        //Constructor & Destructor
        LevelInfo(){
            MEM("LevelInfo Constructor");
        }
        virtual ~LevelInfo(){
            MEM("LevelInfo Destructor");
        }
};

class ParenthesisInfo : public LevelInfo{
    public:
        // NO data - just a separator

        //Constructor & Destructor
        CON_DES(ParenthesisInfo)
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
        // This is either primitive or struct or union or enumConstant (Record)
        
        /*Rules of Record baseType
        name = "struct" | "union" | "enum" + " " + "name" + " " + "scopeNo"
        
        */
        // RecordType recordType; // This will be used for struct, union, enum
        // NotNeeded

        std::vector<TypeQualifier> typeQualifiers;
        // This will have const, volatile, restrict
        

        
        // StorageClass storageClass; // only one of these [🚨 It's a variable property]
        // This will have auto, static, extern

        // int size; // a dynamic value [no need to store can be calculated]

        CON_DES(BaseInfo)

        int size() const;
};

class ParameterInfo : public LevelInfo{
    public:
        std::vector<TypeExpression> paramsType;

        //Constructor & Destructor
        CON_DES(ParameterInfo)
};

int width(const BaseInfo &info); // primitive type's width
/* Logic
- for primitives - check arch variable
- for (Struct,Union) user defined - ask symbol table for record & calculate the width
- for enum - check size == int
*/

/* Equivalance Check Outputs
0 - Equivalent
1 - Warning
-1 - Not Equivalent [Error]
*/

int checkEquivalance(const LevelInfo &info1, const LevelInfo &info2);

int checkEquivalance(const BaseInfo &info1, const BaseInfo &info2);
int checkEquivalance(const PointerInfo &info1, const PointerInfo &info2);
int checkEquivalance(const ArrayInfo &info1, const ArrayInfo &info2);
int checkEquivalance(const ParameterInfo &info1, const ParameterInfo &info2);
// int checkEquivalance(const ParenthesisInfo &info1, const ParenthesisInfo &info2);


bool isParenthesisInfo(const LevelInfo &info);
bool isArrayInfo(const LevelInfo &info);
bool isPointerInfo(const LevelInfo &info);
bool isBaseInfo(const LevelInfo &info);
bool isParameterInfo(const LevelInfo &info);

int whichLevelInfo(const LevelInfo &info);

// $output of whatIsLevelInfo
int const BASE_LEVEL = 0;
int const POINTER_LEVEL = 1;
int const ARRAY_LEVEL = 2;
int const PARAMETER_LEVEL = 3;
int const PARENTHESIS_LEVEL = 4;
int const UNKNOWN_LEVEL = -1;

//---------------- TypeExpression [Level] -------------------------------------------------------------------
class TypeExpression
{
public:
    std::stack<LevelInfo *> levelStack; // Instead of stack we can have {LevelInfo* current; TypeExpression below}
    // ☢️ Pay Attention LevelInfo is pointer thus a copy made for TypeExpression will not copy the LevelInfo
    
    /* LevelInfo Rules
    - BaseInfo
        - width = width of the base type

    - PointerInfo
        - width = ADDRESS_SIZE

    - ArrayInfo
        - width = size of the array * width of the below TypeExpression

    - ParameterInfo
        - width = 1

    - ParenthesisInfo
        - width = width of the below TypeExpression

    # Restrictions
        - BaseInfo always be at the bottom

        - ArrayInfo top of ParameterInfo -> ERROR(declared as array of functions)

        - ParameterInfo on top of ParameterInfo -> ERROR(function cannot return function)
        - ParameterInfo on top of ArrayInfo -> ERROR(function cannot return array)
    
        PoP a level has different meaning
        returnType if top was ParameterInfo
        elementType if top was ArrayInfo
        pointerElementType if top was PointerInfo
        base is UnPopable
        */

    TypeExpression()
    {
        MEM("TypeExpression Constructor");
    }

    ~TypeExpression()
    {
        MEM("TypeExpression Destructor");
    }
};

// ########## TypeExpression Utilities ###################################################################

bool topIsParenthesis(const TypeExpression &typeExpr); // Logic = Check if top is ParenthesisInfo
bool topIsArray(const TypeExpression &typeExpr); // Logic = Check if top is ArrayInfo
bool topIsPointer(const TypeExpression &typeExpr); // Logic = Check if top is PointerInfo
bool topIsBase(const TypeExpression &typeExpr); // Logic = Check if top is BaseInfo
bool topIsParameter(const TypeExpression &typeExpr); // Logic = Check if top is ParameterInfo

Expr_Type whichTypeExpression(const TypeExpression &typeExpr); // Logic = Check what is the top level of the type expression

TypeExpression createTypeExpression(GenericSymbol *symbol); 

std::string toString(const TypeExpression &typeExpr); 
// Logic = Remove top-parenthesis if any
int popALevel(TypeExpression &typeExpr); // This will pop a level from stack<LevelTypeExpression> of the data type
//🚨 It's passed by referance to change will affect original
int width(const TypeExpression &typeExpr); 
// Width logic of each level type is written in the TypeExpression class
int checkEquivalance(const TypeExpression &typeExpr1, const TypeExpression &typeExpr2); 
/* Logic
- During type checking all parenthesis are ignored - not just top ones
*/

SPACE getSpace(const TypeExpression &typeExpr); // This will return the space of the type expression

// $output of checkEquivalance
int const OKAY = 0;
int const WARNING = -1;
int const LOW_ERROR = -2;
int const HIGH_ERROR = -3;

bool isEmpty(const TypeExpression &typeExpr); // This will check if the type expression is empty

void removeTopParenthesis(TypeExpression &typeExpr); // This will remove all the parenthesis from the type expression

// VALUE_TYPE getValueType(const TypeExpression &typeExpr); // This will return the value type of the type expression
// bool isLvalue(const TypeExpression &typeExpr); // This will check if the type expression is Lvalue or not
// bool isRvalue(const TypeExpression &typeExpr); // This will check if the type expression is Rvalue or not
// ❌ Not possible to check just on basis of TypeExpression


bool isModifiableLvalue(const TypeExpression &type);
/*Logic of Non-Modifialbe LAVLUE
- top is ArrayInfo, ParameterInfo
- top is PointerInfo or BaseInfo with "const" qualifier
- if BaseInfo - need to check for RecordType;
    struct & union are not modifiable
*/

VALUE_TYPE getValueType(const TypeExpression &typeExpr);

// #################################################################################################################

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

    int insertRecord(const std::string &key, GenericSymbol *symbol);
    int insert(const std::string &key, GenericSymbol *symbol);
    // Returns 0 if the symbol is inserted successfully
    // Returns -1 if the symbol is already present in the current scope
    
    int lookupRecord(const std::string &key, GenericSymbol *&sym);
    int lookup(const std::string &key, GenericSymbol *&sym);
    // Returns 0 if the symbol is found
    // Returns -1 if the symbol is not found

    int lookupRecord(const std::string &key, GenericSymbol *&sym, int lookInScopeNo);
    int lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo); // This will lookinto the specific scope
    // Returns 0 if the symbol is found
    // Returns -1 if the symbol is not found

    int lookupRecordNode(const std::string &key, SymbolNode *&node);
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

        // Type Info
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
        // UserDType* enumType; // This will store the user defined data type info of the enum constant

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
    RecordType recordType; // This will be used for struct, union, enum

    // Members of the record
    std::unordered_map<std::string, TypeExpression> members;
    // [Handled 👍] These Variables are NOT ❌ allowed to have storage class, as they are part of the record

    // Constructor & Destructor
    CON_DES(UserDType)
};

std::string newRecordName();

int width(const UserDType &dtype); // This will return the width of the user defined data type
std::string toString(const UserDType &dtype); // This will return the string representation of the user defined data type
int checkEquivalance(const UserDType &dtype1, const UserDType &dtype2); 
/*Logic
- struct & union different scope - give error
- enum in different scope - give warning
*/

//============================== [ Complete SymbolTable ]=====================================================
/* NOT NEEDED
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

*/

#endif // !SYM_H