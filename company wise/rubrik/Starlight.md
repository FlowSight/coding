The presented problem involves an astral constellation, depicted as an array of n integers where each representing the luminosity of a star. The beauty of this constellation is determined by the maximum overall sum of luminance of any consecutive light cluster. It could range from none of the stars to all the stars of the constellation.

Bear in mind an example of a constellation represented by the array [20, -9, 0, 4, 0] the beauty of this constellation is 21. On the other hand, a constellation represented by [-3, -5, -1, -4] has a beauty of 0 units.

Assume that you are equipped with a cosmic amplifier, having a power multiplier of z. This device allows you to magnify the luminescence of any chosen segment within the constellation by a factor of z. Here comes the challenge: You can use this amplification at most once, so the task is to decipher how to maximize the beauty constellation after this amplification procedure.

Function Description

Complete the function enhanceLuminescence.

enhanceLuminescence has the following parameters:

int arr[n]: represents the individual luminescence of each celestial entity within the constellation.
int z: the power multiplier that can be applied to a chosen sequence within the constellation.
Returns

int: the maximum possible beauty of the arrangement after applying the amplification.

Constraints:

The size of the stars array, n, lies in the range of 1 ≤ n ≤ 2 * 10^5.
The elements of the stars array, a1, a2, a3, ..., lie in the range 10^-9 ≤ ai ≤ 10^9.
The amplification power, z, lies in the range -100 ≤ z ≤ 100.
Example
Input
arr = [3, 2]
z = 2
Output
10