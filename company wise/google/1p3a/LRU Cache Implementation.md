mplement an LRU (Least Recently Used) Cache class. The constructor takes the maximum capacity of the cache as a parameter. Implement two methods: get(key) and put(key, value) with the following requirements:

When the cache reaches its maximum capacity, it should remove the least recently used item before inserting a new item.
get(key): Return the value of the key if the key exists in the cache (always positive), otherwise return -1.
put(key, value): Write the data value if the key does not exist. When the cache reaches maximum capacity, it should remove the least recently used data to make space for the new value.
Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 10^4
At most 3 * 10^4 calls will be made to get and put.
Test Cases:

Input: put(1, 1), put(2, 2), get(1), put(3, 3), get(2), put(4, 4), get(1), get(3), get(4) Output: 1, -1, -1, 3, 4
Input: put(2, 1), put(2, 2), get(2), put(1, 1), put(4, 1), get(2) Output: 2, -1
Input: put(1, 1), get(1), put(2, 2), get(1), get(2) Output: 1, 1, 2
Input: put(3, 3), get(3), put(3, 4), get(3) Output: 3, 4
Input: put(1, 1), put(1, 2), get(1) Output: 2
Example
Input
put 1 1
put 2 2
get 1
put 3 3
get 2
put 4 4
get 1
get 3
get 4