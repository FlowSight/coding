Design a system for collecting and displaying massive temperature sensor data distributed across a large geographic area (such as Washington state).

Input
1 to 10 million temperature sensors, evenly distributed across the area.
Low-cost, simple-function sensors not supporting mesh network.
Sensors send data to the backend via HTTP, both having IP addresses.
Temperature changes slowly, but the system needs to track temperature changes of any sensor at 10-second granularity.
Output
Near real-time temperature distribution maps for Web interface display.
At around 1 million sensors, one pixel corresponds to one sensor (capable of fully displaying on a 4K screen).
Supports querying the current temperature, minimum, and maximum temperature within a time range (such as a day or a year).
The system needs to run stably for years.