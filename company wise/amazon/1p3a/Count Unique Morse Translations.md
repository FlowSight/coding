
Given an array of strings words, each word can be translated into Morse code by replacing each letter with its Morse code string and concatenating them in order.

For example, "cab" becomes "-.-..--..." because it equals the concatenation of "-.-." + ".-" + "-...".

Translate every word in words and return the number of distinct translations.

Input/Output
Input:
Line 1: integer n, number of words
Next n lines: one lowercase word per line
Output:
An integer: the number of distinct Morse translations
Constraints
1 <= n <= 100

1 <= len(words[i]) <= 12

words[i] consists of lowercase letters a-z

Use the following 26 Morse codes for a to z:

.- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..

Examples
Example 1
Input:

4
gin
zen
gig
msg
Output:

2
Example 2
Input:

1
cab
Output:

1
Example
Input
4
gin
zen
gig
msg
Output
2