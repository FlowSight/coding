
// 25 may 2025..
//legendary qs..i failed..but again i was half asleep

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& arr) {
        sort(arr.begin(),arr.end(),[](vector<int>& v1, vector<int>& v2){
            return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0];
        });
        vector<int> seqArr;
        seqArr.push_back(arr[0][1]);
        int n = arr.size();
        for(auto i=1;i<n;i++){
            auto lb = findLb(seqArr,arr[i][1]);
            if(lb == seqArr.size()-1) seqArr.push_back(arr[i][1]);
            else seqArr[lb+1] = arr[i][1];
        }
        
        return seqArr.size();
    }

    int findLb(vector<int>& arr, int ele){
        int  n = arr.size(), l = 0, r = n-1, mid = 0;
        while(l<r){
            if(l+1 == r){
                if((arr[r] < ele) && (arr[r] < ele)) return r;
                if((arr[l] < ele) && (arr[l] < ele)) return l;
                return -1;
            }
            mid = (l+r)/2;
            if(arr[mid] < ele) l = mid;
            else r = mid-1;
        }
        return (arr[l] < ele) ? l : -1;
    }
};