

For example, there are n = 4 presenters scheduled for the course of the event which begins at time 0 and ends at time t = 15. The meetings start at times start = [4, 6, 7, 10] and end at times finish = [5, 7, 8, 11]. You can rearrange up to k = 2 meetings. In this case, we have 4 periods without speakers scheduled: [0-3], [5], [8-9], [11-14]. The meeting ends after hour 14. If the first meeting is shifted to an hour later, a break is created from 0 to 5 (5 hours). If the last speech is moved up to 8, it will end at 9, leaving a break from 9 to 15. There is no point in moving the middle two speeches in this case. The longest break that can be achieved is 15 - 9 = 6 hours by moving the last speech two hours earlier.

Function Description

Complete the function findMaximumBreakTime in the editor.

findMaximumBreakTime has the following parameters:

int[] start: an array of integers representing the start times of meetings
int[] finish: an array of integers representing the end times of meetings
int t: the total duration of the day
int k: the number of meetings that can be rescheduled
Returns

int: the maximum break time that can be achieved by rescheduling up to k meetings

Constraints:

1≤n≤10^5 (number of events)
0≤k≤n (number of reschedules allowed)
1≤t≤10^9 (total duration of the day)
0≤start[i]
Example
Input
start = [4, 6, 7, 10]
finish = [5, 7, 8, 11]
t = 15
k = 2
Output
6