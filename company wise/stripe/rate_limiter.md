Rate Limiter
Problem Description
Your task is to build a rate limiter. A rate limiter tracks how users access an API and limits how many requests they can make. It must work for multiple clients (identified by unique keys like User IDs) and decide if a request is allowed based on a sliding time window.

Your code needs to support two main actions:

hit(key, timestamp): Save a request event for a specific user at a specific time.
allowed(key, timestamp): Check if the user is currently allowed to make a request.
The limit is a maximum number of requests inside a time window. For example, if the limit is 100 requests per 60 seconds, a user is allowed only if they made fewer than 100 requests in the last 60 seconds.

Core Requirements
Track each key (user) separately.
Use a "sliding window" logic for accuracy.
Handle timestamps that arrive out of order.
Clean up old data to save memory.
Usage Example
# Rate limit: 3 requests per 10-second window
limiter = RateLimiter(max_requests=3, window_seconds=10)

limiter.hit("user_1", 1)
limiter.hit("user_1", 2)
limiter.allowed("user_1", 3)   # Returns True (2 hits in window, safe)
limiter.hit("user_1", 3)       # Records 3rd hit
limiter.allowed("user_1", 4)   # Returns False (3 hits = limit reached)

limiter.allowed("user_1", 12)  # Returns True (hits at t=1,2 are old, only 1 hit left)
limiter.allowed("user_2", 5)   # Returns True (new key, no past hits)
Part 1: The Basics
Task
Write a RateLimiter class. It should count hits for each key using a sliding window.

class RateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        """
        Setup the rate limiter.

        Args:
            max_requests: Max requests allowed in the window
            window_seconds: Size of the time window in seconds
        """
        pass

    def hit(self, key: str, timestamp: int) -> None:
        """
        Record a request for a key at a specific time.
        """
        pass

    def allowed(self, key: str, timestamp: int) -> bool:
        """
        Check if the key is allowed to make a request.

        Returns:
            True if hits in current window < max_requests,
            False otherwise.
        """
        pass
Questions to Ask the Interviewer
Should hit() stop requests that go over the limit, or just record them?
Are the timestamps always positive numbers?
Is the time measured in seconds or milliseconds?
Does allowed() count the current request, or only the past ones?
Part 2: Saving Memory
The Issue
In real systems, a user might stop sending requests for a long time. You need to remove old timestamps efficiently. If you don't, the memory will fill up with useless data.

Interview Follow-Ups
What is the Time Complexity (speed) and Space Complexity (memory) of your code?
How do you remove old data?
What happens if a user comes back after a long break?
Goals
Remove timestamps that are older than the current window.
Memory usage should depend on active requests, not all past requests.
Cleaning up data must not slow down the system.
Part 3: Tricky Situations
The Issue
You need to improve your code to handle difficult situations that happen in production.

What to Watch Out For
Burst Traffic: Many requests arrive at the exact same time.
New Keys: A request comes from a user you have never seen before.
Out-of-Order Timestamps: A request arrives with a timestamp older than the previous one.
Time Gaps: A user is inactive for a long time, then suddenly active.
Examples
limiter = RateLimiter(max_requests=3, window_seconds=10)

# Burst traffic: multiple hits at exact same time
limiter.hit("user_1", 5)
limiter.hit("user_1", 5)
limiter.allowed("user_1", 5)  # Returns True (2 hits, safe)
limiter.hit("user_1", 5)
limiter.allowed("user_1", 5)  # Returns False (3 hits = limit reached)

# Out-of-order timestamps
limiter.hit("user_2", 10)
limiter.hit("user_2", 8)      # Old timestamp arrives late
limiter.allowed("user_2", 10) # Should count both hits

# Large time gap
limiter.hit("user_3", 1)
limiter.hit("user_3", 2)
limiter.allowed("user_3", 1000)  # Returns True (old hits are gone)
Part 4: Handling Multiple Threads
The Issue
In a real system, many threads or processes might call hit() and allowed() at the same time. Your code must be thread-safe. It needs to handle this without crashing or corrupting data.

Interview Follow-Ups
What errors (race conditions) could happen with your code right now?
How do you make your rate limiter thread-safe?
What are the good and bad points of different locking strategies?
How do you keep the system fast while using locks?
Goals
Simultaneous calls for the same key must work correctly.
Prevent data corruption.
Keep the system fast (minimize waiting for locks).
Balance accuracy with speed.
Example Error
# Without protection, this can fail:
# Start: count = 2 (Limit is 3)
# Thread A checks allowed -> sees count 2 -> Returns True
# Thread B checks allowed -> sees count 2 -> Returns True
# Thread A hits -> count becomes 3
# Thread B hits -> count becomes 4 (Over limit!)
# Both were allowed, but only one should have been.
How to Solve It
Solution 1: Using a Deque
Strategy:

