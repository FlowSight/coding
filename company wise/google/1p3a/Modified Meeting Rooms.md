Suppose there is a server that runs some jobs daily, with each job having a start time and an end time. The server can only handle one job at a time. If two jobs overlap, they can be considered the same job and handled on a single server simultaneously. If a job cannot be completed the same day, it needs to be truncated and continued at the next available time. Write a function to determine if the server can run the same jobs each day.

Example
Input
jobs = [(1, 5), (2, 6), (4, 8)]