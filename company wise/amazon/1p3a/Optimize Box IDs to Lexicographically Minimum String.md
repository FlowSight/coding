Problem: Optimize Box IDs to Get the Lexicographically Minimum String
In a warehouse, boxes are arranged in a row from left to right. Their IDs are represented by a string boxIds consisting only of digits '0' to '9', where the i-th box has ID boxIds[i].

You may perform the following operation any number of times (possibly zero):

Choose an index i and remove the digit boxIds[i].
Update that box’s ID to min((original digit value) + 1, 9), then insert this updated digit at any position in the string (beginning, end, or between any two adjacent digits).
Return the lexicographically smallest string that can be obtained after any number of operations.

Lexicographic order: for two strings of the same length, the one with a smaller digit at the first position where they differ is lexicographically smaller.

Example
Input: boxIds = "26547"

Output: "24677"

Function Signature
string optimizeBoxIds(string boxIds)

Constraints
1 ≤ |boxIds| ≤ 2 * 10^5
boxIds contains only digits '0' to '9' (leading zeros allowed)
Sample Tests
Input: 26547
Output: 24677
Input: 0
Output: 0
Input: 9
Output: 9
Input: 109
Output: 019
Input: 9990
Output: 0999
Example
Input
26547
Output
24677