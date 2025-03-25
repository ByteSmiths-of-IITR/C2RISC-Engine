#include "sym.h"
#include "debugger.h"

// #define here std::cerr << "HERE at lineNo -" << __LINE__ << std::endl;
#define here //

#define CORNER "+"
#define SEP "|"
#define BORDER '-'
#define OUTER '='
#define GAP 16

// Enum class function to string

    std::string getSymbolString(SymbolType st){
        switch(st){
            case SymbolType::VARIABLE: return "Variable";
            case SymbolType::FUNCTION: return "Function";
            case SymbolType::ARRAY: return "Array";
            // case SymbolType::STRUCT: return "Struct";
            // case SymbolType::ENUM: return "Enum";
            // case SymbolType::UNION: return "Union";
            default: return "UNKNOWN";
        }
    }
    

    std::string dTypeString(DataType dt){
        switch(dt){
            case DataType::VOID: return "void";
            case DataType::CHAR: return "char";
            case DataType::INT: return "int";
            case DataType::FLOAT: return "float";
            case DataType::DOUBLE: return "double";
            case DataType::INVALID: return "INVALID";
            default : return "!!UNKNOWN!!";
        }
    }
    DataType getDataType(const std::string& baseType){
        if(baseType == "void") return DataType::VOID;
        else if(baseType == "char") return DataType::CHAR;
        else if(baseType == "int") return DataType::INT;
        else if(baseType == "float") return DataType::FLOAT;
        else if(baseType == "double") return DataType::DOUBLE;
        else return DataType::INVALID;
    }

    std::string getStorageClassString(StorageClass sc){
        switch(sc){
            case StorageClass::AUTO: return "auto";
            case StorageClass::STATIC: return "static";
            case StorageClass::EXTERN: return "extern";
            default: return "UNKNOWN";
        }
    }

// DTypeInfo Member Function

    DTypeInfo::DTypeInfo(DataType dt, int ptr) : dataType(dt), ptrLevel(ptr) {
        for(int i=0; i<=ptr; i++){
            toWhichConst.push_back(false); // default is non-const
        }
    }

    DTypeInfo::DTypeInfo(const std::string& dtype){
        // -- ToDo -- to which level of ptr is constant assigned [Later]

        // Only Handled oneLevel pointer [ Will be implemente if needed by grammar]
        /* possible inputs
        1. dtype 
        2. dtype*
        3. dtype const 
        4. dtype* const // here const is for pointer not for data
        5. const dtype
        6. const dtype* // here const is for data not for pointer
        7. const dtype* const // here const is for both data and pointer
        */
        
        // For Now just simple dtype string is given
        this->dataType = getDataType(dtype);

        // Default values
        this->ptrLevel = 0;
        toWhichConst.push_back(false);
    }

    void DTypeInfo::setConst(int level, bool isConst){
        if(level >= toWhichConst.size()){
            toWhichConst.resize(level+1, false);
        }
        toWhichConst[level] = isConst;
    }

    int  DTypeInfo::getSize() const {
        if(ptrLevel > 0) return WORD_SIZE;

        switch(dataType){
            case DataType::VOID: return 0;
            case DataType::CHAR: return BYTE_SIZE;
            case DataType::INT: return WORD_SIZE;
            case DataType::FLOAT: return WORD_SIZE;
            case DataType::DOUBLE: return 2*WORD_SIZE;
            default: return 0;
        }
    }

    void DTypeInfo::isPointer(int level){
        this->ptrLevel = level;
    }

    bool DTypeInfo::isConst(int level){
        if(level >= toWhichConst.size()){
            std::cerr << "Given level doesn't exist" << std::endl;
            return false;
        }
        return toWhichConst[level];
    }

    void DTypeInfo::display(std::ostream& out) const {
        // Collecting values dynamically
        std::string dataTypeStr = dTypeString(dataType);
        int size = getSize();
        std::string sizeStr = std::to_string(size);
        std::string isPointerStr = (ptrLevel > 0) ? "Yes" : "No";
        std::string isConstStr = toWhichConst[0] ? "Yes" : "No";

        // Compute max width for proper box formatting
        int maxWidth = 8;
        int boxWidth = maxWidth + GAP; // Adding padding

        // Print top border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
        out << "│" << std::setw((boxWidth + 18) / 2) << "DType Information" << std::setw((boxWidth - 18) / 2) << "│\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        // Print dynamically sized content
        out << "│ Base DType    : " << std::setw(maxWidth) << dataTypeStr << " │\n";
        out << "│ Size          : " << std::setw(maxWidth) << sizeStr << " │\n";
        out << "│ isPointer     : " << std::setw(maxWidth) << isPointerStr << " │\n";
        out << "│ isConst       : " << std::setw(maxWidth) << isConstStr << " │\n";

        // Print bottom border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
    }

