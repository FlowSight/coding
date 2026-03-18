Design a class that supports the following operations:

find(): Find and return the smallest missing positive integer.
fill(): Fill in the smallest missing positive integer found previously and return that number.
delete(x): Delete the specified number x from the data structure.
The input data might be a collection of unordered positive integers, and the data structure should support dynamic additions and deletions. Examples and edge cases will include empty inputs and the minimum positive integer being 1. Design the data structure and implement these methods to achieve optimal performance. Assume constant time (amortized) for all operations.

Example:
Input: operation sequence ["insert", "find", "fill", "delete"] and parameters [[3, 4, -1, 1], [], [], [4]]
Output: The smallest missing number is 2, after fill the data becomes [3, 4, -1, 1, 2], and after deleting 4 the data is [3, -1, 1, 2]
Notes:
insert is not a public method but is a dataset given during class initialization.
Assume operations are conducted over a range from [0, 10^8] inclusive of all positive integers below that.
Example
Input
["insert", "find", "fill", "delete"] with parameters [[3, 4, -1, 1], [], [], [4]]