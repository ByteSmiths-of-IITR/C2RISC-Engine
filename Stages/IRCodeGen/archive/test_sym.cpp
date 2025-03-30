#include "sym.h"

extern int MEMORY_MONITORING;

#define LINE std::cerr << "Reaching till line-" <<  __LINE__ << std::endl;

std::ofstream symFile;

//Signal Handler
void signalHandler(int signum){
    std::cerr << "Signal Handler Called with Signal No: " << signum << std::endl;

    //Flush the in/out streams
    std::cerr.flush();
    std::cout.flush();
    symFile.flush();

    //Close the file
    symFile.close();

    exit(signum);
}

int main(int argc, char *argv[]){

    // usage - ./test_sym <sym_table_file>
    if(argc != 2){
        std::cerr << "Usage: ./test_sym <sym_table_file>" << std::endl;
        exit(1);
    }

    std::string sym_table_file = argv[1];

    //Signal Handler
    signal(SIGSEGV, signalHandler);
    std::string errorFile = "output/sym_error.log";
    freopen(errorFile.c_str(), "w", stderr);

    // Open SymbolTable File in truncate mode for fresh start
    
    symFile.open(sym_table_file, std::ios_base::trunc);

    MEMORY_MONITORING = 0;
    
    //Testing SymbolTable
    SymbolTable *table = new SymbolTable();

    table->enterScope();
    // table->printTable(symFile);


    //New Variable
    Variable *var = new Variable();
    table->insert("var", var);

    //New Function
    Function *func = new Function();
    table->insert("func", func);

    //New EnumConstant
    EnumConstant *enumConst = new EnumConstant();
    table->insert("enumConst", enumConst);

    //Lookup
    GenericSymbol *sym;
    std::string key = "var";
    if(table->lookup(key, sym) == 0){
        std::cout << key << " Found" << std::endl;
    }
    else{
        std::cout << key << " Not Found" << std::endl;
    }

    table->printTable(symFile);
    // table->printTable(symFile);

    key = "func";
    if(table->lookup(key, sym) == 0){
        std::cout << key << " Found" << std::endl;
    }
    else{
        std::cout << key << " Not Found" << std::endl;
    }

    table->enterScope();

    LINE

    key = "var";
    if(table->lookup(key, sym) == 0){
        std::cout << key << " Found" << std::endl;
    }
    else{
        std::cout << key << " Not Found" << std::endl;
    }

    LINE

    table->printTable(symFile);

    LINE

    table->exitScope();
    LINE
    table->exitScope();
    LINE

    key = "var";
    if(table->lookup(key, sym) == 0){
        std::cout << key << " Found" << std::endl;
    }
    else{
        std::cout << key << " Not Found" << std::endl;
    }

    LINE

    table->printTable(symFile);


}