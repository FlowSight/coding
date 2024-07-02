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