#include <iostream>
#include <vector>

std::vector<int> getRow(int rowIndex) {
    std::vector<int> f(rowIndex + 1, 1);
    for (int i = 2; i < rowIndex + 1; ++i) {
        for (int j = i - 1; j > 0; --j) {
            f[j] += f[j - 1];
        }
    }
    return f;
}

int main() {
    int rowIndex;
    std::cout << "Enter the row index: ";
    std::cin >> rowIndex;

    std::vector<int> row = getRow(rowIndex);
    std::cout << "The " << rowIndex << "-th row of Pascal's Triangle is: [";
    for (size_t i = 0; i < row.size(); ++i) {
        std::cout << row[i];
        if (i < row.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}
