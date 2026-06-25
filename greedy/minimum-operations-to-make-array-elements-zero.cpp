/// Severity: Sev0..Sev0..Sev0..Sev0..Sev0..Sev0..Sev0..Sev0    
// Date: 02Jun26
// LC: 3495
// Where I failed: algo..i didnt get that for a list of elements where total ops needed
// is p, and if i can choose 2 at a time to do that op, it will take (p+1)/2 ops.
// Pattern: pattern_name
// Notes: additional_notes

class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long ans = 0;
        for(auto it : queries){
            auto tot = 0LL;
            for(auto i=1LL,prev = i,div = 1LL;i<INT_MAX;div++){
                i<<=2;
                long long l = it[0], r = it[1];
                l = max(l,prev);
                r = min(i-1,r);
                if(l<=r) tot += (r-l+1)*div;
                prev = i;
            }
            ans += (tot+1)/2;
        }
        return ans;
    }
};
