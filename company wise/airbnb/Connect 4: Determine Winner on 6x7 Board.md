Connect 4 Game Check
Implement a function to determine if there's a winner in a given Connect 4 game board. The board is a 6 x 7 2D array where X, O, and empty characters represent the states.

Requirements:

Input is a 6 x 7 2D array.
Output is a string representing the winner ('X' or 'O'), or 'No Winner' if no winner is found.
Check for a streak of four in a row, column, or either diagonal direction.
Test Cases
board1 = [
  ['X', 'X', 'X', 'X', ' ', ' ', ' '],
  ['O', 'O', ' ', ' ', ' ', ' ', ' '],
  ['X', ' ', ' ', 'O', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' ']
]
assert check_winner(board1) == 'X'

board2 = [
  ['O', 'O', 'O', '', ' ', ' ', ' '],
  ['O', 'X', 'X', 'X', 'X', ' ', ' '],
  [' ', ' ', ' ', ' ', 'O', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' ']
]
assert check_winner(board2) == 'X'

board3 = [
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' '],
  [' ', ' ', ' ', ' ', ' ', ' ', ' ']
]
assert check_winner(board3) == 'No Winner'
Hint
You need to scan through each row, column, and diagonal for four consecutive matching pieces.
Example
Input
board = [['X', 'X', 'X', 'X', ' ', ' ', ' '], ['O', 'O', ' ', ' ', ' ', ' ', ' '], ['X', ' ', ' ', 'O', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' ']]