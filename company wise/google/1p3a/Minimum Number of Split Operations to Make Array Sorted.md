You're optimizing video chunks for streaming. Each chunk has a size represented in a 0-indexed array nums. To ensure smooth playback, chunk sizes must be in non-decreasing order.

You can split any chunk into two smaller chunks whose sizes add up to the original.

For example, if nums = [10,5,8], you can split 10 into [4,6] making it [4,6,5,8].

Return the minimum number of split operations needed to make the array sorted in non-decreasing order.

The candidate was able to come up with an O(n^2) solution within 15 minutes but was asked to improve it to O(n), which they couldn't achieve.

Example
Input
nums = [10, 5, 8]
Output
1