class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    bool canFinish(int n, vector<vector<int>>& preReq) {
        vvi g(n,vi());
        vi ind(n,0);
        for(const auto& it : preReq){
            g[it[1]].push_back(it[0]);
            ind[it[0]]++;
        }
        queue<int> q;
        for(auto i=0;i<n;i++){
            if(ind[i] == 0)q.push(i);
        }
        int cnt = 0;
        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto tp = q.front();
                cnt++;
                q.pop();
                for(const auto& v : g[tp]){
                    ind[v]--;
                    if(ind[v] == 0){
                        q.push(v);
                    }
                }
            }
        }
        return cnt == n;

    }
};
