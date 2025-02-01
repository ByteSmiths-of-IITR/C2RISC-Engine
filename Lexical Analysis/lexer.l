/*** Definition Section has one variable
which can be accessed inside yylex() 
and main() ***/
%{

// Include necessary header files
#include <iostream>
using namespace std;

// 






int count = 0;
%}

/*** Rule Section has three rules, first rule 
matches with capital letters, second rule
matches with any character except newline and 
third rule does not take input after the enter***/
%%
[A-Z]   {return 1;}
\n      {return 3;}
[0-9]+  {printf("?");}
.       {ECHO;}
%%

/*** Code Section prints the number of
capital letter present in the given input***/
int yywrap(){
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    // Open input and output files
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");

    if (!yyin || !yyout) {
        cout << "Error opening files\n";
        return 1;
    }

    int scanner = yylex();
    while(scanner != 0){
        scanner = yylex();
    }

    // Print count of capital letters
    cout << "Number of capital letters: " << count << endl;

    // Close files
    fclose(yyin);
    fclose(yyout);

return 0;
}
