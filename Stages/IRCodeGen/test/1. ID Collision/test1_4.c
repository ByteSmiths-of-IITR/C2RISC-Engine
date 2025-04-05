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
// Error: Member Selection expression "$0" not found in symbol table
// Error: Member Selection expression "$1" not found in symbol table
// Error: Member Selection expression "$2" not found in symbol table
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : $0 = c$1.offset               
// 2          : $1 = c$1.offset               
// 3          : $2 = c$1.offset               
// 4          : color$1 = 0                   
// 
