#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<sstream>
#include<set>

using namespace std;




class CurrencyConverter {
    public:
    CurrencyConverter(string currencies){
        string rate;
        vector<string> rates = splitHelper(currencies,',');
        for(auto it : rates){
            vector<string> rateDet = splitHelper(it,':');
            auto u = rateDet[0], v = rateDet[1], val = rateDet[2];
            g[u][v] = stod(val);
            g[v][u] = (1.0) * (1/stod(val));
        }
    }
    double getRate(string fromcur, string tocur){
        if(g.find(fromcur) == g.end()) return -1;
        if(g.find(tocur) == g.end()) return -1;
        if(g[fromcur].find(tocur) != g[fromcur].end()) return setprecision( g[fromcur][tocur],3);
        double ans = 0;
        for(auto it : g[fromcur]){
            if(g[it.first].find(tocur) != g[it.first].end()) {
                ans = max(ans,it.second * g[it.first][tocur]);
            }
        }
        return ans == 0 ? -1 : setprecision(ans,3);
    }

    double getRate2(string fromcur, string tocur){
        queue<pair<string,double>> q;
        q.push({fromcur,1.0});
        unordered_set<string> visited;
        visited.insert(fromcur);
        while(!q.empty()) {
            int sz = q.size();
            while (sz--)
            {
               auto tp = q.front();
               q.pop();
               if(tp.first == tocur) return tp.second;
               for(auto it : g[tp.first]) {
                if(visited.find(it.first) != visited.end()) continue;
                q.push({it.first,it.second * tp.second});
                visited.insert(it.first);
               }
            }
        }
        return -1;
    }
    private:

    struct amountpair {
        double dist;
        string cur;
        amountpair(double _dist, string _cur){
            dist = _dist;
            cur = _cur;
        }
        bool operator< (amountpair ap) const {
            return dist > ap.dist;
        }
    };
    unordered_map<string,unordered_map<string,double>> g;

    vector<string> splitHelper(string s, char sep) {
        stringstream ss(s);
        string tmp = "";
        vector<string> ans;
        while(getline(ss,tmp,sep)){
            ans.push_back(tmp);
        }
        return ans;
    }

    double setprecision(double d, int pre){
        double mult = pow(10,pre);
        return round(d*mult)/mult;
    }
};

void testmethod3() {
    string rates = "USD:EUR:0.85,EUR:GBP:0.88,GBP:JPY:150,JPY:AUD:0.012";
    CurrencyConverter cc(rates);
    cout<<cc.getRate2("USD", "AUD")<<endl;
    cout<<cc.getRate2("AUD", "USD")<<endl;
}

void testmethod2() {
    string rates = "USD:EUR:0.85,USD:GBP:0.75,EUR:GBP:0.88,GBP:CAD:1.7,EUR:CAD:1.45";
    CurrencyConverter cc(rates);
    cout<<cc.getRate("USD", "CAD")<<endl;
}

void testmethod1() {
    string rates = "USD:EUR:0.85,EUR:GBP:0.88,USD:JPY:110";
    CurrencyConverter cc(rates);
    cout<<cc.getRate("USD", "GBP")<<endl;
    cout<<cc.getRate("GBP", "JPY")<<endl;
}
int main() {
    testmethod3();
    return 0;
}




// A->B
// B->A
// if not exist? none or -1
// input as?string
// can there be conflicting rates?no
// duplicate rates?
// precision of decimal ?

// parse + create graph 
// unordered_map<string,unordered_map<string,double>> 

// O(N)/O(N)
// N : no of rates given
