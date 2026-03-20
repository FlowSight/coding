In a neighborhood, there are N empty houses numbered from 1 to N arranged in a line. Each day, starting from day 1, one house will be occupied by residents. The sequence of occupied houses is given as a permutation of length N. On the ith day, the house with the number given by the ith element of the permutation will be occupied.

The neighborhood will be considered happy if there is at least one set of consecutive occupied houses. On which day will the neighborhood become happy?

Note: A permutation of length N is an array of N integers where each element is between 1 and N, with no repetitions.

Function Description

Complete the function solve. This function takes the following 3 parameters and returns the required answer:

N: Represents the number of houses
M: Represents the number of consecutive houses needed
house: Represents an array indicating the house that will be filled on each day
Input format for custom testing

Note: Use this input format if you are testing against custom input or writing code in a language where we don't provide boilerplate code.

The first line contains N denoting the number of houses.
The second line contains M denoting the number of consecutive houses needed.
The third line contains an array house denoting the house that will be filled on each day.
Output format

Print a single integer representing the first day on which the neighborhood becomes happy.

Constraints: ``

Example
Input
N = 3
M = 1
house = [3, 2, 1]
Output
1