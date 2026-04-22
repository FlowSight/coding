In Amazon EC2, there are n virtual machine (VMs) types, and each type has a limited number of instances available. Each time a VM instance is rented, the customer pays a fee equal to:

the lowest non-zero availability among all VM types + the highest availability among all VM types
There are m customers arriving one by one. Each customer always rents from the VM type that currently has the highest availability. After a rental, the availability of that VM type decreases by 1. The task is to determine the total revenue earned after serving all rental requests.

Example:

n = 3 vmStock = [1, 2, 4] m = 4

There are 3 different types of VMs available with 4 customer requests.

Initial state: Customer | VM type | Cost | Remaining 1 | 3 | 1+4=5| [1, 2, 3] 2 | 3 | 1+3=4| [1, 2, 2] 3 | 2 (or 3)| 1+2=3| [1, 1, 2] 4 | 3 | 1+2=3| [1, 1, 1]

The revenue earned is 5+4+3+3=15, so the answer is 15.

Example
Input
3
[1, 2, 4]
4
Output
15