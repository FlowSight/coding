Given a list of currency pairs with their conversion rates, design a function to convert any currency to another. You need to handle multiple currencies and real-time rate changes, and provide the optimal path to reach a specific currency. Assume the exchange rates are given as directed graph edges, where nodes represent currencies, and you can use different path combinations for conversion. Consider graph connectivity and possible cycles. The input includes a list of currency pairs with rates and conversion requests. The output should be the converted currency value or an error message if conversion is not possible.

Input
exchangeRates: List containing tuples of (currency_from, currency_to, rate), representing the conversion rate from currency_from to currency_to.
queries: List of queries containing tuples (convert_from, convert_to, value), representing the need to convert value of convert_from currency to convert_to currency.
Output
A list, where each element is the converted value or the string "Cannot convert".
Example
Input: exchangeRates = [("USD", "EUR", 0.85), ("EUR", "JPY", 129.0), ("JPY", "CNY", 0.06)] queries = [("USD", "CNY", 100), ("EUR", "USD", 200)]

Output: [673.5, "Cannot convert"]

Example
Input
2
USD EUR 0.85
EUR JPY 129.0
USD JPY 100