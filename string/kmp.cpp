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

/////////////////////////
///// threaded KMP search /////
// Worker: KMP search in [L, R) slice; checks 'stop' to early-exit if other thread found a match.
static bool kmpRange(const string& text, const string& pat, const vector<int>& lps,
                     int L, int R, std::atomic<bool>& stop) {
    int n = (int)pat.size();
    if (n == 0) { 
        stop.store(true, std::memory_order_relaxed); 
        return true; 
    }
    int idx = 0;
    for (int i = L; i < R; ++i) {
        if (stop.load(std::memory_order_relaxed)) return false;
        while (idx && text[i] != pat[idx]) idx = lps[idx - 1];
        if (text[i] == pat[idx]) ++idx;
        if (idx == n) { stop.store(true, std::memory_order_relaxed); return true; }
    }
    return false;
}

// Two-thread parallel search with (n-1) overlap to catch boundary-crossing matches.
bool substr_parallel_2threads(const string& s1, const string& s2){
    int m = (int)s1.size(), n = (int)s2.size();
    if (n == 0) return true;
    if (m < n) return false;

    auto lps = getLPS(s2);
    int mid = m / 2;

    int L0 = 0;
    int R0 = std::min(m, mid + std::max(0, n - 1));       // [0, mid + n - 1)
    int L1 = std::max(0, mid - std::max(0, n - 1));       // [mid - (n-1), m)
    int R1 = m;

    std::atomic<bool> found{false};
    bool res0 = false, res1 = false;

    std::thread t0([&]{ res0 = kmpRange(s1, s2, lps, L0, R0, found); });
    std::thread t1([&]{ res1 = kmpRange(s1, s2, lps, L1, R1, found); });

    t0.join(); t1.join();
    return found.load(std::memory_order_relaxed) || res0 || res1;
}