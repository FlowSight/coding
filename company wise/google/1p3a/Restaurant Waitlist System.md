
Design a restaurant waitlist system. The system should implement the following features:

Add party: Given the size of a party, add it to the waitlist.
Remove party: Given the size of a party, remove it from the waitlist.
Match seat: Given a table size, find the earliest waiting party that fits.
For special cases, if a table of a particular size becomes available, match it first with parties of the same size, and if none are available, try to match with smaller parties one by one. For example, if a table for size 5 becomes available and no 5-person party is waiting, match with a 4-person party, then 3-person, and so on.

Please provide a Python implementation and relevant test cases.

Example
Input
Add: 5, party1
Add: 3, party2
Match: 4
Remove: 3, party2
Match: 5