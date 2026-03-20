"\n

\n \n- You have a list of meetings in your calendar with a start and end time. \n- You are very busy, so meetings can overlap. \n- You also have one "Do Not Schedule" (DNS) interval during which you don't attend any meeting. \n- \n Any meeting schedule that overlaps with a DNS slot is automatically cut such that it does not overlap with the DNS slot anymore.\n \n\n

\n Return a list of non-overlapping time intervals when you are in a meeting.\n

\n \n

\n ![](.concat(nh.default.src, )\n

\n\n

\n Function Description\n

\n Complete the function getMeetingIntervals in the editor.\n

\n

\n getMeetingIntervals has the following parameters:\n

\n2. 1. int[][] meetings: an arr of intervals representing meeting times \n4. 2. Interval dns: an interval representing the "Do Not Schedule" time \n \n

\n\n

\n Returns\n

\n int[][]: an arr of non-overlapping intervals when you are in a meeting\n

\n

\n

\n\n

\n ")

Constraints: :)

Example
Input
meetings = [[1, 7], [5, 10], [12, 30], [22, 30], [40, 50], [60, 70]]
dns = [18, 25]
Output
[[1, 10], [12, 18], [25, 30], [40, 50], [60, 70]]