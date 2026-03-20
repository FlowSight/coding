Hi! The outputs are just placeholders. This problem is here to give you a glimpse of what a Google interviewer asked in one of their phone screens today. And today is 03-27-2025

We are given a grid of size N*M having characters "#", "" (empty space), and any English lowercase alphabet letter.

"#": Filled
"": Empty
Any English alphabet letter
We are also given a string word. We have to find if we can fit this word in the grid either by directly matching with English alphabet letters or using the empty spaces (by filling them with matching characters). The word should match exactly, and no empty space should be left before and after. We can have the word match from left to right and top to bottom only.

Example
Input
grid = [['#', '#', '#', '#'], ['L', '_', '#', ' '], ['A', 'L', 'A', '_'], ['#', 'X', '#', '_']]
word = "ALA"
Output
0