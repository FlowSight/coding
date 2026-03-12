Given an array of integers arr, define a function flip to completely reverse the digits of a number (the reversed number cannot have leading zeros). For example, flip(800) = 8 and flip(210) = 12. For every pair of elements arr[i] and arr[j] in the array, where indices i, j are within the range of the array, count the number of pairs where arr[i] + flip(arr[j]) = arr[j] + flip(arr[i]).

Input:
An array of integers arr.
Output:
The count of such pairs.
Example Input:
[1, 20, 2, 11]
Example Output:
2
Constraints:
1 <= len(arr) <= 10^5
1 <= arr[i] <= 10^4
Example
Input
4
1 20 2 11