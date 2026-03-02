Suggest a split stay where you stay at 2 different houses, one for the first part of your trip and the other for the remainder. Create an API endpoint that will return all possible combos of split stays across 2 listings for a given date range. Each listing is given a name ('A', 'B', etc.) and the availability will be a list of day numbers. For example, given the date range [3-11], the expected result is all sets of two Airbnbs that could form a split stay: [B, C]. Write comprehensive test cases to validate the algorithm.

Example
Input
{"listings": {"A": [1,2,3,6,7,10,11], "B": [3,4,5,6,8,9,10,13], "C": [7,8,9,10,11]}, "start_date": 3, "end_date": 11}