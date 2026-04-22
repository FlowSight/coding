Given a string, encode it based on the following rules:

Use Run-length Encoding (RLE) if there are 8 or more consecutive identical characters.
For other cases, keep the original using a Bin Packing strategy without any encoding.
For any remaining part not making up 8 consecutive characters, prefer RLE if possible.
Also, provide a function to decode the string from this encoding format.

Input: A string consisting of lowercase english letters.

Output:

An encoded string.
The original string.
Test Cases:

Input: "aaaaaaaabbbcc" Output: "8a3b2c" Decode: "aaaaaaaabbbcc"

Input: "abcdefgh" Output: "abcdefgh" Decode: "abcdefgh"

Input: "aaaabbbbcccc" Output: "4a4b4c" Decode: "aaaabbbbcccc"

Input: "a" Output: "a" Decode: "a"

Input: "bbbbbbbbbbb" Output: "8b3b" Decode: "bbbbbbbbbbb"

Constraints:

The length of the input string does not exceed 1000.
Example
Input
aaaaaaaabbbcc