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
#define ADDRESS_SIZE 8 // 64 bit address

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
extern std::string CAST;
extern std::string LABEL;
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
extern std::string MEM_COPY;
extern std::string ALLOCATE;

class TAC_Quadruple
{
public:
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
    // ASTNode *addedAt;

    CON_DES(TAC_Quadruple)

    TAC_Quadruple(std::string op, std::string arg1, std::string arg2, std::string result);

    std::string toString();
};

int mergeList(std::vector<int> &list1, const std::vector<int> &addition); // This will merge the two lists
int mergeList(std::vector<int> &target, int addition);

std::string newTemp(); // Generates a new temporary variable [compiler generated]

class TAC
{
public:
    std::vector<TAC_Quadruple> code;
    std::vector<std::string> roData;
    // std::vector<std::string> stackData;
    std::vector<std::string> bssData;
    std::vector<std::string> data;
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
extern TAC CODE_BASE;         // Global TAC Code Base

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

#define semanticWarning(x)                                           \
    semanticLOG.push_back("SEMANTIC Warning ❗️: " + std::string(x)); \
    aptLOG("❗️ " + std::string(x));

#define HERE std::cerr << "[" << __LINE__ << " in " << __FILE__ << "] " << std::endl

#define semanticError(x)                                           \
    semanticLOG.push_back("SEMANTIC ERROR ‼️ : " + std::string(x)); \
    aptLOG("‼️ " + std::string(x));

extern std::string semanticMessage;

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

#define BUG_H \                                                                                        
    if (ANNOTATE) node->addAttribute("😱 COMPILER BUG Exit [" + std::to_string(__LINE__) + ":" + __FILE__ + "] ✋")

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
#define CERR std::cerr << "[ 🐛 " << __FILE__ << " : " << __LINE__ << "]"

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
            CODE_BASE.addTAC((node), tempName, ALLOCATE, std::to_string(size), NO_ARG);           \
            CODE_BASE.addTAC((node), tempName, RIGHT_STAR, (value), NO_ARG);                      \
            value = tempName;                                                                     \
        }                                                                                         \
    }                                                                                             \
    else if ((space) != SPACE::VALUE_SPACE)                                                       \
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
// CODE_BASE - Will be Globaly available (TAC)

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
int initializer_H(ASTNode *node, TypeExpression &type, std::string &varName, int &size);
int initializer_list_H(ASTNode *node, TypeExpression &type, std::string &varName, int &size);

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

using RISCV_CODE = std::vector<std::string>;

int codeGen(const TAC &irCode, RISCV_CODE &riscvCode);

class BasicBlock
{
public:
    std::vector<TAC_Quadruple> irCode;  // Not using NOW
    std::vector<std::string> riscvCode; // Will be generated

    std::string label;                 // Label for the basic block
    // std::vector<std::string> inLinks;  // can be 1 or more
    // std::vector<std::string> outLinks; // <= 2

    // Two Special ENTRY and EXIT blocks
};

class CFG
{
public:
    std::vector<BasicBlock> blocks;
    std::map<std::string, int> labelMap; // Map of labels to block index
    std::vector<int> leaders;

    int nextBlockIndex = 0;

    std::string newBlock();

    std::vector<std::pair<std::string, std::string>> edges; // Edges between blocks

    CFG() = default;

    // This will help find to which block any index belongs
    int whichBlock(int index);

    int addEdge(const std::string &from, const std::string &to);

    int generateDOTFile(const std::string &filename); // This will generate a dot file for the CFG

    void generateRISCVCodes(RISCV_CODE &riscvCode);
};

int makeBasicBlocks(const TAC &irCode, CFG &cfg);

#endif // !HEADER_H