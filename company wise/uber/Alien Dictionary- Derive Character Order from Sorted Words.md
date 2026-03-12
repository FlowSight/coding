Given a list of words written in an alien language, where the words are sorted lexicographically according to the rules of this alien language, determine the order of characters in the alien alphabet. Return the order as a string of characters. If the order cannot be determined, return "". Assume all words contain at least one character and all characters are lowercase letters. The input list is sorted in accordance with the alien language's lexicographical order. If there are multiple valid solutions, return the one that is smallest in lexicographical order.

Example 1:

Input: ["wrt", "wrf", "er", "ett", "rftt"]

Output: "wertf"

Example 2:

Input: ["z", "x"]

Output: "zx"

Example 3:

Input: ["z", "x", "z"]

Output: ""

Explanation: The input contains a cycle, hence no valid character order can be derived.

Example
Input
["wrt", "wrf", "er", "ett", "rftt"]