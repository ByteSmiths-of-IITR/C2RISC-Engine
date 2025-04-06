// redeclaration of enum variable (enum constant) in the same scope
enum COLOR {RED, GREEN, BLUE};
int RED = 10; // error: ‘RED’ redeclared as different kind of symbol

// redefinition of struct 
struct A{
    int a;
    int b;
};

struct A{ // error: redefinition of ‘struct A’
    int x;
    int y;
};

// struct and variable name collision - no error here
int A = 10;
char a = 'a';

int main(){
    // no error
    int RED = 100;
    int A = 20;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Symbol "RED" already 🫠 present in the current scope
// SEMANTIC ERROR ‼️ : RecordID "A" already 🫠 present in the current scope
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : RED$0 = 10                    
// 1          : A$0 = 10                      
// 2          : a$0 = a                       
// 
// 3          : main                          
// 4          : RED$1 = 100                   
// 5          : A$1 = 20                      
// 
