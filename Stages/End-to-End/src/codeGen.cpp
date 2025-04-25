#include "header.h"
#include "utility.h"

//=====================[ Code Generation ]=========================================================================================

SymTable SYM_RECORD; // Global Symbol Table [offset + liveliness + getRegUtilities]
RegisterInfo REG_TABLE;

// We have access to IRCode via -> IR_CODE
CFG CFG_CODE;          // This will be the control flow graph
RISCV_CODE FINAL_CODE; // This will be the final RISC-V code

int codeGen()
{

    // Step 1. Add SymbolTable Info (offset, function-size, etc)

    int check = addSymbolsToSymTable();
    if (check != OKAY)
    {
        CERR << "Error in adding symbols to symbol table" << std::endl;
        return check;
    }

    // Step 1# Checking SymTable
    std::ofstream symTableFile("output/symRecord.txt");
    SYM_RECORD.printTable(symTableFile);
    symTableFile.close();
    CERR << " | Symbol Table generated successfully at output/symRecord.txt" << std::endl;

    // Step 2. Identify basic blocks & control flow +

    check = makeBasicBlocks();
    if (check != OKAY)
    {
        CERR << "Error in making basic blocks" << std::endl;
        return check;
    }


    // Step 3. Liveliness Analysis + CodeTransfer

    check = livelinessPass();
    if (check != OKAY)
    {
        CERR << "Error in liveliness pass" << std::endl;
        return check;
    }

    // Step 3#. Try to visualize the CFG
    std::string dotFileName = "build/cfg.dot";
    REACHING;
    check = CFG_CODE.generateDOTFile(dotFileName);
    REACHING;
    if (check != OKAY)
    {
        CERR << "Error in generating dot file" << std::endl;
        return check;
    }
    CERR << " | CFG generated successfully at " << dotFileName << std::endl;
    // Step 4. PerBlock RISC-V CODEGEN
}

//======================[ Symbol Table Adding Code ]=========================================================================================

int addSymbolsToSymTable()
{
    // This will add all the symbols to the symbol table
    // We will use the IR_CODE to get the symbols

    for (int i = 0; i < IR_CODE.code.size(); i++)
    {
        TAC_Quadruple currIR = IR_CODE.code[i];
        std::string op = currIR.op;

        if (op == FUNCTION_ENTRY)
        {
            // This is a function entry
            std::string funcName = currIR.result;
            int check = SYM_RECORD.enterFunction(funcName);
            if (check != OKAY)
            {
                CERR << "Error in entering function" << std::endl;
                return check;
            }
        }
        else if (op == FUNCTION_EXIT)
        {
            // This is a function exit
            int check = SYM_RECORD.exitFunction();
            if (check != OKAY)
            {
                CERR << "Error in exiting function" << std::endl;
                return check;
            }
        }
        else if (op == ALLOCATE)
        {
            // This is a variable allocation
            std::string varName = currIR.result;
            int size = std::stoi(currIR.arg1);
            int check = SYM_RECORD.insert(varName, size);
            if (check != INSERT_SUCCESS)
            {
                CERR << "Error in inserting variable" << std::endl;
                return check;
            }
        }
    }

    return OKAY;
}

//=====================[ Basic Block Class Functions ]=========================================================================================

void BasicBlock::logLivelinessInfo()
{
    std::cerr << "----- Liveliness Info for Block --------" << label << std::endl;
    for (auto it : livelinessInfo)
    {
        std::cerr << "Variable " << it.first << " : ";
        if (it.second.first)
        {
            std::cerr << "isLive";
        }
        else
        {
            std::cerr << "notLive";
        }

        std::cerr << " nextUse at -";
        for (auto j : it.second.second)
        {
            std::cerr << " " << j;
        }
        std::cerr << std::endl;
    }
    std::cerr << "--------------------------------" << std::endl;
}

void BasicBlock::printCode(std::ostringstream &oss)
{
    oss << label << " : " << std::endl;
    for (auto it : irCode.code)
    {
        oss << std::string(2, ' ') << std::setw(3) << std::to_string(it.first) << " : " << it.second.toString() << std::endl;
    }
    // oss << std::endl;
}

//=====================[ CFGs Class Functions ]=========================================================================================

