// 26 apr 2025
// 2 compiler error.
// sev1


class Solution {
    public:
        vector<int> exclusiveTime(int n, vector<string>& logs) {
            vector<vector<int>> arr;
            for(auto it : logs){
                arr.push_back(parse(it));
            }
            int m = logs.size();
            vector<int> ans(n,0);
            stack<vector<int>> st;
    
            for(auto i=0,cur = 0;i<m;i++,cur = 0){
                if(arr[i][1] == 1){
                    while((st.top()[0] != arr[i][0]) || (st.top()[1] != 0)) {
                        cur += st.top()[2];
                        st.pop();
                    }
                    int timeGap = arr[i][2]-st.top()[2] + 1;
                    ans[st.top()[0]] += timeGap - cur;
                    st.top() = {arr[i][0],2,timeGap};
                } else {
                    st.push(arr[i]);
                }
            }
            return ans;
        }
    
        vector<int> parse(string& s){
            vector<int> cur = {0,0,0};
            int n = s.size(), id = 0, time = 0, idx = 0;
            string idStr = "";
            while((idx<n) &&(s[idx] != ':')){
                idStr.push_back(s[idx++]);
            }
            cur[0] = stoi(idStr);
            idx++;
            cur[1] = s[idx] == 's' ? 0 : 1;
            while((idx<n) &&(s[idx] != ':'))idx++;
            idx++;
            idStr = "";
            while(idx<n){
                idStr.push_back(s[idx++]);
            }
            cur[2] = stoi(idStr);
            return cur;
        }
    };
    