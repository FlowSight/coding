Two players have their own set of cards. In each turn, both draw the top card from their respective decks. If player1's card is greater than or equal to player2's card, player2's card is appended to player1's deck. Otherwise, player1's card is appended to player2's deck. The order of appending: the winner's card first, then the loser's card. The game continues until one player has no cards left. The question is: what is the maximum number of moves the game can last? Assume the initial cards are unique and positive integers. Test case 1: player1 = [3, 4, 5]; player2 = [6, 1, 2]; Result: the game lasts 3 steps. Scale: 1 <= number of cards <= 100.

Example
Input
3,4,5
6,1,2