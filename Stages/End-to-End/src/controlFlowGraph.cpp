#include "header.h"
#include "utility.h"

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

    if (edges.find(from) == edges.end())
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
        for (auto toBlock : edge.second)
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
    for (size_t i = 0; i < leaders.size(); i++)
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

std::string CFG::blockName(int index)
{
    int leaderIndex = whichBlock(index);
    if (leaderToBlockMap.find(leaderIndex) != leaderToBlockMap.end())
    {
        return leaderToBlockMap[leaderIndex];
    }
    return NO_BLOCK;
}

int CFG::addLeader(int leader)
{
    // This will create a Leader
    if(leaderToBlockMap.find(leader) != leaderToBlockMap.end())
    {
        // Leader already exists
        return OKAY; // Already Exists
    }
    std::string newBLockName = newBlock();
    leaderToBlockMap[leader] = newBLockName;
    leaders.push_back(leader);
    return 0;
}

bool CFG::isALeader(int index)
{
    // This will check if the index is a leader
    if (leaderToBlockMap.find(index) != leaderToBlockMap.end())
    {
        return true;
    }
    return false;
}


int CFG::addLeader(int leader, std::string blockName)
{
    if(leaderToBlockMap.find(leader) != leaderToBlockMap.end())
    {
        // Leader already exists
        return OKAY; // Already Exists
    }
    leaderToBlockMap[leader] = blockName;
    leaders.push_back(leader);
    return OKAY;
}

void CFG::sortLeaders()
{
    sort(leaders.begin(), leaders.end());
}

int CFG::addEdge(int from, int to)
{
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

int CFG::attachLiveInfoToLine(int atLine)
{
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
    if (it == blocks[name].irCode.code.end())
    {
        CERR << "Error in attachLiveInfoToLine - atLine not found" << std::endl;
        return FAIL;
    }
    it->second.VarInfo = info;
    return OKAY;
}
