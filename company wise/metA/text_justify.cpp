// 3 june 2025.
// corner case misses..sev0
// 30 mins 

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int idx = 0, n = words.size(), cur = 0, curLen = 0;
        string tmp = "";
        while(idx<n) {
            cur = idx;
            curLen = 0;
            tmp = "";
            for(;cur<n;){
                int wordCntSofar = cur-idx, spaceCntNow = wordCntSofar;
                if(curLen + spaceCntNow + words[cur].size() > maxWidth) {
                    break;
                }
                curLen += words[cur++].size();
            }
            int wordsTaken = cur-idx, 
                isLastLine = (cur == n),
                noOfGaps =  wordsTaken -1,
                totalGap = maxWidth - curLen, 
                gapSize =  isLastLine ? 1 : (noOfGaps ? totalGap/noOfGaps : 0),
                gapRemaining = totalGap - (noOfGaps * gapSize);
            for(auto i=idx;i<cur;i++){
                if(i>idx){
                    if(isLastLine)tmp.push_back(' ');
                    else {
                        for(auto j=1;(j<=gapSize);j++) tmp.push_back(' ');
                        if(gapRemaining){
                            tmp.push_back(' ');
                            gapRemaining--;
                        }
                    }
                }
                for(auto &c: words[i]) tmp.push_back(c);
            }
            while(gapRemaining) {
                tmp.push_back(' ');
                gapRemaining--;
            }
            idx = cur;
            ans.push_back(tmp);
        }
        return ans;
    }
};

// left and right justified

// 1. start going from idx, check until we can accomodate no more words
// 2. calculate extra space, assign even space. Even if then space is remaining..then keep adding rest on to left most space
// 3. form strings like this and return list of string

// a  computer.  Art is