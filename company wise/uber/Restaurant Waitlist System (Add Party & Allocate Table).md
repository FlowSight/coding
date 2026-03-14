Implement a restaurant waitlist system with the following core operations.

Maintain waitlists grouped by party size, and each size-specific waitlist is FIFO.

Operations
add(party_id, size)

Add a party to the waitlist.
party_id is unique; if it already exists, you may ignore or overwrite (state your choice).
allocate(table_id, capacity)

A table with capacity seats becomes available.
Allocation rule (follow-up version): you may allocate any party with size <= capacity, but you must choose the party that has waited the longest globally (earliest arrival time among all eligible parties).
If a party is allocated: return its party_id and remove it from the system.
If none eligible: return None.
Input
Line 1: integer m, number of operations. Next m lines, each is one operation:

ADD party_id size
ALLOC table_id capacity
Output
For each ALLOC, print one line:

the allocated party_id, or
NONE if no party can be seated.
Constraints
1 <= m <= 2 * 10^5
1 <= size, capacity <= 10^5
party_id, table_id are strings
Example
Input:

7
ADD p1 2
ADD p2 4
ADD p3 2
ALLOC t1 2
ALLOC t2 4
ALLOC t3 4
ALLOC t4 1
Output:

p1
p2
p3
NONE
Example
Input
7
ADD p1 2
ADD p2 4
ADD p3 2
ALLOC t1 2
ALLOC t2 4
ALLOC t3 4
ALLOC t4 1
Output
p1
p2
p3
NONE