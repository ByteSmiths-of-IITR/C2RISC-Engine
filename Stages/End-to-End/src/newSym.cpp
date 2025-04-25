#include "header.h"
#include "utility.h"

//======================[ SymbTable Offset+Function Code ]=========================================================================================

bool isASymbol(const std::string &name)
{
    // std::cerr << "Checking if " << name << " is a symbol" << std::endl;
    if (SYM_RECORD.symTable.find(name) != SYM_RECORD.symTable.end())
    {
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
