#include<iostream>

using namespace std;


struct Transaction
{
    string account_id;
    int amount;
    Transaction(string _acc, int _am){
        account_id = _acc;
        amount = _am;
    }
};

class AccBalManager {
    public:
    AccBalManager() = default;
    void get_account_balances(vector<Transaction>& trans){
        for(auto it : trans){
            balmap[it.account_id] += it.amount;
        }
        for(auto it : balmap){
            if(it.second >0) cout<<it.first<<" : "<<it.second<<endl;
        }
    }

    void process_transactions(vector<Transaction>& trans){
        vector<Transaction> rejected;
        for(auto it : trans){
            if(balmap.find(it.account_id) == balmap.end()) balmap[it.account_id] = 0;
            if(balmap[it.account_id] + it.amount < 0){
                rejected.push_back(it);
                continue;
            }
            balmap[it.account_id] += it.amount;
        }
        for(auto it : balmap){
            if(it.second >0) cout<<it.first<<" : "<<it.second<<endl;
        }
        cout<<"===rejected transactions====="<<endl;
        for(auto it : rejected){
            cout<<"Account Id: "<<it.account_id<<" , amount : "<<it.amount<<endl;
        }
    }

    void process_with_coverage(vector<Transaction>& trans, string platform_acc_id){
        int ans = 0;
        for(auto it : trans){
            if(balmap.find(it.account_id) == balmap.end()) balmap[it.account_id] = 0;
            balmap[it.account_id] += it.amount;
            if(balmap[it.account_id] < 0){
                int loan = abs(balmap[it.account_id]);
                ans += loan;
                balmap[platform_acc_id] -= loan;
                balmap[it.account_id] = 0;
            } 
            
        }
        cout<<ans<<endl;
    }

    unordered_map<string,int> balmap;
};

// what if platform runs out?
// if platform is debited?

void testmethod1() {
    vector<Transaction> arr = {
        Transaction("account_A",100),
        Transaction("account_B",50),
         Transaction("account_A", -30),
        Transaction("account_C", 200),
        Transaction("account_B",-50),
    };
    AccBalManager abm;
    abm.get_account_balances(arr);
}

void testmethod2() {
    vector<Transaction> arr = {
        Transaction("account_A",100),
        Transaction("account_A",-150),
         Transaction("account_B", 50),
        Transaction("account_A", -80),
        Transaction("account_B",-100),
    };
    AccBalManager abm;
    abm.process_transactions(arr);
}

void testmethod3() {
    vector<Transaction> arr = {
        Transaction("platform",1000),
        Transaction("account_A",100),
        Transaction("account_A",-150),
         Transaction("account_B", 50),
        Transaction("account_B",-100),
        Transaction("account_A", -30),
    };
    AccBalManager abm;
    abm.process_with_coverage(arr,"platform");
}

int main(){
    testmethod3();
    return 0;
}

// starting amunt? 
// order of ret? any
// have map 
// iterate :
//     parse
//     maintain sum
// iterate map : get all >0

