#include <sym.h>

#define MEM(x) (MEMORY_MONITORING ? std::cerr << x << std::endl : std::cerr)

bool isVariable(const SymbolDetails &sym){
    return dynamic_cast<const VariableInfo*>(&sym);
}

bool isFunction(const SymbolDetails &sym){
    return dynamic_cast<const FunctionInfo*>(&sym);
}