#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


// ASTNode class definition
class ASTNode {
public:
    std::string type; // token type
    std::string value; // token value
    std::pair<int,int> position; // line and column number [for error reporting]
    std::vector<ASTNode *> children;

    // Function used for TOKENS
    ASTNode(std::string type, std::string value,int line=-1, int column=-1); //default values for line and column [unset]
    ASTNode(std::string type, std::string value, std::pair<int,int> position);
    ASTNode(TokenAttribute* tokenAtr);
    // Function used for TYPES 
    ASTNode(std::string type);
    ~ASTNode();

    void addChild(ASTNode *child); // used by TYPES
    void addChildren(std::vector<ASTNode *> children);
    // Used by TOKENS
    void addChild(std::string type, std::string value, int line=-1, int column=-1);
    void addChild(TokenAttribute* tokenAtr);

    void print(int level);
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
void writeNode(std::ofstream &out, ASTNode *node, int parentId, int &nodeCount);
void generateDOT(ASTNode *root, const std::string &filename);
void printSExpression(ASTNode *root, std::ofstream &outputFile, int indent = 0);
void writeASTToSExpression(ASTNode *root, const std::string &outputFileName);
void printASTRecursive(ASTNode *node, std::ofstream &outFile, const std::string &prefix, bool isLast);
void printASTToFile(ASTNode *root, const std::string &outputFileName);

#endif // UTILITY_H
