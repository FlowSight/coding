Write two functions: a training function and a predictor function.

Training Function: It accepts a list of training sentences, where each sentence is a list of words, and records the frequency of subsequent words for each word.

Predictor Function: It inputs a word and outputs the most likely word that follows it.

Example:

Training data:

[
  ["I", "am", "Sam"],
  ["Sam", "I", "am"],
  ["I", "like", "green", "eggs", "and", "ham"]
]
For word "I", the predictor should return "am".

Follow-up 1:
Optimize the time complexity of the previous predictor function from $O(k)$ (where k is the number of possible subsequent words) to $O(1)$.

Follow-up 2:
Modify the predictor function to return possible following words based on probability. For example, for the word "I", it should return "am" with a probability of 2/3 and "like" with a probability of 1/3.

Example
Input
[["I", "am", "Sam"], ["Sam", "I", "am"], ["I", "like", "green", "eggs", "and", "ham"]]
"I"
Output
am or like