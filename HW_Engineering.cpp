//2020203099 박재규

// 수정 후 코드
#include <stack>
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

int zero_error = 0;
int paren_error = 0;

void evaluate_stack(stack<double>& numbers, stack<char>& operations);

double read_and_evaluate(istream& ins) {
    stack<double> numbers;
    stack<char> operations;

    double number;
    char symbol;

    while (ins && ins.peek() != 'E') {
        while (ins && ins.peek() != '\n') {
            zero_error = 0;
            
            if (isdigit(ins.peek()) || ins.peek() == '.') {
                ins >> number;
                numbers.push(number);
            }
            else if (strchr("+-*/", ins.peek()) != NULL) {
                ins >> symbol;
                if (symbol == '+' || symbol == '-') {
                    evaluate_stack(numbers, operations);
                }
                operations.push(symbol);
            }
            
            else if (ins.peek() == '(') {
                ins >> symbol;
                operations.push(symbol);
            }
            else if (ins.peek() == '{') {
                ins >> symbol;
                operations.push(symbol);
            }
            else if (ins.peek() == '[') {
                ins >> symbol;
                operations.push(symbol);
            }
            
            else if (ins.peek() == ')') {
                ins >> symbol;
                operations.push(symbol);
                char oper = operations.top();
                while (oper != '(') {
                    operations.pop();
                    evaluate_stack(numbers, operations);
                    oper = operations.top();
                    if (operations.size() == 1 && oper != '(') {
                        cout << "Error!: unbalanced parentheses" << endl;
                        paren_error = 1;
                        break;
                    }
                }
                if (paren_error != 0) {
                    paren_error = 0;
                    ins.ignore(100, '\n');
                }
                operations.pop();
            }
            else if (ins.peek() == '}') {
                ins >> symbol;
                operations.push(symbol);
                char oper = operations.top();
                while (oper != '{') {
                    operations.pop();
                    evaluate_stack(numbers, operations);
                    oper = operations.top();
                    if (operations.size() == 1 && oper != '{') {
                        cout << "Error!: unbalanced parentheses" << endl;
                        paren_error = 1;
                        break;
                    }
                }
                if (paren_error != 0) {
                    paren_error = 0;
                    ins.ignore(100, '\n');
                }
                operations.pop();
            }
            else if (ins.peek() == ']') {
                ins >> symbol;
                operations.push(symbol);
                char oper = operations.top();
                while (oper != '[') {
                    operations.pop();
                    evaluate_stack(numbers, operations);
                    oper = operations.top();
                    if (operations.size() == 1 && oper != '[') {
                        cout << "Error!: unbalanced parentheses" << endl;
                        paren_error = 1;
                        break;
                    }
                }
                if (paren_error != 0) {
                    paren_error = 0;
                    ins.ignore(100, '\n');
                }
                operations.pop();
            }
        }
        ins.ignore();
        evaluate_stack(numbers, operations);

        if (zero_error == 0) {
            cout << fixed;
            cout.precision(3);
            cout << numbers.top() << endl;
            numbers.pop();
        }
    }
    return 0;
}

void evaluate_stack(stack<double>& numbers, stack<char>& operations) {
    while (!operations.empty()) {
        if (operations.top() == '(' || operations.top() == '{' || operations.top() == '[') {
            break;
        }

        double operand1, operand2;
        operand2 = numbers.top();
        numbers.pop();
        operand1 = numbers.top();
        numbers.pop();
        char oper;
        oper = operations.top();
        operations.pop();

        switch (oper) {
        case '+': numbers.push(operand1 + operand2);
                break;
        case '-': numbers.push(operand1 - operand2);
                break;
        case '*': numbers.push(operand1 * operand2);
                break;
        case '/': numbers.push(operand1 / operand2);
            if (operand2 == 0) {
                cout << "Error!: divided by zero" << endl;
                zero_error = 1;
                break;
            }
        }
    }
}

int main() {
    read_and_evaluate(cin);
}