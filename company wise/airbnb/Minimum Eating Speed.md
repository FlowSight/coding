Your daughter, Alex, has just come home with a bag full of candy after a long night of trick-or-treating. Before going to sleep, Alex places the candy in numPiles piles with the i-th pile containing candyPiles[i] number of candies.

After arranging the candies into piles, Alex announces she is going to sleep for numHours hours.

Your plan is to eat all the candy before Alex wakes up in numHours. You can eat c candies per hour, but in each hour you will only eat candy from a single pile. If a pile contains fewer than c candies, you will only eat the number of candies in that pile and you will wait until the next hour to eat more candy.

Having a little bit of self-restraint your goal is to calculate the smallest number of candies c you need to eat per hour in order to finish all the candy before Alex wakes up again.

Function Description

Complete the function minimumEatingSpeed in the editor.

minimumEatingSpeed has the following parameters:

int[] candyPiles: an array of integers representing the number of candies in each pile
int numHours: the number of hours Alex will be asleep for
Returns

int: the smallest number of candies c that you need to eat per hour in order to finish all the candies before Alex wakes up

Constraints: TO-DO

Example
Input
candyPiles = [4, 9, 11, 17]
numHours = 8
Output
6