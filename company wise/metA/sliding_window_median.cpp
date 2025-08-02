//29 july 2025
    vector<double> medianSlidingWindow(vector<int>& arr, int k) {
        int n = arr.size();
        multiset<int,greater<int>> left;
        multiset<int> right;
        vector<double>  ans;
        double first = 0, second = 0;

        for(auto i=0;i<k;i++){
            left.insert(arr[i]);
            if(left.size() > k/2){
                right.insert(*(left.begin()));
                left.erase(left.begin());
            }
        }
        first = *(right.begin())/2.0;
        second = k%2 ? first : *(left.begin())/2.0;
        ans.push_back((first+second));

        for(auto i=k;i<n;i++){
            if(arr[i] >= *(right.begin())) {
                right.insert(arr[i]);
            } else {
                left.insert(arr[i]);
            }
            if(arr[i-k] >= *(right.begin())) {
                right.erase(right.lower_bound(arr[i-k]));
            } else {
                left.erase(left.lower_bound(arr[i-k]));
            }

            if(left.size() > k/2) {
                right.insert(*(left.begin()));
                left.erase(left.begin());
            }

            if(right.size() > k/2 + k%2) {
                left.insert(*(right.begin()));
                right.erase(right.begin());
            }
            first = *(right.begin())/2.0;
            second = k%2 ? first : *(left.begin())/2.0;
            ans.push_back(first+second);
        }
        return ans;
    }

14 june 2025


// two heap is the way..iterator way doesnt makes sense..
// left is half, right is half + (sz%2)
// balance util is the key

class Solution {
public:
        multiset<int> minPq, maxPq;// maxheap
        //mutiset<int,vector<int>,greater<int>> maxPq; // minheap
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> ans;
        int n = nums.size();

        for(auto i=0;i<k;i++) {
            minPq.insert(nums[i]);
        }
        for(auto i=1;i<=(k+1)/2;i++){
            auto it = prev(minPq.end());
            maxPq.insert(*(it));
            minPq.erase(it);
        }
        auto med = k%2 ? *(maxPq.begin()) : (*(maxPq.begin())/2.0 + *(minPq.rbegin())/2.0 );
        ans.push_back(med);
        for(auto i=k;i<n;i++){
            balance(nums[i-k],nums[i],k);
            med = k%2 ? *(maxPq.begin()) : (*(maxPq.begin())/2.0 + *(minPq.rbegin())/2.0 );
            ans.push_back(med);
        }
        return ans;
    }

    void balance(int remove, int add, int k){
        maxPq.insert(add);
        auto it = minPq.lower_bound(remove);
        if(it != minPq.end()){
            // remove from left side max heap
            minPq.erase(it);
            
            auto tp = *(maxPq.begin());
            minPq.insert(tp);
            maxPq.erase(maxPq.begin());
        } else {
            maxPq.erase(maxPq.lower_bound(remove));
        }
        if(k>1){
            auto lMax = *(minPq.rbegin()), rMin = *(maxPq.begin());
            if(lMax> rMin) {
                minPq.erase(minPq.lower_bound(lMax));
                maxPq.erase(maxPq.lower_bound(rMin));
                minPq.insert(rMin);
                maxPq.insert(lMax);
            }
        }
    }
};

// [1,3,-1,-3,5,3,6,7]

// min = {-1}
// max = {1,3}
