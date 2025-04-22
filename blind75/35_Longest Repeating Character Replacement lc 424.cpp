// 16 apr..got the idea..best approach..
// 2 loop edge case mistake..
// took long time to code 20 mins..
// sev2

class Solution {
    public:
        int characterReplacement(string s, int k) {
            vector<int> cnt(26,0); 
            set<pair<int,int>> ss; //cnt,char
            for(auto i=0;i<26;i++){
                ss.insert(make_pair(0,i));
            }
            int ans = 0, n = s.size();
            for(auto l=0,r=0,rem = 0;r<n;r++){
                ss.erase(make_pair(cnt[s[r]-'A'],s[r]-'A'));
                cnt[s[r]-'A']++;
                ss.insert(make_pair(cnt[s[r]-'A'],s[r]-'A'));
                rem = (r-l+1) - ss.rbegin()->first;
    
                while((rem > k) && (l<r)){
                    ss.erase(make_pair(cnt[s[l]-'A'],s[l]-'A'));
                    cnt[s[l]-'A']--;
                    ss.insert(make_pair(cnt[s[l]-'A'],s[l]-'A'));
                    l++;
                    rem = (r-l+1) - ss.rbegin()->first;
                }
                ans = max(ans,r-l+1);
            }
            return ans;
        }
    };


class Solution {
public:
    unordered_map<char,int> cnt;
    int characterReplacement(string s, int k) {
        cnt.clear();
        int n = s.size(), remaining = 0, ans = 0, highest = 0;
        for(auto r = 0, l = 0;r<n;r++){
            cnt[s[r]]++;
            remaining = getRemaining(r-l+1);
            while((remaining > k) && l<r){
                cnt[s[l++]]--;
                remaining = getRemaining(r-l+1);
            }
            if(l<=r)ans = max(ans,r-l+1);
        }
        return ans;
    }

    int getRemaining(int len){
        int high = 0;
        for(auto it : cnt){
            high = max(high,it.second);
        }
        return len-high;
    }
};