// redeclaration of enum variable (enum constant) in the same scope
enum COLOR {RED, GREEN, BLUE};
int RED = 10; // error: ‘RED’ redeclared as different kind of symbol

// redefinition of struct 
struct A{
    int a;
    int b;
};

struct A{ // error: redefinition of ‘struct A’
    int x;
    int y;
};

// struct and variable name collision - no error here
int A = 10;
char a = 'a';

int main(){
    // no error
    int RED = 100;
    int A = 20;
}
