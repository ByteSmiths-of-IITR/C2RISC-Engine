#ifndef UTILITY_H
#define UTILITY_H
//====================[ GCC Header Files ]=========================================================================================
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <stack>
#include <map>
#include <utility>
#include <map>
#include <iomanip>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <map>
#include <utility>
#include <algorithm>
#include <set>
#include <iomanip>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <signal.h>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <cstdint>
#include <queue>

// Forward declaration
class TokenAttribute;
class ASTNode;

extern std::ofstream *handlerLog; // This will be used to log the errors

extern int orderOfEval;
// extern std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> PARSER_TABLE;

#define EMPTY_VAL "!!EMPTY!!"
#define TYPEDEF_FOUND "!!TYPEDEF!!"
extern bool expectingTypeName;

std::string escapeCharacters(const std::string &input);

extern std::set<std::string> typeDefIDs; // Set to store typedefs

// ASTNode class definition
class ASTNode {
public:
    std::string type; // token type
    std::string value; // token value
    std::pair<int,int> position; // line and column number [for error reporting]
    std::vector<ASTNode *> children;

    // Attribute during semantic
    std::vector<std::string> attributes; // used for semantic analysis

    // Function used for TOKENS
    ASTNode(TokenAttribute *tokenAtr);
    ASTNode(std::string type, std::string value, std::pair<int, int> position);
    ASTNode(std::string type, std::string value,int line=-1, int column=-1); //default values for line and column [unset]
    // Function used for TYPES 
    ASTNode(std::string type);
    ASTNode(ASTNode *child);
    ~ASTNode();

    void addChild(ASTNode *child); // used by TYPES
    void addChildren(std::vector<ASTNode *> children);
    void addChild(std::string type);
    // Used by TOKENS
    void addChild(std::string type, std::string value, int line=-1, int column=-1);
    void addChild(std::string type, std::string value, std::pair<int, int> position);
    void addChild(TokenAttribute* tokenAtr);

    void print(int level);

    void addAttribute(std::string attribute);
};

//HelperFunction
std::string getTokenName(int token);
class TokenAttribute {
    public:
        std::string value;
        int tokenType;
        std::pair<int, int> position; // line and column number

        TokenAttribute(int tokenType, std::string value, std::pair<int, int> position);
        TokenAttribute(int tokenType, std::string value, int line, int column);
        ~TokenAttribute();
};

// Function declarations
void printAST(ASTNode *root);
std::string ASTStyle(ASTNode *node);
void writeNode(std::ofstream &out, ASTNode *node, int parentId, int &nodeCount);
void generateDOT(ASTNode *root, const std::string &filename);

void writeNode_A(std::ofstream &out, ASTNode *node, int parentId, int &nodeCount);
void generateDOT_A(ASTNode *root, const std::string &filename);

void printSExpression(ASTNode *root, std::ofstream &outputFile, int indent = 0);
void writeASTToSExpression(ASTNode *root, const std::string &outputFileName);
void printASTRecursive(ASTNode *node, std::ofstream &outFile, const std::string &prefix, bool isLast);
void printASTToFile(ASTNode *root, const std::string &outputFileName);

//Semantic Phase Utilities
extern std::string MARKER;
void insertAfterMarker(const std::string &filename, const std::string &marker, std::ostringstream &newContent);

#endif // UTILITY_H
