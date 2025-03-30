#ifndef HEADER_H
#define HEADER_H

//====================[ GCC Header Files ]=========================================================================================
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>


//================== [Architecture Variables]=========================================================================================
#define WORD_SIZE 4 // int, float
#define WORD_SIZEx2 8 // double
#define BYTE_SIZEx2 2 // short
#define BYTE_SIZE 1 // 8 bits
#define ADDRESS_SIZE 16 // 64 bit address

//===================[ Memory Monitoring + Debugging ]============================================================================================
extern int MEMORY_MONITORING; // 0 - OFF | 1 - ON [value set by header.cpp]

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

#define CON_DES(clasName) clasName(){MEM(#clasName " Constructor");} ~clasName(){MEM(#clasName " Destructor");}

extern std::string lastFuncCalled;

#define debug std::cerr

const int BUG = -1000;

//~~~~~~[Forward Class Declarations]
class LevelInfo;
class GenericSymbol;

//=================== [ TypeExpressions Classes ] ============================================================================================


class TypeExpression{
        public:
            std::stack<LevelInfo*> levelStack;

            CON_DES(TypeExpression)
    };

        //~~~~~~~~~~~~~~~~[ TypeQualifiers & StorageClassSpecifiers Enum Classes ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        enum class TypeQualifier
        {
            CONST,
            VOLATILE,
            RESTRICT,
            UNKNOWN
        };

        enum class StorageClass
        {
            AUTO,
            STATIC,
            EXTERN,
            UNKNOWN
        };

        //~~~~~~~~~~~~~~~~[ SubLevel TypeExpressions Classes ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        class LevelInfo {
        public:
    
            LevelInfo() {
                MEM("LevelInfo Constructor");
            }
            virtual ~LevelInfo() { // Virtual Destructor
                MEM("LevelInfo Destructor");
            }
        };

        class ParenthesisInfo : public LevelInfo {
        public:
            // NO data - just a separator

            CON_DES(ParenthesisInfo)
        };

        class ArrayInfo : public LevelInfo {
        public:
            int dimSize; // size of the array

            CON_DES(ArrayInfo)
        };

        class PointerInfo : public LevelInfo {
        public:
            std::vector<TypeQualifier> typeQualifiers;

            CON_DES(PointerInfo)
        };
        
        class ParameterInfo : public LevelInfo {
        public:
            std::vector<TypeExpression> paramsType; // This will have the type of the parameters

            CON_DES(ParameterInfo)
        };
        
        //=====================[ BaseInfo ]=========================================================================================
            extern std::string STRUCT;
            extern std::string UNION;
            extern std::string ENUM;
            extern std::string ENUM_CONSTANT;
            extern std::string INT;
            extern std::string FLOAT;
            extern std::string DOUBLE;
            extern std::string CHAR;
            extern std::string SHORT;
            extern std::string LONG;
            extern std::string VOID;
            extern std::string LONG_LONG;
            extern std::string UNSIGNED; // will be used like - UNSIGNED + PRIMITIVE
            extern std::string SIGNED; // this will be used - PRIMITIVE [Default Signed]

        class BaseInfo : public LevelInfo {
        public:
            std::string baseType; // base type name
            std::vector<TypeQualifier> typeQualifiers; // type qualifiers

            CON_DES(BaseInfo)
        };


//=====================[ TypeExpression Utilities ]=========================================================================================

void removeTopParenthesis(TypeExpression &typeExpr);

enum class Type
{
    VARIABLE,      // Top is BaseInfo - primitive
    ARRAY,         // Top is ArrayInfo
    POINTER,       // Top is PointerInfo
    ENUM_CONSTANT, // Top is BaseInfo - enumConstant
    FUNCTION,      // Top is ParameterInfo
    STRUCT_UNION,  // Top is BaseInfo - Record - struct or union
    ENUM,          // Top is BaseInfo - Record - enum 
    EMPTY,
    UNKNOWN
};

