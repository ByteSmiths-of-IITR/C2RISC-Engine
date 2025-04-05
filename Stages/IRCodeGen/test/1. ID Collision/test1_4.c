struct COLOR{
    int r, g,b;
};

enum COLOR{ RED, GREEN, BLUE, WHITE, BLACK }; // error: ‘COLOR’ defined as wrong kind of tag

int main(){
    // enum COLOR color = RED; // variable ‘color’ has initializer but incomplete type; storage size of ‘color’ isn’t known
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : RecordID "COLOR" already 🫠 present in the current scope
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : return 0                      
// 
