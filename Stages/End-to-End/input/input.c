int main(){
    int a = 4.3;
    float b = 34;
}

//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : alloca $0, 4                  
// 3          : $0 = (int)a$1                 
// 4          : a$1 = $0                      
// 5          : alloca b$1, 4                 
// 6          : alloca $1, 4                  
// 7          : $1 = (float)b$1               
// 8          : b$1 = $1                      
// 9          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
