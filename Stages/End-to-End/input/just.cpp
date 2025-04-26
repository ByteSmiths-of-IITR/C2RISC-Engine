#include <iostream>

int foo(){
    int x = 0;
    int j = x++;
    if (j)
    {
        return 1;
    }
    else{
        return 0;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int k = foo();
    std::cout << "Value of k: " << k << std::endl;
    return 0;
}