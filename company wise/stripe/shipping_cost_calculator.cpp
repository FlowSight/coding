Interview Problem: Shipping Cost Calculator
Problem Summary
You need to write code to calculate shipping costs for an online store. The cost depends on the country and the type of product.

This interview problem has three steps. It starts simple and gets harder:

Simple Fixed Price: Each item has a set price.
Volume Discounts: The price changes based on how many items you buy (tiers).
Mixed Pricing Types: Some ranges charge per item, while others charge a flat fee.
Data Format
You get two pieces of data:

1. Order Object: This tells you the country and the list of items being bought.

{
    "country": "US",
    "items": [
        {"product": "mouse", "quantity": 20},
        {"product": "laptop", "quantity": 5}
    ]
}
2. Shipping Cost Rules: This is a dictionary that holds the price rules for each country and product. The format changes slightly in each step.

Step 1: Simple Fixed Price
The Task
Write a function called calculate_shipping_cost(order, shipping_cost). It must calculate the total cost when every product has one fixed price per unit.

Example Case
Input:

order_us = {
    "country": "US",
    "items": [
        {"product": "mouse", "quantity": 20},
        {"product": "laptop", "quantity": 5}
    ]
}

order_ca = {
    "country": "CA",
    "items": [
        {"product": "mouse", "quantity": 20},
        {"product": "laptop", "quantity": 5}
    ]
}

shipping_cost = {
    "US": [
        {"product": "mouse", "cost": 550},
        {"product": "laptop", "cost": 1000}
    ],
    "CA": [
        {"product": "mouse", "cost": 750},
        {"product": "laptop", "cost": 1100}
    ]
}
Output:

calculate_shipping_cost(order_us, shipping_cost) == 16000
# Math: (20 × 550) + (5 × 1000) = 11000 + 5000 = 16000

calculate_shipping_cost(order_ca, shipping_cost) == 20500
# Math: (20 × 750) + (5 × 1100) = 15000 + 5500 = 20500
Key Requirements
Handle orders with multiple different products.
Use the correct prices for the specific country.
Return the answer as an integer (whole number).
Step 2: Volume Discounts
The Task
Update your function to handle "tiered pricing." This means the cost per unit changes based on the quantity.

Each tier has a start number (minQuantity) and an end number (maxQuantity). This works like a bulk discount—buying more units might lower the price for the extra items.

Example Case
Input:

# Orders remain the same as Part 1

shipping_cost = {
    "US": [
        {
            "product": "mouse",
            "costs": [
                {"minQuantity": 0, "maxQuantity": None, "cost": 550}
            ]
        },
        {
            "product": "laptop",
            "costs": [
                {"minQuantity": 0, "maxQuantity": 2, "cost": 1000},
                {"minQuantity": 3, "maxQuantity": None, "cost": 900}
            ]
        }
    ],
    "CA": [
        {
            "product": "mouse",
            "costs": [
                {"minQuantity": 0, "maxQuantity": None, "cost": 750}
            ]
        },
        {
            "product": "laptop",
            "costs": [
                {"minQuantity": 0, "maxQuantity": 2, "cost": 1100},
                {"minQuantity": 3, "maxQuantity": None, "cost": 1000}
            ]
        }
    ]
}
Output:

calculate_shipping_cost(order_us, shipping_cost) == 15700
# Math:
# mouse: 20 × 550 = 11000 (standard rate)
# laptop: (2 × 1000) + (3 × 900) = 2000 + 2700 = 4700
# Total: 11000 + 4700 = 15700

calculate_shipping_cost(order_ca, shipping_cost) == 20200
# Math:
# mouse: 20 × 750 = 15000
# laptop: (2 × 1100) + (3 × 1000) = 2200 + 3000 = 5200
# Total: 15000 + 5200 = 20200
Key Requirements
Process the rules in order from lowest quantity to highest.
If maxQuantity is None, it means there is no limit for that tier.
The range includes the start number but stops before the end number ( [min, max) ).
Calculate the cost for each tier separately and add them up.
Clarification Questions
Are the tiers always sorted by minQuantity?
Do the ranges include the maxQuantity number or exclude it?
Are there gaps between tiers, or do they overlap?
What should happen if the quantity is zero?
Step 3: Mixed Pricing Types
The Task
Now, the system needs to support two different ways to charge for a tier:

incremental: Charge per unit (Quantity × Cost). This is the same as Step 2.
fixed: Charge one flat fee for the whole tier, no matter how many items are in it.
A single product can mix these types. For example, the first 2 items might be a fixed fee, and the rest are per unit.

Example Case
Input:

# Orders remain the same

shipping_cost = {
    "US": [
        {
            "product": "mouse",
            "costs": [
                {
                    "type": "incremental",
                    "minQuantity": 0,
                    "maxQuantity": None,
                    "cost": 550
                }
            ]
        },
        {
            "product": "laptop",
            "costs": [
                {
                    "type": "fixed",
                    "minQuantity": 0,
                    "maxQuantity": 2,
                    "cost": 1000
                },
                {
                    "type": "incremental",
                    "minQuantity": 3,
                    "maxQuantity": None,
                    "cost": 900
                }
            ]
        }
    ],
    "CA": [
        {
            "product": "mouse",
            "costs": [
                {
                    "type": "incremental",
                    "minQuantity": 0,
                    "maxQuantity": None,
                    "cost": 750
                }
            ]
        },
        {
            "product": "laptop",
            "costs": [
                {
                    "type": "fixed",
                    "minQuantity": 0,
                    "maxQuantity": 2,
                    "cost": 1100
                },
                {
                    "type": "incremental",
                    "minQuantity": 3,
                    "maxQuantity": None,
                    "cost": 1000
                }
            ]
        }
    ]
}
Output:

