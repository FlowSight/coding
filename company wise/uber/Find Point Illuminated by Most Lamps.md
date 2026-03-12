There are some lamps placed on a coordinate line. Each of these lamps illuminates some space around it within a given radius. You are given the coordinates of the lamps on the line, and the effective radius of the lamps' light.

In other words, you are given a two-dimensional array lamps, where lamps[i] contains information about the ith lamp. lamps[i][0] is an integer representing the lamp's coordinate, and lamps[i][1] is a positive integer representing the effective radius of the ith lamp. That means that the ith lamp illuminates everything in a range from lamps[i][0] - lamps[i][1] to lamps[i][0] + lamps[i][1] inclusive.

Your task is to find the coordinate of the point that is illuminated by the highest number of lamps. In case of a tie, return the point among them with the minimal possible coordinate.

Constraints: TO-DO

Example
Input
lamps = [[-2, 3], [2, 3], [2, 1]]
Output
1