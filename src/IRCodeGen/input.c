struct A{
    int a;
    int b;
};

int main(){

    struct A obj2;

    enum A
    {
        a,
        b
    };

    enum A obj = a;

    obj = obj2;
}