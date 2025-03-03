#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

class Calculator {

public:

    double evaluate(const std::string& expression) {

        std::string postfix = infixToPostfix(expression);       // convert to postfix

        return evaluatePostfix(postfix);            // evaluate the expression
    }

private:
    // Convert the infix expression to postfix using the Shunting Yard Algorithm
    std::string infixToPostfix(const std::string& expression) {
        std::stack<char> operators;
        std::string output;
        int i = 0;

        while (i < expression.length()) {
            char token = expression[i];

            if (std::isdigit(token)) {

                while (i < expression.length() && std::isdigit(expression[i])) {
                    output += expression[i++];
                }
                output += " ";
            }
            else if (token == '(') {
                operators.push(token);
                i++;
            }
            else if (token == ')') {

                while (!operators.empty() && operators.top() != '(') {
                    output += operators.top();
                    output += " ";
                    operators.pop();
                }
                operators.pop();
                i++;
            }
            else if (isOperator(token)) {

                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    output += operators.top();
                    output += " ";
                    operators.pop();
                }
                operators.push(token);
                i++;
            }
            else {i++;}
        }

        while (!operators.empty()) {
            output += operators.top();
            output += " ";
            operators.pop();
        }

        return output;
    }


    // Evaluate the postfix expression
    double evaluatePostfix(const std::string& expression) {
        std::stack<double> stack;
        int i = 0;

        while (i < expression.length()) {
            char token = expression[i];

            if (std::isdigit(token)) {

                double number = 0;
                while (i < expression.length() && std::isdigit(expression[i])) {
                    number = number * 10 + (expression[i] - '0');
                    i++;
                }
                stack.push(number);
            }
            else if (isOperator(token)) {

                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();

                if (token == '+') stack.push(a + b);
                else if (token == '-') stack.push(a - b);
                else if (token == '*') stack.push(a * b);
                else if (token == '/') stack.push(a / b);
                i++;
            }
            else { i++; }
        }

        return stack.top();
    }

    // Function to return precedence of the operator
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // Check if character is an operator
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
};

