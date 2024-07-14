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

// 165,221 65,424. 351,507.   387,722.  259,722.  19,797.  314,807.   136,897
// 19,797. 65,424. 136,897    165,221.  259,722.  314,807  351,507.   387,722. 

