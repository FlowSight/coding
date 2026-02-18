//sev0..missed edge case
class Solution {
public:
    unordered_map<int,int> mm;
    vector<string> braceExpansionII(string str) {
        int n = str.size();
        stack<int> st;
        for(auto i=0;i<n;i++){
            if(str[i] == '{')st.push(i);
            else if(str[i] == '}') {
                mm[st.top()] = i;
                st.pop();
            }
        }
        auto tmp = helper(str,0,n-1);
        auto ans = vector<string>(tmp.begin(),tmp.end());
        sort(ans.begin(),ans.end());
        return ans;
    }

    unordered_set<string> helper(string& str, int l, int r){
        unordered_set<string> ans,tmp, tmp1;
        while(l<=r){
            if(str[l] == '{'){
                tmp1 = helper(str,l+1,mm[l]-1);
                l = mm[l]+1;
                tmp = mult(tmp,tmp1);
                tmp1.clear();
            } else if(str[l] == '}') l++;
            else if(str[l] == ',') {
                for(auto it : tmp) ans.insert(it);
                tmp.clear();
                l++;
            } else {
                tmp1.insert(string(1,str[l++]));
                tmp = mult(tmp,tmp1);
                tmp1.clear();
            }

        }
        for(auto it : tmp) ans.insert(it);
        return ans;
    }

    unordered_set<string> mult(unordered_set<string>& set1, unordered_set<string>& set2){
        if(set1.empty()) return set2;
        if(set2.empty()) return set1;
        unordered_set<string> ans;
        for(auto it1: set1){
            for(auto it2: set2){
                ans.insert(it1+it2);
            }
        }
        return ans;
    }
};