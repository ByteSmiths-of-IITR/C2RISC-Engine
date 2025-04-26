#ifndef HEADER_H
#define HEADER_H

#include "utility.h"

//====================[ Globaly Accessible SymbolTable & TAC-CodeBase ]=========================================================================================

//====================[ Annotated PTree Utilities ]=========================================================================================

extern int ANNOTATE; // 0 - OFF | 1 - ON [value set by header.cpp]

//================== [Architecture Variables]=========================================================================================
#define WORD_SIZE 4    // int, float
#define WORD_SIZEx2 8  // double, long
#define WORD_SIZEx4 16 // long double or long long
#define BYTE_SIZEx2 2  // short
#define BYTE_SIZE 1    // 8 bits, char
#define ADDRESS_SIZE 4 // 32 bit address

//===================[ Memory Monitoring + Debugging ]============================================================================================
extern int MEMORY_MONITORING; // 0 - OFF | 1 - ON [value set by header.cpp]

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

#define CON_DES(clasName)                         \
    clasName() { MEM(#clasName " Constructor"); } \
    ~clasName() { MEM(#clasName " Destructor"); }

extern std::string lastFuncCalled;

#define debug std::cerr

const int BUG = -1000;

//~~~~~~[Forward Class Declarations]
class LevelInfo;
class GenericSymbol;

//=================== [ TypeExpressions Classes ] ============================================================================================

int const BASE_LEVEL = 0;
int const POINTER_LEVEL = 1;
int const ARRAY_LEVEL = 2;
int const PARAMETER_LEVEL = 3;
int const PARENTHESIS_LEVEL = 4;
int const UNKNOWN_LEVEL = -1;

class TypeExpression
{
public:
    std::vector<LevelInfo *> levelStack;

    CON_DES(TypeExpression)
};

//~~~~~~~~~~~~~~~~[ TypeQualifiers & StorageClassSpecifiers Enum Classes ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum class TypeQualifier
{
    CONST,
    VOLATILE,
    RESTRICT,
    UNKNOWN,
    NONE
};

enum class StorageClass
{
    AUTO,
    STATIC,
    EXTERN,
    NONE,
    UNKNOWN,
    TYPEDEF // This will be used for typedef
};

//~~~~~~~~~~~~~~~~[ SubLevel TypeExpressions Classes ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class LevelInfo
{
public:
    int levelType; // This will be used to keep track of the level number
    LevelInfo()
    {
        MEM("LevelInfo Constructor");
    }
    virtual ~LevelInfo()
    { // Virtual Destructor
        MEM("LevelInfo Destructor");
    }
};

class ParenthesisInfo : public LevelInfo
{
public:
    // NO data - just a separator

    ParenthesisInfo()
    {
        levelType = PARENTHESIS_LEVEL;
        MEM("ParenthesisInfo Constructor");
    }
    ~ParenthesisInfo()
    {
        MEM("ParenthesisInfo Destructor");
    }
};

class ArrayInfo : public LevelInfo
{
public:
    int dimSize; // size of the array

    ArrayInfo()
    {
        dimSize = -1; // Default value
        levelType = ARRAY_LEVEL;
        MEM("ArrayInfo Constructor");
    }
    ~ArrayInfo()
    {
        MEM("ArrayInfo Destructor");
    }
};

class PointerInfo : public LevelInfo
{
public:
    std::vector<TypeQualifier> typeQualifiers;

    PointerInfo()
    {
        levelType = POINTER_LEVEL;
        MEM("PointerInfo Constructor");
    }
    ~PointerInfo()
    {
        MEM("PointerInfo Destructor");
    }
};

class ParameterInfo : public LevelInfo
{
public:
    bool isAbstract;
    bool isVaradic;
    std::vector<std::string> paramsName;
    std::vector<TypeExpression> paramsType; // This will have the type of the parameters
    bool isVariadic;                        // This will be used to check if the function is variadic or not
    ParameterInfo()
    {
        levelType = PARAMETER_LEVEL;
        isAbstract = false;
        MEM("ParameterInfo Constructor");
    }
    ~ParameterInfo()
    {
        MEM("ParameterInfo Destructor");
    }
};

//=====================[ BaseInfo ]=========================================================================================
extern std::string TYPE_STRUCT;
extern std::string TYPE_UNION;
extern std::string TYPE_ENUM;
extern std::string ENUM_CONSTANT;

extern std::string TYPE_VOID;

extern std::string TYPE_VA_LIST;
extern std::string VARADIC;
extern std::string TYPE_QUALIFIERS;

extern std::string TYPE_FLOAT;
extern std::string TYPE_DOUBLE;
extern std::string TYPE_LONG_DOUBLE;

extern std::string TYPE_CHAR;
extern std::string TYPE_SHORT;
extern std::string TYPE_INT;
extern std::string TYPE_LONG;
extern std::string TYPE_LONG_LONG;

extern std::string TYPE_UNSIGNED; // will be used like - UNSIGNED + PRIMITIVE
extern std::string TYPE_SIGNED;   // this will be used - PRIMITIVE [Default Signed]

class BaseInfo : public LevelInfo
{
public:
    std::string baseType;                      // base type name
    std::vector<TypeQualifier> typeQualifiers; // type qualifiers

    BaseInfo()
    {
        levelType = BASE_LEVEL;
        MEM("BaseInfo Constructor");
    }
    ~BaseInfo()
    {
        MEM("BaseInfo Destructor");
    }
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
std::string toString(Type whichType);
// There is no isPopable function - you can check 'whatIsType' to check if it is popable or not

int popALevel(TypeExpression &typeExpr); // Clear's ParenthesisInfo
// Return Values
extern int const POP_SUCCESS;
extern int const POP_FAILURE; // if empty

int width(std::string primType); // This will return the width of the primitive type

int width(const TypeExpression &typeExpr);

int ourEquivalent(const TypeExpression &type1, const TypeExpression &type2);

int typeResolution(const TypeExpression &target, const TypeExpression &soucre);

int typeResoulution(const std::string &target, const std::string &source);

int checkEquivalance(const TypeExpression &typeExpr1, const TypeExpression &typeExpr2);
// Return Values
extern const int OKAY;
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

int width(const BaseInfo &info);

int whichLevelInfo(const LevelInfo &info);
// Return Values
// int const BASE_LEVEL = 0;
// int const POINTER_LEVEL = 1;
// int const ARRAY_LEVEL = 2;
// int const PARAMETER_LEVEL = 3;
// int const PARENTHESIS_LEVEL = 4;
// int const UNKNOWN_LEVEL = -1;

bool isParenthesisInfo(const LevelInfo &info);
bool isArrayInfo(const LevelInfo &info);
bool isPointerInfo(const LevelInfo &info);
bool isBaseInfo(const LevelInfo &info);
bool isParameterInfo(const LevelInfo &info);

/*



                                    SYMBOL TABLE



*/

//=====================[ Symbols (VarSymbol & UserDType) | SymbolTable ]=========================================================================================

enum class SYMBOL_TYPE
{
    VARIABLE,
    ENUM_CONSTANT,
    FUNCTION,
    USER_DTYPE,
    TYPEDEF,
    NONE
};

class GenericSymbol
{
public:
    // General Info
    std::pair<int, int> location;
    std::string symbolName;
    int scopeNo;
    SYMBOL_TYPE symbolType; // This will be used to identify the type of symbol

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

// Return values of insert()
extern int const INSERT_SUCCESS;              // Inserted Successfully
extern int const INSERT_SUCCESS_WITH_WARNING; // Inserted but had a same key in ancestor scope
extern int const INSERT_FAILURE;              // Already present in the current scope

// Return values of lookup()
extern int const LOOKUP_SUCCESS; // Found
extern int const LOOKUP_FAILURE; // Not Found

extern std::string GLOBAL_SCOPE;
extern std::string LOCAL_SCOPE;
extern int NO_EXIT;
extern int IGNORED;
class SymbolTable
{
public:
    // Faster lookup
    std::map<std::string, SymbolNode *> symTable;

    std::stack<SymbolNode *> listStack; // Keep track of order of insertions
    std::stack<int> scopeBottom;        // Track the bottom marker to above stack of symbols

    int globalScope;

    std::string currnetScope;
    bool wasEarlyEntered; // This will be used to ignore the next entry in the symbol table

    std::stack<int> lastScopeNo; // A ancestor scope tracker
    int scopeNo;                 // This will keep the current scope number [unique to each scope] [not like level]
    int nextScopeNo;
    int NodeCount; // This will keep the count of the symbols in the SymbolTable

    SymbolTable()
    {
        this->scopeNo = -1;
        this->nextScopeNo = 0;
        this->NodeCount = 0;
        this->globalScope = -100;
        this->wasEarlyEntered = false;
        this->currnetScope = "NONE"; // This will be used to find the name of the function we are in- to check return type match the signature
        this->lastScopeNo.push(-1);  // This will keep the last scope number
        MEM("SymbolTable Constructor");
    }

    ~SymbolTable();

    int enterScope(); // This will create a new scope and return the scope number
    int exitScope();  // Will return the ScopeNo that has been exited.

    // Early Scope Entry - This will be used to enter the scope before the compound statement

    int earlyEntry(); // This will make sure One-such call get's ignored
    int earlyExit();  // This will make sure One-such call get's ignored

    // Concept of ScopeName name will be needed for function signature checking
    void setScopeName(const std::string &scopeName);
    std::string getScopeName(); // Will be used to find name of function we are in- to check retrun type match the signature

    int getGlobaScopeNo();

    // There are time when we need to have early scopeEntry - This will make sure One-such call get's ignored
    // void ignoreNextEntry();

    int insertRecord(const std::string &key, GenericSymbol *symbol);
    int insert(SYMBOL_TYPE symbolType, const std::string &key, GenericSymbol *symbol);

    int lookupRecord(const std::string &key, GenericSymbol *&sym);
    int lookup(const std::string &key, GenericSymbol *&sym);

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

class Variable : public GenericSymbol
{
public:
    TypeExpression type;

    StorageClass storageClass;

    // Think about Initialized values ? [ToThink 🧠]
    int offset;

    long compileTimeConstant; // This will be used for constant variables

    CON_DES(Variable)
};

class EnumConstant : public GenericSymbol
{
public:
    int value; // This will be loaded directly [a compile time constant]

    CON_DES(EnumConstant)
};

class Function : public GenericSymbol
{
public:
    TypeExpression type; // This will also hold the parameter(top) + (all below)returnType
    bool isDefined;      // To deal with forward declaration

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

class UserDType : public GenericSymbol
{
public:
    RecordType recordType; // This will be used for struct, union, enum
    bool isComplete;       // This will be used for struct, union, enum
    // Members of the record
    std::map<std::string, TypeExpression> members; // Enum won't use this

    std::map<std::string, int> membersOffset; // This will be used for struct, union

    int totalSize; // This will be used for struct, union

    CON_DES(UserDType)
};

class TypeDefs : public GenericSymbol
{
public:
    TypeExpression type; // This will be used for typedef

    CON_DES(TypeDefs)
};

//=====================[ Symbol Utilities ]=========================================================================================

bool isVariable(const GenericSymbol &sym);
bool isEnumConstant(const GenericSymbol &sym);
bool isFunction(const GenericSymbol &sym);
bool isUserDType(const GenericSymbol &sym);
bool isTypeDefs(const GenericSymbol &sym);

std::string newRecordName(); // For Un-Named Struct/Union/Enum

std::string const RECORD_PREFIX = "RECORD_";   // Prefix for Record Names
std::string const TYPEDEF_PREFIX = "TYPEDEF_"; // Prefix for TypeDef Names

int width(const UserDType &dtype); // This will return the width of the user defined data type

/*


                            THREE ADDRESS CODE


*/

//=====================[ Three Address Code ]=========================================================================================

//==================[ Custom TAC Arguments ]=========================================================================================
extern std::string NO_ARG;
extern std::string RIGHT_STAR;
extern std::string LEFT_STAR;
extern std::string FUNCTION_ENTRY;
extern std::string FUNCTION_EXIT;
// extern std::string BLANK;
extern std::string OFFSET_LOAD;
extern std::string CAST;
extern std::string AMPERSEND;
extern std::string RO_DATA;
extern std::string STACK_DATA;
extern std::string DATA;
extern std::string BSS;
extern std::string PARAM;
extern std::string CALL; // leader for function call
extern std::string ASSIGN_OP;

// leader for Control Flow
extern std::string IF_FALSE;
extern std::string IF_TRUE;
extern std::string GOTO_LABEL;
extern std::string GOTO_EQUAL;

extern std::string TO_BACKPATCH;
extern std::string RETURN_FUNCTION;
extern std::string ALLOCATE;
extern std::string GLOBAL_VAR; // This is used to identify the global variable
// extern std::string ADDRESS_VAR; // This is used to identify the address variable

class TAC_Quadruple
{
public:
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;

    CON_DES(TAC_Quadruple)

    TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result);

    std::string toString();
};

int mergeList(std::vector<int> &list1, const std::vector<int> &addition); // This will merge the two lists
int mergeList(std::vector<int> &target, int addition);

std::string newTemp(); // Generates a new temporary variable [compiler generated]

class dataSegment
{
public:
    std::string name;
    std::string type;  // can be .word, .byte
    std::string value; // value of the data
    bool inAddressSpace; // This will be used to check if the data is in address space or not
};

extern std::string dataByte;
extern std::string dataHalfByte;
extern std::string dataWord;
extern std::string dataDouble;
extern std::string dataString;
extern std::string dataFloat;
extern std::string dataZero; // Used for data-space allocation

class TAC
{
public:
    std::vector<TAC_Quadruple> code;

    std::map<std::string, dataSegment> dataSection;

    const int w = 10;
    const int wcode = 30;

    CON_DES(TAC)

    // void addTAC(std::string op, std::string arg1, std::string arg2, std::string result);
    int addTAC(ASTNode *addedAt, std::string result, std::string op, std::string arg1, std::string arg2); // More readable
    int addTAC(TAC_Quadruple q);

    void printTAC(std::ofstream &file);
    void printTAC();                               // prints to stdout
    void printTAC(std::vector<std::string> &list); // prints to stdout
    void printTAC(std::ostringstream &oss);        // prints to string stream

    std::string newLabel();
    int nextIndex();
    int getLastInserted(); // This will return the last inserted index

    int backpatch(ASTNode *currNode, const std::vector<int> &list, std::string lable);
    int backpatch(ASTNode *currNode, const std::vector<int> &list, int labelIndex); // This will be used to backpatch the list with the label index

    // Overload =operator
    TAC &operator=(const TAC &other)
    {
        this->code = other.code;
        this->dataSection = other.dataSection;
        return *this;
    }

};

/*


                            TYPE CHECKING 🅰️ + TYPE CASTING 🆎


*/

//=====================[ TypeChecking Utilities 🅰️ ]=========================================================================================
bool isVoid(const TypeExpression &typeExpr);                // This will check if the type expression is void or not
bool isValidTypeExpression(const TypeExpression &typeExpr); // This will check if the type expression is valid or not

bool isIntegral(const TypeExpression &typeExpr);
bool isConstant(const TypeExpression &typeExpr);
bool isNumeric(const TypeExpression &typeExpr);
bool isFloatingPoint(const TypeExpression &typeExpr);
std::string isPrimitive(const TypeExpression &typeExpr);
// Return values will be Primitive Types
bool isA_InbuiltType(std::string baseType);                            // Check if base type is primitive
bool isA_IntegralType(std::string baseType);                           // Check if base type is integral
bool isA_FloatingType(std::string baseType);                           // Check if base type is floating
std::string combineType(std::vector<std::string> typeSpecifierVector); // Combine the types
// Return value
extern std::string INVALID_COMBINATION; // This will be used for invalid combination of types

int isFunctionAbstract(const TypeExpression &typeExpr);                                        // This will check if the function is abstract or not
int ProcessConstants(std::string constant, TypeExpression &typeExpr, std::string &finalValue); // This will process the constants

int elementWidth(const TypeExpression &typeExpr); // This will return the width of the element or say below level

//======================[ TypeCasting Utilities 🆎 ]=========================================================================================

std::string maxWidth(std::string primTyp1, std::string primType2);

/*


                            HANDLER FUNCTIONS 🥌



*/

//=====================[ toString Utilities ]=========================================================================================
std::string toString(int value);
std::string toString(bool flag);
std::string toString(std::vector<std::string> valueVector);
std::string toString(std::vector<int> valueVector);
std::string toString(StorageClass storageClass);
std::string toString(TypeQualifier typeQualifier);
std::string toString(std::vector<TypeQualifier> typeQualifiers);
std::string toString(std::map<std::string, TypeExpression> members);
std::string toString(std::vector<PointerInfo *> ptrInfo);
std::string toString(std::vector<TypeExpression> &paramVector);
std::string toString(SPACE space);
std::string toString(VALUE_TYPE valueType);
std::string toString(RecordType recordType);

//====================[ Helper Functions ]=========================================================================================
std::string getProduction(ASTNode *node);
int ProcessDecSpecifiers(std::vector<std::string> &valueVector, TypeExpression &type, StorageClass &storageClass);

//====================[ Globally Accessible Variables ]=========================================================================================
extern SymbolTable SYM_TABLE; // Global Symbol Table
extern TAC IR_CODE;           // Global TAC Code Base

//====================[ Annotated Parse Tree ]=========================================================================================

extern int ANNOTATE; // 0 - OFF | 1 - ON [extern declared in header.h]

#define A_PTree if (ANNOTATE)

//=====================[ Handler Error Handling ]=========================================================================================

extern std::vector<std::string> compilerLOG;
// extern std::vector<std::string> semanticWarning;
#define compilerError(x)                             \
    compilerLOG.push_back(LOC + " 💥 " + x + " 💥"); \
    aptLOG(x);                                       \
    BUG_H; // This will be used to log the errors

extern std::ofstream *handlerLog; // This will be used to log the errors

#define aptHERE   \
    if (ANNOTATE) \
    node->addAttribute("👌 " + std::to_string(__LINE__) + ":" + __FILE__ + " ")

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define TODO(x) _Pragma(TOSTRING(message("TODO: " x)))

#define FEATURE_OFF(x) _Pragma(TOSTRING(message("FEATURE OFF: " x)))

#define semanticWarning(x)                                           \
    semanticLOG.push_back("SEMANTIC Warning ❗️: " + std::string(x)); \
    aptLOG("❗️ " + std::string(x));

#define HERE std::cerr << "[" << __LINE__ << " in " << __FILE__ << "] " << std::endl

#define semanticError(x)                                           \
    semanticLOG.push_back("SEMANTIC ERROR ‼️ : " + std::string(x)); \
    aptLOG("‼️ " + std::string(x));

extern std::string semanticMessage;

#define REACHING \
    std::cout << "Reaching " << __LINE__ << " in " << __FILE__ << std::endl;

#define aptLOG(x) \
    if (ANNOTATE) \
    node->addAttribute(x)

#define ENTRY_H   \
    if (ANNOTATE) \
        node->addAttribute("🤞 Entry");

#define FAIL_H    \
    if (ANNOTATE) \
        node->addAttribute("🆎 EXIT ✋");

#define EXIT_H    \
    if (ANNOTATE) \
        node->addAttribute("Exit ✌️");

#define LOC std::to_string(__LINE__) + " :" + __FILE__

#define BUG_H do { \
    if (ANNOTATE) { \
        node->addAttribute("😱 COMPILER BUG Exit [" + std::to_string(__LINE__) + ":" + std::string(__FILE__) + "] ✋"); \
    } \
} while(0)

#define RECOVER_H \
    if (ANNOTATE) \
    node->addAttribute("🤕 RECOVERY from Semantic Error 🤘")

#define RECOVER_THE_ERROR(x) \
    if ((x) == FAIL)         \
    {                        \
        RECOVER_H;           \
    }                        \
    else if ((x) == BUG)     \
    {                        \
        BUG_H;               \
        return BUG;          \
    }

#define PASS_THE_ERROR(x) \
    if ((x) == FAIL)      \
    {                     \
        FAIL_H;           \
        return FAIL;      \
    }                     \
    else if ((x) == BUG)  \
    {                     \
        BUG_H;            \
        return BUG;       \
    }

extern const int PASS;
// const int OKAY;
extern const int FAIL;

// #define ENTRY_MSG

#define HERE std::cerr << "[" << __LINE__ << " in " << __FILE__ << "] " << std::endl

#define H_HERE *handlerLog << "[" << __FILE__ << " : " << __LINE__ << "] ";
#define CERR std::cerr << "[ 🐛 " << __FILE__ << " : " << __LINE__ << "] "

#define REPORT std::cerr << "[" << __FILE__ << " : " << __LINE__ << "] "

#define LINE1 /**/

//---------------------- Space 🚀Change 🔖IR Code for varName2 [🤫 General Space Before USAGE]
#define USAGE_SPACE_CHANGE(value, type, space, node)                                              \
    if ((space) == SPACE::ADDRESS_SPACE)                                                          \
    {                                                                                             \
        if (getSpace(type) == SPACE::VALUE_SPACE)                                                 \
        {                                                                                         \
            std::string tempName = newTemp();                                                     \
            int size = width(type);                                                               \
            IR_CODE.addTAC((node), tempName, ALLOCATE, std::to_string(size), NO_ARG);             \
            IR_CODE.addTAC((node), tempName, RIGHT_STAR, (value), std::to_string(size));          \
            value = tempName;                                                                     \
            (node)->attributes.push_back("🌋 Space Change from ADDRESS to VALUE 💥 ");             \
        }                                                                                         \
    }                                                                                             \
    else if ((space) == SPACE::VALUE_SPACE)                                                       \
    {                                                                                             \
        if (getSpace(type) == SPACE::ADDRESS_SPACE)                                               \
        {                                                                                         \
            std::string offset = newTemp();                                                       \
            int size = width(type);                                                               \
            IR_CODE.addTAC((node), offset, ALLOCATE, std::to_string(size), NO_ARG);               \
            IR_CODE.addTAC((node), offset, OFFSET_LOAD, (value), NO_ARG);                         \
            value = offset;                                                                       \
            (node)->attributes.push_back("🌋 Space Change from VALUE to ADDRESS 💥 ");             \
        }                                                                                         \
    }                                                                                             \
    else                                                                                          \
    {                                                                                             \
        (node)->attributes.push_back("🌋 Something Wrong in Space 💥 Change Code [" + LOC + "]"); \
        BUG_H;                                                                                    \
        return BUG;                                                                               \
    }

#define TO_GIVEN_SPACE_CHANGE(value, oldSpace, newSpace, type, node)                              \
    if ((oldSpace) == SPACE::ADDRESS_SPACE)                                                       \
    {                                                                                             \
        if ((newSpace) == SPACE::VALUE_SPACE)                                                     \
        {                                                                                         \
            std::string tempName = newTemp();                                                     \
            int size = width(type);                                                               \
            IR_CODE.addTAC((node), tempName, ALLOCATE, std::to_string(size), NO_ARG);             \
            IR_CODE.addTAC((node), tempName, RIGHT_STAR, (value), std::to_string(size));          \
            value = tempName;                                                                     \
            (node)->attributes.push_back("   Space Change from ADDRESS to VALUE    ");            \
        }                                                                                         \
    }                                                                                             \
    else if ((oldSpace) == SPACE::VALUE_SPACE)                                                    \
    {                                                                                             \
        if ((newSpace) == SPACE::ADDRESS_SPACE && getSpace(type) == SPACE::ADDRESS_SPACE)         \
        {                                                                                         \
            std::string offset = newTemp();                                                       \
            int size = width(type);                                                               \
            IR_CODE.addTAC((node), offset, ALLOCATE, std::to_string(size), NO_ARG);               \
            IR_CODE.addTAC((node), offset, OFFSET_LOAD, (value), NO_ARG);                         \
            value = offset;                                                                       \
            (node)->attributes.push_back(" .  Space Change from VALUE to ADDRESS   ");            \
        }                                                                                         \
    }                                                                                             \
    else                                                                                          \
    {                                                                                             \
        (node)->attributes.push_back("🌋 Something Wrong in Space 💥 Change Code [" + LOC + "]"); \
        BUG_H;                                                                                    \
        return BUG;                                                                               \
    }

extern const std::string PASS_ERROR;

void openHandlerLog(const std::string &filename);
void closeHandlerLog();

extern std::vector<std::string> semanticLOG; // [declared in handler.cpp]

extern std::string IN_SYNTAX_PHASE;

extern std::string NOT_CONSTANT;

std::string getCurrentTime();

//=====================[ Main Semantic Pass Handler ]=========================================================================================

void semanticPass(ASTNode *node);
// SYM_TABLE - Will be Globaly available
// IR_CODE - Will be Globaly available (TAC)

//=====================[ Starting Handlers ]=========================================================================================

int translation_unit_H(ASTNode *node);
int external_declaration_H(ASTNode *node);

//=====================[ Function Definition Handlers ]=========================================================================================

int function_definition_H(ASTNode *node);

//=====================[ Labels ]=========================================================================================

extern std::map<std::string, int> labelMap;               // This will be used to keep track of the labels
extern std::map<std::string, std::vector<int>> labelList; // This will be used to keep track of the labels

//=====================[ Statements Handlers ]=========================================================================================
extern std::string DEFAULT_CASE;
extern int caseAllowed;
extern int breakAllowed;    // This will be used to check if break is allowed or not
extern int continueAllowed; // This will be used to check if continue is allowed or not

int statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap);
int statement_list_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap);

int labeled_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap);   // 1
int compound_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap);  // 2
int expression_statement_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);       // 3
int selection_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap); // 4
int iteration_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap); // 5
int jump_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap);      // 6
// int declaration(ASTNode* node); // 7 [In Declaration Handler Section]

