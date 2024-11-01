#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Function to find the k-th distinct string
std::string kthDistinct(std::vector<std::string>& arr, int k) {
    std::unordered_map<std::string, int> cnt;

    // Count occurrences of each string in the array
    for (const auto& s : arr) {
        ++cnt[s];
    }

    // Find the k-th distinct string in the order they appear
    for (const auto& s : arr) {
        if (cnt[s] == 1) { // Check if the string is distinct
            --k;
            if (k == 0) {
                return s; // Return the k-th distinct string
            }
        }
    }

    // If fewer than k distinct strings, return an empty string
    return "";
}

int main() {
    int n, k;
    std::cout << "Enter the number of strings in the array: ";
    std::cin >> n;

    std::vector<std::string> arr;
    std::string inputString;
    std::cout << "Enter each string followed by pressing Enter:\n";

    for (int i = 0; i < n; ++i) {
        std::cout << "String " << (i + 1) << ": ";
        std::cin >> inputString;
        arr.push_back(inputString);
    }

    std::cout << "Enter the value of k (position of distinct string to find): ";
    std::cin >> k;

    // Call the kthDistinct function and store the result
    std::string result = kthDistinct(arr, k);

    if (result.empty()) {
        std::cout << "There are fewer than " << k << " distinct strings in the array.\n";
    } else {
        std::cout << "The " << k << "-th distinct string in the array is: " << result << "\n";
    }

    return 0;
}

