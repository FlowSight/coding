#include<iostream>
#include<algorithm>
#include<ctime>

using namespace std;

typedef vector<int>  vi;
vector<int> getnextdate(vi date){
    vi ans = date;
    ans[2]++;
    if((ans[1]==2) && (ans[2] == 29)) {
        ans[2] = 0;
        ans[1]++;
    } else if((ans[2] == 31) && 
            ((ans[1] == 4) || (ans[1] == 6) || (ans[1] == 9) || (ans[1] = 11))){
            ans[2] = 0;
            ans[1]++;
    } else if(ans[2] == 32) {
            ans[2] = 0;
            ans[1]++;
    }
    if(ans[1] == 13) {
        ans[1] = 1;
        ans[0]++;
    }
    ans[3] = ans[4] = ans[5] = 0;
    return ans;
}

void incr(int& starthr, int& startmin){
    startmin += 30;
    if(startmin == 60){
        startmin = 0;
        starthr++;
    }
}

bool earlier(int starthr,int startmin, int endhr, int endmin){
    if(starthr != endhr) return starthr < endhr;
    return
}

void getslots(vi startdate, vi enddate, int sthr, int endhr){
    if(startdate[0] != enddate[0]) return;
    if(startdate[1] != enddate[1]) return;
    if(startdate[2] != enddate[2]) return;
    int starthr = max(sthr,startdate[3]), startmin = (sthr >= startdate[3] ? 0 : startdate[4]);
    if(startmin >30) {
        starthr++;
        startmin = 0;
    } else if (startmin >0) {
        startmin = 30;
    }
    while(earlier(starthr,startmin,endhr)){
        cout<<starthr<<" "<<startmin<<endl;
        incr(starthr, startmin);
    }
}
bool samedate(vi date1, vi date2){
    return (date1[0] == date2[0]) &&  (date1[1] == date2[1]) &&  (date1[2] == date2[2]);
}

void testmethod(){
    vector<int> startdate = {2025,4,17,0,0,0},
        enddate = {2025,4,23,10,59,0};
    for(auto date = startdate;date<=enddate;date = getnextdate(date)){
        vi end = date;
        if(samedate(end,enddate)) end = enddate;
        else {
            end[3] = 23, end[4] = 59, end[5] = 59;
        }
        getslots(date,end,9,11);
    }
    
}

int main(){
    testmethod();
    return 1;
}