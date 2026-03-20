Given an array of strings, where each element is a sentence in the format [["word1", "word2", ...], [...]], and a specific word word, find the word most likely to appear next. Count the frequency of words following each word and return the word that has the highest frequency following the current word.

Example:

Input: sentences = [["I", "am", "Sam"], ["Sam", "I", "am"]], word = "am" Output: "Sam"

Example
Input
[["I", "am", "Sam"], ["Sam", "I", "am"]] "am"