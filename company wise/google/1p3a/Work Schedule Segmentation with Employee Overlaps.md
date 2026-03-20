Given a schedule of people's working hours, where each entry includes a name, start time, and end time, your task is to output a work schedule for each time segment indicating which people are working.

Input
A list of work schedules, each schedule contains a tuple (name, start_time, end_time):
Example: [(A, 10, 30), (B, 20, 40), (C, 30, 40)]
Output
A list containing time period work information, with the period represented as a tuple (start_time-end_time, employee_names):
Example: [(10-20, 'A'), (20-30, 'A&B'), (30-40, 'B&C')]
You need to consider overlapping times and correctly merge employee names.

Example
Input
[('A', 10, 30), ('B', 20, 40), ('C', 30, 40)]