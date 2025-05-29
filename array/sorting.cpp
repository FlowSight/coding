// qucik sort
// avg case tc = 2t(n/2) + n = O(nlogn)
// for kth smallest or largest avg case = t(n/2) + n = O(n)
// sev0


// avg case tc = 2t(n/2) + n = O(nlog
void quickSort(vector<int>& nums, int l, int r){
        if(l>=r)return;
        int pIdx = partition(nums,l,r);
        quickSort(nums,l,pIdx-1);
        quickSort(nums,pIdx+1,r);
    }

    // >=...pivot...<
    // mistake point : have to remember how are we partitioning..greater first or lesser first
    // having hard time remembering this
    int partition(vector<int>& nums, int l, int r){
        int n = (r-l+1), idx = l+1, pIdx = rand()%n+l, pivot = nums[pIdx];
        swap(nums[l],nums[pIdx]);

        for(auto i=l+1;i<=r;i++){
            if(nums[i] >= pivot){
                swap(nums[idx++],nums[i]);
            }
            if((r>i) && (nums[r]<=pivot))r--; // critical step to reduce iterations
        }
        swap(nums[--idx],nums[l]);
        return idx;
    }

    // another >=...pivot...< partition
    int partition(vector<pair<int,int>>& arr, int l, int r){
        int idx = rand()%(r-l+1) + l;
        swap(arr[l],arr[idx]);
        for(auto i=l+1;i<=r;i++){
            if(arr[i].first < arr[l].first){
                swap(arr[r--],arr[i--]);
            } 
            if((r>i) && (nums[r]<=nums[l]))r--;
        }
        swap(arr[l],arr[r]);
        return r;
    }

    // <= ... pivot ..>
    int partition(vector<vector<int>>& arr, int l, int r){
        int idx = l+rand()%(r-l+1);
        swap(arr[l],arr[idx]);
        for(auto i=l+1;i<=r;i++){
            if(dist(arr[i]) > dist(arr[l])) {
                swap(arr[r--],arr[i--]);
            }
        }
        swap(arr[r],arr[l]);
        return r;
    }
// TODO : Floyd-Rivest 

// heap sort
// avg case tc = 2t(n/2) + n = O(nlogn)


void heapSort(vector<int>& nums){
    int n = nums.size();
    for(int i=n/2-1;i>=0;i--){
        heapify(nums,n,i);
    }
    for(int i=n-1;i>0;i--){
        swap(nums[0],nums[i]);
        heapify(nums,i,0);
    }
}


void heapify(vector<int>& nums, int n, int i){
    int l = 2*i+1, r = 2*i+2, largest = i;
    if(l<n && nums[l]>nums[largest])largest = l;
    if(r<n && nums[r]>nums[largest])largest = r;
    if(largest != i){
        swap(nums[i],nums[largest]);
        heapify(nums,n,largest);
    }
}

priority queue 
class MyHeap {
public:
    vector<int> arr;
    int sz;
    MyHeap(){
        sz = 0;
    }

    int getSize(){
        return sz;
    }

    int top() {
        return sz ? arr[0] : INT_MIN;
    }
    void push(int num){
        arr.push_back(num);
        sz++;
        bubbleUp(sz-1);
    }

    void pop(){
        if(sz == 0) return;
        swap(arr[0],arr[sz-1]);
        arr.pop_back();
        sz--;
        bubbleDown(0);
    }

    void bubbleDown(int idx){
        int smaller = idx;
        if((2*idx+1 < sz) && (arr[2*idx+1] <= arr[smaller])) smaller = 2*idx+1;
        if((2*idx+2 < sz) && (arr[2*idx+2] <= arr[smaller])) smaller = 2*idx+2;
        swap(arr[idx],arr[smaller]);
        if(idx != smaller) {
            bubbleDown(smaller);
        }
    }

    void bubbleUp(int idx){
        int par = (idx-1)/2;
        if(arr[par] > arr[idx]) {
            swap(arr[idx],arr[par]);
            bubbleUp(par);
        }
    }
};

