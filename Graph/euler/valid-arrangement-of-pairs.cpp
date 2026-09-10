/// Severity: Sev0
// Date: 29Aug26
// LC: 2097
// Where I failed: algo..i coudl not realize hamiltonian can be reduced to euler
// Pattern: euler
// Notes: additional_notes



class Solution {
public:
    unordered_map<int, stack<int>> g;
    unordered_map<int,int> in,out;
    typedef vector<int> vi;
    typedef vector<vector<int>> vvi;

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        for(auto it : pairs){
            auto u = it[0], v =it[1];
            g[u].push(v);
            in[v]++;
            out[u]++;
        }
        int start = -1;
        // if its indegree < outdegree , then its start, if it > then out, else pick any
        for(auto it:out){
            auto outd = it.second;
            if((in.find(it.first) == in.end()) || (outd > in[it.first])) {
                start = it.first;
                break;
            }
        }
        if(start == -1) start = pairs[0][0];
        vvi ans;
        vi res;
        euler(start,res);
        reverse(res.begin(),res.end());
        for(auto i=1;i<res.size();i++)ans.push_back({res[i-1],res[i]});
        return ans;
    }
    void euler(int start, vi& res){
        auto& st = g[start];
        while(!st.empty()){
            auto tp = st.top();
            st.pop();
            euler(tp,res);
        }
        res.push_back(start);
    }
};
