Problem
You are given an array of strings words. Each lowercase letter has a corresponding Morse code representation. The transformation of a word is defined as the concatenation of the Morse codes of its letters in order.

Return the number of distinct transformations among all words in words.

The Morse mapping is (for a to z):

[".-","-...","-.-.","-..",".","..-.","--.","....","..",
 ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
 "...","-","..-","...-",".--","-..-","-.--","--.."]
Input Format
Line 1: integer n, the number of words.
Next n lines: one lowercase word per line.
Output Format
Print one integer: the number of distinct transformations.
Constraints
1 <= n <= 1000
1 <= len(words[i]) <= 12
words[i] contains only a-z
Example
Input:

4
gin
zen
gig
msg
Output:

2
Example
Input
4
gin
zen
gig
msg
Output
2