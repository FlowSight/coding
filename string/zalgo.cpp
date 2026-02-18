vector<int> getZ(const string& s) {
    int n = s.length();
    vector<int> z(n);
    int left = 0, right = 0;
    
    for (int i = 1; i < n; i++) {
        if (i <= right) {
            // i is inside the Z-box [left, right]
            // So z[i] is at least min(z[i-left], right-i+1)

            // 0..i..right-left.....left...i..right
            // len = right-left+1
            // prefix arr = 0..len-1 = 0...right-left
            // index of i in prefix arrr = right-left - (right-i) = i-left
            //// s[i..right] matches s[i-left..right-left]
            z[i] = min(z[i - left], right - i + 1);
        }
        
        // Extend z[i] by comparing characters
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        
        // Update Z-box if we extended past right
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}