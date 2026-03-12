In a concurrent system, calculate the conversion rate of users from visiting a website to completing a purchase. Suppose there are a series of event records, each record containing a user ID, an event type (including 'visit' and 'purchase'), and a timestamp. Please write a program to calculate the overall conversion rate.

Input
The first line is an integer $N$, representing the number of events.
The next $N$ lines, each line contains a user ID (string), an event type (string: 'visit' or 'purchase'), and a timestamp (integer).
Output
Print a float number representing the conversion rate, rounded to two decimal places.
Example
Input:
5
A visit 1
B visit 2
A purchase 3
B purchase 4
C visit 5

Output:
1.00
Constraints
$1 \leq N \leq 10^5$
Each user has at most one visit and one purchase event.
Timestamps are strictly increasing.
Example
Input
5
A visit 1
B visit 2
A purchase 3
B purchase 4
C visit 5