You have N ranges where the i-th range is from low[i] to high[i]. You need to create an array brr of length N. However, brr[i] can only be any prime number such that low[i] <= brr[i] <= high[i] for all possible i.

As we know there can be multiple ways to create brr. It is given that the score of an array is the multiplication of all values in it.

Your task is to find the sum of the score of all possible unique permutations of brr. Since the answer can be very large, return the answer modulo 10^9+7.

Note:

It is guaranteed that there will be at least one element in brr[i], which means there will always be a prime number between low[i] and high[i].
low[i] <= high[i] for all possible i (1 <= i <= N).
Constraints:

1 <= N <= 10^5
1 <= low[i], high[i] <= 10^6
Example
Input
low = [1, 3]
high = [3, 5]
Output
40