Given a list of tasks, where each task is defined by a task ID, a task deadline (as an integer), and a task reward. Each task requires one unit of time to complete. Write an algorithm to maximize the task rewards and return the optimal order of task completion.

For example, if the input is [('a', 2, 8), ('b', 1, 3), ('c', 2, 5), ('d', 3, 3)], the possible outputs are [c, a, d] or [a, c, d].

The requirement is to write an optimized algorithm to solve the problem. Avoid using a greedy algorithm. Improve the solution using specific data structures and implement.

Input:
A list of tasks, where each task is a tuple of (task_id, task_deadline, task_reward).
Output:
A list of task IDs indicating the optimal task completion order to maximize the reward.
Example:
Input: [('a', 2, 8), ('b', 1, 3), ('c', 2, 5), ('d', 3, 3)]
Output: [c, a, d] or [a, c, d]
Constraints:
Up to 1000 tasks.
Constraints:
Each task can only be completed before its deadline.
Hint:
Optimize the algorithm by using sorting and data structure improvements to reduce complexity.
Example
Input
[('a', 2, 8), ('b', 1, 3), ('c', 2, 5), ('d', 3, 3)]