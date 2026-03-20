You are given an array A of length N, a starting index cur, and a distance D.

Your task is to iteratively update the array A starting from index cur. At each step, replace A[cur] with A[cur] + 1, then find the nearest index (left or right, within distance D) where this new value exists in the array.

If multiple indices exist at the same distance, choose the leftmost index. If no such index exists within distance D, keep the value in the same index and stop updating.

Function Description

Complete the function nearestValueReplacement in the editor.

nearestValueReplacement has the following parameters:

1. int[] A: an array of integers
2. int cur: the starting index
3. int D: the distance within which to search
Returns

int[]: the updated array

Example
Input
A = [1, 3, 2, 3, 4, 5, 2]
cur = 2
D = 2
Output
[1, 3, 3, 3, 4, 5, 2]