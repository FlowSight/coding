Delivery Billing System
Problem Requirements
Create an in-memory service for a food delivery app. This system needs to calculate how much to pay drivers and show live data.

The Situation
Scale: Tens of thousands of drivers. Each does hundreds of deliveries a week.
Data Flow: Delivery data comes in immediately after a job finishes.
Rates: Each driver has their own hourly pay rate.
Concurrency: A driver can do multiple deliveries at once.
Rule: Each delivery pays the full amount.
Example: If two jobs overlap, the driver gets paid for both. The payouts are added together.
Tech Constraints: Use efficient data structures. Do not worry about saving data to a database (persistence) or thread safety.
Time & Math
Time Format: Use Unix epoch seconds (integers).
Duration: Each delivery is between 1 second and 3 hours long.
The Formula: To calculate pay: Payout = Hourly Rate * (Duration in Hours)

Example:

Rate: $10.00/hour
Time: 1 hour 30 minutes (1.5 hours)
Payout: $15.00
Part 1: Basic Billing Logic
Task Description
Write three methods:

add_driver: Save a driver's ID and their hourly rate.
record_delivery: Save a finished delivery.
The driver already exists.
The end_time is in the past.
get_total_cost: Return the total money owed for all deliveries ever recorded.
Performance: This runs on a live dashboard, so it must be O(1).
Input Example
system = DeliveryBillingSystem()

# Add drivers
system.add_driver(1, 10.00)  # Driver 1 gets $10/hour
system.add_driver(2, 15.00)  # Driver 2 gets $15/hour

# Record jobs (times are seconds)
system.record_delivery(1, 1000, 4600)  # 1 hour long -> $10
system.record_delivery(1, 5000, 6800)  # 30 mins long -> $5
system.record_delivery(2, 2000, 5600)  # 1 hour long -> $15

print(system.get_total_cost())  # Output: 30.00
Strategy
To make get_total_cost O(1), we cannot loop through a list every time. Instead, we keep a running total variable. Every time a delivery comes in, we calculate the cost and add it to self.total_cost immediately.

Part 1: Solution Code
from dataclasses import dataclass, field

@dataclass
class Driver:
    driver_id: int
    hourly_rate: float
    deliveries: list = field(default_factory=list)  # Storing this for later parts

class DeliveryBillingSystem:
    def __init__(self):
        self.drivers: dict[int, Driver] = {}
        self.total_cost: float = 0.0

    def add_driver(self, driver_id: int, usd_hourly_rate: float) -> None:
        self.drivers[driver_id] = Driver(driver_id, usd_hourly_rate)

    def record_delivery(self, driver_id: int, start_time: int, end_time: int) -> None:
        driver = self.drivers[driver_id]
        duration_hours = (end_time - start_time) / 3600.0
        payout = driver.hourly_rate * duration_hours

        # Save data for Part 2 and 3
        driver.deliveries.append({
            'start_time': start_time,
            'end_time': end_time,
            'payout': payout,
            'paid': False
        })

        # Add to running total for O(1) access
        self.total_cost += payout

    def get_total_cost(self) -> float:
        return self.total_cost
Complexity Analysis:

All operations are O(1) time.
Space is O(1) per call (excluding storage for the delivery list).
Part 2: Payment Processing
Task Description
Now we need to mark deliveries as "paid."

pay_up_to(end_time): Mark all deliveries finishing at or before end_time as PAID.
Do not pay the same delivery twice.
The end_time provided will always increase (monotonic).
get_unpaid_amount(): Return the total money currently owed.
Formula: Total Cost - Total Paid.
Must be O(1).
Input Example
system = DeliveryBillingSystem()
system.add_driver(1, 10.00)

# Three jobs, each costs $10
system.record_delivery(1, 0, 3600)       # Ends at 3600
system.record_delivery(1, 7200, 10800)   # Ends at 10800
system.record_delivery(1, 14400, 18000)  # Ends at 18000

print(system.get_unpaid_amount())  # $30.00 (Nothing paid yet)

system.pay_up_to(5000)   # Pay anything ending by 5000
print(system.get_unpaid_amount())  # $20.00 (First job paid)

system.pay_up_to(12000)  # Pay anything ending by 12000
print(system.get_unpaid_amount())  # $10.00 (First two jobs paid)
Strategy
Since pay_up_to is called with increasing times, we want to find the "oldest" deliveries first. A Min-Heap is the best tool for this. We order the heap by end_time.

When recording a delivery, push it into the heap.
When paying, pop items off the top of the heap as long as their end_time is less than the cutoff.
Part 2: Solution Code
import heapq
from dataclasses import dataclass, field
from typing import Optional

