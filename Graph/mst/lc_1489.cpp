class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // get mst weight first
        // for each edge:
            // 1. form mst without this edge.
            //     a. if the its not mst, then its critical edge
            //     b. if its mst : could be pce or not. but definitely not ce.
            // 4. force add it to mst, then form mst
            //     a. if mst is valid and same as ex 
    }
};