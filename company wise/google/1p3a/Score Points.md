There is a board with N cells (numbered from 0 to N-1) arranged in a row. The board is described by an array points and a string tokens, both of length N. The K-th cell of the string tokens is either 'T' or 'E', indicating whether the K-th cell contains a token or is empty.

If the K-th cell contains a token, we assign the number of points equal to points[K]. Additionally, we score another for every pair of adjacent tokens. The goal is the total number of points we score?

** ོBig shoutout to Aura Man for all the support! **

Constraints:

array points and string tokens are of the same length N;
N is an integer within [1, 100];
each element of array points is an integer within the range [1, 1,000];
string tokens consists only of the characters 'E' and/or 'T'.
Example
Input
points = [3, 4, 5, 2, 3]
tokens = "TEETT"
Output
9