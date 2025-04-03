struct COLOR{
    int r, g,b;
};

enum COLOR{ RED, GREEN, BLUE, WHITE, BLACK }; // error: ‘COLOR’ defined as wrong kind of tag

int main(){
    struct COLOR c; // error: storage size of ‘c’ isn’t known
    c.r = 10;
    c.g = 20;
    c.b = 30;
    enum COLOR color = RED; // variable ‘color’ has initializer but incomplete type; storage size of ‘color’ isn’t known
    return 0;
}