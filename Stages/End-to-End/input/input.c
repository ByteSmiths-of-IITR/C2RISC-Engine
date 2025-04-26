int main(){
    int arr[3];
    arr[7] = 3;
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
// 1          : alloca arr$1, 12              
// 2          : alloca $0, 12                 
// 3          : $0 = arr$1.offset             
// 4          : alloca $1, 4                  
// 5          : $1 = 7 * 4                    
// 6          : alloca $2, 4                  
// 7          : $2 = $0 + $1                  
// 8          : (4)*$2 = 3                    
// 9          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
// 🅰️ ---- IR Code After Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca arr$1, 12              
// 2          : alloca $0, 12                 
// 3          : $0 = arr$1.offset             
// 4          : alloca $1, 4                  
// 5          : $1 = 28                       
// 6          : alloca $2, 4                  
// 7          : $2 = $0 + $1                  
// 8          : (4)*$2 = 3                    
// 9          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
