#include "calculate.hpp"
#include "parser.hpp"
#include <iostream>

int main() {
    std::cout <<shunting_yard::calculate("2 + 3 * (3 + 5) "); 
    return 0; 
}