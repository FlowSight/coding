// 22 apr 2025
// 10 mins..clean

// 27 dec 2024..
// 13 min..
// 1 compiler error
// didnt read qs initiallly..while dry running realized the actual ans..
// verdict : FAIL


    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int i = 0, j = 0, m = firstList.size(), n = secondList.size();
        vector<vector<int>> ans;
        while((i<m) && (j<n)){
            if(firstList[i][1] < secondList[j][0]){
                i++;
            } else if(secondList[j][1] < firstList[i][0]){
                j++;
            } else {
                ans.push_back({max(firstList[i][0],secondList[j][0]), min(firstList[i][1],secondList[j][1])});
                if(firstList[i][1] > secondList[j][1]){
                    j++;
                } else {
                    i++;
                }
            }
        }
        return ans;

    }
};