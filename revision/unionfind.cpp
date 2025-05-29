class UnionFind{
    public:
    vector<int> par;
    int sz;
    UnionFind(int _sz){
        sz = _sz;
        for(auto i=0;i<sz;i++) par.push_back(i);
    }
    // dont do 
    // return (par[x] == -1 )? x : find(par[x]);
    // if 1<-2<-3 and add(1,3), then par[1] = 1.then it will be stuck in loop
    int find(int x){
        return (par[x] == x )? x : find(par[x]);
    }

    void add(int x,int y){
        int px = find(x), py = find(y);
        par[px] = py;
    }
};