Type whatIsType(const TypeExpression &typeExpr);

std::string toString(const TypeExpression &typeExpr);

// There is no isPopable function - you can check 'whatIsType' to check if it is popable or not

int popALevel(TypeExpression &typeExpr); // Clear's ParenthesisInfo
    //Return Values
    extern int const POP_SUCCESS;
    extern int const POP_FAILURE; // if empty

int width(const TypeExpression &typeExpr);

int checkEquivalance(const TypeExpression &typeExpr1, const TypeExpression &typeExpr2);
    // Return Values
    extern int const EQUIVALENT;
    extern int const WARNING;
    extern int const LOW_ERROR;
    extern int const HIGH_ERROR;

TypeExpression createTypeExpression(GenericSymbol *symbol); // This will create a type expression from the symbol

enum class SPACE
{
    ADDRESS_SPACE,
    VALUE_SPACE,
    UNKNOWN_SPACE
};

SPACE getSpace(const TypeExpression &typeExpr); // Tell's in what space should this type must be dealt with

bool isEmpty(const TypeExpression &typeExpr); // Ignores parenthesis

bool isModifiableLvalue(const TypeExpression &typeExpr); 

enum class VALUE_TYPE
{
    RVALUE,    // Read Only Value
    M_LVALUE,  // Modifiable LValue
    NM_LVALUE, // Non Modifiable LValue
    UNKNOWN
};

VALUE_TYPE getValueType(const TypeExpression &typeExpr); // Only Valid for Identifiers [not any general type expression]

    //================[ SubLevel Type's Utilities ]=========================================================================================
    int checkEquivalance(const LevelInfo &info1, const LevelInfo &info2);
        
    int checkEquivalance(const BaseInfo &info1, const BaseInfo &info2);
    int checkEquivalance(const PointerInfo &info1, const PointerInfo &info2);
    int checkEquivalance(const ArrayInfo &info1, const ArrayInfo &info2);
    int checkEquivalance(const ParameterInfo &info1, const ParameterInfo &info2);
    // int checkEquivalance(const ParenthesisInfo &info1, const ParenthesisInfo &info2); [Not Needed]


    int whichLevelInfo(const LevelInfo &info);
        // Return Values
        int const BASE_LEVEL = 0;
        int const POINTER_LEVEL = 1;
        int const ARRAY_LEVEL = 2;
        int const PARAMETER_LEVEL = 3;
        int const PARENTHESIS_LEVEL = 4;
        int const UNKNOWN_LEVEL = -1;
    
    bool isParenthesisInfo(const LevelInfo &info);
    bool isArrayInfo(const LevelInfo &info);
    bool isPointerInfo(const LevelInfo &info);
    bool isBaseInfo(const LevelInfo &info);
    bool isParameterInfo(const LevelInfo &info);


/*







*/


//=====================[ Symbols (VarSymbol & UserDType) | SymbolTable ]=========================================================================================

class GenericSymbol
{
public:
    // General Info
    std::pair<int, int> location; 
    std::string symbolName;      
    int scopeNo;            

    GenericSymbol()
    {
        MEM("GenericSymbol Constructor");
    }

    virtual ~GenericSymbol() // Virtual Destructor
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
    // Faster lookup
    std::unordered_map<std::string, SymbolNode *> symTable;

    std::stack<SymbolNode *> listStack; // Keep track of order of insertions
    std::stack<int> scopeBottom;        // Track the bottom marker to above stack of symbols

    std::stack<int> lastScopeNo; // A ancestor scope tracker
    int scopeNo; // This will keep the current scope number [unique to each scope] [not like level]
    int nextScopeNo;
    int NodeCount; // This will keep the count of the symbols in the SymbolTable

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
        // Return values
        int const INSERT_SUCCESS = 0; // Inserted Successfully
        int const INSERT_SUCCESS_WITH_WARNING = 1; // Inserted but had a same key in ancestor scope
        int const INSERT_FAILURE = -1; // Already present in the current scope

