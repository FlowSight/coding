#include<bits/stdc++.h>

using namespace std;

typedef vector<string> vs;
typedef vector<vs> vvs;
struct Node {
    public:
    int hostid,idx;
    Node* next;
    Node(int _hostid, int _idx){
        hostid = _hostid;
        idx = _idx;
        next = nullptr;
    }
};
unordered_map<int,Node*> mm;


vvs getpagerank(vvs& arr, int pagesize){
    int n = arr.size();
    for(auto i=0;i<n;i++){
        auto node = new Node(stoi(arr[i][0]),i);
        if(mm.find(node->hostid) == mm.end()){
            mm[node->hostid] = node;
        } else {
            mm[node->hostid]->next = node;
        }
        if(mm.size() >= pagesize){

        }
    }
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