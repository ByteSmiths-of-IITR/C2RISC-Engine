// Run this code and gcc will tell you the type of each 
// variable and their different levels of constness.

int arr0[12][4];

int *arr1[12][4];

int (* arr2)[12][4];

int arr4[] = {1, 2, 3, 4};

struct Person
{
    char name[50];
    int age;
    float salary;
};

struct Person p1[10];

int *ptr;

int main()
{

    // arr0 = 'd';
    // arr0[0] = 'e';
    // arr0[0][0] = "f";
    arr1 = "d";
    arr1[0] = "e";
    arr1[0][0] = "f";
    arr2 = "d";
    *arr2 = "d";
    arr2[0] = "e";
    *arr2[0] = "e";
    arr2[0][0] = "f";
    *arr2[0][0] = "f";
    // int *arr0 = "d";

    // arr4 = 'd';
    // arr4[0] = 'e';
    // arr4[0][0] = "f";

    // p1 = 'd';
    // p1[0] = 'e';
    // p1[0][0] = "f";
    // ptr = "d";
    // ptr[0] = "e";

    return 0;
}