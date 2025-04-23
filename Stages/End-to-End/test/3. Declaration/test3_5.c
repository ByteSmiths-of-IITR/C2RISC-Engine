// use AST to check for proper type assignment for...
// Functions with (Const, Ptrs) - NO GCC ERROR

int* func1(); // int *()
int (*func2)(); // int (*)()

const int* func3(); // const int*()
int* const func4(); // int *const()

float* const func5(); // float *const()
float (* const func6)(); // float (*const)()

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
