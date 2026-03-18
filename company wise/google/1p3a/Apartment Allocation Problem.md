Given a list of N apartments and M applicants, each applicant has their own preference score for each apartment. The goal is to maximize the total preference score of each applicant. Design an algorithm to complete the allocation such that the total preference score of all applicants is maximized.

Input:

A 2D integer array preferences where preferences[i][j] indicates the preference score of applicant i for apartment j.
Output:

An integer representing the maximum total preference score of all applicants.
Example:

Input:

[[7, 5, 9],
 [8, 6, 4],
 [5, 8, 7]]
Output:

24
Constraints:

1 <= N, M <= 1000
Each preferences[i][j] is between 0 and 1000.
Example
Input
[[7, 5, 9], [8, 6, 4], [5, 8, 7]]