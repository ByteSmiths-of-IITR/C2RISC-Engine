#ifndef HEADER_H
#define HEADER_H

#include "utility.h"

//====================[ GCC Header Files ]=========================================================================================
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <stack>
#include <map>
#include <utility>
#include <map>

//====================[ Globaly Accessible SymbolTable & TAC-CodeBase ]=========================================================================================

//====================[ Annotated PTree Utilities ]=========================================================================================

extern int ANNOTATE; // 0 - OFF | 1 - ON [value set by header.cpp]

//================== [Architecture Variables]=========================================================================================
#define WORD_SIZE 4 // int, float
#define WORD_SIZEx2 8 // double, long
#define WORD_SIZEx4 16 // long double or long long
#define BYTE_SIZEx2 2 // short
#define BYTE_SIZE 1 // 8 bits, char
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
        LevelInfo()
        {
            MEM("LevelInfo Constructor");
        }
        virtual ~LevelInfo()
        { // Virtual Destructor
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


            bool isAbstract;
            std::vector<std::string> paramsName;
            std::vector<TypeExpression> paramsType; // This will have the type of the parameters

            CON_DES(ParameterInfo)

        };
        
        //=====================[ BaseInfo ]=========================================================================================
            extern std::string TYPE_STRUCT;
            extern std::string TYPE_UNION;
            extern std::string TYPE_ENUM;
            extern std::string ENUM_CONSTANT;

            extern std::string TYPE_VOID;

            extern std::string TYPE_FLOAT;
            extern std::string TYPE_DOUBLE;
            extern std::string TYPE_LONG_DOUBLE;

            extern std::string TYPE_CHAR;
            extern std::string TYPE_SHORT;
            extern std::string TYPE_INT;
            extern std::string TYPE_LONG;
            extern std::string TYPE_LONG_LONG;

            extern std::string TYPE_UNSIGNED; // will be used like - UNSIGNED + PRIMITIVE
            extern std::string TYPE_SIGNED; // this will be used - PRIMITIVE [Default Signed]

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



                                    SYMBOL TABLE



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

// Return values of insert()
extern int const INSERT_SUCCESS;              // Inserted Successfully
extern int const INSERT_SUCCESS_WITH_WARNING; // Inserted but had a same key in ancestor scope
extern int const INSERT_FAILURE;              // Already present in the current scope

// Return values of lookup()
extern int const LOOKUP_SUCCESS; // Found
extern int const LOOKUP_FAILURE; // Not Found

class SymbolTable
{
public:
    // Faster lookup
    std::map<std::string, SymbolNode *> symTable;

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

        class Variable : public GenericSymbol {
        public:
            TypeExpression type; 
            
            StorageClass storageClass; 

            // Think about Initialized values ? [ToThink 🧠]

            long compileTimeConstant; // This will be used for constant variables

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
            std::map<std::string, TypeExpression> members; // Enum won't use this

            CON_DES(UserDType)
        };

        class TypeDefs : public GenericSymbol {
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

std::string const RECORD_PREFIX = "RECORD_"; // Prefix for Record Names

int width(const UserDType &dtype); // This will return the width of the user defined data type


/*


                            THREE ADDRESS CODE


*/

//=====================[ Three Address Code ]=========================================================================================

    //==================[ Custom TAC Arguments ]=========================================================================================
        extern const std::string NO_ARG;
        extern const std::string RIGHT_STAR;
        extern const std::string LEFT_STAR;
        extern const std::string FUNCTION_LABEL;
        extern const std::string BLANK;



        class TAC_Quadruple
        {
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


