ISRO is tasked with launching a set of satellites to monitor specific regions on Earth. Each satellite has a limited range within which it can gather data. The goal is to deploy the minimum number of satellites necessary to cover a set of target regions on Earth completely.

You are given:

An array of target regions, each represented as an interval [start, end], which shows the latitude range of Earth that requires monitoring.
A set of satellites, each having a monitoring range [coverageStart, coverageEnd].
Write an algorithm to calculate the minimum number of satellites required to cover all given target regions completely. If coverage is not possible, return -1.

Additional Details:

Each satellite can cover any region within its range.
Overlapping satellite ranges can be used to extend coverage.
No partial coverage is allowed—a region must be fully covered by one or more satellites.
Constraints: :)

Example
Input
targetRegions = [[1, 5], [6, 10], [11, 15]]
satellites = [[1, 6], [5, 9], [10, 15]]
Output
3