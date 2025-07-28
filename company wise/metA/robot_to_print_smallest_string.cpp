// better way is with O(1) space..
//failed sev0

class Solution {
public:
    string robotWithString(string s) {
        int n = s.size();
        vector<char> sufMin(n,'*');
        string t = "", p = "";
        sufMin[n-1] = s[n-1];
        for(auto i=n-2;i>=0;i--){
            sufMin[i] = min(sufMin[i+1],s[i]);
        }
        for(auto i=0;i<n;i++){
            while(t.size() && (t.back() <= sufMin[i])) {
                p.push_back(t.back());
                t.pop_back();
            }
            if(sufMin[i] == s[i]){
                if(!t.size() || (s[i] < t.back())) p.push_back(s[i]);
                else  p.push_back(s[i]);
            } else  t.push_back(s[i]);
        }
        reverse(t.begin(),t.end());
        p += t;
        return p;
    }
};
