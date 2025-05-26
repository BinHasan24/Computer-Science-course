#include <iostream>

//--- Base case: when there is only one argument left(just print it)
template<typename T>
void print(T&& arg) {
    std::cout << std::forward<T>(arg) << '\n';
}

//--- Recursive case: print the first argument, then the rest
template<typename T, typename... Args>
void print(T&& first, Args&&... rest) {
    std::cout << std::forward<T>(first) << ' ';
    print(std::forward<Args>(rest)...);  // recursive call with other remaining arguments
}

int main() {
    int a = 42;
    std::string name = "MIPT";
    double pi = 3.14;

    // --- Various test cases
    print("Hello", name, a, pi);
    print(1, 2, 3, 4, 5);
    print("This", "is", "a", "test");
    print(); // ---- no output and no arguments

    return 0;
}
