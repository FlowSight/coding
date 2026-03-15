
You have a fixed-size buffer (say capacity N) shared between producer threads and consumer threads.

Producers add items to the queue
Consumers remove items from the queue
The Rules
Bounded: The queue holds at most N items. A producer cannot add when the queue is full.
Blocking:
If a producer tries to enqueue() and the queue is full → it blocks (waits) until a consumer removes an item
If a consumer tries to dequeue() and the queue is empty → it blocks (waits) until a producer adds an item
Thread-safe: Multiple producers and multiple consumers operate concurrently. No data corruption, no lost items, no duplicate consumption.