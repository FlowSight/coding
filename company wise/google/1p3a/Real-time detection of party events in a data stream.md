Real-time Detection of Party Events in a Data Stream
You have a continuous data stream with tuples (user_id, timestamp, place_id) indicating that a user is present at a certain place at a particular time. Detect if a 'party' event occurs at any place in real-time.

Rules:
If a user moves to a new place_id, they leave the old place_id.
A party event is defined as a place_id consistently having at least 100 same users in the last 60 minutes.
The detection needs to be instantaneous upon any report made by any user's report(user_id, timestamp, place_id) API call and cannot rely solely on a periodic report.
Please implement a report(user_id, timestamp, place_id) function to process and detect these events efficiently.

Input/Output:
Input: Several calls to the report function; each call includes user_id, timestamp, place_id.
Output: After each call, immediately detect and output if a party event is occurring or not.
Test Cases:
Call: report(1, 1600000000, 'place_1')
Call: report(2, 1600000030, 'place_1')
Call: report(3, 1600000060, 'place_1') ... (design data to specifically test for the 100 users in 60-minute threshold)
Example
Input
report(1, 1600000000, 'place_1')