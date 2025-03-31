#include "header.h"

//================ [ Memory Monitoring ]=========================================================================================
int MEMORY_MONITORING = 0; // 0 - OFF | 1 - ON [Initialized here]

//===================[ Intialized Externed Variable ]===============================

std::string TYPE_STRUCT = "struct";
std::string TYPE_UNION = "union";
std::string TYPE_ENUM = "enum";
std::string ENUM_CONSTANT = "enum_constant";
std::string TYPE_INT = "int";
std::string TYPE_FLOAT = "float";
std::string TYPE_DOUBLE = "double";
std::string TYPE_LONG_DOUBLE = "long_double";
std::string TYPE_CHAR = "char";
std::string TYPE_SHORT = "short";
std::string TYPE_LONG = "long";
std::string TYPE_VOID = "void";
std::string TYPE_LONG_LONG = "long_long";
std::string TYPE_UNSIGNED = "unsigned"; // will be used like - UNSIGNED + PRIMITIVE
std::string TYPE_SIGNED = "signed";

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


std::string lastFuncCalled = "init"; // Global variable to keep track of the last function called

//=== [Global Variables] ==========================================================================================================
// SymbolTable SYM_TABLE; // Global Symbol Table
// TAC CODE_BASE; // Global TAC Code Base [declared in handler.cpp]