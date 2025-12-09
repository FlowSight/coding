//sev0..failed to come up with classic sort..28/10/25


// classic encoding of pos wise votes.. missed it
class Solution {
public:
    string rankTeams(vector<string>& votes) {
        vector<vector<int>> arr(26,vector<int>(27,0));
        for(auto c: votes[0]) arr[c-'A'][26] = c;
        for(auto v : votes){
            for(auto i=0;i<v.size();i++){
                arr[v[i]-'A'][i]--;
            }
        }
        string ans = "";
        sort(arr.begin(),arr.end());
        for(auto i=0;i<26;i++){
            if(arr[i].back() == 0) continue;
            ans.push_back(arr[i].back());
        }
        return ans;
    }
};

// ABC
// A: -5 0 0 A
// B: 0 -2 -3 B
// C: 0 -3 -3 C