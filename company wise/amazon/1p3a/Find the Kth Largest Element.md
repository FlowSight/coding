Design a class to support real-time returning of the kth largest element in a stream of numbers. Implement the KthLargest class:

KthLargest(int k, int[] nums) initializes the object with the integer k and the stream of integers nums.
int add(int val) inserts the integer val into the stream and returns the current kth largest element in the stream.
Input
Integer k - 1 to 10^4
Integer array nums - maximum length and element value up to 10^4
Integer val - maximum element value up to 10^4
Output
Return the kth largest element in the stream.

Example
kthLargest = KthLargest(3, [4, 5, 8, 2]);
print(kthLargest.add(3))   # returns 4
print(kthLargest.add(5))   # returns 5
print(kthLargest.add(10))  # returns 5
print(kthLargest.add(9))   # returns 8
print(kthLargest.add(4))   # returns 8
Example
Input
3
4 5 8 2
3
5
10
9
4