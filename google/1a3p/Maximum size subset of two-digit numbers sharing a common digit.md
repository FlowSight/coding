Problem (Google OA / 26NG)
You are given an array A of length N, where each element is a two-digit integer (from 10 to 99, inclusive).

Select as many elements as possible from the array such that:

All selected numbers share at least one common decimal digit (one digit among 0~9).
Return the maximum number of elements you can select.

Input / Output
Input:
Line 1: integer N
Line 2: N integers representing array A
Output:
One integer: the maximum size of such a subset
Constraints
1 <= N <= 100
10 <= A[i] <= 99
Each A[i] is guaranteed to be a two-digit number
Examples
Example 1

Input: A = [52, 25, 11, 52, 34, 55]
Output: 4
Explanation: Select 52, 25, 52, 55 — they all contain digit 5.
Example 2

Input: A = [71, 23, 57, 15]
Output: 2
Explanation: Select 71, 57 — both contain digit 7.
Example 3

Input: A = [11, 33, 55]
Output: 1
Explanation: No two numbers share a digit, so you can only select one.
Example 4

Input: A = [90, 90, 90]
Output: 3
Explanation: All three contain digit 9 (or 0), so all can be selected.
Example
Input
6
52 25 11 52 34 55
Output
4