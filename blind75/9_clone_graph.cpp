/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    unordered_map<int,Node*> mm;
    Node* cloneGraph(Node* node) {
        mm.clear();
        return cloneNode(node);
    }

    Node* cloneNode(Node* node){
        if(!node)return nullptr;
        if(mm.find(node->val) != mm.end()) return mm[node->val];
        Node* newNode = new Node(node->val);
        mm[node->val] = newNode;
        for(auto v : node->neighbors){
            auto clonedNeighbour = cloneNode(v);
            if(clonedNeighbour) {
                newNode->neighbors.push_back(clonedNeighbour);
            }
        }
        return newNode;
    }
};

