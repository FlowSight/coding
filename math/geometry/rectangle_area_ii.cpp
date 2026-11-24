/// Severity: Sev0
// Date: 24Oct26
// LC: 850
// Where I failed:
// 1. Used operator= instead of operator== for equality.
// 2. Missed the trailing const required by the multiset comparator.
// 3. Treated active Y coverage as maxY-minY, which counts gaps between disjoint ranges.
// 4. Used end=nextEnd while merging instead of end=max(end,nextEnd), so nested ranges shrank coverage.
// Pattern: line sweep; optimized with coordinate compression + segment tree

// O(n^2): keep active Y-ranges sorted and merge them at every X-coordinate.
class Solution {
    static constexpr int MOD = 1'000'000'007;

    struct Range {
        int y1;
        int y2;

        bool operator<(const Range& other) const {
            if (y1 == other.y1) {
                return y2 < other.y2;
            }
            return y1 < other.y1;
        }
    };

    long long getCoveredY(const multiset<Range>& ranges) {
        if (ranges.empty()) {
            return 0;
        }

        auto it = ranges.begin();
        int start = it->y1;
        int end = it->y2;
        ++it;

        long long covered = 0;
        for (; it != ranges.end(); ++it) {
            if (it->y1 <= end) {
                end = max(end, it->y2);
            } else {
                covered += static_cast<long long>(end) - start;
                start = it->y1;
                end = it->y2;
            }
        }

        return covered + static_cast<long long>(end) - start;
    }

public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        map<int, vector<array<int, 3>>> events;

        for (const auto& rectangle : rectangles) {
            int x1 = rectangle[0];
            int y1 = rectangle[1];
            int x2 = rectangle[2];
            int y2 = rectangle[3];
            events[x1].push_back({y1, y2, 1});
            events[x2].push_back({y1, y2, -1});
        }

        multiset<Range> active;
        long long area = 0;
        int previousX = events.begin()->first;

        for (const auto& [x, xEvents] : events) {
            long long width = static_cast<long long>(x) - previousX;
            area = (area + width * getCoveredY(active)) % MOD;

            for (const auto& [y1, y2, delta] : xEvents) {
                Range range{y1, y2};
                if (delta == 1) {
                    active.insert(range);
                } else {
                    active.erase(active.find(range));
                }
            }

            previousX = x;
        }

        return static_cast<int>(area);
    }
};

// O(n log n): the tree stores covered geometric Y-length, not coordinate count.

// failed : y coords = [.....], seg tree on ranges, if a range is (1,5) left = (1,3) right = (3,5), its dupe at 3, will res in double cnt
// say ys = [2,5,7,9], ranges = [[2,5][5,7],[7,9]] l = 0, r = 2, mid = 1 so left child is [0,1] i.e range [2,5],[5,7] and right is (1,2) == > (7,9)
// now if a rect's {y1,y2} = {5,7} and xs = {2,4}, idx1 = 1, idx2 = 2-1 = 1 ==> ranges : {5,7} 
// if u see carefully, y1 is pointed to the range where range.start == y, but y2 = range.end, as we do -1. so if for 2 diff 
// rectangles, rec1.y2 == rec2.y1, e.g. ys = [2,5,7,9] rec1(y1,y2) = {5,7} rec2(y1,y2) = {7,9}, rec1(idx1,idx2) = (1,1) and rec2(idx1,idx2) = (2,2)
// thats how double counting is avoided.
// The tree indexes elementary half-open Y-intervals, not Y-coordinate points.
// For ys = [2,5,7,9], leaves are:
//   0 -> [2,5), 1 -> [5,7), 2 -> [7,9).
//
// A rectangle [y1,y2) maps to leaf indices
// [index(y1), index(y2)-1].
//
// Thus [5,7) maps to [1,1], while [7,9) maps to [2,2].
// They share only boundary point 7, which has zero length, so no area is
// double-counted. The -1 is needed because index(y2) identifies the first
// elementary interval starting at y2, which is outside [y1,y2).



typedef vector<int> vi;
typedef vector<vi> vvi;
int MOD = 1e9+7;
class Solution {
public:
    struct SegmentTree {
        const vector<int>& ys;
        long long covcount, totalcovered,lidx, ridx;
        SegmentTree* left = nullptr;
        SegmentTree* right = nullptr;
        public:
        SegmentTree(const vi& _ys, int _left, int _right) : ys(_ys),covcount(0), totalcovered(0),lidx(_left),ridx(_right){
            if(lidx == ridx) return;
            int mid = (lidx+ ridx)/2;
            left = new SegmentTree(ys,lidx,mid);
            right = new SegmentTree(ys,mid + 1,ridx);
        }

        ~SegmentTree() {
            delete left;
            delete right;
        }

        SegmentTree(const SegmentTree&) = delete;
        SegmentTree& operator=(const SegmentTree&) = delete;

        void refreshcovered(){
            if(covcount > 0){
                totalcovered = ys[ridx+1]-ys[lidx];
                return;
            }
            if(lidx == ridx) {
                totalcovered = 0;
                return;
            }
            totalcovered = left->totalcovered + right->totalcovered;
        }
        void update(int l, int r, int delta) {
            if((r<lidx) || (l> ridx)) return;
            if((l<=lidx) && (r>=ridx)) {
                covcount += delta; 
                refreshcovered();
                return;
            }
            int mid = (lidx + ridx)/2;
            if(l<=mid) left->update(l,r,delta);
            if(r>mid) right->update(l,r,delta);
            refreshcovered();
            // ------*--------*-------
            // lidx.    mid.    ridx
        }
    };
    int rectangleArea(vector<vector<int>>& rectangles) {
        long n = rectangles.size(), area = 0, lastx = 0, ans = 0;
        
        vi ys;
        vvi events;
        for(auto &it : rectangles) {
            events.push_back({it[0],it[1],it[3],1}); // {x1,y1,y2,1}
            events.push_back({it[2],it[1],it[3],-1}); // {x2,y1,y2,1}
            ys.push_back(it[1]);
            ys.push_back(it[3]);
        }
        sort(events.begin(),events.end());
        sort(ys.begin(),ys.end());
        ys.erase(unique(ys.begin(),ys.end()),ys.end());

        SegmentTree* st = new SegmentTree(ys,0,ys.size()-2);
        lastx = events[0][0];
        for(auto &it : events){
            long long width = it[0] - lastx;
            long long height = st->totalcovered;
            ans = (ans + (width * height)%MOD) % MOD;
            int idx1 = lower_bound(ys.begin(),ys.end(),it[1]) - ys.begin(), 
                idx2 = lower_bound(ys.begin(),ys.end(),it[2]) - ys.begin(); 
            st->update(idx1,idx2-1,it[3]);
            lastx = it[0];
        }
        return ans;

    }
};
