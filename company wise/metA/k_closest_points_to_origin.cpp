// 21 apr 2025
// 9 min..clean

// 9 mar 2025
// pq 3 mins..
// partition : forgot partition code...semantic mistake : 30 mins..
// verdict : FAIL
// sev1

class Solution {
    public:
        vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
            vector<vector<int>> ans;
            int n = points.size(), l = 0, r = n-1, idx = 0;
            while(true){
                idx = partition(points,l,r);
                if(idx == k-1) break;
                if(idx  > k-1){
                    r = idx-1;
                } else {
                    l = idx;
                }
            }
            for(auto i=0;i<=idx;i++){
                ans.push_back(points[i]);
            }
            return ans;
        }
        
        int partition(vector<vector<int>>& arr, int l, int r){
            int idx = l+rand()%(r-l+1);
            swap(arr[l],arr[idx]);
            for(auto i=l+1;i<=r;i++){
                if(dist(arr[i]) > dist(arr[l])) {
                    swap(arr[r--],arr[i--]);
                }
            }
            swap(arr[r],arr[l]);
            return r;
        }
    
        int dist(vector<int>& point){
            auto x= point[0], y = point[1];
            return x*x + y*y;
        }
    };

    

// 15 jan 2025..
// 5 min
// 1 compiling mistake : revised but didnt do semantic check...
// couldnt think of quick sort way...
// verdict : FAIL

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<double,int>> pq;
        vector<vector<int>> ans;
        int n = points.size();
        for(auto i=0;i<n;i++){
            auto dist = points[i][1]*points[i][1] + points[i][0]*points[i][0];
            pq.push({dist,i});
            if(pq.size() > k)pq.pop();
        }
        while(!pq.empty()){
            ans.push_back(points[pq.top().second]);
            pq.pop();
        }
        return ans;
    }
};