// Base Class of SymbolDetails
    SymbolDetails::SymbolDetails(const std::string& name, int line) : symbolName(name), lineNo(line) {}

// VariableInfo Class Implementation

    // Constructor
    VariableInfo::VariableInfo(
        const int lineNo,
        const std::string& varName,
        const std::string& baseType,
        StorageClass sc,
        int off,
        const std::string& initVal
    ) :   
    SymbolDetails(varName, lineNo), 
    storageClass(sc), 
    offset(off), 
    initValue(initVal) 
    {
        this->variableType = DTypeInfo(baseType);
    }

    // Setter Functions
    void VariableInfo::setVarDType(DataType dt){
        this->variableType.dataType = dt;
    }

    void VariableInfo::setVarStorage(StorageClass sc){
        this->storageClass = sc;
    }

    void VariableInfo::setVarConst(int level, bool isConst){
        this->variableType.setConst(level, isConst);
    }

    void VariableInfo::setInitialValue(const std::string& initVal){
        this->initValue = initVal;
    }

    void VariableInfo::setOffset(int off){
        this->offset = off;
    }

    void VariableInfo::setDataConst(const std::string& initVal){
        this->initValue = initVal;
        this->variableType.setConst();
    }

    // Getter Functions
    bool VariableInfo::isDataConst() const {
        return isConst(0);
    }

    bool VariableInfo::isPtrConst()const{
        return isConst(1);
    }

    bool VariableInfo::isConst(int level) const{
        if(level >= this->variableType.toWhichConst.size()){
            std::cerr << "Given level doesn't exist" << std::endl;
            return false;
        }
        return this->variableType.toWhichConst[level];
    }

    bool VariableInfo::isPointer()const {
        return this->variableType.ptrLevel > 0;
    }

    bool VariableInfo::isInited()const {
        return !this->initValue.empty();
    }

    void VariableInfo::display(std::ostream& out) const {
        // Collecting values dynamically
        here
        std::string dataTypeStr = dTypeString(variableType.dataType);
        here
        std::string isPointerStr = (isPointer() ? "Yes" : "No");
        here
        std::string isConstantStr = (isDataConst() ? "Yes" : "No");
        here
        std::string storageClassStr = getStorageClassString(storageClass);
        here
        std::string lineNoStr = std::to_string(lineNo);
        here
        std::string offsetStr = std::to_string(offset);
        here
        std::string initValueStr = initValue.empty() ? "None" : initValue;
        std::string symbolNameStr = symbolName.empty() ? "Unknown" : symbolName;

        
        // Compute max width for proper box formatting
        int maxWidth = 8;
        int boxWidth = maxWidth + GAP; // Adding padding for box border
        int index = (boxWidth - 8) / 2;

        // Print top border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
        out << "│" << std::setw(index-2) << "" << "Variable : " << symbolNameStr << std::setw(index) << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        
        // Data Type Information Section
        out << "│ Line No       : " << std::setw(maxWidth) << lineNoStr << " │\n";
        out << "│ Base Type     : " << std::setw(maxWidth) << dataTypeStr << " │\n";
        out << "│ Size          : " << std::setw(maxWidth) << variableType.getSize() << " │\n";
        out << "│ isPointer     : " << std::setw(maxWidth) << isPointerStr << " │\n";
        out << "│ isConstant    : " << std::setw(maxWidth) << isConstantStr << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";
        
        // Variable Specific Information
        out << "│ Storage Class : " << std::setw(maxWidth) << storageClassStr << " │\n";
        out << "│ Offset        : " << std::setw(maxWidth) << offsetStr << " │\n";
        out << "│ Init Value    : " << std::setw(maxWidth) << initValueStr << " │\n";

        // Print bottom border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
    }

