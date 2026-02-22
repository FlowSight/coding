/// Severity: Sev0
// Date: 22Feb26
// LC: 2571
// Where I failed: algo
// Pattern: greedy+math.
// Notes: every num is expressable in form : (+-)pow(2,i1) (+-)pow(2,i2) ...  



class Solution {
public:
    int minOperations(int n) {
     vector<int> arr;
     int power = 1, ans= 0;
     while(power<=1e5){
        arr.push_back(power);
        power *= 2;
     } 

     while(n){
        auto it = lower_bound(arr.begin(),arr.end(),n);
        if(it == arr.end()) it--;
        else if(it != arr.begin()) {
            auto prevIt = prev(it);
            if(abs(*(prevIt) - n) <= abs(*(it)-n)) it--;
        }
        n = abs(n-*(it));
        ans++;
     }  
     return ans;
    }
};