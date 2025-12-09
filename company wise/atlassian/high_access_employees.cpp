// sev1 28/10/25
// had bug in 2 pointer


class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        vector<string> ans;
        sort(access_times.begin(),access_times.end(),[](vector<string>& v1, vector<string>& v2){
            if(v1[0] == v2[0]) return v1[1] < v2[1];
            return v1[0]<v2[0];
        });
        int n = access_times.size();
        for(auto i=0;i<n;i++){
            auto emp = access_times[i][0];
            int l = i, r = i;
            while((r<n) && (access_times[r][0] == emp)) {
                while(!withInHour(access_times[l][1],access_times[r][1]) && (l<r)) l++;
                if(r-l+1>=3){
                    ans.push_back(emp);
                    while((r<n) && (access_times[r][0] == emp)) r++;
                    break;
                }
                r++;
            }
            i = r-1;
        }
        return ans;
    }

    bool withInHour(string& str1, string& str2){
        auto h1 = stoi(str1.substr(0,2)), m1 = stoi(str1.substr(2)),
            h2 = stoi(str2.substr(0,2)), m2 = stoi(str2.substr(2));
        if(abs(h1-h2)>1) return false;
        if(h1 == h2) return true;
        return (h1<h2 ? (60-m1) + m2 : (60-m2) + m1 ) < 60;
    }
};