//=====================[ Declaration Handlers ]=========================================================================================

// ----- Main Declaration Handler
int declaration_H(ASTNode *node);
int declaration_list_H(ASTNode *node);

//----- Init Declarator Handler

int init_declarator_list_H(ASTNode *node, TypeExpression inh_type, StorageClass inh_storageClass);
int init_declarator_H(ASTNode *node, TypeExpression inh_type, StorageClass inh_storageClass);

// ----- TypeSpecifier + TypeQualifier + StorageClass -----
int declaration_specifiers_H(ASTNode *node, std::vector<std::string> &valueVector);
int storage_class_specifier_H(ASTNode *node, std::string &value);
int type_specifier_H(ASTNode *node, std::string &value);
int type_qualifier_H(ASTNode *node, std::string &value);
int specifier_qualifier_list_H(ASTNode *node, std::vector<std::string> &valueVector);
int type_qualifier_list_H(ASTNode *node, std::vector<TypeQualifier> &typeQualifiers);

//----- Struct/Union -----
int struct_or_union_specifier_H(ASTNode *node, std::string &value);
// struct_or_union_H not needed
int struct_declaration_list_H(ASTNode *node, std::map<std::string, TypeExpression> &members);
int struct_declaration_H(ASTNode *node, std::map<std::string, TypeExpression> &members);
int struct_declarator_list_H(ASTNode *node, TypeExpression inh_type, std::map<std::string, TypeExpression> &members);
int struct_declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type);
// -- Enum -----
int enum_specifier_H(ASTNode *node, std::string &value);
int enumerator_list_H(ASTNode *node, std::string recordID, int &lastInitValue);
int enumerator_H(ASTNode *node, std::string &varName, int &explicitInitValue, bool &isExplicityInit);

