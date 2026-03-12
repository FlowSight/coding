You are given an array of commands. There are only three possible commands: cmd1, cmd2, and cmd3. Your task is to return an array of size 3 that contains the frequency of each command in the input array, in the order [frequency of cmd1, frequency of cmd2, frequency of cmd3].

Also, any element in the form of ![index] refers to the same command that was present at the position in the input array. Note that indexing starts from 1 (not 0).

Function Description

Complete the function commandFrequencyCounter in the editor.

commandFrequencyCounter has the following parameter:

String[] commands: an array of commands
Returns

int[]: an array of size 3 containing the frequency of each command

Constraints: :)

Example
Input
commands = ["cmd1", "cmd2", "cmd3", "!1", "!2", "cmd3", "cmd1"]
Output
[3, 2, 2]