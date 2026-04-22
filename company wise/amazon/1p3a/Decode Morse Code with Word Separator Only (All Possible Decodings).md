Problem: Decode Morse Code with Word Separator Only (Return All Possible Decodings)
You are given a string s representing a Morse-code message.

s contains only ., -, and a word separator string word_sep.
word_sep splits s into word segments. Inside each word segment, there is no character separator.
You are given a mapping morse_to_char from a Morse token (e.g. ".-") to its decoded character (e.g. "A").
For each word segment, you must partition it into consecutive substrings, where each substring is a key in morse_to_char, then map each to a character to form a decoded word.

Because there is no character separator, the partitioning may be non-unique. Return all possible fully decoded sentences:

Words in a sentence are joined with a single space.
Return a deduplicated list (or set) of all possible sentences; order does not matter.
Constraints
1 <= len(s) <= 1e4
number of words <= 200
morse_to_char is constant-sized (e.g., standard Morse alphabet)
the output can be very large; return all results as required
Example (illustrative)
Assume morse_to_char includes "."->"E", ".."->"I", "-"->"T".

Input: s = "..", word_sep = " / "
Possible output: ["I", "EE"]
Example
Input
s=..
word_sep= / 
# mapping includes '.'->E, '..'->I
Output
I
EE