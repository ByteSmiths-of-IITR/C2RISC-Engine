#include "header.h"
#include "utility.h"

//=====================[ Code Generation ]=========================================================================================

SymTable SYM_RECORD; // Global Symbol Table [offset + liveliness + getRegUtilities]

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
    CERR << " | Liveliness Pass completed successfully" << std::endl;

    // Step 3#. Try to visualize the CFG
    std::string dotFileName = "build/cfg.dot";

    check = CFG_CODE.generateDOTFile(dotFileName);

    if (check != OKAY)
    {
        CERR << "Error in generating dot file" << std::endl;
        return check;
    }
    CERR << " | CFG generated successfully at " << dotFileName << std::endl;

    // Step 4. Generate RISC-V code (final Code)
    check = riscvCodeGen();

    if (check != OKAY)
    {
        CERR << "Error in generating RISC-V code" << std::endl;
        return check;
    }
    CERR << " | RISC-V code generated successfully" << std::endl;

    return OKAY;
}

//======================[ Offset Calculation with SymTable ]=========================================================================================

int addSymbolsToSymTable()
{
    // This will add all the symbols to the symbol table
    // We will use the IR_CODE to get the symbols

    // Scan the IR_CODE dataSection
    for (auto it : IR_CODE.dataSection)
    {
        std::string varName = it.first;
        dataSegment obj = it.second;

        int size;
        if (obj.type == dataByte)
        {
            size = 1;
        }
        else if (obj.type == dataHalfByte)
        {
            size = 2;
        }
        else if (obj.type == dataWord)
        {
            size = 4;
        }
        else if (obj.type == dataFloat)
        {
            size = 4;
        }
        else if (obj.type == dataDouble)
        {
            size = 8;
        }
        else if (obj.type == dataString)
        {
            size = obj.value.size();
        }
        else
        {
            CERR << "Error in data section type" << std::endl;
            return FAIL;
        }

        // Add the symbol to the symbol table
        bool space = obj.inAddressSpace; // This will be used to check if the data is in address space or not
        int check = SYM_RECORD.insertGlobal(varName, size, space);
        if (check != INSERT_SUCCESS)
        {
            CERR << "Error in inserting symbol to symbol table" << std::endl;
            return check;
        }
    }

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
            
            bool space = (currIR.arg2 == ADDRESS_VAR) ? true : false; // This will be used to check if the data is in address space or not

            int check = SYM_RECORD.insert(varName, size,space);
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
            else
            {
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

    //
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
            CERR << "FCall Edge " << fromBlock << " -> " << toBlock << std::endl;

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
                    CERR << "FCall Edge " << returnBlock << " -> " << it << std::endl;
                }
            }
            else
            {
                CFG_CODE.addEdge(returnBlock, "EXIT");
                CERR << "FCall Edge " << returnBlock << " -> EXIT" << std::endl;
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
                CFG_CODE.addEdge(fromIndex, toIndex);
            }
        }
    }

    //
    // Handle Return from points of main
    for (auto it : functionReturnFrom["main"])
    {
        CFG_CODE.addEdge(it, "EXIT");
        CERR << "Main Edge " << it << " -> EXIT" << std::endl;
    }

    //

    return OKAY;
}

//=====================[ Live & NextUse + CodeCopy ]=========================================================================================

int livelinessPass()
{
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

        CERR << "Scanning " << i << " - " << op << std::endl;

        if (isNewBlock)
        {
            std::cerr << "New Block's Bottom at " << i << std::endl;
            CFG_CODE.resetLiveliness(i);
        }

        /*
        Step 1. Copy the IR_CODE to CFG_CODE with Liveliness info
        */

        NEW_TAC_Quadruple newTAC(IR_CODE.code[i]); // This copies oldTAC to newTAC
        LivelinessDS info;
        int check = CFG_CODE.getAllLivelinessInfo(i, info);
        if (check != OKAY)
        {
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

        if (op == CALL || op == LEFT_STAR ||
            op == GOTO_EQUAL || op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE)
        {
            // Those in which result is used & not assigned

            if (isASymbol(result))
            {
                // If it's a symbol
                if (CFG_CODE.usageAt(i, result) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for result=" << result << std::endl;
                    return FAIL;
                }
            }
            if (isASymbol(arg1))
            {
                // If it's a symbol
                if (CFG_CODE.usageAt(i, arg1) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for arg1=" << arg1 << std::endl;
                    return FAIL;
                }
            }
            if (isASymbol(arg2))
            {
                // If it's a symbol
                if (CFG_CODE.usageAt(i, arg2) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for arg2=" << arg2 << std::endl;
                    return FAIL;
                }
            }
        }
        else if (op == FUNCTION_ENTRY || op == FUNCTION_EXIT || op == ALLOCATE)
        {
            // Those to be Ignored

            if (op == ALLOCATE)
            {
                std::string varName = result;
                int check = CFG_CODE.removeLifeInfo(i, varName);
                if (check != OKAY)
                {
                    CERR << "Error in removing liveliness info from SYM_TABLE" << std::endl;
                    return check;
                }
            }
        }
        else
        {
            // Normal Operator's Type Operations + Special OP with assignment to result
            // Includes -> ASSIGN_OP, RIGHT_STAR, AMPERSEND, CAST {assignment to result}
            // Include -> PARAM, RETURN_FUNCTION {NO result variable}

            // Special Case of AMPERSEND -> does not use Value of arg1 (just address)

            if (isASymbol(result))
            {
                // If it's a symbol
                if (CFG_CODE.assignmentAt(i, result) != OKAY)
                {
                    CERR << "Error in adding assignment at " << i << "for result=" << result << std::endl;
                    return FAIL;
                }
            }

            if (isASymbol(arg1) && op != AMPERSEND)
            {
                // If it's a symbol

                if (CFG_CODE.usageAt(i, arg1) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for arg1=" << arg1 << std::endl;
                    return FAIL;
                }
            }

            if (isASymbol(arg2))
            {
                // If it's a symbol
                if (CFG_CODE.usageAt(i, arg2) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for arg2=" << arg2 << std::endl;
                    return FAIL;
                }
            }
        }

        // Step 3. Tracking when a new block is starting
        // This will ensure when we are about to enter a new Block
        if (CFG_CODE.isALeader(i))
        {
            // This is a new block
            isNewBlock = true;
        }
        else
        {
            isNewBlock = false;
        }
    }

    // The LiveLinees Tracker will be kept in symbolRecord Itself - as it's a temporary datastructure;
    return OKAY;
}

