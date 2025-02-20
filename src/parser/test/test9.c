#include <stdio.h>
#include <string.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    char name[50];
    int salary;
    struct Date joinDate;
    int performance[2][3];  // 2x3 array for performance metrics
};

int main() {
    struct Employee emp;
    strcpy(emp.name, "John Doe");
    emp.salary = 50000;
    emp.joinDate.day = 15;
    emp.joinDate.month = 6;
    emp.joinDate.year = 2020;
    
    // Initialize performance metrics
    int counter = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            emp.performance[i][j] = counter++;
        }
    }
    
    printf("Employee: %s\nSalary: %d\nJoin Date: %02d/%02d/%4d\n", 
           emp.name, emp.salary, emp.joinDate.day, emp.joinDate.month, emp.joinDate.year);
    printf("Performance Metrics:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", emp.performance[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
