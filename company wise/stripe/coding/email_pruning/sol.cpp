#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<sstream>
#include<set>

using namespace std;

typedef vector<string> vs;
typedef vector<char> vc;
class EmailValidator {
    public:
    EmailValidator() = default;

    bool validate(string email){
        auto local = getLocal(email), domain = getDomain(email);
        return isValidLocal(local) && isValidDomain(domain);
    }

    string canonize(string email){
        auto local = getLocal(email), domain = getDomain(email);
        return canonizeLocal(local) + "@" + canonizeDomain(domain);
    }

    string getLocal(string email){
        string local = "";
        auto idx = email.find('@');
        if(idx == string::npos) return local;
        local = email.substr(0,idx);
        return local;
    }
    private:
        string getDomain(string email){
        string domain = "";
        auto idx = email.find('@');
        if(idx == string::npos) return domain;
        domain = email.substr(idx+1);
        return domain;
    }
    bool isValidLocal(string local){
        if(local.empty()) return false;
        int n = local.size();
        for(auto i=0;i<n;i++){
            if(local[i] == '@') return false;
        }
        return true;
    }
    bool isValidDomain(string domain){
        if(domain.empty()) return false;
        int n = domain.size(), dot = false;
        for(auto i=0;i<n;i++){
            if(domain[i] == '@') return false;
            if(domain[i] == '.') {
                dot = true;
                if((i==0) || (i==n-1)) return false;
            }
        }
        return dot;
    }
    string canonizeLocal(string local){
        string ans = "";
        for(auto c : local){
            if((c>='A') && (c<='Z')) ans.push_back(c-'A'+'a');
            else if(c=='+') break;
            else if(c=='.') continue;
            else ans.push_back(c);
        }
        return ans;
    }
    string canonizeDomain(string domain){
        string ans = "";
        for(auto c : domain){
            if((c>='A') && (c<='Z')) ans.push_back(c-'A'+'a');
            else ans.push_back(c);
        }
        return ans;
    }

};  

void testmethod() {
    EmailValidator ev;
    cout<<ev.canonize("John.Smith+promo@Gmail.com")<<endl;
}
int main() {
    testmethod();
    return 0;
}



// 1 @ 
// local, domain both not empty 
// domain at least 1 ., not first or last 
// traverse
// O(n)/O(1)