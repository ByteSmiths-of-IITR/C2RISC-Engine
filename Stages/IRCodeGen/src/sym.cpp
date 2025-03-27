#include "sym.h"

int MEMORY_MONITORING = 0;

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

#define debug std::cerr

std::string lastFuncCalled = "";

//--------------- SymbolNode ---------------------------------------------------------------------------------------
void SymbolNode::deleteCurrent(){

    lastFuncCalled = "SymbolNode::deleteCurrent";
    SymbolNode *tempn = this->next;
    SymbolNode *tempp = this->prev;

    if(tempp){
        tempp->next = tempn;
    }
    if(tempn){
        tempn->prev = tempp;
    }

    delete this;
}

void SymbolNode::insertAfter(SymbolNode *node){

    lastFuncCalled = "SymbolNode::insertAfter";

    if(this->next){
        this->next->prev = node;
    }
    node->next = this->next;
    node->prev = this;
    this->next = node;
}

void SymbolNode::insertBefore(SymbolNode *node){

    lastFuncCalled = "SymbolNode::insertBefore";

    if(this->prev){
        this->prev->next = node;
    }
    node->prev = this->prev;
    node->next = this;
    this->prev = node;
}

//--------------- SymbolTable --------------------------------------------------------------------------------------

int SymbolTable::enterScope(){
    
    lastFuncCalled = "SymbolTable::enterScope";

    this->lastScopeNo.push(this->scopeNo);
    this->scopeNo = this->nextScopeNo++;

    // Inserting the scope bottom
    int size = this->listStack.size();
    this->scopeBottom.push(size); // This will keep the index of the bottom of the scope in the symbolStack

    return this->scopeNo;    
}

void SymbolTable::exitScope(){

    lastFuncCalled = "SymbolTable::exitScope";

    // Deleting the symbols of the current scope
    int size = this->listStack.size();
    debug << "Size: " << size << std::endl;
    int bottom;
    if(this->scopeBottom.empty()){
        debug << "No Scope to exit\n";
        return;
    }else{
        bottom = this->scopeBottom.top();
        this->scopeBottom.pop();
        debug << "Bottom: " << bottom << std::endl;
    }

    while(size > bottom){
        SymbolNode *node = this->listStack.top();
        this->listStack.pop();
        
        // Delete the GenericSymbol in the node
        // [📍 ToDo]

        // Deleting the node 
        node->deleteCurrent(); // This will delete the node and update the list
        size--;
        this->NodeCount--;
    }

    debug << "Size after: " << size << std::endl;

    // Restoring the scope number
    this->scopeNo = this->lastScopeNo.top();
    this->lastScopeNo.pop();
}

