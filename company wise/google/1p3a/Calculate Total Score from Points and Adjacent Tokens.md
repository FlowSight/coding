Score Adjacent Tokens
Given a new row of N cells numbered from 0 to N-1. The row is described by an integer array points, of length N. A string tokens, of length N, with each character 'T' or 'E', indicates whether the K-th cell contains a token. Every pair of adjacent cells has a total score, which includes tokens, and the number of adjacent point pairs we score. Additionally, for every pair of adjacent points, score 2. If a token is there, an additional 1 is scored. Return the total number of points we score.

Examples
Input: points = [3, 2, 4], tokens = "TEET"

Explanation: Score includes 3 + 2 + 4 and tokens = 5. Thus, adjacent cell scores are: 3 + 2 = 5, 2 + 4 = 6. The function should return 11.
Input: points = [2, 2, 2], tokens = "ETTE"

Explanation: Score includes 2, 2, 2 and score 2 for each adjacent pair. The function should return 11.
Assume:

points and tokens lengths are both N.
Example
Input
3
3 2 4
TEET