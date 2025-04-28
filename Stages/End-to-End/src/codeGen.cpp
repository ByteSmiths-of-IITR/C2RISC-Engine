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
    // CERR << " | Symbol Table generated successfully at output/symRecord.txt" << std::endl;

    // Step 2. Identify basic blocks & control flow -> CFG Link Formed
    check = makeBasicBlocks();
    if (check != OKAY)
    {
        CERR << "Error in making basic blocks" << std::endl;
        return check;
    }

    // Step 3. Liveliness Analysis + CodeTransfer from IR_CODE to CFG_CODE
    check = livelinessPass();
    if (check != OKAY)
    {
        CERR << "Error in liveliness pass" << std::endl;
        return check;
    }
    CERR << " | Liveliness Pass completed successfully" << std::endl;

    // Step 3#. Try to visualize the CFG after CODE Transfer
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

    // Add the variable from dataSection to CFG_CODE
    for (auto it : IR_CODE.dataSection)
    {
        std::string varName = it.first;
        dataSegment obj = it.second;

        int size;
        std::string type = obj.type;
        if (type == dataByte)
        {
            size = 1;
        }
        else if (type == dataHalfByte)
        {
            size = 2;
        }
        else if (type == dataWord)
        {
            size = 4;
        }
        else if (type == dataFloat)
        {
            size = 4;
        }
        else if (type == dataDouble)
        {
            size = 8;
        }
        else if (type == dataString)
        {
            size = obj.value.size();
        }
        else if (type == dataZero)
        {
            size = std::stoi(obj.value);
        }
        else
        {
            CERR << "Error in data section type" << std::endl;
            return FAIL;
        }

        bool isF = (type == dataFloat || type == dataDouble) ? true : false; // This will be used to check if the data is float or not

        SYM_RECORD.insertGlobal(varName, size, isF);
    }

    for (size_t i = 0; i < IR_CODE.code.size(); i++)
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

            bool isF = (currIR.arg2 == "YES") ? true : false; // This will be used to check if the data is float or not

            // bool space = (currIR.arg2 == ADDRESS_VAR) ? true : false; // This will be used to check if the data is in address space or not
            int check = SYM_RECORD.insert(varName, size, isF);
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

    // All those instruction with operation GOTO_LABEL, IF_TRUE, IF_FALSE, FUNCTION_ENTRY, GOTO_EQUAL

    // Assign Name to each Block & Fill indexToBlockMap
    for (size_t i = 0; i < IR_CODE.code.size(); i++)
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
        if (op == GOTO_EQUAL || op == IF_FALSE || op == IF_TRUE /* Call is Not Leader AnyMore || op == CALL*/ || op == GOTO_LABEL)
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

    // // Checking Leaders [DEBUG]
    // CERR << "Leaders : ";
    // for (size_t i = 0; i < CFG_CODE.leaders.size(); i++)
    // {
    //     std::cerr  << CFG_CODE.leaders[i] << " ";
    // }
    // CERR << std::endl;

    // Step 2. Change Lables in jump instructions

    // Change jump (lineNo) -> (block labels)
    for (size_t i = 0; i < IR_CODE.code.size(); i++)
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

    std::string firstBlock = CFG_CODE.blockName(0);
    CFG_CODE.addEdge("ENTRY", firstBlock);

    std::string lastBlock = CFG_CODE.blockName(IR_CODE.code.size() - 1);
    CFG_CODE.addEdge(lastBlock, "EXIT");

    /* [TURNED OFF] -> Function call's as block
    // ------ Considering Function Calls to be a Block End
        // Return From Points in Functions [Needed for Function Control Flow Connections]
        std::map<std::string, std::vector<std::string>> functionReturnFrom;
        std::string currFunction = "NULL";
        for (size_t i = 0; i < IR_CODE.code.size(); i++)
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
    // ------
    */

    //
    // Now we will add edges to all the blocks
    for (size_t i = 0; i < IR_CODE.code.size(); i++)
    {
        std::string op = IR_CODE.code[i].op;
        if (op == IF_FALSE || op == IF_TRUE || op == GOTO_LABEL || op == GOTO_EQUAL)
        {
            std::string fromBlock = CFG_CODE.blockName(i);

            std::string toBlock = IR_CODE.code[i].result;
            CFG_CODE.addEdge(fromBlock, toBlock);
        }
        /* - TURNED OFF -> Function call's as block
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
        */
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

    /* [TURNED OFF] -> Function call's as block
        // Handle Return from points of main
        for (auto it : functionReturnFrom["main"])
        {
            CFG_CODE.addEdge(it, "EXIT");
            CERR << "Main Edge " << it << " -> EXIT" << std::endl;
        }
    */

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

        // CERR << "Scanning " << i << " - " << op << std::endl;

        if (isNewBlock)
        {
            CERR << "New Block's Bottom at " << i << std::endl;
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

            if (isAValueSymbol(result))
            {
                // If it's a symbol
                if (CFG_CODE.usageAt(i, result) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for result=" << result << std::endl;
                    return FAIL;
                }
            }
            if (isAValueSymbol(arg1))
            {
                // If it's a symbol
                if (CFG_CODE.usageAt(i, arg1) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for arg1=" << arg1 << std::endl;
                    return FAIL;
                }
            }
            if (isAValueSymbol(arg2))
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

            if (isAValueSymbol(result))
            {
                // If it's a symbol
                if (CFG_CODE.assignmentAt(i, result) != OKAY)
                {
                    CERR << "Error in adding assignment at " << i << "for result=" << result << std::endl;
                    return FAIL;
                }
            }

            if (isAValueSymbol(arg1) && op != AMPERSEND)
            {
                // If it's a symbol

                if (CFG_CODE.usageAt(i, arg1) != OKAY)
                {
                    CERR << "Error in adding usage at " << i << "for arg1=" << arg1 << std::endl;
                    return FAIL;
                }
            }

            if (isAValueSymbol(arg2))
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

    // Copying the Data Section from IR_CODE to FINAL_CODE
    FINAL_CODE.addDataSection(IR_CODE.dataSection);

    std::stack<std::string> parameterStack;

    std::queue<std::string> blockOrder;
    std::map<std::string, bool> visitedBlocks;

    bool returnValueViaRegister = true; //[FOR Simple Things - OKAY]

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

        // Ignore Entry & Exit Blocks
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
                FINAL_CODE.addComment(" ~TAC~ ➔ ENTRY (start) - " + funcName);

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

                //-- Spilling Code
                spillingCode();

                int stackSize = SYM_RECORD.getSize(funcName);
                std::string riscCode;
                int loc;

                // Return value was Stored in a1

                // --- Return Value Code
                // Decide OnHow to return the value
                if (!returnValueViaRegister)
                {
                    // Store the return value at this address (but will depend on size of return value)
                    // Assuming the return value's address is stored in `a0` (explicit address)
                    int returnSize = std::stoi(currIR.arg1);

                    // Now depending on the size of return we need to call multiple store instructions
                    int destImm = 0; // w.r.t `a1` register;
                    int srcImm = 0;  // w.r.t `a0` register;
                    std::string srcReg = "t1", destReg = "t2";

                    // If return size = -1 // denotes 'void' type
                    // fetch the address where the return value must be stored [in the caller's Stack]
                    int loc = 12;
                    std::string imm = "-" + std::to_string(loc);
                    riscCode = indentOP("lw") + destReg + ", " + imm + "(sp)";
                    FINAL_CODE.addCode(riscCode, "Load return value's address from fp(-12) set by caller");

                    // The return Variable's Address in present in `a1` register
                    srcReg = "a1"; // Set during return statement

                    // Now we need to copy the data from srcReg to destReg
                    FINAL_CODE.addCopyInst("retVar", returnSize, srcImm, srcReg, destImm, destReg);
                }
                else
                {
                    std::string retReg;

                    // We have got the register
                    retReg = "a1"; // This is the register where the return value is stored

                    // We return the value via `a0` register, and return statment has set it in register `a5`
                    // We just need to move the value to the destination
                    riscCode = indentOP("mv") + "a0, " + retReg;
                    FINAL_CODE.addCode(riscCode, "Move return value stored by return statement into " + retReg + " to a0(default return reg)");
                    // Now store the value in the destination
                }

                // ---

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
                FINAL_CODE.addComment(" ~TAC~ ➔ Assign OP 🟰 - " + currIR.toBaseString());
                // This will store address(explicit address) of return value in `a0` register
                std::string dest = currIR.result;
                std::string src = currIR.arg1;

                bool isDead = !currIR.isAlive(dest);
                if (isDead)
                {
                    // This variable is dead, so we can ignore it
                    FINAL_CODE.addComment("🪦 Ignoring Assignment ☠️ dead variable " + dest);
                    continue;
                }

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                // NOW since dest is assigned, we need to update the SYM_RECORD
                SYM_RECORD.variableRest(dest); // update the variable assigned

                std::string destReg;
                // SYM_RECORD.freeGivenReg(regMap[dest]); // free the register (exclusive access)
                SYM_RECORD.addVarInReg(dest, regMap[dest]); // add the variable to the register

                // Special Case src is label
                if (isALabel(src))
                {
                    // src is a label
                    destReg = getRegName(regMap[dest]);
                    riscCode = indentOP("la") + destReg + ", " + src;
                    FINAL_CODE.addCode(riscCode, "Load address of label - " + src + " into " + destReg + "(" + dest + ")");
                }
                else if (isAValueSymbol(src))
                {
                    // src is a variable - No Need to load
                    FINAL_CODE.addComment(" 🔄 Automatic copy - of " + src + " into " + destReg + "(" + dest + ")");
                }
                else
                {
                    // src is a constant
                    destReg = getRegName(regMap[dest]);
                    // Load the constant in a register (temporary) (t0)
                    riscCode = indentOP("li") + destReg + ", " + src;
                    FINAL_CODE.addCode(riscCode, "Load constant - " + src + " into " + destReg + "(" + dest + ")");
                }
            }
            else if (op == LEFT_STAR)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ Left Star 🌟 - " + currIR.toBaseString());
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

                std::string destReg = getRegName(regMap[dest]);

                if (isAValueSymbol(src))
                {
                    // src is a variable
                    std::string srcReg = getRegName(regMap[src]);

                    int size = std::stoi(currIR.arg2);
                    std::string sl_type = store_load_Type(size);

                    // Load x[srcReg] in address of x[destReg]
                    riscCode = indentOP("s" + sl_type) + srcReg + ", 0(" + destReg + ")";
                    FINAL_CODE.addCode(riscCode, "Store variable of reg " + srcReg + " at address pointed by " + destReg);
                }
                else
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
            }
            else if (op == RIGHT_STAR)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ Right Star ✨ - " + currIR.toBaseString());
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
                std::string destReg = getRegName(regMap[dest]);
                SYM_RECORD.addVarInReg(dest, regMap[dest]); // add the variable to the register

                std::string srcReg = getRegName(regMap[src]);

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
                FINAL_CODE.addComment(" ~TAC~ ➔  Ampersend (&) - " + currIR.toBaseString());
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

                std::string destReg = getRegName(regMap[dest]);
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
                    FINAL_CODE.addCode(riscCode, "Load address of variable (via fp) - " + src + " into " + destReg);
                }
            }

            // Cast Operations
            else if (op == CAST)
            {
                // Only when int-type -> float->type or vice-versa
                FINAL_CODE.addComment(" ~TAC~ ➔ Cast - " + currIR.toBaseString());

                std::string dest = currIR.result;
                std::string src = currIR.arg1;
            }

            else if (op == OFFSET_LOAD)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ Offset Load - " + currIR.toBaseString());
                // This will load the address of the variable in the register
                std::string dest = currIR.result;
                std::string src = currIR.arg1;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                std::string destReg = getRegName(regMap[dest]);

                bool isGlobal = SYM_RECORD.isGlobal(src);
                if (isGlobal)
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
                    FINAL_CODE.addCode(riscCode, "Load address of variable (via fp) - " + src + " into " + destReg);
                }
            }

            // Param + Function Call + Return
            else if (op == PARAM)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ Param - " + currIR.toBaseString());
                // Only one argument
                std::string funcArg = currIR.arg1;

                // We need to push the argument in the queue
                parameterStack.push(funcArg); // Rest will be done by `CALL` instruction
                FINAL_CODE.addComment("Adding " + funcArg + " to parameter queue");

                // NO Code Generation
            }
            else if (op == CALL)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ Function Call - " + currIR.toBaseString());
                int noOfArg = std::stoi(currIR.arg2);
                std::string result = currIR.result;
                std::string funcName = currIR.arg1;

                // Find all the required params;
                std::vector<std::string> args;
                // std::set<std::string> usedVars;

                bool isFunctionALabel = isALabel(funcName);

                for (int i = 0; i < noOfArg; i++)
                {
                    if (parameterStack.empty())
                    {
                        CERR << "Error - Not enough parameters in queue" << std::endl;
                        return FAIL;
                    }
                    std::string arg = parameterStack.top();
                    parameterStack.pop();
                    args.push_back(arg);
                }

                // Reverse the args
                std::reverse(args.begin(), args.end());

                // NOW we would NEED to send all these arguments to the calle function's Stack
                int targetOffset = 16; // end of 4th word
                for (int i = 0; i < noOfArg; i++)
                {
                    // Now we need to store this register's value at the address of the caller's stack
                    int offset = SYM_RECORD.getOffset(args[i]);
                    int size = SYM_RECORD.getSize(args[i]);
                    targetOffset += size; //
                    if (size > 4)
                    {
                        // If size More than 4 we need MEMCOPY

                        std::string var = args[i];
                        int srcImm = 0, destImm = 0;
                        std::string srcReg = "t1", destReg = "t2";

                        // Load the address of the variable in a register (temporary) (t0)
                        std::string imm = "-" + std::to_string(offset);
                        std::string sl_type = store_load_Type(size);
                        riscCode = indentOP("addi") + srcReg + ", fp, " + imm;
                        FINAL_CODE.addCode(riscCode, "Load arg variable's address - " + args[i] + " into " + srcReg);

                        // Load the address of the variable in a register (temporary) (t0)
                        std::string imm2 = std::to_string(targetOffset);
                        std::string sl_type2 = store_load_Type(size);
                        riscCode = indentOP("addi") + destReg + ", sp, " + imm2;
                        FINAL_CODE.addCode(riscCode, "Load callee's stack address for - " + args[i] + " into " + destReg);

                        // Now we need to copy the data from srcReg to destReg
                        FINAL_CODE.addCopyInst(var, size, srcImm, srcReg, destImm, destReg);
                    }
                    else
                    {

                        std::string sl_type = store_load_Type(size);
                        std::string tempReg = "t2";

                        // Before using check if the variable is in memory
                        int regNo = SYM_RECORD.varStoredInWhichReg(args[i]);
                        if (regNo != -1)
                        {
                            // If variable is not in any register it must be in memory

                            bool isInMemory = SYM_RECORD.isInMemory(args[i]);
                            if (!isInMemory)
                            {
                                CERR << "Error - Variable must have been in memory" << std::endl;
                                return FAIL;
                            }

                            // Load the variable into tempReg from memory
                            std::string imm = "-" + std::to_string(offset);
                            riscCode = indentOP("l" + sl_type) + tempReg + ", " + imm + "(fp)";
                            FINAL_CODE.addCode(riscCode, "Load variable - " + args[i] + " into " + tempReg);
                        }
                        else
                        {
                            tempReg = getRegName(regNo);
                        }

                        // Now store this tempReg to the caller's stack
                        std::string imm2 = std::to_string(targetOffset);
                        riscCode = indentOP("s" + sl_type) + tempReg + ", " + imm2 + "(sp)";
                        FINAL_CODE.addCode(riscCode, "Store argument " + args[i] + " via " + tempReg + " to callee's stack");
                    }
                }

                // Now that we have loaded all the arguments, we need to call the function

                // Spill the registers
                spillingCode();

                // Call the function
                riscCode = indentOP("jal") + "x1, " + funcName; // jal x1, funcName
                FINAL_CODE.addCode(riscCode, "Call function - " + funcName);

                // Now we need to load the return value from the function
                if (returnValueViaRegister)
                {
                    // This will assume the return value is in a0 register
                    // We need to load the return value in the caller's stack
                    int offset = SYM_RECORD.getOffset(result);
                    std::string imm = "-" + std::to_string(offset);
                    // Store this register in the place of result
                    std::string destReg = "a0";
                    std::string sl_type = store_load_Type(4);
                    // Store this register in the place of result
                    riscCode = indentOP("s" + sl_type) + destReg + ", " + imm + "(fp)";
                    FINAL_CODE.addCode(riscCode, "Store return value in caller's stack for - " + result);
                    // Now we need to update the SYM_RECORD
                    SYM_RECORD.variableRest(result); // update the variable assigned
                    SYM_RECORD.setInMemory(result);  // set the variable in memory
                }
                else
                {
                    // Store the return variable's address into caller's stack
                    int offset = SYM_RECORD.getOffset(result);
                    std::string imm = "-" + std::to_string(offset);

                    // Find address of result variable
                    std::string addrReg = "t0";
                    riscCode = indentOP("addi") + addrReg + ", fp, " + imm;
                    FINAL_CODE.addCode(riscCode, "Load variable's address - " + result + " into " + addrReg);

                    // Store this address in the caller's stack
                    int loc = 12; // 3rd word
                    riscCode = indentOP("sw") + addrReg + ", " + std::to_string(loc) + "(sp)";
                    FINAL_CODE.addCode(riscCode, "Store return variable's address - " + result + " into caller's stack");
                }
            }
            else if (op == RETURN_FUNCTION)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ Return Statements - " + currIR.toBaseString());
                std::string retVar = currIR.arg1;
                bool defaultRet = (retVar == NO_ARG);

                std::string retReg = "a1";

                // Decide OnHow to return the value
                if (!returnValueViaRegister)
                {
                    // Store the return value at this address (but will depend on size of return value)
                    // Assuming the return value's address is stored in `a0` (explicit address)

                    if (defaultRet)
                    {
                        // SHOULD NOT HAPPEN
                        // Store x0 into `a1` register
                        riscCode = indentOP("mv") + retReg + ", x0";
                        FINAL_CODE.addCode(riscCode, "Move default return value in a1");
                    }
                    else
                    {
                        // Store the return variable's address into `a1`
                        int offset = SYM_RECORD.getOffset(retVar);
                        std::string imm = "-" + std::to_string(offset);
                        // Find address of result variable
                        riscCode = indentOP("addi") + retReg + ", fp, " + imm;
                        FINAL_CODE.addCode(riscCode, "Load return variable's address - " + retVar + " into " + retReg);
                    }
                }
                else
                {
                    std::string valueReg = "x0";
                    std::string retReg = "a1";
                    if (defaultRet)
                    {
                        valueReg = "x0"; // default return value - 0
                    }
                    else
                    {

                        // We need to check if return value is a constant or variable

                        bool isVariable = isAValueSymbol(retVar);

                        if (isVariable)
                        {
                            std::map<std::string, int> regMap;
                            int check = getReg(currIR, regMap);
                            if (check != OKAY)
                            {
                                CERR << "Error in getReg()" << std::endl;
                                return check;
                            }
                            // We have got the register
                            valueReg = getRegName(regMap[retVar]);
                        }
                        else
                        {
                            // It's a constant
                            valueReg = "t1"; // default return value - 0
                            // Load the constant in a register (temporary) (t0)
                            riscCode = indentOP("li") + valueReg + ", " + retVar;
                            FINAL_CODE.addCode(riscCode, "Load constant - " + retVar + " into " + valueReg);
                        }
                    }

                    // We return the value via `a0` register, and return statment has set it in register `a5`
                    // We just need to move the value to the destination
                    riscCode = indentOP("mv") + retReg + ", " + valueReg;
                    FINAL_CODE.addCode(riscCode, "Move return value's reg - " + valueReg + " to " + retReg);
                    // Now store the value in the destination
                }

                // This will store address(explicit address) of return value in `a0` register
            }

            // Jump Operations
            else if (op == GOTO_EQUAL)
            {
                FINAL_CODE.addComment(" ~TAC~ ➔ GOTO_EQUAL - " + currIR.toBaseString());

                // Spilling Code
                spillingCode();

                std::string condVar1 = currIR.arg1;
                std::string condVar2 = currIR.arg2;
                std::string label = currIR.result;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                std::string condReg1 = getRegName(regMap[condVar1]);
                std::string condReg2 = getRegName(regMap[condVar2]);

                // Now we have the register having the condVar
                riscCode = indentOP("beq") + condReg1 + ", " + condReg2 + ", " + label;
                FINAL_CODE.addCode(riscCode, "Jump to label - " + label + " if " + condVar1 + " == " + condVar2);
            }
            else if (op == GOTO_LABEL)
            {

                // Spilling Code
                spillingCode();

                FINAL_CODE.addComment(" ~TAC~ ➔ GOTO_LABEL - " + currIR.toBaseString());
                // Unconditional Jump
                std::string label = currIR.result;

                // We need to jump to this label
                riscCode = indentOP("j ") + label;
                FINAL_CODE.addCode(riscCode, "Unconditional Jump to label - " + label);
            }
            else if (op == IF_TRUE)
            {

                // Spilling Code
                spillingCode();

                FINAL_CODE.addComment(" ~TAC~ ➔ IF_TRUE - " + currIR.toBaseString());
                std::string condVar = currIR.arg1;
                std::string label = currIR.result;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                std::string condReg = getRegName(regMap[condVar]);

                // Now we have the register having the condVar
                riscCode = indentOP("bne") + condReg + ", x0, " + label;
                FINAL_CODE.addCode(riscCode, "Jump to label - " + label + " if " + condVar + " is true");
            }
            else if (op == IF_FALSE)
            {

                // Spilling Code
                spillingCode();

                FINAL_CODE.addComment(" ~TAC~ ➔ IF_FALSE - " + currIR.toBaseString());
                std::string condVar = currIR.arg1;
                std::string label = currIR.result;

                std::map<std::string, int> regMap;
                int check = getReg(currIR, regMap);
                if (check != OKAY)
                {
                    CERR << "Error in getReg()" << std::endl;
                    return check;
                }

                // Now we have the register having the condVar
                std::string condReg = getRegName(regMap[condVar]);
                riscCode = indentOP("beq") + condReg + ", x0, " + label;
                FINAL_CODE.addCode(riscCode, "Jump to label - " + label + " if " + condVar + " is false");
            }

            // Instruction to Ignore
            else if (op == ALLOCATE)
            {
                // TO Ignore
            }

            // Other Operation Based Insturctions
            else
            {
                // This will be a simple operation
                FINAL_CODE.addComment(" ~TAC~ ➔ Simple Operation - " + currIR.toBaseString());

                generateSimpleExpCode(currIR); // This will do all the work
            }
        }
    }

    return OKAY;
}


