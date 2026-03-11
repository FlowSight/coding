The cost of a stock on each day is given in an array, arr. An investor wants to buy the stocks in triplets such that the sum of the cost for three days is divisible by d. The goal is to find the number of distinct triplets (i, j, k) such that i < j < k and the sum (arr[i]+arr[j]+arr[k]) is divisible by d.

Function Description

Complete the function getTripletCount in the editor below. The function must return an integer denoting the total number of distinct triplets.

getTripletCount has the following parameters:

int arr[n]: an array of integers
int d: the divisor
Constraints:

3 ≤ n ≤ 10^3
1 ≤ arr[i] ≤ 10^9
2 ≤ d ≤ 10^6
Example
Input
arr = [3, 3, 4, 7, 8]
d = 5
Output
3

