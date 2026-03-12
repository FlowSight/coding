A sequence is considered harmonious if it can be divided into a series of groups, and each group starts with a number that indicates the number of items in that group, followed by exactly that many items.

For example, the sequence [3, 7, 2, 6, 2, 4, 4] is harmonious because it can be divided into two groups: [3, 7, 2, 6] and [2, 4, 4]. The first group begins with the number 3, indicating 3 elements following it. The second group begins with the number 2, indicating 2 elements following it.

Similarly, the sequence [1, 8, 4, 5, 2, 6, 1] is harmonious, as it can be divided into groups [1, 8] and [4, 5, 2, 6, 1] that satisfy the criteria.

However, the sequence [3, 2, 1] is not harmonious.

An empty sequence is harmonious.

You are given a sequence of integers A of length N. In one operation, you can remove any element from the sequence. What is the minimum number of operations required to make the sequence harmonious?

Input

The input to the solution function consists of:

A single integer N (1 ≤ N ≤ 200,000) the length of the sequence A.
A sequence of N integers A1, A2, A3...An (1 ≤ Ai ≤ 100,000) the elements of the sequence A.
Output

Return the answer, which is the minimum number of operations required to make the sequence harmonious.

Constraints: N/A

Example
Input
A = [3, 4, 1, 6, 7, 7]
Output
1