#pragma once 
#include <unordered_map>
#include <functional>
#include <stdexcept>

namespace shunting_yard {
    template<typename T_>
    class basic_calculator {
        private: 
        std::unordered_map<char, std::function<T_(std::pair<T_, T_>)>> calculators; 
        public: 
        // Calculator function declerations. These are the holders for our calculations. 
        // This gives us flexibility to add more functions in the feature and is faster since
        // unordered_map is O(1) access. 
        basic_calculator() : calculators({
            {'+', [](std::pair<T_, T_> operands) -> T_ {
                return operands.first + operands.second;
            }},
            {'-', [](std::pair<T_, T_> operands) -> T_ {
                return operands.first - operands.second;
            }},
            {'*', [](std::pair<T_, T_> operands) -> T_ {
                return operands.first * operands.second; 
            }}, 
            {'/', [](std::pair<T_, T_> operands) -> T_ {
                if(operands.second == 0) { throw std::invalid_argument("Divison by 0 is requested!"); }
                return operands.first / operands.second; 
            }}, 
            {'^', [](std::pair<T_, T_> operands) -> T_ {
                T_ temp = operands.first; 
                for(int i{}; i < operands.second - 1; i++) {
                    temp *= operands.first; 
                }
                return temp; 
            }}
        }) {}
        T_ operator()(char operator_, std::pair<T_, T_> operands) {
            return calculators[operator_](operands); 
        }
        T_ operator()(char operator_, T_ first, T_ second) {
            return calculators[operator_]({first, second}); 
        }
        std::function<T_(std::pair<T_, T_>)>& operator[](char& operator_) {
            return calculators[operator_]; 
        }
        decltype(calculators) GetMap() {
            return calculators;
        }
        bool operator_exists(const std::string& op) {
            return calculators.find(*op.begin()) != calculators.end(); 
        }
    }; 
}

