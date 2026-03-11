Design a drivers payment system with the following functionalities:

Part1
add_driver(driver_id [integer], usd_hourly_rate [float])

Register a new driver, assuming there are no existing drivers with the same ID.
record_delivery(driver_id [integer], start_time, end_time)

Discuss your chosen time format.
Time precision must be at least to the second.
Ensure the driver exists in the system.
All deliveries are recorded immediately after completion.
Maximum delivery duration is 3 hours.
get_total_cost()

Return the total cost of recorded deliveries for all drivers.
Part2
pay_up_to(pay_time [integer, Unix time from epoch])

Pay for all deliveries completed at or before the given time.
get_total_cost_unpaid()

Return the total cost of all unpaid deliveries.
Example
Input
add_driver(1, 15.0)