Use a Dictionary (HashMap). It maps a User Key to a Deque (double-ended queue).
hit(): Add the timestamp to the end of the deque.
allowed(): Remove old timestamps from the front. Then, check if the count is less than the limit.
Why Deque?

Adding to the end is fast: O(1).
Removing from the front is fast: O(1).
It keeps timestamps in order naturally.
Code:

from collections import defaultdict, deque

class RateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.hits = defaultdict(deque)

    def _cleanup(self, key: str, timestamp: int) -> None:
        """Remove timestamps that are too old."""
        window_start = timestamp - self.window_seconds
        while self.hits[key] and self.hits[key][0] <= window_start:
            self.hits[key].popleft()

    def hit(self, key: str, timestamp: int) -> None:
        self._cleanup(key, timestamp)
        self.hits[key].append(timestamp)

    def allowed(self, key: str, timestamp: int) -> bool:
        self._cleanup(key, timestamp)
        return len(self.hits[key]) < self.max_requests
Time Complexity:

hit(): O(k) amortized (k is how many old items we remove).
allowed(): O(k) amortized.
Space Complexity:

O(n × m). n is the number of keys, m is the average hits per key.
Solution 2: Optimizing Memory
Better Cleanup Strategy:

The basic code removes old items during operations. We can improve this:

Lazy Cleanup: Only clean when we touch a key.
Periodic Cleanup: In a real system, a background job could scan for inactive users.
Key Expiration: If a deque becomes empty, delete the key from the dictionary entirely.
from collections import defaultdict, deque

class RateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.hits = {}  # Regular dict so we can delete keys

    def _cleanup(self, key: str, timestamp: int) -> None:
        """Remove old timestamps and delete empty keys."""
        if key not in self.hits:
            return

        window_start = timestamp - self.window_seconds
        while self.hits[key] and self.hits[key][0] <= window_start:
            self.hits[key].popleft()

        # If key is empty, delete it to save memory
        if not self.hits[key]:
            del self.hits[key]

    def hit(self, key: str, timestamp: int) -> None:
        if key not in self.hits:
            self.hits[key] = deque()
        self._cleanup(key, timestamp)
        self.hits[key].append(timestamp)

    def allowed(self, key: str, timestamp: int) -> bool:
        self._cleanup(key, timestamp)
        if key not in self.hits:
            return True
        return len(self.hits[key]) < self.max_requests
Complexity Analysis:

| Operation | Best Case | Worst Case | Amortized | | :--- | :--- | :--- | :--- | | hit() | O(1) | O(m) | O(1) | | allowed() | O(1) | O(m) | O(1) |

m is the number of timestamps in the deque.

Why Amortized O(1)?

Each timestamp is added exactly once and removed exactly once. Over time, the cost averages out to O(1) per operation.

Solution 3: Handling Tricky Cases
Out-of-Order Timestamps:

If times arrive mixed up, a Deque is not enough because it expects order. You can:

Use a Sorted List: Always keeps data sorted.
Binary Search Insert: Find the right spot to insert the timestamp.
from collections import defaultdict
import bisect

class RateLimiterWithUnorderedTimestamps:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.hits = defaultdict(list)

    def _cleanup(self, key: str, timestamp: int) -> None:
        """Remove old timestamps using binary search."""
        window_start = timestamp - self.window_seconds
        # Find the first timestamp inside the window
        idx = bisect.bisect_right(self.hits[key], window_start)
        if idx > 0:
            self.hits[key] = self.hits[key][idx:]

    def hit(self, key: str, timestamp: int) -> None:
        # Insert while keeping the list sorted
        bisect.insort(self.hits[key], timestamp)
        self._cleanup(key, timestamp)

    def allowed(self, key: str, timestamp: int) -> bool:
        self._cleanup(key, timestamp)
        return len(self.hits[key]) < self.max_requests
Trade-offs:

Using a sorted list is slower to add data. Insertion is O(m) because you have to shift elements.
This is safer if data order is unreliable.
New Keys:

The dictionary handles this naturally. If a key is new, it starts empty.

Burst Traffic:

We store every timestamp, even duplicates. This correctly counts bursts.

Solution 4: Thread Safety
Locking Strategies:

Here are ways to make the code safe for multiple threads:

1. Global Lock (Simple)

Use one lock for everything. It is easy to write but can be slow because threads have to wait in line.

import threading
from collections import deque

class ThreadSafeRateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.hits = {}
        self.lock = threading.Lock()

    def _cleanup(self, key: str, timestamp: int) -> None:
        if key not in self.hits:
            return
        window_start = timestamp - self.window_seconds
        while self.hits[key] and self.hits[key][0] <= window_start:
            self.hits[key].popleft()
        if not self.hits[key]:
            del self.hits[key]

    def hit(self, key: str, timestamp: int) -> None:
        with self.lock:
            if key not in self.hits:
                self.hits[key] = deque()
            self._cleanup(key, timestamp)
            self.hits[key].append(timestamp)

    def allowed(self, key: str, timestamp: int) -> bool:
        with self.lock:
            self._cleanup(key, timestamp)
            if key not in self.hits:
                return True
            return len(self.hits[key]) < self.max_requests
2. Per-Key Locks (Better Speed)

Use a different lock for each user key. This allows different users to be processed at the same time.

import threading
from collections import deque

class PerKeyLockRateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.hits = {}
        self.locks = {}
        self.global_lock = threading.Lock()  # Protects access to the dictionaries

    def _get_lock(self, key: str) -> threading.Lock:
        with self.global_lock:
            if key not in self.locks:
                self.locks[key] = threading.Lock()
            return self.locks[key]

    def _cleanup(self, key: str, timestamp: int) -> None:
        if key not in self.hits:
            return
        window_start = timestamp - self.window_seconds
        while self.hits[key] and self.hits[key][0] <= window_start:
            self.hits[key].popleft()

    def hit(self, key: str, timestamp: int) -> None:
        lock = self._get_lock(key)
        with lock:
            with self.global_lock:
                if key not in self.hits:
                    self.hits[key] = deque()
            self._cleanup(key, timestamp)
            self.hits[key].append(timestamp)

    def allowed(self, key: str, timestamp: int) -> bool:
        lock = self._get_lock(key)
        with lock:
            self._cleanup(key, timestamp)
            if key not in self.hits:
                return True
            return len(self.hits[key]) < self.max_requests
3. Read-Write Lock

Allows many threads to read (check limits) at once, but only one to write (add hits).

import threading
from collections import deque

class RWLockRateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.hits = {}
        self.rw_lock = threading.RLock()
        self.read_count = 0
        self.read_lock = threading.Lock()

    # Note: Python doesn't have a native RWLock in standard lib.
    # This is just a concept for illustration.
4. Lock-Free

Uses atomic operations. This is very fast but very hard to code correctly.

from collections import defaultdict
import threading

class AtomicCounter:
    """Simple atomic counter example."""
    def __init__(self):
        self._value = 0
        self._lock = threading.Lock()

    def increment(self):
        with self._lock:
            self._value += 1
            return self._value

    def get(self):
        return self._value
Comparison:

| Approach | Pros | Cons | Best For | | :--- | :--- | :--- | :--- | | Global Lock | Simple, Correct | Slow with many users | Low traffic, prototyping | | Per-Key Lock | Good Parallelism | Memory for locks | Many distinct users | | Read-Write Lock | Fast Reads | Complex, Writer issues | Read-heavy apps | | Lock-Free | Fastest | Very Complex | Extreme performance needs |

Atomic Check-and-Hit:

To fix the race condition mentioned earlier, you can combine checking and hitting into one locked step:

def check_and_hit(self, key: str, timestamp: int) -> bool:
    """
    Check limit and record hit in one atomic step.
    Returns True if allowed, False if not.
    """
    with self._get_lock(key):
        self._cleanup(key, timestamp)
        if key not in self.hits:
            self.hits[key] = deque()

        if len(self.hits[key]) < self.max_requests:
            self.hits[key].append(timestamp)
            return True
        return False
Extra Discussion Points
Alternative Data Structures
Circular Buffer (Ring Buffer):

Create a fixed-size array. The size is the max requests allowed.
Overwrite old entries using math (modulo).
Pros: Memory size never changes.
Cons: Harder to track time accurately if buffer size is small.
class CircularBufferRateLimiter:
    def __init__(self, max_requests: int, window_seconds: int):
        self.max_requests = max_requests
        self.window_seconds = window_seconds
        self.buffer_size = max_requests + 1
        self.buffers = {}  # key -> (circular array, head index, count)
Fixed Window vs. Sliding Window
Fixed Window:

Counts requests in fixed blocks (e.g., 12:00:00 to 12:00:59).
Pros: Simpler code. Less memory.
Cons: You can have a burst at the edge. A user could make 100 requests at 12:00:59 and 100 more at 12:01:00. This is 200 requests in 2 seconds, which might overload the system.
Sliding Window:

The window moves smoothly with time.
Pros: More accurate. Prevents the edge-burst issue.
Cons: Uses more memory because you store individual timestamps.