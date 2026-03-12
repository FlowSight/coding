Imagine you have a square matrix of numbers, and you're given a set of instructions, called queries, to transform this matrix in different ways. Depending on the query, you might rotate the matrix 90 degrees clockwise, reflect it along its main diagonal, or reflect it along its secondary diagonal. Your task is to apply all these transformations in the order given and return the matrix after it's been beautifully transformed by each of the queries. Don't worry about finding the most efficient way to do this; just ensure your approach isn't too slow for the given task.

Constraints: ``

Example
Input
a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
q = [0, 1, 2]
Output
[[3, 6, 9], [2, 5, 8], [1, 4, 7]]