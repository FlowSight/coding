Minimum Cost to Cover Desired Items (Bitmask DP)
You are given a list of bundles. Each bundle contains some food items (strings) and has a positive cost. You also have a desired list want. You may purchase any subset of bundles (assume each bundle can be bought at most once). Your goal is to cover all items in want (you may get extra items). Return the minimum total cost to cover want, or -1 if impossible.

Input
bundles[i]: items contained in bundle i
cost[i]: cost of bundle i
want: distinct desired items
Output
Minimum total cost to cover all desired items, or -1.
Constraints
1 <= len(want) <= 20
1 <= len(bundles) <= 200
1 <= cost[i] <= 1e9
Example
bundles = [["a","b","c"], ["d","e"], ["a","c"]], cost = [5,2,1], want = ["a","c","d"]. Buy bundle 2 and 3: 2 + 1 = 3 → output 3.

11101
Sample Tests
(See Chinese section for 5 tests.)

Example
Input
bundles=[[a,b,c],[d,e],[a,c]]
cost=[5,2,1]
want=[a,c,d]
Output
3