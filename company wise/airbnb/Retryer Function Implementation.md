Design a retryer function that takes an asynchronous function and a maximum number of retries. The retry delay should grow exponentially (e.g., 2 seconds, 4 seconds, 8 seconds, etc.). If the asynchronous function succeeds within the maximum retries, return the result; if it fails after the maximum retries, throw an error.

Input
func: an asynchronous function to retry, with no parameters.
max_retries: an integer specifying the maximum number of retries.
Output
Returns the result of the asynchronous function or throws an error.
Example
async def my_async_function():
    # Simulate a potentially failing async call

result = await retryer(my_async_function, 3)
Constraints
Assume each call to the async function is independent and has no global state.
Exponential backoff should wait for a maximum of 16 seconds, use await asyncio.sleep() to simulate wait time.
Example
Input
async def test_func1():
    raise Exception("Failure")
await retryer(test_func1, 3)