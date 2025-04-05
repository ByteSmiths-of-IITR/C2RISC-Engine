// union declaration and its obj scope errors

union U{
    int a;
}obj;

void func(){
    obj.a = 2;
    union U{ // no redefinition error
        int a;
    }obj;
}

int main(){
    obj.b = 'c'; // error: ‘union U’ has no member named ‘b’
    {
        union U1{
            char b;
        }obj1;
    }
    obj1.b = 'd'; // error: ‘obj1’ undeclared (first use in this function)
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Member "b" not found in record "U"
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 0          : func                          
// 1          : $0 = obj$0.offset             
// 2          : $1 = $0 + 0                   
// 3          : *$1 = 2                       
// 4          : main                          
// 5          : $2 = obj$0.offset             
// 