    int lookupRecord(const std::string &key, GenericSymbol *&sym);
    int lookup(const std::string &key, GenericSymbol *&sym);
        // Return values
        int const LOOKUP_SUCCESS = 0; // Found 
        int const LOOKUP_FAILURE = -1; // Not Found

    int lookupRecord(const std::string &key, GenericSymbol *&sym, int lookInScopeNo);
    int lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo); // This will lookinto the specific scope
        // Return values - same as above

    int lookupRecordNode(const std::string &key, SymbolNode *&node);
    int lookupNode(const std::string &key, SymbolNode *&node);
        // Return values - same as above

    void printTable(std::ofstream &file);
};

    //=====================[ VarSymbols ]=========================================================================================
        // Class VarSymbols NotNeeded

        class Variable : public GenericSymbol {
        public:
            TypeExpression type; 
            
            StorageClass storageClass; 

            // Think about Initialized values ? [ToThink 🧠]

            CON_DES(Variable)
        };

        class EnumConstant : public GenericSymbol {
        public:
            int value; // This will be loaded directly [a compile time constant]

            CON_DES(EnumConstant)
        };

        class Function : public GenericSymbol {
        public:
            TypeExpression type; // This will also hold the parameter(top) + (all below)returnType

            bool isDefined; // To deal with forward declaration

            CON_DES(Function)
        };

    // =====================[ User Defined Data Type ]=========================================================================================

        enum class RecordType
        {
            STRUCT,
            UNION,
            ENUM,
            NONE
        };

        class UserDType : public GenericSymbol {
        public:
            RecordType recordType; // This will be used for struct, union, enum

            // Members of the record
            std::unordered_map<std::string, TypeExpression> members; // Enum won't use this

            CON_DES(UserDType)
        };

//=====================[ Symbol Utilities ]=========================================================================================

bool isVariable(const GenericSymbol &sym);
bool isEnumConstant(const GenericSymbol &sym);
bool isFunction(const GenericSymbol &sym);
bool isUserDType(const GenericSymbol &sym);

std::string newRecordName(); // For Un-Named Struct/Union/Enum

std::string const RECORD_PREFIX = "RECORD_"; // Prefix for Record Names

int width(const UserDType &dtype); // This will return the width of the user defined data type


/*





*/

//=====================[ Three Address Code ]=========================================================================================

    //==================[ Custom TAC Arguments ]=========================================================================================
        const std::string NO_ARG = "";


class TAC_Quadruple{
    public:
        std::string op;
        std::string arg1;
        std::string arg2;
        std::string result;

        CON_DES(TAC_Quadruple)

        TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result);

        std::string toString() const;
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

        void printTAC(std::ofstream &file);
        void printTAC(); // prints to stdout
};


/*





*/


//=====================[ TypeChecking Utilities 🅰️ ]=========================================================================================

bool isIntegral(const TypeExpression &typeExpr);



//======================[ TypeCasting Utilities 🆎 ]=========================================================================================



/*






*/

//=====================[ Non-Terminal DataStructure ]=========================================================================================

class BaseData
{
public:
    BaseData()
    {
        MEM("BaseData Constructor");
    }
    virtual ~BaseData()
    {
        MEM("BaseData Destructor");
    }
};

class ExpressionData : public BaseData
{
public:
    // syn_Attributes to be passed up ⬆️
    std::string varName;
    TypeExpression type;
    VALUE_TYPE valueType;
    SPACE valueSpace;

    // inh_Attributes to be passed down ⬇️
    std::string whereToSendString; // ❓ Check if needed
};

class DeclarationData : public BaseData
{
public:
    // syn_Attributes to be passed up ⬆️
    TypeExpression type;
    std::string varName;

    // inh_Attributes to be passed down ⬇️
    TypeExpression inh_type;
    StorageClass inh_storageClass;
};

#endif // !HEADER_H