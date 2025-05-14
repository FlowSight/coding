// 22 apr..
// missed a corner case..
// sev2

class Solution {
    public:
        int maximumSwap(int num) {
            string s = to_string(num);
            int n = s.size(), maxsofar = n-1;
            vector<int> cand = {0,0};
            for(auto i=n-2;i>=0;i--){
                if(s[i] < s[maxsofar]) {
                    cand = {i,maxsofar};
                }
                else if(s[i] > s[maxsofar]){
                    maxsofar = i;
                }
            }
            swap(s[cand[0]],s[cand[1]]);
            return stoi(s);
    
        }
    };

class Solution {
    public:
        int maximumSwap(int num) {
            if(num < 10) return num;
    
            auto str = to_string(num);
            int n = str.size();
            vector<int> sufMax(n,n-1);
    
            for(auto i=n-2;i>=0;i--){
                if(str[sufMax[i+1]] >= str[i]) sufMax[i] = sufMax[i+1];
                else sufMax[i] = i;
            }
            for(auto i=0;i<n;i++){
                if(str[i] != str[sufMax[i]]){
                    swap(str[i],str[sufMax[i]]);
                    break;
                } 
            }
            return stoi(str);
        }
    };
    
    // 987