struct Test { int x; } t;

// int arr[10];

int *ptr;

int func(int *a, int b) {
    return 0;
}

struct A {
    int x;
};

float arr(){
    return 0.0f;
}

int main() {
    int* a;
    a[0];
    int b;
    // func();
    func(a, b); // error: ‘b’ undeclared (first use in this function)

    struct A *ptr;

    t.x;
    // ptr->x; //  error: request for member ‘x’ in something not a structure or union

    a++; 
    a--;

    struct A t;

    // Negative Cases
    arr();  // error: called object ‘arr’ is not a function or function pointer
    t.x;  // error: invalid type argument of ‘->’ (have ‘struct Test’)
    
    return 0;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// 
// ------------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : func                          
// 1          : return 0                      
// 
// 2          : arr                           
// 3          : return 0.000000               
// 
// 4          : main                          
// 5          : $0 = 0 * 4                    
// 6          : $1 = a$3 + $0                 
// 7          : param a$3                     
// 8          : param b$3                     
// 9          : $2 = call func, 2             
// 10         : $3 = t$0.offset               
// 11         : $4 = $3 + 0                   
// 12         : $5 = a$3                      
// 13         : a$3 = a$3 + 4                 
// 14         : $6 = a$3                      
// 15         : a$3 = a$3 - 4                 
// 16         : $7 = call arr, 0              
// 17         : $8 = t$3.offset               
// 18         : $9 = $8 + 0                   
// 19         : return 0                      
// 
