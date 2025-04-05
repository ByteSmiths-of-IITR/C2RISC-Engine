#include "utility.h"
#include "parser.tab.h"

int orderOfEval = 0; // Global variable to keep track of the order of evaluation

// std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> PARSER_TABLE;

std::set<std::string> typeDefIDs; // Defined Here
bool expectingTypeName = false; // Global variable to check if we are expecting a type name

//----------- ASTNode Class

    void ASTNode::addAttribute(std::string attribute) {
        // std::cerr << "Adding attribute: " << attribute << std::endl;
        attribute += " (" + std::to_string(orderOfEval) + ")";
        orderOfEval++;
        this->attributes.push_back(attribute);

        // When adding attributes clear the value field of node
        this->value = EMPTY_VAL; // This was filled during parsing

        // // Check if the attribute is added
        // for(const std::string &attr : this->attributes) {
        //     if (attr == attribute) {
        //         std::cout << "Attribute added: " << attribute << std::endl;
        //     }
        // }

    }

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

    ASTNode::ASTNode(ASTNode* child) {
        this->type = child->type;
        this->value = child->value;
        this->position = child->position;
        this->children = child->children;
        this->attributes = child->attributes;
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

    // IDs
    if (param == "IDENTIFIER") {
        return "shape=egg, style=filled, fillcolor=seagreen1";
    }
    if (param == "TYPE_NAME") {
        return "shape=parallelogram, style=filled, fillcolor=seagreen1";
    }

    // Constants and literals
    else if (param == "CONSTANT")
    {
        return "shape=Mcircle, style=filled, fillcolor=coral";
    }
    else if (param == "STRING_LITERAL"){
        return "shape=box, style=rounded, fillcolor=lightcoral";
    }
    // Program
    else if(param == "Program")
    {
        return "shape=doubleoctagon, style=filled, fillcolor=aqua";
    }
    // Root 
    else if (param == "translation_unit")
    {
        return "shape=octagon, style=filled, fillcolor=lightcoral";
    }

    // Struct Union Enum
    else if (param == "struct_or_union")
    {
        return "shape=box3d, style=filled, fillcolor=olivedrab1";
    }
    else if(param =="ENUM"){
        return "shape=box3d, style=filled, fillcolor=olivedrab3";
    }

    // SymbolTable Entry Points
    else if(param=="function_definition"){
        return "shape=cylinder, style=filled, fillcolor=darkolivegreen2";
    }
    else if(param == "struct_or_union_specifier"){
        return "shape=box3d, style=filled, fillcolor=darkolivegreen1";
    }
    else if(param =="init_declarator"){
        return "shape=box, style=filled, fillcolor=cyan2";
    }

    else if(node->value != EMPTY_VAL){
        // It's a leaf node with a value
        return "shape=box, style=filled, fillcolor=lightblue";
    }

    return "shape=box, style=filled, fillcolor=bisque";
    }

//--------------- Writes the AST to a DOT format file recursively

    void insertAfterMarker(const std::string &fileName, const std::string &marker, std::ostringstream &newContent)
    {
        std::ifstream inputFile(fileName);
        if (!inputFile)
        {
            std::cerr << "Error: Cannot open file for reading: " << fileName << std::endl;
            return;
        }

        std::ostringstream fileBuffer;
        std::string line;
        bool markerFound = false;

        while (std::getline(inputFile, line))
        {
            fileBuffer << line << '\n';
            if (!markerFound && line.find(marker) != std::string::npos)
            {
                markerFound = true;

                std::istringstream contentStream(newContent.str());
                std::string contentLine;
                while (std::getline(contentStream, contentLine))
                {
                    fileBuffer << "// "<< contentLine << '\n';
                }
                break;
            }
        }

        if (!markerFound)
        {
            std::cerr << "⚠️ Marker not found in file: " << fileName << "\n";
            fileBuffer << '\n'; // Optional extra line
            std::istringstream contentStream(newContent.str());
            std::string contentLine;
            while (std::getline(contentStream, contentLine))
            {
                fileBuffer << "// " << contentLine << '\n';
            }
        }

        inputFile.close();

        std::ofstream outputFile(fileName);
        if (!outputFile)
        {
            std::cerr << "Error: Cannot open file for writing: " << fileName << std::endl;
            return;
        }

        outputFile << fileBuffer.str();
        outputFile.close();
    }

