Given an array arr, such as [1, 20, 2, 11], define two variables i, j in [0, len(arr)). Find the number of times arr[i] + flip(arr[j]) = arr[j] + flip(arr[i]) is satisfied. flip(x) means reversing the digits of x, such as flip(20) = 2.

Input format:

The first line is an integer array arr.
Output format:

Output the number of pairs (i, j) that satisfy the condition.
Example
Input
arr = [1, 20, 2, 11]