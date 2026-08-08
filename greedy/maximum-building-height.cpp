

/// Severity: Sev0
// Date: 06Aug26
// LC: 1840
// Where I failed: algo..corner case..
// Pattern: two pass, simplified CHT
// Notes: additional_notes


class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& res) {
        res.push_back({1, 0});
        res.push_back({n, n - 1});
        sort(res.begin(),res.end(),[](vector<int>& r1, vector<int>& r2) {
            return r1[0] < r2[0];
        });
        int m = res.size(), lastx = 1, lasthei = 0, ans = 0;
        for(auto& it : res){
            it[1] = min(it[1],lasthei + (it[0]-lastx));
            lasthei = it[1], lastx = it[0];
        }
        for(auto i=m-2;i>=0;i--){
            res[i][1] = min(res[i][1],lasthei + (lastx-res[i][0]));
            lasthei = res[i][1], lastx = res[i][0];
        }
        lasthei = 0, lastx = 1;
        for(auto i=0;i<m;i++){
            ans = max(ans, (lasthei + res[i][1] +  res[i][0] - lastx)/2);
            lasthei = res[i][1], lastx = res[i][0];
        }
        return ans;
    }
};


// 1  2   5  7  10
// 0  5   3. 4  3
// 0  1.  3. 4. 3



// 2 . . . . 2
//   3 4 4 3 

// So the max feasible height at any position is the lower envelope of V-shapes 
// A min of linear functions is concave,
// what is li-chao /CHt?

// peak = (h1+h2+(id2-id1))/2

// 6 x x x x x 2