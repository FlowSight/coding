Given array arr of length n, we define function f(arr) as- if n=1, f(arr) = arr[0]; else, f(arr) = f(arr[0] ^ arr[1], arr[1] ^ arr[2],..., arr[n-2] ^ arr[n-1]) where ^ is bitwise XOR operator.

For example, arr = [1, 2, 4, 8], n = 4 f(1, 2, 4, 8) = f(1^2, 2^4, 4^8) = f(3,6,12) = f(3^6,6^12) = f(5, 10) = f(5^10) = f(15) = 15.

You need to answer q queries, each query you are given two integers l and r. For each query, what is the maximum of f() for all continuous subsegments of the array from l to r.

Function Description

Complete the function maximumXORForEachQuery in the editor.

maximumXORForEachQuery has the following parameters:

int arr[]: an array of integers
int l: an integer representing the left index of the range
int r: an integer representing the right index of the range
Returns

int: the maximum XOR value for all continuous subsegments of the array from l to r

Constraints: N/A

Example
Input
arr = [1, 2, 4, 8, 16, 32]
l = 1
r = 4
Output
15