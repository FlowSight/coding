// LC : 1298

class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size(), ans = 0;
        vector<int> processed(n,-1), opened(n,0), keysseen(n,0);
        queue<int> q;
        for(auto it : initialBoxes){
            processed[it] = status[it];
            if(processed[it] == 1) q.push(it);
        }
        while(!q.empty()){
            auto idx = q.front();
            q.pop();
            ans += candies[idx];
            for(auto k : keys[idx]) keysseen[k] = 1;
            for(auto b : containedBoxes[idx]) {
                if(processed[b] == -1) {
                    processed[b] = status[b];
                    if(processed[b]) q.push(b);
                }
            }
            for(auto i=0;i<n;i++){
                if(processed[i]) continue;
                if(keysseen[i]) {
                    q.push(i);
                    processed[i] = 1;
                }
            }
        }
        return ans;
    }
};
