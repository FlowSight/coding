Design a rules engine to map input binary signals to specific configuration values. The system maintains a pattern list, each associated with a value.

Input Description
Configuration Phase (Build/Pre-process):
Given a list List<Pair<String, Integer>> patterns.
Key (Pattern): A string composed of 0, 1, * characters.
Value: An integer representing a classification ID, weight, or action.
Query Phase (Query):
Given a binary string input, which only includes 0 and 1.
Symbol Definitions
0: Matches character 0.
1: Matches character 1.
*: Wildcard that matches any length (including zero) of any binary sequence.
Note: Equivalent to * in Shell/Glob or .* in Regex.
.: Can match any single character.
Objective
Implement the match(input) function that finds the matching Pattern for the input and returns its corresponding Value.

Example
Input
List<Pair<String, Integer>> patterns = {('1*0', 5), ('*10', 10)}; input = '110';
Output
10