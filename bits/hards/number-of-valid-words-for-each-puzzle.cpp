/// Severity: Sev0
// Date: 21Oct26
// LC: 1178
// Where I failed: all smaller bit subsets of a number can be obtained by num = (num-1)&bm
// Pattern: ???
// Notes: additional_notes



class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int,int> mm; // map[bm] = total cnt of that bm
        for(auto &it : words) mm[getbm(it)]++;
        vector<int> ans;
        for(auto &it : puzzles) {
            int bm = getbm(it), curans = 0;
            int cur = bm, firstletterbm = (1<<(it[0]-'a'));

            while(cur) {
                if((cur & firstletterbm) == firstletterbm) curans += mm[cur];
                cur = (cur-1) & bm;
            }
            ans.push_back(curans);
        }
        return ans;
    }

    int getbm(string& word){
        int ans = 0;
        for(auto c: word){
            ans = ans | (1<<(c-'a'));
        }
        return ans;
    }

};