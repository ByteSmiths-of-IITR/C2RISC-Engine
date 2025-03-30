#include "header.h"

//================ [ Memory Monitoring ]=========================================================================================
int MEMORY_MONITORING = 0; // 0 - OFF | 1 - ON [Initialized here]

//===================[ Intialized Externed Variable ]===============================

std::string STRUCT = "struct";
std::string UNION = "union";
std::string ENUM = "enum";
std::string ENUM_CONSTANT = "enum_constant";
std::string INT = "int";
std::string FLOAT = "float";
std::string DOUBLE = "double";
std::string CHAR = "char";
std::string SHORT = "short";
std::string LONG = "long";
std::string VOID = "void";
std::string LONG_LONG = "long_long";
std::string UNSIGNED = "unsigned"; // will be used like - UNSIGNED + PRIMITIVE
std::string SIGNED = "signed";

int const POP_SUCCESS = 0;
int const POP_FAILURE = -1; // if 
int const EQUIVALENT = 0;
int const WARNING = -1;
int const LOW_ERROR = -2;
int const HIGH_ERROR = -3;

int const INSERT_SUCCESS = 0;
int const INSERT_SUCCESS_WITH_WARNING = 1;
int const INSERT_FAILURE = -1; // Already present in the current scope

int const LOOKUP_SUCCESS = 0; // Found
int const LOOKUP_FAILURE = -1; // Not Found


std::string lastFuncCalled;

//=== [Global Variables] ==========================================================================================================
SymbolTable SYM_TABLE; // Global Symbol Table
TAC CODE_BASE; // Global TAC Code Base