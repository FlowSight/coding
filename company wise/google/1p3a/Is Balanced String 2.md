Write a function to check if the given input string is balanced or not. The input string will contain parentheses and digits.

whenever digit is occurred you need to remove digit number left side paranathesis in any order (ex: if digit is 2 you need to remove 2 paranthesis from left side means if inp == )(1, either I can remove ( or ) left side of 1). string is balanced if opening paranthesis is equal to closing (ex: (()), ()(), ()), treat each digit seperately if 11 is present in input treat them as 2 ones.

pps: 1 == true, 0 == false

Example
Input
s = "(()1(1)) "
Output
1