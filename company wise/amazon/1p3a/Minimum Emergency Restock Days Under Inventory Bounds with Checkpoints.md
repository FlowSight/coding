You manage an inventory system with capacity max_products.

You are given an integer array task of length n, where task[i] is the net inventory change at the end of day i (positive = incoming, negative = outgoing). You may choose to perform an "emergency restock" on some days; a restock happens at the beginning of that day and instantly sets inventory to max_products (that day counts as one restock day).

Constraints:

Inventory must never exceed max_products at any time.
Only on days with task[i] == 0, the end-of-day inventory must be non-negative (inventory_end >= 0). On other days, inventory is allowed to go negative.
Given initial inventory init (inventory at the beginning of day 0), compute the minimum number of emergency restock days required.

Input

Line 1: integer n
Line 2: n integers task[i]
Line 3: integer init
Line 4: integer max_products
Output

The minimum number of restock days
Constraints (assumed)

1 <= n <= 2e5
-1e9 <= task[i] <= 1e9
0 <= init <= max_products <= 1e9
Example Input:

6
-3 -3 0 -2 5 0
2
10
Output:

1
Example
Input
6
-3 -3 0 -2 5 0
2
10
Output
1