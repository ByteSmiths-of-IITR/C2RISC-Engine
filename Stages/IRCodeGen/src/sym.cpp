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

//===========[ Sub-Level TypeExpression Utilities ]====================

bool isArrayInfo(const LevelInfo &info)
{
    return dynamic_cast<const ArrayInfo *>(&info);
}

bool isPointerInfo(const LevelInfo &info)
{
    return dynamic_cast<const PointerInfo *>(&info);
}

bool isBaseInfo(const LevelInfo &info)
{
    return dynamic_cast<const BaseInfo *>(&info);
}

bool isParameterInfo(const LevelInfo &info)
{
    return dynamic_cast<const ParameterInfo *>(&info);
}

bool isParenthesisInfo(const LevelInfo &info)
{
    return dynamic_cast<const ParenthesisInfo *>(&info);
}

int width(const BaseInfo &info){
    // This will depend on stding baseType
    // [📍 ToDo]
    /*Also need to handle the case of enum, struct, union*/
    return 0;
}

int checkEquivalance(const BaseInfo &info1, const BaseInfo &info2){
    // Convert to string and compare
    if(info1.baseType != info2.baseType){
        return HIGH_ERROR;
    }

    return OKAY;
}

int checkEquivalance(const PointerInfo &info1, const PointerInfo &info2){
    // nothing to check
    return OKAY;
}

int checkEquivalance(const ArrayInfo &info1, const ArrayInfo &info2){
    if(info1.dimSize != info2.dimSize){
        return LOW_ERROR;
    }

    return OKAY;
}

int checkEquivalance(const ParameterInfo &info1, const ParameterInfo &info2){
    if(info1.paramsType.size() != info2.paramsType.size()){
        return HIGH_ERROR;
    }

    for(int i=0; i<info1.paramsType.size(); i++){
        int res = checkEquivalance(info1.paramsType[i], info2.paramsType[i]);
        if(res != OKAY){
            return res;
        }
    }

    return OKAY;
}

int whichLevelInfo(const LevelInfo &info){
    if(isBaseInfo(info)){
        return BASE_LEVEL;
    }else if(isPointerInfo(info)){
        return POINTER_LEVEL;
    }else if(isArrayInfo(info)){
        return ARRAY_LEVEL;
    }else if(isParameterInfo(info)){
        return PARAMETER_LEVEL;
    }else if(isParenthesisInfo(info)){
        return PARENTHESIS_LEVEL;
    }else{
        return UNKNOWN_LEVEL;
    }
}

int checkEquivalance(const LevelInfo &info1, const LevelInfo &info2){
    // This will depend on stding baseType
    
    int type1 = whichLevelInfo(info1);
    int type2 = whichLevelInfo(info2);
    if(type1 != type2){
        return LOW_ERROR;
        // Different levelTypes is Low Error
    }

    if(type1 == BASE_LEVEL){
        // BaseInfo
        const BaseInfo *base1 = dynamic_cast<const BaseInfo*>(&info1);
        const BaseInfo *base2 = dynamic_cast<const BaseInfo*>(&info2);
        return checkEquivalance(*base1, *base2);

    }else if(type1 == POINTER_LEVEL){
        // PointerInfo
        const PointerInfo *ptr1 = dynamic_cast<const PointerInfo*>(&info1);
        const PointerInfo *ptr2 = dynamic_cast<const PointerInfo*>(&info2);
        return checkEquivalance(*ptr1, *ptr2);

    }else if(type1 == ARRAY_LEVEL){
        // ArrayInfo
        const ArrayInfo *arr1 = dynamic_cast<const ArrayInfo*>(&info1);
        const ArrayInfo *arr2 = dynamic_cast<const ArrayInfo*>(&info2);
        return checkEquivalance(*arr1, *arr2);

    }else if(type1 == PARAMETER_LEVEL){
        // ParameterInfo
        const ParameterInfo *param1 = dynamic_cast<const ParameterInfo*>(&info1);
        const ParameterInfo *param2 = dynamic_cast<const ParameterInfo*>(&info2);
        return checkEquivalance(*param1, *param2);

    }else if(type1 == PARENTHESIS_LEVEL){
        // No need to check
        return OKAY;
    }else{
        // Unknown Level
        std::cerr << "Error: Unknown LevelInfo\n";
        return LOW_ERROR;
    }

    return false;
}

//===========[ TypeExpression Utilities ]====================
std::string toString(const TypeExpression &typeExpr){
    TypeExpression temp = typeExpr;
    //First Remove top Parenthesis
    removeTopParenthesis(temp);

    // [📍 ToDo]
    return "";
}

