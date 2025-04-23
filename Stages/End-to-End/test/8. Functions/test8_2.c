#include <stdio.h>

// Function declarations
int add(int a, int b);
float multiply(float a, float b);

// Function pointer types
typedef int (*IntBinaryOp)(int, int);
typedef float (*FloatBinaryOp)(float, float);

int main()
{
    IntBinaryOp op1 = add;        // ✅ Correct assignment
    FloatBinaryOp op2 = multiply; // ✅ Correct assignment

    // ❌ Mismatch #1: Assign function with wrong signature
    IntBinaryOp badOp = multiply; // ⚠️ Error: incompatible pointer types

    // ❌ Mismatch #2: Calling via incorrect prototype
    int result = badOp(3, 4); // ⚠️ Undefined behavior

    printf("Result: %d\n", result);
    return 0;
}

// Definitions
int add(int a, int b)
{
    return a + b;
}

float multiply(float a, float b)
{
    return a * b;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC Warning ❗️: Initialization type mismatch - Expected : 'int (*)(int, int)' Found : 'float *(float, float)'
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// .rodata section : ------------------------------
// @str$1 : c"Result: %d\n\0" 
// 
// ----------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : op1$1 = add                   
// 2          : op2$1 = multiply              
// 3          : badOp$1 = multiply            
// 4          : param 3                       
// 5          : param 4                       
// 6          : $0 = call badOp$1, 2          
// 7          : result$1 = $0                 
// 8          : param @str$1                  
// 9          : param result$1                
// 10         : $2 = call printf, 2           
// 11         : return 0                      
// 
// 12         : add                           
// 13         : $3 = a$2 + b$2                
// 14         : return $3                     
// 
// 15         : multiply                      
// 16         : $4 = a$3 * b$3                
// 17         : return $4                     
// 
