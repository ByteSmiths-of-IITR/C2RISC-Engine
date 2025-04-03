// variable scope conflict

void func(){
    {
        int A = 2;
    }
    int x = A; // error: ‘A’ undeclared (first use in this function)
}

int main(){
    x = 4; // error: ‘x’ undeclared (first use in this function)
    {
        int a = 2;
    }
    int b = a; // error: ‘a’ undeclared (first use in this function)
}