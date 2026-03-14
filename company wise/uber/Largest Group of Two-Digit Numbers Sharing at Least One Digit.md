You are given an integer array nums where every element is a two-digit number (from 10 to 99). Two numbers are considered in the same group if they share at least one digit (e.g., 34 and 44 share digit 4).

The relation is transitive: if a shares a digit with b, and b shares a digit with c, then a, b, c are in the same group (i.e., connected component).
Return the size of the largest group (largest connected component) that can be formed from nums.

Input:

First line: integer m.
Second line: m integers representing nums.
Output: one integer, the size of the largest group.

Constraints (suggested): 1 <= m <= 2e5.

Example: Input: 5 34 44 19 91 28 Output: 4

The example mainly illustrates I/O format; connectivity depends on the exact numbers present.

Example
Input
5
34 44 19 91 28
4