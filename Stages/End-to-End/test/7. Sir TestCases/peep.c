
#include <stdio.h>
int main()
{
    int a = 5, b = 10, c = 15, d = 20;

    // Redundant calculation
    int x = a * 2;
    int y = a + a;

    // Constant folding
    int z = 4 * 5;
    float w = 30.0 / 5.0;

    // Strength reduction
    int u = d * 8;

    // Dead code (if optimization is enabled)
    int unused = 100;

    // Combine multiple increments
    int counter = 0;
    counter = counter + 1;
    counter = counter + 1;
    counter = counter + 1;

    int temp = b;
    temp = temp; // Useless assignment

    if (1)
    {
        printVar(1);
    }
    else
    {
        printVar(2);
    }

    printVar(x);
    printVar(y);
    printVar(z);
    printVar(w);
    printVar(u);
    printVar(counter);

    return 0;
}
