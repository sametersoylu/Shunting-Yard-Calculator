#pragma once 
#include "basic_calculator.hpp"
#include "parser.hpp"
#include <stdexcept>


namespace shunting_yard {
    template<typename T_>
    inline T_ calculate(std::string expression) {
        throw std::invalid_argument("not implemented!"); 
    }

    template<>
    inline int calculate<int>(std::string expression) {
        basic_calculator<int> calc;
        std::stack<int> operands; 
        auto parsed = parser{}.parse(expression);
        std::stringstream input{parsed};
        
        for(std::string token; std::getline(input, token, '#');) {
            if(not calc.operator_exists(token)) { operands.push(std::stoi(token)); continue; }
            int first = operands.top(); operands.pop();
            int second = operands.top(); operands.pop(); 
            int result = calc(token.back(), second, first);
            operands.push(result); 
        }
        return operands.top(); 
    }

    template<>
    inline float calculate<float>(std::string expression) {
        basic_calculator<float> calc;
        std::stack<float> operands; 
        auto parsed = parser{}.parse(expression);
        std::stringstream input{parsed};
        
        for(std::string token; std::getline(input, token, '#');) {
            if(not calc.operator_exists(token)) { operands.push(std::stof(token)); continue; }
            float first = operands.top(); operands.pop();
            float second = operands.top(); operands.pop(); 
            float result = calc(token.back(), second, first);
            operands.push(result); 
        }
        return operands.top(); 
    }
}