// ArrayInfo Class Implementation

    ArrayInfo::ArrayInfo(
        const int lineNo,
        const std::string& arrayName,
        const std::string& elementDType,
        StorageClass sc,
        std::vector<int> dims,
        int off
    ) : 
    SymbolDetails(arrayName, lineNo),
    storageClass(sc),
    dimensions(dims),
    offset(off)
    {
        this->elementTypeInfo = DTypeInfo(elementDType);
        setTotalSize();
    }

    // Setter Functions
    void ArrayInfo::setElementType(const std::string& dtype){
        this->elementTypeInfo = DTypeInfo(dtype);
    }

    void ArrayInfo::setElementTypeInfo(DTypeInfo dt){
        this->elementTypeInfo = dt;
    }

    void ArrayInfo::setElementAsPointer(int level){
        this->elementTypeInfo.isPointer(level);
    }

    void ArrayInfo::setElementAsConst(int level, bool isConst){
        this->elementTypeInfo.setConst(level, isConst);
    }

    void ArrayInfo::setArrConst(bool isConst){
        this->isArrConst = isConst;
    }

    void ArrayInfo::setStorageClass(StorageClass sc){
        this->storageClass = sc;
    }

    void ArrayInfo::setDimensions(std::vector<int> dims){
        this->dimensions = dims;
        setTotalSize(); // Update total size
    }

    void ArrayInfo::addDimension(int dim){
        this->dimensions.push_back(dim);
        setTotalSize();
    }

    void ArrayInfo::setTotalSize(){
        totalSize = elementTypeInfo.getSize();
        for(int dim : dimensions){
            totalSize *= dim;
        }
    }

    // Getter Functions
    // bool ArrayInfo::isArrConst(){
    //     return isArrConst;
    // }

    bool ArrayInfo::isDataConst(int level){
        return elementTypeInfo.isConst(level);
    }

    bool ArrayInfo::isDataPointer(){
        return elementTypeInfo.ptrLevel > 0;
    }
    
    std::vector<int> ArrayInfo::getDimensions(){
        return dimensions;
    }

    int ArrayInfo::getTotalSize(){
        return totalSize;
    }

    void ArrayInfo::display(std::ostream& out) const {
        // Collecting values dynamically
        // std::string symbolNameStr = symbolName.empty() ? "Unknown" : symbolName;
        std::string elementDataTypeStr = dTypeString(elementTypeInfo.dataType);
        std::string elementSizeStr = std::to_string(elementTypeInfo.getSize());
        std::string isPointerStr = (elementTypeInfo.ptrLevel > 0 ? "Yes" : "No");
        std::string isConstStr = (isArrConst ? "Yes" : "No");
        std::string storageClassStr = getStorageClassString(storageClass);
        std::string lineNoStr = std::to_string(lineNo);
        std::string offsetStr = std::to_string(offset);
        std::string totalSizeStr = std::to_string(totalSize);
        std::string dimensionsStr = "";
        for(int dim : dimensions){
            dimensionsStr += std::to_string(dim) + " ";
        }

        // Compute max width for proper box formatting
        int maxWidth = 8;
        int boxWidth = maxWidth + GAP; // Adding padding for box border
        int index = (boxWidth - 8) / 2;
        // Print top border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
        out << "|" << std::setw(index) << "" << " Array : " << symbolName << std::setw(index) << "|\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        // Data Type Information Section
        out << "│ Line No       : " << std::setw(maxWidth) << lineNoStr << " │\n";
        out << "│ Element Type  : " << std::setw(maxWidth) << elementDataTypeStr << " │\n";
        out << "│ Element Size  : " << std::setw(maxWidth) << elementSizeStr << " │\n";
        out << "│ isPointer     : " << std::setw(maxWidth) << isPointerStr << " │\n";
        out << "│ isConstant    : " << std::setw(maxWidth) << isConstStr << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        // Array Specific Information
        out << "│ Storage Class : " << std::setw(maxWidth) << storageClassStr << " │\n";
        out << "│ Offset        : " << std::setw(maxWidth) << offsetStr << " │\n";
        out << "│ Total Size    : " << std::setw(maxWidth) << totalSizeStr << " │\n";
        out << "│ Dimensions    : " << std::setw(maxWidth) << dimensionsStr << " │\n";
        out << "| isArrConst    : " << std::setw(maxWidth) << isConstStr << " │\n";

        // Print bottom border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
    }

