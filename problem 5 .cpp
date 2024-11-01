#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to add two binary numbers
string addBinary(string a, string b) {
    string result = "";  // To store the result
    int carry = 0;       // To store carry value
    int i = a.size() - 1, j = b.size() - 1;

    // Iterate from the end of both strings
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;

        if (i >= 0) {
            sum += a[i] - '0';  // Convert char to int
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';  // Convert char to int
            j--;
        }

        result += (sum % 2) + '0';  // Append the binary result of sum % 2
        carry = sum / 2;            // Update the carry
    }

    reverse(result.begin(), result.end());  // Reverse to get correct order
    return result;
}

// Main function
int main() {
    string binary1, binary2;

    // Prompt user to input the first binary number
    cout << "Please enter the first binary number (X): ";
    cin >> binary1;

    // Prompt user to input the second binary number
    cout << "Please enter the second binary number (Y): ";
    cin >> binary2;

    // Perform binary addition
    string sum = addBinary(binary1, binary2);

    // Output result with comments
    cout << "\n=== Result ===" << endl;
    cout << "The sum of the binary numbers " << binary1 << " and " << binary2 << " is: " << sum << endl;
    cout << "================" << endl;

    return 0;
}
