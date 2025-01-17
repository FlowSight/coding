class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = 1;
        unordered_map<double,int> mm;
        for(auto i=0,samepoint = 0;i<n;i++,samepoint = 0){
            mm.clear();
            for(auto j=i+1;j<n;j++) {
                double  del_y = points[i][1]-points[j][1],del_x = points[i][0]-points[j][0];
                double slope = 0;
                string key = "";
                if(del_x == 0){
                    slope = INT_MAX;
                } else {
                   slope = (double)del_y/(double)del_x;
                }
                mm[slope]++;
            }
            for(auto it : mm) {
                ans = max(ans,it.second+1);
            }
        }
        return ans;
    }
};


25oct2024
// slope for two points...vs 3 points..
//     I used to think that if, p1 and p2 slope is same, and p3 and p4 slope is same. p1 and p3 WILL have same slope...thats true ONLY if the c in 'y=mx+c' is same...so cant take this situation for granted 
// didnt check for the final ans val..it had to be +1
// in "double" way : didnt make "everything" double