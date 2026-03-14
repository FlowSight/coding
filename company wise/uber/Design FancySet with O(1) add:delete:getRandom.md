Design (Data Structure)
Design a data structure FancySet that supports the following operations in amortized O(1) time:

add(x): Insert integer x into the set. Return false if x already exists; otherwise insert and return true.
delete(x): Remove integer x from the set. Return false if x does not exist; otherwise remove and return true.
getRandom(): Return a uniformly random element from the current set. Define clearly what happens if the set is empty (e.g., throw, return sentinel), and be prepared to justify it.
Requirements
add / delete / getRandom must all be amortized O(1).
The behavior of getRandom() on an empty set must be explicitly defined.
Handle edge cases such as:
removing the last element
updating index mappings after deletion
repeated inserts / deleting non-existing elements
Extension discussion:
How would you make it thread-safe under concurrent access (multi-threaded calls to add/delete/getRandom)? Provide at least two locking strategies (e.g., global lock vs. striped/fine-grained locks) and discuss trade-offs.
Constraints (reasonable for interview)
Number of operations: 1 <= Q <= 2*10^5
Value range: 32-bit signed integer
Example
add(1) -> true
add(2) -> true
add(1) -> false
getRandom() -> 1 or 2 (50% each)
delete(1) -> true
getRandom() -> 2
Example
Input
add 1
add 2
add 1
getRandom
delete 1
getRandom
Output
true
true
false
1|2
true
2