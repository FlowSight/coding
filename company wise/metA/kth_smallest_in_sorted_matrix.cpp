class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), l = matrix[0][0], r = matrix[n-1][n-1], mid = 0;
        while(l<r){
            if(l+1 == r){
                if(getRank(matrix,l) >=k) return l;
                return r;
            }
            mid = (l+r)/2;
            auto rank = getRank(matrix,mid);
            if(rank >= k) r = mid;
            else l = mid+1;
        }
        return l;
    }

    int getRank(vector<vector<int>>& matrix, int& num) {
        int n = matrix.size(), c = n-1, ans = 0;
        for(auto i=0;i<n;i++) {
            while((c>=0) && (matrix[i][c] > num)) c--;
            ans += (c+1);
        }
        return ans;
    }
};


class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for(auto i=0;i<min(n,k);i++) pq.push({matrix[i][0],i,0});
        for(auto i=1;i<k;i++){
            auto cur = pq.top();
            pq.pop();
            auto r = cur[1], c = cur[2];
            if(c+1<n) pq.push({matrix[r][c+1],r,c+1});
        }
        return pq.top()[0];
    }
};

// // bin search
// log(D^2)n = nlogD
// space :O(1)

// // heap
// time : O(klogk)
// space: O(k)