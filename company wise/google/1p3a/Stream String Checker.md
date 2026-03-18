Implement a program to process an input stream. Each input is in the format of [timestamp, string], and the program needs to output all unique strings within the last 60 seconds. If a duplicate string is found, the current string should be dropped and not appear in the output. The follow-up requires dropping all duplicates within the last 60 seconds once a duplicate is found. Specific requirements are as follows:

Each input is an array in the format of [timestamp, string].
timestamp is an integer representing time in seconds.
In the output, return all strings without duplicates from the last 60 seconds.
If a certain input lists a string that has appeared within the last 60 seconds, the string from this input is dropped.
In the follow-up handling requirement, if an input string appears again, all duplicate strings within 60 seconds should be dropped.
Example:

Suppose the input stream is:

[0, 'a']
[30, 'b']
[60, 'a']
[61, 'c']
[120, 'a']
The output will be:

['a', 'b', 'c']
When 'a' appears the second time, since it reappears within the past 60 seconds, it is dropped.

Can this program handle these requirements correctly?

Example
Input
0 a
30 b
60 a
61 c
120 a