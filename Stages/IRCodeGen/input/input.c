int funct(int a,int b){
    int res = a + b;
    int k = funct(a, res);
    return 0;
}

int main(){
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹 
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : funct                         
// 1          : $0 = a$1 + b$1                
// 2          : res$1 = $0                    
// 3          : param a$1                     
// 4          : param res$1                   
// 5          : $1 = call funct, 2            
// 6          : k$1 = $1                      
// 7          : return 0                      
// 
// 8          : main                          
// 9          : return 0                      
// 
