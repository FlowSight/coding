    long base1 = 131, base2 = 137;
    int mod1 = 1e9+7, mod2 = 1e9+11, n;
    vector<long> phash, phashrev, power1, power2;
    string str, revstr;
    // does : calculate 2 types of hash + gets hash of any substr
    struct StrHash {
        public:
        int n;
        vector<long> hash1, hash2;
        StrHash() = default;
        StrHash(string s){
            n = s.size();
            hash1 = vector<long> (n+1,0);
            hash2 = vector<long> (n+1,0);
            for(auto i=0;i<n;i++){
                hash1[i+1] = (hash1[i]*base1 + s[i]-'a')%mod1;
                hash2[i+1] = (hash2[i]*base2 + s[i]-'a')%mod2;
            }
        }
        pair<long,long> gethash(int l, int r){
            int len = r-l+1;
            auto h1 = (hash1[r+1] - (hash1[l]*power1[len])%mod1 + mod1) %mod1;
             auto h2 = (hash2[r+1] - (hash2[l]*power2[len])%mod2 + mod2) %mod2;
            return {h1,h2};
        }
    };
    StrHash sh, revsh;

class Solution {
public:
    
    // any candidate string without materializing
    // does:
    // hash of any prefix
    // comparing prefix hash with another candidate
    // getting char at index
    struct Candidate {
        public:
        int rev1, l1, r1; // part1
        int rev2, l2, r2; // part1

        pair<long,long> gethash(int r){
            int len = r1-l1+1;
            if(r<len){
                return rev1? revsh.gethash(l1,l1+r) : sh.gethash(l1,l1+r);
            }
            int len2 = r-len+1;
            r-=len;
            auto ll = rev1? revsh.gethash(l1,r1) : sh.gethash(l1,r1);
            auto rr = rev2? revsh.gethash(l2,l2+r) : sh.gethash(l2,l2+r);
            
            ll.first = (ll.first*power1[len2]%mod1 + rr.first)%mod1;
            ll.second = (ll.second*power2[len2]%mod2 + rr.second)%mod2;
            return ll;
        }

        bool issmaller(Candidate can){
            int l = 0, r = n-1, mid = 0, idx = mid;
            while(l<r){
                mid = (l+r)/2;
                if(gethash(mid) == can.gethash(mid)) l = mid+1;
                else r = idx = mid;
            }
            return getch(l) < can.getch(l);
        }
        
        char firstch(){
            return getch(0);
        }
        char getch(int idx){
            int len1 = r1-l1+1;
            if(idx<len1) return rev1 ? revstr[l1+idx] : str[l1+idx];
            idx -= len1;
            return rev2 ? revstr[l2+idx] : str[l2+idx];
        }
    };

    string lexSmallest(string s) {
        n = s.size();
        str = s;
        revstr = s;
        reverse(revstr.begin(),revstr.end());
        power1 = vector<long> (n+1,1);
        power2 = vector<long> (n+1,1);
        sh = StrHash(str);
        revsh = StrHash(revstr);
        
        // calculate power
        // init hash objects for str and reverse strng
        // iterate over type 1 and type2 string candidates to get best
        for(auto i=1;i<=n;i++){
            power1[i] = (power1[i-1]*base1)%mod1;
            power2[i] = (power2[i-1]*base2)%mod2;
        }

        Candidate best = {0,0,0,0,1,n-1};
        // compare with all type1 strings
        for(auto k=2;k<=n;k++){
            Candidate cur = {1,n-k,n-1,0,k,n-1};
            if((cur.firstch() < best.firstch())
                || ( (cur.firstch() == best.firstch()) &&  cur.issmaller(best) )) best = cur;

            Candidate cur1 = {0,0,n-k-1,1,0,k-1};
            if(cur1.firstch() > best.firstch()) continue;
            if((cur1.firstch() < best.firstch())
                || (cur1.issmaller(best) )) best = cur1;
        }
        string ans = "";
        for(auto i=0;i<n;i++){
            ans.push_back(best.getch(i));
        }
        return ans;
    }
};
