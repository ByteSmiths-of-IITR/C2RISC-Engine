
#include <stdio.h>
enum Color
{
    RED,
    GREEN,
    BLUE
};

int main(){
    enum Color favorite = GREEN;
    if (favorite == GREEN)
    {
        printVar(favorite);
    }
    return 0;
}