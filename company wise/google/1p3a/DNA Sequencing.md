Some data scientists are building a utility to analyze palindromic trends in the DNA sequencing of a string. The palindrome transformation cost of a string is defined as the minimum number of characters that need to be changed in it so that it can be rearranged to form a palindrome. For example, the palindrome transformation cost of the string "aabcd" is 1 since we can change the last character 'd' to 'c' so that the string becomes "aabcc" that can be rearranged to "acbca" which is a palindrome.

Given string dna, find the total sum of palindrome transformation cost of all the substrings of the given string.

Note: A palindrome is a sequence that reads the same backward as forward, for example, sequences "z", "aba" and "aaa" are palindromes, but sequences "xy", "rank" are not.

Function Description

Complete the function setTotalPalindromeTransformationCost in the editor below. The function returns the total sum of palindrome transformation costs across all substrings.

setTotalPalindromeTransformationCost has the following parameter:

dna: string
**༊·° Now sending 1009th thank you to spike! **

Constraints:

1 <= |dna| <= 2 * 10^5
The string dna contains lowercase english letters only
Example
Input
dna = "abca"
Output
6