// 13 mar 2025
// got the idea..
// missed 2 corner cases
// also messed up implementation somewhat.
// sev1

class DetectSquares {
    public:
        unordered_map<int,multiset<int>> xAxis, yAxis;
        unordered_map<string,int> cnt;
        DetectSquares() {
            xAxis.clear();
            yAxis.clear();
            cnt.clear();
        }
        
        void add(vector<int> point) {
            auto x = point[0], y = point[1];
            xAxis[x].insert(y);
            yAxis[y].insert(x);
            cnt[makeKey(x,y)]++;
        }
    
        string makeKey(int x, int y){
            return to_string(x)+":"+to_string(y);
        }
        
        
        int count(vector<int> point) {
            auto x = point[0], y = point[1], ans = 0;
            for(auto it: xAxis[x]){
                auto y1 = it, len = abs(y1-y);
                if(y1 == y) continue;
                auto key1 = makeKey(x+len,y), key2 = makeKey(x+len,y1);
                auto cnt1 = cnt.find(key1) == cnt.end() ? 0 : cnt[key1],
                    cnt2 = cnt.find(key2) == cnt.end() ? 0 : cnt[key2];
                ans += cnt1*cnt2;
    
                key1 = makeKey(x-len,y);
                key2 = makeKey(x-len,y1);
                cnt1 = cnt.find(key1) == cnt.end() ? 0 : cnt[key1];
                cnt2 = cnt.find(key2) == cnt.end() ? 0 : cnt[key2];
                ans += cnt1*cnt2;
            }
            return ans;
        }
    };
    
    //  11 :{2}