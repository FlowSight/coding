// 4 feb 2025
// completely  beaten..learned
// could not solve..
// even compiler error while coding seen solution..
// sev0
// verdict : FAILED
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int maxVal = 0, maxCount = 1;
        unordered_map<int,int> mm;
        for(auto it : tasks) {
            mm[it-'A']++;
            if(mm[it-'A'] > maxVal){
                maxVal = mm[it-'A'];
                maxCount = 1;
            } else if(mm[it-'A'] == maxVal){
                maxCount++;
            }
        }
        int noSlots = maxVal-1, slotRem = n-(maxCount-1), totalFitting = slotRem * noSlots, 
            idles = max(0,totalFitting-((int)tasks.size()-maxVal*maxCount));
        return tasks.size() + idles;
    }
};