//  // create a string data structure where insert(idx), update(idx)
// delete(idx) and read(idx) is less than O(n) TC
// Solution: Use a Rope data structure or Balanced BST (Treap/AVL)

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Rope Data Structure using Binary Tree
// Each node represents a substring
// Operations: O(log n) for insert, delete, read, update

class RopeNode {
public:
    string data;
    int weight;  // Number of chars in left subtree + current node
    shared_ptr<RopeNode> left;
    shared_ptr<RopeNode> right;
    
    RopeNode(const string& s) : data(s), weight(s.length()), left(nullptr), right(nullptr) {}
    RopeNode() : weight(0), left(nullptr), right(nullptr) {}
};

class OptimizedString {
private:
    shared_ptr<RopeNode> root;
    
    // Helper: Get character at index
    char getCharHelper(shared_ptr<RopeNode> node, int idx) {
        if (!node) return '\0';
        
        if (idx < node->weight) {
            // Index is in left subtree or current node
            if (!node->left) {
                return node->data[idx];
            }
            return getCharHelper(node->left, idx);
        } else {
            // Index is in right subtree
            return getCharHelper(node->right, idx - node->weight);
        }
    }
    
    // Helper: Concatenate two ropes
    shared_ptr<RopeNode> concatenate(shared_ptr<RopeNode> left, shared_ptr<RopeNode> right) {
        auto newNode = make_shared<RopeNode>();
        newNode->left = left;
        newNode->right = right;
        newNode->weight = getWeight(left);
        return newNode;
    }
    
    // Helper: Get total weight
    int getWeight(shared_ptr<RopeNode> node) {
        if (!node) return 0;
        return node->weight + getWeight(node->right);
    }
    
    // Helper: Split rope at index
    pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> split(shared_ptr<RopeNode> node, int idx) {
        if (!node) return make_pair(nullptr, nullptr);
        
        if (idx <= 0) return make_pair(nullptr, node);
        if (idx >= getWeight(node)) return make_pair(node, nullptr);
        
        if (idx < node->weight) {
            if (!node->left) {
                // Leaf node - split the string
                auto leftNode = make_shared<RopeNode>(node->data.substr(0, idx));
                auto rightNode = make_shared<RopeNode>(node->data.substr(idx));
                return make_pair(leftNode, concatenate(rightNode, node->right));
            }
            
            pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult = split(node->left, idx);
            auto newRight = concatenate(splitResult.second, node->right);
            return make_pair(splitResult.first, newRight);
        } else {
            pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult = split(node->right, idx - node->weight);
            auto newLeft = concatenate(node->left, splitResult.first);
            return make_pair(newLeft, splitResult.second);
        }
    }
    
    // Helper: Build string from rope
    void buildString(shared_ptr<RopeNode> node, string& result) {
        if (!node) return;
        
        if (!node->left && !node->right) {
            result += node->data;
            return;
        }
        
        buildString(node->left, result);
        buildString(node->right, result);
    }
    
public:
    OptimizedString(const string& s = "") {
        if (!s.empty()) {
            root = make_shared<RopeNode>(s);
        }
    }
    
    // O(log n) - Read character at index
    char read(int idx) {
        return getCharHelper(root, idx);
    }
    
    // O(log n) - Update character at index
    void update(int idx, char c) {
        // Split at idx and idx+1, replace middle
        pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult1 = split(root, idx);
        pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult2 = split(splitResult1.second, 1);
        
        auto newMid = make_shared<RopeNode>(string(1, c));
        root = concatenate(splitResult1.first, concatenate(newMid, splitResult2.second));
    }
    
    // O(log n) - Insert character at index
    void insert(int idx, char c) {
        pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult = split(root, idx);
        auto newNode = make_shared<RopeNode>(string(1, c));
        root = concatenate(splitResult.first, concatenate(newNode, splitResult.second));
    }
    
    // O(log n) - Insert string at index
    void insertString(int idx, const string& s) {
        pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult = split(root, idx);
        auto newNode = make_shared<RopeNode>(s);
        root = concatenate(splitResult.first, concatenate(newNode, splitResult.second));
    }
    
