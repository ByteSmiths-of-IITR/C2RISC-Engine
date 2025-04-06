// use AST to check for proper type assignment for...
// Arrays with (Const, Ptrs) - NO GCC ERROR

const char arr0[2]; // const char[2]
const const int* arr1[3]; // const int*[3]

int *arr2[5]; // int*[5]
int (*arr3)[3]; // int (*)[3]

int func(){
    const int *arr4[3]; // const int*[3]
    float* const arr5[3]; // float* const[3]
    return 1;
}

int main(){
    char **arr6[3]; // char **[3]
    char* (*arr7)[3]; // char *(*)[3]
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC Warning ❗️: Declaration Specifier - Duplicate Type Qualifiers in declaration specifiers
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : func                          
// 1          : return 1                      
// 
// 2          : main                          
// 3          : return 0                      
// 
