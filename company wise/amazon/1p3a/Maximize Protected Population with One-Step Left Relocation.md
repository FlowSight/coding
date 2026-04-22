You are given n cities arranged from left to right. City i (1-indexed) has population population[i] and a binary string unit of length n where:

unit[i] = '1' means city i initially has one security unit,
unit[i] = '0' means it has none.
You may relocate security units: for any city i > 1 with unit[i] = '1', that unit may optionally move to the immediate left neighbor city i-1. Each unit can be moved at most once (or stay).

After relocations, a city is protected if it has at least one security unit.

Compute the maximum possible total population of protected cities.

Suggested Input
Line 1: integer n
Line 2: n integers population[1..n]
Line 3: binary string unit (length n)
Output
One integer: the maximum protected population sum
Example
n = 5, population = [10,5,8,9,6], unit = "01101" → output 27

Constraints (typical)
1 <= n <= 2e5
0 <= population[i] <= 1e9
Example
Input
5
10 5 8 9 6
01101
Output
27