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

bool isASymbol(const std::string &name)
{
    // std::cerr << "Checking if " << name << " is a symbol" << std::endl;
    if (SYM_RECORD.symTable.find(name) != SYM_RECORD.symTable.end())
    {
        // Search if $ is present
        for (int i = 0; i < name.size(); i++)
        {
            if (name[i] == '$')
            {
                // It's A Variable (local, global, or compilerTemp)
                return true;
            }
        }

        return false; // It's a function Name (would be a label) [would need special care]
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

    // Set offset as size of return value
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