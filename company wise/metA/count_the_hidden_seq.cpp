// 23 apr 2025
// failed..2 corner cases.
// but there is another genious approach
// sev0

// the genious way
class Solution {
    public:
        int numberOfArrays(vector<int>& diff, int lower, int upper) {
            long sum = 0, maxi = 0, mini = 0;
            for (int i : diff) {
                sum += i;
                maxi = max(maxi, sum);
                mini = min(mini, sum);
            }
            return max(0L, upper - lower - maxi + mini + 1);
        }
    };



    // my way
class Solution {
    public:
        int numberOfArrays(vector<int>& differences, int lower, int upper) {
            long n = differences.size(), minSum = 0, minIdx = -1, cur = 0, maxVal = lower;
            for(auto i=0;i<n;i++){
                cur += differences[i];
                if(cur<minSum) {
                    minSum = cur;
                    minIdx = i;
                }
            }
            cur = lower;
            for(auto i=minIdx+1;i<n;i++){
                cur += differences[i];
                maxVal = max(maxVal,cur);
            }
            cur = lower;
            for(auto i=minIdx;i>=0;i--){
                cur -= differences[i];
                maxVal = max(maxVal,cur);
            }
            return max((long)0,upper-maxVal+1);
    
        }
    };