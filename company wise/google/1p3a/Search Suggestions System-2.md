You are given a list of products, where each product is a string. You are also given a searchWord. After each character typed, return the top k suggestions of product names that match the typed prefix.

Each product also has an associated popularity score (Map) ((P.S. changed it to String[][] for FP's convenience :)). Suggestions should be returned in order of:

Highest popularity score
If scores are equal, return the lexicographically smaller product.
You must return suggestions after each character of searchWord. Handle up to 1e5 products and optimize for performance.

Example
Input
products = ["apple", "appetizer", "application", "app", "apply", "banana", "appstore"]
popularity = [["apple", "80"], ["appetizer", "70"], ["application", "90"], ["app", "90"], ["apply", "85"], ["banana", "60"], ["appstore", "90"]]
searchWord = "app"
k = 3
Output
[["app", "application", "appstore"], ["app", "application", "appstore"], ["app", "application", "appstore"]]