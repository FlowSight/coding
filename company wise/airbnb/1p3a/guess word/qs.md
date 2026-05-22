to guess a four-digit number.

Example:
    # correct code: 3264
    # GUESS 1111 => 0 0 (no correct digits)
    # GUESS 1214 => 2 0 (digits 2 and 4 are correct and on the correct position)
    # GUESS 6111 => 0 1 (digit 6 is present, but on a different position)
    # GUESS 6211 => 1 1 (digit 2 is not counted towards the second count!)

You need to connect to a server when writing this.

    # START\n
    # GUESS 1111\n => 0 0
    # etc.....



variation 2:
Guess a number. 
Guess a 4-digit number, where each digit is from 1 to 6. 
Provide an API that takes a number as input and returns the number of digits that were guessed correctly. For example, if the number to be guessed is 1234, and the guessed number is 1111, then return 1. If the guessed number is 1212, then return 2. 
Write a program that calls this API multiple times and returns the guessed number. 1111, 2222, 3333, 4444, 5555. Find 4 numbers in 5 tries. 
6666 doesn't need to be found because guess(6666) = 4 - (guess(1111) + ... + guess(5555)). 
Then try a1a1a1a1, a1a2a2a2, a1a3a3a3. Similarly, a1a4a4a4 doesn't need to be tried. 
The goal is to find the combination of the last three numbers (not a permutation). 
Finding the last 3 numbers determines the first number, and in this round, a1a1a1a1 doesn't need to call the API, as it's already in the first round. 
Second round (2 times): Fix the first number and find the combination of the last 3 numbers. Similarly, in the third round...
 Next: Fix the second number, find the combination of the last two numbers. 
there's one more round in the fourth round. Test one permutation of the last two numbers. The rest is... But thinking about it, this round might not be necessary. Correction: The best I can think of right now is 5 + 2 + 1 = 8 times.