std::string CFG::newBlock()
{
    std::string label = "Block_" + std::to_string(nextBlockIndex++);
    return label;
}

int CFG::add_NEWTAC(int irLineNo, NEW_TAC_Quadruple code)
{

    std::string name = blockName(irLineNo);
    if (blocks.find(name) == blocks.end())
    {
        // The block must already exist
        CERR << "Error in adding new TAC - Block not found" << std::endl;
        return FAIL;
    }
    blocks[name].irCode.addTAC(irLineNo, code);
    return OKAY;
}

int CFG::addEdge(const std::string &from, const std::string &to)
{
    // This will add an edge from 'from' to 'to'
    // We will use the labelMap to get the index of the blocks

    // auto itFrom = labelMap.find(from);
    // auto itTo = labelMap.find(to);

    // if (itFrom == labelMap.end() || itTo == labelMap.end())
    // {
    //     CERR << "Error in adding edge - Block not found" << std::endl;
    //     return FAIL;
    // }

    // int fromIndex = itFrom->second;
    // int toIndex = itTo->second;

    if(edges.find(from) == edges.end())
    {
        edges[from] = std::vector<std::string>();
    }
    edges[from].push_back(to);

    return OKAY;
}

int CFG::generateDOTFile(const std::string &filename)
{
    // This will generate a dot file for the CFG
    std::ofstream dotFile(filename);
    if (!dotFile.is_open())
    {
        CERR << "Error in opening file" << std::endl;
        return FAIL;
    }

    dotFile << "digraph G {" << std::endl;
    // Add nodes
    for (auto block : blocks)
    {
        dotFile << block.first;
        dotFile << " [label=<\n";
        dotFile << "<table border=\"0\" cellborder=\"1\" cellspacing=\"1\">\n";

        // Heading with larger font
        std::string headerColor = "blue3";
        dotFile << "  <tr><td><FONT COLOR=\"" << headerColor << "\"><font point-size=\"12\"><b>" << block.first << "</b></font></FONT></td></tr>\n";

        // Extra info with smaller font
        for (auto it : block.second.irCode.code)
        {
            std::string info = it.second.toString();
            info = escapeCharacters(info);
            info = std::to_string(it.first) + " : " + info;
            dotFile << "  <tr><td><FONT COLOR=\"brown1\"><font point-size=\"10\">" << info << "</font></FONT></td></tr>\n";
        }
        dotFile << "</table>\n";
        dotFile << ">, shape=box];" << std::endl;
    }

    
    // Add edges
    for (auto edge : edges)
    {
        std::string fromBlock = edge.first;
        for(auto toBlock : edge.second)
        {
            dotFile << fromBlock << " -> " << toBlock << ";" << std::endl;
        }
    }

    dotFile << "}" << std::endl;
    dotFile.close();

    return OKAY;
}

int CFG::whichBlock(int index)
{
    // Find the just smaller leader than index
    int foundLeader = -1;
    for (int i = 0; i < leaders.size(); i++)
    {
        if (leaders[i] <= index)
        {
            foundLeader = leaders[i];
        }
        else
        {
            break;
        }
    }

    return foundLeader;
}

std::string CFG::blockName(int index){
    int leaderIndex = whichBlock(index);
    if(leaderToBlockMap.find(leaderIndex)!=leaderToBlockMap.end()){
        return leaderToBlockMap[leaderIndex];
    }
    return NO_BLOCK;
}

int CFG::addLeader(int leader){
    // This will create a Leader
    std::string newBLockName = newBlock();
    leaderToBlockMap[leader] = newBLockName;
    leaders.push_back(leader);
    return 0;
}

bool CFG::isALeader(int index){
    // This will check if the index is a leader
    if(leaderToBlockMap.find(index) != leaderToBlockMap.end()){
        return true;
    }
    return false;
}

int CFG::addLeader(int leader, std::string blockName){
    leaderToBlockMap[leader] = blockName;
    leaders.push_back(leader);
    return OKAY;
}

void CFG::sortLeaders(){
    sort(leaders.begin(), leaders.end());
}

int CFG::addEdge(int from,int to){
    std::string fromBlock = blockName(from);
    std::string toBlock = blockName(to);
    return addEdge(fromBlock, toBlock);
}

