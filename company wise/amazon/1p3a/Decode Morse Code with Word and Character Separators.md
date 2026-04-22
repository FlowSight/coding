Problem: Decode Morse Code with Word and Character Separators
You are given a string s representing a Morse-code message.

Each letter is encoded as a sequence of . and -.
Letters are separated by a character separator string char_sep.
Words are separated by a word separator string word_sep.
You are also given a mapping morse_to_char from a Morse token (e.g. ".-") to its decoded character (e.g. "A"). The separators in s are used consistently.
Decode s into plain text:

Split into words using word_sep.
For each word, split into Morse tokens using char_sep.
Each token must exist in morse_to_char.
Join decoded words with a single space.
Constraints
1 <= len(s) <= 1e5
total number of tokens <= 1e5
morse_to_char is constant-sized (e.g., standard Morse alphabet)
Example
Input: s = ".... . .-.. .-.. --- / .-- --- .-. .-.. -..", char_sep = " ", word_sep = " / "
Output: "HELLO WORLD"
Example
Input
s=.... . .-.. .-.. --- / .-- --- .-. .-.. -..
char_sep= 
word_sep= / 
# morse_to_char=standard
Output
HELLO WORLD