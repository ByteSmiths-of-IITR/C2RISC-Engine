// using less than required arguments in function call
int func(int a, char ch){
    {
        int a = 2;
    }
    return a;
}

int main(){
    int a;
    func(a); // error: too few arguments to function ‘func’
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Function Call expression "func" does not match the signature
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : func                          
// 1          : a$2 = 2                       
// 2          : return a$1                    
// 
// 3          : main                          
// 4          : return 0                      
// 