//=====================[ RISC-V Code Generation ]=========================================================================================

int riscvCodeGen()
{
    // Now we will generate the RISC-V code from the CFG_CODE (block by block in breadth first manner)

    std::queue<std::string> parameterQueue;

    std::queue<std::string> blockOrder;
    std::map<std::string, bool> visitedBlocks;

    bool returnValueViaRegister = true;

    blockOrder.push("ENTRY");
    while (!blockOrder.empty())
    {
        std::string currBlock = blockOrder.front();
        blockOrder.pop();
        if (visitedBlocks.find(currBlock) != visitedBlocks.end())
        {
            continue;
        }
        visitedBlocks[currBlock] = true;

        // Add the Next Blocks in CFG to QUE
        for (auto it : CFG_CODE.edges[currBlock])
        {
            blockOrder.push(it);
        }

        // Now PerBlock Code Generation
        BasicBlock &block = CFG_CODE.blocks[currBlock];
        std::string riscCode;

        // add block label
        if (currBlock == "ENTRY" || currBlock == "EXIT")
        {
            continue;
        }

        // Add Lable
        riscCode = currBlock + ":";
        FINAL_CODE.addCode(riscCode);

        for (auto it : block.irCode.code)
        {
            NEW_TAC_Quadruple &currIR = it.second;

            // Now we have got the IR Code each
            std::string op = currIR.op;

            // Function Entry & Exit [Activation Record]
            if (op == FUNCTION_ENTRY)
            {

                std::string funcName = currIR.result;

                int stackSize = SYM_RECORD.getSize(funcName);

                // Adding Comment
                FINAL_CODE.addComment(" -- ENTRY Activation (start) - " + funcName);

                // Allocate Stack Space
                riscCode = indentOP("addi") + "sp, sp, -" + std::to_string(stackSize);
                FINAL_CODE.addCode(riscCode, "Allocating Stack Space");

                // Store return address for PC
                int loc = stackSize - 4;
                riscCode = indentOP("sw") + "ra, " + std::to_string(loc) + "(sp)";
                FINAL_CODE.addCode(riscCode, "Store return address (PC)");

                // Store old frame pointer
                loc = stackSize - 8;
                riscCode = indentOP("sw") + "fp, " + std::to_string(loc) + "(sp)";
                FINAL_CODE.addCode(riscCode, "Store old frame pointer");

                // Set new frame pointer
                riscCode = indentOP("addi") + "fp, sp," + std::to_string(stackSize);
                FINAL_CODE.addCode(riscCode, "Set new frame pointer");

                // Argument Storing Code will be done by Caller Itself
                // The Callee will assume the arguments are already in place

                // Done
            }
            else if (op == FUNCTION_EXIT)
            {

                // This is a function exit
                std::string funcName = currIR.result;
                FINAL_CODE.addComment(" -- EXIT Activation (start) - " + funcName);

                // At the End of the block, we need to store all the registers into the memory
                FINAL_CODE.addComment("   ~~ At End of Funcion Spilling Code - " + currBlock);
                // We need to store all the variables in the registers -> memory
                for (auto each : SYM_RECORD.regMap)
                {
                    int regNo = each.first;
                    std::set<std::string> vars = each.second;

                    for (auto var : vars)
                    {
                        // We need to store the variable in the memory
                        if (SYM_RECORD.isInMemory(var))
                        {
                            continue; // already in memory
                        }
                        FINAL_CODE.addStoreInst(var, regNo); // store the variable in the memory
                        SYM_RECORD.setInMemory(var); // set the variable in memory
                    }

                    SYM_RECORD.freeGivenReg(regNo); // free this register
                }

                // Finally we reset the SYM_RECORD for this block
                SYM_RECORD.resetRegTable(); // reset the register map

                int stackSize = SYM_RECORD.getSize(funcName);
                std::string riscCode;

                FINAL_CODE.addComment("   ~~ Finished Variable Spilling Code");
                // Comment
                int loc;

                // Decide OnHow to return the value
                if (!returnValueViaRegister)
                {
                    // Store the return value at this address (but will depend on size of return value)
                    // Assuming the return value's address is stored in `a0` (explicit address)
                    int returnSize = std::stoi(currIR.arg1);
                    
                    // Now depending on the size of return we need to call multiple store instructions
                    int destLoc = 0; // w.r.t `a1` register;
                    int srcLoc = 0;  // w.r.t `a0` register;
                    
                    // If return size = -1 // denotes 'void' type
                    // fetch the address where the return value must be stored [in the caller's Stack]
                    int loc = stackSize - 12;
                    riscCode = indentOP("lw") + "a1, " + std::to_string(loc) + "(sp)"; // load value stored at (sp + loc) to a0
                    FINAL_CODE.addCode(riscCode, "Load return value's address from old_sp(-12)");
                    while (returnSize > 0)
                    {
                        // load the data in a temp register

                        int sizeOfData = returnSize > 4 ? 4 : returnSize;

                        std::string sl_type = store_load_Type(sizeOfData);

                        riscCode = indentOP("l" + sl_type) + "a2, " + std::to_string(srcLoc) + "(a0)";
                        FINAL_CODE.addCode(riscCode, "Load return value");

                        // Store the data in the destination
                        riscCode = indentOP("s" + sl_type) + "a2, " + std::to_string(destLoc) + "(a1)";
                        FINAL_CODE.addCode(riscCode, "Store return value");
                        returnSize -= 4;
                        destLoc += 4;
                        srcLoc += 4;
                    }
                }
                else
                {
                    // We return the value via `a0` register, and return statment has set it in register `a5`

                    // We just need to move the value to the destination
                    riscCode = indentOP("mv") + "a0, a5";
                    FINAL_CODE.addCode(riscCode, "Move return value to a0");
                    // Now store the value in the destination
                }
                
                
                // Restore the old return PC
                loc = stackSize - 4;
                riscCode = indentOP("lw") + "ra, " + std::to_string(loc) + "(sp)";
                FINAL_CODE.addCode(riscCode, "Restore return address (PC)");

                // Restore the old frame pointer
                loc = stackSize - 8;
                riscCode = indentOP("lw") + "fp, " + std::to_string(loc) + "(sp)";
                FINAL_CODE.addCode(riscCode, "Restore old frame pointer");

                // Restore the stack pointer
                riscCode = indentOP("addi") + "sp, sp, " + std::to_string(stackSize);
                FINAL_CODE.addCode(riscCode, "Restore stack pointer");

                // Jump to the return address
                riscCode = indentOP("jr") + "ra";
                FINAL_CODE.addCode(riscCode, "Jump to return address(back to caller)");

                FINAL_CODE.addComment(" -- EXIT Activation (end) - " + funcName);

                // Done
            }
            // AssignOP
            else if (op == ASSIGN_OP)
            {
                FINAL_CODE.addComment(" ~~ Assign OP 🟰 - " + currIR.toBaseString());
                // This will store address(explicit address) of return value in `a0` register
                std::string dest = currIR.result;
                std::string src = currIR.arg1;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                // NOW since dest is assigned, we need to update the SYM_RECORD
                SYM_RECORD.variableRest(dest); // update the variable assigned

                std::string destReg = "x" + std::to_string(regMap[dest]);
                // SYM_RECORD.freeGivenReg(regMap[dest]); // free the register (exclusive access)
                SYM_RECORD.addVarInReg(dest, regMap[dest]); // add the variable to the register

                // Special Case src is label
                if (isALabel(src))
                {
                    // src is a label
                    riscCode = indentOP("la") + destReg + ", " + src;
                    FINAL_CODE.addCode(riscCode, "Load address of label - " + src + " into " + destReg);
                }
                else if (!isASymbol(src))
                {
                    // src is a constant
                    riscCode = indentOP("li") + destReg + ", " + src;
                    FINAL_CODE.addCode(riscCode, "Load constant - " + src + " into " + destReg);
                }
                else
                {
                    // src is a variable
                    // NO NEED to create a code, just update DS;
                    FINAL_CODE.addComment(" 🔄 Automatically Assigned - " + src + " into " + dest);
                }
            }
            else if (op == LEFT_STAR)
            {
                FINAL_CODE.addComment(" ~~ Left Star 🌟 - " + currIR.toBaseString());
                // src can't be label -> variable or constant
                // dest can be a label or constant -> only variable

                std::string dest = currIR.result;
                std::string src = currIR.arg1;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                std::string destReg = "x" + std::to_string(regMap[dest]);

                if (!isASymbol(src))
                {
                    // src is a constant

                    // Load the constant in a register (temporary) (t0)
                    riscCode = indentOP("li") + "t0, " + src;
                    FINAL_CODE.addCode(riscCode, "Load constant - " + src + " into t0");

                    int size = std::stoi(currIR.arg2);
                    std::string sl_type = store_load_Type(size);
                    
                    std::string srcReg = "t0";
                    // Load x[srcReg] in address of x[destReg]
                    riscCode = indentOP("s" + sl_type) + srcReg + ", 0(" + destReg + ")";
                    FINAL_CODE.addCode(riscCode, "Store constant of reg " + srcReg + " at address pointed by " + destReg);
                }
                else
                {
                    // src is a variable
                    std::string srcReg = "x" + std::to_string(regMap[src]);

                    int size = std::stoi(currIR.arg2);
                    std::string sl_type = store_load_Type(size);

                    // Load x[srcReg] in address of x[destReg]
                    riscCode = indentOP("s" + sl_type) + srcReg + ", 0(" + destReg + ")";
                    FINAL_CODE.addCode(riscCode , "Store variable of reg " + srcReg + " at address pointed by " + destReg);
                }
            }
            else if (op == RIGHT_STAR)
            {
                FINAL_CODE.addComment(" ~~ Right Star ✨ - " + currIR.toBaseString());
                // src can't be a label or constant -> only variable
                // dest can be a label or constant -> only variable
                std::string dest = currIR.result;
                std::string src = currIR.arg1;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                // Since we are doing assigning, we need to update the SYM_RECORD
                SYM_RECORD.variableRest(dest); // update the variable assigned
                std::string destReg = "x" + std::to_string(regMap[dest]);
                SYM_RECORD.addVarInReg(dest, regMap[dest]); // add the variable to the register

                std::string srcReg = "x" + std::to_string(regMap[src]);

                // Write a load instruction
                // std::cout << "stoi on " << currIR.arg2 << std::endl;
                // std::cout << "code - " << currIR.toString() << std::endl;
                int size = std::stoi(currIR.arg2);
                std::string sl_type = store_load_Type(size);

                // Load x[srcReg] in address of x[destReg]
                riscCode = indentOP("l" + sl_type) + destReg + ", 0(" + srcReg + ")";
                FINAL_CODE.addCode(riscCode, "Load reg " + srcReg + " with value at address pointed by " + destReg);

                // SYM_RECORD already updated
            }
            else if (op == AMPERSEND)
            {
                FINAL_CODE.addComment(" ~~  Ampersend (&) - " + currIR.toBaseString());
                std::string dest = currIR.result;
                std::string src = currIR.arg1;
                // src can't be constant -> variable or label
                // dest can be a label or constant -> only variable

                bool isLabel = isALabel(src);
                bool isGlobal = SYM_RECORD.isGlobal(src);

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                std::string destReg = "x" + std::to_string(regMap[dest]);
                if (isLabel || isGlobal)
                {
                    // src is a label or global variable

                    // Load the address of the label in a register (temporary) (t0)
                    riscCode = indentOP("la") + destReg + ", " + src; // la destReg, src(label)
                    FINAL_CODE.addCode(riscCode, "Load address of label - " + src + " into " + destReg);
                }
                else
                {
                    // src is a variable (local)

                    int offset_src = SYM_RECORD.getOffset(src);
                    std::string imm = "-" + std::to_string(offset_src); // Negative offset
                    // Store this offset (w.r.t fp(frame pointer)) in destReg
                    riscCode = indentOP("addi") + destReg + ", fp, " + imm;
                    FINAL_CODE.addCode(riscCode , "Load address of variable (via fp) - " + src + " into " + destReg);
                }
            }

            // Cast Operations
            else if (op == CAST)
            {
            }

            // Param + Function Call + Return
            else if (op == PARAM)
            {

                // Only one argument
                std::string funcArg = currIR.arg1;
                
                // We need to push the argument in the queue
                parameterQueue.push(funcArg); // Rest will be done by `CALL` instruction
                FINAL_CODE.addComment("Adding " + funcArg + " to parameter queue");

                // NO Code Generation
            }
            else if (op == CALL)
            {

                int noOfArg = std::stoi(currIR.arg2);
                std::string result = currIR.result;
                std::string funcName = currIR.arg1;

                // Find all the required params;
                std::vector<std::string> args;
                std::set<std::string> usedVars;

                bool isFunctionALabel = isALabel(funcName);

                if(!isFunctionALabel){
                    // We are calling a variable (func Pointer) - we would need to find it's value
                    usedVars.insert(funcName); 
                }

                for (int i = 0; i < noOfArg; i++)
                {
                    if (parameterQueue.empty())
                    {
                        CERR << "Error - Not enough parameters in queue" << std::endl;
                        return FAIL;
                    }
                    std::string arg = parameterQueue.front();
                    parameterQueue.pop();
                    args.push_back(arg);
                    usedVars.insert(arg);
                }

                LivelinessDS info = currIR.VarInfo; // Copy the liveliness info
                
                // NOW we would NEED to send all these arguments to the calle function's Stack
                for (int i = 0; i < noOfArg;i++){

                    // Now we need to store this register's value at the address of the caller's stack
                    int offset = SYM_RECORD.getOffset(args[i]);
                    int size = SYM_RECORD.getSize(args[i]);

                    

                }
            }
            else if (op == RETURN_FUNCTION)
            {

                // This will store address(explicit address) of return value in `a0` register
            }

            // Jump Operations
            else if (op == GOTO_EQUAL)
            {
            }
            else if (op == GOTO_LABEL)
            {
            }
            else if (op == IF_TRUE)
            {
            }
            else if (op == IF_FALSE)
            {
            }

            // Instruction to Ignore
            else if (op == ALLOCATE)
            {
                // TO Ignore
            }

            // Other Operation Based Insturctions
            else
            {
            }
        }

        // At the End of the block, we need to store all the registers into the memory
        FINAL_CODE.addComment(" ~~ At End of Block Variable Spilling - " + currBlock);
        // We need to store all the variables in the registers -> memory
        for (auto each : SYM_RECORD.regMap)
        {
            int regNo = each.first;
            std::set<std::string> vars = each.second;

            for (auto var : vars)
            {
                // We need to store the variable in the memory
                if (SYM_RECORD.isInMemory(var))
                {
                    continue; // already in memory
                }
                FINAL_CODE.addStoreInst(var, regNo); // store the variable in the memory
                SYM_RECORD.setInMemory(var); // set the variable in memory
            }

            SYM_RECORD.freeGivenReg(regNo); // free this register
        }

        // Finally we reset the SYM_RECORD for this block
        SYM_RECORD.resetRegTable(); // reset the register map

        FINAL_CODE.addComment(" ~~ Finished Spilling Variable at end of block ");
    }

    return OKAY;
}

