Given a set of delivery drivers' online time intervals, calculate the maximum number of drivers that were simultaneously online at any point during the past 24 hours.

Input:

A list where each element is a sublist containing two timestamps representing a driver's online start and end time (in the format 'HH:MM').
Output:

An integer representing the maximum number of drivers that were simultaneously online during the past 24 hours.
Constraints:

When start and end times overlap at the same moment, prioritize the end.
Example:

Input: [ ['08:00', '12:00'], ['09:00', '10:00'], ['11:00', '13:00'], ['12:30', '13:30'] ] Output: 3

Example
Input
[['08:00', '12:00'], ['09:00', '11:00'], ['11:00', '13:00']]