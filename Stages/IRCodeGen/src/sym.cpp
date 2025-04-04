#include "header.h"

extern std::string lastFuncCalled;

//--------------- SymbolNode ---------------------------------------------------------------------------------------
void SymbolNode::deleteCurrent()
{

    lastFuncCalled = "SymbolNode::deleteCurrent";
    SymbolNode *tempn = this->next;
    SymbolNode *tempp = this->prev;

    if (tempp)
    {
        tempp->next = tempn;
    }
    if (tempn)
    {
        tempn->prev = tempp;
    }

    delete this;
}

void SymbolNode::insertAfter(SymbolNode *node)
{

    // lastFuncCalled = "SymbolNode::insertAfter";

    if (this->next)
    {
        this->next->prev = node;
    }
    node->next = this->next;
    node->prev = this;
    this->next = node;
}

void SymbolNode::insertBefore(SymbolNode *node)
{

    // lastFuncCalled = "SymbolNode::insertBefore";

    if (this->prev)
    {
        this->prev->next = node;
    }
    node->prev = this->prev;
    node->next = this;
    this->prev = node;
}

//================[ SymTable - Scope + general + print ]=================================================================================================

int SymbolTable::getGlobaScopeNo()
{
    return this->globalScope;
}

int SymbolTable::earlyEntry(){
    if(this->wasEarlyEntered){
        // it's true // So why called again
        CERR << "Error: Twice EarlyEntry is already true\n";
        return -1;
    }
    
    // it's false // So we can set it to true
    CERR << "Info: earlyEntry is set to true\n";
    // call the enterScope
    int k = this->enterScope();
    this->wasEarlyEntered = true;
    return k;
}

int NO_EXIT = -10;
int IGNORED = -20;

int SymbolTable::earlyExit(){
    // If it's true - So we need to exit
    this->wasEarlyEntered = false; // set it to false
    return (this->exitScope());
}

int SymbolTable::enterScope()
{
    if(wasEarlyEntered){
        // Ignore this enter
        wasEarlyEntered = false; // set it to false
        return IGNORED;
    }

    if(globalScope == -100){
        globalScope = this->nextScopeNo;
    }

    lastFuncCalled = "SymbolTable::enterScope";

    this->lastScopeNo.push(this->scopeNo);
    this->scopeNo = this->nextScopeNo++;

    // Inserting the scope bottom
    int size = this->listStack.size();
    this->scopeBottom.push(size); // This will keep the index of the bottom of the scope in the symbolStack

    return this->scopeNo;
}

int SymbolTable::exitScope()
{

    // lastFuncCalled = "SymbolTable::exitScope";

    int exitedScopeNo = this->scopeNo;

    // Deleting the symbols of the current scope
    int size = this->listStack.size();
    debug << "Size: " << size << std::endl;
    int bottom;
    if (this->scopeBottom.empty())
    {
        debug << "No Scope to exit\n";
        return -1;
    }
    else
    {
        bottom = this->scopeBottom.top();
        this->scopeBottom.pop();
    }

    while (size > bottom)
    {
        SymbolNode *node = this->listStack.top();
        this->listStack.pop();

        // Delete the GenericSymbol in the node
        // [📍 ToDo]

        // Deleting the node
        node->deleteCurrent(); // This will delete the node and update the list
        size--;
        this->NodeCount--;
    }

    // Restoring the scope number
    this->scopeNo = this->lastScopeNo.top();
    this->lastScopeNo.pop();
    // Returning the exited scope number
    return exitedScopeNo;
}