// ArgumentInfo class Implementation

    ArgumentInfo::ArgumentInfo(
        const std::string& argName,
        const std::string& baseType,
        bool isConst,
        bool isPtr
    ){
        this->argName = argName;
        this->argType = DTypeInfo(baseType);
        this->isPassedByRef = isPtr;
        this->argType.setConst(0, isConst);
    }

    void ArgumentInfo::setArgDType(const std::string& dtype){
        this->argType = DTypeInfo(dtype);
    }

    void ArgumentInfo::setArgAsConst(int level, bool isConst){
        this->argType.setConst(level, isConst);
    }

    void ArgumentInfo::setArgAsPointer(int level){
        this->argType.isPointer(level);
    }

    void ArgumentInfo::setPassedByRef(bool isRef){
        this->isPassedByRef = isRef;
    }

    void ArgumentInfo::display(std::ostream& out) const {
        // Collecting values dynamically
        std::string argNameStr = argName.empty() ? "Unknown" : argName;
        std::string dataTypeStr = dTypeString(argType.dataType);
        std::string isConstStr = (argType.toWhichConst[0] ? "Yes" : "No");
        std::string isPointerStr = (argType.ptrLevel > 0 ? "Yes" : "No");
        std::string isRefStr = (isPassedByRef ? "Yes" : "No");

        // Compute max width for proper box formatting
        int maxWidth = 8;
        int boxWidth = maxWidth + GAP; // Adding padding for box border
        int index = (boxWidth - 8) / 2;

        // Print top border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
        out << "│" << std::setw(index) << "" << "Argument : " << argNameStr << std::setw(index) << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        // Data Type Information Section
        out << "│ Data Type     : " << std::setw(maxWidth) << dataTypeStr << " │\n";
        out << "│ isConstant    : " << std::setw(maxWidth) << isConstStr << " │\n";
        out << "│ isPointer     : " << std::setw(maxWidth) << isPointerStr << " │\n";
        out << "│ isPassedByRef : " << std::setw(maxWidth) << isRefStr << " │\n";

        // Print bottom border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
    }

// FunctionInfo Class Implementation
    FunctionInfo::FunctionInfo(
        const int lineNo,
        const std::string& funcName,
        const std::string& returnType,
        bool isConst,
        bool isVar,
        bool isRec,
        bool isDef,
        void* addr
    ) : 
    SymbolDetails(funcName, lineNo),
    returnType(DTypeInfo(returnType)),
    isFuncConst(isConst),
    isVariadic(isVar),
    isRecursive(isRec),
    isDefined(isDef),
    address(addr)
    {}

    // Setter Functions
    void FunctionInfo::setReturnType(DataType dt){
        this->returnType.dataType = dt;
    }

    void FunctionInfo::setFunctionAsConst(bool isConst){
        this->isFuncConst = isConst;
    }

    void FunctionInfo::setVariadic(bool var){
        this->isVariadic = var;
    }

    void FunctionInfo::setRecursive(bool rec){
        this->isRecursive = rec;
    }

    void FunctionInfo::setDefined(bool def){
        this->isDefined = def;
    }

    void FunctionInfo::setAddress(void* addr){
        this->address = addr;
    }

    void FunctionInfo::addParameter(const std::string& name, const std::string& dtype, bool isConst, bool isRef, int ptrLevel){
        this->parameters.push_back(ArgumentInfo(name, dtype, isConst, isRef));
        this->parameters.back().setArgAsPointer(ptrLevel);
        this->parameters.back().setArgAsPointer(ptrLevel);
        this->parameters.back().setPassedByRef(isRef);
    }

    void FunctionInfo::addParameter(const ArgumentInfo& arg){
        this->parameters.push_back(arg);
    }

    // Getter Functions

    // bool FunctionInfo::isFunctionConst(){
    //     return isFuncConst;
    // }

    // bool FunctionInfo::isFunctionVariadic(){
    //     return isVariadic;
    // }

    // bool FunctionInfo::isFunctionRecursive(){
    //     return isRecursive;
    // }

    // bool FunctionInfo::isFunctionDefined(){
    //     return isDefined;
    // }

    void* FunctionInfo::getAddress(){
        return address;
    }

    std::vector<ArgumentInfo> FunctionInfo::getParameters(){
        return parameters;
    }

    void FunctionInfo::display(std::ostream& out) const {
        // Collecting values dynamically
        std::string funcNameStr = symbolName.empty() ? "Unknown" : symbolName;
        std::string returnTypeStr = dTypeString(returnType.dataType);
        std::string isConstStr = (isFuncConst ? "Yes" : "No");
        std::string isVarStr = (isVariadic ? "Yes" : "No");
        std::string isRecStr = (isRecursive ? "Yes" : "No");
        std::string isDefStr = (isDefined ? "Yes" : "No");
        std::string addressStr = (address == nullptr ? "Unknown" : std::to_string((long)address));

        // Compute max width for proper box formatting
        int maxWidth = 8;
        int boxWidth = maxWidth + GAP; // Adding padding for box border
        int index = (boxWidth - 8) / 2;

        // Print top border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
        out << "│" << std::setw(index-2) << "" << "Function : " << funcNameStr << std::setw(index) << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        // Function Type Information Section
        out << "│ Line No       : " << std::setw(maxWidth) << lineNo << " │\n";
        out << "│ Return Type   : " << std::setw(maxWidth) << returnTypeStr << " │\n";
        out << "│ isConst       : " << std::setw(maxWidth) << isConstStr << " │\n";
        out << "│ isVariadic    : " << std::setw(maxWidth) << isVarStr << " │\n";
        out << "│ isRecursive   : " << std::setw(maxWidth) << isRecStr << " │\n";
        out << "│ isDefined     : " << std::setw(maxWidth) << isDefStr << " │\n";
        out << "│ Address       : " << std::setw(maxWidth) << addressStr << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";

        // Parameters Information
        out << "│ Parameters    : " << std::setw(maxWidth) << parameters.size() << " │\n";
        out << "|-" << std::string(boxWidth,BORDER) << "-|\n";
        for(auto& param : parameters){
            out << "│ " << std::setw(maxWidth) << param.argName << " │\n";
            out << "| Arg Data Type : " << std::setw(maxWidth) << dTypeString(param.argType.dataType) << " │\n";
            out << "| isConst       : " << std::setw(maxWidth) << (param.argType.toWhichConst[0] ? "Yes" : "No") << " │\n";
            out << "| isPointer     : " << std::setw(maxWidth) << (param.argType.ptrLevel > 0 ? "Yes" : "No") << " │\n";
            out << "| isPassedByRef : " << std::setw(maxWidth) << (param.isPassedByRef ? "Yes" : "No") << " │\n";
            out << "|-" << std::string(boxWidth,BORDER) << "-|\n";
        }

        // Print bottom border
        out << CORNER << std::string(boxWidth+2,BORDER) << CORNER << "\n";
    }

