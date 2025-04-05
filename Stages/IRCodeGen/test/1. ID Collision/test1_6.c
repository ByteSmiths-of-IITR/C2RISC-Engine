// same enum ID in different scopes

enum Color { RED, GREEN, BLUE };
enum TrafficLight { RED, YELLOW, BLACK };  // error: redeclaration of enumerator 'RED'

void func(){
    enum Color { RED, INDIGO, YELLOW }; // no error
}

int main() {
    enum Color { RED, INDIGO, YELLOW }; // no error
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Enum Constant "RED" already present in the current scope
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : func                          
// 1          : main                          
// 2          : return 0                      
// 
