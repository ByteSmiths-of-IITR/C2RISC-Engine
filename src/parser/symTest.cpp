#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include "sym.h"

using namespace std;



int main() {
    SymbolTable symTable;

    // outputFile
    string outputFile = "symbol_table.txt";
    freopen(outputFile.c_str(), "w", stdout);

    // Adding a variable
    SymbolEntry* var1 = new SymbolEntry("x", SymbolType::VARIABLE, 
        new VariableInfo(DataType::INT, StorageClass::AUTO, 4, 0, false));
    symTable.insert(var1);

    // Adding an integer array
    SymbolEntry* arr = new SymbolEntry("arr", SymbolType::ARRAY, 
        new ArrayInfo(DataType::INT, StorageClass::AUTO, {10, 20}));
    symTable.insert(arr);

    // Adding a function
    FunctionInfo* funcInfo = new FunctionInfo(DataType::VOID, false, false);
    funcInfo->addParameter("param1", DataType::INT);
    SymbolEntry* func = new SymbolEntry("myFunc", SymbolType::FUNCTION, funcInfo);
    symTable.insert(func);

    // Displaying the table
    symTable.display();

    return 0;
}
