typedef vector<int> vi;
typedef vector<vi> vvi;

class UnionFind {
    public:
    int sz;
    unordered_map<int,int> par, rank;
    UnionFind(int _n) {
        sz = _n;
        par.clear();
    }
    int find(int idx){
        if(par.find(idx) == par.end()) {
            rank[idx] = 0;
            par[idx] = idx;
            return idx;
        }
        return par[idx] = (par[idx] == idx ? idx : find(par[idx]));
    }

    void add(int u, int v){
        int par1 = find(u), par2 = find(v);
        if (par1 == par2) {
            return;
        }
        if(rank[par1] > rank[par2]) par[par2] = par1;
        else if(rank[par2] > rank[par1]) par[par1] = par2;
        else {
            par[par1] = par2;
            rank[par2]++;
        }
    }
    unordered_map<int,vi> getgroups(){
        unordered_map<int,vi> ans;
        for(auto& it : par) {
            ans[find(it.first)].push_back(it.first);
        } 
        return ans;
    }

};

class Solution {
public: 

   
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
         map<int,vvi> mm;
        int m = matrix.size(), n = matrix[0].size();
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++) {
                mm[matrix[i][j]].push_back({i,j});
            }
        }
        vvi ans(m,vi(n,0));
        vi maxrank(m+n,0);
        for(const auto& it : mm){
            UnionFind uf(m+n);
            for(auto &cell : it.second){
                uf.add(cell[0],cell[1] + m);
            }
            for(auto& group : uf.getgroups()){
                int maxval = 0;
                for(auto &rowcol : group.second) {
                    maxval = max(maxval,maxrank[rowcol]);
                }
                for(auto &rowcol : group.second) {
                   maxrank[rowcol] = maxval + 1;
                }
            }
            for(auto const& cell : it.second){
                ans[cell[0]][cell[1]] = maxrank[cell[0]];
            }
        }
        return ans;
    }
};

// pick min values group, set all to 1
// update maxrank per row/col
// continue for next group, same val or higher val

class EpochUnionFind {
    vector<int> parent;
    vector<int> componentSize;
    vector<int> activeEpoch;
    int epoch = 0;

    void activate(int node) {
        if (activeEpoch[node] == epoch) {
            return;
        }

        activeEpoch[node] = epoch;
        parent[node] = node;
        componentSize[node] = 1;
    }

public:
    explicit EpochUnionFind(int nodeCount)
        : parent(nodeCount),
          componentSize(nodeCount),
          activeEpoch(nodeCount, -1) {}

    void beginBatch() {
        ++epoch;
    }

    int find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void unite(int u, int v) {
        activate(u);
        activate(v);

        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return;
        }

        if (componentSize[rootU] < componentSize[rootV]) {
            swap(rootU, rootV);
        }

        parent[rootV] = rootU;
        componentSize[rootU] += componentSize[rootV];
    }

    int currentEpoch() const {
        return epoch;
    }
};

class SolutionEpochDSU {
    struct Cell {
        int value;
        int row;
        int col;
    };

public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int cellCount = rows * cols;

        vector<Cell> cells;
        cells.reserve(cellCount);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                cells.push_back({matrix[row][col], row, col});
            }
        }
        
        // sorting once is faster at scale + can be parallelized. 
        // map is sparse and sparse in mem.
        sort(cells.begin(), cells.end(), [](const Cell& a, const Cell& b) {
            return a.value < b.value;
        });

        vector<vector<int>> answer(rows, vector<int>(cols));
        vector<int> maxRank(rows + cols);
        vector<int> componentRank(rows + cols);
        vector<int> componentRankEpoch(rows + cols, -1);
        EpochUnionFind dsu(rows + cols);

        for (int start = 0; start < cellCount;) {
            int end = start + 1;
            while (end < cellCount && cells[end].value == cells[start].value) {
                ++end;
            }

            dsu.beginBatch();

            for (int i = start; i < end; ++i) {
                dsu.unite(cells[i].row, rows + cells[i].col);
            }

            for (int i = start; i < end; ++i) {
                int rowNode = cells[i].row;
                int colNode = rows + cells[i].col;
                int root = dsu.find(rowNode);

                if (componentRankEpoch[root] != dsu.currentEpoch()) {
                    componentRankEpoch[root] = dsu.currentEpoch();
                    componentRank[root] = 0;
                }

                componentRank[root] = max(
                    componentRank[root],
                    max(maxRank[rowNode], maxRank[colNode]) + 1
                );
            }

            for (int i = start; i < end; ++i) {
                int rowNode = cells[i].row;
                int colNode = rows + cells[i].col;
                int rank = componentRank[dsu.find(rowNode)];

                answer[cells[i].row][cells[i].col] = rank;
                maxRank[rowNode] = max(maxRank[rowNode], rank);
                maxRank[colNode] = max(maxRank[colNode], rank);
            }

            start = end;
        }

        return answer;
    }
};

