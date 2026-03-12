Given two arrays 'layers' and 'energy', along with an initial energy value K. Assume you start exploring from the i-th level, where layers[i] indicates the energy consumed by this level. If the remaining energy after consumption is greater than or equal to energy[i], the level is considered completed and 1 point is scored. If a level fails, subsequent levels cannot be attempted. Return a list of size n, where each element indicates the score achievable starting from that level.

Example
Input
2