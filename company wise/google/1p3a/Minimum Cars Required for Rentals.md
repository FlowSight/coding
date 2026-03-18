Given a list of rental records, each containing the pickup and return time. You need to calculate the minimum number of cars required to satisfy all requests and return the assignment of rentals for each car. Implement min_cars_required(records: List[Tuple[int, int]]) -> Tuple[int, List[List[int]]], where records is a list of tuples with the pickup and return times for each rental. The return value should be the minimum number of cars and a list of rental assignments for each car. Assume times are represented as integers and the number of records does not exceed $10^5$. Provide test cases.

Example
Input
3
1 4
2 6
5 7