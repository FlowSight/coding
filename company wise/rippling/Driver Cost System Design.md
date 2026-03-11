Problem Statement
Design a driver payment system with the following functionalities:

Add_driver(driver_id, usd_hourly_rate): Add a new driver and set their hourly rate.
Record_delivery(driver_id, start_time, end_time): Record a completed delivery with the given driver ID and start-end times.
Get_Total_Cost(): Return the total cost that the delivery platform needs to pay to all drivers.
Note: Each delivery record is entered into the system in chronological order.

Task 1
Implement the update of total payment (total_pay) when driver records are updated.
Record and store each driver's delivery records.
Task 2
Pay_Up_To(pay_time: int): Pay for all completed orders before the given pay time (note: each record is paid only once).
Total_Cost_Unpaid(): Calculate and return the total costs of unpaid deliveries.
Implementation details:

Use pointers to manage paid records and update a global variable (totalpaid) to track the paid amount.
Use Get_Total_Cost minus totalpaid to get unpaid costs.
Task 3
Given a timestamp, calculate the number of drivers who were online in the previous 24 hours.
Use binary search on each driver's record list to verify.
Tips
Object-Oriented Design is recommended by defining a Driver class to store driver information.
Determine the timestamp format, and consider using float for simplification.
Format financial calculations to two decimal places.
Example
Input
add_driver(1, 10.0)
record_delivery(1, 9, 11)
get_total_cost()
pay_up_to(12)
get_unpaid_cost()