std::string NO_BLOCK = "NO_BLOCK";

void CFG::printCode(std::ostringstream &oss)
{
    std::string currBlock = "ENTRY";
    oss << "====================== [ CFG Code ] ======================" << std::endl;
    oss << ".data" << std::endl;
    for (auto it : dataSection)
    {
        dataSegment currData = it.second;
        oss << std::string(4, ' ') << currData.name << " : " << std::setw(20) << currData.type << " " << std::setw(20) << currData.value << std::endl;
    }
    oss << std::endl;

    oss << ".text" << std::endl;
    // We would like to print block code in order of control flow
    std::queue<std::string> order;
    std::map<std::string, bool> visited;
    order.push("ENTRY");
    while (!order.empty())
    {
        std::string currBlock = order.front();
        order.pop();
        if (visited.find(currBlock) != visited.end())
        {
            continue;
        }
        visited[currBlock] = true;

        // This will print the code for the current block
        CFG_CODE.blocks[currBlock].printCode(oss);

        // Add the edges to the queue
        if (edges.find(currBlock) != edges.end())
        {
            for (auto it : edges[currBlock])
            {
                order.push(it);
            }
        }
    }
}

//=====================[ Basic Blocks]=========================================================================================

int makeBasicBlocks()
{

    // Step 1. Identify basic blocks & some small stuffs

    // All those instruction with operation GOTO_LABEL, IF_TRUE, IF_FALSE, FUNCTION_ENTRY, GOTO_EQUAL, CALL

    // Assign Name to each Block & Fill indexToBlockMap
    for (int i = 0; i < IR_CODE.code.size(); i++)
    {
        std::string op = IR_CODE.code[i].op;

        // Target Leaders
        if (op == FUNCTION_ENTRY)
        {
            std::string funcName = IR_CODE.code[i].result;
            CFG_CODE.addLeader(i, funcName);
        }

        if (op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE || op == GOTO_EQUAL)
        {
            int targetIndex = std::stoi(IR_CODE.code[i].result);
            CFG_CODE.addLeader(targetIndex);
        }

        // Return Point Leader - i.e next line to goto, call, etc.
        if (op == GOTO_EQUAL || op == IF_FALSE || op == IF_TRUE || op == CALL || op == GOTO_LABEL)
        {

            // Special Case of merging if-else block
            if (op == IF_TRUE || op == IF_FALSE)
            {
                // and next line is a goto label & target is next-to-next line
                std::string op_next = IR_CODE.code[i + 1].op;
                int target = std::stoi(IR_CODE.code[i].result);
                if (op_next == GOTO_LABEL && target == i + 2)
                {
                    continue;
                }
            }

            // Else all next lines are leaders
            if (i + 1 < IR_CODE.code.size())
            {
                CFG_CODE.addLeader(i + 1);
            }
        }
    }

    CFG_CODE.sortLeaders(); // Sort the Leaders

    // Step 2. Change Lables in jump instructions

    // Change jump (lineNo) -> (block labels)
    for (int i = 0; i < IR_CODE.code.size(); i++)
    {

        std::string op = IR_CODE.code[i].op;

        if (op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE || op == GOTO_EQUAL)
        {
            int targetIndex = std::stoi(IR_CODE.code[i].result);
            std::string newBlockLable = CFG_CODE.blockName(targetIndex);
            if (newBlockLable != NO_BLOCK)
            {
                std::cerr << "Goto Label Change from " << IR_CODE.code[i].result << " to " << newBlockLable << std::endl;
                IR_CODE.code[i].result = newBlockLable;
            }
            else{
                // Something Wrong, The target labels must be Leaders
                std::cerr << "Error in Goto Label - Target not found" << std::endl;
            }
        }
    }

    /*

    Step 3. Create All the blocks

    */
    BasicBlock entryBlock;
    entryBlock.label = "ENTRY";
    CFG_CODE.blocks["ENTRY"] = entryBlock;
    // CFG_CODE.labelMap["ENTRY"] = 0;

    // Now Create all Block and Map their Name to Blocks in CFG
    for (auto it : CFG_CODE.leaderToBlockMap)
    {
        // std::cerr << "Block Name : " << it.first << " - " << it.second << std::endl;
        BasicBlock newBlock;
        newBlock.label = it.second; // Block Name
        CFG_CODE.blocks[newBlock.label] = newBlock;
    }

    BasicBlock exitBlock;
    exitBlock.label = "EXIT";
    CFG_CODE.blocks["EXIT"] = exitBlock;

    /*

    Step 4. Create the edges

    */
    // We scan the IRCode and MakeEdges

    // Link Entry
    CFG_CODE.addEdge("ENTRY", "main");

    // Return From Points in Functions [Needed for Function Control Flow Connections]
    std::map<std::string, std::vector<std::string>> functionReturnFrom;
    std::string currFunction = "NULL";
    for (int i = 0; i < IR_CODE.code.size(); i++)
    {
        std::string op = IR_CODE.code[i].op;

        if (op == FUNCTION_ENTRY)
        {
            currFunction = IR_CODE.code[i].result;
        }

        std::string name = CFG_CODE.blockName(i);
        if (op == RETURN_FUNCTION)
        {
            // We need to store the return point
            if (functionReturnFrom.find(currFunction) == functionReturnFrom.end())
            {
                // Not added to map YET
                functionReturnFrom[currFunction] = std::vector<std::string>();
            }
            functionReturnFrom[currFunction].push_back(name);
        }

        if (op == FUNCTION_EXIT)
        {
            if (functionReturnFrom.find(currFunction) == functionReturnFrom.end())
            {
                functionReturnFrom[currFunction] = std::vector<std::string>();
                functionReturnFrom[currFunction].push_back(name);
            }
            // Else not need
        }
    }


    std::cerr << "Function Return Points" << std::endl;
    for (auto it : functionReturnFrom)
    {
        std::cerr << "ForFunction : " << it.first << " has return points -";
        for (auto jt : it.second)
        {
            std::cerr << " " << jt;
        }
        std::cerr << std::endl;
    }

    // REACHING;
    // Now we will add edges to all the blocks
    for (int i = 0; i < IR_CODE.code.size(); i++)
    {
        std::string op = IR_CODE.code[i].op;
        if (op == IF_FALSE || op == IF_TRUE || op == GOTO_LABEL || op == GOTO_EQUAL)
        {
            std::string fromBlock = CFG_CODE.blockName(i);

            std::string toBlock = IR_CODE.code[i].result;
            CFG_CODE.addEdge(fromBlock, toBlock);
        }
        else if (op == CALL)
        {
            int fromIndex = CFG_CODE.whichBlock(i);
            std::string fromBlock = CFG_CODE.blockName(i);
            std::string toBlock = IR_CODE.code[i].arg1;

            CFG_CODE.addEdge(fromBlock, toBlock);
            CERR<< "FCall Edge " << fromBlock << " -> " << toBlock << std::endl;

            int returnIndex = CFG_CODE.whichBlock(i + 1);
            std::cerr << "Func called from " << fromIndex << " return block " << returnIndex << std::endl;
            std::string returnBlock = CFG_CODE.leaderToBlockMap[returnIndex];
            // All Possible fromReturn points are in functionReturnFrom
            if (functionReturnFrom.find(toBlock) != functionReturnFrom.end())
            {
                std::vector<std::string> returnPoints = functionReturnFrom[toBlock];
                for (auto it : returnPoints)
                {
                    CFG_CODE.addEdge(it, returnBlock);
                    CERR<< "FCall Edge " << returnBlock << " -> " << it << std::endl;
                }
            }
            else
            {
                CFG_CODE.addEdge(returnBlock, "EXIT");
                CERR<< "FCall Edge " << returnBlock << " -> EXIT" << std::endl;
            }
        }
        else
        {
            int fromIndex = CFG_CODE.whichBlock(i);
            int toIndex = CFG_CODE.whichBlock(i + 1);

            if (fromIndex != toIndex)
            {
                std::cerr << "Trivial Connecting" << i << " & " << i + 1 << std::endl;
                std::cerr << "Edge " << fromIndex << " -> " << toIndex << std::endl;
                CFG_CODE.addEdge(fromIndex,toIndex);
            }
        }
    }

    // REACHING;
    // Handle Return from points of main
    for (auto it : functionReturnFrom["main"])
    {
        CFG_CODE.addEdge(it, "EXIT");
        CERR<< "Main Edge " << it << " -> EXIT" << std::endl;
    }

    // REACHING;

    return OKAY;
}

