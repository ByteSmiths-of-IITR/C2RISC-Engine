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
// ❤️‍🔥 SignalHandler 💥SIGSEGV received. Exiting gracefully.
// ❤️‍🔥 SignalHandler 💥SIGSEGV received. Exiting gracefully.
// My Name is 54859and I am commiting Suicide 😵 at 2025-04-05 - 12:19:13 🪦
// 
// ------------------------------------------------------------------------------------
// The Last Function Called - SymbolNode::deleteCurrent
// 😎 Exiting gracefully 😎
// 
// ----------------------------------- SEMANTIC LOG -----------------------------------
// Error: Member Selection expression "$0" not found in symbol table
// Error: Member Selection expression "$1" not found in symbol table
// ----------------------------------- END OF LOG -----------------------------------
// 
// ------------------------------------------------------------------------------------
// 
