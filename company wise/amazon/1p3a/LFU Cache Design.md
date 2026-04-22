Design a LFU Cache and implement the following operations: get(key) - Retrieve the value associated with the key if it exists, otherwise return -1. put(key, value) - Update the value of the key if it exists. If it does not exist, insert the key-value pair. When the cache reaches its capacity, it should remove the least frequently used entry before inserting a new one. The operations should follow the LFU (Least Frequently Used) strategy.

Example
Input
2
put 1 1
put 2 2
get 1
put 3 3
get 2
get 3
put 4 4
get 1
get 3
get 4