/// Severity: Sev0
// Date: 06Oct26
// LC: 248
// Where I failed: i overcomplicated ..missed case: low == 0 (skip continue), seperating (0,1,8) vs(6,9)
    // i could have merged helper_in_between and helper_greater_lesser
// Pattern: dfs on digit
// Notes: 



class Solution {
public:
    unordered_map<char,char> stogmap;
    int strobogrammaticInRange(string low, string high) {
        stogmap['0'] = '0';
        stogmap['1'] = '1';
        stogmap['6'] = '9';
        stogmap['8'] = '8';
        stogmap['9'] = '6';
        int lowsize = low.size(), highsize = high.size();
        int ans = get_middle_nos(lowsize+1,highsize-1);
        ans += get_in_range_strogs(low,high);
        return ans;
    }

    int get_middle_nos(int low, int high){
        if(low> high) return 0;
        int ans = 0;
        for(auto i=low;i<=high;i++){
            ans += get_no_of_stogs(i);
        }
        return ans;
    }
    int get_no_of_stogs(int len){
        int ans = 1;
        for(auto i=1;i<=len/2;i++){
            ans *= (4 + (i >1));
        }
        if(len %2 ) ans *= 3;
        return ans;
    }
    int get_in_range_strogs(string low, string high){
        int m = low.size(), n = high.size();
        if(m == n) {
            string cur(m,'0');
            return helper_in_between(cur,low,high);
        }
        string curlow(m,'0'), curhigh(n,'0');
        return helper_greater_lesser(low,curlow,0) + helper_greater_lesser(high,curhigh,1);
    }

    int helper_in_between(string& cur, string& low, string& high, int idx = 0){
        if(low.size() != high.size()) return 0;
        int idx1 = low.size() - idx -1;
        if(idx > idx1) return (cur >= low) && (cur <= high);
        int ans = 0;
        auto tmp1 = cur[idx], tmp2 = cur[idx1];
        for(auto& it : stogmap){
            auto ch = it.first, chmap = it.second;
            if((idx == 0 ) && (ch == '0') && (low != "0")) continue;
            if((idx == idx1) && ((ch == '6') || (ch == '9'))) continue;
            cur[idx] = ch;
            cur[idx1] = chmap;
            ans += helper_in_between(cur,low,high,idx+1);
        }
        cur[idx] = tmp1;
        cur[idx1] = tmp2;
        return ans;
    }
    // greater/lesser but same len; cmp =  0 means cur >= str
    int helper_greater_lesser(string& str, string& cur,int cmp, int idx = 0){
        int idx1 = str.size() - idx -1, ans = 0;
        if(idx > idx1) return cmp ? (cur <= str ): (cur >= str);
        auto tmp1 = cur[idx], tmp2 = cur[idx1];
        for(auto& it : stogmap){
            auto ch = it.first, chmap = it.second;
            if((idx == 0 ) && (ch == '0') && (str != "0") ) continue;
            if((idx == idx1) && ((ch == '6') || (ch == '9')) ) continue;
            cur[idx] = ch;
            cur[idx1] = chmap;
            ans += helper_greater_lesser(str,cur,cmp,idx+1);
        }
        cur[idx] = tmp1;
        cur[idx1] = tmp2;
        return ans;
    }
};
