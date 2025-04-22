// 12 apr 2025
// 2 compiler mistake..
// but code was better than before...but 12 mins
// sev3

// 29 march 2025
// 17 min..
// no mistake..but didnt use sep as i thought sep like $ is inside 256

class Codec {
    public:
    
        // Encodes a list of strings to a single string.
        string encode(vector<string>& strs) {
            int n = strs.size(), idx = 0;
            string ans = "";
            serializeIntToStr(n,ans);
            for(auto &it : strs){
                auto len = it.size();
                serializeIntToStr(len,ans);
                for(auto c:it){
                    ans.push_back(c);
                }
            }
            return ans;
        }
    
        void serializeIntToStr(int num, string& ans){
            string res = "";
            int tmp = num;
            while(num){
                res.push_back('0'+num%10);
                num/=10;
            }
    
            if(tmp<100) res.push_back('0');
            if(tmp<10) res.push_back('0');
            if(tmp == 0)res.push_back('0');
    
            reverse(res.begin(),res.end());
    
            for(auto &c : res){
                ans.push_back(c);
            }
        }
    
        // Decodes a single string to a list of strings.
        vector<string> decode(string s) {
            vector<string> ans;
            int idx = 0;
            int len = getLen(s,idx);
            for(auto i=1;i<=len;i++){
                auto curLen = getLen(s,idx);
                string cur = "";
                for(auto j=1;j<=curLen;j++){
                    cur.push_back(s[idx++]);
                }
                ans.push_back(cur);
            }
            return ans;
        }
    
        int getLen(string& s, int& idx){
            int len = 0;
            for(auto i=0;i<3;i++){
                len = len*10+(s[idx++]-'0');
            }
            return len;
        }
    };
    
    // Your Codec object will be instantiated and called as such:
    // Codec codec;
    // codec.decode(codec.encode(strs));



class Solution {
public:
    /*
     * @param strs: a list of strings
     * @return: encodes a list of strings to a single string.
     */
     char sep = '$';
    string encode(vector<string> &strs) {
        string ans = "";
        for(auto& it : strs){
            string lenStr = to_string(it.size());
            for(auto c: lenStr)ans.push_back(c);
            ans.push_back(sep);
            for(auto c : it)ans.push_back(c);
        }
        return ans;
    }

    /*
     * @param str: A string
     * @return: decodes a single string to a list of strings
     */
    vector<string> decode(string &str) {
        int idx = 0;
        vector<string> ans;
        while(idx<str.size()){
            ans.push_back(decodeHelper(str,idx));
        }
        return ans;
    }

    string decodeHelper(string& str, int& idx){
        string lenStr = "", val = "";
        while(idx<str.size() && str[idx]!=sep){
            lenStr.push_back(str[idx++]);
        }
        idx++;
        int len = stoi(lenStr);
        for(auto i=1;i<=len;i++){
            val.push_back(str[idx++]);
        }
        return val;
    }
};