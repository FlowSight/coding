#include<iostream>
#include<unordered_map>

using namespace std;

struct Transaction
{
    public:
    string account_id;
    long amount;
    Transaction(string _account_id, long _amount){
        amount = _amount;
        account_id = _account_id;
    }
};


struct ReturnType2{
    public:
        vector<pair<string,long>> ans;
        vector<Transaction> rejected;
        ReturnType2(vector<pair<string,long>> _arr, vector<Transaction> _rejected){
            ans = _arr;
            rejected = _rejected;
        }
};

struct ReturnType3{
    public:
        vector<pair<string,long>> ans;
        long totalAmount;
        ReturnType3(vector<pair<string,long>> _arr, long _totalAmount){
            ans = _arr;
            totalAmount = _totalAmount;
        }
};

class AccountBalanceManager {
    public:
    unordered_map<string,long> mm;
    AccountBalanceManager() {}

    vector<pair<string,long>> get_account_balances(vector<Transaction> trans){
        vector<pair<string,long>> ans;
        for(auto& it : trans){
            mm[it.account_id] += it.amount;
        }
        for(auto it : mm){
            if(it.second >0) ans.push_back({it.first,it.second});
        }
        return ans;
    }


    ReturnType2 get_account_balances_with_overdraft_check(vector<Transaction> trans){
        vector<pair<string,long>> ans;
        vector<Transaction> rejected;
        for(auto& it : trans){
            if(mm[it.account_id] + it.amount < 0) {
                rejected.push_back(it);
                continue;
            }
            mm[it.account_id] += it.amount;
        }
        for(auto it : mm){
            if(it.second >0) ans.push_back({it.first,it.second});
        }
        return ReturnType2{ans,rejected};
    }

    long get_account_balances_with_bank_intervention(vector<Transaction> trans){
        vector<pair<string,long>> ans;
        long bankLend = 0;
        for(auto& it : trans){
            mm[it.account_id] += it.amount;
            if(mm[it.account_id] < 0) {
                bankLend += abs(mm[it.account_id]);
                mm[it.account_id] = 0;
            }
        }
        for(auto it : mm){
            if(it.second >0) ans.push_back({it.first,it.second});
        }
        return bankLend;
    }
};

void testPart1(){
    vector<Transaction> trans;
    trans.push_back(Transaction("account_A",100));
    trans.push_back(Transaction("account_B",50));
    trans.push_back(Transaction("account_A",-30));
    trans.push_back(Transaction("account_C",200));
    trans.push_back(Transaction("account_B",-50));

    AccountBalanceManager abm;
    auto res = abm.get_account_balances(trans);
    for(auto it :res){
        cout<<it.first<< ": "<<it.second<<endl;
    }
}

void testPart2(){
    vector<Transaction> trans;
    trans.push_back(Transaction("account_A",100));
    trans.push_back(Transaction("account_A",-150));
    trans.push_back(Transaction("account_B",50));
    trans.push_back(Transaction("account_A",-80));
    trans.push_back(Transaction("account_B",-100));

    AccountBalanceManager abm;
    auto res = abm.get_account_balances_with_overdraft_check(trans);
    for(auto it :res.ans){
        cout<<it.first<< ": "<<it.second<<endl;
    }
    for(auto it :res.rejected){
        cout<<"account_id : "<<it.account_id << ", amount: "<<it.amount<<endl;
    }
}

void testPart3(){
    vector<Transaction> trans;
    trans.push_back(Transaction("platform",1000));
    trans.push_back(Transaction("account_A",100));
    trans.push_back(Transaction("account_A",-150));
    trans.push_back(Transaction("account_B",50));
    trans.push_back(Transaction("account_B",-100));
    trans.push_back(Transaction("account_A",-30));

    AccountBalanceManager abm;
    auto res = abm.get_account_balances_with_bank_intervention(trans);
    cout<<res<<endl;
}
int main(){
    testPart3();
    return 0;
}


/* -- input:
vector of transactions 
{account id, amount, }
amount int? yes
amount :+-

total for each acc, only for +bal 
order? */