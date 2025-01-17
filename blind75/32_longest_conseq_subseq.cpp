// 22 dec 2024..missed the set usecase..11 mins
// verdict : FAIL

    int longestConsecutive(vector<int>& nums) {
        unordered_map<int,int> left, right;
        unordered_set<int> seen;
        int ans  = 0;
        for(auto it : nums){
            if(seen.find(it) != seen.end()) continue;
            seen.insert(it);
            if(left.find(it-1) == left.end()) {
                left[it] = it;
            } else {
                left[it] = left[it-1];
                left.erase(it-1);
                right[left[it]] = it;
            }
            if(right.find(it+1) == right.end()) {
                right[it] = it;
            } else {
                right[it] = right[it+1];
                right.erase(it+1);
                left[right[it]] = it;
            }
            if((left[it] != it) && (right[it] != it)){
                auto ll = left[it], rr = right[it];
                right[ll] = rr;
                left[rr] = ll;
                left.erase(it);
                right.erase(it);
            }
        }
        for(auto it : left){
            ans = max(ans,(it.second-it.first+1));
        }
        for(auto it : right){
            ans = max(ans,(it.second-it.first+1));
        }
        return ans;
    }



//1 nov 2024
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int ans = 0;
        unordered_map<int,int> left, right,seen;
        for(auto it : nums) {
            if(seen.find(it) != seen.end())continue;
            seen[it]=it;
            if(left.find(it-1) != left.end() &&
                right.find(it+1) != right.end()) {
                    auto ll = left[it-1], rr = right[it+1];
                    right[ll]=rr;
                    left[rr] = ll;
                    left.erase(it-1);
                    right.erase(it+1);
            } else if (left.find(it-1) != left.end()) {
                left[it] = left[it-1];
                right[left[it-1]] = it;
                left.erase(it-1);
            } else if(right.find(it+1) != right.end()) {
                right[it] = right[it+1];
                left[right[it+1]] = it;
                right.erase(it+1);
            } else {
                left[it]=it;
                right[it]=it;
            }
        }
        for(auto it : left){
            ans = max(ans,it.first-it.second+1);
        }
        return ans;
    }
};

// 100:100,4:4,200:200,1:1,3:3,2:1
// 100:100,4:4,200:200,1:2,3:3

// 1. silly mistakes in algo..long list
// 2. missed corner case..remembered...still didnt fix as i thought it will be covered



// july 2024
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int,int> l2r, r2l;
        unordered_set<int> ss(nums.begin(),nums.end());
        int ans = 0;
        for(auto it : ss){
            if((l2r.find(it+1) != l2r.end()) && (r2l.find(it-1) != r2l.end())) {
                auto ll = r2l[it-1], rr = l2r[it+1];
                l2r.erase(it+1);
                r2l.erase(it-1);
                l2r[ll] = rr;
                r2l[rr] = ll;
            }
            else if(r2l.find(it-1) != r2l.end()){
                auto ll = r2l[it-1];
                r2l.erase(it-1);
                r2l[it] = ll;
                l2r[ll] = it;
            }
            else if(l2r.find(it+1) != l2r.end()){
                auto rr = l2r[it+1];
                l2r.erase(it+1);
                l2r[it] = rr;
                r2l[rr] = it;
            }
             else {
                l2r[it] = it;
                r2l[it] = it;
            }
        }
        for(auto it : l2r){
            ans = max(ans,it.second-it.first+1);
        }
        return ans;
    }
};
