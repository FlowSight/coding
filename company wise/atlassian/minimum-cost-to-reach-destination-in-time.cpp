// sev0..14nov25
// didnt get the other case..and the fact that time has to be kept track of too.
// crunch : Note: The reason for including extra condition which is allowing to
 //traverse edges which cause the time to reduce is that it is possible that 
 //hese edges led us to destination. However if we just traverse those edge 
 // causing cost to decrease then we are ignoring the time which can lead us to 
 // a non-optimal answer or even a case where time exceed the maxTime leading us 
 // to return -1.

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        priority_queue<vi,vvi,greater<vi>> pq;
        int n = passingFees.size();
        vvi g(n,vi(n,-1));
        vi minCost(n,INT_MAX), minTime(n,INT_MAX);
        minCost[0] = passingFees[0];
        minTime[0] = 0;
        pq.push({passingFees[0],0,0});
        for(auto it : edges){
            auto u = it[0], v = it[1], time = it[2];
            g[u][v] = g[v][u] = (g[u][v] == -1 ? time : min(g[u][v],time));
        }

        while(!pq.empty()){
            auto tp = pq.top();
            pq.pop();
            auto cost = tp[0], time = tp[1], v = tp[2];
            for(auto i=0;i<n;i++){
                if(g[v][i] == -1) continue;
                int newcost = cost + passingFees[i], newtime = time + g[v][i];
                if(newtime > maxTime) continue;
                if(newcost < minCost[i]) {
                    minCost[i] = newcost;
                    minTime[i] = newtime;
                    pq.push({newcost,newtime,i});
                }
                else if(newtime < minTime[i]) {
                    minTime[i] = newtime;
                    pq.push({newcost,newtime,i});
                }
 
            }
        }
        return minCost[n-1] == INT_MAX ? -1 :minCost[n-1];
    }
};

// {cost,time,idx}
// 0 2 4 3 IM
// {4,1,2}
// {3,10,3}
// {4,4,3}
// {4,4,3}

