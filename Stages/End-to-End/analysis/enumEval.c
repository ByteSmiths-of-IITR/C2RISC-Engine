struct A
{
    int a;
    int b = 1; // error: field's member initializer is not a constant expression
};

const int var = 33; // constant variable can be used in enum

enum color
{
    RED,
    BLUE = RED + 1,
    Green = var
};

int main() {}