int popALevel(TypeExpression &typeExpr){
    // First Remove top Parenthesis
    removeTopParenthesis(typeExpr);

    if(typeExpr.levelStack.empty()){
        // Nothing to pop
        std::cerr << "Error: TypeExpression is empty\n";
        return -1;
    }
    
    typeExpr.levelStack.pop(); // Pop the top level
    return 0;
}

int width(const TypeExpression &typeExpr){
    TypeExpression temp = typeExpr;
    
    // First Remove top Parenthesis
    removeTopParenthesis(temp);

    int size = 0;
    if (topIsBase(temp))
    {
        BaseInfo *base = dynamic_cast<BaseInfo*>(temp.levelStack.top());
        size = width(*base);
    }
    else if(topIsPointer(temp)){
        size =  ADDRESS_SIZE;
    }else if(topIsArray(temp)){
        ArrayInfo *array = dynamic_cast<ArrayInfo*>(temp.levelStack.top());
        TypeExpression element = temp; popALevel(element);
        size = array->dimSize * width(element);
    }
    else if(topIsParameter(temp)){
        size = 1;
    }else{
        std::cerr << "Error : Something wrong in width(TypeExpression)\n";
        return -1;
    }

    // This will return the width of the type expression
    return size;
}

void removeTopParenthesis(TypeExpression &typeExpr){
    // This will remove only the top parenthesis
    while(topIsParenthesis(typeExpr)){
        typeExpr.levelStack.pop(); // ignore top-parenthesis
    }
}