//======================[ Register Allocation ]=========================================================================================

// Variour Possible Cases of getReg()
/*
1 - 1 assign + 2 usage
2 - 1 assign + 1 usage
3 - 1 assign + 0 usage [can be possible with `li`]
4 - 0 assign + 2 usage
5 - 0 assign + 1 usage
6 - 0 assign + 0 usage [ cases of using only constants ]
*/

int getReg(NEW_TAC_Quadruple &code, std::map<std::string, int> &regMap)
{

    // int lineNo = code.lineNo;

    std::string op = code.op;
    std::vector<std::string> usageType;
    std::vector<std::string> assignmentType;

    std::string result = code.result;
    std::string arg1 = code.arg1;
    std::string arg2 = code.arg2;

    // Step 1. Dividing things into usage & assignment Type
    if (op == CALL || op == LEFT_STAR ||
        op == GOTO_EQUAL || op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE)
    {
        // Those in which result is used & not assigned

        if (isASymbol(result))
        {
            usageType.push_back(result);
        }
        if (isASymbol(arg1))
        {
            usageType.push_back(arg1);
        }
        if (isASymbol(arg2))
        {
            usageType.push_back(arg2);
        }
    }
    else if (op == FUNCTION_ENTRY || op == FUNCTION_EXIT || op == ALLOCATE)
    {
        // Those to be Ignored
    }
    else
    {
        // Normal Operator's Type Operations + Special OP with assignment to result
        // Includes -> ASSIGN_OP, RIGHT_STAR, AMPERSEND, CAST {assignment to result}
        // Include -> PARAM, RETURN_FUNCTION {NO result variable}

        if (isASymbol(result))
        {
            assignmentType.push_back(result);
        }

        if (isASymbol(arg1))
        {
            usageType.push_back(arg1);
        }

        if (isASymbol(arg2))
        {
            usageType.push_back(arg2);
        }
    }

    std::string usageVar1 = (usageType.size() > 0) ? usageType[0] : "NULL";
    std::string usageVar2 = (usageType.size() > 1) ? usageType[1] : "NULL";

    std::string assignVar = (assignmentType.size() > 0) ? assignmentType[0] : "NULL";

    if (usageType.size() > 2)
    {
        CERR << "Error - More than 2 usage variables" << std::endl;
        return FAIL;
    }
    if (assignmentType.size() > 1)
    {
        CERR << "Error - More than 1 assignment variables" << std::endl;
        return FAIL;
    }

    // Function Entry & Exit [Activation Record]
    if (op == FUNCTION_ENTRY || op == ALLOCATE || op == RETURN_FUNCTION)
    {
        // Would never call getReg()
    }

    // Cast Operations
    else if (op == CAST)
    {
    }

    else
    {
        /* Included Here
        - Simple Operations
        - all jump operations
        - function call, param, return
        - left-star, right-star, ampersand
        - assign op
        */

        // Special Case Handling
        if (op == AMPERSEND)
        {
            usageVar1 = "NULL"; // since it would be loaded from memory
        }

        std::set<int> justUsedReg;
        if (usageVar1 != "NULL")
        {
            std::string usageVar = usageVar1;
            std::string otherUsageVar = usageVar2;

            int presentIn = SYM_RECORD.varStoredInWhichReg(usageVar);
            if (presentIn != -1)
            {
                // This is already in register
                regMap[usageVar] = presentIn;
                justUsedReg.insert(presentIn);
            }
            else
            {
                // Not present in any register
                int anyFree = SYM_RECORD.getFreeReg();
                if (anyFree != -1)
                {
                    // Give this register to the variable
                    regMap[usageVar] = anyFree;
                    justUsedReg.insert(anyFree);

                    // Update the SYM_RECORD
                    SYM_RECORD.addVarInReg(usageVar, anyFree);

                    // Generate Load Instruction
                    FINAL_CODE.addLoadInst(usageVar, anyFree);
                }
                else
                {
                    // No free register exits
                    int bestScore = INT_MAX;
                    int bestReg = -1;
                    for (auto it : SYM_RECORD.regMap)
                    {

                        int chosenReg = it.first;

                        if (justUsedReg.find(chosenReg) != justUsedReg.end())
                        {
                            // This is already used
                            continue;
                        }

                        std::set<std::string> storeVars = it.second;

                        // Find score over all the variables
                        int score = 0;
                        for (auto v : storeVars)
                        {
                            int isPresentInMem = SYM_RECORD.isInMemory(v);
                            bool noNextUsage = (code.isAlive(v) == false);

                            if (isPresentInMem == true || assignVar == v || noNextUsage)
                            {
                                // Nothing to do
                            }
                            else
                            {
                                // Else, we need to spill this variable
                                score++;
                            }
                        }

                        if (score < bestScore)
                        {
                            bestScore = score;
                            bestReg = chosenReg;
                        }
                    }

                    // Now we have the best register
                    if (bestReg == -1)
                    {
                        CERR << "Error in finding best register" << std::endl;
                        return FAIL;
                    }

                    // Let's Spill the variables in the bestReg
                    std::set<std::string> storeVars = SYM_RECORD.regMap[bestReg];
                    for (auto v : storeVars)
                    {
                        int isPresentSomeWhereElse = SYM_RECORD.isInMemory(v);
                        isPresentSomeWhereElse = isPresentSomeWhereElse || (SYM_RECORD.varStoreInHowManyReg(v) > 1);

                        if (isPresentSomeWhereElse == false)
                        {
                            // This is not in memory, so we need to store it

                            // We would need a store instruction
                            FINAL_CODE.addStoreInst(v, bestReg);

                            SYM_RECORD.setInMemory(v);
                        }
                        else
                        {
                            // Okay is present somewhere else
                        }

                        // Update the SYM_RECORD
                        SYM_RECORD.removeVarFromReg(v, bestReg);
                    }
                    SYM_RECORD.freeGivenReg(bestReg); // free the register (exclusive access)

                    // Now we can use this register
                    bool justChecking = SYM_RECORD.isFree(bestReg);
                    if (justChecking == false)
                    {
                        CERR << "Error - Register is still held by someone else" << std::endl;
                        return FAIL;
                    }

                    regMap[usageVar] = bestReg;
                    justUsedReg.insert(bestReg);

                    SYM_RECORD.addVarInReg(usageVar, bestReg);
                    // Generate Load Instruction
                    FINAL_CODE.addLoadInst(usageVar, bestReg);
                    // Now we can use this register
                }
            }
        }

        if (usageVar2 != "NULL")
        {
            std::string usageVar = usageVar2;
            std::string otherUsageVar = usageVar1;

            int presentIn = SYM_RECORD.varStoredInWhichReg(usageVar);
            if (presentIn != -1)
            {
                // This is already in register
                regMap[usageVar] = presentIn;
                justUsedReg.insert(presentIn);
            }
            else
            {
                // Not present in any register
                int anyFree = SYM_RECORD.getFreeReg();
                if (anyFree != -1)
                {
                    // Give this register to the variable
                    regMap[usageVar] = anyFree;
                    justUsedReg.insert(anyFree);

                    // Update the SYM_RECORD
                    SYM_RECORD.addVarInReg(usageVar, anyFree);

                    // Generate Load Instruction
                    FINAL_CODE.addLoadInst(usageVar, anyFree);
                }
                else
                {
                    // No free register exits
                    int bestScore = INT_MAX;
                    int bestReg = -1;
                    for (auto it : SYM_RECORD.regMap)
                    {

                        int chosenReg = it.first;

                        if (justUsedReg.find(chosenReg) != justUsedReg.end())
                        {
                            // This is already used
                            continue;
                        }

                        std::set<std::string> storeVars = it.second;

                        // Find score over all the variables
                        int score = 0;
                        for (auto v : storeVars)
                        {
                            int isPresentInMem = SYM_RECORD.isInMemory(v);
                            bool noNextUsage = (code.isAlive(v) == false);

                            if (isPresentInMem == true || assignVar == v || noNextUsage)
                            {
                                // Nothing to do
                            }
                            else
                            {
                                // Else, we need to spill this variable
                                score++;
                            }
                        }

                        if (score < bestScore)
                        {
                            bestScore = score;
                            bestReg = chosenReg;
                        }
                    }

                    // Now we have the best register
                    if (bestReg == -1)
                    {
                        CERR << "Error in finding best register" << std::endl;
                        return FAIL;
                    }

                    // Let's Spill the variables in the bestReg
                    std::set<std::string> storeVars = SYM_RECORD.regMap[bestReg];
                    for (auto v : storeVars)
                    {
                        int isPresentSomeWhereElse = SYM_RECORD.isInMemory(v);
                        isPresentSomeWhereElse = isPresentSomeWhereElse || (SYM_RECORD.varStoreInHowManyReg(v) > 1);

                        if (isPresentSomeWhereElse == false)
                        {
                            // This is not in memory, so we need to store it

                            // We would need a store instruction
                            FINAL_CODE.addStoreInst(v, bestReg);

                            SYM_RECORD.setInMemory(v);
                        }
                        else
                        {
                            // Okay is present somewhere else
                        }

                        // Update the SYM_RECORD
                        SYM_RECORD.removeVarFromReg(v, bestReg);
                    }
                    SYM_RECORD.freeGivenReg(bestReg); // free the register (exclusive access)

                    // Now we can use this register
                    bool justChecking = SYM_RECORD.isFree(bestReg);
                    if (justChecking == false)
                    {
                        CERR << "Error - Register is still held by someone else" << std::endl;
                        return FAIL;
                    }

                    regMap[usageVar] = bestReg;
                    justUsedReg.insert(bestReg);

                    SYM_RECORD.addVarInReg(usageVar, bestReg);
                    // Generate Load Instruction
                    FINAL_CODE.addLoadInst(usageVar, bestReg);
                
                    // Now we can use this register
                }
            }
        
        }

        if (assignVar != "NULL")
        {

            if (op == ASSIGN_OP && usageVar1 != "NULL")
            {
                regMap[assignVar] = regMap[usageVar1];
                justUsedReg.insert(regMap[usageVar1]);
            }
            else
            {
                // This is the assignment variable
                int presentIn = SYM_RECORD.ex_varStoredInWhichReg(assignVar);
                if (presentIn != -1)
                {
                    // We have got our register
                    regMap[assignVar] = presentIn;
                    justUsedReg.insert(presentIn);
                }
                else
                {
                    // Check if usageVar1 has No next use and the assigned Register to it only holds usageVar1
                    bool noNextUse_1 = (usageVar1 != "NULL") && (code.isAlive(usageVar1) == false);
                    int givenReg_1 = regMap[usageVar1];
                    bool exclusivelyUsed_1 = (SYM_RECORD.regMap[givenReg_1].size() == 1);

                    bool noNextUse_2 = (usageVar2 != "NULL") && (code.isAlive(usageVar2) == false);
                    int givenReg_2 = regMap[usageVar2];
                    bool exclusivelyUsed_2 = (SYM_RECORD.regMap[givenReg_2].size() == 1);

                    if (noNextUse_1 && exclusivelyUsed_1)
                    {
                        // We can use this register
                        regMap[assignVar] = givenReg_1;
                        justUsedReg.insert(givenReg_1);
                    }
                    else if (noNextUse_2 && exclusivelyUsed_2)
                    {
                        // We can use this register
                        regMap[assignVar] = givenReg_2;
                        justUsedReg.insert(givenReg_2);
                    }
                    else
                    {
                        // Look for a free register
                        int anyFree = SYM_RECORD.getFreeReg();
                        if (anyFree != -1)
                        {
                            // Give this register to the variable
                            regMap[assignVar] = anyFree;
                            justUsedReg.insert(anyFree);

                            // SYM_TABLE will be updated later by codeGen
                        }
                        else
                        {
                            // No free register exits
                            int bestScore = INT_MAX;
                            int bestReg = -1;
                            for (auto it : SYM_RECORD.regMap)
                            {

                                int chosenReg = it.first;

                                if (justUsedReg.find(chosenReg) != justUsedReg.end())
                                {
                                    // This is already used
                                    continue;
                                }

                                std::set<std::string> storeVars = it.second;
                                // Find score over all the variables
                                int score = 0;
                                for (auto v : storeVars)
                                {
                                    int isPresentInMem = SYM_RECORD.isInMemory(v);
                                    bool noNextUsage = (code.isAlive(v) == false);

                                    if (isPresentInMem == true || noNextUsage)
                                    {
                                        // Nothing to do
                                    }
                                    else
                                    {
                                        // Else, we need to spill this variable
                                        score++;
                                    }
                                }

                                if (score < bestScore)
                                {
                                    bestScore = score;
                                    bestReg = chosenReg;
                                }
                            }

                            // Now we have the best register
                            if (bestReg == -1)
                            {
                                CERR << "Error in finding best register" << std::endl;
                                return FAIL;
                            }

                            // Let's Spill the variables in the bestReg
                            std::set<std::string> storeVars = SYM_RECORD.regMap[bestReg];
                            for (auto v : storeVars)
                            {
                                int isPresentSomeWhereElse = SYM_RECORD.isInMemory(v);
                                isPresentSomeWhereElse = isPresentSomeWhereElse || (SYM_RECORD.varStoreInHowManyReg(v) > 1);

                                if (isPresentSomeWhereElse == false)
                                {
                                    // This is not in memory, so we need to store it

                                    // We would need a store instruction
                                    FINAL_CODE.addStoreInst(v, bestReg); // store the variable in the memory
                                    

                                    SYM_RECORD.setInMemory(v);
                                }
                                else
                                {
                                    // Okay is present somewhere else
                                }

                                // Update the SYM_RECORD
                                SYM_RECORD.removeVarFromReg(v, bestReg);
                            }
                            SYM_RECORD.freeGivenReg(bestReg); // free the register (exclusive access)

                            // Now we can use this register
                            bool justChecking = SYM_RECORD.isFree(bestReg);
                            if (justChecking == false)
                            {
                                CERR << "Error - Register is still held by someone else" << std::endl;
                                return FAIL;
                            }

                            regMap[assignVar] = bestReg;
                            justUsedReg.insert(bestReg);
                            // Now we can use this register
                        }
                    }
                }
            }
        }
    }

    // At the End of GetReg,
    std::string getRegResult = "";
    getRegResult += " 🙋🏼 GetReg() for " + code.toBaseString();
    for (auto it : regMap)
    {
        std::string varName = it.first;
        int regNo = it.second;

        // We need to update the SYM_RECORD
        getRegResult += " | 🤝 `x" + std::to_string(regNo) + "` reg ➜ " + varName;
    }
    getRegResult += " |";

    FINAL_CODE.addComment(getRegResult);

    return OKAY;
}

