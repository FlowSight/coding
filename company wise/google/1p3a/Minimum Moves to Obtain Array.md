You begin with an array filled with N zeros and you want to obtain an array A.

In one move, you can choose an arbitrary interval and increase all the elements within that interval by 1. For example, you can transform [0, 0, 0, 0] into [0, 1, 1, 1, 0] in a single move. However, you need three moves to obtain [1, 0, 1, 2, 2]. One possible sequence of moves is: [0, 0, 0, 0, 0] → [0, 0, 1, 1, 1] → [0, 0, 1, 2, 2] → [1, 0, 1, 2, 2], where → denotes a single move.

What is the minimum number of moves needed to obtain A, starting from a zero-filled array?

Function Description

Write a function solution.

The function is expected to return an integer, the minimum number of moves needed to transform a zero-filled array into A.

solution has the following parameter:

int[] A: an array of integers
Memo On the source image it says the question is an "exercise", I've never done Google assessment before, so I am not sure if it is just a warm up exercie before the actual test.

Constraints: :)

Example
Input
A = [2, 1, 3]
Output
4