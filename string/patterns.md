# String Patterns

## 1. KMP
- LPS array: longest proper prefix = suffix, for each index
- On mismatch, fall back to lps[idx-1] — never backtrack on text
- Period of string = n - lps[n-1]
- Use: substring search, counting occurrences, shortest repeating unit

## 2. Z-Algorithm
- z[i] = length of longest match starting at i with prefix of s
- Maintain Z-box [left, right]; if i ≤ right, reuse prior z values, then extend
- Pattern search: Z on "pat$text", look for z[i] == |pat|
- Use: pattern matching, string compression, distinct substrings

## 3. Rabin-Karp
- Rolling polynomial hash over a sliding window
- Double hash (two mod/base pairs) to reduce collision probability
- Prefix hash array gives O(1) substring hash queries
- **Gotcha**: hash(A) < hash(B) does NOT imply A < B lexicographically. Hashes only tell equal/not-equal — never ordering.
- Use: multi-pattern search, longest duplicate substring, wildcard matching

## 4. Manacher
- Insert separators → all palindromes become odd-length
- dp[i] = palindrome radius at center i
- If i ≤ right, mirror from 2*center - i, then expand
- Use: longest palindromic substring, count palindromic substrings

## 5. Suffix Array + LCP
- Suffix array: sorted indices of all suffixes — O(n log n) build
- LCP array (Kasai): longest common prefix between adjacent sorted suffixes — O(n)
- Distinct substrings = n(n+1)/2 - sum(lcp)
- Use: longest repeated substring, pattern search via binary search

## 6. Aho-Corasick
- Trie of all patterns + failure links (KMP generalized to a trie)
- Single pass over text matches all patterns simultaneously
- Use: multi-pattern dictionary matching, word break, DNA search

---

| Algorithm | Time | Space | Best For |
|-----------|------|-------|----------|
| KMP | O(n+m) | O(m) | single pattern |
| Z-Algo | O(n+m) | O(n+m) | single pattern, period |
| Rabin-Karp | O(n+m) avg | O(n) | multi-pattern, hashing |
| Manacher | O(n) | O(n) | palindromes |
| Suffix Array | O(n log n) | O(n) | substring queries |
| Aho-Corasick | O(n+Σ|p|) | O(Σ|p|) | multi-pattern simultaneous |

---

## 7. Suffix Automaton (SAM)
- Minimal DAG accepting all suffixes of a string — O(n) build
- Each node = equivalence class of substrings (same set of ending positions)
- suffix link → longest proper suffix that belongs to a different class
- Use: count distinct substrings, longest common substring of 2+ strings, substring occurrence count, smallest rotation

## 8. Palindromic Tree (Eertree)
- Two root nodes (odd-length, even-length), each node = unique palindromic substring
- suffix link → longest proper palindromic suffix
- O(n) build, at most n+2 nodes (at most n distinct palindromic substrings)
- Use: count distinct palindromes, palindrome frequency, series decomposition

## 9. Lyndon Factorization (Duval's Algorithm)
- Lyndon word: strictly smallest rotation of itself
- Any string has unique factorization into non-increasing Lyndon words — O(n) time, O(1) space
- Use: lexicographically smallest rotation, Burrows-Wheeler related, combinatorics on words

## 10. Suffix Tree
- Compressed trie of all suffixes — O(n) build (Ukkonen's)
- Every internal node = a repeated substring; leaves = suffixes
- Use: longest repeated substring, longest common substring, pattern matching with don't-cares, tandem repeats

## 11. String Hashing Tricks
- Polynomial hash with two large primes → compare substrings in O(1)
- Bidirectional hash (forward + reverse prefix hash) → O(1) palindrome check for any substring
- Hash on suffix array → O(log n) LCP via binary search + hash compare
- Use: online palindrome queries, longest common extension (LCE), approximate matching

## 12. Booth's Algorithm
- Find lexicographically smallest rotation in O(n) time, O(n) space
- Modified failure function approach (like KMP on doubled string)
- Use: canonical form of cyclic strings, necklace equivalence

## 13. Minimum Expression / Rotation
- Two-pointer comparison of s+s with itself, skip on mismatch
- O(n) to find starting index of lex-smallest rotation
- Use: canonical cyclic string comparison, isomorphism of circular sequences

## 14. Bitap (Shift-OR)
- Bit-parallel exact/approximate pattern matching
- Encode pattern as bitmasks per character, shift + OR per text char
- O(n * m/w) where w = word size (64) — fast for short patterns
- Use: fuzzy matching (≤k errors), agrep, fgrep internals

---

| Algorithm | Time | Space | Best For |
|-----------|------|-------|----------|
| Suffix Automaton | O(n) | O(n) | distinct substrings, occurrence count |
| Palindromic Tree | O(n) | O(n) | distinct palindromes, frequency |
| Lyndon / Duval | O(n) | O(1) | smallest rotation, factorization |
| Suffix Tree | O(n) | O(n) | all substring queries |
| Booth's | O(n) | O(n) | lex-smallest rotation |
| Bitap | O(n·m/w) | O(|Σ|) | fuzzy/approximate match |