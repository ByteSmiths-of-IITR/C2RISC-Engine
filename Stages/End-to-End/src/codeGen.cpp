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

//======================[ Offset Calculation with SymTable ]=========================================================================================

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

//=====================[ Make Basic Blocks]=========================================================================================

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

int getReg(NEW_TAC_Quadruple &code, std::vector<int> &regList){

    return OKAY;
}
