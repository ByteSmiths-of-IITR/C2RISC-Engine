int main(){
    int a = 0;
    int *p = &a;
    if(a){
        a = 1;
    }
    else{
        a = 2;
    }
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// RISC-V Code Generation completed successfully 
// 
// ----------------------------------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------------------------------
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : a$1 = 0                       
// 3          : alloca p$1, 4                 
// 4          : alloca $0, 4                  
// 5          : $0 = &a$1                     
// 6          : p$1 = $0                      
// 7          : if a$1 goto L(9)              
// 8          : goto L(11)                    
// 9          : a$1 = 1                       
// 10         : goto L(12)                    
// 11         : a$1 = 2                       
// 12         : main: Func EXIT               
// 
// ----------------------------------------------------------------------------------------------------
// ====================== [ CFG Code ] ======================
// .data
// 
// .text
// ENTRY : 
// main : 
//   0   : main: Func ENTER          | No Variable      | 
//   1   : alloca a$1, 4             | a$1 ☠️           | 
//   2   : a$1 = 0                   | a$1 ⬇️ ( 5 7 )   | 
//   3   : alloca p$1, 4             | a$1 ⬇️ ( 5 7 )   | p$1 ☠️           | 
//   4   : alloca $0, 4              | $0 ☠️            | a$1 ⬇️ ( 5 7 )   | p$1 ☠️           | 
//   5   : $0 = &a$1                 | $0 ⬇️ ( 6 )      | a$1 ⬇️ ( 7 )     | p$1 ☠️           | 
//   6   : p$1 = $0                  | a$1 ⬇️ ( 7 )     | 
//   7   : if a$1 goto L(Block_2)    | No Variable      | 
//   8   : goto L(Block_4)           | No Variable      | 
// Block_2 : 
//   9   : a$1 = 1                   | No Variable      | 
//   10  : goto L(Block_3)           | No Variable      | 
// Block_4 : 
//   11  : a$1 = 2                   | No Variable      | 
// Block_3 : 
//   12  : main: Func EXIT           | No Variable      | 
// EXIT : 
// 
