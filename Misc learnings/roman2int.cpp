class Solution {
public:
    unordered_map<char,int> mm;
    int romanToInt(string s) {
        int n = s.size(), ans = 0;
        mm['M'] = 1000;
        mm['V'] = 5;
        mm['L'] = 50;
        mm['D'] = 500;
        mm['C'] = 100;
        mm['X'] = 10;
        mm['I'] = 1;

        for(auto i=0;i<n-1;i++){
            if(mm[s[i]] < mm[s[i+1]]) ans += -mm[s[i]];
            else ans += mm[s[i]];
        }
        ans += mm[s.back()];
        return ans;
    }
};

// another approach

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size(), ans = 0, num = 0;
        unordered_map<string,int> mm;
        for(auto i=n-1;i>=0;i--){
            switch(s[i]){
                case 'I': num = 1; break;
                case 'V': num = 5; break;
                case 'X': num = 10; break;
                case 'L': num = 50; break;
                case 'C': num = 100; break;
                case 'D': num = 500; break;
                case 'M': num = 1000; break;
            }
            if (4 * num < ans) ans -= num;
            else ans += num;
        }
        return ans;
    }
};
