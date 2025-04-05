// 11 mar 2025..
// 11 mins..
// didnt comprehend the depth of qs..
// but i remembered the approach..
// didnt dry run...
// sev1

class Solution {
    public:
        int findDuplicate(vector<int>& nums) {
            int slow = nums[0], fast = nums[0];
            while(true){
                slow = nums[slow];
                fast = nums[nums[fast]];
                if(slow == fast)break;
            }
            slow = nums[0];
            while(slow != fast){
                slow = nums[slow];
                fast = nums[fast];
            }
            return slow;
        }
    };
    // duplicate != only 2 times, 

// sev0
// didnt read testcases..hence didnt ask qs
// could not crack

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(), slow = nums[0], fast = slow;
        while(true){
            slow = nums[slow];
            fast = nums[nums[fast]];
            if(slow == fast)break;
        }
        fast = nums[0];
        while(slow != fast){
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

// at least one dupe num : slow meets fast
