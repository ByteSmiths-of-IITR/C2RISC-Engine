struct A{
    int a;
    int b;
};

// void foo(struct A p){
//     p.a = 5;
// }

// int foo(int arr[4]){
//     arr[2] = 5;
// }

int main(){
    // struct A a;
    // struct A p = a;
    // a.b = 5;
    // foo(a);

    int arr[5];
    int *p = arr + 1;
    // int ar[4];
    // foo(arr);
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
// 1          : alloca arr$1, 20              
// 2          : alloca p$1, 4                 
// 3          : alloca $0, 4                  
// 4          : $0 = arr$1.offset             
// 5          : alloca $1, 4                  
// 6          : $1 = 1 * 4                    
// 7          : alloca $2, 20                 
// 8          : $2 = $0 + $1                  
// 9          : (4)*p$1 = $2                  
// 10         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
// 🅰️ ---- IR Code After Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca arr$1, 20              
// 2          : alloca p$1, 4                 
// 3          : alloca $0, 4                  
// 4          : $0 = arr$1.offset             
// 5          : alloca $1, 4                  
// 6          : $1 = 4                        
// 7          : alloca $2, 20                 
// 8          : $2 = $0 + $1                  
// 9          : (4)*p$1 = $2                  
// 10         : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
