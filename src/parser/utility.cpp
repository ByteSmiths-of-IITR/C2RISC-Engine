#include "utility.h"
#include "parser.tab.h"

#define EMPTY_VAL "!!EMPTY!!"

//----------- ASTNode Class
    ASTNode::ASTNode(
        std::string type, 
        std::string value,
        int line,
        int column
    ) {
        this->type = type;
        this->position = std::make_pair(line, column);
        this->value = value;
    }

    ASTNode::ASTNode(
        std::string type, 
        std::string value, 
        std::pair<int,int> position
    ) {
        this->type = type;
        this->value = value;
        this->position = position;
    }

    ASTNode::ASTNode(TokenAttribute* tokenAtr) {
        this->type = getTokenName(tokenAtr->tokenType);
        this->value = tokenAtr->value;
        this->position = tokenAtr->position;
    }

    ASTNode::ASTNode(std::string type) {
        this->type = type;
        this->value = EMPTY_VAL;
        this->position = std::make_pair(-1, -1); // Not valid position
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

    void ASTNode::addChild(std::string type) {
        ASTNode *child = new ASTNode(type);
        addChild(child);
    }

    // Adds multiple children to the current node
    void ASTNode::addChildren(std::vector<ASTNode *> children) {
        for (ASTNode *child : children) {
            addChild(child);
        }
    }

    void ASTNode::addChild(TokenAttribute* tokenAtr) {
        ASTNode *child = new ASTNode(tokenAtr);
        addChild(child);
    }

    void ASTNode::addChild(
        std::string type,
        std::string value,
        std::pair<int,int> position
    ){
        ASTNode *child = new ASTNode(type, value, position);
        addChild(child);
    }

    // Creates a new child node with the given type and value
    void ASTNode::addChild(
        std::string type, 
        std::string value,
        int line,
        int column
    ) {
        ASTNode *child = new ASTNode(type, value, line, column);
        addChild(child);
    }

    // Prints the ASTNode and its children recursively
    void ASTNode::print(int level) {
        for (int i = 0; i < level; i++) {
            // std::cout << "  ";
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

std::string ASTStyle(ASTNode* node) {
    std::string param = node->type;
    if (param == "IDENTIFIER") {
        return "shape=egg, style=filled, fillcolor=seagreen1";
    }
    else if (param == "structID"){
        return "shape=egg, style=filled, fillcolor=seagreen2";
    }
    else if (param == "unionID"){
        return "shape=egg, style=filled, fillcolor=seagreen3";
    }
    else if (param == "enumID"){
        return "shape=egg, style=filled, fillcolor=seagreen4";
    } 
    else if (param == "CONSTANT")
    {
        return "shape=Mcircle, style=filled, fillcolor=orange";
    }
    else if (param == "STRING_LITERAL"){
        return "shape=plain, style=dashed, fillcolor=lightcoral";
    }
    else if (param == "TranslationUnit")
    {
        // this is the root node
        return "shape=doubleoctagon, style=filled, fillcolor=lightcoral";
    }
    else if(param =="Struct"){
        return "shape=box3d, style=filled, fillcolor=olivedrab1";
    }
    else if(param =="Union"){
        return "shape=box3d, style=filled, fillcolor=olivedrab1";
    }
    else if(param =="Enum"){
        return "shape=box3d, style=filled, fillcolor=olivedrab3";
    }
    else if(param =="Function Definition"){
        return "shape=invhouse, style=filled, fillcolor=lightblue";
    }
    else if(param =="Declaration"){
        return "shape=invtrapezium, style=filled, fillcolor=lightblue";
    }

    // List
    else if(param == "Struct or Union Declarator List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }
    else if (param == "Empty Parameter List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }
    else if(param == "Parameter List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }
    else if(param == "Argument List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }
    else if (param == "Initialization or Declaration List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }
    else if(param =="Enum List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }
    else if(param=="Statement List"){
        return "shape=component, style=striped, fillcolor=lightblue";
    }

    // Member Access
    else if(param=="Member Access"){

    }
    else if(param=="Pointer Member Access"){

    }




    else if (param == "Type Specifier")
    {
            return "shape=parallelogram, style=filled, fillcolor=orange";
    }
    else if(param =="Type Qualifier"){
        return "shape=parallelogram, style=filled, fillcolor=orangered";
    }
    else if(param =="Storage Class Specifier"){
        return "shape=parallelogram, style=filled, fillcolor=orchid";
    }


    else if(param =="Struct Declaration List"){
        return "shape=box, style=filled, fillcolor=lightblue";
    }
    else if(param =="Struct Declaration"){
        return "shape=box, style=filled, fillcolor=lightblue";
    }
    else if(param =="Specifie Qualifier List"){
        return "shape=box, style=filled, fillcolor=lightblue";
    }

    return "shape=oval, style=filled, fillcolor=bisque";
    }

//--------------- Writes the AST to a DOT format file recursively
    void writeNode(std::ofstream &out, ASTNode* node, int parentId, int &nodeCount) {
        if (!node) return;

        int currentId = nodeCount++;
        out << "    node" << currentId << " [label=\"";
        if(node->value == "!!EMPTY!!") {
            out << node->type;
        } else {
            // if the value is a string, escape the quotes
            std::string value = node->value;
            for (size_t i = 0; i < value.size(); ++i) {
                if (value[i] == '\"') {
                    value.insert(i, "\\");
                    i++;
                }
            }
            out << value;
        }
        std::string styleSettings = ASTStyle(node);
        out << "\", " << styleSettings << "];\n";

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
        out << "    node [shape=oval, style=filled, fillcolor=bisque];\n";

        int nodeCount = 0;
        writeNode(out, root, -1, nodeCount); 

        out << "}\n";
        out.close();
    }

//----------- Function to print the AST in S-expression format
    void printSExpression(ASTNode* root, std::ofstream& outputFile, int indent ) {
    // Base case: if the node is null, just return
    if (root == nullptr) return;

    // Print indentation
    outputFile << std::string(indent, ' ');

    // Open parenthesis for the current node
    outputFile << "(";
    
    // Print node type or value
    if (root->value == "!!EMPTY!!") {
        outputFile << root->type;
    } else {
        outputFile << root->value;
    }

    // If there are children, recursively print them
    if (!root->children.empty()) {
        outputFile << "\n"; // Move to the next line for children
        for (size_t i = 0; i < root->children.size(); ++i) {
            printSExpression(root->children[i], outputFile, indent + 2);
            if (i != root->children.size() - 1) {
                outputFile << "\n"; // Separate children
            }
        }
        outputFile << "\n" << std::string(indent, ' '); // Close parenthesis at correct indentation
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


//------------------ Function to recursively print the AST in the desired format
    void printASTRecursive(ASTNode* node, std::ofstream& outFile, const std::string& prefix, bool isLast) {
        if (!node) return;

        // Print the node's type and value
        outFile << prefix;
        if (isLast) {
            outFile << "└── ";  // Last node in the branch
        } else {
            outFile << "├── ";  // Not the last node in the branch
        }

        if (node->value == "!!EMPTY!!") {
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


//-------HelperFunction
#include <string>

std::string getTokenName(int token)
    {
        switch (token)
        {
        case IDENTIFIER:
            return "IDENTIFIER";
        case CONSTANT:
            return "CONSTANT";
        case STRING_LITERAL:
            return "STRING_LITERAL";
        case SIZEOF:
            return "SIZEOF";
        case PTR_OP:
            return "PTR_OP";
        case INC_OP:
            return "INC_OP";
        case DEC_OP:
            return "DEC_OP";
        case LEFT_OP:
            return "LEFT_OP";
        case RIGHT_OP:
            return "RIGHT_OP";
        case LE_OP:
            return "LE_OP";
        case GE_OP:
            return "GE_OP";
        case EQ_OP:
            return "EQ_OP";
        case NE_OP:
            return "NE_OP";
        case AND_OP:
            return "AND_OP";
        case OR_OP:
            return "OR_OP";
        case MUL_ASSIGN:
            return "MUL_ASSIGN";
        case DIV_ASSIGN:
            return "DIV_ASSIGN";
        case MOD_ASSIGN:
            return "MOD_ASSIGN";
        case ADD_ASSIGN:
            return "ADD_ASSIGN";
        case SUB_ASSIGN:
            return "SUB_ASSIGN";
        case LEFT_ASSIGN:
            return "LEFT_ASSIGN";
        case RIGHT_ASSIGN:
            return "RIGHT_ASSIGN";
        case AND_ASSIGN:
            return "AND_ASSIGN";
        case XOR_ASSIGN:
            return "XOR_ASSIGN";
        case OR_ASSIGN:
            return "OR_ASSIGN";
        case TYPE_NAME:
            return "TYPE_NAME";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case LCURLY:
            return "LCURLY";
        case RCURLY:
            return "RCURLY";
        case LSQUARE:
            return "LSQUARE";
        case RSQUARE:
            return "RSQUARE";
        case DOT:
            return "DOT";
        case COMMA:
            return "COMMA";
        case BIT_AND:
            return "BIT_AND";
        case STAR:
            return "STAR";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case BIT_NOT:
            return "BIT_NOT";
        case NOT_OP:
            return "NOT_OP";
        case DIVIDE:
            return "DIVIDE";
        case MOD:
            return "MOD";
        case LESSER_OP:
            return "LESSER_OP";
        case GREATER_OP:
            return "GREATER_OP";
        case XOR:
            return "XOR";
        case BIT_OR:
            return "BIT_OR";
        case QUESTION:
            return "QUESTION";
        case COLON:
            return "COLON";
        case SEMI_COLON:
            return "SEMI_COLON";
        case ASSIGN:
            return "ASSIGN";
        case TYPEDEF:
            return "TYPEDEF";
        case EXTERN:
            return "EXTERN";
        case STATIC:
            return "STATIC";
        case AUTO:
            return "AUTO";
        case REGISTER:
            return "REGISTER";
        case CHAR:
            return "CHAR";
        case SHORT:
            return "SHORT";
        case INT:
            return "INT";
        case LONG:
            return "LONG";
        case SIGNED:
            return "SIGNED";
        case UNSIGNED:
            return "UNSIGNED";
        case FLOAT:
            return "FLOAT";
        case DOUBLE:
            return "DOUBLE";
        case CONST:
            return "CONST";
        case VOLATILE:
            return "VOLATILE";
        case VOID:
            return "VOID";
        case STRUCT:
            return "STRUCT";
        case UNION:
            return "UNION";
        case ENUM:
            return "ENUM";
        case ELLIPSIS:
            return "ELLIPSIS";
        case CASE:
            return "CASE";
        case DEFAULT:
            return "DEFAULT";
        case IF:
            return "IF";
        case ELSE:
            return "ELSE";
        case SWITCH:
            return "SWITCH";
        case WHILE:
            return "WHILE";
        case DO:
            return "DO";
        case FOR:
            return "FOR";
        case GOTO:
            return "GOTO";
        case CONTINUE:
            return "CONTINUE";
        case BREAK:
            return "BREAK";
        case RETURN:
            return "RETURN";
        case UNTIL:
            return "UNTIL";
        default:
            return "UNKNOWN_TOKEN";
        }
    }

//-------------- TokenAttribute ---------
    TokenAttribute::TokenAttribute(
        int tokenName, 
        std::string value, 
        std::pair<int, int> position
    ) {
        this->tokenType = tokenName;
        this->value = value;
        this->position = position;
    }

    TokenAttribute::TokenAttribute(
        int tokenName, 
        std::string value, 
        int line, 
        int column
    ) {
        this->tokenType = tokenName;
        this->value = value;
        this->position = std::make_pair(line, column);
    }

    TokenAttribute::~TokenAttribute() {
        // Destructor
    }

