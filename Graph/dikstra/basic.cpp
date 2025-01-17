// the main crunch of dikjstra is, one node may have been put into queue multiple times with same of different values (from multiple nodes)
// but, when its popped for the first time, further it should not be considered
// crunches : 
// 1. mark visited inside loop, 
// 2. can keep a dist var to track distances calculated for nodes so far which are also NOT marked visited like below:
//     if(dist[v] > new_dist){
//         pq.push({new_dist,it.first});
//     }
//     But it will still not guarantee same node with will not be present twice in heap
// 3. Only way to guarantee same node will not be present twice is, updating the value of the node in heap. Need SET for this.
// Two critical steps :
// 1. Visited
//     Is the final state, means its at the top of heap. After this, that node can not be visited again, this is mathematically provabale.
// 2. reached
//     Can be reached multiple times, inside loop of loop. When reached, have to check the min dist we reached it with,
//     if new_dist is less than that, then only push it to heap and update min dist reached with.
//     If never reached, just push


// example : 


//1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vector<vector<pair<int,int>>> g;

    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        int ans = -1, ansCnt = n;
        g = vector<vector<pair<int,int>>>(n);
        for(auto& it : edges){
            auto u = it[0], v = it[1], w = it[2];
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        }
        for(auto i=0;i<n;i++){
            auto cur = findCityInThresholdDist(i,distanceThreshold,n);
            if(cur<=ansCnt){
                ansCnt = cur;
                ans = i;
            }
        }
        return ans;
    }

    int findCityInThresholdDist(int idx, int dist, int n){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
        pq.push({0,idx}); //dist, idx
        
        vi visited(n,-1);
        int cnt = 0;
        while(!pq.empty()){
            auto [cur_dist,u] = pq.top();
            pq.pop();
            
            if(cur_dist > dist)break;
            if(visited[u] != -1)continue;
            
            cnt++;
            visited[u] = cur_dist;

            for(auto it : g[u]){
                if(visited[it.first] != -1)continue;
                int new_dist = cur_dist+it.second;
                pq.push({new_dist,it.first});
            }
        }
        return cnt;
    }
        int findCityInThresholdDistWithSet(int idx, int dist, int n){
        set<pair<int,int>> ss;
        vi visited(n,-1);

        ss.insert({0,idx}); //dist, idx
        visited[idx] = 0;
        int cnt = 0;
        
        while(!ss.empty()){
            auto [cur_dist,u] = *(ss.begin());
            ss.erase(ss.begin());
            
            if(cur_dist > dist)break;
            cnt++;

            for(auto it : g[u]){
                int newDist = cur_dist+it.second, newV = it.first;
                if(visited[newV] != -1 && visited[newV] < newDist)continue;
                if(newDist < visited[newV]) {
                    ss.erase(ss.find({visited[newV],newV}));
                }
                visited[newV] = newDist;
                ss.insert({newDist,newV});

            }
        }
        return cnt;
    }
};


//cant work if negative edge is present in cycle