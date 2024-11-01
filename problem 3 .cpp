#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Function to create the spiral matrix
vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    vector<vector<int>> ans(m, vector<int>(n, -1)); // Initialize matrix with -1
    int i = 0, j = 0, k = 0;
    const int dirs[5] = {0, 1, 0, -1, 0}; // Directions for spiral movement
    while (head) {
        ans[i][j] = head->val;
        head = head->next;
        while (true) {
            int x = i + dirs[k];
            int y = j + dirs[k + 1];
            if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1) {
                i = x;
                j = y;
                break;
            }
            k = (k + 1) % 4;
        }
    }
    return ans;
}

// Helper function to create a linked list from a vector of values
ListNode* createLinkedList(const vector<int>& values) {
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Main function
int main() {
    int m, n;
    
    // Input matrix dimensions
    cout << "Enter the number of rows for the matrix (m): ";
    cin >> m;
    cout << "Enter the number of columns for the matrix (n): ";
    cin >> n;

    // Input linked list size and elements
    int listSize;
    cout << "Enter the number of elements in the linked list: ";
    cin >> listSize;

    vector<int> values(listSize);
    cout << "Please enter the elements of the linked list in order:" << endl;
    for (int i = 0; i < listSize; i++) {
        cout << "Element " << i + 1 << ": ";
        cin >> values[i];
    }

    // Create the linked list from input values
    ListNode* head = createLinkedList(values);

    // Generate the spiral matrix
    vector<vector<int>> result = spiralMatrix(m, n, head);

    // Output the matrix
    cout << "\nGenerated " << m << " x " << n << " Matrix in Spiral Order:" << endl;
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << "\t"; // Print each element with a tab space
        }
        cout << endl;
    }

    return 0;
}
