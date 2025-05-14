// 21 apr 2025
// 1 compiler + 1 logical mistake..
// sev1

// 18 jan 2025..
// 13 mins..
// no mistake
// verdict : PASS


// MEta key : use the getline method

string simplifyPath(string path) {
    stringstream ss(path);
    vector<string> arr;
    string tmp = "", ans = "";
    while(getline(ss,tmp,'/')){
        if((tmp == ".") || (tmp.size() == 0)) continue;
        if(tmp == "..") { 
            if(!arr.empty()) {
                arr.pop_back();
            }
        }
        else arr.push_back(tmp);
    }

    for(auto it : arr){
        ans.push_back('/');
        for(auto c: it) ans.push_back(c);
    }
    return ans.size() == 0 ? "/" : ans;
}

class Solution {
public:
    string simplifyPath(string path) {
        int idx = 0;
        string ans = "";
        vector<string> st;
        while(true){
            auto cur = getNext(path,idx);
            if(cur.size()){
                if(cur == ".")continue;
                if(cur == ".."){
                    if(st.size())st.pop_back();
                }
                else st.push_back(cur);
            } else break;
        }
        for(auto i=0;i<st.size();i++){
            ans.push_back('/');
            for(auto &c : st[i])ans.push_back(c);
        }
        return ans.size() == 0 ? "/" :  ans;
    }

    string getNext(string& path, int& idx) {
        string ans = "";
        while((idx<path.size()) && (path[idx]=='/'))idx++;
        while((idx<path.size()) && (path[idx]!='/')){
            ans.push_back(path[idx++]);
         }
         return ans;
    }
};