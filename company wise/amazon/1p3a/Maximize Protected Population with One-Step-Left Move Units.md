There are n cities in a line, indexed 1..n. City i has population population[i].

You are also given an array unit[i] of length n (0/1), where unit[i] = 1 means city i initially has exactly one security unit, otherwise none.

You may reassign units under the following rules:

Each security unit can move at most one step to the left (from city i to city i-1), or stay.
Each unit can be moved at most once.
A unit in city 1 cannot move left.
A city is considered protected if it ends up with at least one unit (extra units do not increase the protected value).
Goal: maximize the sum of populations of protected cities after moving/staying units under the rules.

Input (stdin)
Line 1: integer n
Line 2: n integers population[1..n]
Line 3: n integers unit[1..n] (0/1)
Output (stdout)
One integer: the maximum possible protected population sum
Constraints
1 <= n <= 2e5
0 <= population[i] <= 1e9
unit[i] ∈ {0,1}
Example
Input:

5
10 5 7 6 12
0 1 0 1 0
Output:

23
Example
Input
5
10 5 7 6 12
0 1 0 1 0
Output
23