// 27 dec 2024..
// 5 mins..
// made a logical mistake of adding into set at the end of each iteration..
// verdict : FAIL


    bool isHappy(int n) {
        unordered_set<int> ss;
        int res = 0, tmp = n;
        while(ss.find(n) == ss.end()){
            ss.insert(n);
            res = 0;
            tmp = n;
            while(tmp){
                res += (tmp%10)*(tmp%10);
                tmp/=10;
            }
            n = res;
            //cout<<n<<endl;
            if(n == 1) return true;
        }
        return false;
    }
};