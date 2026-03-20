You are given an array A of N integers. You can split the array into two non-empty parts, left and right, sort the elements in each part independently and join them back together.

For example, given array A = [1, 3, 2, 4], you can split it in the following three ways:

left = [1], right = [3, 2, 4]. Sorting the elements and joining the parts back together results in the array: [1, 2, 3, 4].
left = [1, 3], right = [2, 4]. Resulting sorted and rejoined array: [1, 3, 2, 4].
left = [1, 3, 2], right = [4]. Resulting sorted and rejoined array: [1, 2, 3, 4].
Your task is to find the number of ways of splitting the array into two parts such that, after sorting the two parts and rejoining them into a single array, the resulting array will be sorted in non-decreasing order. For the array shown above, the answer is 2: the first and third splits result in a sorted array.

Function Description

Write a function:

class Solution { public int solution(int[] A); }

which, given an array A of length N, returns the number of different ways of obtaining a sorted array by applying the procedure described above.

Example
Input
A = [1, 3, 2, 4]
Output
2