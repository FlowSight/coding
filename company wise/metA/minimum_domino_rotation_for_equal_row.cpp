// can be done with 2 pass

class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int n = tops.size(), botSwap = 0, topSwap = 0, ans = n+1;
        for(auto i=1;i<=6;i++){
            for(auto j=0;j<n;j++){
                if(tops[j] == i) continue;
                else if(bottoms[j] != i) {
                    topSwap = -1;
                    break;
                }
                topSwap++;
            }
            if(topSwap != -1) ans = min(ans,topSwap);
            topSwap = 0;
        }

        for(auto i=1;i<=6;i++){
            for(auto j=0;j<n;j++){
                if(bottoms[j] == i) continue;
                else if(tops[j] != i) {
                    botSwap = -1;
                    break;
                }
                botSwap++;
            }
            if(botSwap != -1) ans = min(ans,botSwap);
            botSwap = 0;
        }
        return ans == n+1 ? -1 : ans;
    }
};