Design an in-memory service system for a food delivery platform to compute payouts and basic real-time analytics.

Background
There are tens of thousands of drivers; each submits hundreds of deliveries per week.
Delivery details are sent to the system immediately upon completion.
Drivers have hourly rates (which can differ by driver).
Drivers may take multiple deliveries simultaneously. Each delivery is paid independently (overlapping times accumulate).
Use efficient data structures; ignore persistence and thread safety.
Part I — Core API
Time Format

Use Unix epoch seconds (long / 64-bit integer).
Minimum precision: 1 second.
Each delivery satisfies: 0 < (endTime - startTime) ≤ 3 hours.
Payment Rule

A delivery pays: payout = driverHourlyRate * (endTime - startTime) / 3600.
Example: $10.00/hour × 1h30m → $15.00.

Methods
addDriver(driverId: int, usdHourlyRate: double) -> void Registers a driver, who will not previously exist.
recordDelivery(driverId: int, startTime: long, endTime: long) -> void Records a completed delivery for an existing driver.
getTotalCost() -> double Returns the aggregated payout for all recorded deliveries.
Part II — Payments by Cutoff Time
Add support to mark deliveries as paid when they finish before a cutoff time.

pay_up_to(endTime: long) -> void Marks as paid every delivery with delivery.endTime ≤ endTime.
getUnpaidAmount() -> double Returns the total unpaid amount.
Optional: Expose driver-level helpers like getDriverCost(driverId) and getDriverUnpaid(driverId).

Part III — Concurrency Analytics
Compute how many drivers, not deliveries, were simultaneously active in a time window.

maxSimultaneousDriverInPast24Hours(now?: long) -> int Returns the maximum number of distinct drivers who were active at the same time in the last 24 hours.
Recommended approach: For each driver, merge the driver's deliveries into a union of disjoint intervals within the window. Run a sweep line over all merged intervals, treating intervals as half-open [start, end). Optional variant: return the intervals during which the maximum holds, such as maxSimultaneousDriverIntervalsPast24Hours().