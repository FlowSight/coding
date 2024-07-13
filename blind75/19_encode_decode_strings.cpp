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