int checkEquivalance(const TypeExpression &typeExpr1, const TypeExpression &typeExpr2){

    TypeExpression temp1 = typeExpr1;
    TypeExpression temp2 = typeExpr2;

    // Use Recursion to check equivalance
    removeTopParenthesis(temp1);
    removeTopParenthesis(temp2);

    if (isEmpty(temp1) && isEmpty(temp2))
    {
        // Both are empty
        return OKAY;
    }
    if(isEmpty(temp1) ^ isEmpty(temp2)){
        // One is empty and other is not
        // Error
        return LOW_ERROR;
    }

    // Both are not empty

    // Check a level
    LevelInfo *info1 = temp1.levelStack.top();
    LevelInfo *info2 = temp2.levelStack.top();
    if(!info1 || !info2){
        // Should not happen
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    
    int levelcheck = checkEquivalance(*info1, *info2);
    if(levelcheck != OKAY){
        return levelcheck;
    }

    //Current level is OKAY

    // Pop a level
    popALevel(temp1);
    popALevel(temp2);
    // Recursion
    int res = checkEquivalance(temp1, temp2);

    if(res == OKAY || res == WARNING){
        return res; // OKAY or WARNING
    }
    // res == LOW_ERROR [Error from below but can be reduced by higher levels as warning]
    // Depending on current level it will be Error or Warning
    int type1 = whichLevelInfo(*info1);
    int type2 = whichLevelInfo(*info2);
    if(type1 == POINTER_LEVEL && type2 == POINTER_LEVEL){
        // Pointer's Reduce Error level
        if(res == LOW_ERROR){ 
            return WARNING; // Pointer to pointer
        }
        if(res == HIGH_ERROR){
            return LOW_ERROR; // Pointer to pointer
        }
    }

    // Only if this level is pointer we can reduce to warning else No Reduction
    return res;
}

bool isEmpty(const TypeExpression &typeExpr){
    // This will check if the type expression is empty
    return typeExpr.levelStack.empty();
}

//----------- What is the top of the stack
bool topIsParenthesis(const TypeExpression &typeExpr){
    // This will check if the top is ParenthesisInfo
    if(typeExpr.levelStack.empty()){
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    if(!info){
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    return isParenthesisInfo(*info);
}

bool topIsArray(const TypeExpression &typeExpr){
    // This will check if the top is ArrayInfo
    if(typeExpr.levelStack.empty()){
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    if(!info){
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    return isArrayInfo(*info);
}

bool topIsPointer(const TypeExpression &typeExpr){
    // This will check if the top is PointerInfo
    if(typeExpr.levelStack.empty()){
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    if(!info){
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    return isPointerInfo(*info);
}

bool topIsBase(const TypeExpression &typeExpr){
    // This will check if the top is BaseInfo
    if(typeExpr.levelStack.empty()){
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    if(!info){
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    return isBaseInfo(*info);
}

bool topIsParameter(const TypeExpression &typeExpr){
    // This will check if the top is ParameterInfo
    if(typeExpr.levelStack.empty()){
        return false;
    }
    LevelInfo *info = typeExpr.levelStack.top();
    if(!info){
        std::cerr << "Error: LevelInfo is nullptr\n";
        return false;
    }
    return isParameterInfo(*info);
}

bool isModifiableLvalue(const TypeExpression &type)
{
    //First Remove top Parenthesis
    TypeExpression temp = type;
    removeTopParenthesis(temp);

    // Logic - Array or Function
    if(topIsArray(temp) || topIsParameter(temp)){
        return false;
    }

    // Logic - Pointer with const qualifier
    if(topIsPointer(temp)){
        PointerInfo *ptr = dynamic_cast<PointerInfo*>(temp.levelStack.top());
        for(auto qualifier : ptr->typeQualifiers){
            if(qualifier == TypeQualifier::CONST){
                return false;
            }
        }
    }

    // Logic - Base with const qualifier
    if(topIsBase(temp)){
        BaseInfo *base = dynamic_cast<BaseInfo*>(temp.levelStack.top());
        
    // Base with const qualifier
        for(auto qualifier : base->typeQualifiers){
            if(qualifier == TypeQualifier::CONST){
                return false;
            }
        }

    // Base with record type can be modified
    //     std::string baseType = base->baseType;
    //     // it can have 3parts seprated by space or just one
    //     std::string recordType = baseType.substr(0, baseType.find(" "));
    //     if(recordType == "struct" || recordType == "union"){
    //         return true;
    //     }
    //     if(recordType == "enum"){
    //         return true;
    //     }
    }

    return true;
}


Expr_Type whichTypeExpression(const TypeExpression &typeExpr){
    // First Remove top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);
    
    if(temp.levelStack.empty()){
        return Expr_Type::EMPTY;
    }
    LevelInfo *info = temp.levelStack.top();
    if(!info){
        std::cerr << "Error: LevelInfo is nullptr\n";
        return Expr_Type::UNKNOWN;
    }
    
    int topLevel = whichLevelInfo(*info);
    if(topLevel == BASE_LEVEL){
        // Check if it is a record
        BaseInfo *base = dynamic_cast<BaseInfo*>(info);
        std::string baseType = base->baseType;
        std::string recordType = baseType.substr(0, baseType.find(" "));
        if(recordType == STRUCT || recordType == UNION){
            return Expr_Type::STURCT_UNION;
        }
        if(recordType == ENUM){
            return Expr_Type::ENUM;
        }
        if(recordType == ENUM_CONSTANT){
            return Expr_Type::ENUM_CONSTANT;
        }

        // Then it is a variable
        return Expr_Type::VARIABLE;
    }else if(topLevel == POINTER_LEVEL){
        return Expr_Type::POINTER;
    }else if(topLevel == ARRAY_LEVEL){
        return Expr_Type::ARRAY;
    }else if(topLevel == PARAMETER_LEVEL){
        return Expr_Type::FUNCTION;
    }

    return Expr_Type::UNKNOWN;
}

TypeExpression createTypeExpression(GenericSymbol *symbol){
    TypeExpression typeExpr;

    if(!symbol){
        std::cerr << "Error: Symbol is nullptr\n";
        return typeExpr;
    }

    // Check if it is a variable
    if(isVariable(*symbol)){
        Variable *var = dynamic_cast<Variable*>(symbol);
        return var->type;
    }
    else if (isFunction(*symbol))
    {
        Function *func = dynamic_cast<Function*>(symbol);
        return func->type;
    }
    else if(isEnumConstant(*symbol)){
        BaseInfo *base = new BaseInfo();
        base->baseType = ENUM_CONSTANT;
    }
    return typeExpr;

}

VALUE_TYPE getValueType(const TypeExpression &typeExpr){

    // First Remove top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    Expr_Type whichType = whichTypeExpression(temp);

    if(whichType == Expr_Type::ENUM_CONSTANT){
        // This is a constant
        return VALUE_TYPE::RVALUE;
    }

    int isModifiable = isModifiableLvalue(temp);
    if(!isModifiable){
        //Non-modifiable Lvalue (array, function, const keyword)
        return VALUE_TYPE::NM_LVALUE;
    }
    
    return VALUE_TYPE::M_LVALUE;
}

SPACE getSpace(const TypeExpression &typeExpr){
    
    // First Remove top Parenthesis
    TypeExpression temp = typeExpr;
    removeTopParenthesis(temp);

    // Only ARRAY & STRUCT/UNION are in Address Space
    Expr_Type whichType = whichTypeExpression(temp);
    if(whichType == Expr_Type::ARRAY){
        return SPACE::ADDRESS_SPACE;
    }
    if(whichType == Expr_Type::STURCT_UNION){
        return SPACE::ADDRESS_SPACE;
    }

    return SPACE::VALUE_SPACE;
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

std::string newRecordName(){
    static int recordCount = 0;
    std::string recordName = "UnNamedRecord" + std::to_string(recordCount);
    recordCount++;
    return recordName;
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
