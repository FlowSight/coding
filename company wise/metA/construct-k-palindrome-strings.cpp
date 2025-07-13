15 june 2025

no of odd cnt chars determine min how many palin can be made..
we can always make >=oddcount palindromes ..but cant make less than oddcount palindromes

bool canConstruct(string s, int k) {
        vector<int> cnt(26,0);
        int n = s.size(), odd = 0;
        if(k>n) return false;
        for(auto c: s)cnt[c-'a']++;
        for(auto i=0;i<26;i++){
            if(cnt[i]%2) odd++;
        }
        return odd <= k;
    }