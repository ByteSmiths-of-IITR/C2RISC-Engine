

int main(){
    int a = 9;
    int b = 3;
    int c = a & b;
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
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : a$1 = 9                       
// 3          : alloca b$1, 4                 
// 4          : b$1 = 3                       
// 5          : alloca c$1, 4                 
// 6          : alloca $0, 4                  
// 7          : $0 = a$1 & b$1                
// 8          : c$1 = $0                      
// 9          : return                        
// 10         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : a$1 = 9                       
// 3          : alloca b$1, 4                 
// 4          : b$1 = 3                       
// 5          : alloca c$1, 4                 
// 6          : alloca $0, 4                  
// 7          : $0 = a$1 & b$1                
// 8          : c$1 = $0                      
// 9          : return                        
// 10         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
