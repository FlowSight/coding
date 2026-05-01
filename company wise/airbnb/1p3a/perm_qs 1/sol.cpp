// 4123
// 2489

// 4123
// 1234

// 2134

// len 
// same no ? yes 

#include<bits/stdc++.h>

using namespace std;

string ans = "-1";
multiset<char> ss;

bool helper(string num, string limit, int idx, string& cur){
    if(idx==num.size()){
        for(auto it : ss) {
            cur.push_back(it);
        }
        ans = cur;
        return true;
    }
    auto dig = limit[idx];
    auto it = ss.lower_bound(dig);
    while (it != ss.end()) {
        cur.push_back(*(it));
        ss.erase(it);
        if(helper(num, limit,idx+1,cur)) return true;

        ss.insert(dig);
        dig++;
        it = ss.lower_bound(dig);
        cur.pop_back();
    }
    return false;
}


string getsmallestnogreater(string num, string limit){
    ss.clear();
    ans = "-1";
    if(limit.size() > num.size()) return "-1";
    if(limit.size() < num.size())  limit = string(num.size()-limit.size(),'0') + limit;
    for(auto c: num) ss.insert(c);
    string cur = "";
    helper(num,limit,0,cur);
    return ans;
}




int main(){
    cout<<getsmallestnogreater("4139","4109")<<endl;
    cout<<getsmallestnogreater("0149","200")<<endl;
    return 0;
}