Design a prototype for a friend recommendation system for a social media platform.

You have n users labeled from 1 to n, and m friendships represented as a 2D array called friendships. Each entry friendship[i] is a connection between users friendship[i][0] and friendship[i][1]. For any user y, another user x is recommended as a friend if x and y are not currently friends and have the highest number of mutual friends (friends in common). In case of ties (multiple users x with the same number of mutual friends), recommend the user with the smallest index. Given n and friendships, determine the friend recommendation for each user from 1 to n. If no recommendation can be made, return -1 for that user.

Constraints:

n <= 10^5
m <= 2.5 * 10^5
Each user has at most 15 friends.
Example
Input
n = 3
m = 2
friendships = [[0, 1], [0, 2]]
Output
[-1, 2, 1]