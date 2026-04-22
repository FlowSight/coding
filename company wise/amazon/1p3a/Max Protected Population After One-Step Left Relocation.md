Given an array population of length n (population of each city) and a binary string unit of the same length:

unit[i] = '1' means city i currently has one security unit; '0' means none.
Relocation rule: for any i > 1, the unit in city i may be moved one step left to city i-1.
Each unit can be moved at most once; units in city 1 cannot move further left.
If moved, city i loses the unit and city i-1 gains it.
A city is protected if it has a unit after all relocations. The protected population is the sum of population[i] over protected cities.

Return the maximum protected population achievable by relocating units optimally.

Constraints

1 ≤ n ≤ 1e5
1 ≤ population[i] ≤ 1e4
unit consists only of '0' and '1'
Example

population = [10, 5, 8, 9, 6]
unit = "01101"
Move the unit at index 2 left to get 10101, then move the unit at index 5 left to get 10110. Protected cities are 1, 3, 4 with sum 10+8+9=27, so output 27.

Sample 0

Input: population = [20,10,9,30,20,19], unit = "011011"
Output: 80
Sample 1

Input: population = [5,4,5,1], unit = "0111"
Output: 14
Example
Input
5
10 5 8 9 6
01101
Output
27