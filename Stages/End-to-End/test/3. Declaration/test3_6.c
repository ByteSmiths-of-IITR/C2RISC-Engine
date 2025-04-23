// use AST to check for proper type assignment for...
// Struct with (arrays, ptrs, const) - NO GCC ERROR

struct A{
    int a;
    int b;
}obj0[3]; // struct A[3]

struct A obj1[3][4]; // struct A[3][4]
struct A *obj2; // struct A*
struct A **obj3; // struct A**

struct A *obj4[3]; // struct A*[3]
const struct A (*obj5)[3]; // const struct A (*)[3]
const struct A* (*obj6)[3]; // const struct A *(*)[3]

struct A *const obj7[3]; // struct A *const[3]
struct A const (*obj8)[3]; //const struct A (*)[3]


//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
