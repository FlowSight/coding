Imagine you're developing a core feature for a ride-sharing service, similar to Uber Pool, where the goal is to efficiently group individual ride requests into compatible batches. The objective is to minimize the total number of vehicles required by maximizing the number of compatible riders grouped into each vehicle, while respecting batch size limits.

Each incoming ride request provides essential details. Your task is to identify and form groups (batches) of rides, with a maximum of 3 rides per batch, that can be served together based on compatibility criteria.

Ride Data Format:

Each ride is represented as a list of three strings: {"ride_id", "pickup_location", "pickup_time"}

Where:

ride_id : A unique identifier for the ride (e.g., "123", "456"). This will always be a string representing a positive integer.
pickup_location : The specific location where the rider needs to be picked up (e.g., "A", "Downtown Station", "123 Main St"). This will always be a string.
pickup_time : The scheduled pickup time in a 24-hour "HH:MM" format (e.g., "09:30", "14:15").
Compatibility Rules:

Two or more rides are considered compatible and can be grouped into the same batch if, and only if:

Same Pickup Location: They share the exact same pickup_location.
Strict Proximity in Time: The difference between the earliest and the latest pickup_time among all rides in that batch must be within 10 minutes (inclusive). For example, if a batch contains rides at 09:00, 09:05, and 09:10, they are compatible (09:10 - 09:00 = 10 minutes). If a ride at 09:11 is added to a batch starting at 09:00, it would not be compatible (09:11 - 09:00 = 11 minutes).
Batching Constraints:

Maximum 3 Rides per Batch: A batch can contain a maximum of 3 rides. If more than 3 compatible rides are available, they must be split into multiple batches. This means a batch can contain 1, 2, or 3 rides.
Unique Assignment: Each ride can belong to at most one batch. Once a ride is assigned to a batch, it cannot be assigned to another.
Batch Output Format: Each batch should be a sorted list of the ride IDs (as integers) that comprise it.
Output Ordering:

The final list of batches should be ordered based on the earliest original input index of any ride within that batch. For example, if a batch contains rides that were originally at index 0 and index 5 in the input list, and another batch contains rides from index 1 and index 2, the batch containing the ride from index 0 would appear first.

Note: The batches are ordered by the earliest input index: [1,2] (index 0), [3,5] (index 2), [4] (index 3), [6] (index 5).

**Your Task:**Implement a function that takes the list of ride requests as input and returns the final list of batches according to the rules and output ordering specified above.

Example
Input
rides = [
            ["1, Downtown Station, 09:00"],
            ["2, Downtown Station, 09:05"],
            ["3, Uptown Plaza, 10:00"],
            ["4, Downtown Station, 09:12"],
            ["5, Uptown Plaza, 10:07"],
            ["6, Airport Terminal, 11:00"]
          ]
Output
[[1, 2],[3, 5],[4],[6]]