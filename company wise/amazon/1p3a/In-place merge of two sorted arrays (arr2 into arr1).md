Coding: In-place merge two sorted arrays
You are given two non-decreasing (ascending) integer arrays arr1 and arr2. Array arr1 has enough trailing space to hold all elements of arr2.

Merge arr2 into arr1 in-place (O(1) extra space) so that arr1 remains sorted in ascending order.

Input (stdin)
Line 1: m n where arr1 has m valid elements and arr2 has length n
Line 2: arr1 of length m+n (the last n entries are placeholders such as 0)
Line 3: arr2 of length n
Output (stdout)
Print the merged arr1 (length m+n) as space-separated integers
Constraints
0 <= m, n <= 2 * 10^5
Values in [-10^9, 10^9]
Target time complexity: O(m+n)
Example
Input:

3 3
1 2 3 0 0 0
2 5 6
Output:

1 2 2 3 5 6
Follow-up (verbal)
How would you merge if both arrays were sorted in descending order?
If the arrays were unsorted, what would you do (you may modify the input arrays)?
Example
Input
3 3
1 2 3 0 0 0
2 5 6
Output
1 2 2 3 5 6