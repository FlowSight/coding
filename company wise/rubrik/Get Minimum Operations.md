Given two arrays change and arr that consist of n and m integers respectively.

In the ith operation, one of the two operations can be performed:

you can choose to decrement any element of arr by 1 or do nothing.
if change[i] > 0 and arr[change[i]] = 0, it can be changed to NULL.
Assume indexing starts from 1, find the minimum number of operations required to change all the elements of the array to NULL or report -1 if it is not possible.

Function Description

Complete the function getMinOperations in the editor below.

getMinOperations has the following parameter(s):

int change[n]: an array of integers
int arr[m]: an array of integers
Returns

int: the minimum number of operations required to change all the elements to NULL, or -1 if it is not possible

Constraints: :o

Example
Input
change = [0, 1, 0, 2]
arr = [1, 1]
Output
4

hint : iter i=1 to n, keep track of noops ie. ops where nullify isnt possible