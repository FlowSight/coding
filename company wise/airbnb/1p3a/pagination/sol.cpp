#include<bits/stdc++.h>

using namespace std;


struct  ListNode
{
   string hostid;
   int idx;
   ListNode* next;
   ListNode(string _hostid, int _idx){
    hostid = _hostid;
    idx = _idx;
    next = nullptr;
   }
};


typedef vector<string> vs;
typedef vector<vs> vvs;
set<pair<int,ListNode*>> ss;
unordered_map<string,ListNode*> mm;
unordered_map<string,ListNode*> tailmm;
vvs listings;


vvs getdedupentries(int pagesize){
    unordered_set<string> seen;
    vvs ans;
    while((ans.size() < pagesize) && (!ss.empty())){
        auto tp = *(ss.begin());
        auto hostid = tp.second->hostid;
        mm[hostid] = mm[hostid]->next;
        seen.insert(hostid);
        ss.erase(ss.begin());
        ans.push_back(listings[tp.first]);
    }
    for(auto it: seen){
        
        if(mm[it]){
            ss.insert({mm[it]->idx,mm[it]});
        } 
    }
    return ans;
}

vvs getdeduporderedentries(int pagesize){
    vvs ans = getdedupentries(pagesize);
    while((ans.size() < pagesize) && (!ss.empty())){
        auto tp = *(ss.begin());
        auto hostid = tp.second->hostid;
        mm[hostid] = mm[hostid]->next;
        ss.erase(ss.begin());
        ans.push_back(listings[tp.first]);
        if(mm[hostid]) ss.insert({mm[hostid]->idx,mm[hostid]});
    }
    return ans;
}

vvs getpagerank(vvs& arr, int pagesize){
    listings = arr;
    int n = listings.size();
    vvs ans;
    vvs res;

    for(auto i=0;i<n;i++){
        if(mm.find(listings[i][0]) == mm.end()){
            mm[listings[i][0]] = new ListNode(listings[i][0],i);
            tailmm[listings[i][0]] = mm[listings[i][0]];
            ss.insert({i,mm[listings[i][0]]});
        } else {
            tailmm[listings[i][0]]->next = new ListNode(listings[i][0],i);
            tailmm[listings[i][0]] = tailmm[listings[i][0]]->next;
        }
    }
    while(!ss.empty()){
        if(ss.size() >= pagesize){
             res = getdedupentries(pagesize);
        } else {
            res = getdeduporderedentries(pagesize);
        }
       for(auto it : res) ans.push_back(it);
    }
    return ans;
}



int main(){
    vvs listings = {
        {"1","28","310.6","SF"},
        {"4","5","204.1","SF"},
        {"20","7","203.2","Oakland"},
        {"6","8","202.2","SF"},
        {"6","10","199.1","SF"},
        {"1","16","190.4","SF"},
        {"6","29","185.2","SF"},
        {"7","20","180.1","SF"},
        {"6","21","162.1","SF"},
        {"2","18","161.2","SF"},
        {"2","30","149.1","SF"},
        {"3","76","146.2","SF"},
        {"2","14","141.1","San Jose"}
    };
    auto res = getpagerank(listings,5);
    for(auto it : res){
        for(auto it1 : it)cout<<it1<<" ";
        cout<<endl;
    }
    return 0;
}








// (101)-> (1,3,5)
// (102)-> (2,4,6)
// (103)-> (7)
// (104)-> (8,9,10)
// (105)-> (11,12,13,14)

// heap = {104->(10),105->(12,13,14)}
// done = {}

// set = {}
// cur = 


// ans = {{101,102,103,104,105}{101,102,101,102,104}}