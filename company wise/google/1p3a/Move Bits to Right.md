An engineer is tasked with developing an integrated binary circuit that processes an input binary string ( s ). This binary string, which consists solely of 0s and 1s, needs to be rearranged so that all 1s are moved to the end of the string. For example, the string "01010" should be transformed into "00011".

To achieve this, the engineer can perform a series of operations where any "1" from the string can be moved to the right. The operation cost is defined as ( 1 + ) the number of positions the "1" is moved. For instance, in the string "100010", moving the first "1" three positions to the right costs ( 1 + 3 = 4 ). Each "1" must be moved as far to the right as possible during the operation.

Given a binary string ( s ), determine the maximum total cost of operations required to segregate the string so that all 1s are at the end.

Constraints: ``

Example
Input
s = "110100"
Output
13