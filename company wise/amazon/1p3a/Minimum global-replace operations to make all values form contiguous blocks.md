Problem: Minimum global replace operations to make values form contiguous blocks
Given an integer array a of length n.

You may perform the following operation any number of times:

Choose two values x and y, and replace all occurrences of x in the array with y (a global replace).
An array is contiguous (block-wise by value) if:

For every distinct value v in the array, all indices where a[i] == v form one continuous interval (i.e., v appears in exactly one block and is never split as v ... non-v ... v).
Compute the minimum number of operations required to make a contiguous.

Input format (recommended)
Line 1: integer n
Line 2: n integers representing a
Output format
Print one integer: the minimum number of operations.
Constraints (typical OA completion if not provided)
1 <= n <= 2e5
a[i] fits in 32-bit signed integer (you may compress values)
Sample tests (stdin/stdout)
input:

7
1 2 1 2 3 3 3
output:

1
input:

5
1 1 2 2 3
output:

0
input:

6
1 2 1 3 2 3
output:

2
input:

1
42
output:

0
input:

8
5 1 5 5 2 1 2 2
output:

2
Example
Input
7
1 2 1 2 3 3 3
Output
1