//=====================[ Live & NextUse + CodeCopy ]=========================================================================================

int livelinessPass(){
    // This will Perform Liveliness Scan & Also add irCode to CFG_CODE;

    // Check Leaders
    // for(auto k:CFG_CODE.leaderToBlockMap){
    //     std::cerr << "Leader " << k.first << " - " << k.second << std::endl;
    // }

    // We would need a bottom up scan perblock
    int n = IR_CODE.code.size();
    bool isNewBlock = true;
    for (int i = n - 1; i >= 0; i--)
    {

        std::string op = IR_CODE.code[i].op;
        std::string result = IR_CODE.code[i].result;
        std::string arg1 = IR_CODE.code[i].arg1;
        std::string arg2 = IR_CODE.code[i].arg2;

        std::cerr << "Scanning " << i << " - " << op << std::endl;

        if(isNewBlock){
            std::cerr << "New Block's Bottom at " << i << std::endl;
            CFG_CODE.resetLiveliness(i);
        }

        /*
        Step 1. Copy the IR_CODE to CFG_CODE with Liveliness info
        */
        
        NEW_TAC_Quadruple newTAC(IR_CODE.code[i]); // This copies oldTAC to newTAC
        LivelinessDS info;
        int check = CFG_CODE.getAllLivelinessInfo(i, info);
        if(check != OKAY){
            CERR << "Error in getting liveliness info from SYM_TABLE" << std::endl;
            return check;
        }

        // We are adding Information of all Variables - regardless of  

        // Now we will add the liveliness info to the newTAC
        newTAC.addLivelinessInfo(info);

        // Add this newTAC to the CFG_CODE
        CFG_CODE.add_NEWTAC(i, newTAC);

        /*
        Step 2. Update the Liveliness info in CFG_CODE's Respective Block
        */

        // First we identify OP that have Assigment Actions on results
        

        if(op == CALL || op == LEFT_STAR || 
            op == GOTO_EQUAL || op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE){
            // Those in which result is used & not assigned


            if(isASymbol(result)){
                // If it's a symbol
                if(CFG_CODE.usageAt(i, result) != OKAY){
                    CERR << "Error in adding usage at " << i << "for result=" << result << std::endl;
                    return FAIL;
                }
            }
            if(isASymbol(arg1)){
                // If it's a symbol
                if(CFG_CODE.usageAt(i, arg1) != OKAY){
                    CERR << "Error in adding usage at " << i << "for arg1=" << arg1 << std::endl;
                    return FAIL;
                }
            }
            if(isASymbol(arg2)){
                // If it's a symbol
                if(CFG_CODE.usageAt(i, arg2) != OKAY){
                    CERR << "Error in adding usage at " << i << "for arg2=" << arg2 << std::endl;
                    return FAIL;
                }
            }

        }
        else if(op == FUNCTION_ENTRY || op == FUNCTION_EXIT || op == ALLOCATE){
            // Those to be Ignored

            if(op == ALLOCATE){
                std::string varName = result;
                int check = CFG_CODE.removeLifeInfo(i, varName);
                if(check != OKAY){
                    CERR << "Error in removing liveliness info from SYM_TABLE" << std::endl;
                    return check;
                }
            }

        }
        else{
            // Normal Operator's Type Operations + Special OP with assignment to result
            // Includes -> ASSIGN_OP, RIGHT_STAR, AMPERSEND, CAST {assignment to result}
            // Include -> PARAM, RETURN_FUNCTION {NO result variable}

            if(isASymbol(result)){
                // If it's a symbol
                if(CFG_CODE.assignmentAt(i, result) != OKAY){
                    CERR << "Error in adding assignment at " << i << "for result=" << result << std::endl;
                    return FAIL;
                }
            }

            if(isASymbol(arg1)){
                // If it's a symbol
                if(CFG_CODE.usageAt(i, arg1) != OKAY){
                    CERR << "Error in adding usage at " << i << "for arg1=" << arg1 << std::endl;
                    return FAIL;
                }
            }

            if(isASymbol(arg2)){
                // If it's a symbol
                if(CFG_CODE.usageAt(i, arg2) != OKAY){
                    CERR << "Error in adding usage at " << i << "for arg2=" << arg2 << std::endl;
                    return FAIL;
                }
            }
            

        }

        // Step 3. Tracking when a new block is starting
        // This will ensure when we are about to enter a new Block
        if(CFG_CODE.isALeader(i)){
            // This is a new block
            isNewBlock = true;
        }
        else{
            isNewBlock = false;
        }

    }

    // The LiveLinees Tracker will be kept in symbolRecord Itself - as it's a temporary datastructure;
    return OKAY;
}

