Problem: Maximum Equal-Frequency Block Count for Each Prefix
Given a string s of length n consisting of uppercase letters A-Z.

For each prefix p = s[0..i] (for 0 ≤ i < n), compute the maximum integer k such that:

The prefix can be split into k contiguous blocks;
All blocks have the same length (so k divides len(p));
For every character c, the number of occurrences of c is identical in every block (i.e., all blocks share the same frequency vector).
Output the maximum k for each prefix.

Input
One line: string s
Output
n integers: the i-th integer is the answer for prefix s[0..i].
Constraints
1 ≤ n ≤ 2e5
s contains only A-Z
Example
Input:

ABBA
Output:

1 1 1 2
Example
Input
ABBA
Output
1 1 1 2