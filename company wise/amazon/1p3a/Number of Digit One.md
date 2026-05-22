
    int countDigitOne(int n) {
        int ans = 0;
        for(long i=1;i<=n;i*=10){
            int a = n/i, b = n%i;
            ans += (a+8)/10 * i + (a%10 == 1)*(b+1);
        }
        return ans;
    }

Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

Input:

An integer n (1 <= n <= 10^9)
Output:

The count of digit 1 appearing from 1 to n.
Example:

Input: 13
Output: 6
Explanation: The numbers containing digit 1 are 1, 10, 11, 12, 13.
Example
Input
13