std::string MARKER = "//=========================== C2RISC-Engine ==========================================//";

void writeNode(std::ofstream &out, ASTNode* node, int parentId, int &nodeCount) {
    if (!node) return;

    int currentId = nodeCount++;
    out << "    node" << currentId << " [label=\"";
    std::string nodeType = node->type;

    // if the value is a string, escape the quotes
    std::string nodeValue = node->value;
    for (size_t i = 0; i < nodeValue.size(); ++i) {
        if (nodeValue[i] == '\"') {
            nodeValue.insert(i, "\\");
            i++;
        }
    }
    
    std::string header = nodeType + (nodeValue != EMPTY_VAL ? (" : " + nodeValue): "");

    // std::string expectingTypeNameStr = expectingTypeName ? "true" : "false";
    // header += "\\n expectingTypeName = " + expectingTypeNameStr;

    out << header << "\\n";
    
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
    std::cerr << "UnAnnotated DOT File" << std::endl;
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    if(root == nullptr){
        std::cerr << "Error: Root node is null\n";
        return;
    }

    out << "digraph AST {\n";
    out << "    node [shape=oval, style=filled, fillcolor=bisque, fontname=\"Cochin\"];\n";

    int nodeCount = 0;
    writeNode(out, root, -1, nodeCount); 

    out << "}\n";
    out.close();
}

std::string escapeCharacters(const std::string &input)
{
    std::ostringstream result;

    std::unordered_map<std::string, std::string> opEscape = {
        {"<", "&lt;"},
        {">", "&gt;"},
        {"&", "&amp;"},
        {"\"", "&quot;"},
        {"'", "&apos;"},
        {"[", "&#91;"},
        {"]", "&#93;"},
        {"{", "&#123;"},
        {"}", "&#125;"},
        {"<=", "&le;"},
        {">=", "&ge;"},
        {"==", "&#61;&#61;"},
        {"!=", "&#33;&#61;"},
        {"&&", "&#38;&#38;"},
        {"||", "&#124;&#124;"},
        {"=", "&#61;"},
        {"!", "&#33;"}
    };

    // Scan character-by-character and build escapes
    for (size_t i = 0; i < input.size();)
    {
        bool matched = false;

        // Try to match longest possible multi-char operator first
        for (const auto &entry : opEscape)
        {
            const std::string &op = entry.first;
            if (input.substr(i, op.length()) == op)
            {
                result << entry.second;
                i += op.length();
                matched = true;
                break;
            }
        }

        // If no match, copy character as is
        if (!matched)
        {
            result << input[i];
            ++i;
        }
    }

    return result.str();
}

std::string escapeCharacters1(const std::string &input)
{
    // return input;
    std::string result;
    for (char ch : input)
    {
        if (ch == '[')
        {
            result += "\["; // Escape opening bracket
        }
        else if (ch == ']')
        {
            result += "\]"; // Escape closing bracket (optional, for safety)
        }
        else
        {
            result += ch;
        }
    }
    return result;
}

std::string getSecondLastWord(const std::string &infoStr)
{
    size_t lastSpace = infoStr.find_last_of(" ");

    // If no spaces found, there's only one word
    if (lastSpace == std::string::npos)
    {
        return ""; // No second last word exists
    }

    size_t secondLastSpace = infoStr.find_last_of(" ", lastSpace - 1);

    // Extract second last word
    return infoStr.substr(secondLastSpace == std::string::npos ? 0 : secondLastSpace + 1,
                          lastSpace - (secondLastSpace == std::string::npos ? 0 : secondLastSpace + 1));
}

