#include "calculate.hpp"
#include <iostream>

int main() {
    std::cout << shunting_yard::calculate("2 ^ 3"); 
    return 0; 
}