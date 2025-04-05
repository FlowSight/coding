// 15 mar 2025
// 10 min..
// from airport..actually i was in a hurry
// missed very basic corner case..
// compiler error : 2
// sev1

class Solution {
    public:
        bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
            vector<int> found = {0,0,0};
            for(auto &it : triplets) {
                if(isCovered(it,target)){
                    if(it[0] == target[0]) found[0] = 1;
                    if(it[1] == target[1]) found[1] = 1;
                    if(it[2] == target[2]) found[2] = 1;
                }
            }
            return found[0] && found[1] && found[2];
        }
    
        bool isCovered(vector<int>& arr, vector<int>& target){
            for(auto i=0;i<3;i++){
                if(arr[i] > target[i]) return false;
            }
            return true;
        }
    };