//----- Declarator -----
int declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type);
int direct_declarator_H(ASTNode *node, TypeExpression inh_type, std::string &varName, TypeExpression &type);

//----- Pointer -----
int pointer_H(ASTNode *node, std::vector<PointerInfo *> inh_ptrInfo, std::vector<PointerInfo *> &ptrInfo);

//----- Parameters -----
int parameter_type_list_H(ASTNode *node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list);
int parameter_list_H(ASTNode *node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list);
int parameter_declaration_H(ASTNode *node, TypeExpression &type, std::string &varName);

//----- Identifier List -----
int identifier_list_H(ASTNode *node, std::vector<std::string> &idList);

//----- Type Name -----
int type_name_H(ASTNode *node, TypeExpression &type);

//----- Abstract Declarator -----
int abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type);
int direct_abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type);
extern std::string NO_ARG_NAME;

//----- Initializer -----
int initializer_H(ASTNode *node, TypeExpression inh_type, std::string inh_varName, SPACE inh_valueSpace, VALUE_TYPE inh_valueType);
int initializer_list_H(ASTNode *node, TypeExpression inh_type, std::string inh_varName, int &totalInitializers);

//======================[ Expression Handlers ]=========================================================================================

int expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int primary_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int argument_expression_list_H(ASTNode *node, std::vector<TypeExpression> &argType, std::vector<std::string> &argName);
int postfix_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int unary_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int cast_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int multiplicative_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int additive_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int shift_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int relational_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int equality_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int and_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int exclusive_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int inclusive_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int logical_and_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int logical_or_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int conditional_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);
int assignment_expression_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace);

