Implement a system to track customer visits to a website. You need to implement two functions. The first function records the customer's visit to the website. The second function returns the first customer who has visited only once. The input is a stream of customer visit events (each event contains a customer ID), and you need to implement recording these events and executing the above two functionalities. Assume customer IDs are always valid. Provide test cases to validate your implementation.

Example
Input
cw = CustomerWebsite()
cw.visit(1)
cw.visit(2)
cw.visit(3)
cw.visit(2)
cw.first_unique()