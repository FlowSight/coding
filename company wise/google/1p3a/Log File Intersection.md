You have two log files, each containing a set of records. Each record consists of a timestamp, obj_ID, and clientID. Your task is to find those obj_IDs that:

Exist in both log files.
Are associated with at least two different clientIDs.
Design an algorithm to efficiently find the obj_IDs that meet the above conditions.

Example
Input
log1 = [(1, 'a', 'c1'), (2, 'b', 'c2'), (3, 'a', 'c3')], log2 = [(1, 'a', 'c4'), (2, 'd', 'c5')]