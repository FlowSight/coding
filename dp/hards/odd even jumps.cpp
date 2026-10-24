/// Severity: Sev0
// Date: 21Oct26
// LC: 975
// Where I failed: algo slow implementation, i didnt realize that when coming from 
    // right to left, we can just keep (elem,idx). no need to have map[elem] = {all idxs}
    // im slow in lower/upper bound.
    //  lower/upper bound needs -> instead of .
// Pattern: sparse dp
// Notes: i



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int oddEvenJumps(vector<int>& arr) {
        map<int,int> mm;
        int n = arr.size();
        vvi dp(n,vi(2,0)); // is is possible to move from ith idx to end starting with odd/even jumps
        dp[n-1][0] = dp[n-1][1] = 1;
        mm[arr[n-1]] = n-1;
        int ans = 1;
        for(auto i=n-2;i>=0;i--){
            auto it = mm.lower_bound(arr[i]);
            int oddidx = -1, evenidx = -1;
            // if same elem more
            if((it != mm.end())) {
                oddidx = it->second;
                if(it->first == arr[i]) evenidx = it->second; // if same elem, then evenidx
                else if(it != mm.begin()) evenidx = prev(it)->second; // if more, then just last elem if evenidx
            } else {
                it--;
                evenidx = it->second;
            }

            if(oddidx != -1) {
                dp[i][0] = dp[oddidx][1];
            }
            if(evenidx != -1) {
                dp[i][1] = dp[evenidx][0];
            }
            ans += dp[i][0];
            mm[arr[i]] = i;
        }
        return ans;
    }
};