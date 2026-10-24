/// Severity: Sev0
// Date: 24Oct26
// LC: 850
// Where I failed: description
// Pattern:  line sweep
// Notes: additional_notes

class Solution {
public:
    struct Range { 
        int y1, y2;
        Range(int _y1, int _y2){
            y1 = _y1, y2 = _y2;
        }
        bool operator< (const Range& ran) const {
            if(y1 == ran.y1) return y2 < ran.y2;
            return y1 < ran.y1;
        }
        // bool operator== (const Range& ran){
        //     return (y1==ran.y1 )&& (y2 == ran.y2);
        // }
    };

    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int mod = 1e9+7;
    int rectangleArea(vector<vector<int>>& rectangles) {
        multiset<Range> ss;
        map<int,vvi> mm;
        int n = rectangles.size(), last = -1;
        long long ans = 0;
        for(auto i=0;i<n; i++) {
            auto x1 = rectangles[i][0] , y1 = rectangles[i][1], x2 = rectangles[i][2], y2 = rectangles[i][3], hei = y2 - y1;
            mm[x1].push_back({y1,y2,i,0});
            mm[x2].push_back({y1,y2,i,1});
        }
        last = (mm.begin()->first);
        for(auto it : mm){
            long long curx = (it.first) , delx = curx - last;
            long long cury = getcury(ss);
            long long curarea = (delx * cury) %mod;
            //cout<<curx<<" "<<cury<<" "<<*(ss.rbegin())<<" "<< *(ss.begin())<<endl;
            ans = (ans + curarea ) %mod; // hei * wid

            for(auto it1: it.second) {
                if(it1[3] == 0) {
                    ss.insert(Range(it1[0],it1[1])); // start
                }
                else  {
                    ss.erase(ss.lower_bound(Range(it1[0],it1[1]))); //end
                }
            }
            last = curx;
        }
        return ans;
    }
    long long getcury(multiset<Range>& ss) {
        int i=0, start = -1, end = -1;
        long long sum = 0;
        for(auto it : ss){
            int st = it.y1, en = it.y2;
            if(end >= st) {
                end = max(end,en); 
            } else {
                sum = (sum +  (end-start))%mod;
                start = st;
                end = en;
            }
        }
        return sum;
    }
};