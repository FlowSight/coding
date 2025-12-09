#include <iostream>
#include <memory>

enum Color { RED, BLACK };

template<typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        Color color;
        std::shared_ptr<Node> left, right, parent;
        
        Node(const T& value, Color c = RED) : data(value), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    using NodePtr = std::shared_ptr<Node>;
    NodePtr root;
    NodePtr nil; // Sentinel node
    
    // Initialize NIL node (black sentinel)
    void initializeNil() {
        nil = std::make_shared<Node>(T{}, BLACK);
        nil->left = nil->right = nil->parent = nil;
    }
    
    // Left rotation
    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        
        if (y->left != nil) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    // Right rotation
    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        
        if (y->right != nil) {
            y->right->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        
        y->right = x;
        x->parent = y;
    }
    
    // Fix violations after insertion
    void insertFixup(NodePtr z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                NodePtr y = z->parent->parent->right; // Uncle
                
                if (y->color == RED) {
                    // Case 1: Uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: z is right child
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: z is left child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                // Mirror cases for right subtree
                NodePtr y = z->parent->parent->left; // Uncle
                
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    // Transplant subtrees
    void transplant(NodePtr u, NodePtr v) {
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    
    // Find minimum in subtree
    NodePtr minimum(NodePtr node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }
    
    // Fix violations after deletion
    void deleteFixup(NodePtr x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                NodePtr w = x->parent->right;
                
                if (w->color == RED) {
                    // Case 1: sibling is red
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    // Case 2: both children of sibling are black
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        // Case 3: right child of sibling is black
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // Case 4: right child of sibling is red
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                // Mirror cases for right subtree
                NodePtr w = x->parent->left;
                
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    
    // Search helper
    NodePtr searchHelper(NodePtr node, const T& key) const {
        if (node == nil || key == node->data) {
            return node;
        }
        
        if (key < node->data) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }
    
    // Inorder traversal helper
    void inorderHelper(NodePtr node) const {
        if (node != nil) {
            inorderHelper(node->left);
            std::cout << node->data << " ";
            inorderHelper(node->right);
        }
    }

public:
    RedBlackTree() {
        initializeNil();
        root = nil;
    }
    
    // Insert operation
    void insert(const T& key) {
        NodePtr z = std::make_shared<Node>(key);
        NodePtr y = nil;
        NodePtr x = root;
        
        // Find position to insert
        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        z->parent = y;
        if (y == nil) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
        
        z->left = nil;
        z->right = nil;
        z->color = RED;
        
        insertFixup(z);
    }
    
    // Delete operation
    void remove(const T& key) {
        NodePtr z = searchHelper(root, key);
        if (z == nil) return; // Key not found
        
        NodePtr y = z;
        NodePtr x;
        Color originalColor = y->color;
        
        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            originalColor = y->color;
            x = y->right;
            
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        
        if (originalColor == BLACK) {
            deleteFixup(x);
        }
    }
    
    // Search operation
    bool search(const T& key) const {
        return searchHelper(root, key) != nil;
    }
    
    // Print inorder traversal
    void inorder() const {
        inorderHelper(root);
        std::cout << std::endl;
    }
    
    // Check if tree is empty
    bool empty() const {
        return root == nil;
    }
};

// Test the Red-Black Tree
int main() {
    RedBlackTree<int> rbt;
    
    // Insert elements
    std::cout << "Inserting: 10, 20, 30, 15, 25, 5, 1\n";
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(5);
    rbt.insert(1);
    
    std::cout << "Inorder traversal: ";
    rbt.inorder();
    
    // Search operations
    std::cout << "Search 15: " << (rbt.search(15) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 100: " << (rbt.search(100) ? "Found" : "Not Found") << std::endl;
    
    // Delete operations
    std::cout << "Deleting 20\n";
    rbt.remove(20);
    std::cout << "After deletion: ";
    rbt.inorder();
    
    std::cout << "Deleting 30\n";
    rbt.remove(30);
    std::cout << "After deletion: ";
    rbt.inorder();
    
    return 0;
}