std::string getColor(std::string infoStr){
    std::string firstWord = infoStr.substr(0, infoStr.find(" "));
    std::string type = infoStr.substr(0, 3);
    std::string lastWord = getSecondLastWord(infoStr);
    // std::string lastWord = infoStr.substr(infoStr.find_last_of(" ") + 1);
    // std::cout << "Type: " << type << std::endl;
    std::string color = "darkorchid2";
    // std::cerr << "Type: |" << type << "|" << std::endl;
    // std::cerr << "First: |" << firstWord << "|" << std::endl;
    // std::cerr << "Last: |" << lastWord << "|" << std::endl;
    if (type == "syn" || firstWord == "⏫" || firstWord == "🔺" || firstWord == "⬆️" || lastWord == "⏫" || lastWord == "⬆️" || lastWord == "🔺")
    {
        color = "firebrick3";
    }
    else if (type == "inh" || firstWord == "🔻" || firstWord == "⏬" || firstWord == "⬇️" || lastWord == "🔻" || lastWord == "⏬" || lastWord == "⬇️")
    {
        color = "blue3";
    }
    else if (lastWord == "⤵️" || lastWord == "☀️" || lastWord == "↙️" || type == "Scope" || type == "Early")
    {
        color = "darkgreen";
    }
    else if (firstWord == "🥺")
    {
        // no attribute
        color = "white";
    }
    else if (firstWord == "🟡")
    {
        // Stop attribute
        color = "yellow";
    }
    else if(lastWord == "✌️"){
        // Exit
        color = "red";
    }
    else if(firstWord == "🤞"){
        // Entry
        color = "green";
    }
    else if(firstWord == "🚨"){
        // Error 
        color = "red";
    }
    else if(lastWord == "👆"){
        // Pass the Error
        color = "red";
    }
    else if(firstWord == "TAC:"){
        // Three Addres Code
        color = "lightblue";
    }

    return color;
}

//--------------- Write the Annotated PTree to a DOT format file recursively
void writeNode_A(std::ofstream &out, ASTNode *node, int parentId, int &nodeCount)
{
    if (!node)
        return;
    
    int currentId = nodeCount++;
    std::string header;

    std::string nodeType = node->type;

    // if the value is a string, escape the quotes
    std::string nodeValue = node->value;
    for (size_t i = 0; i < nodeValue.size(); ++i)
    {
        if (nodeValue[i] == '\"')
        {
            nodeValue.insert(i, "\\");
            i++;
        }
    }

    header = (nodeValue != EMPTY_VAL ? nodeValue : nodeType);

    std::string styleSettings = ASTStyle(node);

    //-----
    out << "    node" << currentId;
    out << " [label=<\n";
    out << "<table border=\"0\" cellborder=\"0\" cellspacing=\"0\">\n";

    // Heading with larger font
    std::string headerColor = "black";
    out << "  <tr><td><FONT COLOR=\"" << headerColor << "\"><font point-size=\"14\"><b>" << escapeCharacters(header) << "</b></font></FONT></td></tr>\n";

    // Extra info with smaller font
    // int size = node->attributes.size();
    // std::cerr << "Size of attributes: " << size << std::endl;
    for (const auto &info : node->attributes)
    {
        // std::cerr << "Printing attribute " << std::endl;
        // Check for syn_attr and inh_attr 
        
        // Customize the color based on the attribute type
        std::string color = getColor(info);
        
        out << "  <tr><td><FONT COLOR=\"" << color << "\"><font point-size=\"10\">" << escapeCharacters(info) << "</font></FONT></td></tr>\n";
    }

    out << "</table>\n";
    out << ">,";
    out << styleSettings << "];\n";

    //-----
    if (parentId != -1)
    {
        out << "    node" << parentId << " -> node" << currentId << ";\n";
    }

    for (ASTNode *child : node->children)
    {
        writeNode_A(out, child, currentId, nodeCount);
    }
}

