/// Severity: Sev1
// Date: 30Jun26
// LC: 1707
// Where I failed: trie implementation.timing
// Pattern: pattern_name
// Notes: additional_notes



typedef vector<int> vi;
typedef vector<vi> vvi;

class Trie {
    public:
    vector<Trie*> children;
    int val;
    Trie(int _v){
        val = _v;
        children = vector<Trie*>(2,nullptr);
    }
    void add(int& num, int idx = 31){
        if(idx <0) return;
        bool bit = num & (1<<idx);
        //<num<<" "<<idx<<" "<<bit<<endl;
        if(!children[bit]) children[bit] = new Trie(bit);
        children[bit]->add(num,idx-1);
    }

    void findmax(int& num, int idx, int& cur){
        if(idx<0) return;
        bool bit = (num & (1<<idx));
        //cout<<num<<"**"<<idx<<"**"<<bit<<endl;
        if(children[!bit]) {
            cur |= (1<<idx);
            children[!bit]->findmax(num,idx-1,cur);
        } else {
            if(children[bit]){
                children[bit]->findmax(num,idx-1,cur);
            }
        }
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        Trie* root = new Trie(100);
        int n = queries.size(), m = nums.size();

        for(auto i=0;i<n;i++) {
            queries[i].push_back(i);
        }
        sort(queries.begin(),queries.end(),[](vi& v1, vi& v2){
            return v1[1] < v2[1];
        });
        sort(nums.begin(),nums.end());

        vi ans(n,0);

       for(auto i=0,l = 0;i<n;i++) {
            auto tmp = queries[i];
            auto x = tmp[0], mi = tmp[1], idx = tmp[2];
            while((l<m) && (nums[l] <= mi)) {
                root->add(nums[l++]);
            }
            int curans = 0;
            root->findmax(x,31,curans);
            ans[idx] = l ?  curans : -1;
        }
        return ans;
    }
};


