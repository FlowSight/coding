// Implement a Retryer. Based on object-oriented design principles, write a default retryer and explain how to make it extensible with custom parameters or configurations. Provide detailed code examples demonstrating how to implement the retry strategy. Ensure the code can handle multiple retry scenarios, such as maximum retry attempts, retry interval, and backoff strategies.

// Example Test Cases
// Input:
// Maximum retry attempts: 5
// Retry interval (milliseconds): 100
// Backoff strategy: exponential backoff
// Output:
// Retryer successfully initialized and able to execute under the given retry strategy.