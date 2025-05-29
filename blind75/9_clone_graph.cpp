//bfs : has issue..sev0
// dfs no issue..


// 18 mar 2025
// 11 min 
// no issue

// 2 nov 2024..22 min..one corner case missed...



class Solution {
public:
    unordered_map<Node*,Node*> mm;
    Node* cloneGraph(Node* node) {
        if(!node) return node;
        queue<Node*> q;
        q.push(node);
        mm[node] = new Node(node->val);
        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto cur = q.front();
                q.pop();
                for(auto it : cur->neighbors){
                    if(mm.find(it) == mm.end()){
                        mm[it] = new Node(it->val);
                        q.push(it);
                    }
                    mm[cur]->neighbors.push_back(mm[it]);
                }
            }
        }
        return mm[node];
    }
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

