Design a data structure to implement an LRU (Least Recently Used) cache, supporting the following operations: retrieving data from the cache, writing data into the cache, and removing data from the cache. Note that each time you access the cache, that data should be considered as recently used. Ensure that retrieval, insertion, and deletion operations have O(1) time complexity. Provide class constructor, get, put, and delete methods implementation with a set of test cases.

Example
Input
2
put 1 1
put 2 2
get 1
put 3 3
get 2
put 4 4
get 1
get 3
get 4