Given a sequence of events, each event has a type and a timestamp. Find the segments in the sequence that satisfy the 'super streak' condition: the number of consecutive events of the same type is at least N, the time interval between adjacent events does not exceed T, and the total duration is at least X. Implement a function to count such segments.

Input:

An array events, where each element is a tuple ('type', timestamp).
An integer N indicating the minimum number of consecutive events.
An integer T indicating the maximum time interval.
An integer X indicating the minimum total duration.
Output:

Return an integer indicating the number of segments that meet the condition.
Test case:

Input: events = [('A', 1), ('A', 2), ('A', 3), ('B', 4), ('A', 5)], N = 2, T = 1, X = 2
Output: 1
Example
Input
[('A', 1), ('A', 2), ('A', 3), ('B', 4), ('A', 5)] 2 1 2