int constant_expression_H(ASTNode *node, std::string &value);

/*


                                    🧬 Code Generations 🧬


*/

//=====================[ Code Generations ]=========================================================================================

bool isALabel(const std::string &varName); // This will check if the variable is a label or not
bool isAValueSymbol(const std::string &varName); // This will check if the variable is a symbol or not
// bool isAddressSymbol(const std::string &varName); // This will check if the variable is a address symbol or not
// using RISCV_CODE = std::vector<std::string>;

std::string indentOP(std::string op);

class RISCV_CODE{
    std::vector<std::string> code;
    std::map<std::string, dataSegment> data;

public:
    void addDataSection(const std::map<std::string, dataSegment> &dataSection);

    void addCode(std::string code);
    void addCode(std::string code, std::string info);

    void printCode(std::ostringstream &oss);

    void addLabel(std::string label);

    void addComment(std::string comment);

    void addCopyInst(std::string variable, int size, int srcImm, std::string src_wrtReg, int destImm, std::string dest_wrtReg);

    void addLoadInst(const std::string &varName, int regNo);
    void addStoreInst(const std::string &varName, int regNo);
    };

int codeGen();


using LivelinessDS = std::map<std::string, std::pair<bool, std::set<int>>>; // This will be used to keep track of the liveliness of the variables

