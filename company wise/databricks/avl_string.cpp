// AVL Tree-based String (Balanced BST approach)
// create a string data structure where insert(idx), update(idx)
// delete(idx) and read(idx) is less than O(n) TC
// Solution: AVL Tree - self-balancing BST
// Each node stores a single character with subtree size for indexing
// All operations: O(log n)

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    char data;
    int height;
    int size;  // Size of subtree (for index calculation)
    AVLNode* left;
    AVLNode* right;
    
    AVLNode(char c) : data(c), height(1), size(1), left(nullptr), right(nullptr) {}
};

class AVLString {
private:
    AVLNode* root;
    
    // Helper: Get height
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    // Helper: Get size
    int size(AVLNode* node) {
        return node ? node->size : 0;
    }
    
    // Helper: Update height and size
    void update(AVLNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
            node->size = 1 + size(node->left) + size(node->right);
        }
    }
    
    // Helper: Get balance factor
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    // Right rotation
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        update(y);
        update(x);
        
        return x;
    }
    
    // Left rotation
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        update(x);
        update(y);
        
        return y;
    }
    
    // Helper: Insert at index
    AVLNode* insertHelper(AVLNode* node, int idx, char c) {
        if (!node) return new AVLNode(c);
        
        int leftSize = size(node->left);
        
        if (idx <= leftSize) {
            node->left = insertHelper(node->left, idx, c);
        } else {
            node->right = insertHelper(node->right, idx - leftSize - 1, c);
        }
        
        update(node);
        
        // Balance the tree
        int balance = getBalance(node);
        
        // Left Left
        if (balance > 1 && idx <= size(node->left->left)) {
            return rotateRight(node);
        }
        
        // Right Right
        if (balance < -1 && idx > size(node->left) + 1 + size(node->right->left)) {
            return rotateLeft(node);
        }
        
        // Left Right
        if (balance > 1 && idx > size(node->left->left)) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left
        if (balance < -1 && idx <= size(node->left) + 1 + size(node->right->left)) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Helper: Get character at index
    char readHelper(AVLNode* node, int idx) {
        if (!node) return '\0';
        
        int leftSize = size(node->left);
        
        if (idx == leftSize) {
            return node->data;
        } else if (idx < leftSize) {
            return readHelper(node->left, idx);
        } else {
            return readHelper(node->right, idx - leftSize - 1);
        }
    }
    
    // Helper: Update character at index
    AVLNode* updateHelper(AVLNode* node, int idx, char c) {
        if (!node) return nullptr;
        
        int leftSize = size(node->left);
        
        if (idx == leftSize) {
            node->data = c;
        } else if (idx < leftSize) {
            node->left = updateHelper(node->left, idx, c);
        } else {
            node->right = updateHelper(node->right, idx - leftSize - 1, c);
        }
        
        return node;
    }
    
    // Helper: Find min node
    AVLNode* minNode(AVLNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    // Helper: Delete at index
    AVLNode* deleteHelper(AVLNode* node, int idx) {
        if (!node) return nullptr;
        
        int leftSize = size(node->left);
        
        if (idx < leftSize) {
            node->left = deleteHelper(node->left, idx);
        } else if (idx > leftSize) {
            node->right = deleteHelper(node->right, idx - leftSize - 1);
        } else {
            // Node to be deleted found
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = minNode(node->right);
                node->data = temp->data;
                node->right = deleteHelper(node->right, 0);
            }
        }
        
        if (!node) return nullptr;
        
        update(node);
        
        // Balance the tree
        int balance = getBalance(node);
        
        // Left Left
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        
        // Left Right
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Right
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        
        // Right Left
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Helper: Build string from tree (in-order traversal)
    void buildString(AVLNode* node, string& result) {
        if (!node) return;
        buildString(node->left, result);
        result += node->data;
        buildString(node->right, result);
    }
    
    // Helper: Destroy tree
    void destroy(AVLNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    
public:
    AVLString(const string& s = "") : root(nullptr) {
        for (int i = 0; i < s.length(); i++) {
            root = insertHelper(root, i, s[i]);
        }
    }
    
    ~AVLString() {
        destroy(root);
    }
    
    // O(log n) - Read character at index
    char read(int idx) {
        return readHelper(root, idx);
    }
    
    // O(log n) - Update character at index
    void update(int idx, char c) {
        root = updateHelper(root, idx, c);
    }
    
    // O(log n) - Insert character at index
    void insert(int idx, char c) {
        root = insertHelper(root, idx, c);
    }
    
    // O(log n) - Delete character at index
    void remove(int idx) {
        root = deleteHelper(root, idx);
    }
    
    // Get full string - O(n)
    string toString() {
        string result;
        buildString(root, result);
        return result;
    }
    
    // Get length - O(1)
    int length() {
        return size(root);
    }
};

int main() {
    cout << "=== AVL Tree-based String ===" << endl;
    AVLString avl("Hello World");
    
    cout << "Initial: " << avl.toString() << endl;
    cout << "Length: " << avl.length() << endl;
    cout << "Read(0): " << avl.read(0) << endl;
    cout << "Read(6): " << avl.read(6) << endl;
    
    avl.update(0, 'h');
    cout << "After update(0, 'h'): " << avl.toString() << endl;
    
    avl.insert(5, '!');
    cout << "After insert(5, '!'): " << avl.toString() << endl;
    cout << "Length: " << avl.length() << endl;
    
    avl.insert(6, '@');
    cout << "After insert(6, '@'): " << avl.toString() << endl;
    
    avl.remove(5);
    cout << "After remove(5): " << avl.toString() << endl;
    cout << "Length: " << avl.length() << endl;
    
    // Test multiple operations
    cout << "\n=== Additional Tests ===" << endl;
    AVLString str("abcde");
    cout << "Initial: " << str.toString() << endl;
    
    str.insert(2, 'X');
    cout << "After insert(2, 'X'): " << str.toString() << endl;
    
    str.remove(3);
    cout << "After remove(3): " << str.toString() << endl;
    
    str.update(1, 'Y');
    cout << "After update(1, 'Y'): " << str.toString() << endl;
    
    cout << "Read(0): " << str.read(0) << endl;
    cout << "Read(2): " << str.read(2) << endl;
    cout << "Final length: " << str.length() << endl;
    
    return 0;
}
