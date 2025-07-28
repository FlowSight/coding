class Solution {
public:
    string removeKdigits(string num, int k) {
        vector<vector<int>> cntIdx(10);
        string ans = "";
        int n= num.size();
        for(auto i=n-1;i>=0;i--){
            cntIdx[num[i]-'0'].push_back(i);
        }
        for(auto i=0,drop = 0;i<n;i++,drop = 0) {
            int dig = num[i]-'0';
            for(auto j=dig-1;j>=0;j--) {
                if(cntIdx[j].size() && (cntIdx[j].back()-i <=k)) {
                    drop = 1;
                    k--;
                    break;
                }
            }
            if(!drop) {
                if((ans.size()>0) || dig)ans.push_back(num[i]);
            }
            cntIdx[dig].pop_back();
        }
        while(k && ans.size()) {
            ans.pop_back();
            k--;
        }
        return ans.size() ? ans : "0";
    }
};