int SymbolTable::insert(SYMBOL_TYPE symbolType, const std::string &key, GenericSymbol *symbol)
{

    // lastFuncCalled = "SymbolTable::insert";

    // Checking if the symbol is already present

    GenericSymbol *temp;

    int status = 0;
    // 0 - not present
    // -1 - present in the current scope
    // 1 - present in the outer scope

    if (lookup(key, temp) == 0)
    {
        // Symbol is Present

        // Checking if the symbol is in the current scope [We can't insert it]
        if (temp->scopeNo == this->scopeNo)
        {
            std::cerr << "Error: Symbol is already present in the current scope\n";
            return INSERT_FAILURE;
        }
        status = 1;
        // Symbol is present in the outer scope [We can insert it]
    }

    // Symbol is not present or present in the outer scope [We can insert it]

    // Filling Some Information in the SymbolNode
    if (!symbol)
    {
        std::cerr << "Error: Symbol is nullptr\n";
        return BUG;
    }

    symbol->symbolType = symbolType;

    // symbol->symbolName = key; [WE can't set this here, since records have a different key and name]
    // The name of symbol will be filled by the caller
    symbol->scopeNo = this->scopeNo;
    // symbol->location [we can't know here]

    // Creating a new SymbolNode
    SymbolNode *node = new SymbolNode();
    node->symbol = symbol;

    SymbolNode *head;

    // head is just a dummy node

    if (status == 1)
    {
        // Symbol is present in the outer scope
        head = this->symTable[key]; // won't give segmentation fault
        if (!head)
        {
            std::cerr << "Error: Symbol is present in the outer scope but head is nullptr\n";
            // This should not happen
            return BUG;
        }

        // Insert at the beginning
        head->insertAfter(node);
    }
    else
    {
        // Creating a new dummy node
        head = new SymbolNode();
        node->prev = NULL;
        head->symbol = NULL; // This is a dummy node
        this->symTable[key] = head;

        // Insert at the beginning
        head->insertAfter(node);

        // Inserting the head in the listStack
        // this->listStack.push(head);
        /* If we do this during exit of scope, the head will
        be deleted but the symTable will still have the key
        and will be pointing to the deleted head. So, we
        will have to delete the head in the destructor of
        SymbolTable
        */
    }

    // Insert the node in the listStack
    this->listStack.push(node);

    // Incrementing the NodeCount
    this->NodeCount++;

    if (status == 0)
    {
        return INSERT_SUCCESS;
    }
    return INSERT_SUCCESS_WITH_WARNING; // status = 1;
}

int SymbolTable::lookup(const std::string &key, GenericSymbol *&sym)
{

    // lastFuncCalled = "SymbolTable::lookup";

    if (!this->symTable.count(key))
    {
        return LOOKUP_FAILURE;
    }

    SymbolNode *head = this->symTable[key];

    if (!head)
    {
        compilerLOG.push_back("If symbolKey is present, then head should not be nullptr");
    }

    SymbolNode *node = head->next;
    if (!node)
    {
        return LOOKUP_FAILURE; // This would happen if symbol was deleted
    }

    sym = node->symbol;
    return LOOKUP_SUCCESS;
}

int SymbolTable::lookupNode(const std::string &key, SymbolNode *&node)
{

    // lastFuncCalled = "SymbolTable::lookupNode";

    if (!this->symTable.count(key))
    {
        return LOOKUP_FAILURE;
    }
    // This will return the first node of that key

    SymbolNode *head = this->symTable[key];
    if (!head)
    {
        return LOOKUP_FAILURE;
    }

    SymbolNode *temp = head->next;
    if (!temp)
    {
        return BUG; // This would happen if node is deleted
    }

    node = temp;
    return LOOKUP_SUCCESS;
}

SymbolTable::~SymbolTable()
{

    lastFuncCalled = "SymbolTable::~SymbolTable";

    // CleanUp Code [📍 ToDo]
    for (auto &pair : this->symTable)
    {
        SymbolNode *node = pair.second;
        while (node)
        {
            SymbolNode *temp = node;
            node = node->next;
            delete temp;
        }
    }
    MEM("SymbolTable Destructor");
}

// Print the SymbolTable

