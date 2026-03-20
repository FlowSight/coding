Given two arrays 'points' and 'tokens', the 'tokens' array contains characters 'T' or 'E'. If 'T' appears in 'tokens', add the value from the 'points' array at the corresponding index. Additionally, if two consecutive 'T's ('TT') are found, increment the total score by 1. Compute the final score. The input consists of two arrays 'points' and 'tokens', and the output is an integer representing the total score.

Example:

Input: points = [3, 9, 10], tokens = ['T', 'E', 'T']

Output: 13

Explanation: Add 3 (1st 'T'), skip 9 ('E'), add 10 (2nd 'T'), no consecutive 'TT', thus the total score is 13.

Example
Input
points = [1,2,3]
tokens = ['T','T','T']