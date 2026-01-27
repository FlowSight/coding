// 7 jan..missed one optimization..sev0..

class SegmentTree {
    public:
    SegmentTree* leftNode;
    SegmentTree* rightNode;
    int left, right, sum;
    SegmentTree(vector<int>& arr, int _left, int _right){
        leftNode = nullptr;
        rightNode = nullptr;
        left = _left;
        right = _right;
        if(left == right){
            sum = arr[left];
            return;
        }
        int mid = (left+right)/2;
        leftNode = new SegmentTree(arr,left,mid);
        rightNode = new SegmentTree(arr,mid+1,right);
        sum = leftNode->sum + rightNode->sum;
    }
    void update(int& idx, int& val){
        if((idx <left) || (idx>right)) return;
        if(left == right) {
            sum = val;
            return;
        }
        int mid =  (right+left)/2;
        if(idx<=mid) leftNode->update(idx,val);
        else rightNode->update(idx,val);
        sum = leftNode->sum + rightNode->sum;
    }

    int getSum(int l, int& r){
        if((left == right) && (l==left) && (r == right)) return sum;
        if (l <= left && r>= right) return sum;
        if((r<left) || (l>right)) return 0;
        int mid = (right+left)/2;
        if(r<=mid) return leftNode->getSum(l,r);
        if(l>mid) return rightNode->getSum(l,r);
        return leftNode->getSum(l,mid) + rightNode->getSum(mid+1,r);
    }
};
class NumArray {
public:
    SegmentTree* root;
    int n;
    NumArray(vector<int>& nums) {
        n = nums.size();
        root = new SegmentTree(nums,0,n-1);
    }
    
    void update(int index, int val) {
        root->update(index,val);
    }
    
    int sumRange(int left, int right) {
        return root->getSum(left,right);
    }
};

