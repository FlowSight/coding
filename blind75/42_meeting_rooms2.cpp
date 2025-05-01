
// 29 march 2025
// failed..forgot and oversimplified the problem
// sev0
// there is another method with sorting + O(n) space..try that

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param intervals: an array of meeting time intervals
     * @return: the minimum number of conference rooms required
     */
    int minMeetingRooms(vector<Interval> &intervals) {
        // Write your code here
        map<int,int> mm;
        for(auto it : intervals){
            mm[it.start]++;
            mm[it.end]--;
        }
        int ans = 0,cur = 0;
        for(auto it : mm){
            cur+=it.second;
            ans = max(ans,cur);
        }
        return ans;
    }
};

