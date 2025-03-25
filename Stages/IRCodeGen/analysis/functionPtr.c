
// funtion pointer

int add(int x, int y)
{
    return x + y;
}

int (*fun_ptr)(int, int) = &add;

int main()
{
    int a = 10;
    float b = 20;
    int c = fun_ptr(a, b);
    c = add(a, b);
    return 0;
}