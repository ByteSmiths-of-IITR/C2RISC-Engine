int main(){
    char *str = "int a; int *p; if (a) a = 1; else a = 2;";
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// RISC-V Code Generation failed 
// 
// ----------------------------------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------------------------------
// .data      : ------------------------------
//            : @str$0:   .string    "int a; int *p; if (a) a = 1; else a = 2;"
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca str$1, 4               
// 2          : str$1 = @str$0                
// 3          : main: Func EXIT               
// 
// ----------------------------------------------------------------------------------------------------
// ====================== [ CFG Code ] ======================
// .data
// 
// .text
// ENTRY : 
// main : 
//   0   : main: Func ENTER          | Default            | 
//   1   : alloca str$1, 4           | str$1 ☠️           | 
//   2   : str$1 = @str$0            | Default            | 
//   3   : main: Func EXIT           | Default            | 
// EXIT : 
// 
