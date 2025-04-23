#include <iostream>
#include "utility.h"

int main(){
    std::string a = ">";
    std::string b = escapeCharacters(a);
    std::cout << b << std::endl;
}