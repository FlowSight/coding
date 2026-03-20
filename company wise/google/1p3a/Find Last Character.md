You are given an alphanumeric string S and an integer K. Consider a new string in which S is appended K-1 times. Now, in this new string, the following operations are performed:-

Every alternate character starting from the first character is removed.
Every alternate character starting from the last character is removed.
The above two operations are repeated until one character remains. Your task is to find and return a string representing the last remaining character after performing all the operations.

Note: Here, alphanumeric refers to the string that may contain alphabets (a-z and A-Z), numerals (0-9), and certain special characters such as '$', '#', '&', and '*'

Input Specification:

input1: A string S, representing the alphanumeric string.

input2: An integer value K.

Output Specification:

Return a string representing the last remaining character after performing all the operations mentioned.

Constraints: N/A 

Example
Input
S = "abcd"
K = 3
Output
"b"