Given a list of integers, first parse the data and then compute the median. You need to implement the following function:

def find_median(lst: List[int]) -> float:
    pass
Input
lst: A list of integers, with length 1 <= len(lst) <= 10^5, each integer in the range -10^6 <= lst[i] <= 10^6.
Output
Return the median of the parsed integer list.
Note
If the number of elements in the list is even, the median is the average of the two middle numbers after sorting.
Example
find_median([3, 1, 2, 5, 4]) # returns 3
find_median([3, 1, 2, 5, 4, 6]) # returns 3.5
Example
Input
[1, 2, 3, 4, 5]