int getManyReg(std::set<std::string> varNames, LivelinessDS liveInfo, std::map<std::string, int> &regMap)
{
    // All the variable will be of usageType

    // We have a set of variables - Even if multiple variables are used in the same line - there won't be any issue

    std::set<int> justUsedReg;

    for(auto usageVar : varNames){

        int presentIn = SYM_RECORD.varStoredInWhichReg(usageVar);
        if (presentIn != -1)
        {
            // This is already in register
            regMap[usageVar] = presentIn;
            justUsedReg.insert(presentIn);
        }
        else
        {
            // Not present in any register
            int anyFree = SYM_RECORD.getFreeReg();
            if (anyFree != -1)
            {
                // Give this register to the variable
                regMap[usageVar] = anyFree;
                justUsedReg.insert(anyFree);

                // Update the SYM_RECORD
                SYM_RECORD.addVarInReg(usageVar, anyFree);

                // Generate Load Instruction
                FINAL_CODE.addLoadInst(usageVar, anyFree);
            }
            else
            {
                // No free register exits
                int bestScore = INT_MAX;
                int bestReg = -1;
                for (auto it : SYM_RECORD.regMap)
                {

                    int chosenReg = it.first;

                    if (justUsedReg.find(chosenReg) != justUsedReg.end())
                    {
                        // This is already used
                        continue;
                    }

                    std::set<std::string> storeVars = it.second;

                    // Find score over all the variables
                    int score = 0;
                    for (auto v : storeVars)
                    {
                        int isPresentInMem = SYM_RECORD.isInMemory(v);
                        bool isLive = liveInfo[v].first;
                        bool noNextUsage = (isLive == false);

                        if (isPresentInMem == true|| noNextUsage)
                        {
                            // Nothing to do
                        }
                        else
                        {
                            // Else, we need to spill this variable
                            score++;
                        }
                    }

                    if (score < bestScore)
                    {
                        bestScore = score;
                        bestReg = chosenReg;
                    }
                }

                // Now we have the best register
                if (bestReg == -1)
                {
                    CERR << "Error in finding best register" << std::endl;
                    return FAIL;
                }

                // Let's Spill the variables in the bestReg
                std::set<std::string> storeVars = SYM_RECORD.regMap[bestReg];
                for (auto v : storeVars)
                {
                    int isPresentSomeWhereElse = SYM_RECORD.isInMemory(v);
                    isPresentSomeWhereElse = isPresentSomeWhereElse || (SYM_RECORD.varStoreInHowManyReg(v) > 1);

                    if (isPresentSomeWhereElse == false)
                    {
                        // This is not in memory, so we need to store it

                        // We would need a store instruction
                        FINAL_CODE.addStoreInst(v, bestReg);

                        SYM_RECORD.setInMemory(v);
                    }
                    else
                    {
                        // Okay is present somewhere else
                    }

                    // Update the SYM_RECORD
                    SYM_RECORD.removeVarFromReg(v, bestReg);
                }
                SYM_RECORD.freeGivenReg(bestReg); // free the register (exclusive access)

                // Now we can use this register
                bool justChecking = SYM_RECORD.isFree(bestReg);
                if (justChecking == false)
                {
                    CERR << "Error - Register is still held by someone else" << std::endl;
                    return FAIL;
                }

                regMap[usageVar] = bestReg;
                justUsedReg.insert(bestReg);

                SYM_RECORD.addVarInReg(usageVar, bestReg);
                // Generate Load Instruction
                FINAL_CODE.addLoadInst(usageVar, bestReg);

                // Now we can use this register
            }
        }
    }


    // At the End of GetReg,
    std::string getRegResult = "";
    getRegResult += " 🙋🏼‍♀️ GetManyReg() for multiple variables";
    for (auto it : regMap)
    {
        std::string varName = it.first;
        int regNo = it.second;

        // We need to update the SYM_RECORD
        getRegResult += " | 🤝 `x" + std::to_string(regNo) + "` reg ➜ " + varName;
    }

    getRegResult += " |";
    FINAL_CODE.addComment(getRegResult);

    return OKAY;
}

