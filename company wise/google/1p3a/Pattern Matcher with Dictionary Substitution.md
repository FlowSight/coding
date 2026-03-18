Question
Given a string str and a dictionary dict, where the string contains patterns enclosed within %. Replace each pattern with the value in the dictionary. If a value cannot be found, return error.

Input
A string str with patterns in the format %pattern%.
A dictionary dict with patterns as keys and replacement strings as values.
Output
The modified string after replacement. If substitution fails, return error.
Example
Input: str = "a%sd%fasd%dog%sdfisan", dict = {"sd": "START", "dog": "DOG"}

Output: "aSTARTfasdDOGsdfisan"

Input: str = "%rat% in the %hat%", dict = {"cat": "CAT"}

Output: "error"

Example
Input
"a%sd%fasd%dog%sdfisan"
{"sd": "START", "dog": "DOG"}