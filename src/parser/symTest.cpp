#include <iostream>

#include "sym.h"
// extern int DEBUGMODE;

int main() {
    SymbolTable symTable;

    std::string outputFile = "symbol.txt";
    freopen(outputFile.c_str(), "w", stdout);

    // Insert a variable
    VariableInfo* var = new VariableInfo(1, "x", "int", StorageClass::AUTO);
    SymbolEntry* varEntry = new SymbolEntry("x", SymbolType::VARIABLE, var);
    symTable.insert(varEntry);

    // Insert an array
    std::vector<int> dims = {10, 20};
    ArrayInfo* arr = new ArrayInfo(2, "arr", "int", StorageClass::STATIC, dims);
    SymbolEntry* arrEntry = new SymbolEntry("arr", SymbolType::ARRAY, arr);
    symTable.insert(arrEntry);

    // Insert a function
    FunctionInfo* func = new FunctionInfo(3, "myFunc", "void");
    func->addParameter("param1", "int", false, false);
    SymbolEntry* funcEntry = new SymbolEntry("myFunc", SymbolType::FUNCTION, func);
    symTable.insert(funcEntry);

    // Display the symbol table
    std::cout << "\nSymbol Table Contents:\n";
    // symTable.display();

    // Lookup symbols
    std::cout << "\nLookup Results:\n";
    SymbolEntry* lookupVar = symTable.lookup("x");
    if (lookupVar) lookupVar->display();
    else std::cout << "Variable 'x' not found.\n";

    // SymbolEntry* lookupArr = symTable.lookup("arr");
    // if (lookupArr) lookupArr->display();
    // else std::cout << "Array 'arr' not found.\n";

    // SymbolEntry* lookupFunc = symTable.lookup("myFunc");
    // if (lookupFunc) lookupFunc->display();
    // else std::cout << "Function 'myFunc' not found.\n";

    return 0;
}
