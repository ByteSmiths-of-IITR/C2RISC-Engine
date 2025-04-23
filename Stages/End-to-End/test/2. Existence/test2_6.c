// struct not defined in this scope; 
// struct member not defined
int main()
{
    {
        struct Person
        {
            int gender;
        };

        struct Person p;
        p.gender = 1;
        p.age = 10; // error: ‘struct Person’ has no member named ‘age’
    }

    struct Person p1; // error: storage size of ‘p1’ isn’t known
    p1.age = 20;

    int Person = 190;
}

//=========================== C2RISC-Engine =========================================================//
// Lexical Analysis 👍 | Syntax Analysis 👍 | Semantic Analysis ❌
// 
// ------------------------------------------------------------------------------------
// ----------------------------------- SEMANTIC LOG -----------------------------------
// SEMANTIC ERROR ‼️ : Member "age" not found in record "Person"
// SEMANTIC ERROR ‼️ : RecordID "Person" not found
// SEMANTIC ERROR ‼️ : Identifier "p1" not 🫠 found in the current scope
// SEMANTIC ERROR ‼️ : Function 'main's return type is not void but no return statement found
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// CodeLineNo : TAC                           
// ---------- : -------------------------------
// 
// 0          : main                          
// 1          : $0 = p$2.offset               
// 2          : $1 = $0 + 0                   
// 3          : *$1 = 1                       
// 4          : $2 = p$2.offset               
// 5          : Person$1 = 190                
// 
