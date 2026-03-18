Design a restaurant waitlist system that supports the following functions:

Add a guest to the waitlist.
Remove a guest from the waitlist.
Serve a guest when a table becomes available. The system should maintain good user interaction, allowing assumptions and operations based on those assumptions.
Please design a class or multiple functions to implement these features and provide complete code.

Input:

A list of operations to add and remove guests as well as events for when tables become available.
Output:

Output the name of the guest each time they are served.
Note: Guests can be identified by their names, and the number of tables at the restaurant is limited.

Example:

Input: ["add Alice", "add Bob", "serve", "add Cindy", "serve", "serve"]
Output: "Alice", "Bob", "Cindy"
Example
Input
add Alice
add Carol
remove Alice
serve
serve