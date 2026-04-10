Problem: Mouse and Cheese
Two mice and n pieces of cheese. For cheese i:

Mouse 1 gets reward1[i]
Mouse 2 gets reward2[i]
Mouse 1 must eat exactly k cheeses; the remaining n-k are eaten by mouse 2.

Compute the maximum possible total reward.

Input
Line 1: integers n and k
Line 2: n integers reward1[i]
Line 3: n integers reward2[i]
Output
One integer: the maximum total reward.

Constraints
1 <= n <= 2 * 10^5
0 <= k <= n
0 <= reward1[i], reward2[i] <= 10^9
O(n log n) is acceptable
Test cases
Example
Input
4 2
1 1 3 4
4 4 1 1
Output
15