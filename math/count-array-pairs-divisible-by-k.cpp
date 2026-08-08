/// Severity: Sev0
// Date: 08Aug26
// LC: 2183
// Where I failed: algo
// Pattern: gcd 
// Notes: additional_notes



class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        unordered_map<long,int> mm;
        long long ans = 0;
        for(auto it : nums){
            auto gcd = __gcd(it, k);
            for(auto it1: mm){
                if((it1.first*gcd)%k == 0) ans+=it1.second;
            }
            mm[gcd]++;
        }
        return ans;
    }
};