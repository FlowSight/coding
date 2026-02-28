We are given an array representing the number of instances available for each machine type.
 Customers arrive one by one (M customers total).

For each customer:

Allocate an instance from the machine type having the maximum available instances.

The cost incurred by that customer =
(maximum instances before allocation) + (minimum non-zero instances currently present).

After allocation, reduce that machine’s instance count by 1.

Continue until all customers are processed or instances run out.

We need to return the total cost incurred by all customers.

Example:
Instances = [1, 3, 2, 4]
Customer 1 → max=4, min=1 → cost=5 → array becomes [1,3,2,3]
…and so on.