int func(){
    return 0;
}

#include <stdio.h>

int main(){
    int (*ptr)() = &func;

    // printf("address of func = %p\n", func);
    // printf("value of ptr = %p\n", ptr);
    // printf("address of func + 1 = %p\n", func + 1);

    // int arr[4];
    // int *p = &arr[2];
}

//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// .text      : ------------------------------
// 0          : func: Func ENTER              
// 1          : return 0                      
// 2          : func ret(4): EXIT             
// 
// 3          : main: Func ENTER              
// 4          : alloca ptr$2, 4               
// 5          : alloca $0, 4                  
// 6          : ptr$2 = func                  
// 7          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
