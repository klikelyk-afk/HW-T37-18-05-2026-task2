#include <iostream>
#include <string>
#include "MyStack.h"

using namespace std;

int getPriority(char sign) {
    if (sign == '*' || sign == '/') return 2;
    if (sign == '+' || sign == '-') return 1;
    return 0;
}

string postfix_record(string line) {
    string answer = "";
    myStack::Stack<char> sign;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') continue;

        if (isdigit(line[i])) {
            while (i < line.length() && isdigit(line[i])) {
                answer += line[i++];
            }
            answer += " ";
            i--;
        }
        else if (line[i] == '(') {
            sign.push(line[i]);
        }
        else if (line[i] == ')') {
            while (!sign.isEmpty() && sign.top() != '(') {
                answer += sign.top();
                answer += " ";
                sign.pop();
            }
            if (!sign.isEmpty()) sign.pop();
        }
        else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') {
            while (!sign.isEmpty() && getPriority(sign.top()) >= getPriority(line[i])) {
                answer += sign.top();
                answer += " ";
                sign.pop();
            }
            sign.push(line[i]);
        }
    }

    while (!sign.isEmpty()) {
        answer += sign.top();
        answer += " ";
        sign.pop();
    }
    return answer;
}

int calculateRPN(const string& expression) {
    myStack::Stack<int> stack;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') continue;

        if (isdigit(expression[i]) || (expression[i] == '-' && i + 1 < expression.length() && isdigit(expression[i + 1]))) {
            string token = "";

            if (expression[i] == '-') {
                token += expression[i++];
            }
            while (i < expression.length() && isdigit(expression[i])) {
                token += expression[i++];
            }
            i--;

            stack.push(stoi(token));
        }

        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            int operand2 = stack.top(); stack.pop();
            int operand1 = stack.top(); stack.pop();

            if (expression[i] == '+') stack.push(operand1 + operand2);
            else if (expression[i] == '-') stack.push(operand1 - operand2);
            else if (expression[i] == '*') stack.push(operand1 * operand2);
            else if (expression[i] == '/') stack.push(operand1 / operand2);
        }
    }
    return stack.top();
}

int main() {
    string rpn_example = "4 5 7 2 + - *";

    cout << "--- RPN Calculation ---" << endl;
    cout << "Input RPN: " << rpn_example << endl;
    cout << "Result: " << calculateRPN(rpn_example) << endl;

    string infix = "(2 + 3) * 4";
    string converted = postfix_record(infix);
    cout << "\n--- Custom Test ---" << endl;
    cout << "Infix: " << infix << endl;
    cout << "Converted to RPN: " << converted << endl;
    cout << "Result: " << calculateRPN(converted) << endl;

    return 0;
}