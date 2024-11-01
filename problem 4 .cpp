#include <iostream>
#include <vector>

using namespace std;

// Function to check if two rectangles overlap
bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    int x1 = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];
    int x3 = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];
    return !(y3 >= y2 || y4 <= y1 || x3 >= x2 || x4 <= x1);
}

int main() {
    vector<int> rec1(4), rec2(4);

    // Input for the first rectangle
    cout << "Enter coordinates for the first rectangle  [x1 y1 x2 y2] (each one followed by Enter) : ";
    for (int i = 0; i < 4; ++i) {
        cin >> rec1[i];
    }

    // Input for the second rectangle
    cout << "Enter coordinates for the second rectangle [x3 y3 x4 y4] (each one followed by Enter): ";
    for (int i = 0; i < 4; ++i) {
        cin >> rec2[i];
    }

    // Output "true" or "false" based on overlap check
    cout << (isRectangleOverlap(rec1, rec2) ? "true" : "false") << endl;

    return 0;
}
