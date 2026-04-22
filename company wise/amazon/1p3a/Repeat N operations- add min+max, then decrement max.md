Problem
Given an integer array array and an integer n (number of requests/operations), perform n operations and return an array res of length n, where res[i] is the sum obtained in the i-th operation.

Operation
For each operation on the current array:

Let mn be the current minimum value and mx be the current maximum value.
Append mn + mx to the result list.
Update one occurrence of the maximum value in the array to mx - 1 (all other elements unchanged).
Output
Return the list of sums produced by the n operations.

Constraints
1 <= len(array) <= 2*10^5
0 <= array[i] <= 10^9
1 <= n <= 2*10^5
Sample Tests
array=[1,2,3], n=2 -> [4,4] (subject to exact decrement rules)
array=[5], n=3 -> [10,9,8]
array=[0,0,0], n=2 -> [0,0]
array=[2,2,2], n=3 -> [4,4,4]
array=[1,100,100], n=2 -> [101,101]
Note: If the original OA specified additional constraints (e.g., values cannot go below 0), follow the original statement.

Example
Input
3 2
1 2 3
Output
4
3