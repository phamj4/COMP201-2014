#include <iostream>
#include <stack>
#include <math.h>

void calculation(int number1, int number2, int number3, int number4, char check);
using namespace std;
stack<int> a;

int main() 
{

	bool value = false;
	char check;
	char done;

	int number1, number2, number3, number4;

	cout << "Reverse Polish Notation : " << endl;
	cout << "Enter expression: " << endl;
	while (!value)
	{
		cin >> number1;
		cin >> number2;
		cin >> number3;
		cin >> number4;
		cin >> check;

		calculation(number1, number2,number3,number4 , check);
		if (!cin)
			value = false;
		else
		{
			value = true;
			calculation(number1, number2,number3,number4, check);
		}
	}
	cout << "Your expression is " << a.top() << endl;
}

void calculation(int number1, int number2, int number3, int number4, char check)
{
	switch (check)
	{
	case '+':
		a.push((number1 - number2) + (number3 * number4));
		break;
	case '-':
		a.push((number1 - number2) - (number3 * number4));
		break;
	case '*':
		a.push((number1 - number2) * (number3 * number4));
		break;
	case '/':
		a.push((number1 - number2) / (number3 * number4));
		break;

	}
}