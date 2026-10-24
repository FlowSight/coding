/// Severity: Sev0
// Date: 07Oct26
// LC: 774
// Where I failed: mistake that i can onnly split into half, it can be split in k pieces also
// i could not come up with bin search
// Pattern: pattern_name
// Notes: additional_notes


// this will timeput as its O(k * log(stations))
class Solution {
public:
    struct Gap {
        public:
        int len,added;
        Gap(int _len, int _added) : len(_len), added(_added){}
        double getgap() const {
            return static_cast<double>(len) / (added + 1);
        }
        bool operator>(const Gap& gap) const {
            return getgap() > gap.getgap();
        }
    };
    double minmaxGasDist(vector<int>& arr, int k) {
        multiset<Gap,greater<Gap>> gaps;
        int n = arr.size();
        for(auto i=1;i<n;i++){
            gaps.insert(Gap(arr[i]-arr[i-1],0));
        }
        while(k--){
            auto tp = *(gaps.begin());
            gaps.erase(gaps.begin());
            tp.added++;
            gaps.insert(tp);
        }
        auto tp = *(gaps.begin());
        return tp.getgap();
    }
};

// binary search
class Solution {
public:
    double minmaxGasDist(vector<int>& arr, int k) {
        int n = arr.size();
        double mingap = 0, maxgap = 1, mid = 0;
        for(auto i=1;i<n;i++){
            maxgap = max(maxgap,static_cast<double>(arr[i]-arr[i-1]));
        }
        while(maxgap - mingap > 1e-6) {
            mid = (maxgap + mingap)/2;
            if(valid(arr,k,mid)) maxgap = mid;
            else mingap = mid;
        }
        return mingap;
    }

    bool valid(vector<int>& arr, int k, double& gap){
        int n = arr.size();
        for(auto i=1;i<n;i++){
            int cur = arr[i]-arr[i-1];
            k -= ceil(cur/gap) - 1;
            if(k<0) return false;
        }
        return true;
    }
};
