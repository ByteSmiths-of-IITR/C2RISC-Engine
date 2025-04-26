int main(){
    int arr[3];
    int k = arr[7];
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
// 2          : alloca k$1, 4                 
// 3          : alloca $0, 12                 
// 4          : $0 = arr$1.offset             
// 5          : alloca $1, 4                  
// 6          : $1 = 7 * 4                    
// 7          : alloca $2, 4                  
// 8          : $2 = $0 + $1                  
// 9          : alloca $3, 4                  
// 10         : $3 = (4)*$2                   
// 11         : k$1 = $3                      
// 12         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
// 🅰️ ---- IR Code After Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca arr$1, 12              
// 2          : alloca k$1, 4                 
// 3          : alloca $0, 12                 
// 4          : $0 = arr$1.offset             
// 5          : alloca $1, 4                  
// 6          : $1 = 28                       
// 7          : alloca $2, 4                  
// 8          : $2 = $0 + $1                  
// 9          : alloca $3, 4                  
// 10         : $3 = (4)*$2                   
// 11         : k$1 = $3                      
// 12         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
