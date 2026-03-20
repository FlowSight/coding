There is a board with N cells (numbered from 0 to N-1) arranged in a row. The board is described by an array points and a string tokens, both of length N. The k-th letter of the string tokens is either 'T' or 'E', indicating whether the k-th cell contains a token or is empty.

If the k-th cell contains a token, we score the number of points equal to points[k]. Additionally, we score another point for every pair of adjacent tokens. What is the total number of points we score?

that, given an array of integers points and a string tokens, both of length N, returns the total number of points scored.

** Can’t thank Rachel enough, as always **

Constraints:

Array points and string tokens are of the same length N;
N is an integer within the range [1..100];
Each element of array points is an integer within the range [1..1,000];
String tokens consists only of the characters 'E' and/or 'T'.
Example
Input
points = [3, 4, 5, 2, 3]
tokens = "TEETT"
Output
9