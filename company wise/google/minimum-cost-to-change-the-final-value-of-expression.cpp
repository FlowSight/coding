/// Severity: Sev0
// Date: 18Feb26
// 
// Where I failed: algo
// Pattern: 2d dfs..i kept thinking dfs(i..j) is n^2..
//



class Solution {
public:
    unordered_map<int,int> mm;
    int minOperationsToFlip(string str) {
        stack<int> st;
        int n = str.size();
        
        for(auto i=0;i<n;i++) {
            if(str[i] == '(') st.push(i);
            else if(str[i] == ')') {
                mm[i] = st.top();
                st.pop();
            }
        }
        return dfs(str,0,n-1)[1];
    }
    // ret : (val existing, min op req)
    vector<int> dfs(string& str, int left, int right){
        if(left == right) return {str[left]-'0',1};
        vector<int> ll, rr, ans;
        char op = 'f';
        if(str[right] == ')') {
            if(mm[right] == left) return dfs(str,left+1,right-1);
            ll = dfs(str,left,mm[right]-2);
            rr = dfs(str,mm[right]+1, right-1);
            op = str[mm[right]-1];
        } else {
            ll = dfs(str, left, right-2);
            rr = dfs(str,right,right);
            op = str[right-1];
        }
        if(op == '&'){
            if(ll[0] ^ rr[0]) ans = {0,1};
            else if(ll[0] && rr[0]) ans = {1,min(ll[1],rr[1])};
            else ans = {0,1+min(ll[1],rr[1]) };
        } else {
            if(ll[0] ^ rr[0]) ans = {1,1};
            else if(ll[0] && rr[0]) ans = {1,1+min(ll[1],rr[1])};
            else ans = {0,min(ll[1],rr[1])};
        }
        return ans;
    }
};

// () | 1
// ()