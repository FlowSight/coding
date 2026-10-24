/// Severity: Sev0
// Date: 12Oct26
// LC: 726
// Where I failed: description
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
     map<string,int> mm;
    string countOfAtoms(string formula) {
        int n = formula.size(), idx = 0;
       auto tmp = helper(formula,idx);
       for(auto it : tmp) mm[it.first] = it.second;
       string ans = "";
       for(auto it : mm){
        ans += it.first;
        if(it.second > 1) ans += to_string(it.second);
       }
       return ans;
    }
    unordered_map<string,int> helper(string& str, int& idx){
        unordered_map<string,int> ans, tmp;
        int dig = 0;
        while(idx < str.size()) {
            if(str[idx] == '(') {
                for(auto it : tmp) ans[it.first] += it.second;
                tmp.clear();
                idx++;
                tmp = helper(str,idx);
            } else if(str[idx] == ')'){
                idx++;
                break;
            } else if(isdigit(str[idx])) {
                dig = 0;
                while((idx<str.size()) && isdigit(str[idx])) {
                    dig = dig*10 + (str[idx++]-'0');
                }
                for(auto it : tmp) {
                    ans[it.first] += dig * it.second;
                }
                tmp.clear();
                dig = 1;
            } else {
                get_elem(str,idx,tmp);
            }
        }
        for(auto it : tmp) ans[it.first] += it.second;
        return ans;
    }

    void get_elem(string& str, int& idx, unordered_map<string,int>& cnt){
        string cur = "";
        int dig = 0;
        while(idx<str.size()) {
                if(isdigit(str[idx])) {
                    dig = 0;
                    while((idx<str.size()) && isdigit(str[idx])) {
                        dig = dig*10 + (str[idx++]-'0');
                    }
                    cnt[cur] += (dig-1);
                }
                else if(isupper(str[idx])) {
                    if(cur.size() > 0) cnt[cur]++;
                    cur = "";
                    cur.push_back(str[idx++]);
                } else if(islower(str[idx])) {
                     cur.push_back(str[idx++]);
                } else break;
                
        }
        if(cur.size()) cnt[cur]++;
    }

    bool isdigit(char c){
       return  (c >= '0') && (c <= '9');
    }
};