//=====================[ RISC-V Code Generation ]=========================================================================================

//======================[ Register Allocation ]=========================================================================================



//======================[ SymbTable Offset+Function Code ]=========================================================================================

bool isASymbol(const std::string &name)
{
    // std::cerr << "Checking if " << name << " is a symbol" << std::endl;
    if(SYM_RECORD.symTable.find(name) != SYM_RECORD.symTable.end()){
        return true;
    }
    std::cerr << "Not a symbol" << std::endl;
    return false;
}


int SymTable::insert(const std::string &key, SymInfo &info)
{
    // This will insert the key and info in the table
    if (symTable.find(key) != symTable.end())
    {
        return INSERT_FAILURE;
    }

    symTable[key] = info;
    return INSERT_SUCCESS;
}

int SymTable::lookup(const std::string &key, SymInfo &info)
{
    // This will lookup the key and return the info
    if (symTable.find(key) == symTable.end())
    {
        return LOOKUP_FAILURE;
    }

    info = symTable[key];
    return LOOKUP_SUCCESS;
}

int SymTable::remove(const std::string &key)
{
    // This will remove the key and return the info
    if (symTable.find(key) == symTable.end())
    {
        return LOOKUP_FAILURE;
    }

    symTable.erase(key);
    return OKAY;
}

