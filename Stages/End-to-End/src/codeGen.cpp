#include "header.h"
#include "utility.h"

//=====================[ Code Generation ]=========================================================================================

SymTable symTable; // Global Symbol Table


int codeGen(const TAC &irCode, RISCV_CODE &riscvCode)
{
    // This will Take TAC irCode and give final riscvCode

    // Step 1. Identify basic blocks & control flow
    CFG controlFlowGraph;

    int check = makeBasicBlocks(irCode, controlFlowGraph);
    if (check != OKAY)
    {
        std::cerr << LOC << "Error in making basic blocks" << std::endl;
        return check;
    }

    // Try to visualize the CFG
    std::string dotFileName = "build/cfg.dot";
    check = controlFlowGraph.generateDOTFile(dotFileName);
    if (check != OKAY)
    {
        std::cerr << LOC << "Error in generating dot file" << std::endl;
        return check;
    }
    std::cerr << LOC << " | CFG generated successfully at " << dotFileName << std::endl;


    // Step 2. Add all Symbol Needed to the Symbol Table setting it's offsets & other things
}


//=====================[ Basic Blocks & CFGs ]=========================================================================================

std::string CFG::newBlock()
{
    std::string label = "Block_" + std::to_string(nextBlockIndex++);
    return label;
}

int CFG::addEdge(const std::string &from, const std::string &to)
{
    // This will add an edge from 'from' to 'to'
    // We will use the labelMap to get the index of the blocks

    // auto itFrom = labelMap.find(from);
    // auto itTo = labelMap.find(to);

    // if (itFrom == labelMap.end() || itTo == labelMap.end())
    // {
    //     std::cerr << LOC << "Error in adding edge - Block not found" << std::endl;
    //     return FAIL;
    // }

    // int fromIndex = itFrom->second;
    // int toIndex = itTo->second;

    edges.push_back({from, to});

    return OKAY;
}

