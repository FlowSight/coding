iven a string s. You may pick some characters from s (preserving relative order, not necessarily contiguous) to form a subsequence t.

Determine whether for every subsequence t of s with length >= 3, there exists a permutation (rearrangement) of t that forms a valid English word.

Equivalently, for each such t, there exists a dictionary word w such that t and w are anagrams (same multiset of characters).

Return true if the condition holds for all length-≥3 subsequences, otherwise return false.

Assume an oracle isWord() exists, or a dictionary set is provided (clarify in interview).

I/O (suggested)
Input: one line string s
Output: true or false
Constraints
1 <= |s| <= N (unspecified)
Sample tests
Input: eat -> true
Input: abcd -> typically false
Input: aetx -> depends on dictionary
Input: aaa -> depends on whether a 3-'a' word exists
Input: abca -> must hold for every length≥3 subsequence's character multiset
Example
Input
eat
Output
true