#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>

class Calculator {

public:

    double evaluate(const std::string& expression) {

        std::string postfix = infixToPostfix(expression);

        return evaluatePostfix(postfix);
    }

private:

    std::string infixToPostfix(const std::string& expression) {
        std::stack<char> operators;
        std::ostringstream output;

        for (int i = 0; i < expression.length(); ++i) {
            char token = expression[i];

            if (std::isdigit(token)) {

                while (i < expression.length() && std::isdigit(expression[i])) {
                    output << expression[i++];
                }
                output << " ";
                --i;
            }
            else if (token == '(') {
                operators.push(token);
            }
            else if (token == ')') {

                while (!operators.empty() && operators.top() != '(') {
                    output << operators.top() << " ";
                    operators.pop();
                }
                operators.pop();
            }
            else if (token == '+' || token == '-' || token == '*' || token == '/') {

                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    output << operators.top() << " ";
                    operators.pop();
                }
                operators.push(token);
            }
        }


        while (!operators.empty()) {
            output << operators.top() << " ";
            operators.pop();
        }

        return output.str();
    }


    double evaluatePostfix(const std::string& expression) {
        std::stack<double> stack;
        std::istringstream input(expression);
        std::string token;

        while (input >> token) {
            if (isdigit(token[0])) {

                stack.push(std::stod(token));
            }
            else {

                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();

                if (token == "+") stack.push(a + b);
                else if (token == "-") stack.push(a - b);
                else if (token == "*") stack.push(a * b);
                else if (token == "/") stack.push(a / b);
            }
        }


        return stack.top();
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
};


