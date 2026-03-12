Given a logs array, where each entry represents a record of a function call at a specific time. Each log entry is separated into three parts by colons: function ID, call state (start or end), and timestamp. Calculate the exclusive time of each function, taking into account the multithreaded nature and potential nested calls. The requested time is exclusive time, meaning it does not include nested calls. The input function IDs are in increasing order, and the output should follow this order. Each 'start' record has a corresponding 'end' record. Provide an algorithm to compute the exclusive execution time of each function.

Example
Input
2
0:start:0
1:start:2
1:end:5
0:end:6
