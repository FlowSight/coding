/// Severity: Sev2..sev2..sev0
// Date: 22May26
// LC: 815
// Where I failed: clean implementation  + less space optimization
// Pattern: bfs on meta-graph
// Notes: additional_notes



class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        int n = routes.size();
        unordered_map<int,vector<int>> businroute;
        for(auto i=0;i<n;i++){
            for(auto it : routes[i]){
                businroute[it].push_back(i);
            }
        }
        queue<vector<int>> q;
        q.push({source,0});
        unordered_set<int> visited;
        visited.insert(source);
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto tp = q.front();
                q.pop();
                auto idx = tp[0], cnt = tp[1];
                if(idx == target) return cnt;
                for(auto v : businroute[idx]){ // all buses that we can take from this station
                    while(!routes[v].empty()){
                        auto u = routes[v].back();
                        routes[v].pop_back();
                        if(visited.find(u) == visited.end()){
                            visited.insert(u);
                            q.push({u,cnt+1});
                        }
                    }
                }
            }
        }
        return -1;
    }
};




w = vd 
v = 500
d = w/v = 
dW  = w1/v 
dI  = w2/v 
w1 > w2 
dW > dI 