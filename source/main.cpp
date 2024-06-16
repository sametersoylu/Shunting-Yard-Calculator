#include "calculate.hpp"
#include <iostream>

int main() {
    std::cout << shunting_yard::calculate<int>("2.5 + 3 * (3 + 5)") << std::endl // 26
              << shunting_yard::calculate<float>("2 + 2 * (3.5 * (2.1 + 2.2))") << std::endl
    ;

    return 0; 
}