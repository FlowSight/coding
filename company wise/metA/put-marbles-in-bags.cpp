29 july 2025
lost again (sev0)
10 june 2025
sev2

// i lost here..
// just add gaps..gaps will increase score..
// k-1 gaps..each gap score = arr[i]+arr[i+1]..
// pick min/max k-1 such i


    long long putMarbles(vector<int>& weights, int k) {
        vector<long long> arr;
        long long ans = 0;
        int n = weights.size();
        for(auto i=0;i<n-1;i++) arr.push_back(weights[i]+weights[i+1]);
        sort(arr.begin(),arr.end());
        for(auto i=0;i<k-1;i++){
            ans += arr[n-2-i] - arr[i];
        }
        return ans;
    }




