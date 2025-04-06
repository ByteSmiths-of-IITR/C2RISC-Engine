// int func(int a){
//     return a;
// }

int main(){
    // int x = func(9);
    int a = 0;
    printf("%d\n", 3);
    scanf("%d\n", 3);
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$0 : c"%d\n\00" 
// @str$2 : c"%d\n\00" 
// 
// ----------------------------------------------
// .data section : ------------------------------
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : main                          
// 1          : param @str$0                  
// 2          : param 3                       
// 3          : $1 = call printf, 2           
// 4          : param @str$2                  
// 5          : param 3                       
// 6          : $3 = call scanf, 2            
// 7          : return 0                      
// 
// 