int SymTable::getSize(const std::string &key)
{
    // This will return the size of the key
    if (symTable.find(key) == symTable.end())
    {
        return -1;
    }

    return symTable[key].size;
}

int SymTable::getOffset(const std::string &key)
{
    // This will return the offset of the key
    if (symTable.find(key) == symTable.end())
    {
        return -1;
    }

    return symTable[key].offset;
}

bool SymTable::isGlobal(const std::string &key)
{
    // This will return the isGlobal of the key
    if (symTable.find(key) == symTable.end())
    {
        return false;
    }

    return symTable[key].isGlobal;
}

int SymTable::enterFunction(const std::string &funcName)
{
    // This will enter the function and set the offset
    if (inFunction)
    {
        CERR << "Error in entering function - already in function" << std::endl;
        return FAIL;
    }

    // This will set the offset of the function
    stack_offset = activation_start_offset; // This will set the offset of the function
    inFunction = true;
    functionName = funcName;
    return OKAY;
}

int SymTable::exitFunction()
{
    // This will exit the function and set the offset
    if (!inFunction)
    {
        CERR << "Error in exiting function - not in function" << std::endl;
        return FAIL;
    }

    // We also need to create a Symbol with name of function
    SymInfo funcSymbol;
    funcSymbol.size = stack_offset;
    funcSymbol.offset = 0;                              // Function Offset NOT NEEDED IG;
    funcSymbol.isGlobal = true;                         // Function is Global
    int check = this->insert(functionName, funcSymbol); // Insert the function in the table
    if (check != INSERT_SUCCESS)
    {
        CERR << "Error in inserting function at exit - already present" << std::endl;
        return FAIL;
    }

    inFunction = false;
    functionName = "NULL";
    return OKAY;
}

int SymTable::insert(const std::string &key, int size)
{
    // We are only give size
    SymInfo info;
    info.size = size;
    info.offset = stack_offset; // This will set the offset of the function
    info.isGlobal = false;      // Function is Global
    stack_offset += size;       // This will set the offset of the function
    return insert(key, info);
}

