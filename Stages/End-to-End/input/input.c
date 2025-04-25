int main(){
    char *str = "int a; int *p; if (a) a = 1; else a = 2;";
}


//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis 👍 | 🔖 IRCode Gen
// RISC-V Code Generation completed successfully 
// 
// ----------------------------------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------------------------------
// ====================== [ CFG Code ] ======================
// .data
// 
// .text
// ENTRY : 
// main : 
//     0 : main: Func ENTER          | Default            | 
//     1 : alloca str$1, 4           | str$1 ☠️           | 
//     2 : str$1 = @str$0            | Default            | 
//     3 : main ret(4): EXIT         | Default            | 
// EXIT : 
// .data
// 
// .text
//     main:
//         # ENTRY Activation (start) - main
//         add   sp, sp, -20
//         sw    s0, 12(sp)
//         add   s0, sp,20
//         # ENTRY Activation (end) - main
//         # EXIT Activation (start) - main
//         lw    a1, 12(s0)
//         lw    a2, 0(a0)
//         sw    a2, 0(a1)
//         lw    ra, 16(sp)
//         lw    s0, 12(sp)
//         addi  sp, sp, 20
//         jr    ra
//         # EXIT Activation (end) - main
// 
// 
