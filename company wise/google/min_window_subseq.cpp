// 13feb2026.
// did get Omn idea..not good enough
// O(n) could not think of sev0
// failed to implement corner cases in single shot..sev0

class Solution {
public:
    string minWindow(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size(), ans = n1+1, ansL = 0,idx1 = 0, idx2 = 0;
        while(idx1<n1){
            if(s1[idx1] == s2[idx2]){
                int end = idx1;
                if(idx2++ == n2-1){
                    while(--idx2>=0){
                        while(s1[idx1] != s2[idx2])idx1--;
                        idx1--;
                    }
                    idx1++;
                    idx2++;
                    if(end-idx1+1 < ans){
                        ans = end-idx1+1;
                        ansL = idx1;
                    }
                }
            }
            idx1++;
        }
        return ans > n1 ? "" : s1.substr(ansL,ans);
    }
};