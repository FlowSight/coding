// 22 apr 2025
// 3.5 min..pass

// 27 dec 2024.5 mins 
// verdict : PASS
    int minAddToMakeValid(string s) {
        int ans = 0, cur = 0;
        for(auto c : s){
            if(c=='(')cur++;
            else cur--;
            if(cur < 0) {
                ans++;
                cur = 0;
            }
        }
        return ans+cur;
    }
