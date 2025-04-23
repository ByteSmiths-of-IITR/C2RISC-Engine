#include <stdio.h>

// Define an enum for days of the week
enum Day
{
    SUNDAY,    // 0
    MONDAY,    // 1
    TUESDAY,   // 2
    WEDNESDAY, // 3
    THURSDAY,  // 4
    FRIDAY,    // 5
    SATURDAY   // 6
};

// Function to check if it's a weekend
int isWeekend(enum Day d)
{
    return (d == SUNDAY || d == SATURDAY);
}

int main()
{
    enum Day today = FRIDAY;

    

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
// 0          : isWeekend                     
// 1          : $0 = d$1 == 0                 
// 2          : $1 = d$1 == 6                 
// 3          : $2 = $0 || $1                 
// 4          : return $2                     
// 
// 5          : main                          
// 6          : today$2 = 5                   
// 7          : return 0                      
// 