void SymbolTable::printTable(std::ofstream &file)
{

    lastFuncCalled = "SymbolTable::printTable";

    // file << "~~~~~~~~~~~~~~~~~~~~~~~ Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n";

    // Table Variables
    file << "Scope No: " << this->scopeNo << std::endl;
    file << "Next Scope No: " << this->nextScopeNo << std::endl;
    file << "Node Count: " << this->NodeCount << std::endl;
    file << "Bottom of Scope Stack: " << (this->scopeBottom.empty() ? -1 : this->scopeBottom.top()) << std::endl;

    // Print Scope Stack
    file << "Scope Stack: ";
    std::stack<int> temp = this->lastScopeNo;
    file << this->scopeNo << " ";
    while (!temp.empty())
    {
        file << temp.top() << " ";
        temp.pop();
    }
    file << std::endl;

    for (auto &pair : this->symTable)
    {
        std::string key = pair.first;
        SymbolNode *head = pair.second;

        if (!head)
        {
            continue;
        }

        SymbolNode *node = head->next;
        if (!node)
        {
            continue;
        }
        file << "----------- " << key << " -----------\n";
        while (node)
        {
            if (node->symbol)
            {
                file << "Scope No: " << node->symbol->scopeNo << " | Name: " << node->symbol->symbolName;
            }
            node = node->next;
        }
        file << "---------------------------------\n";
    }

    // file << "~~~~~~~~~~~~~~~~~~~~~~~ End of Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

//================= [Record Functions] ===================================================================================================

int SymbolTable::insertRecord(const std::string &key, GenericSymbol *symbol)
{

    std::string newKey = RECORD_PREFIX + key;
    return this->insert(SYMBOL_TYPE::USER_DTYPE, newKey, symbol);
}

int SymbolTable::lookupRecord(const std::string &key, GenericSymbol *&sym)
{

    std::string newKey = RECORD_PREFIX + key;
    return this->lookup(newKey, sym);
}

int SymbolTable::lookupRecordNode(const std::string &key, SymbolNode *&node)
{

    std::string newKey = RECORD_PREFIX + key;
    return this->lookupNode(newKey, node);
}

//=====================[ ScopeLookUps ]=========================================================================================

int SymbolTable::lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo)
{

    lastFuncCalled = "SymbolTable::lookup_scope";

    if (!this->symTable.count(key))
    {
        return -1;
    }

    SymbolNode *head = this->symTable[key];

    if (!head)
    {
        return -1;
    }

    SymbolNode *node = head->next;
    if (!node)
    {
        return -1; // This would happen if node is deleted
    }

    while (node)
    {
        if (node->symbol->scopeNo == lookInScopeNo)
        {
            sym = node->symbol;
            return 0;
        }
        node = node->next;
    }

    return -1;
}

int SymbolTable::lookupRecord(const std::string &key, GenericSymbol *&sym, int lookInScopeNo)
{

    std::string newKey = RECORD_PREFIX + key;
    return this->lookup(newKey, sym, lookInScopeNo);
}

void SymbolTable::setScopeName(const std::string &scopeName)
{
    this->currnetScope = scopeName;
}

std::string GLOBAL_SCOPE = "Global";
std::string LOCAL_SCOPE = "Local";


std::string SymbolTable::getScopeName()
{
    return this->currnetScope;
}

//=====================[ SymbolTable Utilities ]=========================================================================================

bool isVariable(const GenericSymbol &sym)
{
    return (sym.symbolType == SYMBOL_TYPE::VARIABLE);
}

bool isFunction(const GenericSymbol &sym)
{
    return (sym.symbolType == SYMBOL_TYPE::FUNCTION);
}

bool isEnumConstant(const GenericSymbol &sym)
{
    return (sym.symbolType == SYMBOL_TYPE::ENUM_CONSTANT);
}

bool isUserDType(const GenericSymbol &sym)
{
    return (sym.symbolType == SYMBOL_TYPE::USER_DTYPE);
}

bool isTypeDefs(const GenericSymbol &sym)
{
    return (sym.symbolType == SYMBOL_TYPE::TYPEDEF);
}

std::string newRecordName()
{
    static int recordCount = 0;
    std::string recordName = "UnNamedRecord" + std::to_string(recordCount);
    recordCount++;
    return recordName;
}
