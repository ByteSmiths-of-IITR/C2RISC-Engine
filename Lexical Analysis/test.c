#include <iostream>

class A {
    public:
        A() {
            std::cout << "Constructor called" << std::endl;
        }
        ~A() {
            std::cout << "Destructor called" << std::endl;
        }
};

int main() {
    A a;
    return 0;
}