void SymTable::printTable(std::ofstream &file)
{
    // Use setw() for formatting - left aligned
    int maxSize = 20;
    int minSize = 10;
    file << "======================[ Symbol Table ]=========================================================================================" << std::endl;
    file << std::left << std::setw(maxSize) << "Name" << std::setw(maxSize) << "Size" << std::setw(maxSize) << "Offset" << std::setw(maxSize) << "isGlobal" << std::endl;
    file << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
    for (auto it : symTable)
    {
        file << std::left << std::setw(maxSize) << it.first << std::setw(maxSize) << it.second.size << std::setw(maxSize) << (it.second.offset) << std::setw(maxSize) << (it.second.isGlobal ? "YES" : "NO") << std::endl;
    }
    file << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
    file << "Total Symbols : " << symTable.size() << std::endl;
    file << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
    return;
}

//======================[ CFG's Liveliness Code ]=========================================================================================

bool CFG::isAlive(int atLine, const std::string &varName)
{
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in isAlive - Block not found" << std::endl;
        return false;
    }
    auto it = blocks[name].livelinessInfo.find(varName);
    if (it == blocks[name].livelinessInfo.end())
    {
        // If variable is not found - then custom logic [add it to the map]
        // If it's Compiler Temp - then notLive
        // Else - a local variable - then live
        CERR << "Var Not Found - Adding New Variable" << std::endl;
        std::pair<bool, std::set<int>> newInfo;

        bool isCompilerTemp = varName[0] == '$';

        newInfo.first = (isCompilerTemp) ? false : true;

        newInfo.second = std::set<int>();
        newInfo.second.insert(atLine);
        blocks[name].livelinessInfo[varName] = newInfo;

    }
    return it->second.first;
}

int CFG::setAlive(int atLine, const std::string &varName)
{
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in setAlive - Block not found" << std::endl;
        return FAIL;
    }

    auto it = blocks[name].livelinessInfo.find(varName);
    if (it == blocks[name].livelinessInfo.end())
    {
        // Variable not found - add the variable
        CERR << "Var " << varName << " Not Found - Adding New Variable" << std::endl;
        std::pair<bool, std::set<int>> newInfo;
        newInfo.first = true;
        newInfo.second = std::set<int>();
        newInfo.second.insert(atLine);
        blocks[name].livelinessInfo[varName] = newInfo;

        return OKAY;
    }

    it->second.first = true;
    return OKAY;
}

int CFG::setDead(int atLine, const std::string &varName)
{
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in setDead - Block not found" << std::endl;
        return FAIL;
    }
    auto it = blocks[name].livelinessInfo.find(varName);
    if (it == blocks[name].livelinessInfo.end())
    {
        // Variable not found - add the variable
        CERR << "Var " << varName << " Not Found - Adding New Variable" << std::endl;
        std::pair<bool, std::set<int>> newInfo;
        newInfo.first = false;
        newInfo.second = std::set<int>();
        newInfo.second.insert(atLine);
        blocks[name].livelinessInfo[varName] = newInfo;


        return OKAY;
    }
    it->second.first = false;
    return OKAY;
}

int CFG::setAllAlive(int atLine)
{
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in setAllAlive - Block not found" << std::endl;
        return FAIL;
    }
    for (auto it : blocks[name].livelinessInfo)
    {
        it.second.first = true;
    }
    return OKAY;
}

int CFG::setAllDead(int atLine)
{
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in setAllDead - Block not found" << std::endl;
        return FAIL;
    }
    for (auto it : blocks[name].livelinessInfo)
    {
        it.second.first = false;
    }
    return OKAY;
}

int CFG::addUsage(int atLine, const std::string &key, int usageLine)
{
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in addUsage - Block not found" << std::endl;
        return FAIL;
    }
    auto it = blocks[name].livelinessInfo.find(key);
    if (it == blocks[name].livelinessInfo.end())
    {
        // Variable not found - add the variable
        CERR << "Var " << key << " Not Found - Adding New Variable" << std::endl;
        std::pair<bool, std::set<int>> newInfo;
        newInfo.first = true;
        newInfo.second = std::set<int>();
        newInfo.second.insert(usageLine);
        blocks[name].livelinessInfo[key] = newInfo;
        return OKAY;
    }
    it->second.second.insert(usageLine);
    return OKAY;
}

