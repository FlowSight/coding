Given a string s. You may pick some characters from s (preserving relative order, not necessarily contiguous) to form a subsequence.

A subsequence is considered “valid” if:

its length len >= 3, and
it is a valid English word.
Determine whether all subsequences of s with length >= 3 are valid English words.

Implement and return a boolean: return true if all such subsequences are valid, otherwise return false.

You may assume there is an oracle function isWord(t: str) -> bool that returns whether t is a valid English word.

I/O (suggested)
Input: one line string s
Output: true or false
Constraints
1 <= |s| <= N (exact N unspecified; discuss complexity assumptions)
Sample tests
Input: abc Output: depends on isWord("abc")
Input: abcd Output: must have isWord("abc"), isWord("abd"), isWord("acd"), isWord("bcd"), isWord("abcd"), etc. all true
Input: aab Output: true (if there is no subsequence of length ≥ 3; confirm with interviewer)
Input: aaaa Output: depends on isWord("aaa") and isWord("aaaa")
Input: xyzpq Output: typically false
Example
Input
abc
Output
(depends on isWord("abc"))