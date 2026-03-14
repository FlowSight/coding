Problem: Guess the hidden word with positional match feedback (Interactive)
You are given a candidate list wordlist (all words have the same length, commonly 6). One word in the list is the hidden target word secret.

You may make at most 10 guesses. For each guessed word guess, the system returns an integer match, the number of positions where guess[i] == secret[i].

Design a strategy to find secret within 10 guesses.

Notes
This is an interactive problem: in practice you call an API such as Master.guess(word) which returns match.
You need to implement the strategy: after each feedback, filter the candidate set and choose the next guess.
Typical Constraints
1 <= len(wordlist) <= 100
All words have the same length (commonly 6)
Max guesses: 10
Output
No explicit output in a real interactive environment.
The goal is to guarantee or strongly increase the chance of finding secret within 10 guesses under the constraints.