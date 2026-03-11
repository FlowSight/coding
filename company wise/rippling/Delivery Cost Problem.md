Calculate the total delivery cost based on customer orders and delivery addresses. The delivery cost consists of a base fee and an additional fee depending on the distance. Please write a function to calculate the total delivery cost.

Input:

A list of customer orders, each containing an order id and delivery address.
A list of delivery distances, each distance corresponding to an address (in kilometers).
A base fee (in dollars).
An additional fee per kilometer (in dollars).
Output:

Return a dictionary where the key is the order id and the value is the total cost.
Example:

Input:

total_delivery_cost([{ 'order_id': 1, 'address': 'A' }, { 'order_id': 2, 'address': 'B' }], { 'A': 10, 'B': 25 }, 5, 0.5)

Output: {1: 10.0, 2: 17.5}

Example
Input
orders=[{'order_id': 1, 'address': 'A'}, {'order_id': 2, 'address': 'B'}], distances={'A': 10, 'B': 25}, base_fee=5, additional_fee_per_km=0.5