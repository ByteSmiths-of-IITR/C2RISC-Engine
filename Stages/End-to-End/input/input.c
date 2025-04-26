int main(){
    int a = 3 + 3;
    int b = 342 + 342;
}

//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// 
// 🅰️ ---- IR Code Before Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : alloca $0, 4                  
// 3          : $0 = 3 + 3                    
// 4          : a$1 = $0                      
// 5          : alloca b$1, 4                 
// 6          : alloca $1, 4                  
// 7          : $1 = 342 + 342                
// 8          : b$1 = $1                      
// 9          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
// 🅰️ ---- IR Code After Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : alloca $0, 4                  
// 3          : $0 = 6                        
// 4          : a$1 = $0                      
// 5          : alloca b$1, 4                 
// 6          : alloca $1, 4                  
// 7          : $1 = 684                      
// 8          : b$1 = $1                      
// 9          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
