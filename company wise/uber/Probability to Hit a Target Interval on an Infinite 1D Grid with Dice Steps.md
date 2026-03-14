Problem: Winning Probability of Hitting a Target Interval on an Infinite 1D Grid
You start at position 0 on an infinite 1D integer grid.

You repeatedly do the following:

Roll a die that returns an integer d in 1..K (uniformly at random).
Move from position x to x + d.
Given a target closed interval [mn, mx] (with 0 <= mn <= mx):

You win if after some roll your position enters the interval [mn, mx] for the first time (i.e., you reach some x with mn <= x <= mx).
You lose if you ever move to a position > mx before entering the interval, since you can never come back.
Compute the probability of eventually winning starting from 0.

Input
A single line with three integers:

K mn mx
Output
Print a floating-point number: the winning probability. Absolute/relative error up to 1e-6 is accepted.

Constraints
1 <= K <= 1e5
0 <= mn <= mx <= 1e5
Examples
Input:

6 7 9
Output:

0.5
Input:

1 3 3
Output:

1.0
Input:

2 1 1
Output:

0.5
Input:

3 2 3
Output:

0.7777777778
Input:

10 0 0
Output:

1.0
Example
Input
6 7 9
Output
0.5000000000