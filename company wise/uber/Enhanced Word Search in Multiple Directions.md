In a 2D character grid, find all words that can be formed by sequences of consecutive characters moving in eight possible directions: up, down, left, right, and all four diagonals. Implement a function to search and return all such words. Each word in the grid should not repeat. Assume the word list is non-empty and each word has at most 10 characters. The grid size is 10x10.

Input:

A character grid 'board'.
A list of strings 'words' containing the words.
Output:

A list of all words that can be found in the grid.
Example:

Input:
board = [
  ['a', 'b', 'c', 'd'],
  ['n', 'm', 'l', 'k'],
  ['o', 'p', 'q', 'r'],
  ['s', 't', 'u', 'v']
],
words = ['abcd', 'opr', 'mk', 'uv']
Output: ['abcd', 'opr', 'uv']
All words should be printed from top to bottom, left to right.

Example
Input
{'board': [['a', 'b', 'c', 'd'], ['n', 'm', 'l', 'k'], ['o', 'p', 'q', 'r'], ['s', 't', 'u', 'v']], 'words': ['abcd', 'opr', 'mk', 'uv']}