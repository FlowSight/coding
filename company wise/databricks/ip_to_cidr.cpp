//sev0.28/10/25




// actully bad question
class Solution {
public:
    vector<string> ipToCIDR(string ip, int n) {
        vector<string> ans;
        long ipVal = toInt(ip);
        while(n){
            long trailZero = getZero(ipVal), maxVal = (long) 1<<trailZero
                , shiftCnt = 0, shiftVal = 1;
            for(auto i=1;i<=trailZero && (shiftVal<<1<=n);i++){
                shiftCnt++;
                shiftVal<<=1;
            }
            ans.push_back(process(ipVal,32-shiftCnt));
            n -= shiftVal;
            ipVal+=shiftVal;
        }
        return ans;
    }

    string process(int num, int cnt){
        vector<string> arr;
        string ans = "";
        for(auto i=1;i<=4;i++){
            auto val = num & 255;
            arr.push_back(to_string(val));
            num >>= 8;
        }
        for(auto i=3;i>=0;i--){
            ans+=arr[i];
            ans.push_back('.');
        }
        ans.pop_back();
        ans.push_back('/');
        ans += to_string(cnt);
        return ans;
    }

    long toInt(string str){
        stringstream ss(str);
        string tmp = "";
        long ans = 0;
        while(getline(ss,tmp,'.')){
            ans*=256;
            ans += stoi(tmp);
            tmp = "";
        }
        return ans;
    }

    long getZero(long num){
        long ans = 0;
        for(auto i=1;i<=32;i++){
            if(num & 1) break;
            ans++;
            num >>= 1;
        }
        return ans;
    }
};