//======================[ RISC-V Code Generation Utilities ]=========================================================================================


void RISCV_CODE::addCopyInst(std::string variable, int size, int srcImm, std::string src_wrtReg, int destImm, std::string dest_wrtReg){
    // We will be copying the variable (srcImm + src_wrtReg) to (destImm + dest_wrtReg) with size


}

void RISCV_CODE::addLoadInst(const std::string &varName, int regNo)
{
    // Write Code to Load This Variable from Memory

    std::string riscCode;
    int sizeOfVar = SYM_RECORD.getSize(varName);

    std::string sl_type = store_load_Type(sizeOfVar);

    // The Variable to Store in global we don't have it's offset first we need to load the address of the variable
    bool isGlobal = SYM_RECORD.isGlobal(varName);

    bool inAddrSpace = SYM_RECORD.isInAddressSpace(varName);

    if(inAddrSpace){
        if(isGlobal){
            
            // We need to load the address of this Global Variable in the given register
            std::string addrReg = "x" + std::to_string(regNo);
            riscCode = indentOP("la") + addrReg + ", " + varName;
            this->addCode(riscCode, "Loading Address of Global Variable(address Space) - " + varName + " in x" + std::to_string(regNo));
            }
        else{
            // Else it's a local variable - we need its offset
            int loc = SYM_RECORD.getOffset(varName); // [This Offset is w.r.t fp]
            riscCode = indentOP("addi") + "x" + std::to_string(regNo) + ", fp, -" + std::to_string(loc); // w.r.t frame pointer(fp)
            this->addCode(riscCode, "Loading Offset of Local Variable(address Space) - " + varName + " in x" + std::to_string(regNo));
        }
    }
    else{
        if (isGlobal)
        {
            // We need to load the address of the variable in a register
            std::string addrReg = "t0";
            riscCode = indentOP("la") + addrReg + ", " + varName;
            this->addCode(riscCode, "Loading Address of Global Variable - " + varName);

            // Now we can store the value in the memory
            riscCode = indentOP("l" + sl_type) + "x" + std::to_string(regNo) + ", 0(" + addrReg + ")";
            this->addCode(riscCode, "Load Global Var - " + varName + " via " + addrReg + " in x" + std::to_string(regNo));
        }
        else
        {
            // Else it's a local variable - we need its offset
            int loc = SYM_RECORD.getOffset(varName);                                                                 // [This Offset is w.r.t fp]
            riscCode = indentOP("l" + sl_type) + "x" + std::to_string(regNo) + ", -" + std::to_string(loc) + "(fp)"; // w.r.t frame pointer(fp)
            this->addCode(riscCode, "Load Local Var - " + varName + " via fp in x" + std::to_string(regNo));
        }
    }
    return;
}

