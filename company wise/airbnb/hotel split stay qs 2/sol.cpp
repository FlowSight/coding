#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii; // {cost, switches}

const int INF = 1e9;
unordered_map<string, pii> memo; // "day,idx" -> {min_cost, min_switches}

// returns {min_cost, min_switches} to cover [day..end] using listings[idx..N-1]
pii helper(int day, int end, int idx, int size, vvi& availability){
    int N = availability.size();
    if(day > end) return {0, 0};
    if(idx >= N || availability[idx][1] > day) return {INF, INF};

    string key = to_string(day) + "," + to_string(idx);
    if(memo.count(key)) return memo[key];

    pii best = {INF, INF};

    // try every listing from idx onward that can cover 'day'
    for(int i = idx; i < N && availability[i][1] <= day; i++){
        // skip if listing ends before current day or can't fit party
        if(availability[i][2] < day || availability[i][3] < size) continue;

        int maxday = min(end, availability[i][2]);
        for(int last = day; last <= maxday; last++){
            int nights = last - day + 1;
            int cost = nights * availability[i][4];
            pii sub = helper(last + 1, end, i + 1, size, availability);
            if(sub.first >= INF) continue;
            int totcost = cost + sub.first;
            int totsw   = 1 + sub.second;
            if(totcost < best.first || (totcost == best.first && totsw < best.second))
                best = {totcost, totsw};
        }
    }

    return memo[key] = best;
}

// availability : {id,st,end,size,cost}
int hotelsplitstay(int st, int end, int size, vvi availability ){
    sort(availability.begin(),availability.end(),[](const vi& av1, const vi& av2) {
        return av1[1] == av2[1] ? av1[2]< av2[2] : av1[1] < av2[1];
    });
    memo.clear();
    pii res = helper(st, end, 0, size, availability);
    return res.first >= INF ? -1 : res.first;
}



void testmethod(){
    vvi availability = {
        {1,0,7,4,10},
        {2,5,8,2,5},
        {3,8,10,3,4},
        {4,1,10,1,2}
    };
    cout<<hotelsplitstay(0,9,2,availability)<<endl;
}


int main(){
    testmethod();
    return 0;
}