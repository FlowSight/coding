There are n cities indexed from 1..n (left to right). You are given an array population[i] for each city.

You are also given a binary string unit of length n:

unit[i] = '1' means there is initially one guard unit in city i.
unit[i] = '0' means there is no guard in city i.
You may move each guard unit at most once under the rules:

A guard can only move one step to the left (from i to i-1).
Guards cannot move out of bounds (a guard at city 1 cannot move left).
Each guard can be moved at most once; it may also stay.
After all moves, any city that ends up with at least one guard is considered protected, and its population is counted.

Return the maximum total protected population achievable.

Input (stdin)
Line 1: integer n Line 2: n integers population[1..n] Line 3: string unit

Output (stdout)
One line: maximum protected population

Constraints
Not provided; assume n up to 2e5.

Example
Input
5
10 5 8 9 6
01101
Output
(depends on official statement)