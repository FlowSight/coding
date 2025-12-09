// Rope Data Structure Implementation
// create a string data structure where insert(idx), update(idx)
// delete(idx) and read(idx) is less than O(n) TC
// Solution: Rope data structure using Binary Tree
// Operations: O(log n) for insert, delete, read, update

#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class RopeNode {
public:
    string data;
    int weight;  // Number of chars in left subtree + current node
    shared_ptr<RopeNode> left;
    shared_ptr<RopeNode> right;
    
    RopeNode(const string& s) : data(s), weight(s.length()), left(nullptr), right(nullptr) {}
    RopeNode() : weight(0), left(nullptr), right(nullptr) {}
};

class RopeString {
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
    RopeString(const string& s = "") {
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
class ChunkedString {
private:
    enum { CHUNK_SIZE = 100 };
    vector<string> chunks;
    
    pair<int, int> getPosition(int idx) {
        int chunkIdx = idx / CHUNK_SIZE;
        int posInChunk = idx % CHUNK_SIZE;
        return make_pair(chunkIdx, posInChunk);
    }
    
public:
    ChunkedString(const string& s = "") {
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

int main() {
    cout << "=== Rope-based String ===" << endl;
    RopeString rope("Hello World");
    
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
    
    cout << "\n=== Chunk-based String ===" << endl;
    ChunkedString chunked("Hello World");
    
    cout << "Initial: " << chunked.toString() << endl;
    cout << "Read(0): " << chunked.read(0) << endl;
    cout << "Read(6): " << chunked.read(6) << endl;
    
    chunked.update(0, 'h');
    cout << "After update(0, 'h'): " << chunked.toString() << endl;
    
    chunked.insert(5, '!');
    cout << "After insert(5, '!'): " << chunked.toString() << endl;
    
    chunked.remove(5);
    cout << "After remove(5): " << chunked.toString() << endl;
    
    return 0;
}
