// Task Description
// You have an object defined by a set of fields, each occupying a certain number of bytes.

// For example, (foo, 3), (bar, 6), (baz, 2) means the object's initial state where:

// foo occupies index [0, 3)
// bar occupies [3, 9)
// baz occupies [9, 11)
// Requirements
// Implement two functions:

// getOffset(field): Returns the starting offset of the specified field.

// Example: getOffset("bar") should return 3.
// insert(field, length, index): Inserts a new field at the specified index position (order of fields) and shifts subsequent fields accordingly.

// Example: Given the initial state, calling insert("qux", 2, 1) results in:
// foo (index 0) at [0, 3)
// qux (index 1) at [3, 5)
// bar (index 2) at [5, 11)
// ...and so on.
// Constraints & Edge Cases
// Consider the logic for updating field order and offsets efficiently.
// Handle out-of-bound indices for insertion.
// Handle invalid inputs (e.g., negative lengths).
// Deliverables
// Code implementation.
// Test cases validating offsets before and after insertion.

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

// Skip List implementation for O(log n) position-based insertion
template <typename T>
class SkipList {
private:
    static const int MAX_LEVEL = 16;
    static const float PROBABILITY = 0.5;
    
    struct Node {
        T data;
        vector<Node*> forward;
        int level;
        
        Node(const T& val, int lv) : data(val), level(lv), forward(lv + 1, nullptr) {}
    };
    
    Node* header;
    int current_level;
    int size_;
    
    int randomLevel() {
        int lv = 0;
        while ((rand() % 100) < (PROBABILITY * 100) && lv < MAX_LEVEL) {
            lv++;
        }
        return lv;
    }

public:
    class Iterator {
    public:
        Node* node;
        
        Iterator(Node* n = nullptr) : node(n) {}
        
        Iterator& operator++() {
            if (node) node = node->forward[0];
            return *this;
        }
        
        T& operator*() const {
            return node->data;
        }
        
        bool operator==(const Iterator& other) const {
            return node == other.node;
        }
        
        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }
    };
    
    SkipList() : current_level(0), size_(0) {
        header = new Node(T(), MAX_LEVEL);
    }
    
    ~SkipList() {
        Node* current = header->forward[0];
        while (current) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }
    
    void push_back(const T& val) {
        int new_level = randomLevel();
        if (new_level > current_level) {
            for (int i = current_level + 1; i <= new_level; i++) {
                header->forward[i] = nullptr;
            }
            current_level = new_level;
        }
        
        Node* new_node = new Node(val, new_level);
        vector<Node*> update(MAX_LEVEL + 1, nullptr);
        Node* current = header;
        
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i]) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
        
        size_++;
    }
    
    // Insert at specific index position - O(log n) to find, O(1) to insert
    Iterator insertAt(int index, const T& val) {
        if (index < 0 || index > size_) {
            return Iterator(nullptr);
        }
        
        int new_level = randomLevel();
        if (new_level > current_level) {
            for (int i = current_level + 1; i <= new_level; i++) {
                header->forward[i] = nullptr;
            }
            current_level = new_level;
        }
        
        Node* new_node = new Node(val, new_level);
        vector<Node*> update(MAX_LEVEL + 1, nullptr);
        Node* current = header;
        int count = 0;
        
        // Find position
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && count + (1 << i) <= index) {
                count += (1 << i);
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        // Advance one more step to reach exact position
        if (current->forward[0]) {
            for (int j = 0; j < index - count; j++) {
                current = current->forward[0];
                update[0] = current;
            }
        }
        
        // Insert
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
        
        size_++;
        return Iterator(new_node);
    }
    
    Iterator begin() {
        return Iterator(header->forward[0]);
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }
    
    size_t size() const {
        return size_;
    }
    
    bool empty() const {
        return size_ == 0;
    }
};

class ObjectLayout {
private:
    SkipList<string> field_names;                          // Skip List for O(log n) position access
    unordered_map<string, int> field_sizes;               // name -> size
    unordered_map<string, int> offsets;                   // name -> offset (cached for O(1) lookup)
    unordered_map<string, SkipList<string>::Iterator> name_to_iter;  // Quick access by name
    int total_size;                                        // Cache total size for O(1) queries

    // Recalculate offsets from a given iterator onwards
    void recalculateOffsetsFrom(SkipList<string>::Iterator it) {
        int offset = 0;
        // Calculate offset up to the iterator position
        for (auto iter = field_names.begin(); iter != it; ++iter) {
            offset += field_sizes[*iter];
        }
        // Update offsets from iterator onwards
        for (auto iter = it; iter != field_names.end(); ++iter) {
            offsets[*iter] = offset;
            offset += field_sizes[*iter];
        }
    }

public:
    // Constructor with initial fields
    ObjectLayout(vector<pair<string, int>> initial_fields = {}) : total_size(0) {
        for (const auto& [name, size] : initial_fields) {
            field_names.push_back(name);
            // Store iterator to this element
            auto temp_iter = field_names.begin();
            while (temp_iter != field_names.end()) {
                ++temp_iter;
            }
            --temp_iter;  // Point to last element
            name_to_iter[name] = temp_iter;
            field_sizes[name] = size;
            total_size += size;
        }
        recalculateOffsetsFrom(field_names.begin());
    }

