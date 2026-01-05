
//28/12/25..got beaten..sev0..

class Solution {
public:
    string smallestBeautifulString(string s, int k) {
        int n = s.size();
        string ans = "";
        for(auto i=n-1;i>=0;i--){
            s[i]++;
            while((s[i] < 'a'+k) && !isValid(s,k,i)) s[i]++;
            if(!isValid(s,k,i)) continue;
            for(auto j=i+1;j<n;j++){
                for(char c = 'a'; c<('a'+k); c++) {
                    s[j] = c;
                    if(isValid(s,k,j)) break;
                }
            }
            return s;
        }
        return ans;
    }

    bool isValid(const string& s, int& k, int& idx){
        if(s[idx] >= ('a'+k)) return false;
        auto last = idx ? s[idx-1] : '*', secLast = idx>=2 ? s[idx-2] : last;
        return (s[idx] != last) && (s[idx] != secLast);
    }
};

//Intuition

// If there is a palindrome with even length,
// there must be a palindrome with length = 2.

// If there is a palindrome with odd length,
// there must be a palindrome with length = 3.

// Reversely,
// If s[i] == s[i + 1], s[i], s[i + 1] is a palindrome.
// If s[i] == s[i + 2], s[i], s[i + 1], s[i + 2] is a palindrome.