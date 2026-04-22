Given a directed graph representing course prerequisites, determine if all courses can be completed. You are given an integer n representing the number of courses, and an array prerequisites where prerequisites[i] = [ai, bi] indicates you must take course bi before course ai. Write a function to check if all courses can be completed.

Input/Output Format

Input:
n (int) for number of courses.
prerequisites (List[List[int]]) for course prerequisites.
Output:
True (bool) if all courses can be completed.
False otherwise.
Example Input

Number of Courses: 2
Course List: [[1, 0]]
Example Output

True
Example
Input
2
[[1, 0]]