// SymbolEntry class

    SymbolEntry::SymbolEntry(
        const std::string& key,
        SymbolType type,
        SymbolDetails* det
    ){
        this->symbolKey = key;
        this->symbolType = type;
        this->details = det;
    }

    SymbolEntry::~SymbolEntry(){
        delete details;
    }

    void SymbolEntry::display(std::ostream& out) const {
        // Collecting values dynamically
        std::string symbolKeyStr = symbolKey.empty() ? "Unknown" : symbolKey;
        std::string symbolTypeStr = getSymbolString(symbolType);

        // Compute max width for proper box formatting
        int maxWidth = 8;
        int boxWidth = maxWidth+GAP; // Adding padding for box border
        int index = (boxWidth-8)/2;

        // Print top border
        out << CORNER << std::string(boxWidth+2,OUTER) << CORNER << "\n";
        out << "|" << std::setw(index) << "" << "Symbol : " << symbolKeyStr << std::setw(index) << "|\n";
        out << "|=" << std::string(boxWidth,OUTER) << "=|\n";

        // Symbol Information Section
        out << "│ Symbol Key    : " << std::setw(maxWidth) << symbolKeyStr << " │\n";
        out << "│ Symbol Type   : " << std::setw(maxWidth) << symbolTypeStr << " │\n";
        // out << "|=" << std::string(boxWidth,OUTER) << "=|\n";

        // Symbol Specific Information
        switch (symbolType)
        {
        case SymbolType::VARIABLE:
            std::cerr << "1" << std::endl;
            static_cast<VariableInfo *>(details)->display(out);
            // std::cerr << "1.1" << std::endl;
            break;
        case SymbolType::ARRAY:
            std::cerr << "2" << std::endl;
            static_cast<ArrayInfo *>(details)->display(out);
            break;
        case SymbolType::FUNCTION:
            std::cerr << "3" << std::endl;
            static_cast<FunctionInfo *>(details)->display(out);
            break;
        }

        // Print bottom border
        out << CORNER << std::string(boxWidth+2,OUTER) << CORNER << "\n";
    }

// SymbolTable class

    SymbolTable::~SymbolTable(){
        for(auto& pair : table) delete pair.second;
    }

    void SymbolTable::insert(SymbolEntry* entry){
        table[entry->symbolKey] = entry;
    }

    SymbolEntry* SymbolTable::lookup(const std::string& symbolKey){
        return table.count(symbolKey) ? table[symbolKey] : nullptr;
    }

    void SymbolTable::display(std::ostream& out) const {
        for(auto& pair : table){
            pair.second->display(out);
        }
    }

// End of File

