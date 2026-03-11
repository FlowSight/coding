"OOP Design Question: Billing System for Delivery Cost Calculation"
You're designing an object-oriented billing system that tracks deliveries performed by different drivers and calculates their total cost. The system should expose the following methods:

add_driver(driver_id: int, cost: float): Registers a new driver with a given hourly rate.
add_delivery(driver_id: int, start_time: int, end_time: int): Records a delivery for a driver, with start and end times in Unix seconds.
get_total_cost(): Calculates the total cost of all completed deliveries across all drivers, based on each driver’s hourly rate.
Follow-Up Features
pay_up_to(time: int): Pays off the total cost for all deliveries that ended on or before the specified Unix timestamp.
Should not double-count deliveries that were already paid in previous calls.
get_unpaid_amount(): Returns the remaining unpaid cost — the difference between total cost so far and the amount already paid via pay_up_to().
Assumptions
You can assume all inputs are valid (no negative durations, no missing drivers, etc.).
Delivery times are given in Unix time (i.e., in seconds).
You don't need to handle overlapping deliveries or concurrent activity.
The goal is to demonstrate good OOP design, encapsulation, and maintainability.
Discussion Points (if applicable)
Would you use a Delivery class or store raw tuples?
How would you extend this to support get_driver_cost(driver_id)?
Can you persist payment state per delivery instead of globally?
Example
Input
add_driver(1, 10.0)
add_delivery(1, 1620000000, 1620003600)
get_total_cost()