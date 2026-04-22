You are given a string s consisting only of characters '0', '1', and '!'. You must replace each '!' with either '0' or '1' to obtain a final binary string.

For the final string, for any pair of indices i < j:

If (s[i], s[j]) = ('1','0'), it forms a 10 pair; each such pair contributes x errors.
If (s[i], s[j]) = ('0','1'), it forms a 01 pair; each such pair contributes y errors.
Choose replacements to maximize the total number of errors and return the maximum total modulo 1_000_000_007.

Total errors are defined as: x * count10 + y * count01, where count10/count01 are the numbers of such subsequence pairs (i<j), not subarrays.

Input (stdin)
Line 1: string s Line 2: integer x Line 3: integer y

Output (stdout)
One line: the maximum total errors modulo 1_000_000_007.

Constraints
Not provided; assume large |s| (e.g., up to 2e5).

Example
Input
101!1
3
2
Output
(depends on official statement)