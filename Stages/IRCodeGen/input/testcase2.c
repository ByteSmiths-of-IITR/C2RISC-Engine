// int printf(char *, ...);

// class check
// {
//     int a;

// public:
//     void setA(int a);

// protected:
//     int b;
// };

union Data
{
    int intValue;
    float floatValue;
    char strValue[50];
};

void setA(int a)
{
}

// class newCheck : public check
// {
//     int c;
// };

// typedef class newCheck newType;

int main()
{
    // class check *temp = new class check();
    // class newCheck *temp1 = new class newCheck();
    // newType *temp2 = new class newCheck();
    void (*func_ptr)(int);
    int arr[10][20][30];
    func_ptr = &(setA);
    func_ptr(5);
    union Data data;
    data.intValue = 2006;
    data.floatValue = 2.2;
    ***(arr + 2) = 20;
    return 0;
}