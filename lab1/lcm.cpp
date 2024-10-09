#include <iostream>
#include <cstdlib> 
using namespace std;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int plcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return abs(a * b) / gcd(a, b);
}

int main() {
    int num1, num2;

    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    int result = plcm(num1, num2);
    cout << "The least common multiple of " << num1 << " and " << num2 << " is " << result << endl;

    return 0;
}
