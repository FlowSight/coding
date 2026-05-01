#include<bits/stdc++.h>

using namespace std;

typedef vector<string> vs;

long iptolong(string ip){
    stringstream ss(ip);
    string cur = "";
    vector<long> arr;
    long ans = 0;
    while (getline(ss,cur,'.'))
    {
        arr.push_back(stol(cur));
    }
    ans = (arr[0]<<24) + (arr[1]<<16) + (arr[2]<<8) + (arr[3]);
    return ans;
}

string iptostr(long ip) {
    vs arr;
    string ans = "";
    for(auto i=0;i<4;i++){
        arr.push_back(to_string(ip & 0x000000ff));
        ip = ip>>8;
    }
    reverse(arr.begin(),arr.end());
    for(auto i=0;i<4;i++) {
        ans += arr[i];
        ans.push_back('.');
    }
    ans.pop_back();
    return ans;
}

vs iptocidr(string ip, int range){
    long start = iptolong(ip);
    long end = start+range-1;
    vs ans;
    while(start <= end){
        int idx = 0;
        for(;idx<32;idx++){
            if(start & (1<<idx)) break;
        }
        int gap = log2(end-start+1);
        int suf = min(gap,idx), chosen = min(gap,suf);
        int mask = 32 - suf;
        ans.push_back(iptostr(start)+"/"+to_string(mask));
        start += (1<<suf);
    }
    return ans;
}


int main(){
    auto ans = iptocidr("0.0.0.111",10);
    for(auto it : ans)cout<<it<<endl;
    return 0;
}
