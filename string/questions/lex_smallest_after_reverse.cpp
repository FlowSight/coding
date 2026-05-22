/*
 * LC#/CF: Lexicographically Smallest String After One Reversal
 * Difficulty: hard
 * Pattern: Hashing / String
 *
 * Given string s of length n (n up to 1e5), perform exactly one operation:
 * - Choose k (1 <= k <= n)
 * - Either reverse first k chars OR reverse last k chars
 * Return the lexicographically smallest result.
 *
 * Approach:
 *   Each candidate is a concatenation of two substrings of s or rev(s).
 *   - Type 1 (reverse first k): rev(s[0..k-1]) + s[k..n-1]
 *   - Type 2 (reverse last k, split at j=n-k): s[0..j-1] + rev(s[j..n-1])
 *
 *   Use double polynomial hashing to compare any two candidates in O(log n)
 *   via binary search on the first differing position.
 *   Iterate all 2n candidates, maintain minimum.
 *
 * Time: O(n log n), Space: O(n)
 * 
 * to know : 
 *  hash of 2 strings might be < or >. that has nothing to do with lexicography
 *  
 * steps of the qs : 
 *  1. get hash struct of orig string and reverse string + ability to give hash of substr in O(1)
 *  2. create candiate strings without materializing
 *  3. compare each candidate in O(logn) with best so far
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
const long long BASE1 = 131, BASE2 = 137;
const int MAXN = 100005;

long long pw1[MAXN], pw2[MAXN];

struct StrHash {
    vector<long long> h1, h2;
    void build(const string& t) {
        int m = t.size();
        h1.assign(m + 1, 0);
        h2.assign(m + 1, 0);
        for (int i = 0; i < m; i++) {
            h1[i+1] = (h1[i] * BASE1 + t[i]) % MOD1;
            h2[i+1] = (h2[i] * BASE2 + t[i]) % MOD2;
        }
    }
    // 0 1 2 3 4 5 6 7 // index
    // 7 6 5 4 3 2 1 0 //bs power
    // t0*b^7 + t1*b^6 + t2*b^5 + .... + t7*b^0
    // t5*b^2+ t6*b^1 + t7*b^0
    // hash(0...r) = hash(0..l)*(b^len) + hash(l+1..r)

    pair<long long, long long> query(int l, int r) const {
        int len = r - l + 1;
        long long v1 = (h1[r+1] - h1[l] * pw1[len] % MOD1 + MOD1 * 2) % MOD1;
        long long v2 = (h2[r+1] - h2[l] * pw2[len] % MOD2 + MOD2 * 2) % MOD2;
        return {v1, v2};
    }
};

// Moved into lexSmallest as locals

struct Cand {
    int w1, a1, b1;
    int w2, a2, b2;
    int split;
};

string lexSmallest(string s) {
    int n = s.size();
    if (n == 1) return s;

    static bool pw_init = false;
    if (!pw_init) {
        pw1[0] = pw2[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            pw1[i] = pw1[i-1] * BASE1 % MOD1;
            pw2[i] = pw2[i-1] * BASE2 % MOD2;
        }
        pw_init = true;
    }

    string rev_s(s.rbegin(), s.rend());
    StrHash hs, hr;
    hs.build(s);
    hr.build(rev_s);

    auto seg_hash = [&](int w, int l, int r) -> pair<long long,long long> {
        return w == 0 ? hs.query(l, r) : hr.query(l, r);
    };

    auto cand_hash = [&](const Cand& c, int l, int rr) -> pair<long long,long long> {
        if (rr < c.split) {
            return seg_hash(c.w1, c.a1 + l, c.a1 + rr);
        } else if (l >= c.split) {
            return seg_hash(c.w2, c.a2 + (l - c.split), c.a2 + (rr - c.split));
        } else {
            auto [x1, x2] = seg_hash(c.w1, c.a1 + l, c.b1);
            auto [y1, y2] = seg_hash(c.w2, c.a2, c.a2 + (rr - c.split));
            int len2 = rr - c.split + 1;
            long long v1 = (x1 * pw1[len2] + y1) % MOD1;
            long long v2 = (x2 * pw2[len2] + y2) % MOD2;
            return {v1, v2};
        }
    };

    auto cand_at = [&](const Cand& c, int i) -> char {
        if (i < c.split) return (c.w1 == 0 ? s : rev_s)[c.a1 + i];
        return (c.w2 == 0 ? s : rev_s)[c.a2 + (i - c.split)];
    };

    auto cand_less = [&](const Cand& a, const Cand& b) -> bool {
        int lo = 0, hi = n - 1, pos = n;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (cand_hash(a, 0, mid) == cand_hash(b, 0, mid))
                lo = mid + 1;
            else {
                pos = mid;
                hi = mid - 1;
            }
        }
        if (pos == n) return false;
        return cand_at(a, pos) < cand_at(b, pos);
    };

    // Initial best = identity (type1, k=1) = s itself
    Cand best = {1, n-1, n-1, 0, 1, n-1, 1};

    // Type 1: reverse first k -> r[n-k..n-1] + s[k..n-1]
    for (int k = 2; k <= n; k++) {
        Cand c;
        c.w1 = 1; c.a1 = n - k; c.b1 = n - 1; c.split = k;
        c.w2 = 0; c.a2 = k; c.b2 = n - 1;

        char fc = cand_at(c, 0), fb = cand_at(best, 0);
        if (fc > fb) continue;
        if (fc < fb || cand_less(c, best)) best = c;
    }

    // Type 2: reverse last k (split at j=n-k) -> s[0..j-1] + r[0..n-1-j]
    for (int j = 1; j < n; j++) {
        Cand c;
        c.w1 = 0; c.a1 = 0; c.b1 = j - 1; c.split = j;
        c.w2 = 1; c.a2 = 0; c.b2 = n - 1 - j;

        char fc = cand_at(c, 0), fb = cand_at(best, 0);
        if (fc > fb) continue;
        if (fc < fb || cand_less(c, best)) best = c;
    }

    string res(n, ' ');
    for (int i = 0; i < n; i++) res[i] = cand_at(best, i);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n; string s;
        cin >> n >> s;
        cout << lexSmallest(s) << "\n";
    }

    return 0;
}

// sumita astro
// dhanu lagna tula rashi

// rabi shukra brishpati : kalsarpa 
// 12 rokom kalsarpa : 10th e ache , working place , ghatak kalsarpa jog
// na gharka na ghatka
// ghoshe ghoshe kaj korche ..not working 

// 4: shani ketu
// 2: brihospoti, shukro , robi
// shani mahadasha now
// veg on the day of dharon
