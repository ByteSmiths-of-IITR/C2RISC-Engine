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
    struct A a;
    struct A p = a;
    // foo(a);

    // int arr[5];
    // int ar[4];
    // foo(arr);
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase) 
// 
// ----------------------------------------------------------------------------------------------------
// 
// 
// 🅰️ ---- IR Code Before Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 8                 
// 2          : alloca p$1, 8                 
// 3          : alloca $0, 4                  
// 4          : $0 = a$1.offset               
// 5          : p$1 = $0                      
// 6          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
// 🅰️ ---- IR Code After Machine Independent Optimization 🅰️
// .text      : ------------------------------
// 0          : main: Func ENTER              
// 1          : alloca a$1, 8                 
// 2          : alloca p$1, 8                 
// 3          : alloca $0, 4                  
// 4          : $0 = a$1.offset               
// 5          : p$1 = $0                      
// 6          : main ret(4): EXIT             
// 
// ----------------------------------------------------------------------------------------------------
// 
