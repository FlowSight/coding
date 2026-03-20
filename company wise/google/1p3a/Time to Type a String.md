magine you have a special keyboard with all keys in a single row. The layout of characters on a keyboard is denoted by a string keyboard of length 26. Initially your finger is at index 0. To type a character, you have to move your finger to the index of the desired character. The time taken to move your finger from index i to index j is abs(j - i).

Given a string keyboard that describe the keyboard layout and a string text, return an integer denoting the time taken to type string text.

Function Description

Complete the function calculateTime in the editor.

calculateTime has the following parameters:

String keyboard: a string that describes the keyboard layout
String text: the text to be typed
Returns

int: the time taken to type the string text

Constraints:

length of keyboard will be equal to 26 and all the lowercase letters will occur exactly once;
the length of text is within the range [1..100,000];
string text contains only lowercase letters [a-z].
Example
Input
keyboard = "abcdefghijklmnopqrstuvwxy"
text = "cba"
Output
4