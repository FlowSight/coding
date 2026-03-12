Design a data structure that supports the following two operations:

Insert an integer into the data structure.
Return the current median of all integers in the data structure.
Implement the MedianFinder class:

MedianFinder() initializes the data structure object.
void addNum(int num) adds the integer num to the data structure.
double findMedian() returns the median of all elements so far.
Advanced: Modify your data structure such that the removeNum(int num) function can remove a specific integer, and still be able to find the median in constant time.

Example:
Input:
commands = ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
args = [[], [1], [2], [], [3], []]

Output:
[null, null, null, 1.5, null, 2.0]

Explanation:
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);
medianFinder.addNum(2);
medianFinder.findMedian(); // returns 1.5
medianFinder.addNum(3);
medianFinder.findMedian(); // returns 2.0
Constraints:
At most 10^5 calls will be made to addNum.
At most 10^5 calls will be made to findMedian.
All input numbers are in the range of -10^5 to 10^5.
Example
Input
commands = ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
args = [[], [1], [2], [], [3], []]