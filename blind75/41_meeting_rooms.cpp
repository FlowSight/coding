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
     * @return: if a person could attend all meetings
     */
    bool canAttendMeetings(vector<Interval> &intervals) {
        // Write your code here
        sort(intervals.begin(),intervals.end(), [] (const Interval& i1, const Interval& i2) {
            return i1.start < i2.start;
        });
        int n = intervals.size();
        for(auto i=1;i<n;i++){
            if(intervals[i].start < intervals[i-1].end)return false;
        }
        return true;
    }
};