// 26 feb 25
//  did in 11 mins.
//  didnt consider corner case in add...
//  sev1

class UnionFind {
        int n,sz;
        vector<int> par,rank;
    public:
        UnionFind(int _n){
            n = _n;
            sz = n;
            par = vector<int>(n,-1);
            rank = vector<int>(n,1);
        }
        int find(int v) {
            return par[v] == -1 ? v :  find(par[v]);
        }

        void add(int u, int v){
            auto parX = find(u), parY = find(v);
            if(parX == parY) return;
            auto rankX = rank[parX], rankY = rank[parY];
            if(rankX == rankY) {
                rank[parY]++;
                par[parX] = parY;
            } else if(rankX > rankY) {
                par[parY] = parX;
            } else  {
                par[parX] = parY;
            }
            if(parX != parY) sz--;
        }
        int numComponents(){
            return this->sz;
        }
};


class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind* uf = new UnionFind(n);
        for(auto &e : edges){
            uf->add(e[0],e[1]);
        }
        return uf->numComponents();
    }
};