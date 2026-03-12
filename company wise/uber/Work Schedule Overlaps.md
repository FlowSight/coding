Given a delivery service couriers' schedule, couriers[i] = [start, end] represents the working time interval of the i-th courier where start is inclusive and end is exclusive. The intervals may overlap. The task is to return a list of sublists, outputting a sublist each time the number of couriers working simultaneously changes. The third element of each sublist represents the number of couriers working simultaneously.

For example: Given couriers = [[1, 5], [3, 7]], the output should be [[1, 3, 1], [3, 5, 2], [5, 7, 1]].

Example
Input
[[1, 5], [3, 7]]