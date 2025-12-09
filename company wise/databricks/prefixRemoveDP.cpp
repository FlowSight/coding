// sev0

// You are given a string S of length N consisting of lowercase English alphabets and an integer K. You need to partition the string until it is empty in the following way,

// Select a maximum length substring from the beginning of string S such that it has at most K distinct characters.

// Delete the selected substring in step-1 from string S.

// You are allowed to change at most 1 character.

// Determine the maximum count of substrings that can be formed until the string S becomes empty.

// Example:

// Assumptions

// N = 7
// K = 3
// S = abcccba
// Approach

// Without changing any character in string S.

// For string S = abcccba.

// The selected substring is "abcccba". On deleting the substring, the string S = ""(an empty string).
// On changing S[3] with character 'z'.

// For string S = abczcba.

// The selected substring is "abc". On deleting the substring the string S = zcba. For string S = zcba.
// The selected substring is "zcb". On deleting the substring the string S = a. For string S = a.
// The selected substring is "a". On deleting the substring the string S = "" (an empty string). Thus the answer is 3. Therefore the answer is 3.