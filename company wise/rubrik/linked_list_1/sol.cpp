
#include<iostream>
#include<thread>
#include<algorithm>
#include<functional>
#include<queue>
#include<mutex>
#include<shared_mutex>
#include<semaphore>
#include<future>
#include<condition_variable>

using namespace std;

struct DLL {
    public:
    DLL() = default;
    DLL(int _key , int _val){
        key = _key;
        val = _val;
        prev = nullptr;
        next = nullptr;
    }
    int val,key;
    DLL* prev;
    DLL* next;

};

class LLCrud {
    public:

    explicit LLCrud(int _numIn, int _numSe, int _numDel){
        numSer = _numSe;
        numDel = _numDel;
        numIn = _numIn;
        dummy = new DLL(-1,-1);
        last = dummy;
        for(auto i=0;i<numSer;i++)searchers.emplace_back(&LLCrud::searchWorker,this);
        for(auto i=0;i<numIn;i++)inserters.emplace_back(&LLCrud::insertWorker,this);
        for(auto i=0;i<numDel;i++)deleters.emplace_back(&LLCrud::deleteWorker ,this);
    }

    void insert(int key, int val){
        unique_lock<mutex> sl(mtxinser);
        inserQ.push({key,val});
        cvInser.notify_all();
    }

    void search(int num){
        unique_lock<mutex> ul(mtxSer);
        searchQ.push(num);
        cvSer.notify_all();
    }

    void deleteNum(int num){
        unique_lock<shared_mutex> ul(mtxLL);
        deleteQ.push(num);
        cvDel.notify_all();
    }

    void shutdown(){
        stopped = true;
        cvSer.notify_all();
        cvInser.notify_all();
        cvDel.notify_all();
        for(auto &th : inserters){
            if(th.joinable()) th.join();
        }
        for(auto &th : searchers){
            if(th.joinable()) th.join();
        }
        for(auto &th : deleters){
            if(th.joinable()) th.join();
        }
    }

    private:
    int numIn, numDel, numSer;
    vector<thread> searchers,inserters, deleters;
    shared_mutex mtxLL;
    mutex mtxSer, mtxinser;
    DLL* last;
    DLL* dummy;
    queue<int> deleteQ, searchQ;
    queue<pair<int,int>> inserQ;
    //queue<promise<int>> searchQ;
    condition_variable_any cvSer,cvInser,cvDel;
    binary_semaphore bs{1};
    atomic<int> stopped{0};

    void searchWorker(){
        int serKey  = -1;
        while(true){
            shared_lock<shared_mutex> ul(mtxLL);
            cvSer.wait(ul,[this]{
                return stopped || !searchQ.empty();
            });
            if(stopped) return;
            {
             unique_lock<mutex> ul(mtxSer);
             serKey = searchQ.front();
             searchQ.pop();
            }
            auto node = dummy->next;
            while(node && (node->key != serKey)) node = node->next;
            if(node) {
                cout<<"found node with key "<<serKey<<" with val: "<<node->val<<endl;
            } else {
                cout<<"failed to search : "<<serKey<<endl;
            }
        }
    }
    void insertWorker(){
        pair<int,int> inserKey;
        while(true){
            bs.acquire();
            {
                shared_lock<shared_mutex> ul(mtxLL);
                cvInser.wait(ul,[this]{
                    return stopped || !inserQ.empty();
                });
                if(stopped) return;

                {
                    unique_lock<mutex> ul(mtxinser);
                    inserKey = inserQ.front();
                    inserQ.pop();
                }
                last->next = new DLL(inserKey.first,inserKey.second);
                last->next->prev = last;
                last = last->next;
                cout<<"inserted : "<<inserKey.first<<" with val : "<<inserKey.second<<endl;
            }   
            bs.release();
        }
    }

    void deleteWorker(){
        while(true){
            unique_lock<shared_mutex> ul(mtxLL);
            cvDel.wait(ul,[this]{
                return stopped || !deleteQ.empty() ;
            });
            if(stopped) return;
            auto delKey = deleteQ.front();
            deleteQ.pop();
            auto node = dummy->next;
            while(node && (node->key != delKey)) node = node->next;
            if(node) {
                auto prev = node->prev;
                auto next = node->next;
                prev->next = next;
                if(next) next->prev = prev;
                if(node == last) last = prev;
                delete node;
                cout<<"deleted "<<delKey<<endl;
            } else {
                cout<<"failed to delete : "<<delKey<<endl;
            }
        }
    }

};


void testmethod1(){
    LLCrud llcrud(2,2,2);
    for(auto i=0;i<10;i++)llcrud.insert(i,2*i);
    this_thread::sleep_for(chrono::milliseconds(500));
    for(auto i=0;i<10;i++)llcrud.deleteNum(i/2);
    this_thread::sleep_for(chrono::milliseconds(500));
    for(auto i=0;i<10;i++)llcrud.search(i);
    this_thread::sleep_for(chrono::milliseconds(300));
    llcrud.shutdown();
}

int main(){
    testmethod1();
    return 0;
}
