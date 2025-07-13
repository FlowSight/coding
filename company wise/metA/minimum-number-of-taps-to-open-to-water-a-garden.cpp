12 june 2025
i did a suboptimal sol..
there is O(n) time sol...todo ...sev0



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int minTaps(int n, vector<int>& ranges) {
        vvi arr;
        for(auto i=0;i<=n;i++){
            if(ranges[i] == 0) arr.push_back({-1,-1,i});
            else arr.push_back({i-ranges[i],i+ranges[i],i});
        }
        sort(arr.begin(),arr.end());
        priority_queue<int> pq;
        int right = 0, idx = 0, ans = 0;
        for(auto i=0;i<=n;i++){
            while((idx<=n) && (arr[idx][0] < i)) {
                pq.push(arr[idx++][1]);
            }
            if(i<=right) continue;
            if(pq.empty() || (pq.top() < i)) return -1;
            right = pq.top();
            pq.pop();
            ans++;
        }
        return ans;
    }
    
};


// one othet way 
    int minTaps(int n, vector<int>& A) {
        vector<int> dp(n + 1, n + 2);
        dp[0] = 0;
        for (int i = 0; i <= n; ++i){
            int left = max(i-A[i]+1,0), right = min(i+A[i],n);
            for (int j = left; j <= right; ++j){
                 dp[j] = min(dp[j], dp[max(0,left-1)] + 1); //basically dp[i] = no of min taps to water 0..i
            }
        }
        return dp[n]  < n + 2 ? dp[n] : -1;
    }