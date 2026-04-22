Given an integer array codes where each element is an error code, sort the array using the following priority rules and return the sorted array (keeping duplicates):

Frequency first: error codes with lower frequency come earlier.
Value tie-breaker: if two codes have the same frequency, the smaller numeric value comes earlier.
Return the fully sorted array.

Constraints

1 <= len(codes) <= 2*10^5
-10^9 <= codes[i] <= 10^9
Example

Input: [4, 5, 6, 5, 4, 3]
Frequencies: 3->1, 6->1, 4->2, 5->2
Output: [3, 6, 4, 4, 5, 5]
Example
Input
6
4 5 6 5 4 3
Output
3 6 4 4 5 5