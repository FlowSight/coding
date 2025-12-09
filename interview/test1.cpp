#include<iostream>
#include<vector>
#include<climits>
#include<chrono>

using namespace std;

// Given a list of servers, each server has a cost associated with it. The servers are represented as an array of N integers.
// If you choose server i, then i servers ahead of it are automatically selected.
// You may skip selecting those servers, but sometimes it might be beneficial to select them as well.
// Find the min cost to cover all servers.

void test(){
    for(auto i=0;i<20;i++){
        auto now = chrono::system_clock::now();
        auto msTS = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());
        cout<<msTS.count()<<endl;
    }

}

int main () {
    test();
    return 0;
}