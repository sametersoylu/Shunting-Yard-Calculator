#pragma once
#include <string>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <functional>

namespace shunting_yard {
    class parser {
        private:
        std::stack<char> operators; 
        std::unordered_map<char, std::pair<unsigned short, char>> precidence; 
        std::string tokenized; 
        
        template<typename signature>
        void do_for_once(bool& expr, std::function<signature> func) { if(expr) { func(); expr = false; } }
        
        std::string parse_(std::string tokenized_string) {
            if(tokenized_string.empty()) { return {}; }
            std::stringstream inp {tokenized_string}; 
            std::string output{}; 
            for(std::string bit{}; std::getline(inp, bit, '#');) {
                auto might_be_op = *bit.begin();
                if(not is_operator(might_be_op) and might_be_op != '(' and might_be_op != ')') { 
                    output += bit + "#"; 
                    continue; 
                }
                
                if(might_be_op == '(') { operators.push(might_be_op); continue; }
                
                if(might_be_op == ')') {
                    while(not operators.empty() and operators.top() != '(') {
                        output += operators.top() + std::string{"#"}; 
                        operators.pop(); 
                    }
                    operators.pop(); 
                    continue; 
                }
                 
                while(not operators.empty() and precidence_compare(might_be_op, operators.top()) == -1 and precidence[might_be_op].second == 'l') {
                    output += operators.top() + std::string{"#"}; 
                    operators.pop();
                }
                operators.push(might_be_op); 
            }
            while(not operators.empty()) {
                if(operators.top() == '(') {
                    throw std::invalid_argument("Given expression is invalid!"); 
                }
                output += operators.top() + std::string{"#"}; 
                operators.pop();
            }
            return output;
        }
        
        public: 
        parser() {
            precidence = {
                {'+', {2, 'l'}}, 
                {'-', {2, 'l'}},
                {'*', {3, 'l'}},
                {'/', {3, 'l'}},
                {'^', {4, 'r'}}
            }; 
        }
        bool is_numerical(char ch) {
            return '0' < ch and ch < '9'; 
        } 
        
        bool is_operator(char op) { 
            return precidence.find(op) != precidence.end(); 
        }
        
        short precidence_compare(char first, char second) {
            return 
            precidence[first].first < precidence[second].first ? -1 :
                precidence[first].first == precidence[second].first ? 0 : 
                    (first == '(' or second == '(' or first == ')' or second == ')') ? -2 : 1;
        }
        
        std::string add_token(std::string eq) {
            bool add_token_ = false, last_was_operand = false; 
            tokenized.clear(); 
            std::string aux; 
            for(auto ch : eq) {
                if(ch == ' ' and not aux.empty()) { add_token_ = true; continue; }
                do_for_once<void()>(add_token_, [&]() {
                    if(last_was_operand) { throw std::runtime_error("two operands can not be back to back"); }
                    tokenized += aux + "#"; 
                    aux.clear(); 
                    last_was_operand = true; 
                });
                if(is_numerical(ch)) { aux += ch; continue; }
                if(is_operator(ch) or ch == '(' or ch == ')') {
                    if(not aux.empty()) { tokenized += aux + "#"; aux.clear(); }
                    tokenized += std::string{ch} + "#"; 
                    last_was_operand = false; 
                    continue; 
                }
                if(not is_numerical(ch) and not is_operator(ch) and ch != ' ') { throw std::invalid_argument("The value you entered is not supported as an operand or an operator!"); }
            }
            if(not aux.empty()) {
                tokenized += aux + "#"; 
            }
            return tokenized; 
        }
        
        std::string parse(std::string expression) {
            add_token(expression); 
            return parse_(tokenized); 
        }
        
        std::string parse() {
            return parse_(tokenized);
        }
        
        std::string& get_tokenized() {
            return tokenized; 
        }
    };
}