                            TYPE CHECKING 🅰️ + TYPE CASTING 🆎


*/


//=====================[ TypeChecking Utilities 🅰️ ]=========================================================================================

bool isIntegral(const TypeExpression &typeExpr);
bool isConstant(const TypeExpression &typeExpr);
std::string isPrimitive(const TypeExpression &typeExpr);
// Return values will be Primitive Types
bool isA_InbuiltType(std::string baseType); // Check if base type is primitive
bool isA_IntegralType(std::string baseType); // Check if base type is integral
bool isA_FloatingType(std::string baseType); // Check if base type is floating
std::string combineType(std::vector<std::string> typeSpecifierVector); // Combine the types
// Return value
extern std::string INVALID_COMBINATION; // This will be used for invalid combination of types

//======================[ TypeCasting Utilities 🆎 ]=========================================================================================

std::string maxWidth(std::string primTyp1, std::string primType2);

/*


                            HANDLER FUNCTIONS 🥌



*/

//=====================[ toString Utilities ]=========================================================================================
std::string toString(int value);
std::string toString(bool flag);
std::string toString(std::vector<std::string> valueVector);
std::string toString(StorageClass storageClass);
std::string toString(TypeQualifier typeQualifier);
std::string toString(std::vector<TypeQualifier> typeQualifiers);
std::string toString(std::map<std::string, TypeExpression> members);
std::string toString(std::vector<PointerInfo> ptrInfo);
std::string toString(std::vector<TypeExpression> &paramVector);


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

extern std::ofstream* handlerLog; // This will be used to log the errors

#define HERE *handlerLog << "AT line " << __LINE__ << " in " << __FILE__ << std::endl
#define HEREFUNC *handlerLog << "AT line " << __LINE__ << " in " << __FILE__ << " in function: " << lastFuncCalled << std::endl

#define CERR *handlerLog << "[" << __FILE__ << " : " << __LINE__ <<  "] "

// #define LINE1 std::cerr << "At line " << __LINE__ << " in " << __FILE__ << std::endl;
#define LINE1 /**/

void openHandlerLog(const std::string &filename);
void closeHandlerLog();

extern std::string IN_SYNTAX_PHASE;

//=====================[ Main Semantic Pass Handler ]=========================================================================================

void semanticPass(ASTNode *node, std::string filename);
// SYM_TABLE - Will be Globaly available
// CODE_BASE - Will be Globaly available (TAC)

//=====================[ Starting Handlers ]=========================================================================================

void translation_unit_H(ASTNode *node);
void external_declaration_H(ASTNode *node);

//=====================[ Function Definition Handlers ]=========================================================================================

void function_definition_H(ASTNode *node);

//=====================[ Statements Handlers ]=========================================================================================

void statement_H(ASTNode *node);
void compound_statement_H(ASTNode* node, bool earlyScopeEntry);

//=====================[ Declaration Handlers ]=========================================================================================

// ----- Main Declaration Handler
void declaration_H(ASTNode *node);
void declaration_list_H(ASTNode *node);


//----- Init Declarator Handler
void init_declarator_list_H(ASTNode* node, TypeExpression inh_type, StorageClass inh_storageClass);
void init_declarator_H(ASTNode* node, TypeExpression inh_type, StorageClass inh_storageClass);

// ----- TypeSpecifier + TypeQualifier + StorageClass -----
void declaration_specifiers_H(ASTNode *node, std::vector<std::string> &valueVector);
void storage_class_specifier_H(ASTNode* node, std::string &value);
void type_specifier_H(ASTNode* node, std::string &value);
void type_qualifier_H(ASTNode* node, std::string &value);
void specifier_qualifier_list_H(ASTNode* node, std::vector<std::string> &valueVector);
void type_qualifier_list_H(ASTNode* node, std::vector<TypeQualifier> &typeQualifiers);

//----- Struct/Union -----
void struct_or_union_specifier_H(ASTNode* node, std::string &value);
// struct_or_union_H not needed
void struct_declaration_list_H(ASTNode* node, std::map<std::string, TypeExpression> &members);
void struct_declaration_H(ASTNode* node, std::map<std::string, TypeExpression> &members);
void struct_declarator_list_H(ASTNode* node, TypeExpression inh_type, std::map<std::string, TypeExpression> &members);
void struct_declarator_H(ASTNode* node, TypeExpression inh_type, std::string &varName, TypeExpression &type);
// -- Enum -----
void enum_specifier_H(ASTNode* node, std::string &value);
void enumerator_list_H(ASTNode* node, std::string recordID, int &lastInitValue);
void enumerator_H(ASTNode* node, std::string &varName, int &explicitInitValue, bool &isExplicityInit);

//----- Declarator -----
void declarator_H(ASTNode* node, TypeExpression inh_type, std::string &varName, TypeExpression &type);
void direct_declarator_H(ASTNode* node, TypeExpression inh_type, std::string &varName, TypeExpression &type);

//----- Pointer -----
void pointer_H(ASTNode* node, std::vector<PointerInfo> inh_ptrInfo, std::vector<PointerInfo> &ptrInfo);

//----- Parameters -----
void parameter_type_list_H(ASTNode* node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list);
void parameter_list_H(ASTNode* node, std::vector<TypeExpression> &paramVector, std::vector<std::string> &varName_list);
void parameter_declaration_H(ASTNode* node, TypeExpression &type, std::string varName);

//----- Identifier List -----
void identifier_list_H(ASTNode *node, std::vector<std::string> &idList);

//----- Type Name -----
void type_name_H(ASTNode *node, TypeExpression &type);

//----- Abstract Declarator -----
void abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type);
void direct_abstract_declarator_H(ASTNode *node, TypeExpression inh_type, TypeExpression &type);
extern std::string NO_ARG_NAME;


//----- Initializer -----
void initializer_H(ASTNode *node);
void initializer_list_H(ASTNode *node);

//======================[ Expression Handlers ]=========================================================================================

void constant_expression_H(ASTNode *node, std::string &value);
       





#endif // !HEADER_H