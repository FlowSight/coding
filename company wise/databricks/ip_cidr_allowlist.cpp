// Implement a firewall feature considering following points:

// Some rules are defined ("ALLOW", "192.168.1.0/24"), ("ALLOW", "1.2.3.4"), ("DENY", "10.5.12.10/28")
// Only allow requests from IP addresses that follow the rule. All other requests should be denied.

#include <iostream>
#include<vector>
#include <unordered_map>
#include <sstream>

using namespace std;

namespace Interview {
class Trie {
    public:
    vector<Trie*> children = {nullptr,nullptr};
    bool allow;
    Trie(bool allow = false){
        allow = false;
    }
    void add(vector<int> ipArr,int idx, int prefix, int _allow){
        prefix--;
        if(prefix == 0) {
            allow = _allow;
            return;
        }
        if(!children[ipArr[idx]]) {
            children[ipArr[idx]] = new Trie();
        }
        children[ipArr[idx]]->add(ipArr,idx-1,prefix,_allow);
    }

    bool find(vector<int> ipArr,int idx){
        bool ans = allow;
        if(ans) return ans;
        int val = ipArr[idx];
        if(!children[val]) return ans;
        return ans | children[val]->find(ipArr,idx-1);
    }
};

vector<int> processIp(string ip){
    stringstream ss(ip);
    string tmp = "";
    vector<int> ipArr;
    while(getline(ss, tmp, '.')){
        int val = stoi(tmp);
        for(auto i=7;i>=0;i--) ipArr.push_back((bool) (val & (1<<i)));
    }
    reverse(ipArr.begin(),ipArr.end());
    return ipArr;
}

void parseAndFillTrie(Trie* root, vector<vector<string>>& arr) {
    for(auto &it : arr){
        int allowDeny = (it[0][0] =='A' ? 1 : 0);
        auto cidr = it[1];
        auto it1 = cidr.find('/');
        int pref = 32;
        string ip = cidr;
        if(it1 != string::npos) {
            pref = stoi(cidr.substr(it1+1));
            ip = cidr.substr(0,it1);
        }
        vector<int> ipArr = processIp(ip);
        root->add(ipArr,31,pref,allowDeny);
    }
}

void tester() {
    vector<vector<string>> arr = {
        {"ALLOW", "192.168.1.0/24"},
        {"ALLOW", "1.2.3.4"},
        {"DENY", "10.5.12.10/28"}
    };
    vector<string> ipToTest = {"192.168.1.1","10.5.12.11","192.168.1.255"};
    Trie* trie = new Trie();
    parseAndFillTrie(trie,arr);
    for(auto it : ipToTest){
        auto ipArr = processIp(it);
        cout<<trie->find(ipArr,31)<<endl;
    }
}

}
int main(){
    Interview::tester();
}