Fixed-Width Text Formatting (Multi-Column Follow-up)
Given a text string text (a sequence of words separated by spaces) and a positive integer width, format the text into multiple lines such that each line has exactly width characters.

Rules
Keep the original word order.
Put as many words as possible on each line (greedy left-to-right packing).
Separate adjacent words by at least one space.
After placing as many words as possible, if the line length is less than width, pad trailing spaces to reach length width (left-aligned).
Each word length is guaranteed to be <= width.
Output
Return/print the formatted lines (each line is a string). Examples may show lines wrapped with | only to visualize trailing spaces (the real output does not include |).

Follow-up: Multi-Column Layout
If a column count k is given (e.g., 2 or 3 columns), first generate all single-column lines using the rules above, then lay them out into k columns:

Each column width is width
Columns are separated by exactly 1 space
Output final rows by concatenating row i from each column; if a column runs out of lines, use an all-space line of length width.
Constraints
Number of words n: 1 ≤ n ≤ 1e5
1 ≤ width ≤ 100
1 ≤ k ≤ 5 (follow-up)
Sample Tests (single-column)
Input
text = "this is a article"
width = 10
Output

this is a 
article    
Input
text = "a b c d e"
width = 3
Output

a b
c d
e  
Input
text = "hello"
width = 5
Output

hello
Input
text = "aa bb ccc"
width = 4
Output

aa  
bb  
ccc 
Input
text = "one two three four"
width = 8
Output

one two 
three   
four    
Example
Input
this is a article
10
Output
this is a 
article    