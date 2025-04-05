// use AST to check for proper type assignment for...
// Enum with (arrays, ptrs, const) - NO GCC ERROR

enum E{a,b,c};

enum E obj0; // enum E

enum E* obj1; // enum E*
enum E** obj2; // enum E**

enum E obj3[3]; // enum E[3]
enum E* obj4[3]; // enum E *[3]
enum E (*obj5)[3]; // enum E (*)[3]
const enum E* (*obj6)[3]; // enum E *(*)[3]

enum E* const obj7[3]; // enum E *const[3]
enum E **const obj8[3]; // enum E **const[3]
enum E const (*obj9)[3]; //const enum E (*)[3]


//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