calculate_shipping_cost(order_us, shipping_cost) == 14700
# Math:
# mouse: 20 × 550 = 11000 (incremental)
# laptop: 1000 (fixed fee for first 2) + (3 × 900) = 1000 + 2700 = 3700
# Total: 11000 + 3700 = 14700

calculate_shipping_cost(order_ca, shipping_cost) == 19100
# Math:
# mouse: 20 × 750 = 15000 (incremental)
# laptop: 1100 (fixed fee for first 2) + (3 × 1000) = 1100 + 3000 = 4100
# Total: 15000 + 4100 = 19100
Key Requirements
Check the pricing type (fixed or incremental).
Fixed: Add the cost once if the items fall into this tier.
Incremental: Multiply the quantity by the cost.
Handle patterns that switch back and forth between types.
How to Solve It
Solution for Step 1
Plan:

Get the country code from the order.
Make a lookup table (Dictionary) to find the cost for each product quickly.
Loop through the items in the order.
For each item, do: quantity × cost and add it to the total.
Time Complexity: O(n + m) (where n is the number of price rules and m is the number of items ordered). Space Complexity: O(n) (to store the price lookup table).

Code Implementation:

def calculate_shipping_cost(order, shipping_cost):
    country = order["country"]
    cost_map = {}

    # Create a quick way to find price by product name
    for product_info in shipping_cost[country]:
        cost_map[product_info["product"]] = product_info["cost"]

    total = 0
    for item in order["items"]:
        product = item["product"]
        quantity = item["quantity"]
        total += quantity * cost_map[product]

    return total
Edge Cases:

What if the items list is empty?
What if a product is missing from the price list?
What if the quantity is negative?
Solution for Step 2
Plan:

Create a lookup table that maps product names to their list of tiers.
For each item, keep track of how many units you still need to pay for (remaining).
Loop through the tiers in order:
Figure out how many units fit into the current tier.
Calculate the cost for those specific units.
Subtract those units from remaining.
Stop when all units are paid for.
Math Detail: The "capacity" of a tier is maxQuantity - minQuantity. The number of units that fall in a tier is the smaller number between remaining and capacity.

Time Complexity: O(n × t + m × t) (where t is the average number of tiers).

Code Implementation:

def calculate_shipping_cost(order, shipping_cost):
    country = order["country"]
    cost_map = {}

    # Map product to its list of cost tiers
    for product_info in shipping_cost[country]:
        cost_map[product_info["product"]] = product_info["costs"]

    total = 0
    for item in order["items"]:
        product = item["product"]
        quantity = item["quantity"]
        remaining = quantity

        for tier in cost_map[product]:
            if remaining <= 0:
                break

            min_qty = tier["minQuantity"]
            max_qty = tier["maxQuantity"]
            cost = tier["cost"]

            # Figure out how many items fit in this tier
            if max_qty is None:
                tier_units = remaining
            else:
                tier_capacity = max_qty - min_qty
                tier_units = min(remaining, tier_capacity)

            total += tier_units * cost
            remaining -= tier_units

    return total
Important Notes:

Make sure you understand if the ranges are inclusive or exclusive.
Handle the maxQuantity: None case carefully—it acts as an infinity.
Solution for Step 3
Plan:

Use the same logic as Step 2.
Add an if statement to check the type.
If type is "fixed", add the cost directly. Do not multiply by quantity.
If type is "incremental", multiply quantity × cost.
Code Implementation:

def calculate_shipping_cost(order, shipping_cost):
    country = order["country"]
    cost_map = {}

    for product_info in shipping_cost[country]:
        cost_map[product_info["product"]] = product_info["costs"]

    total = 0
    for item in order["items"]:
        product = item["product"]
        quantity = item["quantity"]
        remaining = quantity

        for tier in cost_map[product]:
            if remaining <= 0:
                break

            min_qty = tier["minQuantity"]
            max_qty = tier["maxQuantity"]
            cost = tier["cost"]
            pricing_type = tier["type"]

            # Figure out how many items fit in this tier
            if max_qty is None:
                tier_units = remaining
            else:
                tier_capacity = max_qty - min_qty
                tier_units = min(remaining, tier_capacity)

            # Apply logic based on the type
            if pricing_type == "fixed":
                total += cost
            else:  # incremental
                total += tier_units * cost

            remaining -= tier_units

    return total
Bonus Discussion Topics
Improving the Code
Question: How would you make this code better for a real production system?

Ideas:

Split it up: Move the logic for calculating a single tier into its own function.
Add Types: Use Python type hints so it is easier to read and debug.
Handle Errors: Make sure the code does not crash if data is missing.
Testing: Write tests to check edge cases.
Refactoring Example:

from typing import Dict, List, Optional
from dataclasses import dataclass

@dataclass
class TierCost:
    type: str
    min_quantity: int
    max_quantity: Optional[int]
    cost: int

def calculate_tier_cost(quantity: int, tier: TierCost) -> tuple[int, int]:
    """
    Calculate cost for a single tier and return (cost, units_consumed).
    """
    if tier.max_quantity is None:
        tier_units = quantity
    else:
        tier_capacity = tier.max_quantity - tier.min_quantity
        tier_units = min(quantity, tier_capacity)

    if tier.type == "fixed":
        calculated_cost = tier.cost
    else:
        calculated_cost = tier_units * tier.cost

    return calculated_cost, tier_units

def calculate_product_cost(quantity: int, tiers: List[TierCost]) -> int:
    """
    Calculate total cost for a product given its quantity and tier structure.
    """
    total = 0
    remaining = quantity

    for tier in tiers:
        if remaining <= 0:
            break

        tier_cost, units_consumed = calculate_tier_cost(remaining, tier)
        total += tier_cost
        remaining -= units_consumed

    return total