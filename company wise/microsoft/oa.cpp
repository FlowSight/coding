#include <bits/stdc++.h>
using namespace std;

// Precompute Pascal's triangle for combinations
vector<vector<long long>> C;

void precomputeCombinations(int maxN) {
    C.assign(maxN + 1, vector<long long>(maxN + 1, 0));
    for (int i = 0; i <= maxN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

int countSetBits(long long n) {
    return __builtin_popcountll(n);
}

// Find next number with same number of set bits
long long nextWithSameBits(long long n) {
    // Find rightmost 0 bit that has a 1 to its right
    long long c = n;
    long long c0 = 0;  // count of 0s to the right
    long long c1 = 0;  // count of 1s to the right
    
    // Count trailing zeros
    while (((c & 1) == 0) && c != 0) {
        c0++;
        c >>= 1;
    }
    
    // Count ones after trailing zeros
    while ((c & 1) == 1) {
        c1++;
        c >>= 1;
    }
    
    // Position of rightmost non-trailing zero
    long long pos = c0 + c1;
    
    // Flip rightmost non-trailing zero
    n |= (1LL << pos);
    
    // Clear all bits to the right of pos
    n &= ~((1LL << pos) - 1);
    
    // Insert (c1-1) ones on the right
    n |= (1LL << (c1 - 1)) - 1;
    
    return n;
}

void precomputeCombinations(int maxN) {
    C.assign(maxN + 1, vector<long long>(maxN + 1, 0));
    for (int i = 0; i <= maxN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

// Count numbers from 0 to n with exactly k set bits using digit DP
long long countWithKSetBits(long long n, int k) {
    if (k < 0 || k > 64) return 0;
    
    // Check if n has all bits set (n = 2^m - 1)
    // If n has all bits set, the answer is simply C(m, k)
        // n has all bits set, count trailing ones
    int m = __builtin_popcountll(n);
    if (k <= m) {
        return C[m][k];s
    }
    return 0;
}

long long countIntegersWithSameBits(long long n, int setBits) {
    // Count numbers from 1 to n with exactly 'setBits' set bits
    return countWithKSetBits(n, setBits);
}

int main() {
    long long n;
    cout << "Enter integer n: ";
    cin >> n;
    
    // Precompute combinations up to 64 bits
    precomputeCombinations(64);
    
    int setBits = countSetBits(n);
    cout << "Number of set bits in " << n << ": " << setBits << endl;
    
    long long f_n = nextWithSameBits(n);
    cout << "f(n) = " << f_n << endl;
    
    long long result = countIntegersWithSameBits(f_n, setBits);
    cout << "Count of integers <= f(n) with same set bits: " << result << endl;
    
    return 0;
}