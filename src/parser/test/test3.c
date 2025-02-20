#include <stdio.h>

// Define a structure for a person
struct Person {
    char name[50];
    int age;
};

// Function that takes a Person structure as an argument
void displayPerson(struct Person p) {
    printf("Name: %s, Age: %d\n", p.name, p.age);
}

int main() {
    struct Person person;
    char c[50];
    printf("Enter name: ");
    scanf("%s", person.name);
    printf("Enter age: ");
    scanf("%d", &person.age);
    
    displayPerson(person);
    return 0;
}
