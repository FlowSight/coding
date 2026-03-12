Meeting Scheduler
Given availability time slots of multiple participants, find a time interval where a meeting can be scheduled.

Input
Integer k: number of participants.
For each participant i, an availability list slots[i], where each slot is a half-open interval [start, end).
Integer duration: required meeting length.
Output
Return any interval [meetingStart, meetingEnd) such that meetingEnd = meetingStart + duration and all participants are available for the whole interval.
If no such interval exists, return empty.
Constraints
1 <= k <= 1e5 (or as specified)
slots[i] may be unsorted and may overlap.
start < end, duration > 0
Time values are non-negative integers and may be up to 1e9.
Examples (tests)
input:
k=2
slots0=[[10,50],[60,120],[140,210]]
slots1=[[0,15],[60,70]]
duration=8
output:
[60,68]
input:
k=2
slots0=[[10,50]]
slots1=[[60,120]]
duration=5
output:
[]
input:
k=3
slots0=[[10,100]]
slots1=[[20,30],[40,90]]
slots2=[[0,25],[30,60]]
duration=10
output:
[40,50]
input:
k=1
slots0=[[5,10]]
duration=5
output:
[5,10]
input:
k=2
slots0=[[1,3],[3,5]]
slots1=[[2,4]]
duration=2
output:
[2,4]
Example
Input
2
3
10 50
60 120
140 210
2
0 15
60 70
8
Output
60 68