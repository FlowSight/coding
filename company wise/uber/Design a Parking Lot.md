Design a parking lot system. The parking lot can have multiple areas, each with different types of parking spots such as bike spots and car spots. Design class structures and methods to complete the following functions:

Initialize parking lot information, including areas and spot distribution.
Provide a parking function to record vehicle parking information.
Provide a function for vehicles to leave, canceling the parking record.
Implement a method to query the current status of the parking lot, returning the number of available spots in each area.
Example
Assume a parking lot with two areas:

Area 1: 3 bike spots, 5 car spots.
Area 2: 2 bike spots, 4 car spots.
Perform the following operations:

A bike parks in Area 1
A car parks in Area 1
The bike leaves
Query the current status, which should return:

Area 1 has 3 bike spots and 4 car spots available.
Area 2 has 2 bike spots and 4 car spots available.
Constraints
Total number of parking spots does not exceed 100.
Example
Input
areas = [Area(3, 5), Area(2, 4)]

# Operations
parking_lot = ParkingLot(areas)
parking_lot.park_vehicle('bike', 0)
parking_lot.park_vehicle('car', 0)
parking_lot.leave_vehicle('bike', 0)
parking_lot.get_status()