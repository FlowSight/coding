Design a delivery system with the following interfaces:

add_driver(id, salary): Add a driver, including driver ID and salary.
add_delivery(driverID, start_time, end_time): Add a new delivery task for a specific driver with start and end times.
get_all_cost(): Return the total salary cost of all drivers.
Ensure the design considers efficient data storage and querying.

Example
Input
1,100 2,120
1,08:00,10:00
1,11:00,13:00
get_all_cost()