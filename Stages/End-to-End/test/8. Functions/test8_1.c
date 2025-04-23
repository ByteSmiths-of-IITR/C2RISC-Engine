// Function declarations
int add(int x, int y);
void printResult(int result);
float wrongReturn(); // Expected to return float

int main()
{
    int a = 5;
    float b = 3.2;

    // ❌ Mismatch #1: Passing float instead of int
    int sum = add(a, b); // Compiler may warn or implicitly cast

    // ❌ Mismatch #2: Passing no argument instead of one
    printResult(); // Missing required argument

    // ❌ Mismatch #3: Assigning float-returning function to int
    int bad = wrongReturn(); // Narrowing conversion from float to int

    return 0;
}

// Definitions
int add(int x, int y)
{
    return x + y;
}

void printResult(int result)
{
    // Do something
}

float wrongReturn()
{
    return 42.5;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Function Call expression "printResult" does not match the signature
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : a$1 = 5                       
// 2          : $0 = (float)3.200000          
// 3          : b$1 = $0                      
// 4          : $1 = (int)b$1                 
// 5          : param a$1                     
// 6          : param $1                      
// 7          : $2 = call add, 2              
// 8          : sum$1 = $2                    
// 9          : $3 = call wrongReturn, 0      
// 10         : $4 = (int)$3                  
// 11         : bad$1 = $4                    
// 12         : return 0                      
// 
// 13         : add                           
// 14         : $5 = x$2 + y$2                
// 15         : return $5                     
// 
// 16         : printResult                   
// 
// 17         : wrongReturn                   
// 18         : $6 = (float)42.500000         
// 19         : return $6                     
// 
