int foo(){
    return 1 + 3;
}
int a = 3;

int main(){
    int a = foo();
}

int b = 0;
//=========================== C2RISC-Engine =========================================================//
// 🌴 APTree 🌴 has been generated, can be used for debugging ❤️‍🩹
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | Machine Independent Optimization 👍 |  🔖 IRCode Gen
// 😊 Thanku for using our "C2RISC-Engine" (Till IR Phase)
//
// ----------------------------------------------------------------------------------------------------
//
//  ---- IR Code Before Machine Independent Optimization ----
// .text      : ------------------------------
// 0          : foo: Func ENTER
// 1          : alloca $0, 4
// 2          : $0 = 1 + 3
// 3          : return $0
// 4          : foo ret(4): EXIT
//
// 5          : main: Func ENTER
// 6          : alloca a$2, 4
// 7          : alloca $1, 4
// 8          : $1 = call foo, 0
// 9          : a$2 = $1
// 10         : return
// 11         : main ret(4): EXIT
//
// ----------------------------------------------------------------------------------------------------
//
//  ---- IR Code After Machine Independent Optimization ----
// .text      : ------------------------------
// 0          : foo: Func ENTER
// 1          : alloca $0, 4
// 2          : $0 = 4
// 3          : return $0
// 4          : foo ret(4): EXIT
//
// 5          : main: Func ENTER
// 6          : alloca a$2, 4
// 7          : alloca $1, 4
// 8          : $1 = call foo, 0
// 9          : a$2 = $1
// 10         : return
// 11         : main ret(4): EXIT
//
// ----------------------------------------------------------------------------------------------------
//