int CFG::clearAllUsage(int atLine, const std::string &key)
{
    // This will clear all the usage of the variable
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in clearAllUsage - Block not found" << std::endl;
        return FAIL;
    }

    auto it = blocks[name].livelinessInfo.find(key);
    if (it == blocks[name].livelinessInfo.end())
    {
        // Variable not found - add the variable
        CERR << "Var Not Found - Clear Usage Failed" << std::endl;
        return FAIL;
    }
    it->second.second.clear();
    return OKAY;
}

int CFG::assignmentAt(int atLine, const std::string &key)
{
    // If a variable is assigned at line 
    // Set it as dead & clear all usage
    int check = setDead(atLine, key);
    if (check != OKAY)
    {
        CERR << "Error in assignmentAt - setDead failed" << std::endl;
        return check;
    }
    check = clearAllUsage(atLine, key);
    if (check != OKAY)
    {
        CERR << "Error in assignmentAt - clearAllUsage failed" << std::endl;
        return check;
    }
    // Now we will set the variable as dead
    return OKAY;
}

int CFG::usageAt(int atLine, const std::string &key)
{
    // If a variable is used at line 
    // Set it as alive & add usage
    int check = setAlive(atLine, key);
    if (check != OKAY)
    {
        CERR << "Error in usageAt - setAlive failed" << std::endl;
        return check;
    }
    check = addUsage(atLine, key, atLine);
    if (check != OKAY)
    {
        CERR << "Error in usageAt - addUsage failed" << std::endl;
        return check;
    }
    // Now we will set the variable as alive
    return OKAY;
}

int CFG::resetLiveliness(int atLine)
{
    // Remove all the liveliness info of the block
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in resetLiveliness - Block not found" << std::endl;
        return FAIL;
    }
    blocks[name].livelinessInfo = LivelinessDS();
    return OKAY;
}

int CFG::getAllLivelinessInfo(int atLine, LivelinessDS &info)
{
    // This will get all the liveliness info of the block
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in getAllLivelinessInfo - Block not found" << std::endl;
        return FAIL;
    }
    info = blocks[name].livelinessInfo;
    return OKAY;
}

int CFG::removeLifeInfo(int atLine, const std::string &key)
{
    // This will remove the liveliness info of the variable
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error during removal of var" << key << " - Block not found" << std::endl;
        return FAIL;
    }
    auto it = blocks[name].livelinessInfo.find(key);
    if (it == blocks[name].livelinessInfo.end())
    {
        // Variable not found - add the variable
        // Not needed to remove
        return OKAY;
    }
    blocks[name].livelinessInfo.erase(it);
    return OKAY;
}

int CFG::attachLiveInfoToLine(int atLine){
    // This will attach current liveliness info to the block's ir or that line
    std::string name = blockName(atLine);
    if (blocks.find(name) == blocks.end())
    {
        // Should Not Happen
        CERR << "Error in attachLiveInfoToLine - Block not found" << std::endl;
        return FAIL;
    }
    LivelinessDS info = blocks[name].livelinessInfo;

    // Attach this to irCode of that line
    auto it = blocks[name].irCode.code.find(atLine);
    if(it == blocks[name].irCode.code.end()){
        CERR << "Error in attachLiveInfoToLine - atLine not found" << std::endl;
        return FAIL;
    }
    it->second.VarInfo = info;
    return OKAY;
}


//======================[ SymbTable RegUtilites Code ]=========================================================================================

bool SymTable::isInMemory(const std::string &key)
{
    // This will check if the variable is in memory or not
    if (symTable.find(key) == symTable.end())
    {
        return false;
    }

    return symTable[key].inMemory;
}

int SymTable::setInMemory(const std::string &key)
{
    // This will set the variable as in memory
    if (symTable.find(key) == symTable.end())
    {
        return FAIL;
    }

    symTable[key].inMemory = true;
    return OKAY;
}   

int SymTable::setNotInMemory(const std::string &key)
{
    // This will set the variable as not in memory
    if (symTable.find(key) == symTable.end())
    {
        return FAIL;
    }

    symTable[key].inMemory = false;
    return OKAY;
}


//======================[ CFG's Data Section Code ]=========================================================================================

int getReg(NEW_TAC_Quadruple &code, std::vector<int> &regList){

    return OKAY;
}
