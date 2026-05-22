/// Severity: Sev1
// Date: 17May26
// LC: 502
// Where I failed: implemetation took time
// Pattern: greedy 2d, sort by one dimen, then pq by another dimen
// Notes: sev0..sev0..



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vvi arr; // {cap,prof}
        int n = profits.size(), idx = 0, taken = 0;
        priority_queue<pair<int,int>> pq; // {prof,cap used}
        for(auto i=0;i<n;i++){
            arr.push_back({capital[i],profits[i]});
        }
        sort(arr.begin(),arr.end());
        while(k--) {
            while((idx<n) && (arr[idx][0] <= w) ) {
                pq.push({arr[idx][1],arr[idx][0]});
                idx++;
            }
            if(pq.empty()) break;
            auto pick = pq.top();
            pq.pop();
            w = (w+pick.first);
        }
        return w;
    }
};


class Project{
    public:
    int profit, capital;
    Project(int _profit, int _capital){
        profit = _profit;
        capital = _capital;
    }

    bool operator< (const Project& p1) const {
        return this->profit >= p1.profit;
        // already sorted by capital..so if == is not put here..it will mean equal elements will be randomly ordered..
        // lets say k1>k2 and k1==k3 so..k1->k2 and k1->k3 and k3->k2..
    }
};

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vvi pv;
        int idx = 0, n = profits.size();
        for(auto i=0;i<n;i++)pv.push_back({profits[i],capital[i]});
        sort(pv.begin(),pv.end(),[](const vi& v1, const vi& v2){
            return v1[1]<v2[1];
        });
        set<Project> ss;
        while(k){
            while(idx<n && pv[idx][1]<=w){
                ss.insert(Project(pv[idx][0],pv[idx][1]));
                idx++;
            }
            if(ss.empty())break;
            auto it = *(ss.begin());
            w+=it.profit;
            ss.erase(ss.begin());
            k--;
        }
        return w;
    }
};