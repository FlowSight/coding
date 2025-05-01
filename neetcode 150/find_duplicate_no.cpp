// 11 mar 2025..
// 11 mins..
// didnt comprehend the depth of qs..
// but i remembered the approach..
// didnt dry run...
// sev1

// explanation : linked_list_cycle2.md
// basic idea is make a linked list of the array..then with help of the disgram 
// above it will be clear

// one more solution..changes the array 
class Solution {
    public:
        int findDuplicate(vector<int>& nums) {
            while (nums[0] != nums[nums[0]])
                swap(nums[0], nums[nums[0]]);
            return nums[0];
        }
    };
// one more solution..reuires two passes
class Solution {
    public:
        int findDuplicate(vector<int>& nums) {
            int duplicate = -1;
            for (int i = 0; i < nums.size(); i++) {
                int cur = abs(nums[i]);
                if (nums[cur] < 0) {
                    duplicate = cur;
                    break;
                }
                nums[cur] *= -1;
            }
            
            // Restore numbers
            for (auto& num : nums)
                num = abs(num);
            
            return duplicate;
        }
    };

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
