class UF {
    public:
    int sz, count;
    vector<int> par, rank;
    UF(int n){
        sz = n;
        count = sz;
        par = vector<int>(sz,-1);
        rank = vector<int>(sz,-1);
    }

    void add(int x, int y){
        int parX = find(x) , parY = find(y);
        if(parX == parY) return;
        if(rank[parX] > rank[parY]) {
            par[parY] = parX;
        } else {
            par[parX] = parY;
            if(rank[parX] == rank[parY]) rank[parY]++;
        }
        count--;

    }

    int find(int x){
        return par[x] == -1 ? x : find(par[x]);
    }

    int findCompCount(){
        return count;
    }
};