Metric Counter Library
What We Need to Build
We need to design a library that helps services count and track data (metrics). Most real-world systems use this to track events, check speed, and show graphs on dashboards.

Your library needs a simple interface. Services will use it to save data and check values. The library must do three main things:

Count up: Record when things happen (like API calls, errors, or user clicks).
Check time windows: Look at counts for specific times (like the last minute, hour, or day).
Use tags: Allow us to label data with details (like server region or error code).
Code Structure
// Add to the count
void increment(String metricName)
void increment(String metricName, Map<String, String> tags)
void increment(String metricName, Map<String, String> tags, long value)

// Get the total count for a specific time
long getCount(String metricName, TimeWindow window)
long getCount(String metricName, Map<String, String> tags, TimeWindow window)

// Example usage:
counter.increment("api.requests", Map.of("endpoint", "/payments", "status", "200"))
long lastMinute = counter.getCount("api.requests", TimeWindow.LAST_MINUTE)
Important Design Choices
Performance: How do we record a lot of data very fast? We must not slow down the main service.
Memory: Storing data for different time windows takes space. How do we make sure we don't use too much memory?
Accuracy: Do the numbers need to be perfect? Is it okay to use an estimate? When should we use probabilistic data structures?
Sending Data: How and when do we send the metrics to a central system for storage?
Deeper Questions
Be ready for the interviewer to ask harder questions about the details:

Window Types: How do you code sliding windows versus tumbling windows? What is good or bad about each?
High Cardinality: What happens if a metric has too many unique tags (like one for every User ID)?
Thread Safety: How do you make sure the count is correct when many threads write at the same time?
Sending Batches: How often does the library send data out? What happens if the send fails?
Clock Skew: How do you handle time windows if the system clock is slightly wrong?
Aggregation: Do you sum up the numbers locally first, or send every raw event?
Memory Limits: How do you stop the library from crashing the app if memory gets full?
Integration: How does this work with tools like Prometheus or StatsD?