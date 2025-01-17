// 14 jan 2025.. 
// 8 mins.. 
// 1 compiler mistake.. 
// 1 logical mistake..didnt revise code..
// verdict : FAIL
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vector<int> findOrder(int n, vector<vector<int>>& arr) {
        vvi g(n);
        vi ind(n,0), ans;
        deque<int> q;
        for(auto &it : arr) {
            g[it[1]].push_back(it[0]);
            ind[it[0]]++;
        }
        for(auto i=0;i<n;i++){
            if(ind[i] == 0)q.push_back(i);
        }
        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto v = q.front();
                q.pop_front();
                ans.push_back(v);
                for(auto u : g[v]){
                    ind[u]--;
                    if(ind[u] == 0) q.push_front(u);
                }
            }
        }
        return ans.size() == n ?  ans : vector<int>();
    }