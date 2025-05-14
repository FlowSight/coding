// 12 may 2025
// fucked up bad..corner cases..implementation etc..


class Solution {
    public:
        bool validWordAbbreviation(string word, string abbr) {
            int idx1= 0, idx2 = 0, m = word.size(), n = abbr.size(), val = 0;
            while((idx1 < m) && (idx2 <n)){
                if(isDigit(abbr[idx2])){
                    if(abbr[idx2] == '0') return false;
                    while((idx2<n) && isDigit(abbr[idx2])){
                        val = val*10 + (abbr[idx2++]-'0');
                    }
                    idx1 += val;
                    val = 0;
                } else{
                    if(abbr[idx2] != word[idx1]) return false;
                    idx1++;
                    idx2++;
                }
            }
            return (idx1 == m) && (idx2 == n) ;
        }
    
        bool isDigit(char c){
            return (c>='0') && (c<='9');
        }
    };