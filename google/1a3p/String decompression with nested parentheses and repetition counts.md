Problem
Implement a string decompression function decompress(s: str) -> str.

The input contains:

lowercase letters a-z
parentheses ( and ) denoting a subexpression
braces {} that appear immediately after a right parenthesis ) to indicate repeating the parenthesized subexpression
Rules:

X(Y){k} means output X followed by Y repeated k times.
Parentheses may be nested.
k is in [2, 99].
The input is guaranteed valid (no need to handle malformed parentheses/braces), and { always appears after the matching ).
Examples:

"a(abc){3}" -> "aabcabcabc"
"a(b(c){2}){3}d" -> "abccbccbccd"
Constraints
1 <= len(s) <= 2 * 10^5
Output may be large; generating the full string is acceptable unless it exceeds memory (you may mention streaming as an optimization).
Task
Return the decompressed string.

Example
Input
a(abc){3}
Output
aabcabcabc