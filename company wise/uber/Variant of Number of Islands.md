Given a 2D grid composed of '1' (land) and '0' (water), calculate the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. Implement in Python using DFS or BFS to find the total number of islands. The grid size ranges from 1x1 to 300x300. Diagonal connections are not considered.\n\nExample 1:\n\n\nInput: grid = \n[['1', '1', '1', '0', '0'], \n ['1', '1', '0', '0', '0'], \n ['0', '0', '1', '0', '0'], \n ['0', '0', '0', '1', '1']]\nOutput: 3\n\n\nExample 2:\n\n\nInput: grid = \n[['1', '1', '0', '0', '0'], \n ['1', '1', '0', '0', '0'], \n ['0', '0', '1', '0', '0'], \n ['0', '0', '0', '1', '1']]\nOutput: 3\n

Example
Input
{'grid': [['1', '1', '1'], ['0', '1', '0'], ['1', '1', '1']]}