
#include<iostream>

using namespace std;


typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

class BuildcostCalc {
    public:
    BuildcostCalc(vvvi& _stages){
        stages = _stages;
        m = stages.size();
        for(auto it : stages) n = max(n,(int)it.size());
    }

    int find_minimum_cost() {
        int ans = 0, minCost = 1e8;
        for(auto &it : stages){
            for(auto it1: it){
                minCost = min(minCost,it1[0]);
            }
            ans += minCost;
            minCost = 1e8;
        }
        return ans;
    }
    int find_minimum_cost_with_dist() {
        int ans = 1e8;
        vvi dp(m,vi(n,1e8));
        for(auto i=m-1;i>=0;i--){
            for(auto j=0;j<n;j++){
                if(i==m-1){
                    dp[i][j] = stages[i][j][0];
                } else {
                    for(auto k=0;k<n;k++){
                        dp[i][j] = min(dp[i][j] , stages[i][j][0] + dp[i+1][k] + abs(stages[i][j][1] - stages[i+1][k][1]));
                    }
                }
                if(i==0) ans = min(ans,dp[i][j]);
            }
        }
        return ans;
    }

    int find_minimum_cost_with_skip() {
        int ans = 1e8;
        dpskip = vvvi(m,vvi(n,vi(2,1e8)));
        for(auto c=0;c<n;c++){
            ans = min(ans, helper(0,c,0));
            ans = min(ans, helper(0,c,1));
        }
        return ans == 1e8 ? -1 : ans;
    }

    private:
    vvvi stages;
    int m, n;
    vvvi dpskip;

    int helper(int r, int c, int skip){
        if(r==m) {
            if(skip == 0 ) return 1e8;
            return 0;
        }
        if(r==m-1){
            if(skip == 0 || (c >= stages[r].size())) return 1e8;
            return dpskip[r][c][skip] = stages[r][c][0];
        }
        if((r<0) || (r>=m+1) || (c<0) || (c>=stages[r].size())) return 1e8;

        if(dpskip[r][c][skip] != 1e8) return dpskip[r][c][skip];
        int ans = 1e8;
        for(auto i=0;i<stages[r+1].size();i++){
            auto tmp = helper(r+1,i,skip);
            if(tmp == 1e8) continue;
            ans = min(ans,stages[r][c][0] +
                abs(stages[r][c][1] - stages[r+1][i][1]) + tmp);
        }
        if(skip == 0){
                for(auto i=0;i<n;i++){
                    auto tmp = helper(r+2,i,1);
                    if(tmp == 1e8) continue;
                    ans = min(ans,stages[r][c][0] +
                       (((r+2<m )&& (c<stages[r+2].size())) ? abs(stages[r][c][1] - stages[r+2][i][1]) : 0) + tmp);
                }
        }
        return dpskip[r][c][skip] = ans; 
    }
};

void testmethod1(){
    vvvi stages = {
        {{10, 0}, {20, 0}, {35, 0}},  
        {{35, 0}, {50, 0}, {25, 0}},
        {{30, 0}, {5, 0}, {40, 0}}
        };
    vvvi stages1 = {
        {{10, 0}, {20, 0}, {35, 0}}
        };
    BuildcostCalc bcc(stages1);
    cout<<bcc.find_minimum_cost()<<endl;

}

void testmethod2(){
    vvvi stages = {
        {{100, 2}, {50,0}, {30, 1}},  
        {{100,1}, {20,2}, {10,5}},
        {{10,1}, {12, 1}, {5, 3}}
        };
    vvvi stages1 = {
        {{10, 0}, {20, 0}, {35, 0}}
        };
    BuildcostCalc bcc(stages1);
    cout<<bcc.find_minimum_cost_with_dist() <<endl;
}

void testmethod3(){
    vvvi stages = {
        {{10, 0}, {20,2}},  
        {{100,5}},
        {{15,1}, {25, 3}},
        {{5,2}, {15, 0}}
        };
    BuildcostCalc bcc(stages);
    cout<<bcc.find_minimum_cost_with_skip() <<endl;
}

int main(){
    testmethod3();
    return 0;
}







// all pos position?
// can 2 at same place?
// can there be uneven no of fact in each stages?

// how many stages?any N 
// vector of vector 
// ret int ?

// approch
// pick min from each stage 
// sum over all stages
// tc : O(S*N)
// sc : O(1)