void spillingCode()
{
    // At the End of the block, we need to store all the registers into the memory
    FINAL_CODE.addComment(" ~~ Spilling Code ~~ ");
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
            SYM_RECORD.setInMemory(var);         // set the variable in memory
        }

        SYM_RECORD.freeGivenReg(regNo); // free this register
    }

    // Finally we reset the SYM_RECORD for this block
    SYM_RECORD.resetRegTable(); // reset the register map [Thus Next Block will assume all registers are free]

    FINAL_CODE.addComment(" ~~ Finished Spilling Code ~~ ");
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
    int minIntReg = 12;
    int maxIntReg = 31;
    std::pair<int, int> regLimit = std::make_pair(minIntReg, maxIntReg);
    int check = getRegLimit(code, regMap, regLimit);
    if (check != OKAY)
    {
        CERR << "Error in getRegLimit()" << std::endl;
        return check;
    }
    return OKAY;
}

int getRegLimit(NEW_TAC_Quadruple &code, std::map<std::string, int> &regMap, std::pair<int, int> regLimit)
{
    // THis will only consider the registers within the given limit
    // int lineNo = code.lineNo;

    std::string op = code.op;
    std::vector<std::string> usageType;
    std::vector<std::string> assignmentType;

    std::string result = code.result;
    std::string arg1 = code.arg1;
    std::string arg2 = code.arg2;

    // We would never allocate a register to a address type variables

    if (op == FUNCTION_ENTRY || op == FUNCTION_EXIT || op == ALLOCATE)
    {
        return OKAY; // Would never call getReg()
    }
    else
    {
        // All OP will need arg1 & arg2 as Usage
        if (isAValueSymbol(arg1))
        {
            // If it's a symbol
            usageType.push_back(arg1);
        }

        if (isAValueSymbol(arg2))
        {
            // If it's a symbol
            usageType.push_back(arg2);
        }

        if (op == CALL || op == LEFT_STAR ||
            op == GOTO_EQUAL || op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE)
        {
            // Those in which result is used & not assigned
            if (isAValueSymbol(result))
            {
                usageType.push_back(result);
            }
        }
        else
        {
            // Normal Operator's Type Operations + Special OP with assignment to result
            // Includes -> ASSIGN_OP, RIGHT_STAR, AMPERSEND, CAST {assignment to result}
            // Include -> PARAM, RETURN_FUNCTION {NO result variable}

            if (isAValueSymbol(result))
            {
                assignmentType.push_back(result);
            }
        }
    }

    // Step 1. Dividing things into usage & assignment Type

    std::string usageVar1 = (usageType.size() > 0) ? usageType[0] : "NULL";
    std::string usageVar2 = (usageType.size() > 1) ? usageType[1] : "NULL";
    std::string assignVar = (assignmentType.size() > 0) ? assignmentType[0] : "NULL";

    CERR << "------ Debugging getReg() ------ " << std::endl;
    CERR << "Given TAC - " << code.toBaseString() << std::endl;
    CERR << "Usage Variables - " << usageVar1 << " " << usageVar2 << std::endl;
    CERR << "Assignment Variables - " << assignVar << std::endl;
    CERR << "--------------------------" << std::endl;

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
    if (op == FUNCTION_ENTRY || op == ALLOCATE || op == FUNCTION_EXIT)
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

        if (op == OFFSET_LOAD)
        {
            // We don't need register for 2nd operand
            usageVar2 = "NULL"; // since it would be loaded from memory
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
                int anyFree = SYM_RECORD.getFreeReg(regLimit);
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
                        if (chosenReg < regLimit.first || chosenReg > regLimit.second)
                        {
                            // This is not in the given limit
                            continue;
                        }

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
                    SYM_RECORD.freeGivenReg(bestReg); // since we are loading a new variable

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
                int anyFree = SYM_RECORD.getFreeReg(regLimit);
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

                        if (chosenReg < regLimit.first || chosenReg > regLimit.second)
                        {
                            // This is not in the given limit
                            continue;
                        }

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
                        int anyFree = SYM_RECORD.getFreeReg(regLimit);
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

                                if (chosenReg < regLimit.first || chosenReg > regLimit.second)
                                {
                                    // This is not in the given limit
                                    continue;
                                }

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
        getRegResult += " | 🤝 " + getRegName(regNo) + "` reg ➜ " + varName;
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

    for (auto usageVar : varNames)
    {

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

void RISCV_CODE::addCopyInst(std::string variable, int size, int srcImm, std::string src_wrtReg, int destImm, std::string dest_wrtReg)
{

    // We need to copy the value from one location to another
    FINAL_CODE.addComment(" ~~ Copy Instruction for " + variable + " of size " + std::to_string(size) + " from (" + src_wrtReg + ", " + std::to_string(srcImm) + ") to (" + dest_wrtReg + ", " + std::to_string(destImm) + ")");

    // We would be considering this offset in +ve

    std::string riscCode;
    // We do things in chunks of 4 bytes
    int noOfChunks = size / 4;
    int remainingBytes = size % 4;
    for (int i = 0; i < noOfChunks; i++)
    {
        // We need to copy the value from one location to another
        riscCode = indentOP("lw") + "t0, " + std::to_string(srcImm + (i * 4)) + "(" + src_wrtReg + ")";
        this->addCode(riscCode, "Copying value from (" + src_wrtReg + ", " + std::to_string(srcImm + (i * 4)) + ") to t0");

        riscCode = indentOP("sw") + "t0, " + std::to_string(destImm + (i * 4)) + "(" + dest_wrtReg + ")";
        this->addCode(riscCode, "Copying value from t0 to (" + dest_wrtReg + ", " + std::to_string(destImm + (i * 4)) + ")");
    }

    if (remainingBytes > 0)
    {
        std::string sl_type = store_load_Type(remainingBytes);
        // We need to copy the value from one location to another
        riscCode = indentOP("l" + sl_type) + "t0, " + std::to_string(srcImm + (noOfChunks * 4)) + "(" + src_wrtReg + ")";
        this->addCode(riscCode, "Copying value from (" + src_wrtReg + ", " + std::to_string(srcImm + (noOfChunks * 4)) + ") to t0");

        riscCode = indentOP("s" + sl_type) + "t0, " + std::to_string(destImm + (noOfChunks * 4)) + "(" + dest_wrtReg + ")";
        this->addCode(riscCode, "Copying value from t0 to (" + dest_wrtReg + ", " + std::to_string(destImm + (noOfChunks * 4)) + ")");
    }
}

void RISCV_CODE::addLoadInst(const std::string &varName, int regNo)
{
    /*
    Logic
    - For VALUE_SPACE variables - we load the exact value of the variable at the address given by SYM_RECORD
        - For Global - we load address from label THEN it's value
        - For Local - we directly load the value from the offset
    - For ADDRESS_SPACE variables - we load the address of the variable in a register
        - For Global - we load address from label
        - For Local - we load the offset using fp - this will be exact address (NOT w.r.t fp)
    */

    std::string riscCode;
    int sizeOfVar = SYM_RECORD.getSize(varName);

    std::string sl_type = store_load_Type(sizeOfVar);

    // The Variable to Store in global we don't have it's offset first we need to load the address of the variable
    bool isGlobal = SYM_RECORD.isGlobal(varName);

    bool isFloat = SYM_RECORD.isFloat(varName);
    std::string loadOP = (isFloat) ? "fl" : "l";

    if (isGlobal)
    {
        // We need to load the address of the variable in a register
        std::string addrReg = "t0";
        riscCode = indentOP("la") + addrReg + ", " + varName;
        this->addCode(riscCode, "Loading Address of Global Variable - " + varName);

        // Now we can store the value in the memory
        riscCode = indentOP(loadOP + sl_type) + getRegName(regNo) + ", 0(" + addrReg + ")";
        this->addCode(riscCode, "Load Global Var - " + varName + " via " + addrReg + " in x" + std::to_string(regNo));
    }
    else
    {
        // Else it's a local variable - we need its offset
        int loc = SYM_RECORD.getOffset(varName);                                                          // [This Offset is w.r.t fp]
        riscCode = indentOP(loadOP + sl_type) + getRegName(regNo) + ", -" + std::to_string(loc) + "(fp)"; // w.r.t frame pointer(fp)
        this->addCode(riscCode, "Load Local Var - " + varName + " via fp in x" + std::to_string(regNo));
    }

    return;
}

void RISCV_CODE::addStoreInst(const std::string &varName, int regNo)
{
    /*
    Logic
    - For VALUE_SPACE variables - we store the exact value of the variable at the address given by SYM_RECORD
        - For Global - we store address from label THEN it's value
        - For Local - we directly store the value from the offset
    - For ADDRESS_SPACE variables -
        - For Global - we will need to store the data pointed by reg to the address of the variable
        - For Local - we will need to store the data pointed by reg to - the variable
    */
    std::string riscCode;
    int sizeOfVar = SYM_RECORD.getSize(varName);

    std::string sl_type = store_load_Type(sizeOfVar);

    // The Variable to Store in global we don't have it's offset first we need to load the address of the variable
    bool isGlobal = SYM_RECORD.isGlobal(varName);

    bool isFloat = SYM_RECORD.isFloat(varName);
    std::string storeOP = (isFloat) ? "fs" : "s";

    if (isGlobal)
    {
        // We need to load the address of the variable in a register
        std::string addrReg = "t0";
        riscCode = indentOP("la") + addrReg + ", " + varName;
        this->addCode(riscCode, "Loading Address of Global Variable - " + varName);

        // Now we can store the value in the memory
        riscCode = indentOP(storeOP + sl_type) + getRegName(regNo) + ", 0(" + addrReg + ")";
        this->addCode(riscCode, "Store Global Var - " + varName + " via " + addrReg + " in x" + std::to_string(regNo));
    }
    else
    {
        // Else it's a local variable - we need its offset
        int loc = SYM_RECORD.getOffset(varName);                                                           // [This Offset is w.r.t fp]
        riscCode = indentOP(storeOP + sl_type) + getRegName(regNo) + ", -" + std::to_string(loc) + "(fp)"; // w.r.t frame pointer(fp)
        this->addCode(riscCode, "Store Local Var - " + varName + " via fp in x" + std::to_string(regNo));
    }

    return;
}

std::string store_load_Type(int size)
{
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
    else if (size == 4)
    {
        sl_type = "w";
    }
    else if (size == 8)
    {
        sl_type = "d";
    }
    else
    {
        CERR << "Error - Invalid Size for Store/Load Instruction - " << size << std::endl;
        sl_type = "- WRONG -";
    }

    return sl_type;
}

int getFloatReg(NEW_TAC_Quadruple &code, std::map<std::string, int> &regMap)
{

    // This will return the register number for the variable
    int check = getRegLimit(code, regMap, floatRegLimit);
    if (check != OKAY)
    {
        CERR << "Error - getRegLimit() failed" << std::endl;
        return FAIL;
    }

    return OKAY;
}


int generateSimpleExpCode(NEW_TAC_Quadruple code)
{

    std::string op = code.op;
    std::string assignVar = code.result;
    std::string usageVar1 = code.arg1;
    std::string usageVar2 = code.arg2;

    std::string riscCode;

    bool isFloat = SYM_RECORD.isFloat(assignVar); //[Need to add isFloat variable to SYM_RECORD]

    if (!isFloat)
    {
        // Simple Operation with int type register

        // Possible that one of the two arguments could be an immediate value

        bool isImm1 = isInt(usageVar1);
        bool isImm2 = isInt(usageVar2);

        std::string usageReg1, usageReg2;

        // Call getReg() to get the register for the variables
        std::map<std::string, int> regMap;
        int check = getReg(code, regMap);
        if (check != OKAY)
        {
            CERR << "Error - getReg() failed" << std::endl;
            return FAIL;
        }

        if (isImm1)
        {
            // Load them in a register
            usageReg1 = "t0";
            riscCode = indentOP("li") + usageReg1 + ", " + usageVar1;
            FINAL_CODE.addCode(riscCode, "Loading Immediate Value - " + usageVar1 + " in " + usageReg1);
        }
        else
        {
            usageReg1 = getRegName(regMap[usageVar1]);
        }

        if (isImm2)
        {
            // Load them in a register
            usageReg2 = "t1";
            riscCode = indentOP("li") + usageReg2 + ", " + usageVar2;
            FINAL_CODE.addCode(riscCode, "Loading Immediate Value - " + usageVar2 + " in " + usageReg1);
        }
        else
        {
            usageReg2 = getRegName(regMap[usageVar2]);
        }

        std::string assignReg = getRegName(regMap[assignVar]);

        // Now we are ready to do the operations

        std::string riscOp;

        // We need to update the SYM_RECORD
        SYM_RECORD.variableRest(assignVar); // This variable is
        SYM_RECORD.addVarInReg(assignVar, regMap[assignVar]);

        // Arithmetic OP
        if (op == "+")
        {
            riscOp = "add";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Addition Operation - " + assignVar + " = " + usageVar1 + " + " + usageVar2);
        }
        else if (op == "-")
        {
            riscOp = "sub";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Subtraction Operation - " + assignVar + " = " + usageVar1 + " - " + usageVar2);
        }

        else if (op == "*")
        {
            riscOp = "mul";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Multiplication Operation - " + assignVar + " = " + usageVar1 + " * " + usageVar2);
        }
        else if (op == "/")
        {
            riscOp = "div";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Division Operation - " + assignVar + " = " + usageVar1 + "/" + usageVar2);
        }
        else if (op == "%")
        {
            riscOp = "rem";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Modulus Operation - " + assignVar + " = " + usageVar1 + "%" + usageVar2);
        }

        // Shift OP
        else if (op == "<<")
        {
            riscOp = "sll";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Left Shift Operation - " + assignVar + " = " + usageVar1 + "<< " + usageVar2);
        }
        else if (op == ">>")
        {
            riscOp = "srl";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Right Shift Operation - " + assignVar + " = " + usageVar1 + ">> " + usageVar2);
        }

        // Bitwise OP
        else if (op == "&")
        {
            riscOp = "and";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Bitwise AND Operation - " + assignVar + " = " + usageVar1 + " & " + usageVar2);
        }
        else if (op == "|")
        {
            riscOp = "or";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Bitwise OR Operation - " + assignVar + " = " + usageVar1 + " | " + usageVar2);
        }
        else if (op == "^")
        {
            riscOp = "xor";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Bitwise XOR Operation - " + assignVar + " = " + usageVar1 + " ^ " + usageVar2);
        }

        // Special sizeof Op
        else if (op == "sizeof")
        {
            // Don't think will come - as per TAC -
        }
        // Comparision OP
        else if (op == "<")
        {
            riscOp = "slt";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Less Than Operation - " + assignVar + " = " + usageVar1 + " < " + usageVar2);
        }
        else if (op == ">")
        {
            riscOp = "slt";
            riscCode = indentOP(riscOp) + assignReg + ", " + usageReg2 + ", " + usageReg1;
            FINAL_CODE.addCode(riscCode, "Greater Than Operation - " + assignVar + " = " + usageVar1 + " > " + usageVar2);
        }
        else if (op == "<=")
        {

            // First Check if > // Then invert the result
            std::string tempReg = "t1";
            riscCode = indentOP("slt") + tempReg + ", " + usageReg2 + ", " + usageReg1;
            FINAL_CODE.addCode(riscCode, "Part1 of Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);

            riscCode = indentOP("xori") + assignReg + ", " + tempReg + ", 1";
            FINAL_CODE.addCode(riscCode, "Part2 of Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);

            // Another Way
            // riscCode = indentOP("slt") + tempReg + ", " + usageReg2 + ", " + usageReg1;
            // FINAL_CODE.addCode(riscCode, "Part1 of Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);

            // riscCode = indentOP("seqz") + tempReg + ", " + tempReg;
            // FINAL_CODE.addCode(riscCode, "Part2 Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);

            // riscCode = indentOP("addi") + assignReg + ", " + tempReg + ", 0xff";
            // FINAL_CODE.addCode(riscCode, "Part3 Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);
        }
        else if (op == ">=")
        {
            std::string tempReg = "t1";

            // First Check if < // Then invert the result
            riscCode = indentOP("slt") + tempReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Part1 of Greater Than Equal Operation - " + assignVar + " = " + usageVar1 + " >= " + usageVar2);

            riscCode = indentOP("xori") + assignReg + ", " + tempReg + ", 1";
            FINAL_CODE.addCode(riscCode, "Part2 of Greater Than Equal Operation - " + assignVar + " = " + usageVar1 + " >= " + usageVar2);

            // Another Way
            // riscCode = indentOP("slt") + tempReg + ", " + usageReg2 + ", " + usageReg1;
            // FINAL_CODE.addCode(riscCode, "Part1 of Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);

            // riscCode = indentOP("seqz") + tempReg + ", " + tempReg;
            // FINAL_CODE.addCode(riscCode, "Part2 of Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);

            // riscCode = indentOP("addi") + assignReg + ", " + tempReg + ", 0xff";
            // FINAL_CODE.addCode(riscCode, "Part3 of Less Than Equal Operation - " + assignVar + " = " + usageVar1 + " <= " + usageVar2);
        }
        else if (op == "==")
        {

            std::string tempReg = "t1";
            riscCode = indentOP("sub") + tempReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Part1 of Equality Operation - " + assignVar + " = " + usageVar1 + " == " + usageVar2);

            riscCode = indentOP("seqz") + tempReg + ", " + tempReg;
            FINAL_CODE.addCode(riscCode, "Part2 of Equality Operation - " + assignVar + " = " + usageVar1 + " == " + usageVar2);

            riscCode = indentOP("addi") + assignReg + ", " + tempReg + ", 0xff";
            FINAL_CODE.addCode(riscCode, "Part3 of Equality Operation - " + assignVar + " = " + usageVar1 + " == " + usageVar2);
        }
        else if (op == "!=")
        {
            std::string tempReg = "t1";
            riscCode = indentOP("sub") + tempReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Part1 of Not Equality Operation - " + assignVar + " = " + usageVar1 + " != " + usageVar2);

            riscCode = indentOP("snez") + tempReg + ", " + tempReg;
            FINAL_CODE.addCode(riscCode, "Part2 of Not Equality Operation - " + assignVar + " = " + usageVar1 + " != " + usageVar2);

            riscCode = indentOP("addi") + assignReg + ", " + tempReg + ", 0xff";
            FINAL_CODE.addCode(riscCode, "Part3 of Not Equality Operation - " + assignVar + " = " + usageVar1 + " != " + usageVar2);
        }
        // Logical OP
        else if (op == "&&")
        {
            // Logical AND

            std::string tempReg1 = "t1", tempReg2 = "t2";

            riscCode = indentOP("snez") + tempReg1 + ", " + usageReg1;
            FINAL_CODE.addCode(riscCode, "Part1 of Logical AND Operation - " + assignVar + " = " + usageVar1 + " && " + usageVar2);

            riscCode = indentOP("snez") + tempReg2 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Part2 of Logical AND Operation - " + assignVar + " = " + usageVar1 + " && " + usageVar2);

            riscCode = indentOP("and") + assignReg + ", " + tempReg1 + ", " + tempReg2;
            FINAL_CODE.addCode(riscCode, "Part3 of Logical AND Operation - " + assignVar + " = " + usageVar1 + " && " + usageVar2);
        }
        else if (op == "||")
        {
            // Logical OR
            std::string tempReg1 = "t1", tempReg2 = "t2";

            riscCode = indentOP("snez") + tempReg1 + ", " + usageReg1;
            FINAL_CODE.addCode(riscCode, "Part1 of Logical OR Operation - " + assignVar + " = " + usageVar1 + " || " + usageVar2);

            riscCode = indentOP("snez") + tempReg2 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "Part2 of Logical OR Operation - " + assignVar + " = " + usageVar1 + " || " + usageVar2);

            riscCode = indentOP("or") + assignReg + ", " + tempReg1 + ", " + tempReg2;
            FINAL_CODE.addCode(riscCode, "Part3 of Logical OR Operation - " + assignVar + " = " + usageVar1 + " || " + usageVar2);
        }
        else
        {
            // Invalid Operation
            CERR << "Error - Invalid Operation in generateSimpleExpCode()" << std::endl;
            return FAIL;
        }
    }
    else
    {
        // Simple Operation with float type register

        // NO possibility of imm-values - since all would have been stored in memory first before loading

        std::string usageReg1, usageReg2, assignReg;

        std::map<std::string, int> regMap;
        int check = getFloatReg(code, regMap);
        if (check != OKAY)
        {
            CERR << "Error - getReg() failed" << std::endl;
            return FAIL;
        }

        usageReg1 = "f" + std::to_string(regMap[usageVar1]);
        usageReg2 = "f" + std::to_string(regMap[usageVar2]);
        assignReg = "f" + std::to_string(regMap[assignVar]);

        // Arithmetic OP
        if (op == "+")
        {
            riscCode = indentOP("fadd.s") + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "F_Addition Operation - " + assignVar + " = " + usageVar1 + " + " + usageVar2);
        }
        else if (op == "-")
        {
            riscCode = indentOP("fsub.s") + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "F_Subtraction Operation - " + assignVar + " = " + usageVar1 + " - " + usageVar2);
        }
        else if (op == "*")
        {
            riscCode = indentOP("fmul.s") + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "F_Multiplication Operation - " + assignVar + " = " + usageVar1 + " * " + usageVar2);
        }
        else if (op == "/")
        {
            riscCode = indentOP("fdiv.s") + assignReg + ", " + usageReg1 + ", " + usageReg2;
            FINAL_CODE.addCode(riscCode, "F_Division Operation - " + assignVar + " = " + usageVar1 + "/" + usageVar2);
        }

        // Comparision OP
        else if (op == "<")
        {
        }
        else if (op == ">")
        {
        }
        else if (op == "<=")
        {
        }
        else if (op == ">=")
        {
        }
        else if (op == "==")
        {
        }
        else if (op == "!=")
        {
        }
        else
        {
            // Invalid Operation
            CERR << "Error - Invalid Operation in generateSimpleExpCode()" << std::endl;
            return FAIL;
        }
    }

    return OKAY;
}


int addPrint_ScanLib()
{
    // This will add the print and scan library to the code

    std::string printVar = "printVar";
    std::string printString = "printString";
    std::string scanVar = "scanVar";
    std::string scanString = "scanString";

    std::string riscCode;

    FINAL_CODE.addComment(" ==== Adding Print and Scan Library ==== ");

    addPrintVar(); // Signature - void printVar(int var)

    addPrintString(); // Signature - void printString(char *str)

    addScanVar(); // Signature - int scanVar();

    addScanString(); // Signature - char *scanString(int size);

    FINAL_CODE.addComment(" ==== End of Print and Scan Library ==== ");
    FINAL_CODE.addComment(" ");

    return OKAY;
}

void addPrintVar()
{

    std::string riscCode;
    FINAL_CODE.addLabel("printVar");

    int stackSize = 20;

    // Function Entry Code
    FINAL_CODE.addComment("Function Entry - printVar");
    riscCode = indentOP("addi") + "sp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Allocating Stack Space");

    int loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("sw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("sw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Frame Pointer");

    riscCode = indentOP("addi") + "fp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Setting Frame Pointer");

    // Load to print variable in a register
    std::string varReg = "a0"; // DEFAULT register for print - System Call
    loc = 20;                  // Offset of the variable
    riscCode = indentOP("lw") + varReg + ", -" + std::to_string(loc) + "(fp)";

    // Load system call code
    std::string syscallCodeReg = "a7";
    int printVarCode = 1;
    riscCode = indentOP("li") + syscallCodeReg + ", " + std::to_string(printVarCode);

    FINAL_CODE.addCode(riscCode, "Loading Print System Call Code");

    // System Call
    riscCode = indentOP("ecall");
    FINAL_CODE.addCode(riscCode, "System Call for Print");

    FINAL_CODE.addComment("Function Exit - printVar");

    // Resutlt would be in a0 register - exit code - 0 [since it's a void function]
    int exitCode = 0;
    riscCode = indentOP("li") + "a0, " + std::to_string(exitCode);
    FINAL_CODE.addCode(riscCode, "Return value from printVar");

    // Function Exit Code
    loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("lw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("lw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Frame Pointer");

    // Deallocating Stack Space
    riscCode = indentOP("addi") + "sp, sp, " + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Deallocating Stack Space");

    // Return from the function
    riscCode = indentOP("jr") + "ra";
    FINAL_CODE.addCode(riscCode, "Returning from printVar");

    FINAL_CODE.addComment("End of Function - printVar");

    return;
}

void addPrintString()
{

    // Function Signature void printString(char *str)

    std::string riscCode;
    FINAL_CODE.addLabel("printString");

    int stackSize = 20;

    // Function Entry Code
    FINAL_CODE.addComment("Function Entry - printVar");

    riscCode = indentOP("addi") + "sp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Allocating Stack Space");

    int loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("sw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("sw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Frame Pointer");

    riscCode = indentOP("addi") + "fp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Setting Frame Pointer");

    // Load to print variable in a register
    std::string varReg = "a0"; // DEFAULT register for print - System Call
    loc = 20;                  // Offset of the variable
    riscCode = indentOP("lw") + varReg + ", -" + std::to_string(loc) + "(fp)";
    FINAL_CODE.addCode(riscCode, "Loading Address of String Variable");

    // Load system call code
    std::string syscallCodeReg = "a7";
    int printStringCode = 4;
    riscCode = indentOP("li") + syscallCodeReg + ", " + std::to_string(printStringCode);
    FINAL_CODE.addCode(riscCode, "Loading Print System Call Code");

    // System Call
    riscCode = indentOP("ecall");
    FINAL_CODE.addCode(riscCode, "System Call for Print");

    FINAL_CODE.addComment("Function Exit - printString");

    // Resutlt would be in a0 register - exit code - 0 [since it's a void function]
    int exitCode = 0;
    riscCode = indentOP("li") + "a0, " + std::to_string(exitCode);
    FINAL_CODE.addCode(riscCode, "Return value from printString");

    // Function Exit Code
    loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("lw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("lw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Frame Pointer");

    // Deallocating Stack Space
    riscCode = indentOP("addi") + "sp, sp, " + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Deallocating Stack Space");

    // Return from the function
    riscCode = indentOP("jr") + "ra";
    FINAL_CODE.addCode(riscCode, "Returning from printString");

    FINAL_CODE.addComment("End of Function - printString");

    return;
}

void addScanVar()
{

    // Function Signature int scanVar();

    std::string riscCode;
    FINAL_CODE.addLabel("scanVar");

    int stackSize = 20;

    riscCode = indentOP("addi") + "sp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Allocating Stack Space");

    int loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("sw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("sw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Frame Pointer");

    riscCode = indentOP("addi") + "fp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Setting Frame Pointer");

    // Load system call code
    std::string syscallCodeReg = "a7";
    int scanVarCode = 5;

    riscCode = indentOP("li") + syscallCodeReg + ", " + std::to_string(scanVarCode);
    FINAL_CODE.addCode(riscCode, "Loading Scan System Call Code");

    // System Call
    riscCode = indentOP("ecall");
    FINAL_CODE.addCode(riscCode, "System Call for Scan");

    // Resutlt would be in a0 register - from the scan & we need to store it in the variable in `a0` register
    loc = 20; // Offset of the variable
    riscCode = indentOP("sw") + "a0, -" + std::to_string(loc) + "(fp)";
    FINAL_CODE.addCode(riscCode, "Storing Scan Result in Variable(Redundant)");

    FINAL_CODE.addComment("Result already in a0 register");

    // Function Exit Code
    loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("lw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("lw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Frame Pointer");

    // Deallocating Stack Space
    riscCode = indentOP("addi") + "sp, sp, " + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Deallocating Stack Space");

    // Return from the function
    riscCode = indentOP("jr") + "ra";
    FINAL_CODE.addCode(riscCode, "Returning from scanVar");

    FINAL_CODE.addComment("End of Function - scanVar");

    return;
}

void addScanString()
{

    // Function Signature char* scanString(int size);

    std::string riscCode;
    FINAL_CODE.addLabel("scanString");

    std::string strVar = FINAL_CODE.newDataLabel();

    dataSegment dataSeg;
    dataSeg.name = strVar;
    dataSeg.type = dataString;
    int maxSize = 100;
    dataSeg.value = std::to_string(maxSize); // A max of 100 characters scan

    int stackSize = 20;

    riscCode = indentOP("addi") + "sp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Allocating Stack Space");

    int loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("sw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("sw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Saving Frame Pointer");

    riscCode = indentOP("addi") + "fp, sp, -" + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Setting Frame Pointer");

    // Loading Address of the variable
    std::string addrReg = "a0"; // DEFAULT register for print - System Call
    riscCode = indentOP("la") + addrReg + ", " + strVar;
    FINAL_CODE.addCode(riscCode, "Where to store the scanned string");

    // Load size variable in a register
    std::string sizeReg = "a1"; // DEFAULT register for print - System Call
    loc = 20;                   // Offset of the variable
    riscCode = indentOP("lw") + sizeReg + ", -" + std::to_string(loc) + "(fp)";
    FINAL_CODE.addCode(riscCode, "How many bytes to scan");

    // Load system call code
    std::string syscallCodeReg = "a7";
    int scanStringCode = 8;
    riscCode = indentOP("li") + syscallCodeReg + ", " + std::to_string(scanStringCode);
    FINAL_CODE.addCode(riscCode, "Loading Scan System Call Code");

    // System Call
    riscCode = indentOP("ecall");
    FINAL_CODE.addCode(riscCode, "System Call for Scan");

    // Result would be at the dataSection of strVar;
    // We need to return the address of the string
    riscCode = indentOP("la") + "a0, " + strVar;
    FINAL_CODE.addCode(riscCode, "Returning Address of Scanned String");

    // Function Exit Code
    loc = stackSize - 4; // Offset of the return address
    riscCode = indentOP("lw") + "ra, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Return Address");

    loc = stackSize - 8; // Offset of the frame pointer
    riscCode = indentOP("lw") + "fp, " + std::to_string(loc) + "(sp)";
    FINAL_CODE.addCode(riscCode, "Restoring Frame Pointer");

    // Deallocating Stack Space
    riscCode = indentOP("addi") + "sp, sp, " + std::to_string(stackSize);
    FINAL_CODE.addCode(riscCode, "Deallocating Stack Space");

    // Return from the function
    riscCode = indentOP("jr") + "ra";
    FINAL_CODE.addCode(riscCode, "Returning from scanString");

    FINAL_CODE.addComment("End of Function - scanString");
    return;
}