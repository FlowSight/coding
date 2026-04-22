Problem
Given a string s and a dictionary wordDict (no duplicate words), insert spaces into s to form sentences such that every word in the sentence exists in wordDict.

Return all possible sentences (any order). Words in the dictionary may be reused multiple times.

Input Format
Line 1: string s
Line 2: integer m, dictionary size
Next m lines: one word per line
Output Format
Line 1: integer k, number of valid sentences
Next k lines: one valid sentence per line
(If k = 0, output a single line 0.)

Constraints
1 <= len(s) <= 30
1 <= m <= 1000
1 <= len(word) <= 20
s and words contain only lowercase letters a-z
Example
Input:

catsanddog
5
cat
cats
and
sand
dog
Output (order may vary):

2
cats and dog
cat sand dog
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
2
cat sand dog
cats and dog