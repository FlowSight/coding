/// Severity: Sev0
// Date: 20May26
// LC: 233
// Where I failed: math..
// Pattern: math..bucket digit counting
// Notes: sev0..sev0..sev0



int countDigitOne(int n) {
        int ans = 0;
        for(long i=1;i<=n;i*=10){
            int a = n/i, b = n%i;
            ans += (a+8)/10 * i + (a%10 == 1)*(b+1);
        }
        return ans;
    }