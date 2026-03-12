Problem
Design and implement a parking lot system supporting the following operations:

park(vehicle_type, vehicle_id) -> bool: allocate a slot and park the vehicle. Return true if successful, otherwise false.
unpark(vehicle_id) -> bool: remove the vehicle and free its slot. Return true if successful; false if the vehicle is not found.
checkCar(vehicle_id) -> int: return the slot_id where the vehicle is parked; return -1 if not found.
The parking lot has two types of slots:

Motorcycle slots (M): motorcycles only.
Car slots (C): can fit either motorcycles or cars.
Allocation rules:

Each successful park assigns a unique slot_id.
Always choose the smallest available slot_id among eligible slots.
For motorcycles: prefer motorcycle slots; if none available, use a car slot.
For cars: must use a car slot.
I/O Contract (for an executable solution)
Read from stdin:

Line 1: two integers m c (# motorcycle slots and # car slots)
Line 2: integer q (# operations)
Next q lines, each an operation:
park <type> <id> where <type> is M or C
unpark <id>
check <id>
Output:

For park/unpark: print true or false
For check: print slot_id or -1
Constraints
1 <= m, c <= 1e5
1 <= q <= 2e5
vehicle_id is a string (length <= 32); park will not be called with an id already parked.
No payment logic is required.

Example
Input
2 2
9
park M m1
park C c1
park M m2
park M m3
check m2
unpark m1
park M m4
check m4
check m1
Output
true
true
true
true
2
true
true
1
-1