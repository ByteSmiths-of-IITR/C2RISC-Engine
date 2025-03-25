// #include <stdio.h>
enum Color
{
    RED,
    GREEN,
    BLUE
};

enum
{
    // RED, // THis will conflict with the previous RED
    YELLOW = 9,
    ORANGE,
    PINK
} abc;

int main()
{
    enum Color c = 90;
    // printf("%d\n", c);

    int hede = YELLOW;
    // printf("%d\n", hede);

    abc = ORANGE;
    // printf("%d\n", abc);

    enum Color2
    {
        RED = 3, // This will NOT conflict with the previous RED as scope is incremented.
        GREEN,
        BLUE
    };

    int BLUE = 9;

    c = RED;
    int d = BLUE;
    int e = GREEN;
    // printf("%d\n", c);
    // printf("%d\n", d);
    return 0;
}