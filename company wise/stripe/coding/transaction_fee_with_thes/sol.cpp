
#include<iostream>
#include<sstream>

using namespace std;

typedef vector<string> vs;

class FeeCalculator {
    public:
    FeeCalculator() = default;
    void getfees(vector<string> transactions) {
        for(auto it : transactions){
            auto parseddata = parsehelper(it,' ');
            string merch = parseddata[0], provider = parseddata[1];
            int amount = stoi(parseddata[2]);
            cout<<getfee(merch,provider,amount)<<endl;
            totalamountmap[merch][provider] += amount;
        }
    }
    private:
    vs parsehelper(string str, char del){
        vs ans;
        stringstream ss(str);
        string cur = "";
        while(getline(ss,cur,del)){
            ans.push_back(cur);
        }
        //cout<<ans.size();
        return ans;
    }
    int getfee(string merch, string pro, int amount){
        if(totalamountmap.find(merch) == totalamountmap.end()) return amount*0.02;
        if(totalamountmap[merch].find(pro) == totalamountmap[merch].end()) return amount*0.02;
        if(totalamountmap[merch][pro] <10000) return amount*0.02;
        return 0;
    }
    unordered_map<string,unordered_map<string,int>> totalamountmap;
};

void testmethod1(){
    FeeCalculator fc;
    vs arr = {
       "m1 p1 6000",
        "m1 p1 5000",
        "m1 p1 100",
        "m1 p2 20000",
        "m1 p2 1",
        "m2 p1 20000"
    };
    fc.getfees(arr);
}

int main(){
    testmethod1();
}

// merchant_id
// provider_id 
// amount 

// valid format?yes


// parse , fetch details
// map [key :merchent] {
//         key : provider, val : total amount
// }

// O(n) tc 
// O(n) sc 

