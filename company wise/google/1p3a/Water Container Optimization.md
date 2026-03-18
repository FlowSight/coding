There are several buckets, each with a fixed capacity c. Design a distribution to use the minimum number of buckets and minimize the maximum water amount any bucket holds. Implement a function optimize_containers(volumes, c), where volumes is a list of water amounts to be distributed. The function returns an integer indicating the number of buckets used.

Input:
List of integers volumes, representing water amounts to be distributed.
An integer c, the capacity of each bucket.
Output:
An integer, the minimum number of buckets used.
Example:
Input: volumes = [4, 8, 3, 1], c = 5
Output: 6
Constraints:
Length of volumes is up to 10,000.
Each volume is up to 1,000,000,000.
1 <= c <= 1,000,000,000.
Example
Input
4, 8, 3, 1; 5