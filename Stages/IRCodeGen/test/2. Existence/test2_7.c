// union declaration and its obj scope errors

union U{
    int a;
}obj;

void func(){
    obj.a = 2;
    union U{ // no redefinition error
        int a;
    }obj;
}

int main(){
    obj.b = 'c'; // error: ‘union U’ has no member named ‘b’
    {
        union U1{
            char b;
        }obj1;
    }
    obj1.b = 'd'; // error: ‘obj1’ undeclared (first use in this function)
    return 0;
}