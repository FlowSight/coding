14 june 2025
could not do..sev0


//greedy and bs 
// idea is bs way to check can we finish k tasks
// for this above task, choose k easiest tasks and k strongest workers
// match strongest worker to toughest task, if not possible, reduce toughest task by pill strength and find which worker
// can finish it now.

class Solution {
public:
    multiset<int> ss;
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int n = tasks.size(), m = workers.size(), l = 0, r = min(m,n),mid = -1;
        while(l<r){
            if(l+1 == r){
                if(test(tasks,workers,r,pills,strength)) return r;
                return test(tasks,workers,l,pills,strength) ? l : 0;
            }
            mid = (l+r)/2;
            if(test(tasks,workers,mid,pills,strength)) l = mid;
            else r = mid-1;
        }
        return l;
    }

    bool test(vector<int>& tasks, vector<int>& workers,int& cnt, int pills, int& strength){
        ss.clear();
        int n = workers.size();
        for(auto i=n-1;i>n-1-cnt;i--) ss.insert(workers[i]);
        for(auto i=cnt-1;i>=0;i--){
            auto reqStrength = tasks[i];
            auto it = ss.lower_bound(reqStrength);
            if( it == ss.end()){
                if(pills == 0) return false;
                // there is no worker who can directly do it
                reqStrength -= strength;
                it = ss.lower_bound(reqStrength);
                if( it == ss.end()) return false;
                pills--;
            }
            ss.erase(it);
        }
        return true;
    }
};

