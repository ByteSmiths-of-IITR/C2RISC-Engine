#include <iostream>

int main() {
    int num1, num2, product;

    std::cout << "Enter two numbers: ";
    std::cin >> num1 >> num2;

    product = num1 * num2;

    std::cout << "Product: " << product << std::endl;

    return 0;
}