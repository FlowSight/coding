Given an array of meeting room IDs, e.g., [1, 2, 3, 4, 5], and a time interval, e.g., 13:00 - 15:00. Write a function to determine if there is an available meeting room. Return the room ID if found. Assume there is a known dataset of booked time slots for each room.

Example
Input
room_ids = [1, 2, 3, 4, 5]
booking_data = [[(12, 13), (15, 16)], [(9, 10), (13, 14), (16, 17)], [(8, 10), (11, 13)], [(10, 12), (14, 15)], [(16, 18)]]
desired_interval = (13, 15)