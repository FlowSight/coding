
// 3 nov..5 min..no mistakes..
class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int countSubstrings(string s) {
        int n = s.size(), ans = n;
        vvi dp(n,vi(n,0));
        for(auto i=0;i<n;i++)dp[i][i] = 1;
        for(auto len = 2;len<=n; len++){
            for(auto i=0;i+len-1<n;i++) {
                auto j = i+len-1;
                dp[i][j] = (len == 2 ? s[i]==s[j] : (s[i]==s[j]) && (dp[i+1][j-1]) );
                ans+=dp[i][j];
            }
        }
        return ans;
    }
};


class Solution {
public:
    int countSubstrings(string s) {
        int cnt = 0, n = s.size();
        for(auto i=0;i<n;i++){
            cnt += checkOdd(s,i) + checkEven(s,i,i+1);
        }
        return cnt;
    }

    int checkOdd(string& s, int idx){
        int ans = 0, n = s.size();
        if(idx >= n || idx<0) return ans;
        ans++;
        for(auto len=1; (idx+len<n) && (idx-len>=0) && (s[idx-len] == s[idx+len]);len++){
            ans++;
        }
        return ans;
    }
    int checkEven(string& s, int idx1, int idx2){
        int ans = 0, n = s.size();
        if(idx1 >= n || idx2>=n || idx1<0 || idx2<0 || (idx1+1!=idx2) || (s[idx1]!=s[idx2])) return ans;
        ans++;
        for(auto len=1; (idx2+len<n) && (idx1-len>=0) && (s[idx1-len] == s[idx2+len]);len++){
            ans++;
        }
        return ans;
    }
};