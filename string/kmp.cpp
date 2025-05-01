// 29 apr 2025..forgot kmp and substr again
// 14dec ...fucked up kmp code...forgot...

bool substr(string& s1, string& s2){
    int m = s1.size(), n = s2.size();
    auto lps = getLPS(s2);
    for(auto i=0,idx=0;i<m;i++){
        while(idx && (s1[i] != s2[idx]))idx = lps[idx-1];
        if(s1[i] == s2[idx])idx++;
        if(idx == n)return true;
    }
    return false;
}

vector<int> getLPS(string& s){
    int n = s.size();
    vector<int> lps(n,0);
    for(auto i=1,idx=0;i<n;i++){
        while(idx && (s[i] != s[idx]))idx = lps[idx-1];
        idx += (s[i] == s[idx]);
        lps[i] = idx;
    }
    return lps;
}