/// Severity: Sev0..sev0..sev0..
// Date: 30May26
// LC: 2463
// Where I failed: algo 3d..
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    typedef vector<long long> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    vvvi dp;
    long long inf = LONG_MAX-1e10;
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(),robot.end());
        sort(factory.begin(),factory.end());
        int m = robot.size(), n = factory.size();
        dp = vvvi(m,vvi(n,vi(101,-1)));
        return helper(0,0,0,robot,factory);
    }

    long long helper(int ridx, int fidx, int served,vector<int>& robot,vector<vector<int>>& factory){
        if(ridx == robot.size()) return 0;
        if(fidx == factory.size()) return inf;
        if(dp[ridx][fidx][served] != -1) return dp[ridx][fidx][served];
        auto ans = helper(ridx,fidx+1,0,robot,factory); // serve current robot in next fact
        ans = min({ans, (factory[fidx][1] > served ? 
                        helper(ridx+1,fidx,served+1,robot,factory)+abs(robot[ridx]-factory[fidx][0])
                        : inf)});
        return dp[ridx][fidx][served] = ans; 
    }
};