    // O(log n) - Delete character at index
    void remove(int idx) {
        pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult1 = split(root, idx);
        pair<shared_ptr<RopeNode>, shared_ptr<RopeNode>> splitResult2 = split(splitResult1.second, 1);
        root = concatenate(splitResult1.first, splitResult2.second);
    }
    
    // Get full string - O(n)
    string toString() {
        string result;
        buildString(root, result);
        return result;
    }
    
    // Get length - O(n) but can be optimized with caching
    int length() {
        return getWeight(root);
    }
};

// Alternative: Simple implementation using vector with chunk management
class SimpleOptimizedString {
private:
    enum { CHUNK_SIZE = 100 };
    vector<string> chunks;
    
    pair<int, int> getPosition(int idx) {
        int chunkIdx = idx / CHUNK_SIZE;
        int posInChunk = idx % CHUNK_SIZE;
        return make_pair(chunkIdx, posInChunk);
    }
    
public:
    SimpleOptimizedString(const string& s = "") {
        for (int i = 0; i < s.length(); i += CHUNK_SIZE) {
            chunks.push_back(s.substr(i, min((int)CHUNK_SIZE, (int)s.length() - i)));
        }
        if (chunks.empty()) chunks.push_back("");
    }
    
    // O(1) amortized - Read
    char read(int idx) {
        pair<int, int> pos = getPosition(idx);
        return chunks[pos.first][pos.second];
    }
    
    // O(1) amortized - Update
    void update(int idx, char c) {
        pair<int, int> pos = getPosition(idx);
        chunks[pos.first][pos.second] = c;
    }
    
    // O(sqrt(n)) - Insert
    void insert(int idx, char c) {
        pair<int, int> pos = getPosition(idx);
        chunks[pos.first].insert(chunks[pos.first].begin() + pos.second, c);
        
        // Rebalance if chunk too large
        if (chunks[pos.first].length() > CHUNK_SIZE * 2) {
            string right = chunks[pos.first].substr(CHUNK_SIZE);
            chunks[pos.first] = chunks[pos.first].substr(0, CHUNK_SIZE);
            chunks.insert(chunks.begin() + pos.first + 1, right);
        }
    }
    
    // O(sqrt(n)) - Delete
    void remove(int idx) {
        pair<int, int> pos = getPosition(idx);
        chunks[pos.first].erase(chunks[pos.first].begin() + pos.second);
        
        // Merge if chunk too small
        if (chunks[pos.first].length() < CHUNK_SIZE / 2 && pos.first + 1 < chunks.size()) {
            chunks[pos.first] += chunks[pos.first + 1];
            chunks.erase(chunks.begin() + pos.first + 1);
        }
    }
    
    string toString() {
        string result;
        for (const auto& chunk : chunks) result += chunk;
        return result;
    }
};

// AVL Tree-based String (Balanced BST approach)
// Each node stores a single character with subtree size for indexing
// All operations: O(log n)

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
    cout << "=== Rope-based OptimizedString ===" << endl;
    OptimizedString rope("Hello World");
    
    cout << "Initial: " << rope.toString() << endl;
    cout << "Read(0): " << rope.read(0) << endl;
    cout << "Read(6): " << rope.read(6) << endl;
    
    rope.update(0, 'h');
    cout << "After update(0, 'h'): " << rope.toString() << endl;
    
    rope.insert(5, '!');
    cout << "After insert(5, '!'): " << rope.toString() << endl;
    
    rope.insertString(6, " Beautiful");
    cout << "After insertString(6, ' Beautiful'): " << rope.toString() << endl;
    
    rope.remove(5);
    cout << "After remove(5): " << rope.toString() << endl;
    
    cout << "\n=== Chunk-based SimpleOptimizedString ===" << endl;
    SimpleOptimizedString simple("Hello World");
    
    cout << "Initial: " << simple.toString() << endl;
    cout << "Read(0): " << simple.read(0) << endl;
    cout << "Read(6): " << simple.read(6) << endl;
    
    simple.update(0, 'h');
    cout << "After update(0, 'h'): " << simple.toString() << endl;
    
    simple.insert(5, '!');
    cout << "After insert(5, '!'): " << simple.toString() << endl;
    
    simple.remove(5);
    cout << "After remove(5): " << simple.toString() << endl;
    
    cout << "\n=== AVL Tree-based String ===" << endl;
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
    
    return 0;
} 
