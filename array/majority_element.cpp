int majorityElement(vector<int>& arr){
    int n = arr.size(), res = 0;
    for(auto i=0,cnt = 0;i<32;i++,cnt = 0){
        for(auto j=0;j<n;j++){
          if(arr[i] && (1<<i))cnt++;
        }
        if(cnt > n/2)res |= (1<<i);
    }
    return res;
}

int majorityElementMooreVoting(vector<int>& arr){
    int n = arr.size(), majority = arr[0], cnt = 1;
    for(auto i=1;i<n;i++){
        if(arr[i] != majority){
            cnt--;
            if(cnt == 0){
                majority = arr[i];
                cnt = 1;
            }
        }
    }
    return cnt > 0 ? majority : -1;
}