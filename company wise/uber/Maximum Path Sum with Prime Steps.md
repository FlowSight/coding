Given an integer array, you can jump from the start of the array to the end. Each jump can be either 1 step or a prime number of steps ending with the digit 3. When you jump to a step, you gain the array value at that position. Your goal is to find a jump sequence that maximizes the sum at the end.

Input
An integer array nums of length n, where 1 <= n <= 10^5 and -10^4 <= nums[i] <= 10^4.
Output
The maximum possible sum along the path.
Example
Input: nums = [3, 4, 2, 10, 8]
Output: 20
Explanation: Jump from the first element to the second (1 step) to update the sum to 4; then, jump 4 steps to the last element to update the sum to 20.
Note
Prime numbers ending with the digit 3 include: 3, 13, 23, 43, 53, 73, 83, etc.
Example
Input
3 4 2 10 8