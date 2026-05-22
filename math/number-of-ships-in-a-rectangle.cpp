/// Severity: Sev1
// Date: 18May26
// LC: 1274
// Where I failed: didnt think of corner case of cell..truncated cell..
// Pattern: pattern_name
// Notes: sev0..need to think of cell+integer coordinates..
//didnt think of elimination of coordianates


/**
 * // This is Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *   public:
 *     bool hasShips(vector<int> topRight, vector<int> bottomleft);
 * };
 */

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    int countShips(Sea sea, vector<int> topright, vector<int> bottomleft) {
        int x1 = topright[0], y1 = topright[1], 
            x2 = bottomleft[0], y2 = bottomleft[1];
        if((topright[0] < bottomleft[0] )|| (topright[1] < bottomleft[1])) return 0;
        if(!sea.hasShips(topright,bottomleft)) return 0;
        if(ispoint(topright,bottomleft)){
            return 1;
        }
        auto quads = getquads(topright,bottomleft);
        int ans = 0;
        for(auto it : quads){
            if((it[0][0] < it[1][0] )|| (it[0][1] < it[1][1])) continue;
            if(!sea.hasShips(it[0],it[1])) continue;
            ans += countShips(sea,it[0],it[1]);
        }
        return ans;
    }
    vvvi getquads(vector<int>& topright, vector<int>& bottomleft){
        int x1 = topright[0], y1 = topright[1], 
            x2 = bottomleft[0], y2 = bottomleft[1],
            xmid = (x1+x2)/2, ymid = (y1+y2)/2;
        //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<xmid<<" "<<ymid<<endl;
        if(x1 == x2) return {{{x1,ymid},bottomleft}, {topright,{x1,ymid+1}}};
        if(y1 == y2) return {{{xmid,y1},bottomleft}, {topright,{xmid+1,y1}}};
        vvi tl = {{xmid,y1},{x2,ymid}}, tr = {topright,{xmid+1,ymid}},
            bl = {{xmid,ymid-1},bottomleft}, br = {{x1,ymid-1},{xmid+1,y2}};
        return {tl,tr,bl,br};
    }
};