class NEW_TAC_Quadruple : public TAC_Quadruple
{
    // This will a improved version of TAC_Quadruple
public:
    // Storing Status of Three Variables in that Instruction (<= 3)
    LivelinessDS VarInfo;

    int lineNo; // [TODO - Add Support for this]

    NEW_TAC_Quadruple() = default;

    NEW_TAC_Quadruple(TAC_Quadruple oldTAC){
        this->op = oldTAC.op;
        this->arg1 = oldTAC.arg1;
        this->arg2 = oldTAC.arg2;
        this->result = oldTAC.result;
    }

    int addVariable(const std::string &varName, bool islive, const std::set<int> &nextUsage);

    // Check if the variable is alive or NOT (via-reference)
    bool isAlive(const std::string &varName);

    int addLivelinessInfo(const LivelinessDS &info);

    // Find the next usage of a variable
    int nextUse(const std::string &varName, std::set<int> &usage);

    int howManyNextUsage(const std::string &varName, int &total);

    std::string toBaseString();

    std::string toString();
};


class NEW_TAC
{
public:
    std::map<int, NEW_TAC_Quadruple> code;

    int addOLD_TAC(int lineNo, TAC_Quadruple oldIrCode);
    int addVarInfo(int lineNo, const std::string  &varName, bool isAlive, const std::set<int> &nextUsage);

