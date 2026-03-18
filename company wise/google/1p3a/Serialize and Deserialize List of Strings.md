Implement two functions: serialize and deserialize.

serialize: Takes a list of strings and serializes it to a single string. Note that strings can contain any numbers and symbols.

deserialize: Takes a serialized string and returns the original list of strings. Implement these functions to handle any possible list of strings.

Assume the number of strings is at most 10^4, and the total length does not exceed 10^5 characters.

Example:

Input: ['abc', '123', '!@#']

Output: serialize(['abc', '123', '!@#']) => "abc_len:3#abc_len:3#123_len:3#!@#" deserialize("abc_len:3#abc_len:3#123_len:3#!@#") => ['abc', '123', '!@#']

Example
Input
['abc', '123', '!@#']
