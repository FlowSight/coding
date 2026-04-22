Design a general-purpose weighted random generator that supports adding values with weights, and returns a value based on the weight proportionally. The probability of returning a value should be proportional to its weight.

Example:
If the current value-weight pairs are [1, 1], [2, 1], [5, 3], then the probabilities of 1 and 2 are 20% each, and 5 is 60%.
If you add [3, 5], then probabilities for 1 and 2 become 10% each, 5 becomes 30%, and 3 becomes 50%.
The focus should be on code clarity, maintainability, and extensibility rather than optimal performance.

Follow up
Add a method with expiry: addWithExpiry(value: T, weight: Int, expireAfterMs: Int).
Example
Input
add 1 1
add 2 1
add 5 3