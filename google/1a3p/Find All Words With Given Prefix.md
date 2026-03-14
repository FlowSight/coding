Given a dictionary words consisting of distinct lowercase English words and a prefix string prefix, return all words that start with prefix.

Requirements:

Return the result sorted in lexicographical order.
Return an empty list if no word matches.
Constraints:

1 <= len(words) <= 2 * 10^5
1 <= len(words[i]) <= 50
1 <= len(prefix) <= 50
All characters are in 'a'-'z'
Examples:

Input: words = ["apple","app","ape","bat"], prefix = "ap" -> Output: ["ape","app","apple"]
Input: words = ["dog","cat"], prefix = "z" -> Output: []
Example
Input
4
apple
app
ape
bat
ap
Output
ape app apple