#include "ast.h"

// ASTNode constructor
ASTNode::ASTNode(std::string type, std::string value) {
    this->type = type;
    this->value = value;
}

ASTNode::ASTNode(std::string type) {
    this->type = type;
    this->value = "";
}

// Destructor that deletes child nodes
ASTNode::~ASTNode() {
    for (ASTNode *child : children) {
        delete child;
    }
}

// Adds a child node to the current node
void ASTNode::addChild(ASTNode *child) {
    children.push_back(child);
}

// Creates a new child node with the given type and value
void ASTNode::createChild(std::string type, std::string value) {
    ASTNode *child = new ASTNode(type, value);
    addChild(child);
}

// Prints the ASTNode and its children recursively
void ASTNode::print(int level) {
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    std::cout << type << " : " << value << std::endl;
    for (ASTNode *child : children) {
        child->print(level + 1);
    }
}

// Prints the AST by calling print() on the root node
void printAST(ASTNode *root) {
    root->print(0);
}

// Writes the AST to a DOT format file recursively
void writeNode(std::ofstream &out, ASTNode* node, int parentId, int &nodeCount) {
    if (!node) return;

    int currentId = nodeCount++;
    out << "    node" << currentId << " [label=\"";
    if(node->value == "") {
        out << node->type;
    } else {
        out << node->value;
    }
    out << "\"];\n";

    if (parentId != -1) {
        out << "    node" << parentId << " -> node" << currentId << ";\n";
    }

    for (ASTNode* child : node->children) {
        writeNode(out, child, currentId, nodeCount);
    }
}

// Generates a DOT file to visualize the AST
void generateDOT(ASTNode* root, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    out << "digraph AST {\n";
    out << "    node [shape=oval, style=filled, fillcolor=lightgray];\n";

    int nodeCount = 0;
    writeNode(out, root, -1, nodeCount); 

    out << "}\n";
    out.close();
}

// Function to print the AST in S-expression format
    void printSExpression(ASTNode* root, std::ofstream& outputFile) {
        // Base case: if the node is null, just return
        if (root == nullptr) return;

        // Open parenthesis for the current node
        outputFile << "(";
        if(root->value == "") {
            outputFile << root->type;
        } else {
            outputFile << root->value;
        }
        

        // If there are children, recursively print them
        for (ASTNode* child : root->children) {
            printSExpression(child, outputFile);
        }

        // Close the parenthesis for the current node
        outputFile << ")";
    }

    // Wrapper function to take root and output file name
    void writeASTToSExpression(ASTNode* root, const std::string& outputFileName) {
        // Open the output file
        std::ofstream outputFile(outputFileName);

        if (!outputFile) {
            std::cerr << "Error opening file: " << outputFileName << std::endl;
            return;
        }

        // Print the AST in S-expression format starting from the root
        printSExpression(root, outputFile);

        // Close the file
        outputFile.close();
    }



// Function to recursively print the AST in the desired format
    void printASTRecursive(ASTNode* node, std::ofstream& outFile, const std::string& prefix, bool isLast) {
        if (!node) return;

        // Print the node's type and value
        outFile << prefix;
        if (isLast) {
            outFile << "└── ";  // Last node in the branch
        } else {
            outFile << "├── ";  // Not the last node in the branch
        }

        if (node->value.empty()) {
            outFile << "(" << node->type << ")\n";  // Node with type only
        } else {
            outFile << "\"" << node->value << "\"\n";  // Node with value (e.g., variable or literal)
        }

        // Recursively print the children
        for (size_t i = 0; i < node->children.size(); ++i) {
            printASTRecursive(node->children[i], outFile, prefix + (isLast ? "    " : "│   "), i == node->children.size() - 1);
        }
    }

    // Wrapper function to handle the printing of AST to file
    void printASTToFile(ASTNode* root, const std::string& outputFileName) {
        std::ofstream outFile(outputFileName);
        if (!outFile) {
            std::cerr << "Error opening file: " << outputFileName << std::endl;
            return;
        }

        // Print the root node and its children recursively
        printASTRecursive(root, outFile, "", true);

        // Close the output file
        outFile.close();
    }