    int addTAC(int lineNo, NEW_TAC_Quadruple q);

    void printTAC(std::ostringstream &oss);
};

class BasicBlock
{
public:
    NEW_TAC irCode;

    LivelinessDS livelinessInfo; // This will be used to keep track of the liveliness of the variables

    int generateRISCVCode();            // This will generate the RISC-V code & store in it's element -> risvCode

    std::string label; // Label for the basic block

    void printCode(std::ostringstream &oss);

    void logLivelinessInfo();
};

class CFG
{
public:
    std::map<std::string, BasicBlock> blocks; // Direclty map leader's Index to Block

    std::map<std::string, dataSegment> dataSection;

    void printCode(std::ostringstream &oss);

    std::vector<int> leaders;
    std::map<int, std::string> leaderToBlockMap;

    int nextBlockIndex = 0;

    std::string newBlock();

    std::map<std::string, std::vector<std::string>> edges; // This will be used to keep track of the leaders

    CFG() = default;

    // This will help find to which block any index belongs
    int whichBlock(int index);


    bool isALeader(int index);
    int addLeader(int index);                        // will generate a new Name for block & set things
    int addLeader(int index, std::string blockName); // This will set that Name
    void sortLeaders();

    // This will check who is leader and send the leader's blocksLable
    std::string blockName(int index);

