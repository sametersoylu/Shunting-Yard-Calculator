#pragma once 
#include "basic_calculator.hpp"
#include "parser.hpp"


namespace shunting_yard {
    inline int calculate(std::string expression) {
        basic_calculator<int> calc;
        std::stack<int> operands; 
        std::stringstream input{parser{}.parse(expression)};
        
        for(std::string token; std::getline(input, token, '#');) {
            if(not calc.operator_exists(token)) { operands.push(std::stoi(token)); continue; }
            int first = operands.top(); operands.pop();
            int second = operands.top(); operands.pop(); 
            int result = calc(token.back(), second, first);
            operands.push(result); 
        }
        return operands.top(); 
    }
}