    // Returns the starting offset of the specified field - O(1) average case
    // Returns -1 if field not found
    int getOffset(const string& field_name) const {
        auto it = offsets.find(field_name);
        return (it != offsets.end()) ? it->second : -1;
    }

    // Inserts a new field at the specified index position - O(log n) to find position + O(n) offset recalc
    // index: position in the order of fields (0-based)
    bool insert(const string& field_name, int length, int index) {
        // Handle invalid inputs
        if (length < 0) {
            cerr << "Error: Field length cannot be negative" << endl;
            return false;
        }

        if (index < 0 || index > static_cast<int>(field_names.size())) {
            cerr << "Error: Index out of bounds. Valid range: [0, " << field_names.size() << "]" << endl;
            return false;
        }

        // Check if field already exists - O(1) hash lookup
        if (field_sizes.count(field_name)) {
            cerr << "Error: Field '" << field_name << "' already exists" << endl;
            return false;
        }

        // Insert at the specified index - O(log n) for Skip List
        auto new_iter = field_names.insertAt(index, field_name);
        name_to_iter[field_name] = new_iter;
        field_sizes[field_name] = length;
        total_size += length;

        // Recalculate offsets only from insertion point onwards - O(n) unavoidable
        recalculateOffsetsFrom(new_iter);
        return true;
    }

    // Helper function to print the current layout
    void printLayout() const {
        cout << "Object Layout:" << endl;
        int index = 0;
        for (auto iter = field_names.begin(); iter != field_names.end(); ++iter) {
            const string& name = *iter;
            int size = field_sizes.at(name);
            int offset = offsets.at(name);
            cout << "  [" << index << "] " << name << " (size: " << size 
                 << ") at offset [" << offset << ", " << offset + size << ")" << endl;
            ++index;
        }
        cout << "Total size: " << total_size << " bytes" << endl;
    }

    // Helper to get total size - O(1)
    int getTotalSize() const {
        return total_size;
    }

    // Get number of fields - O(1)
    size_t getFieldCount() const {
        return field_names.size();
    }
};

int main() {
    cout << "=== Field Offset and Insert Problem ===" << endl << endl;

    // Create initial object layout: foo(3), bar(6), baz(2)
    ObjectLayout layout({
        {"foo", 3},
        {"bar", 6},
        {"baz", 2}
    });

    cout << "Initial state:" << endl;
    layout.printLayout();
    cout << endl;

    cout << "Testing getOffset():" << endl;
    cout << "  getOffset(\"foo\") = " << layout.getOffset("foo") << " (expected: 0)" << endl;
    cout << "  getOffset(\"bar\") = " << layout.getOffset("bar") << " (expected: 3)" << endl;
    cout << "  getOffset(\"baz\") = " << layout.getOffset("baz") << " (expected: 9)" << endl;
    cout << "  getOffset(\"nonexistent\") = " << layout.getOffset("nonexistent") << " (expected: -1)" << endl;
    cout << endl;

    cout << "Testing insert():" << endl;
    cout << "Inserting \"qux\" (length 2) at index 1:" << endl;
    layout.insert("qux", 2, 1);
    layout.printLayout();
    cout << endl;

    cout << "Testing getOffset() after insert:" << endl;
    cout << "  getOffset(\"foo\") = " << layout.getOffset("foo") << " (expected: 0)" << endl;
    cout << "  getOffset(\"qux\") = " << layout.getOffset("qux") << " (expected: 3)" << endl;
    cout << "  getOffset(\"bar\") = " << layout.getOffset("bar") << " (expected: 5)" << endl;
    cout << "  getOffset(\"baz\") = " << layout.getOffset("baz") << " (expected: 11)" << endl;
    cout << endl;

    // Test edge cases
    cout << "=== Testing Edge Cases ===" << endl;
    cout << "Attempting to insert at invalid index (100):" << endl;
    layout.insert("invalid", 5, 100);
    cout << endl;

    cout << "Attempting to insert with negative length:" << endl;
    layout.insert("negative", -5, 0);
    cout << endl;

    cout << "Attempting to insert duplicate field name:" << endl;
    layout.insert("foo", 2, 0);
    cout << endl;

    cout << "Inserting \"quux\" (length 4) at index 0 (beginning):" << endl;
    layout.insert("quux", 4, 0);
    layout.printLayout();
    cout << endl;

    cout << "Inserting \"corge\" (length 1) at the end:" << endl;
    layout.insert("corge", 1, layout.getFieldCount()); // Insert at the end
    layout.printLayout();

    return 0;
}