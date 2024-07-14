class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int,int> l2r, r2l;
        unordered_set<int> ss(nums.begin(),nums.end());
        int ans = 0;
        for(auto it : ss){
            if((l2r.find(it+1) != l2r.end()) && (r2l.find(it-1) != r2l.end())) {
                auto ll = r2l[it-1], rr = l2r[it+1];
                l2r.erase(it+1);
                r2l.erase(it-1);
                l2r[ll] = rr;
                r2l[rr] = ll;
            }
            else if(r2l.find(it-1) != r2l.end()){
                auto ll = r2l[it-1];
                r2l.erase(it-1);
                r2l[it] = ll;
                l2r[ll] = it;
            }
            else if(l2r.find(it+1) != l2r.end()){
                auto rr = l2r[it+1];
                l2r.erase(it+1);
                l2r[it] = rr;
                r2l[rr] = it;
            }
             else {
                l2r[it] = it;
                r2l[it] = it;
            }
        }
        for(auto it : l2r){
            ans = max(ans,it.second-it.first+1);
        }
        return ans;
    }
};
