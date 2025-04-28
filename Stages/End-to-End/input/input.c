
// test case for simple if and if else and if else if ladder
// Output : c is the greatest

// #include <stdio.h>

int main()
{
    float b = 12.3;
    float a = 2.3;
    float c = a + b;
}

//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// 
//  ---- IR Code Before Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : fVar_0:   .float     12.300000 
//            : fVar_1:   .float     2.300000  
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : alloca float b$1, 4           
// 2          : b$1 = fVar_0                  
// 3          : alloca float a$1, 4           
// 4          : a$1 = fVar_1                  
// 5          : alloca float c$1, 4           
// 6          : alloca $0, 4                  
// 7          : $0 = a$1 + b$1                
// 8          : c$1 = $0                      
// 9          : return                        
// 10         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : fVar_0:   .float     12.300000 
//            : fVar_1:   .float     2.300000  
// .text      : ------------------------------
// 0          : main: Func with 0 args        
// 1          : alloca float b$1, 4           
// 2          : b$1 = fVar_0                  
// 3          : alloca float a$1, 4           
// 4          : a$1 = fVar_1                  
// 5          : alloca float c$1, 4           
// 6          : alloca $0, 4                  
// 7          : $0 = a$1 + b$1                
// 8          : c$1 = $0                      
// 9          : return                        
// 10         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