@dataclass(order=True)
class Delivery:
    end_time: int
    start_time: int = field(compare=False)
    driver_id: int = field(compare=False)
    payout: float = field(compare=False)
    paid: bool = field(default=False, compare=False)

class DeliveryBillingSystem:
    def __init__(self):
        self.drivers: dict[int, float] = {}  # driver_id -> hourly_rate
        self.total_cost: float = 0.0
        self.total_paid: float = 0.0
        self.unpaid_heap: list[Delivery] = []  # min-heap based on end_time
        self.all_deliveries: list[Delivery] = []  # needed for Part 3

    def add_driver(self, driver_id: int, usd_hourly_rate: float) -> None:
        self.drivers[driver_id] = usd_hourly_rate

    def record_delivery(self, driver_id: int, start_time: int, end_time: int) -> None:
        hourly_rate = self.drivers[driver_id]
        duration_hours = (end_time - start_time) / 3600.0
        payout = hourly_rate * duration_hours

        delivery = Delivery(
            end_time=end_time,
            start_time=start_time,
            driver_id=driver_id,
            payout=payout
        )

        heapq.heappush(self.unpaid_heap, delivery)
        self.all_deliveries.append(delivery)
        self.total_cost += payout

    def get_total_cost(self) -> float:
        return self.total_cost

    def pay_up_to(self, cutoff_time: int) -> None:
        """Remove deliveries from heap if end_time <= cutoff_time."""
        while self.unpaid_heap and self.unpaid_heap[0].end_time <= cutoff_time:
            delivery = heapq.heappop(self.unpaid_heap)
            if not delivery.paid:
                delivery.paid = True
                self.total_paid += delivery.payout

    def get_unpaid_amount(self) -> float:
        return self.total_cost - self.total_paid
Complexity Analysis:

record_delivery: O(log D) to push to the heap.
pay_up_to: O(K log D) (where K is the number of items paid).
get_unpaid_amount: O(1).
Part 3: Analytics (Active Drivers)
Task Description
Find the maximum number of unique drivers working at the exact same time during the last 24 hours.

Key Definition:

If a driver has 3 overlapping deliveries at the same time, they still count as 1 active driver.
We are counting people, not deliveries.
Strategy: Merge & Sweep
Because one driver can have overlapping jobs, we cannot simply look at delivery start/end times.

Filter: Only look at deliveries in the last 24 hours.
Merge Intervals: For each specific driver, combine their overlapping delivery times into single, continuous blocks of time.
Example: Driver 1 works 1:00-2:00 and 1:30-3:00. This becomes one block: 1:00-3:00.
Sweep Line: Treat the start and end of these blocks as events on a timeline.
Sort all events by time.
Walk through the events. Increment count on "Start", decrement on "End".
Track the maximum count seen.
Important Logic Detail
If one driver stops at 2:00 PM and another starts at 2:00 PM, we process the End event before the Start event. This ensures we don't accidentally double-count for that single second.

Part 3: Solution Code
from collections import defaultdict
from typing import List, Tuple

class DeliveryBillingSystem:
    # ... (Include methods from Part 1 and 2 here) ...

    def max_simultaneous_drivers_in_past_24_hours(self, now: int) -> int:
        window_start = now - 86400  # 24 hours ago
        window_end = now

        # Step 1: Group deliveries by driver, ignore those outside the window
        driver_intervals: dict[int, list[tuple[int, int]]] = defaultdict(list)

        for delivery in self.all_deliveries:
            # Skip if no overlap with the window
            if delivery.end_time <= window_start or delivery.start_time >= window_end:
                continue

            # Clip times to fit inside the window
            clipped_start = max(delivery.start_time, window_start)
            clipped_end = min(delivery.end_time, window_end)
            driver_intervals[delivery.driver_id].append((clipped_start, clipped_end))

        # Step 2: Merge overlapping times for each driver
        def merge_intervals(intervals: list[tuple[int, int]]) -> list[tuple[int, int]]:
            if not intervals:
                return []
            intervals.sort()
            merged = [intervals[0]]
            for start, end in intervals[1:]:
                if start <= merged[-1][1]:  # Overlaps or touches previous interval
                    merged[-1] = (merged[-1][0], max(merged[-1][1], end))
                else:
                    merged.append((start, end))
            return merged

        # Step 3: Create events for the sweep line
        # Event structure: (time, type, driver_id)
        # Type 0 = End, Type 1 = Start (0 comes before 1 when sorting)
        events = []

        for driver_id, intervals in driver_intervals.items():
            merged = merge_intervals(intervals)
            for start, end in merged:
                events.append((start, 1, driver_id))   # Driver starts working
                events.append((end, 0, driver_id))     # Driver stops working

        # Sort by time. If times are equal, process End (0) before Start (1).
        events.sort()

        # Step 4: Run the sweep line
        active_drivers = set()
        max_drivers = 0

        for time, event_type, driver_id in events:
            if event_type == 1:  # Start
                active_drivers.add(driver_id)
                max_drivers = max(max_drivers, len(active_drivers))
            else:  # End
                active_drivers.discard(driver_id)

        return max_drivers
