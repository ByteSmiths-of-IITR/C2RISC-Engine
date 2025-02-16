// Here we will be designing the symbol table for the compiler

/*
Ideas:
- We have a general class node for basic information - Name, SymbolType+Pointer_toThatClassOfSymbolNode, scope
- We have a class for each type of symbol - Variable, Function, [Later Struct, Enum, Union ]
- For variable, we have - Type, Size, Offset, pointerFlag, ArrayInfo, InitializationValue
- For function, we have - Return Type, parameterList(argType, argName), variadicFlag, recursiveFlag, FunctionAddress




*/