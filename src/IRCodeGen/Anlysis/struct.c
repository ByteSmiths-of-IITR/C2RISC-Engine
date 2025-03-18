/*
struct_examples.c - Comprehensive usage of structs in C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1. Defining a struct Type */
struct Person
{
    char name[50];
    int age;
};

/* 2. Declaring a struct Variable */
struct Person p1;

/* 3. Defining and Declaring in One Step */
struct Animal
{
    char name[50];
    int age;
} a1, a2;

// /* 4. Using struct with typedef */ [NOTSUPPORTE]
// typedef struct
// {
//     char name[50];
//     int age;
// } Car;
// Car c1;

/* 5. Nested struct */
struct Address
{
    char city[50];
    int zip;
};
struct PersonWithAddress
{
    char name[50];
    int age;
    struct Address address;
};

/* 6. Pointer to struct */
struct Person *pPtr;

// 7. Dynamic Memory Allocation with struct [INVALIE]
// pPtr = (struct Person *)malloc(sizeof(struct Person));

/* 8. Array of struct */
struct Person persons[10];

/* 9. Array Inside a struct */
struct Classroom
{
    struct Person students[30];
};

/* 10. Pointer to an Array of struct */
struct Person (*pArray)[10];

/* 11. Function Returning a struct */
struct Person createPerson()
{
    struct Person p;
    strcpy(p.name, "Alice");
    p.age = 30;
    return p;
}

/* 12. Passing struct to a Function */
void displayPerson(struct Person p)
{
    printf("Name: %s, Age: %d\n", p.name, p.age);
}

/* 13. Passing Pointer to struct to a Function */
void modifyPerson(struct Person *p)
{
    p->age = 25;
}

/* 14. Anonymous struct */
struct
{
    int id;
    char name[50];
} employee;

/* 15. Bit Fields in struct */
struct Flags
{
    unsigned int isOn : 1;
    unsigned int hasError : 1;
};

/* 16. Self-Referential struct */
struct Node
{
    int data;
    struct Node *next;
};

/* 17. Flexible Array Members (C99) */
struct Flexible
{
    int length;
    int arr[];
};

// /* 18. typedef with Pointer struct */ [NOTSUPPORTED]
// typedef struct Person *PersonPtr;

/* 19. Structure Assignment */  
struct Person p2;
// p2 = p1; // In Global Scope P1 must be a constant

/* 20. Using const with struct */
const struct Person pConst = {"Bob", 40};

/* 21. Using volatile with struct */
volatile struct Device
{
    int status;
    int control;
} device;

/* 22. struct as Function Argument by Value */
void display(struct Person p)
{
    printf("Name: %s, Age: %d\n", p.name, p.age);
}

/* 23. struct as Function Argument by Reference */
void modify(struct Person *p)
{
    p->age = 35;
}

int main()
{
    p2 = p1; // Okay here
    p1 = createPerson();
    displayPerson(p1);
    modifyPerson(&p1);
    displayPerson(p1);

    struct PersonWithAddress pwa = {"Charlie", 25, {"New York", 10001}};
    printf("Name: %s, City: %s\n", pwa.name, pwa.address.city);

    free(pPtr); // Freeing allocated memory

    return 0;
}