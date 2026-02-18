// 3feb2026..
// could not think of key optimization : make string similar from left..
// dont do n^2 swaps for each word, just check for word[i] which j can it be swapped with : O(n)
// pattern : bfs distance , left to right uniformity
// sev0..sev0
class Solution {
public:
    int kSimilarity(string s1, string s2) {
        int n = s1.size(), dist = 0;
        unordered_set<string> visited;
        queue<string> q;
        visited.insert(s1);
        q.push(s1);
        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto tp = q.front();
                q.pop();
                int matchCnt = 0;
                for(auto i=0;i<n;i++){
                    if(tp[i] == s2[i]) {
                        matchCnt++;
                        continue;
                    }
                    for(auto j=i;j<n;j++){
                        if(i==j) continue;
                        if(tp[j] != s2[i]) continue;
                        swap(tp[i],tp[j]);
                        if(visited.find(tp) == visited.end()) {
                            visited.insert(tp);
                            q.push(tp);
                        }
                        swap(tp[i],tp[j]);
                    }
                    break;
                }
                if(matchCnt == n) return dist;
            }
            dist++;
        }
        return dist;
    }
};