void RISCV_CODE::addStoreInst(const std::string &varName, int regNo)
{
    // Write Code to Store This Variable in Memory

    std::string riscCode;
    int sizeOfVar = SYM_RECORD.getSize(varName);
    
    std::string sl_type = store_load_Type(sizeOfVar);

    // The Variable to Store in global we don't have it's offset first we need to load the address of the variable
    bool isGlobal = SYM_RECORD.isGlobal(varName);
    
    if(isGlobal){
        // We need to load the address of the variable in a register
        std::string addrReg = "t0";
        riscCode = indentOP("la") + addrReg + ", " + varName;
        this->addCode(riscCode, "Loading Address of Global Variable - " + varName);

        // Now we can store the value in the memory
        riscCode = indentOP("s" + sl_type) + "x" + std::to_string(regNo) + ", 0(" + addrReg + ")";
        this->addCode(riscCode, "Store Global Var - " + varName + " via " + addrReg + " in x" + std::to_string(regNo));
    }
    else{
        // Else it's a local variable - we need its offset
        int loc = SYM_RECORD.getOffset(varName); // [This Offset is w.r.t fp]
        riscCode = indentOP("s" + sl_type) + "x" + std::to_string(regNo) + ", -" + std::to_string(loc) + "(fp)"; // w.r.t frame pointer(fp)
        this->addCode(riscCode, "Store Local Var - " + varName + " via fp in x" + std::to_string(regNo));
    }

    return;
}

std::string store_load_Type(int size){
    // This will return the type of store/load instruction
    std::string sl_type;
    if (size == 1)
    {
        sl_type = "b";
    }
    else if (size == 2)
    {
        sl_type = "h";
    }
    else if(size == 4)
    {
        sl_type = "w";
    }
    else if(size == 8)
    {
        sl_type = "d";
    }
    else{
        CERR << "Error - Invalid Size for Store/Load Instruction" << std::endl;
        sl_type = "- WRONG -";
    }
    
    return sl_type;
}