int SymbolTable::insert(const std::string &key, GenericSymbol *symbol){
    
    lastFuncCalled = "SymbolTable::insert";

    // Checking if the symbol is already present

    GenericSymbol *temp;

    int status = 0;
    // 0 - not present
    // -1 - present in the current scope
    // 1 - present in the outer scope

    if(lookup(key, temp) == 0){
        // Symbol is Present 

        // Checking if the symbol is in the current scope [We can't insert it]
        if(temp->scopeNo == this->scopeNo){
            std::cerr << "Error: Symbol is already present in the current scope\n";
            return -1;
        }
        status = 1;
        // Symbol is present in the outer scope [We can insert it]
    }

    // Symbol is not present or present in the outer scope [We can insert it]

    // Filling Some Information in the SymbolNode
    if(!symbol){
        std::cerr << "Error: Symbol is nullptr\n";
        return -1;
    }

    // symbol->symbolName = key; [WE can't set this here, since records have a different key and name] 
    // The name of symbol will be filled by the caller
    symbol->scopeNo = this->scopeNo;
    // symbol->location [we can't know here]

    // Creating a new SymbolNode
    SymbolNode *node = new SymbolNode();
    node->symbol = symbol;

    SymbolNode *head;

    // head is just a dummy node

    if(status==1){
        // Symbol is present in the outer scope
        head = this->symTable[key]; // won't give segmentation fault
        if(!head){
            std::cerr << "Error: Symbol is present in the outer scope but head is nullptr\n";
            // This should not happen
            return -1;
        }

        // Insert at the beginning
        head->insertAfter(node);
    }else{
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

    return 0;
}

int SymbolTable::lookup(const std::string &key, GenericSymbol *&sym){

    lastFuncCalled = "SymbolTable::lookup";

    if(!this->symTable.count(key)){
        return -1;
    }

    SymbolNode *head = this->symTable[key];

    if(!head){
        return -1;
    }

    SymbolNode *node = head->next;
    if(!node){
        return -1; // This would happen if node is deleted
    }

    sym = node->symbol;
    return 0;
}

int SymbolTable::lookupNode(const std::string &key, SymbolNode *&node){

    lastFuncCalled = "SymbolTable::lookupNode";

    if(!this->symTable.count(key)){
        return -1;
    }
    // This will return the first node of that key

    SymbolNode *head = this->symTable[key];
    if(!head){
        return -1;
    }

    SymbolNode *temp = head->next;
    if(!temp){
        return -1; // This would happen if node is deleted
    }

    node = temp;
    return 0;
}

SymbolTable::~SymbolTable(){

    lastFuncCalled = "SymbolTable::~SymbolTable";

    // CleanUp Code [📍 ToDo]
    for(auto &pair : this->symTable){
        SymbolNode *node = pair.second;
        while(node){
            SymbolNode *temp = node;
            node = node->next;
            delete temp;
        }
    }
    MEM("SymbolTable Destructor");
}

//------- Check Derived Classes -------------------------------------------------------------------

bool isVarSymbols(const GenericSymbol &sym){
    return dynamic_cast<const VarSymbols*>(&sym);
}

bool isUserDType(const GenericSymbol &sym){
    return dynamic_cast<const UserDType*>(&sym);
}

//------- Check LevelInfo Derived Classes --------------------------------------------------------

bool isArrayInfo(const LevelInfo& info){
    return dynamic_cast<const ArrayInfo*>(&info);
}

// bool isArrayInfo(const LevelInfo* info){
//     return dynamic_cast<const ArrayInfo*>(info);
// }

bool isPointerInfo(const LevelInfo &info){
    return dynamic_cast<const PointerInfo*>(&info);
}

// bool isPointerInfo(const LevelInfo* info){
//     return dynamic_cast<const PointerInfo*>(info);
// }

bool isBaseInfo(const LevelInfo &info){
    return dynamic_cast<const BaseInfo*>(&info);
}

// bool isBaseInfo(const LevelInfo* info){
//     return dynamic_cast<const BaseInfo*>(info);
// }

//------- Check GenericSymbol Derived Classes --------------------------------------------------------

bool isVariable(const GenericSymbol &sym){
    return dynamic_cast<const Variable*>(&sym);
}

bool isFunction(const GenericSymbol &sym){
    return dynamic_cast<const Function*>(&sym);
}

bool isEnumConstant(const GenericSymbol &sym){
    return dynamic_cast<const EnumConstant*>(&sym);
}


// Print the SymbolTable

void SymbolTable::printTable(std::ofstream &file){

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
    while(!temp.empty()){
        file << temp.top() << " ";
        temp.pop();
    }
    file << std::endl;

    for(auto &pair : this->symTable){
        std::string key = pair.first;
        SymbolNode *head = pair.second;

        if(!head){
            continue;
        }

        SymbolNode *node = head->next;
        if(!node){
            continue;
        }
        file << "----------- " << key << " -----------\n";
        while(node){
            if(node->symbol){
                file << "Scope No: " << node->symbol->scopeNo << " | Name: " << node->symbol->symbolName ;
            }
            node = node->next;
        }
        file << "---------------------------------\n";
    }

    // file << "~~~~~~~~~~~~~~~~~~~~~~~ End of Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n\n";

}

//===========[ DType Utilities ]====================

int width(const BaseInfo &info){
    // This will depend on stding baseType
    // [📍 ToDo]
    /*Also need to handle the case of enum, struct, union*/
    return 0;
}

int width(const DType &type){
    
    // It has levels, so need to consider that as well
    int size = 0;

    std::stack<LevelInfo*> temp = type.levels;
    bool baseFlag = false;
    while(!temp.empty()){
        LevelInfo* info = temp.top();
        temp.pop();

        if(isArrayInfo(*info)){
            ArrayInfo* arr = dynamic_cast<ArrayInfo*>(info);
            size *= arr->dimSize;
        }
        else if (isPointerInfo(*info))
        {
            size = ADDRESS_SIZE;
        }
        else if (isBaseInfo(*info))
        {
            if(!temp.empty()){
                std::cerr << "Error: BaseInfo should be the last level\n";
                return -1;
            }
            baseFlag = true;
            BaseInfo* base = dynamic_cast<BaseInfo*>(info);
            size *= width(*base);
        }
    }

    if(!baseFlag){
        std::cerr << "Error: BaseInfo not found\n";
        return -1;
    }

    return size;
}

std::string toString(const DType &dtype){
    // This will return the string representation of the data type
    // [📍 ToDo]
    return "";
}

int popALevel(DType &dtype){
    // First we check if top level is popable or not
    if(dtype.levels.empty()){
        std::cerr << "Error: No Level to pop\n";
        return EXIT_FAILURE;
    }
    if(isBaseInfo(*dtype.levels.top())){
        std::cerr << "Error: BaseInfo can't be popped | TopLevel must be a Pointer or Array\n";
        return EXIT_FAILURE;
    }

    dtype.levels.pop();
    return EXIT_SUCCESS;
}

//===========[ TypeExpression Utilities ]====================
std::string toString(const TypeExpression &typeExpr){
    // This will return the string representation of the type expression
    // [📍 ToDo]
    return "";
}

int popALevel(TypeExpression &typeExpr){
    // First we check if top level is popable or not
    return popALevel(typeExpr.dtype);
}

int width(const TypeExpression &typeExpr){
    // This will return the width of the returnType of the function
    return width(typeExpr.dtype);
}

//===========[ UserDType Utilities ]====================
int width(const UserDType &dtype){
    // This will return the width of the user defined data type
    // [📍 ToDo]
    return 0;
}

std::string toString(const UserDType &dtype){
    // This will return the string representation of the user defined data type
    // [📍 ToDo] = Make sure to have scopeNo in string as well
    return "";
}

//============ [lookup in given scope] =================
int SymbolTable::lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo){
    
    lastFuncCalled = "SymbolTable::lookup_scope";

    if(!this->symTable.count(key)){
        return -1;
    }

    SymbolNode *head = this->symTable[key];

    if(!head){
        return -1;
    }

    SymbolNode *node = head->next;
    if(!node){
        return -1; // This would happen if node is deleted
    }

    while(node){
        if(node->symbol->scopeNo == lookInScopeNo){
            sym = node->symbol;
            return 0;
        }
        node = node->next;
    }

    return -1;
}


