You are given an array of n magical fruits. The power of the fruit is given in an array of length n. You are also given an integer k. Your task is to find the maximum length L such that every subarray of length L has the sum of powers strictly less than k.

Input Format

The first line contains two integers n and k — the number of fruits and the maximum allowed power sum. The second line contains n integers — the array a, where a[i] is the power of the i-th fruit.

Output Format

Print a single integer — the maximum value of L.

Constraints

1 ≤ n ≤ 2 * 10^5
1 ≤ a[i] ≤ 10^9
1 ≤ k ≤ 10^18
Example
Input
a = [3, 1, 2, 4]
k = 8
Output
3