

int a = 7;

int main() {
    int a = 3;
    if(a){
        return 3;
    }
    else{
        return 4;
    }
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
//            : a:        .word      7         
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : a$1 = 3                       
// 3          : if a$1 goto L(5)              
// 4          : goto L(7)                     
// 5          : return 3                      
// 6          : goto L(8)                     
// 7          : return 4                      
// 8          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .data      : ------------------------------
//            : a:        .word      7         
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : a$1 = 3                       
// 3          : if a$1 goto L(5)              
// 4          : goto L(7)                     
// 5          : return 3                      
// 6          : goto L(8)                     
// 7          : return 4                      
// 8          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
