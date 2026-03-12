Given an integer list scores and an integer K, two people will alternate turns taking K elements from the list. Person A always chooses the sum of the top K scores remaining. Person B always chooses the sum of the K scores with the largest digit sum. They take turns until no elements are left. Calculate the final score sums for each person and return a tuple representing the scores of A and B.

Example
Input
[10, 20, 30, 40, 50]
2