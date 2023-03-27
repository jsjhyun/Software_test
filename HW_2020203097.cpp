

// Á¤Çö_2020203097

#include <stack>
#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
using namespace std;

int error_flag1 = 0;
int error_flag2 = 0;

void evaluate_stack(stack<double>& numbers, stack<char>& operations)
{
	while (!operations.empty())
	{
		if (operations.top() == '(' || operations.top() == '{' || operations.top() == '[')
			break;

		double operand1, operand2;
		operand2 = numbers.top();
		numbers.pop();
		operand1 = numbers.top();
		numbers.pop();

		switch (operations.top())
		{
		case '+': numbers.push(operand1 + operand2); break;
		case '-': numbers.push(operand1 - operand2); break;
		case '*': numbers.push(operand1 * operand2); break;
		case '/': numbers.push(operand1 / operand2);
			if (operand2 == 0) {
				cout << "Error!: divide by zero" << endl;
				++error_flag1;
				break;
			}
		}
		operations.pop();
	}
}

double read_and_evaluate(istream& ins)
{
	stack<double> numbers;
	stack<char> operations;
	double number;
	char symbol;

	while (ins && ins.peek() != 'E')
	{
		while (ins && ins.peek() != '\n')
		{
			error_flag1 = 0;
			if (isdigit(ins.peek()))
			{
				ins >> number;
				numbers.push(number);
			}
			else if (strchr("+-*/", ins.peek()))
			{
				ins >> symbol;
				if (symbol == '+' || symbol == '-')
					evaluate_stack(numbers, operations);

				operations.push(symbol);
			}
			else if (ins.peek() == ')')
			{
				ins >> symbol;
				operations.push(symbol);
				char opt = operations.top();
				while (opt != '(')
				{
					operations.pop();
					evaluate_stack(numbers, operations);
					opt = operations.top();
					if (operations.size() == 1 && opt != '(')
					{
						cout << "Error!: unbalanced parentheses" << endl;
						++error_flag2;
						break;
					}
				}
				if (error_flag2 != 0)
				{
					error_flag2 = 0;
					cin.ignore(100, '\n');
				}
				operations.pop();
			}
			else if (ins.peek() == '}')
			{
				ins >> symbol;
				operations.push(symbol);
				char opt = operations.top();
				while (opt != '{')
				{
					operations.pop();
					evaluate_stack(numbers, operations);
					opt = operations.top();
					if (operations.size() == 1 && opt != '{')
					{
						cout << "Error!: unbalanced parentheses" << endl;
						++error_flag2;
						break;
					}
				}
				if (error_flag2 != 0)
				{
					error_flag2 = 0;
					cin.ignore(100, '\n');
				}
				operations.pop();
			}
			else if (ins.peek() == ']')
			{
				ins >> symbol;
				operations.push(symbol);
				char opt = operations.top();
				while (opt != '[')
				{
					operations.pop();
					evaluate_stack(numbers, operations);
					opt = operations.top();
					if (operations.size() == 1 && opt != '[')
					{
						cout << "Error!: unbalanced parentheses" << endl;
						++error_flag2;
						break;
					}
				}
				if (error_flag2 != 0)
				{
					error_flag2 = 0;
					cin.ignore(100, '\n');
				}
				operations.pop();
			}
			else if (ins.peek() == '(')
			{
				ins >> symbol;
				operations.push(symbol);
			}
			else if (ins.peek() == '{')
			{
				ins >> symbol;
				operations.push(symbol);
			}
			else if (ins.peek() == '[')
			{
				ins >> symbol;
				operations.push(symbol);
			}
		}
		ins.ignore();
		evaluate_stack(numbers, operations);
		if (error_flag1 == 0)
		{
			cout << fixed;
			cout.precision(3);
			cout << numbers.top() << endl;
			numbers.pop();
		}
	}
	return 0;
}

int main()
{
	read_and_evaluate(cin);
}