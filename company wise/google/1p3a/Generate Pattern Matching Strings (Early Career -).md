You are given a pattern consisting of alpha characters and [] (square brackets). Anything outside of [] is literal, anything inside [] are alternatives (pick exactly one). Return all strings from a list of strings that match a given pattern. The pattern changes for every call, the list of strings stays the same and can be preprocessed.

Example
Input
pattern = "tele[op]ho[bnm]e"
strings = ["cat", "dog", "telephone", "telephonepole", "tele", "telehoe", "teleophobme"]
Output
["telephone"]