void generateDOT_A(ASTNode *root, const std::string &filename)
{
    std::cerr << "Annotated DOT File" << std::endl;
    std::ofstream out(filename);
    if (!out)
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    if(root == nullptr)
    {
        std::cerr << "Error: Root node is null\n";
        return;
    }

    out << "digraph AST {\n";
    out << "    node [shape=oval, style=filled, fillcolor=bisque, fontname=\"Cochin\"];\n";

    int nodeCount = 0;
    writeNode_A(out, root, -1, nodeCount);

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

//     // PARSER_TABLE
// void printParserTable(std::ostream &out)
//     {
//         // Sort by (lineNo, columnNo)
//     std::sort(PARSER_TABLE.begin(), PARSER_TABLE.end(),
//                 [](const auto &a, const auto &b)
//                 {
//                     return (a.first.first < b.first.first) ||
//                             (a.first.first == b.first.first && a.first.second < b.first.second);
//                 });

//         // Set dynamic column widths
//         int positionWidth = 14; // Width for "LineNo:Column"
//         int idNameWidth = 20;   // Width for Identifier Name
//         int idTypeWidth = 35;   // Width for Identifier Type

//         // Print table header
//         out << "+" << std::string(positionWidth + 2, '-')
//             << "+" << std::string(idNameWidth + 2, '-')
//             << "+" << std::string(idTypeWidth + 2, '-')
//             << "+" << std::endl;

//         out << "| " << std::setw(positionWidth) << std::left << "Position"
//             << " | " << std::setw(idNameWidth) << std::left << "Identifier Name"
//             << " | " << std::setw(idTypeWidth) << std::left << "Identifier Type"
//             << " |" << std::endl;

//         out << "+" << std::string(positionWidth + 2, '-')
//             << "+" << std::string(idNameWidth + 2, '-')
//             << "+" << std::string(idTypeWidth + 2, '-')
//             << "+" << std::endl;

//         // Print each entry
//         for (const auto &entry : PARSER_TABLE)
//         {
//             int line = entry.first.first;
//             int column = entry.first.second;
//             std::string idName = entry.second.first;
//             std::string idType = entry.second.second;

//             out << "| " << std::setw(positionWidth) << std::left << (std::to_string(line) + ":" + std::to_string(column))
//                 << " | " << std::setw(idNameWidth) << std::left << idName
//                 << " | " << std::setw(idTypeWidth) << std::left << idType
//                 << " |" << std::endl;
//         }

//         // Print table footer
//         out << "+" << std::string(positionWidth + 2, '-')
//             << "+" << std::string(idNameWidth + 2, '-')
//             << "+" << std::string(idTypeWidth + 2, '-')
//             << "+" << std::endl;
//     }

    // void writeLatexTable(std::ostream &out)
    // {
    //     // LaTeX document header
    //     out << "\\documentclass{article}\n";
    //     out << "\\usepackage[a4paper,margin=1in]{geometry}\n";
    //     out << "\\usepackage{longtable}\n";
    //     out << "\\usepackage[table]{xcolor}\n";
    //     out << "\\definecolor{headercolor}{RGB}{79, 129, 189}\n";
    //     out << "\\definecolor{rowcolor}{RGB}{217, 225, 242}\n";
    //     out << "\\begin{document}\n\n";
    //     out << "\\begin{center}\n";
    //     out << "    {\\LARGE \\textbf{Parser Table of Input Program}} \\\\[10pt]\n";
    //     out << "\\end{center}\n\n";
    //     out << "\\renewcommand{\\arraystretch}{1.3}\n";
    //     out << "\\setlength{\\arrayrulewidth}{0.7mm}\n";
    //     out << "\\rowcolors{2}{rowcolor}{white}\n";

    //     // Begin table
    //     out << "\\begin{longtable}{|l|c|c|}\n";
    //     out << "    \\hline\n";
    //     out << "    \\rowcolor{headercolor} \\textbf{lineNo:columnNo} & \\textbf{Identifier Name} & \\textbf{Identifier Type} \\\\ \n";
    //     out << "    \\hline\n";
    //     out << "    \\endfirsthead\n";
    //     out << "    \\hline\n";
    //     out << "    \\rowcolor{headercolor} \\textbf{lineNo:columnNo} & \\textbf{Identifier Name} & \\textbf{Identifier Type} \\\\ \n";
    //     out << "    \\hline\n";
    //     out << "    \\endhead\n";
    //     // Populate table rows from PARSER_TABLE
    //     for (const auto &entry : PARSER_TABLE)
    //     {
    //         std::string correctTokenName;
    //         // Replace _ with \\_
    //         for (char c : entry.second.first)
    //         {
    //             if (c == '_')
    //                 correctTokenName += "\\_";
    //             else
    //                 correctTokenName += c;
    //         }
    //         out << "    " << entry.first.first << ":" << entry.first.second << " & "
    //             << correctTokenName << " & "
    //             << entry.second.second << " \\\\ \n";
    //         out << "    \\hline\n";
    //     }

    //     // End table and document
    //     out << "\\end{longtable}\n\n";
    //     out << "\\end{document}\n";
    // }

    // //