int CFG::generateDOTFile(const std::string &filename)
{
    // This will generate a dot file for the CFG
    std::ofstream dotFile(filename);
    if (!dotFile.is_open())
    {
        std::cerr << LOC << "Error in opening file" << std::endl;
        return FAIL;
    }

    dotFile << "digraph G {" << std::endl;

    // Add nodes
    for (auto block : blocks)
    {
        dotFile << block.label;
        dotFile << " [label=<\n";
        dotFile << "<table border=\"0\" cellborder=\"1\" cellspacing=\"1\">\n";

        // Heading with larger font
        std::string headerColor = "blue3";
        dotFile << "  <tr><td><FONT COLOR=\"" << headerColor << "\"><font point-size=\"12\"><b>" << block.label << "</b></font></FONT></td></tr>\n";
        
        // Extra info with smaller font
        int whichBlock = labelMap[block.label];
        for (auto it : block.irCode)
        {
            std::string info = it.toString();
            info = escapeCharacters(info);
            dotFile << "  <tr><td><FONT COLOR=\"brown1\"><font point-size=\"10\">" << info << "</font></FONT></td></tr>\n";
        }

        dotFile << "</table>\n";
        dotFile << ">, shape=box];" << std::endl;
    }

    // Add edges
    for (auto edge : edges)
    {
        dotFile << edge.first << " -> " << edge.second << ";" << std::endl;
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

int makeBasicBlocks(const TAC &irCode, CFG &cfg)
{

    // Step 1. Identify basic blocks & some small stuffs

    // All those instruction with operation GOTO_LABEL, IF_TRUE, IF_FALSE, FUNCTION_ENTRY, GOTO_EQUAL, CALL

    std::set<int> leaders;
    std::map<int, std::string> indexToBlockMap; // Map of block_name to leader's index

    for (int i = 0; i < irCode.code.size(); i++)
    {
        std::string op = irCode.code[i].op;

        // Target Leaders
            if (op == FUNCTION_ENTRY)
            {
                leaders.insert(i);
                indexToBlockMap[i] = irCode.code[i].result;
            }

            if (op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE || op == GOTO_EQUAL)
            {
                int targetIndex = std::stoi(irCode.code[i].result);
                leaders.insert(targetIndex);
                std::string newBlockLable = cfg.newBlock();
                indexToBlockMap[targetIndex] = newBlockLable;
            }

        // Return Point Leader - i.e next line to goto, call, etc.
            if (op == GOTO_EQUAL || op == IF_FALSE || op == IF_TRUE || op == CALL || op == GOTO_LABEL)
            {

                // Special Case of merging if-else block
                if (op == IF_TRUE || op == IF_FALSE)
                {
                    // and next line is a goto label & target is next-to-next line
                    std::string op_next = irCode.code[i + 1].op;
                    int target = std::stoi(irCode.code[i].result);
                    if (op_next == GOTO_LABEL && target == i + 2)
                    {
                        continue;
                    }
                }

                // Else all next lines are leaders
                if (i + 1 < irCode.code.size())
                {
                    leaders.insert(i + 1);
                    std::string newBlockLable = cfg.newBlock();
                    indexToBlockMap[i + 1] = newBlockLable;
                }
            }
    }

    // copy leader data to cfg
    for (auto it : leaders)
    {
        cfg.leaders.push_back(it);
        std::cerr << "Leader : " << it << std::endl;
    }

    // Step 2. Create All the blocks
    BasicBlock entryBlock;
    entryBlock.label = "ENTRY";
    cfg.blocks.push_back(entryBlock);
    // cfg.labelMap["ENTRY"] = 0;

    // Now we will create blocks
    for (auto it : indexToBlockMap)
    {
        // std::cerr << "Block Name : " << it.first << " - " << it.second << std::endl;
        BasicBlock newBlock;
        newBlock.label = it.second;                      // Block Name
        cfg.blocks.push_back(newBlock);                  // Add to CFG
        cfg.labelMap[it.second] = cfg.blocks.size() - 1; // Map to index

    }


    // // Check indexToBlockMap
    // std::cerr << "Index to Block Map" << std::endl;
    // for (auto it : indexToBlockMap)
    // {
    //     std::cerr << it.first << " - " << it.second << std::endl;
    // }

    // // Check cfg.labelMap
    // std::cerr << "Label to Block Map" << std::endl;
    // for (auto it : cfg.labelMap)
    // {
    //     std::cerr << it.first << " - " << it.second << std::endl;
    // }

    for(int i = 0; i < irCode.code.size(); i++){
        int whichBlock = cfg.whichBlock(i);
        // This Code will belong to which block
        std::string blockName = indexToBlockMap[whichBlock];

        TAC_Quadruple currIR = irCode.code[i];

        // We can make changes in the currentIR
        std::string op = currIR.op;

        // Ignoring psudo IR - like Function Extry & Exit
        // if(op == FUNCTION_EXIT){
        //     continue;
        //     // Ignoring this
        // }

        // changing goto label to block name
        if (op == GOTO_LABEL || op == IF_TRUE || op == IF_FALSE || op == GOTO_EQUAL)
        {
            int targetIndex = std::stoi(currIR.result);
            std::string newBlockLable;
            if (indexToBlockMap.find(targetIndex) != indexToBlockMap.end())
            {
                newBlockLable = indexToBlockMap[targetIndex];
                std::cerr << "Goto Label Change from " << currIR.result << " to " << newBlockLable << std::endl;
                currIR.result = newBlockLable;
            }
            else{
                // Something Wrong, The target labels must be Leaders
                std::cerr << "Error in Goto Label - Target not found" << std::endl;
            }

        }


        cfg.blocks[cfg.labelMap[blockName]].irCode.push_back(currIR);
    }

    BasicBlock exitBlock;
    exitBlock.label = "EXIT";
    cfg.blocks.push_back(exitBlock);


    // Step 3. Create the edges
    // We scan the IRCode and MakeEdges

    // Link Entry
    cfg.addEdge("ENTRY", "main");

    // Return From Points in Functions
    std::map<std::string, std::vector<std::string>> functionReturnFrom;
    std::string currFunction = "NULL";
    for(int i = 0; i< irCode.code.size(); i++){
        std::string op = irCode.code[i].op;

        if (op == FUNCTION_ENTRY)
        {
            currFunction = irCode.code[i].result;
        }

        if(op == RETURN_FUNCTION){
            // We need to store the return point
            int fromIndex = cfg.whichBlock(i);
            if(functionReturnFrom.find(currFunction) == functionReturnFrom.end()){
                functionReturnFrom[currFunction] = std::vector<std::string>();
                functionReturnFrom[currFunction].push_back(indexToBlockMap[fromIndex]);
            }
            else{
                functionReturnFrom[currFunction].push_back(indexToBlockMap[fromIndex]);
            }
        }

        if (op == FUNCTION_EXIT)
        {
            if(functionReturnFrom.find(currFunction) == functionReturnFrom.end()){
                functionReturnFrom[currFunction] = std::vector<std::string>();
                functionReturnFrom[currFunction].push_back(indexToBlockMap[cfg.whichBlock(i)]);
            }
            // Else not need
        }
    }

    std::cerr << "Function Return Points" << std::endl;
    for(auto it : functionReturnFrom){
        std::cerr << "ForFunction : " << it.first << " has return points -";
        for (auto jt : it.second)
        {
            std::cerr << " " << jt;
        }
        std::cerr << std::endl;
    }

    // Now we will add edges to all the blocks
    for (int i = 0; i < irCode.code.size(); i++)
    {
        std::string op = irCode.code[i].op;
        if (op == IF_FALSE || op == IF_TRUE || op == GOTO_LABEL || op == GOTO_EQUAL)
        {
            int fromIndex = cfg.whichBlock(i);
            std::string fromBlock = indexToBlockMap[fromIndex];

            int toIndex = std::stoi(irCode.code[i].result);
            std::string toBlock = indexToBlockMap[toIndex];
            cfg.addEdge(fromBlock, toBlock);

            CERR << "Edge " << fromBlock << " -> " << toBlock << std::endl;

            if(op == IF_FALSE || op == IF_TRUE){
                // Attack the Next Block as well
            }

        }
        else if (op == CALL)
        {
            int fromIndex = cfg.whichBlock(i);
            std::string fromBlock = indexToBlockMap[fromIndex];
            std::string toBlock = irCode.code[i].arg1;

            
            cfg.addEdge(fromBlock, toBlock);
            CERR << "FCall Edge " << fromBlock << " -> " << toBlock << std::endl;

            int returnIndex = cfg.whichBlock(i+1);
            std::cerr << "Func called from " << fromIndex << " return block " << returnIndex << std::endl;
            std::string returnBlock = indexToBlockMap[returnIndex];
            // All Possible fromReturn points are in functionReturnFrom
            if(functionReturnFrom.find(toBlock) != functionReturnFrom.end()){
                std::vector<std::string> returnPoints = functionReturnFrom[toBlock];
                for(auto it : returnPoints){
                    cfg.addEdge(it, returnBlock);
                    CERR << "FCall Edge " << returnBlock << " -> " << it << std::endl;
                }
            }
            else{
                cfg.addEdge(returnBlock, "EXIT");
                CERR << "FCall Edge " << returnBlock << " -> EXIT" << std::endl;
            }
        }
        else{
            int fromIndex = cfg.whichBlock(i);
            int toIndex = cfg.whichBlock(i + 1);

            if(fromIndex != toIndex){
                std::cerr << "Trivial Connecting" << i << " & " << i + 1 << std::endl;
                std::cerr << "Edge " << fromIndex << " -> " << toIndex << std::endl;
                std::string fromBlock = indexToBlockMap[fromIndex];
                std::string toBlock = indexToBlockMap[toIndex];
                cfg.addEdge(fromBlock, toBlock);
            }
        }
    }

    // Handle Return from points of main
    for(auto it : functionReturnFrom["main"]){
        cfg.addEdge(it, "EXIT");
        CERR << "Main Edge " << it << " -> EXIT" << std::endl;
    }

    return OKAY;
}


//=====================[ RISC-V Code Generation ]=========================================================================================

int generatingRISCVCode(CFG &cfg, RISCV_CODE &riscvCode)
{
    // This will generate RISC-V code for each basic block

    // Step 1. Add all ALLOCATE to SymTable with OFFSET & SIZE



    
    // Step 2. Generate RISC-V code for each block


    return OKAY;
}



//======================[ Register Allocation ]=========================================================================================

int getRegister(const std::vector<std::string> &varNames, std::vector<int> &regNos);

//======================[ SymbTable Code ]=========================================================================================

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

