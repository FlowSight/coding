


// 2 nov 2024..22 min..one corner case missed...

class Solution {
public:
    
    Node* cloneGraph(Node* node) {
        if(!node) return node;
        queue<pair<Node*,Node*>> q;
        unordered_map<int,Node*> mm;
        unordered_set<int> visited;
        auto curCloned = new Node(node->val); 
        q.push({node,curCloned});
        mm[node->val] = curCloned;

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto tp = q.front();
                q.pop();
                if(visited.find(tp.first->val) != visited.end())continue;
                visited.insert(tp.first->val);

                for(auto it : tp.first->neighbors){
                    if(mm.find(it->val) != mm.end()) {
                        curCloned = mm[it->val];
                    } else {
                        curCloned = new Node(it->val);
                        mm[it->val] = curCloned;
                    }
                    tp.second->neighbors.push_back(curCloned);
                    if(visited.find(it->val) != visited.end()) continue;
                    q.push({it,curCloned});
                }
            }
        }
        return mm[node->val];
    }
};

// before july 2024
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

