Problem: Convert Reverse Polish Notation to Infix (Minimal Parentheses)
You are given a comma-separated Reverse Polish Notation (RPN) string s. Each token is either:

an integer (may have multiple digits), e.g. 2, 13
a binary operator: +, -, *, /
Convert the RPN expression into an equivalent infix expression string:

The output must be a valid infix expression using + - * /.
Use as few parentheses as possible: add parentheses only when needed to preserve operator precedence and associativity and avoid ambiguity.
Examples
Example 1

Input: 2,1,+,3,*
Output: (2+1)*3
Example 2

Input: 4,13,5,+,/
Output: 4/(13+5)
Requirements
Handle any valid RPN expression.
Parentheses in the output should be minimal while preserving the exact meaning.
Constraints (assumptions for implementation)
1 <= number of tokens <= 1e5
The expression is guaranteed to be valid.
Each integer token length <= 10
Output
Return a string representing the infix expression.

Example
Input
2,1,+,3,*
Output
(2+1)*3