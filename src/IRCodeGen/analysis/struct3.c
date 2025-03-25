#include <stdio.h>

int main()
{
    struct Person
    {
        int age;
    };
    {
        struct Person p2;
        p2.age = 10;
        printf("%d\n", p2.age);

        struct Person
        {
            int gender;
        };

        int Person = 10;
        printf("%d\n", Person);

        struct Person p3;
        p3.gender = 1;
        printf("%d\n", p3.gender);
    }

    struct Person p1;
    p1.age = 20;
    printf("%d\n", p1.age);

    int Person = 190;
}