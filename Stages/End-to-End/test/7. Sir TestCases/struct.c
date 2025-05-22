

#include <stdio.h>

struct Point
{
    int x;
    int y;
};

int main()
{
    struct Point p;
    p.x = 18;
    p.y = 4;
    int p_sum = p.x / p.y;
    printVar(p_sum);
    return 0;
}