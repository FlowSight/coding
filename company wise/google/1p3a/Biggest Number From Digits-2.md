There is an array, named 'digits', consisting of N digits. Choose at most three digits (not necessarily adjacent) and merge them into a new integer without changing the order of the digits. What is the biggest number that can be obtained this way?

Write a function:

biggestNumberFromDigits

that, given an array of N digits, returns the biggest number that can be built.

Examples:

Given digits = [7, 2, 3, 3, 4, 9], the function should return 749.
Given digits = [0, 0, 5, 7], the function should return 57.
Assume that:

N is an integer within the range [3..50];
each element of array named 'digits', is an integer within the range [0..9].
In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.

Memo On the source image it says the question is an "exercise", I've never done Google assessment before, so I am not sure if it is just a warm up exercie before the actual test.

Constraints:

N is an integer within the range [3..50].
Each element of array named 'digits', is an integer within the range [0..9].
Example
Input
digits = [7, 2, 3, 3, 4, 9]
Output
749