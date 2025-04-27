#include "header.h"
#include "utility.h"

//======================[ SymbTable Offset+Function Code ]=========================================================================================

bool isALabel(const std::string &label)
{
    // This will check if the label is a leader or not
    if(CFG_CODE.blocks.find(label) != CFG_CODE.blocks.end()){
        return true;
    }
    return false;
}

bool isAValueSymbol(const std::string &name)
{
    // std::cerr << "Checking if " << name << " is a symbol" << std::endl;
    bool res = false;
    auto it = SYM_RECORD.symTable.find(name);
    if (it != SYM_RECORD.symTable.end())
    { 

        // Search if $ is present
        for (int i = 0; i < name.size(); i++)
        {
            if (name[i] == '$')
            {
                // It's A Variable (local, global, or compilerTemp)
                res = true;
            }
        }
    }
    // CERR << "Variable " << name << (res ? " is a value symbol 👌 " : " is NOT a value symbol ❌") << std::endl;
    return res;
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

bool SymTable::isInAddressSpace(const std::string &key)
{
    // This will return the isGlobal of the key
    if (symTable.find(key) == symTable.end())
    {
        return false;
    }

    return symTable[key].inAddressSpace;
}

bool SymTable::isFloat(const std::string &key)
{
    // TODO
    return false;
}

int SymTable::enterFunction(const std::string &funcName)
{
    // This will enter the function and set the offset
    if (inFunction)
    {
        CERR << "Error in entering function - already in function" << std::endl;
        return FAIL;
    }

    // We have Entered a function, so we need to set the offset
    inFunction = true;
    functionName = funcName;
    stack_offset = activation_start_offset; // This will set the offset of the function

    // Create a Symbol to be used for adding activation record [storage Details]
    SymInfo funcSymbol;
    funcSymbol.size = 4;
    funcSymbol.isGlobal = false; // Function is Global
    funcSymbol.whichFunction = this->functionName; // This will set the function name
    funcSymbol.offset; // to be set

    std::string funcFP = funcName + "$FP(fp)"; // This will be used to set the frame pointer
    std::string funcRA = funcName + "$RA(ra)"; // This will be used to set the return address
    funcSymbol.offset = 8; // offset of fp
    symTable[funcFP] = funcSymbol;
    funcSymbol.offset = 4; // offset of ra
    symTable[funcRA] = funcSymbol; // This will set the return address

    std::string addressOfRetValue = funcName + "$RET_VAL_ADDR"; // This will be used to set the return address
    funcSymbol.offset = 12; // offset of return value address
    symTable[addressOfRetValue] = funcSymbol; // This will set the return address

    funcSymbol.offset = 16; // offset of return value
    symTable[funcName+"(un-used)"] = funcSymbol; // This will set the return address

    
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
    this->inFunction = false;
    std::string oldName = this->functionName;
    this->functionName = "GLOBAL";

    // We also need to create a Symbol with name of function
    SymInfo funcSymbol;
    funcSymbol.size = stack_offset;
    funcSymbol.whichFunction = this->functionName; // This will set the function name
    funcSymbol.offset = -1; // offset of return value
    // Set offset as size of return value
    funcSymbol.isGlobal = true;                         // Function is Global
    int check = this->insert(oldName, funcSymbol); // Insert the function in the table
    if (check != INSERT_SUCCESS)
    {
        CERR << "Error in inserting function at exit - already present" << std::endl;
        return FAIL;
    }

    return OKAY;
}

int SymTable::insert(const std::string &key, int size, bool space)
{
    // We are only give size


    // Allignment Logic -> TURNED OFF
    FEATURE_OFF("Alignment Logic");
    // int padding = std::max(0, (4 - size % 4) % 4); // This will be used to set the padding

    SymInfo info;
    info.size = size;
    info.inAddressSpace = space; // This will be used to set the address space
    stack_offset += size;       // This will set the offset of the function
    info.whichFunction = functionName; // This will set the function name
    info.offset = stack_offset; // This will set the offset of the function
    
    // if(padding != 0){
    //     stack_offset += padding;
    //     SymInfo paddingInfo;
    //     paddingInfo.size = padding;
    //     paddingInfo.whichFunction = functionName; // This will set the function name
    //     paddingInfo.offset = stack_offset; // This will set the offset of the function
    //     SYM_RECORD.insert(key+"(padding)", paddingInfo);
    // }

    info.isGlobal = false;      // Function is Global
    return insert(key, info);
}

int SymTable::insertGlobal(const std::string &key, int size, bool space)
{
    // This will insert the key and info in the table
    if (symTable.find(key) != symTable.end())
    {
        return INSERT_FAILURE;
    }


    SymInfo info;
    info.whichFunction = functionName;
    info.size = size;
    info.inAddressSpace = space; // This will be used to set the address space
    info.offset = -1; // no offset for global variables
    info.isGlobal = true;      // Function is Global
    
    symTable[key] = info;
    return INSERT_SUCCESS;
}

void SymTable::printTable(std::ofstream &file)
{
    std::map<std::string, std::vector<std::pair<int,std::string>>> sortedSymTable;
    int maxSize = 20;
    int minSize = 10;
    
    std::string heading = "[ Symbol Table ]";
    file << std::string(20, '=') << heading << std::string(70-heading.size(), '=') << std::endl;
    file << std::string(4, ' ') << std::left << std::setw(maxSize) << "Name" << std::setw(minSize) << "Size" << std::setw(maxSize) << "Offset(w.r.t(fp))" << std::setw(minSize) << "isGlobal" << std::endl;
    
    for(auto it : symTable)
    {
        std::string func = it.second.whichFunction;
        int offset = it.second.offset;
        std::string toPrint;
        std::ostringstream ss;
        std::string offset_str = (it.second.offset == -1) ? "N/A" : ("-"+std::to_string(it.second.offset));
        ss << std::left << std::setw(maxSize) << it.first << std::setw(minSize) << it.second.size << std::setw(maxSize) << offset_str << std::setw(minSize) << (it.second.isGlobal ? "YES" : "NO") << std::endl;
        toPrint = ss.str();

        // Check if the function is already present
        if(sortedSymTable.find(func) == sortedSymTable.end()){
            // This is the first time we are seeing this function
            sortedSymTable[func] = std::vector<std::pair<int,std::string>>();
        }
        // Add the symbol to the function
        sortedSymTable[func].push_back(std::make_pair(offset, toPrint));
    }

    // Now sort the symbols in the function
    for(auto it : sortedSymTable){
        std::string func = it.first;
        std::vector<std::pair<int,std::string>> symbols = it.second;

        // Sort the symbols in the function
        std::sort(symbols.begin(), symbols.end(), [](const std::pair<int,std::string> &a, const std::pair<int,std::string> &b){
            return a.first > b.first;
        });

        // Print the function name
        if(func != "GLOBAL"){
            file << "Activation Record of Function - " << func << std::endl;
        }
        else{
            file << "Global Variables" << std::endl;
        }
        file << std::string(80, '-') << std::endl;
        
        // Print the symbols in the function
        for(auto jt : symbols){
            file << std::string(4, ' ') << jt.second;
        }
        file << std::string(80, '-') << std::endl;
    }

    file << std::string(90, '=') << std::endl;
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


int SymTable::varStoredInWhichReg(const std::string &key)
{
    // This will check if the variable is stored in register or not
    if (symTable.find(key) == symTable.end())
    {
        return FAIL;
    }

    int totalReg = symTable[key].inRegNo.size();
    if (totalReg == 0)
    {
        return -1;
    }

    auto it = symTable[key].inRegNo.begin();
    int regNo = *it;
    return regNo;
}

int SymTable::varStoreInHowManyReg(const std::string &key)
{
    // This will check how many registers the variable is stored in
    if (symTable.find(key) == symTable.end())
    {
        return -1;
    }

    return symTable[key].inRegNo.size();
}

int SymTable::ex_varStoredInWhichReg(const std::string &key)
{
    // This will check if the variable is stored in register or not
    if (symTable.find(key) == symTable.end())
    {
        return -1; // Variable not found [Should not happen]
    }

    for(auto storeInReg : symTable[key].inRegNo){
        // Check on all these if any register is exclusively used
        if(regMap[storeInReg].size() == 1){
            // This is the only variable in this register
            return storeInReg;
        }
    }
    
    // No register is exclusively used
    return -1;
}

int SymTable::addVarInReg(const std::string &key, int regNo)
{
    // This will add the variable to the register
    if (symTable.find(key) == symTable.end())
    {
        return FAIL;
    }

    // Remove this Reg from the free register set
    SetOfFreeReg.erase(regNo); // Remove the register from the free register set

    // Add to regMap
    regMap[regNo].insert(key); // Add the variable to the register

    // Add to AddressMap
    symTable[key].inRegNo.insert(regNo);
    return OKAY;
}

int SymTable::removeVarFromReg(const std::string &key, int regNo)
{
    // This will remove the variable from the register
    if (symTable.find(key) == symTable.end())
    {
        return FAIL;
    }

    // Remove from regMap
    regMap[regNo].erase(key); // Remove the variable from the register

    // Check if the register is empty
    if (regMap[regNo].size() == 0)
    {
        SetOfFreeReg.insert(regNo); // Add the register to the free register set
    }

    // Remove from AddressMap
    symTable[key].inRegNo.erase(regNo);
    return OKAY;
}

int SymTable::removeVarFromAllReg(const std::string &key)
{
    // This will remove the variable from all the registers
    if (symTable.find(key) == symTable.end())
    {
        return FAIL;
    }

    // Remove from regMap
    for (auto it : symTable[key].inRegNo)
    {
        regMap[it].erase(key); // Remove the variable from the register

        if(regMap[it].size() == 0)
        {
            SetOfFreeReg.insert(it); // Add the register to the free register set
        }
    }

    // Remove from AddressMap
    symTable[key].inRegNo.clear();
    return OKAY;
}

int SymTable::variableRest(const std::string &key)
{
    // Just call 
    int check = removeVarFromAllReg(key);
    if (check != OKAY)
    {
        return FAIL;
    }
    check = setNotInMemory(key);
    if (check != OKAY)
    {
        return FAIL;
    }
    return OKAY;
}

int MIN_REGNO = 12;
int MAX_REGNO = 31; // This will be the maximum number of registers

void SymTable::resetRegTable()
{
    // This will initialize the register table
    for (int i = MIN_REGNO; i <= MAX_REGNO; i++)
    {
        SetOfFreeReg.insert(i); // Add the register to the free register set
        regMap[i] = std::set<std::string>(); // Initialize the register map
    }
}


bool SymTable::isFree(int regNo)
{
    // This will check if the register is free or not
    if (SetOfFreeReg.find(regNo) != SetOfFreeReg.end())
    {
        return true;
    }
    return false;
}

bool SymTable::isVarInReg(int regNo, const std::string &varName)
{
    // This will check if the variable is in the register or not
    if (regMap.find(regNo) == regMap.end())
    {
        return FAIL;
    }

    if (regMap[regNo].find(varName) != regMap[regNo].end())
    {
        return OKAY;
    }
    return FAIL;
}

int SymTable::whatIsInReg(int regNo, std::set<std::string> &varName)
{
    // This will get all the variable whose value is in the arg_given register
    if (regMap.find(regNo) == regMap.end())
    {
        return FAIL;
    }

    varName = regMap[regNo]; // Get the variable from the register
    return OKAY;
}

int SymTable::howManyVarInReg(int regNo)
{
    // This will get the number of variables in the register
    if (regMap.find(regNo) == regMap.end())
    {
        return -1;
    }

    return regMap[regNo].size(); // Get the number of variables in the register
}

int SymTable::freeGivenReg(int regNo)
{
    // This will free the given register
    if (regMap.find(regNo) == regMap.end())
    {
        return FAIL;
    }

    SetOfFreeReg.insert(regNo); // Add the register to the free register set
    return OKAY;
}

int SymTable::freeAllReg()
{
    // This will free all the registers

    for (auto it : regMap)
    {
        regMap[it.first].clear(); // Clear the register map
        SetOfFreeReg.insert(it.first); // Add the register to the free register set
    }
    return OKAY;
}

int SymTable::getFreeReg()
{
    // This will get the register for the variable
    if (SetOfFreeReg.size() == 0)
    {
        return FAIL;
    }

    // Get the free register
    int regNo = *SetOfFreeReg.begin();
    SetOfFreeReg.erase(SetOfFreeReg.begin());

    return regNo;
}

void SymTable::printRegTable(std::ofstream &file)
{
    // This will print the register table
    file << "======================[ Register Table ]=========================================================================================" << std::endl;
    file << std::left << std::setw(10) << "RegNo" << std::setw(20) << "Variable" << std::endl;
    file << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
    for (auto it : regMap)
    {
        file << std::left << std::setw(10) << it.first;
        for (auto jt : it.second)
        {
            file << std::left << std::setw(20) << jt;
        }
        if(it.second.size() == 0)
        {
            file << std::left << std::setw(20) << "It's Free 🆓 ";
        }
        file << std::endl;
    }
    file << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
    return;
}