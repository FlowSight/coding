Deduplicate Events List
You are given a list of events events. Each event contains:

event_id: integer (can be negative or 0)
timestamp: integer
The list may be unsorted, and the same event_id may appear multiple times.

Dedup rule: For each event_id, keep only the event with the largest (latest) timestamp and discard the rest.

Return the deduplicated list sorted by (event_id ascending, timestamp ascending).

Input (stdin)
First line: integer n = number of events
Next n lines: event_id timestamp
Output (stdout)
Print m lines (deduplicated events): event_id timestamp, sorted.

Constraints
0 <= n <= 2e5
-1e9 <= event_id <= 1e9
-1e9 <= timestamp <= 1e9
Handle edge cases: n=0, negative/0 ids, many duplicates, unsorted input.
Sample Tests
See the Chinese section for 5 examples.

Example
Input
6
1 10
2 5
1 7
2 8
0 3
-1 4
Output
-1 4
0 3
1 10
2 8