int main(){
    int a = 7;
    switch (a)
    {
        case 1:
            a = 1;
            break;
        case 2:
            a = 2;
            break;
        case 3:
            a = 3;
            break;
        default:
            a = 4;
            break;
    }
    // int arr[3] = {1, 2, 3};
}

//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
//  📈 CFG Code Generation in progress 
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
// 2          : a$1 = 7                       
// 3          : goto L(13)                    
// 4          : a$1 = 1                       
// 5          : goto L(17)                    
// 6          : a$1 = 2                       
// 7          : goto L(17)                    
// 8          : a$1 = 3                       
// 9          : goto L(17)                    
// 10         : a$1 = 4                       
// 11         : goto L(17)                    
// 12         : goto L(17)                    
// 13         : if a$1 == 1 goto L(4)         
// 14         : if a$1 == 2 goto L(6)         
// 15         : if a$1 == 3 goto L(8)         
// 16         : goto L(10)                    
// 17         : return                        
// 18         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
// 🎨 CFG Code Generation completed successfully 🎨
// #-------------------------------------------------------------------------
// ====================== [ CFG Code ] ======================
// .data
// 
// .text
//  : 
// #-------------------------------------------------------------------------
// 
// 
// 
//  ---- IR Code After Machine Independent Optimization ---- 
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 4                 
// 2          : a$1 = 7                       
// 3          : goto L(13)                    
// 4          : a$1 = 1                       
// 5          : goto L(17)                    
// 6          : a$1 = 2                       
// 7          : goto L(17)                    
// 8          : a$1 = 3                       
// 9          : goto L(17)                    
// 10         : a$1 = 4                       
// 11         : goto L(17)                    
// 12         : goto L(17)                    
// 13         : if a$1 == 1 goto L(4)         
// 14         : if a$1 == 2 goto L(6)         
// 15         : if a$1 == 3 goto L(8)         
// 16         : goto L(10)                    
// 17         : return                        
// 18         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
