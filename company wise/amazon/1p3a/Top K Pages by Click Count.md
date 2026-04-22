Given a log file that records the click counts of various pages, write a function to calculate and return the top K pages with the highest click counts. Assume each line of the log file records a page and its corresponding click count. To ensure efficiency and reliability, a min-heap may be utilized. Consider how to parallelize the handling of a very large log file to derive results efficiently.

Input
int K: The number of top pages to find.
List[Tuple[str, int]] logs: A list where each tuple contains a page name and its corresponding click count.
Output
List[str]: A list of the top K page names with the highest click counts, sorted from highest to lowest click count.
Example
Input: K = 2, logs = [("page1", 3), ("page2", 5), ("page3", 2), ("page4", 5)]
Output: ["page2", "page4"]
Constraints
The size of the log file may be very large, thus consider the performance of your solution.
Example
Input
2
[('page1', 3), ('page2', 5), ('page3', 2), ('page4', 6)]