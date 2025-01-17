//6 nov 2024
//another way
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        for(auto i=0;i<n;i++){
            while(nums[i]<n && nums[i]>=0 && nums[i] != i){
                swap(nums[i],nums[nums[i]]);
            }
        }
        for(auto i=0;i<n;i++){
            if(nums[i] != i)return i;
        }
        return n;
    }

// went on a diff track..dry ran..then fixed it..no errors..8 mins

int missingNumber(vector<int>& nums) {
    int n = nums.size(),sum = 0;
    for(auto it : nums)sum+=it;
    return n*(n+1)/2-sum;
}


class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0, n = nums.size(), expected = n*(n+1)/2;
        for(auto it : nums)sum+=it;
        return expected - sum;
    }
};


 int missingNumber(vector<int>& nums) {

    int xor = 0, i = 0;
	for (i = 0; i < nums.size(); i++) {
		xor = xor ^ i ^ nums[i];
	}

	return xor ^ i;
}