    int add_NEWTAC(int irLineNo, NEW_TAC_Quadruple code);

    int addEdge(const std::string &from, const std::string &to);
    int addEdge(int from, int to);

    int generateDOTFile(const std::string &filename); // This will generate a dot file for the CFG

    void generateRISCVCodes();

    //----------- Utilities for Liveliness Checking
    int getAllLivelinessInfo(int atLine, LivelinessDS &livelinessInfo);

    int attachLiveInfoToLine(int atLine);

    int setAlive(int atLine, const std::string &key); // Set the variable as alive
    int setAllAlive(int atLine);                    // Set all the variables as alive
    int setDead(int atLine, const std::string &key);  // Set the variable as dead
    int setAllDead(int atLine);                     // Set all the variables as dead

    bool isAlive(int atLine, const std::string &key); // Check if the variable is alive or not

    int addUsage(int atLine, const std::string &key, int usageLine);    // Add the usage of the variable in the register
    int removeUsage(int atLine, const std::string &key, int usageLine); // Clear the usage of the variable in the register
    int clearAllUsage(int atLine, const std::string &key);           // Clear all the usage of the variable in the register


    int removeLifeInfo(int atLine, const std::string &key); // Remove the liveliness info of the variable

    // For Us to use Simple Functions

    int assignmentAt(int atLine, const std::string &varName); // This will be used to assign the value to the variable
    int usageAt(int atLine, const std::string &varName); // This will be used to use the variable as an operand

    int resetLiveliness(int atLine);


};

