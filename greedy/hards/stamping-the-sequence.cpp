/// Severity: Sev0
// Date: 15Aug26
// LC: 936
// Where I failed: algo...
// Pattern: greedy
// Notes: for any window, the number of ticked boxes never decreases. 
// A window that was illegal may become legal. A window that was legal can never become illegal.



class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int stars = 0, n = target.size(), m = stamp.size(), match = 0;
        vector<int> visited(n,0);
        vector<int> ans;
        while(stars < n){
            match = 0;
            for(auto i=0;i<=(n-m);i++){
                if(!visited[i] && cover(target,stamp,i,stars)){
                    match = visited[i] = 1;
                    ans.push_back(i);
                    break;
                }
            }
            if(!match) return vector<int>();
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }

    bool cover(string& str, string& stamp, int idx,int& stars){
        int n = str.size(), m = stamp.size();
        for(auto i=0;i<m;i++){
            if((str[i+idx]!= '*') && (str[i+idx] != stamp[i])) return false;
        }
        for(auto i=0;i<m;i++){
            if(str[i+idx]!= '*') {
                str[i+idx] = '*';
                stars++;
            }
        }
        return true;
    }
};
  

//   ababc
//   ababc?