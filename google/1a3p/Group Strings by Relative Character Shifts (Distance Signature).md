Given an array of strings strings, group them by a "shift distance signature".

For a string s, define its signature as the sequence of relative distances between adjacent characters:

For each adjacent pair s[i-1] and s[i], define delta = (ord(s[i]) - ord(s[i-1])) mod 26.
Example: "abc" has signature [1, 1]; "az" has signature [25] (since ('z'-'a') mod 26 = 25).
Strings of length 0 or 1 have an empty signature [].
Group strings with the same signature together and return all groups.

Input
Line 1: integer n, number of strings.
Next n lines: one string per line (assume lowercase a-z).
Output
Print the groups, one group per line, strings in the same group separated by spaces. Order of groups and order within each group do not matter.

Constraints
1 <= n <= 2 * 10^4
0 <= len(strings[i]) <= 10^4
Total length of all strings <= 2 * 10^5
Example
Input:

6
abc
bcd
acef
xyz
az
ba
Possible output:

abc bcd xyz
az ba
acef
(Any order is acceptable.)

Example
Input
6
abc
bcd
acef
xyz
az
ba
Output
abc bcd xyz
az ba
acef