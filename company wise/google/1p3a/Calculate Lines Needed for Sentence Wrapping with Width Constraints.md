Given a list of sentences and a document width, calculate how many lines can be filled with these sentences. The following rules must be observed:

If the remaining space in the current line is not enough for the next word, move that word to the next line without splitting it.
If the width is too narrow, words can be split across lines.
Example:

Input: sentences = ["Hello world", "This is a test"], width = 10 Output: integer indicating the number of lines

Example
Input
["Hello world", "This is a test"] 10