#include <stdio.h>

typedef unsigned int uint;

void process(int x, int y) {
    struct data {
        int id;
        char name[20];
    } d;

    int result = x + y;
    int *ptr = &result;

    // ❌ Syntax Error: `switch` missing parentheses
    switch result {  
    case 10: printf("Ten\n");
    break;
    case 20: printf("Twenty");
    break;
    default printf("Something else"); // ❌ Syntax Error: Missing colon in `default`
    }
}

int main() {
    uint a = 5;
    
    // ❌ Syntax Error: Incorrect `do-while` syntax
    do while (a > 0)  
        printf("%s\n", str);
    
    // ❌ Syntax Error: Function call without parentheses
    process 10, 20; 

    return 0;
}
