// 10 jan 2025
// 6.42 mins..
// logical mistake : didnt see code properly..
// could not optimize.. // TODO : optimize
// verdict : FAIL
    string customSortString(string order, string s) {
        vector<int> rank(26,26);
        int n = order.size();
        for(auto i=0;i<n;i++)rank[order[i]-'a'] = i;
        sort(s.begin(),s.end(),[rank](char c1, char c2){
            auto rank1 = rank[c1-'a'],
                rank2 = rank[c2-'a'];
            return rank1 < rank2;
        });
        return s;
    }
