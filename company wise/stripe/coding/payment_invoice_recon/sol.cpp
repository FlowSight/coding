#include<iostream>
#include<sstream>
#include<unordered_map>
#include<set>
#include<nlohmann/json.hpp>

using namespace std;

typedef vector<string> vs;
struct Invoice {
    public:
    string id, date, amount;
    Invoice() = default;
    Invoice(vs arr){
        id = arr[0];
        date = arr[1];
        amount = arr[2];
    }

    bool operator< (Invoice iv) const {
        if(amount == iv.amount) return date < iv.date;
        return amount < iv.amount;
    }
};


class PaymentManager {
    public:
    PaymentManager() = default;
    void reconcile_payment(string& payment, vs& invoices, int _margin) {
        auto payarr = parsehelper(payment,',');
        int amount = stoi(payarr[1]);
        margin = _margin;

        for(auto it : invoices){
            Invoice iv(parsehelper(it,','));
            mm[iv.id] = iv;
            amountmap[stoi(iv.amount)].insert(iv);
        }

        string id = "";
        maybegetid(payarr[2],id);
        if(!id.empty() && (mm.find(id) != mm.end())) {
            auto iv = mm[id];
            cout<< "Payment " <<payarr[0]<<" paid "<< payarr[1]<< " for invoice" <<  id <<" due on "<<iv.date <<endl;
        } else {
            if(amountmap.find(amount) != amountmap.end()) {
                auto iv = *(amountmap[amount].begin());
                cout<< "Payment " <<payarr[0]<<" paid "<< amount<< " for invoice" <<  iv.id <<" due on "<<iv.date <<endl;
            } else {
                auto iv = fuzzyfound(amount);
                if(!iv.id.empty()){
                    cout<< "Payment " <<payarr[0]<<" paid "<< amount<< " for invoice " <<  iv.id <<" due on "<<iv.date <<endl;
                } else {
                    cout<< "Payment " <<payarr[0]<<" could not be matched to any invoice"<<endl;
                }
            }
        }
    }
    private:
        unordered_map<string,Invoice> mm;
        unordered_map<int,set<Invoice>> amountmap;
        int margin;
    
    Invoice fuzzyfound(int amount) {
        Invoice id({"","9999-99-99","99999999"});
        for(auto it : amountmap) {
            if(abs(it.first - amount) <= margin) {
                auto cand = *(it.second.begin());
                if(id.date > cand.date) id = cand;
            }
        }
        return id;
    }
    vs parsehelper(string str, char sep){
        vs ans;
        stringstream ss(str);
        string val = "";
        while(getline(ss,val,sep)){
            ans.push_back(trimspace(val));
        }
        return ans;
    }
    string trimspace(string str){
        string ans = "";
        int idx = 0, n = str.size();
        while((idx<n) && (str[idx] == ' '))idx++;
        while((idx<n))ans.push_back(str[idx++]);
        return ans;
    }
    void maybegetid(string note, string& id){
        if(note.find(':') == string::npos) return;
        int idx = note.find(':');
        id = trimspace(note.substr(idx+1));
    }
};


void testmethod(){
    string payment =  "payment-003, 98, Customer payment";
    int margin = 5;
    vs invoices = {
    "inv-100, 2024-03-15, 100",
    "inv-200, 2024-02-20, 98",
    "inv-300, 2024-01-10, 102"
    };
    PaymentManager pm;
    pm.reconcile_payment(payment, invoices,margin);
}

int main(){
    testmethod();
    return 0;
}

// payment : a single string of text  : "payment-id, amount, memo"
// invoices : vector of strings : "invoice-id, due-date, amount",

// format always valid?yes
// format always valid for invoices ?yes
// amount : int 
// memo in no other format?
// payment id is case sensive?

// algo:
// 1. find payment id from memo 
// 2. map of inv id to invoice
// 3. for each payment, find in map, if/else

// O(P + I) //tc
// O(I) //sc