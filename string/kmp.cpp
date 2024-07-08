bool substr(string& s1, string& s2){
    int m = s1.size(), n = s2.size();
    auto lps = getLPS(s2);
    for(auto i=0,j=0;i<m;i++){
        while(j && (s1[i] != s2[j]))j = lps[j-1];
        if(s1[i] == s2[j])j++;
        if(j == n)return true;
    }
    return false;
}

vector<int> getLPS(string& s){
    int n = s.size();
    vector<int> lps(n,0);
    for(auto i=1,j=0;i<n;i++){
        while(j && (s[i] != s[j]))j = lps[j-1];
    }
    return lps;
}