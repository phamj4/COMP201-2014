#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	{
		
		int sum = 0;
		ifstream input;
		ofstream output;
		int val;

		input.open(argv[1]);
		output.open("C:/Users/phamj4/Documents/Visual Studio 2013/Projects/Project1/output.txt");

		if (input.fail()) {
			cout << "Hey! pass a file in!" << endl;
		}

		while (input >> val) {
			sum = sum + val;
			cout << " " << val << " \t " << val*val << " \t " << sum << endl;
		}
		input.close();
		output.close();
	}
}
	
