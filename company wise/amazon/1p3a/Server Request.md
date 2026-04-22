You need to handle a series of server requests. Given an array where each element represents the processing time of a request, calculate the minimum total processing time required such that at any moment, the number of requests processed in parallel does not exceed maxRequests. Requests can be processed in parallel but cannot be split. Return the minimum total processing time.

Input:

requests: An integer array representing the processing time of each request.
maxRequests: An integer representing the maximum number of requests that can be processed in parallel by the server.
Output:

An integer representing the minimum total processing time.
Example:

Input:

requests = [3, 2, 4]
maxRequests = 2
Output:

5
Constraints:

1 <= len(requests) <= 10^5
1 <= requests[i] <= 10^4
1 <= maxRequests <= len(requests)
Example
Input
3 2
3 2 4