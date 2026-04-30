// The problem provides a formula: for even numbers, divide by 2; for odd numbers, 
// it becomes 3*n+1. For any positive number, the mathematical conjecture is that 
// it will eventually become 1. Each transformation increments the step count by 1,
//  and an upper limit is given. The task is to find the longest possible number 
//  of steps within that limit. For example, the sequence for transforming 7 to 1 is:
//   7->22->11->34->17->52->26->13->40->20->10->5->16->8->4->2->1,
//   requiring a total of 17 steps.


// int 
// even == n/2
// odd == 3*n+1
// n : 1..n max(f(i)) where i=1...n


#include<bits/stdc++.h>

using namespace std;


unordered_map<int,int> dp;

int helper(int num){
    if(num <= 1) return 1;
    if(dp.find(num) != dp.end()) return dp[num];
    return dp[num] = 1+ (num%2 ? helper(3*num+1) : helper(num/2));
}

int getmaxsteps(int n){
    dp.clear();
    int ans = 0;
    for(auto i=1;i<=n;i++){
        ans = max(ans,helper(i));
    }
    return ans;
}

int main(){
    cout<<getmaxsteps(7)<<endl;
    return 0;
}