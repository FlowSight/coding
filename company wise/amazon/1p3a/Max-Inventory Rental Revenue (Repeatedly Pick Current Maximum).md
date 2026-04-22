Problem: Max-Inventory Rental Revenue (Repeatedly Pick Current Maximum)
There are n VM types with initial inventories a[i] (non-negative integers). There are m customer requests processed sequentially.

For each request:

Pick the VM type with the current maximum inventory (ties can be broken arbitrarily).
The revenue of this request equals that VM type’s current inventory x.
After renting, its inventory decreases by 1 (becomes x-1; if x=0, it cannot be selected).
Compute the total revenue after processing m requests.

Input
Line 1: two integers n m
Line 2: n integers a[1..n]
Output
One integer: total revenue (use 64-bit).
Constraints
1 ≤ n ≤ 2e5
0 ≤ a[i] ≤ 1e9
0 ≤ m ≤ 1e9
Example
Input:

3 4
2 5 1
Output:

14
Explanation: pick inventories 5,4,3,2, revenue 5+4+3+2=14.

Example
Input
3 4
2 5 1
Output
14