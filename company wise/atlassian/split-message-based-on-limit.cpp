//sev0.. 12 nov25
// sev0  5dec25

// The key is below : 
//  for k
//  to_string(k)*2 + 3 < limit
//  to_string(k)*k + 3*k + sum_over(to_string(i)) + message.size() <= limit*k


class Solution {
public:
    vector<string> splitMessage(string message, int limit) {
        int curLen = 0, k = 0, n = message.size(), ans = -1;
        vector<string> res;
        string cur = "";
        for(k=1;k<=n;k++){
            if(to_string(k).size() *2 + 3 >= limit) continue;
            curLen += to_string(k).size();
            if( (to_string(k).size() + 3)*k + curLen + n > limit*k) continue;
            ans = k;
            break;
        }
        if( ans == -1) return res;
        auto ansStr = to_string(ans);
        int ansSize = ansStr.size();
        for(auto i=1,idx = 0;i<=ans;i++){
            cur = "";
            int usedLen = 3 + ansSize + to_string(i).size(),
                remLen = limit - usedLen;
            for(auto j=1;(j<=remLen) && (idx<n);j++,idx++){
                cur.push_back(message[idx]);
            }
            cur.push_back('<');
            cur += to_string(i);
            cur.push_back('/');
            
            for(auto c : ansStr) cur.push_back(c);
            //cur += to_string(ans);
            cur.push_back('>');
            res.push_back(cur);
        }
        return res;
    }
};

