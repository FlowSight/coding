#include<iostream>
#include<unordered_set>
#include<sstream>

using namespace std;

typedef vector<string> vs;

struct CurStruct{
    public:
    string name;
    double q;
    int idx;
    CurStruct() = default;
    CurStruct(string _name, double _q, int _idx) {
        name = _name;
        q = _q;
        idx = _idx;
    }
    bool operator< (const CurStruct& cs) const {
        return q == cs.q ? idx < cs.idx : q > cs.q;
    }
};

class LanguageProcessor {
    public:
    LanguageProcessor() = default;
    vs parse_accept_language(string acceptlan, vs serverlan){
        unordered_set<string> allowed;
        for(auto it : serverlan)allowed.insert(it);
        stringstream ss(acceptlan);
        string str = "";
        vs tmp = parsehelper(acceptlan,','), ans;
        for(auto it : tmp){
            if(allowed.find(it) != allowed.end()) ans.push_back(it);
        }
        return ans;
    }

    vs parse_accept_languagePrefix(string acceptlan, vs serverlan){
        unordered_map<string,unordered_set<string>> allowed;
        for(auto it : serverlan){
            auto parts = parsehelper(it,'-');
            allowed[parts[0]].insert(it);
        }
        unordered_set<string> ansset;
        vector<CurStruct> tmp = parsehelper1(acceptlan,',');
        vs ans;
        for(auto it : tmp){
            if(it.name.size() >2) {
                // full langguage code
                auto lan = it.name.substr(0,2), reg = it.name.substr(3);
                if(allowed.find(lan) == allowed.end()) continue;
                if(allowed[lan].find(it.name) == allowed[it.name].end()) continue;
                if(ansset.find(it.name) != ansset.end()) continue;
                ansset.insert(it.name);
                ans.push_back(it.name);
            } else {
                if(it.name == "*") {
                    for(auto it1: serverlan ){
                        if(ansset.find(it1) != ansset.end()) continue;
                        ansset.insert(it1);
                        ans.push_back(it1);
                    }
                    break;
                }
                 if(allowed.find(it.name) == allowed.end()) continue;
                 for(auto it1 : allowed[it.name]) {
                    //auto curans = it + "-" +it1;
                    if(ansset.find(it1) != ansset.end()) continue;
                    ansset.insert(it1);
                    ans.push_back(it1);
                 }
            }
        }
        return ans;
    }

    private:

    vs parsehelper(string str, char sep){
        stringstream ss(str);
        string val = "";
        vs ans;
        while(getline(ss,val,sep)) {
            val = trimspace(val);
            ans.push_back(val);
        }
        return ans;
    }

     vector<CurStruct> parsehelper1(string str, char sep){
        vector<CurStruct> ans;
        vs arr = parsehelper(str,sep);
        for(auto i=0;i<arr.size();i++){
            double q = 1.0;
            string name = "";
            if(arr[i].find(';') != string::npos) {
                // q exists
                int idx = arr[i].find('='), idxsep = arr[i].find(';');
                q = stod(arr[i].substr(idx+1));
                name = arr[i].substr(0,idxsep);
            } else {
                name = arr[i];
            }
            CurStruct cs(name,q,i);
            //cout<<cs.q<<" "<<cs.name<<endl;
            ans.push_back(cs);
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
    string trimspace(string str){
        string ans = "";
        int idx = 0, n = str.size();
        while((idx<n) && (str[idx] == ' '))idx++;
        while((idx<n) && (str[idx] != ' '))ans.push_back(str[idx++]);
        return ans;
    }
};


void testmethod1() {
    LanguageProcessor lp;
    vs serverlan =   {"en-US","fr-FR"};
    auto res = lp.parse_accept_language("fr-CA ,  fr-FR", serverlan);
    for(auto it : res)cout<<it<<" ";
    cout<<endl;
}

void testmethod2() {
    LanguageProcessor lp;
    string acceptheader = "en;q=0.8, fr;q=0.9, de;q=0.7";
    vs serverlan =   {"en-US", "fr-FR", "de-DE"};
    auto res = lp.parse_accept_languagePrefix(acceptheader, serverlan);
    for(auto it : res)cout<<it<<" ";
    cout<<endl;
}

int main() {
    testmethod2();
    return 0;
}



//space?
// duplicate lan in serve lan? or accept header?
// string with , sep languages 
// \

// approach 
// create unord set of serv lan 
// irertate   + find which one exists 
// O(M + N)  //tc
// O(M) //sc
// M : accept header lan 
// N : server lan 