class SymInfo
{
public:
    // Information of each symbol
    // For Offset Calculations
    int size;
    int offset; // relative to function-block or global-space
    bool isGlobal;
    bool inAddressSpace; // This will be used to check if the variable is in address space or not

    std::string whichFunction;

    // Will be used by getReg
    bool inMemory;
    std::set<int> inRegNo;
};

// Some Constant Needed
int const activation_start_offset = 16; // 4 words
/* Usage of last 4 Words
- (unused)
- Where to Store Return Value Address
- Old Frame Pointer
- Return Address
*/

extern int MIN_REGNO;
extern int MAX_REGNO;

class SymTable
{
    // This will be scope-disabled Symbol Table

public:
    std::map<std::string, SymInfo> symTable; // This will be used to keep track of the symbols

    int bss_offset;  // This will be used to keep track of the bss offset
    int ro_offset;   // This will be used to keep track of the ro offset
    int data_offset; // This will be used to keep track of the data offset

    int stack_offset; // For Local Offset

    bool inFunction;
    std::string functionName = "GLOBAL"; // This will be used to keep track of the function name

    // We will also Insert functions as a variable and it's size = activation record size;

    SymTable(){
        bss_offset = 0;
        ro_offset = 0;
        data_offset = 0;
        stack_offset = 0;

        inFunction = false;
        functionName = "GLOBAL"; // This will be used to keep track of the function name

        resetRegTable();
    }

    int enterFunction(const std::string &funcName);
    int exitFunction();


    int insert(const std::string &key, SymInfo &info);
    int insert(const std::string &key, int size, bool space); // The Offset & isGlobal Will be autoSet
    int insertGlobal(const std::string &key, int size, bool space); // This will be used to insert the global variable
    
    int lookup(const std::string &key, SymInfo &info);

    int remove(const std::string &key);

    int getSize(const std::string &key);
    int getOffset(const std::string &key);
    bool isGlobal(const std::string &key);
    bool isInAddressSpace(const std::string &key);

    void printTable(std::ofstream &file);

    //---------- Utility Function for getReg
    bool isInMemory(const std::string &key); // Check if the variable(updated) is in memory or not

    int setInMemory(const std::string &key);    // Set the variable as in memory
    int setNotInMemory(const std::string &key); // Set the variable as not in memory

    int varStoredInWhichReg(const std::string &key); // Check if the variable is stored in register or not
    int varStoreInHowManyReg(const std::string &key); // Check how many registers the variable is stored in

    int ex_varStoredInWhichReg(const std::string &key); // Check if  variable EXCLUSIVLY is stored in register or not

    int addVarInReg(const std::string &key, int regNo);    // Set the variable as in register
    int removeVarFromReg(const std::string &key, int regNo); // Clear the variable from register
    int removeVarFromAllReg(const std::string &key);          // Clear all the registers for the variable

    int variableRest(const std::string &key); // Reset the variable's info

    // RegDescription Table Structures
    std::map<int, std::set<std::string>> regMap; // Map of register to variable

    std::set<int> SetOfFreeReg; // Set of free registers

    void resetRegTable(); // Initialize the register table

    // Utility Functions for Register Table
    // Check if a particular register is free or NOT
    bool isFree(int regNo);

    // Check a particular variable is in a particular register
    bool isVarInReg(int regNo, const std::string &varName);

    // Get all the variable whose value is in the arg_given register
    int whatIsInReg(int regNo, std::set<std::string> &varName);

    int howManyVarInReg(int regNo); // Get the number of variables in the register

    // Add a variable to the register
    // int addVarToReg(int regNo, const std::string &varName); [Already Present for get_regUtilites]

    // Remove a variable from the register
    // int removeVarFromReg(int regNo, const std::string &varName); [Already Present for get_regUtilites]

    int freeGivenReg(int regNo); // Free the register

    int freeAllReg(); // Free all the registers

    // Get a free register (via-Reference) [Gives Smallest Free Register or -1 if none is free]
    int getFreeReg();

    // void resetRegTable(); // Reset the register info

    // int findRegToEvict(); // Find a register to evict & return the register number

    void printRegTable(std::ofstream &file); // Print the register info
};

int addSymbolsToSymTable();

int makeBasicBlocks();

int riscvCodeGen();

int livelinessPass();

int getReg(NEW_TAC_Quadruple &code, std::map<std::string, int> &retMap);

int getManyReg(std::set<std::string> varName, LivelinessDS livelinessInfo, std::map<std::string, int> &retMap);

std::string store_load_Type(int size);

int generateSimpleExpCode(NEW_TAC_Quadruple code);

//====================[ Externed Global CodeGen Variables ]=========================================================================================

extern std::string NO_BLOCK;

extern CFG CFG_CODE;
extern SymTable SYM_RECORD;

extern RISCV_CODE FINAL_CODE;

//======================[ Code Optimization ]=========================================================================================

int constantFolding();

int machineIndependentOptimization();

//======================[ Code Generation Utilies ]=========================================================================================

#endif // !HEADER_H