You are managing Amazon's package delivery system, where each delivery truck can carry a certain amount of weight. The truck can only carry a specific amount of weight at a time, which decreases after every delivery. When a truck delivers a package, its weight-carrying capacity is reduced to half (rounded down to the nearest integer, i.e., floor division by 2).

Each package has a weight, and the truck can only carry a package if the truck's capacity is equal to or greater than the package's weight.

You are given t different shipment scenarios, where each scenario has:

An array truckCapacities of length n, representing the maximum weight each truck can carry.
An array packageWeights of length m, representing the weight of each package to be delivered.
For each scenario, determine if delivering all packages using the available set of trucks is possible. If all packages can be delivered, return 1; otherwise, return 0. Return an array of boolean values representing the result for each shipment scenario.

Example:

t = 1 truckCapacities = [[7]] m = 2 packageWeights = [[4, 3]]

There is only 1 shipment scenario in this case. One possible method to deliver the packages is as follows:

Use the truck with a capacity of 7 is used to deliver a package weighing 4. Since the truck's capacity is greater than the package weight, the delivery is successful, and the truck's capacity is reduced to floor(7/2) = 3.
With the current capacity of 3, the truck is then used to deliver another package weighing 3. The delivery is successful, reducing the truck's capacity further to floor(3/2) = 1.
Example
Input
1
[[7]]
[[4,3]]
Output
[1]