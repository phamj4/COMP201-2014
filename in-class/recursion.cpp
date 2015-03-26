#include <iostream>

using namespace std;

// Recursion
// 5! = 5 * 4 * 3 * 2 * 1
// factorial 0 = 1
// factorial n = n * factorial (n-1)
int factorial(int n) {
//  Base case
    if (n == 0) { return 1; }
//  Recursive case
    else {
        return n * factorial (n-1);
    }
}

int main() {
    cout << factorial(5);
    return 0;
}