Complexity Analysis:

Time: O(D log D) because we must sort the intervals and events (where D is the number of deliveries).
Space: O(D) to store the temporary interval lists.
Full Code Implementation
Here is the complete class combining all three parts.

import heapq
from collections import defaultdict
from dataclasses import dataclass, field
from typing import List, Tuple

@dataclass(order=True)
class Delivery:
    end_time: int
    start_time: int = field(compare=False)
    driver_id: int = field(compare=False)
    payout: float = field(compare=False)
    paid: bool = field(default=False, compare=False)

class DeliveryBillingSystem:
    def __init__(self):
        self.drivers: dict[int, float] = {}
        self.total_cost: float = 0.0
        self.total_paid: float = 0.0
        self.unpaid_heap: list[Delivery] = []
        self.all_deliveries: list[Delivery] = []

    # ========== Part 1: Basic Billing ==========

    def add_driver(self, driver_id: int, usd_hourly_rate: float) -> None:
        self.drivers[driver_id] = usd_hourly_rate

    def record_delivery(self, driver_id: int, start_time: int, end_time: int) -> None:
        hourly_rate = self.drivers[driver_id]
        duration_hours = (end_time - start_time) / 3600.0
        payout = hourly_rate * duration_hours

        delivery = Delivery(
            end_time=end_time,
            start_time=start_time,
            driver_id=driver_id,
            payout=payout
        )

        heapq.heappush(self.unpaid_heap, delivery)
        self.all_deliveries.append(delivery)
        self.total_cost += payout

    def get_total_cost(self) -> float:
        return self.total_cost

    # ========== Part 2: Payment Logic ==========

    def pay_up_to(self, cutoff_time: int) -> None:
        while self.unpaid_heap and self.unpaid_heap[0].end_time <= cutoff_time:
            delivery = heapq.heappop(self.unpaid_heap)
            if not delivery.paid:
                delivery.paid = True
                self.total_paid += delivery.payout

    def get_unpaid_amount(self) -> float:
        return self.total_cost - self.total_paid

    # ========== Part 3: Analytics Logic ==========

    def max_simultaneous_drivers_in_past_24_hours(self, now: int) -> int:
        window_start = now - 86400
        window_end = now

        # Group by driver, strictly inside the time window
        driver_intervals: dict[int, list[tuple[int, int]]] = defaultdict(list)
        for delivery in self.all_deliveries:
            if delivery.end_time <= window_start or delivery.start_time >= window_end:
                continue
            clipped_start = max(delivery.start_time, window_start)
            clipped_end = min(delivery.end_time, window_end)
            driver_intervals[delivery.driver_id].append((clipped_start, clipped_end))

        # Helper to merge intervals
        def merge(intervals):
            if not intervals:
                return []
            intervals.sort()
            merged = [intervals[0]]
            for s, e in intervals[1:]:
                if s <= merged[-1][1]:
                    merged[-1] = (merged[-1][0], max(merged[-1][1], e))
                else:
                    merged.append((s, e))
            return merged

        # Create sweep events
        events = []
        for driver_id, intervals in driver_intervals.items():
            for start, end in merge(intervals):
                events.append((start, 1, driver_id))
                events.append((end, 0, driver_id))

        events.sort()

        # Execute sweep
        active = set()
        max_count = 0
        for _, event_type, driver_id in events:
            if event_type == 1:
                active.add(driver_id)
                max_count = max(max_count, len(active))
            else:
                active.discard(driver_id)

        return max_count
Further Discussion
During the interview, you might be asked these follow-up questions:

Driver Details: Can you add a function to see how much just one specific driver is owed?
Peak Time: Instead of just returning the number (e.g., "5 drivers"), return the exact time window when the peak happened.
Optimization: If the analytics function is called every second, how can we make it faster?
Idea: Use a sliding window or cache previous results so we don't recalculate everything from scratch.
Limits: How would you enforce a rule that says a driver cannot have more than 3 active deliveries at once?
Trade-offs Table
| Method | Writing Data (record) | Reading Data (analytics) | Notes | | :--- | :--- | :--- | :--- | | Current Solution | Fast (O(log D)) | Slow (O(D log D)) | Good if we record data often but check analytics rarely. | | Sorted Events | Fast (O(log D)) | Medium (O(D)) | Keep events sorted as they come in. | | Sliding Window | Slower | Instant (O(1)) | Calculate updates constantly. Good if the dashboard is checked constantly. |