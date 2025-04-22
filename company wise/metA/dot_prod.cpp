// 21 apr 2025
// 7 mins..clean
// backchodi is expected here on why hashmap is not scalable..so take array
// instead..and use 2 pointers

class SparseVector {
    public:
        unordered_map<int,int> mm;
        int n;
        SparseVector(vector<int> &nums) {
            int n = nums.size();
            for(auto i=0;i<n;i++){
                if(nums[i]) {
                    mm[i] = nums[i];
                }
            }
        }
        
        // Return the dotProduct of two sparse vectors
        int dotProduct(SparseVector& vec) {
            int ans = 0;
            auto secondMap = vec.mm;
            for(auto it : mm){
                // if non zero idx of first vec is absent in 2nd vec, move on
                if(secondMap.find(it.first) == secondMap.end()) continue;
                ans += it.second * secondMap[it.first];
            }
            return ans;
        }
    };