//============= [Record Handling functions of symbol Table] ========================
int SymbolTable::insertRecord(const std::string &key, GenericSymbol *symbol){

    std::string newKey = RECORD_PREFIX + key;
    return this->insert(newKey, symbol);
}

int SymbolTable::lookupRecord(const std::string &key, GenericSymbol *&sym){

    std::string newKey = RECORD_PREFIX + key;
    return this->lookup(newKey, sym);
}

int SymbolTable::lookupRecordNode(const std::string &key, SymbolNode *&node){

    std::string newKey = RECORD_PREFIX + key;
    return this->lookupNode(newKey, node);
}



/* This is NOT NEEDED
//============= [AllSymbolTable] ========================
int AllSymbolTable::enterScope(){
    
    lastFuncCalled = "AllSymbolTable::enterScope";

    int varScope = this->varTable.enterScope();
    int recordScope = this->recordTable.enterScope();

    if(varScope == recordScope){
        return varScope; 
    }

    // Should not happen
    std::cerr << "Error: Scope Number Mismatch\n";
    return -1;
}

void AllSymbolTable::exitScope(){

    lastFuncCalled = "AllSymbolTable::exitScope";

    this->varTable.exitScope();
    this->recordTable.exitScope();
}

int AllSymbolTable::insert(const std::string &key, GenericSymbol *symbol){
    
    lastFuncCalled = "AllSymbolTable::insert";

    return this->varTable.insert(key, symbol);
}

int AllSymbolTable::insertRecord(const std::string &key, GenericSymbol *symbol){
    
    lastFuncCalled = "AllSymbolTable::insertRecord";

    return this->recordTable.insert(key, symbol);
}

int AllSymbolTable::lookup(const std::string &key, GenericSymbol *&sym){
    
    lastFuncCalled = "AllSymbolTable::lookup";

    if(this->varTable.lookup(key, sym) == 0){
        return 0;
    }

    return this->recordTable.lookup(key, sym);
}

int AllSymbolTable::lookupRecord(const std::string &key, GenericSymbol *&sym){
    
    lastFuncCalled = "AllSymbolTable::lookupRecord";

    return this->recordTable.lookup(key, sym);
}

int AllSymbolTable::lookup(const std::string &key, GenericSymbol *&sym, int lookInScopeNo){
    
    lastFuncCalled = "AllSymbolTable::lookup_scope";

    if(this->varTable.lookup(key, sym, lookInScopeNo) == 0){
        return 0;
    }

    return this->recordTable.lookup(key, sym, lookInScopeNo);
}

int AllSymbolTable::lookupRecord(const std::string &key, GenericSymbol *&sym, int lookInScopeNo){
    
    lastFuncCalled = "AllSymbolTable::lookupRecord_scope";

    return this->recordTable.lookup(key, sym, lookInScopeNo);
}

void AllSymbolTable::printTable(std::ofstream &file){
    
    lastFuncCalled = "AllSymbolTable::printTable";

    file << "~~~~~~~~~~~~~~~~~~~~~~~ All Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n";

    this->printVarTable(file);
    this->printRecordTable(file);

    file << "~~~~~~~~~~~~~~~~~~~~~~~ End of All Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void AllSymbolTable::printVarTable(std::ofstream &file){
    
    lastFuncCalled = "AllSymbolTable::printVarTable";

    file << "~~~~~~~~~~~~~~~~~~~~~~~ Variable Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n";
    this->varTable.printTable(file);
    file << "~~~~~~~~~~~~~~~~~~~~~~~ End of Variable Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void AllSymbolTable::printRecordTable(std::ofstream &file){
    
    lastFuncCalled = "AllSymbolTable::printRecordTable";

    file << "~~~~~~~~~~~~~~~~~~~~~~~ Record Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n";
    this->recordTable.printTable(file);
    file << "~~~~~~~~~~~~~~~~~~~~~~~ End of Record Symbol Table ~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

int AllSymbolTable::lookupVarNode(const std::string &key, SymbolNode *&node){
    
    lastFuncCalled = "AllSymbolTable::lookupNode";

    return this->varTable.lookupNode(key, node);
}

int AllSymbolTable::lookupRecordNode(const std::string &key, SymbolNode *&node){
    
    lastFuncCalled = "AllSymbolTable::lookupRecordNode";

    return this->recordTable.lookupNode(key, node);
}
*/

//=======================================================================================================================================================
