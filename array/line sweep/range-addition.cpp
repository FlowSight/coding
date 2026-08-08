/// Severity: Sev3
// Date: 02Aug26
// LC: 370
// Where I failed: clean, no problem
// Pattern: line sweep
// Notes: additional_notes



class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> arr(length,0);
        for(auto it : updates) {
            auto start = it[0], end = it[1]+1, inc = it[2];
            arr[start] += inc;
            if(end < length) arr[end] -= inc;
        }
        for(auto i=1;i<length;i++) arr[i] += arr[i-1];
        return arr;
    }
};