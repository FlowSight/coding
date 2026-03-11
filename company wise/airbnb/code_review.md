https://gist.github.com/airbnb-robot/af6e9068639733bff79d4e3773a8d1dc

There are 3 pull requests: 1, 2, 3
They are in increasing order of complexity and difficulty.

You get a GitHub repo with 3 pull requests. What they don't tell you is that you score "points" for making comments on various issues about the code. Apparently I got a few points below the cutoff for senior software engineer. I got all the low-hanging fruit in the easier pull requests, but I ran out of time on the bigger pull request.

For this interview, start with pull request 3 and make as many comments about the architecture as you can. Apparently the last pull request is worth the most points.

Pull request 1:

This pull request is to fix the wrong type of consistency being sent through the API. The two types are "EVENTUAL" and "STRONG", but someone wrote "WEAK" and "STRONG", which caused a bug. This pull request fixes the bug.

Things to note:

Use Enums instead of the list ["EVENTUAL", "STRONG"] to check the value being sent.
Ask about casing.
Ask the user to test all possible conditions for the enum value.
Python should use f-strings instead of interpolations wherever possible.
Ask the user to log whenever there's an error or add instrumentation and alerting. We should log the actual exception and NOT swallow the exception.
Ask whether we have overall system tests.
Pull request 2:
For this PR, we add a DAO layer to fetch listings data from the listing service and host data from the hosts service. In order to do so, we first need to issue service calls to those services and then transform the raw responses into our internal DAO objects for related processing.

There's a bug between the Listing and the Listings objects when you try to turn a Listing into Listings. If you update a field in Listing and it's not in Listings, then you'll have a key error when you try to do the transformation. Use dict.get(key) instead of dict[key].
Look at the DAOs that are used. They are frozen data classes in Python. Add slots to them. This improves query performance and reduces memory usage.
You should reraise exceptions and avoid ambiguous, catchall exceptions.
Ask the user to add unit tests for the retries.
The retry classes are very similar. You should ask the user to make a base classes with the common functionality.
The type hinting for some of the data classes is incorrect. x: datetime = None should actually be x: Optional[datetime] = None.
Different exceptions should be handled in different ways. You should not treat every Exception the same way.
Suggest using async-await in some places for better performance.
If the listing service gives you a different number of results from what you expected, then you should log the difference between what you expected and what you got.
The logging should use static strings with extra parameters instead of dynamic, interpolated strings.
Pull request 3:

Atlantis has told us that we're calling their API too frequently and they have a batch endpoint that they'd like for us to use instead. To get the status of many reservations and take advantage of this, we will start batching up our calls to Atlantis to make this work without changing our external API. We plan to use a job queue for registrations and listings. Once the queue is large enough or after enough time has passed, we'll pick a bunch of items off this queue.

Leave a general comment saying that you should talk to Atlantis to get a precise rate limit or find out what the problem is. This is a Staff+ level signal.
Leave a comment saying that we should look for distinct listings and registrations instead of a list, which may have duplicates. This is a Staff+ level signal.
Ask what the traffic is from AirBnb to the city of Atlantis. Maybe this isn't the right approach?
Ask whether the queue is durable. Maybe you can use a different data structure instead. Maybe you can sync every few hours instead of every 500 events.
Use a list(set(registration_numbers)) instead of a list(registration_numbers)
Do a bulk upload to YOUR databases instead of sequential updates.
Use better type hinting in the Python. Some methods don't have return types explicitly stated.
We should not have silent failures whenever we try to add jobs to the queue.
Run the queue using an external job instead of from the code layer.
The dequeuing code is not thread safe. You could try to send the same exact request from the queue multiple times.
Magic constants spread throughout the file.
The way the queue is set up, you will have data loss after 500 events have been added. You need to fix this.




S