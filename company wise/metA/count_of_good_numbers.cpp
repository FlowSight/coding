// 17 apr 2025
// didnt realize combination vs permuation
// didnt realize 0 starting combinations
// didnt realize visited parts..
// sev0

class Solution {
    public:
        long long ans;
        vector<int> perm;
        unordered_set<string> visited;
        long long countGoodIntegers(int n, int k) {
            ans = 0;
            int idx = 0;
            visited.clear();
            perm =  vector<int>(n+1,0);
            perm[0] = 1;
    
            for(auto i=1;i<=n;i++) perm[i] = perm[i-1]*i;
    
            string cur = string(n,'.');
    
            helper(n,k,cur,idx);
    
            return ans;
        }
    
        void helper(int n, int k, string& cur, int idx){
            if(idx > (n-1)/2) {
                auto val = stol(cur);
                if(val % k == 0 ){
                    auto tmp = cur;
                    sort(tmp.begin(),tmp.end());
                    if(visited.find(tmp) == visited.end()) {
                        visited.insert(tmp);
                        ans += calcPerm(cur,n);
                    }
                }
                return;
            }
            for(auto i='1';i<='9';i++){
                cur[idx] = i;
                cur[n-1-idx] = i;
                helper(n,k,cur,idx+1);
            }
            if(idx) {
                cur[idx] = '0';
                cur[n-1-idx] = '0';
                helper(n,k,cur,idx+1);
            }
        }
    
        int calcPerm(string& s, int n){
            unordered_map<char,int> mm;
            for(auto c:s)mm[c]++;
            long ans = perm[n];
            for(auto it : mm){
                ans = ans/perm[it.second];
            }
            long long permWithZero = 0;
            if(mm.find('0') != mm.end()) {
                permWithZero = perm[n-1];
                mm['0']--;
                for(auto it : mm){
                    permWithZero = permWithZero/perm[it.second];
                }
            }
            return ans-permWithZero;
    
        }
    };
    