Design a system to manage corporate credit card usage rules and flag expenses and trips that violate them.

We plan to offer a corporate credit card to companies that employees can use for business expenses. Managers can set policies on the cards so that employees do not misuse the card or exceed allowances. We are building a rules engine to support this product. Please ask product-oriented questions and share your assumptions. We'll start with some very basic rules:

No expense at a restaurant can exceed $75 ("vendor_type" == "restaurant")
No airfare expenses ("expense_type" == "airfare")
No entertainment expenses ("expense_type" == "entertainment")
No expenses over $250
A trip cannot exceed $2000 in total expenses
Total meal expenses cannot exceed $200 per trip
Design a system to handle these rules and flag expenses and trips that violate them. Implement the following function:

evaluate_rules(rules: list<rule>, expenses: list<expense>) -> ???
Expenses will be provided as a list of dictionary objects with string keys and values. The return type of evaluate_rules is up to you. In the future, we will add more types of rules and allow rule creation via an API, so we encourage you to think about the flexibility of your design. Before you start coding, let's discuss the return type of the function.

Example
Input
{"rules": [...], "expenses": [...]}