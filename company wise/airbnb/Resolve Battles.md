The input is a list of strings, each describing the action of an army. For example:

'A Munich Hold' means Army A is stationed in Munich and does not move.

'B Warsaw Support A' means Army B, located in Warsaw, provides support to Army A, increasing its strength. In this case, Army A's strength becomes 2.

'C Bohemia Move Munich' means Army C, located in Bohemia, is attacking Munich.

In this scenario, Army C has a strength of 1, and Army A has a strength of 2 (due to support from Army B). As a result, Army C loses, and Army A successfully defends Munich.

If multiple armies in the same location have equal strength, they all lose.

If an army is providing support but gets attacked itself (meaning another army moves into its location), its support becomes invalid.

The function needs to return a list of strings, each describing the final state of every army. For example, in the above scenario, the output would be:

['A Munich', 'B Warsaw', 'C [dead]'].

Constraints: TO-DO

Example
Input
actions = ["A Munich Hold", "B Warsaw Support A", "C Bohemia Move Munich"]
Output
["A Munich", "B Warsaw", "C [dead]"]