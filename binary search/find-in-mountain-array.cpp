/// Severity: Sev2
// Date: 25Aug26
// LC: 1095
// Where I failed: corner case for down
// Pattern: ternery serch
// Notes: additional_notes



class Solution {
public:
    int findInMountainArray(int target, MountainArray &arr) {
        int n = arr.length(), pivotidx = findpivot(arr,0,n-1);
        int leftidx = findleft(arr,0,pivotidx,target);
        if(leftidx != -1) return leftidx;
        return findright(arr,pivotidx+1,n-1,target);
    }

    int findleft(MountainArray &arr, int l, int r, int target){
        if(l>r) return -1;
        int mid = (l+r)/2, num1 = arr.get(mid);
        if(num1 == target) return mid;
        if(num1 > target) return findleft(arr,l,mid-1,target);
        return findleft(arr,mid+1,r,target);
    }
    int findright(MountainArray &arr, int l, int r, int target){
        if(l>r) return -1;
        int mid = (l+r)/2, num1 = arr.get(mid);
        if(num1 == target) return mid;
        if(num1 > target) return findright(arr,mid+1,r,target);
        return findright(arr,l,mid-1,target);
    }
    int findpivot(MountainArray &arr, int l, int r) {
        if(r-l+1 <3) return -1;
        int mid = (l+r)/2, nummid = arr.get(mid), num1 = arr.get(mid-1), num2 = arr.get(mid+1);
        if(num1<nummid) {
            if(nummid > num2) return mid;
            return findpivot(arr,mid,r);
        }
        return findpivot(arr,l,mid);
    }
};
