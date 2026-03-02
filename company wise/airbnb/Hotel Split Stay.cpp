Problem Description
Given an integer n, representing n hotels. Each hotel has a list that shows the available dates of the hotel, i.e., the dates when rooms are free. Another given is a date range [start_date, end_date]. You need to split this range into two consecutive subranges, each covered by a different hotel, without overlap and with only forward checking (no backtracking allowed). Your task is to return the hotel combinations where each subrange can be fulfilled by a different hotel, and hotel combinations must not repeat.

Input
n: integer, 2 <= n <= 100.
hotels: a 2D list where hotels[i] represents the list of available dates for the i-th hotel, with dates in “YYYY-MM-DD” format.
start_date: string representing the start date of the request.
end_date: string representing the end date of the request.
Output
Determine if the request can be completely covered by two different hotels and return all possible hotel ID combinations.
Example
Input:
3 [ ["2023-01-01", "2023-01-02", "2023-01-03"], ["2023-01-02", "2023-01-03", "2023-01-04"], ["2023-01-04", "2023-01-05"] ] "2023-01-01" "2023-01-05"

Output:
[(0, 1), (0, 2)]

Example
Input
3
[["2023-01-01", "2023-01-02", "2023-01-03"], ["2023-01-02", "2023-01-03", "2023-01-04"], ["2023-01-04", "2023-01-05"]]
"2023-01-01"
"2023-01-05"