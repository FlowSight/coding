Developers are working on an algorithm for distributing data over regions based on a parameter called affinity defined for each data piece. There are n (n is even) different data pieces where the affinity parameter of the ith piece is represented by affinity[i]. The data needs to be distributed over 2 regions, namely regionA and regionB. In each step of the algorithm, a region is chosen and then a data piece is migrated to that region. The same region cannot be chosen in consecutive steps. Each time a region is selected, it is configured to maximize the total affinity of data it will store.

Moreover, there are certain pre-defined rules for data distribution represented by m unique pairs of indices. For each unique pair (x, y), if the data piece at the indices x or y is selected for a region, the other must be selected for the next region in the next step mandatorily.

Find the maximum possible sum of memory stored in regionA.

Example
Given n = 6, affinity = [3, 2, -4, 8, 3, -7], m = 2, rules = [[2, 4], [3, 6]].

Region | Affinity | Reason --- | --- | --- A | -4 | Forces regionB to choose -7 because of rule (3, 6) B | -7 | Forced by rule (3, 6) A | 8 | Forces regionB to choose 2 because of rule (2, 4) B | 2 | Forced by rule (2, 4) A | 3 | Maximum affinity out of the remaining B | 3 | Last available data piece

Example
Input
6
3 2 -4 8 3 -7
2
2 4
3 6