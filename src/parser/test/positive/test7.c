#include <stdio.h>

// Define a structure for a student
struct Student
{
    char name[50];
    int age;
    float grades[3]; // Array to store 3 grades
};

// Function that takes a Student structure as an argument
void displayStudent(struct Student s)
{
    printf("Name: %s, Age: %d\n", s.name, s.age);
    printf("Grades: %.2f, %.2f, %.2f\n", s.grades[0], s.grades[1], s.grades[2]);
}

int main()
{
    struct Student student;

    // Taking input for the student
    printf("Enter name: ");
    scanf("%s", student.name);
    printf("Enter age: ");
    scanf("%d", &student.age);
    printf("Enter 3 grades: ");
    for (int i = 0; i < 3; i++)
    {
        scanf("%f", &student.grades[i]);
    }

    // Calling function to display the student
    displayStudent(student);

    // Pointer to structure
    struct Student *ptr = &student;
    printf("Accessing via pointer: Name = %s, Age = %d\n", ptr->name, ptr->age);

    return 0;
}
