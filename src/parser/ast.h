#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// ASTNode class definition
class ASTNode {
public:
    std::string type; // token type
    std::string value; // token value
    std::vector<ASTNode *> children;

    ASTNode(std::string type, std::string value);
    ASTNode(std::string type);
    ~ASTNode();

    void addChild(ASTNode *child);
    void createChild(std::string type, std::string value);
    void print(int level);
};

// Function declarations
void printAST(ASTNode *root);
void writeNode(std::ofstream &out, ASTNode* node, int parentId, int &nodeCount);
void generateDOT(ASTNode* root, const std::string& filename);
void printSExpression(ASTNode* root, std::ofstream& outputFile, int indent = 0);
void writeASTToSExpression(ASTNode* root, const std::string& outputFileName);
void printASTRecursive(ASTNode* node, std::ofstream& outFile, const std::string& prefix, bool isLast);
void printASTToFile(ASTNode* root, const std::string& outputFileName);



#endif // AST_H
