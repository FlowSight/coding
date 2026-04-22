Problem: Morse Code Encoder/Decoder (4 incremental parts)
You are given a mapping from characters to Morse code (e.g., A -> .-, B -> -..., etc.). Implement a Morse code codec in the following 4 parts.

Part 1: Basic Encoding (text → morse)
Encode an uppercase English string s into Morse code.

Input: string s (only A-Z)
Output: morse string m
Rule: separate letters with a single space (e.g., "AB" -> ".- -...").
Part 2: Basic Decoding (morse → text, with separators)
Decode a space-separated Morse string back into text.

Input: morse string m (letters separated by a single space)
Output: decoded string s
Part 3: No-separator decoding with dictionary constraint (recover a word)
Given a continuous Morse string m (no spaces) and a dictionary of words (A-Z only).

Task: find any word w in dictionary such that its Morse encoding (concatenated without spaces) equals m.
Input: continuous morse string m, dictionary dictionary
Output: any valid word w, or empty/None if impossible.
Part 4: No-separator decoding into multiple words (enumerate all sequences)
Given a continuous Morse string m and a dictionary dictionary.

Task: split m into segments, where each segment equals the full concatenated encoding of some dictionary word.
Output: all possible sequences of words that concatenate to exactly m.
Requirements
Multiple words may map to the same morse pattern; Part 4 must enumerate all combinations.
Use backtracking/DFS for Part 4 and preprocess the dictionary into a morse_pattern -> set(words) map for fast lookup.
Typical constraints
|m| up to ~1e3 (may need pruning/memoization)
|dictionary| from 1e3 to 1e5 depending on preprocessing
Example
Input
PART=1
S=ABC
Output
.- -... -.-.