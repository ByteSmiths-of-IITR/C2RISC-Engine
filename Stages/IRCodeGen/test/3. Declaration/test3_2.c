// use AST to check for proper type assignment for...
// static and const - NO GCC ERROR

static int a1 = 1;
const int b1 = 2;
static const int c1 = 3;
int d1 = 9;

void func(){
    static int a2 = 1;
    const int b2 = 2;
    static const int c2 = 3;
    int d2 = 9;
}

int main(){
    static int a3 = 1;
    const int b3 = 2;
    static const int c3 = 3;
    int d3 = 9;

    return 0;
}
