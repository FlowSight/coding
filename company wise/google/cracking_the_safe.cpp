// sev0..13feb26.
// didnt know de bruijn seq..
// fucked up dfs implementation..sev0

// the key was, if you find sol once, thats guaranteed to be minimal de bruijn seq
// so, trying other paths makes no sense..return true+early

class Solution {
public:
    unordered_set<string> keys;
    int total, len;
    string ans;
    string crackSafe(int n, int k) {
        keys.clear();
        total = pow(k,n);
        len = total+n;
        string cur = string(n,'0');
        keys.insert(cur);
        ans = "";
        helper(cur,n,k);
        return ans;
    }

    bool helper(string& str, int& n, int& k){
        //cout<<str<<" " <<keys.size()<<endl;
        if(keys.size() == total){
            if(str.size() <= len){
                len = str.size();
                ans = str;
            }
            return true;
        }
        for(auto c=0;c<k;c++){
            str.push_back(c+'0');
            auto cur = str.substr(str.size()-n,n);
            if(keys.find(cur) == keys.end()) {
                keys.insert(cur);
                if(helper(str,n,k)) return true;
                keys.erase(cur);
            }
            str.pop_back();
        }
        return false;
    }
};
