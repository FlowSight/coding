Relative sorting is defined as sorting two arrays (both in strictly ascending order) such that the only operation allowed is swapping i'th element of one array with the i'th element of the other array. An array is said to be in strictly ascending order if i'th element of the array is smaller than (i+1)'th element of the array. You are given two arrays of size N. print the minimum number of swaps required to make both arrays relatively sorted.

Note:- If the arrays are already relatively sorted, then print '0'

If the arrays cannot be relatively sorted, then print '-1'.
Input Format:

The input consist of 3 lines:- First line consist of the size of each array, i.e. N

The next two lines contain N elements each separated by a space
Output Format:

The output will be an integer i.e., the minimum number of swaps required to make both arrays relatively sorted.

Constraints: 0 < N < 11000
0 < Elements in array <= 10^9

Example
Input
N = 4
A = [1, 4, 4, 9]
B = [2, 3, 5, 10]
Output
1