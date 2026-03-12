You are given a list of house positions in a district, where each house is located at a distinct position along a straight line. Houses that are next to each other without any gaps between them are considered part of the same segment. Your task is to determine how many segments of consecutive houses remain after removing houses according to a series of queries.

Each query removes a house from the district, and after each removal, you need to calculate the number of segments of consecutive houses that remain.

Input:

houses: A list of integers representing the positions of the houses in the district.

queries: A list of integers representing the positions of the houses to be removed. Each query removes one house from the district.

Output:

For each query, return the number of segments of consecutive houses remaining after the corresponding house is removed.

**ᯓᡣspike is the G.O.A.T ᨒ ོ **

Constraints:

The number of houses, n, is at most 10^5.
The number of queries, q, is at most 10^5.
All positions in the house list and queries list are distinct integers.
Example
Input
houses = [1, 2, 3, 6, 7, 9]
queries = [6, 3, 1]
Output
[3, 2, 2]