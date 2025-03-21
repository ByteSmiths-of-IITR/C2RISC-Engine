struct A{
    int a;
    int b;
};

int main(){
    struct A obj1;

    struct A{
        int a;
        int b;
    };

    struct A obj2;

    obj1 = obj2;
    return 0;
}