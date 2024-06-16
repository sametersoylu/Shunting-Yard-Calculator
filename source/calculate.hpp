#pragma once 
#include "basic_calculator.hpp"
#include "parser.hpp"
#include <string>
#include <type_traits>

namespace shunting_yard {
    template<typename T_>
    concept number_type = std::integral<T_> or std::floating_point<T_>;
    template<typename T_>
    concept addable = number_type<T_>; 

    template<typename T_>
    inline T_ string_to(const std::string& val) {
        // Floating point group.
        if constexpr (std::is_same_v<T_, float>) { return std::stof(val); }
        if constexpr (std::is_same_v<T_, double>) { return std::stod(val); }
        if constexpr (std::is_same_v<T_, long double>) { return std::stold(val); }

        // integer group.
        if constexpr (std::is_same_v<T_, int>) { return std::stoi(val); }
        if constexpr (std::is_same_v<T_, long>) { return std::stol(val); }
        if constexpr (std::is_same_v<T_, long long>) { return std::stoll(val); }
        if constexpr (std::is_same_v<T_, unsigned long>) { return std::stoul(val); }
        if constexpr (std::is_same_v<T_, unsigned long long>) { return std::stoull(val); }

    }

    template<number_type T_>
    inline T_ calculate(std::string expression) {
        basic_calculator<T_> calc;
        std::stack<T_> operands; 
        auto parsed = parser{}.parse(expression);
        std::stringstream input{parsed};
        
        for(std::string token; std::getline(input, token, '#');) {
            if(not calc.operator_exists(token)) { operands.push(string_to<T_>(token)); continue; }
            T_ first = operands.top(); operands.pop();
            T_ second = operands.top(); operands.pop(); 
            T_ result = calc(token.back(), second, first);
            operands.push(result); 
        }
        return operands.top(); 
    }

}