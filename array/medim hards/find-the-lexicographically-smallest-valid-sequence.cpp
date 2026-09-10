/// Severity: Sev2
// Date: 02Sep26
// LC: 3302
// Where I failed: corner case wrong index
// Pattern: array + dp
// Notes: additional_notes



class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> match(n,0);
        for(auto i=n-1,idx = m-1,cur = 0;i>=0;i--) {
            match[i] = cur;
            if((idx>=0) && (word2[idx] == word1[i])) {
                match[i]++;
                cur++;
                idx--;
            }
        }
        vector<int> ans;
        for(auto i=0,j=0,skipped = 0;(i<n) && (j<m);i++){
            if(word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } else {
                int rem = m-j-1;
                if(((rem == 0) || ((i<n-1) && (match[i+1] >= rem))) && !skipped) {
                    ans.push_back(i);
                    j++;
                    skipped = 1;
                }
            }
        }
        return ans.size() == m ? ans : vector<int>();
    }
};