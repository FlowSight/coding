Given a sentence and a list of words, check each word in the sentence for the presence of any word from the list. If found, enclose the matching part in brackets [].

Input
A string representing the sentence.
A list of strings representing the words.
Output
A string representing the processed sentence.
Example
Input: sentence = "hello uber", words = ["ll", "ub"]
Output: "he[ll]o [ub]er"
Constraints
The length of the sentence does not exceed 1000.
The total length of characters in the word list does not exceed 200.
Example
Input
hello uber
ll ub