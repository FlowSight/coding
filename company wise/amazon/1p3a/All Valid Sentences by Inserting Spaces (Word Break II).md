Problem
Given a string s and a dictionary of strings wordDict, insert spaces into s to form a sentence such that every word in the sentence exists in wordDict.

Return all possible sentences (any order).

Note: The same dictionary word may be reused multiple times in the segmentation.

Input/Output
Input:
Line 1: string s
Line 2: integer m, size of dictionary
Next m lines: one word per line
Output:
Print all valid sentences, one per line
If no sentence exists, print nothing
Constraints
1 <= len(s) <= 20
1 <= m <= 1000
1 <= len(wordDict[i]) <= 20
All strings contain only lowercase letters
The number of answers can be large, but test cases are designed to be printable in reasonable time
Examples
Example 1
Input:

catsanddog
5
cat
cats
and
sand
dog
Output (any order):

cats and dog
cat sand dog
Example 2
Input:

pineapplepenapple
5
apple
pen
applepen
pine
pineapple
Output (any order):

pine apple pen apple
pineapple pen apple
pine applepen apple
Example 3
Input:

leetcode
2
leet
code
Output:

leet code
Example
Input
catsanddog
5
cat
cats
and
sand
dog
Output
cats and dog
cat sand dog