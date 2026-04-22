Design and implement a Layer class that supports the following operations:

put(key, value): Store a key-value pair.
get(key): Retrieve the current value of the key, or return null if the key does not exist.
commit_batch(): Make the current stored key-value pairs a permanent state, ignoring all previous intermediate states.
get_state(): Get the latest stored state.
Test your implementation with the following example test case:

Input: ["Layer", "put", "put", "commit_batch", "get", "put", "get", "commit_batch", "get"]
Arguments: [[], [key1, value1], [key2, value2], [], [key1], [key1, newValue1], [key1], [], [key1]]
Output: [null, null, null, null, "value1", null, "newValue1", null, "newValue1"]
Data Constraints:

The solution should be efficient and memory-conservative even with a large number of inputs, assuming up to 10,000 operations, with each key and value length not exceeding 100.

Requires a performance and memory usage optimized solution.

Example
Input
Layer
put key1 value1
put key2 value2
commit_batch
get key1
put key1 newValue1
get key1
commit_batch
get key1n