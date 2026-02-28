Currency Exchange System
Problem Summary
You need to build a tool that converts money from one currency to another. The system uses specific exchange rates to do the math.

The rates come as a text string separated by commas. Each entry tells you that 1 unit of the "FROM" currency is equal to a specific amount of the "TO" currency.

Format: "FROM:TO:RATE,FROM:TO:RATE..."

Example: "USD:EUR:0.85,EUR:GBP:0.88,USD:JPY:110"

The interview problem has four parts, starting easy and getting harder:

Direct Rates: Check if there is a direct rate between two currencies (A to B).
One-Step Connection: Convert money using exactly one middle currency (A to B to C).
Best Possible Rate: If there are many ways to convert, find the one that gives the most money.
Any Path Length: Connect currencies through a chain of any size (A to... to Z).
Phase 1: Direct Rates
Problem Requirements
Write a CurrencyConverter class. It parses the rate string. Then, create a function called getRate(from, to).

This function must handle:

Forward check: The rate is explicitly listed (e.g., A to B).
Reverse check: Only the opposite rate is listed (e.g., B to A). You must calculate 1 / rate.
If there is no direct connection, return None or -1.

Example
Input:

rates = "USD:EUR:0.85,EUR:GBP:0.88,USD:JPY:110"
converter = CurrencyConverter(rates)

converter.getRate("USD", "EUR")  # Returns 0.85 (It is in the string)
converter.getRate("EUR", "USD")  # Returns 1.176... (Math: 1 / 0.85)
converter.getRate("USD", "GBP")  # Returns None (No direct link)
Key Goals
Read the input string quickly.
Store the data so you can find it in O(1) time.
Handle reverse math using the reciprocal.
Return a specific value for failure (like None).
Questions You Might Ask
How precise should the decimal numbers be?
Are there duplicate rates in the string?
Is the input format always correct?
What happens if I convert USD to USD?
Phase 2: One-Step Connection
Problem Requirements
Update your solution to handle a "middleman" currency.

For example, if you have USD→EUR and EUR→GBP, you can calculate USD→GBP. The math is: Rate(USD→EUR) * Rate(EUR→GBP).

Example
Input:

rates = "USD:EUR:0.85,EUR:GBP:0.88,USD:JPY:110"
converter = CurrencyConverter(rates)

converter.getRate("USD", "GBP")
# Returns 0.748 (Math: 0.85 * 0.88)

converter.getRate("GBP", "JPY")
# Returns None (This needs 2 middle steps, which is not allowed yet)
Key Goals
Check for a direct rate first (Phase 1).
If that fails, look for a single currency that connects the start and end.
Multiply the two rates together.
Return None if no single-step path exists.
Phase 3: Best Possible Rate
Problem Requirements
Sometimes, there are multiple paths between two currencies. You must find the path that gives the maximum exchange rate.

This ensures the user gets the best deal.

Example
Input:

rates = "USD:EUR:0.85,USD:GBP:0.75,EUR:GBP:0.88,GBP:CAD:1.7,EUR:CAD:1.45"
converter = CurrencyConverter(rates)

converter.getRate("USD", "CAD")
# Path 1: USD→GBP→CAD = 0.75 * 1.7 = 1.275
# Path 2: USD→EUR→CAD = 0.85 * 1.45 = 1.2325
# Path 3: USD→EUR→GBP→CAD = 0.85 * 0.88 * 1.7 = 1.2716
# Result: 1.275 is the winner.
Key Goals
Find every valid path between the currencies.
Calculate the total rate for each path.
Compare them and return the highest number.
Remember to use both forward and reverse rates.
Phase 4: Any Path Length
Problem Requirements
Now, allow conversions through any number of middle currencies. You will need to use graph traversal algorithms like BFS (Breadth-First Search) or DFS (Depth-First Search).

Example
Input:

rates = "USD:EUR:0.85,EUR:GBP:0.88,GBP:JPY:150,JPY:AUD:0.012"
converter = CurrencyConverter(rates)

converter.getRate("USD", "AUD")
# Math: 0.85 * 0.88 * 150 * 0.012 = 1.3464

converter.getRate("AUD", "USD")
# Reverse path returns 1 / 1.3464
Key Goals
Use a graph algorithm to find paths of any length.
Handle cycles (loops) so the program doesn't run forever.
Keep track of visited nodes.
Return the best rate found across all paths.
Return None if the currencies are not connected.
Solution Details
Solution for Phase 1
Strategy:

Split the input string by commas.
For every entry, save FROM:TO:RATE into a HashMap (dictionary).
Structure it like this: rates[from][to] = rate.
To get a rate: check rates[from][to]. If missing, check rates[to][from] and divide 1 by that number.
Data Structure:

# rates["USD"]["EUR"] = 0.85
# rates["EUR"]["GBP"] = 0.88
Time Complexity: O(n) to parse, O(1) to look up. Space Complexity: O(n).

Code:

class CurrencyConverter:
    def __init__(self, rate_string):
        self.rates = {}
        self._parse_rates(rate_string)

    def _parse_rates(self, rate_string):
        if not rate_string:
            return

        for entry in rate_string.split(","):
            parts = entry.split(":")
            from_curr, to_curr, rate = parts[0], parts[1], float(parts[2])

            if from_curr not in self.rates:
                self.rates[from_curr] = {}
            self.rates[from_curr][to_curr] = rate

    def getRate(self, from_curr, to_curr):
        # Same currency
        if from_curr == to_curr:
            return 1.0

        # Direct lookup
        if from_curr in self.rates and to_curr in self.rates[from_curr]:
            return self.rates[from_curr][to_curr]

        # Reverse lookup
        if to_curr in self.rates and from_curr in self.rates[to_curr]:
            return 1.0 / self.rates[to_curr][from_curr]

        return None
Solution for Phase 2
Strategy:

Try the Phase 1 method (direct/reverse) first.
If that returns None, loop through all known currencies.
For each currency, check if it works as a middle step.
If A -> Middle and Middle -> B both exist, multiply them.
Time Complexity: O(n) (Scanning through the list of currencies).

Code:

def getRate(self, from_curr, to_curr):
    # Direct or reverse lookup first
    direct = self._get_direct_rate(from_curr, to_curr)
    if direct is not None:
        return direct

    # Try single intermediate
    all_currencies = set(self.rates.keys())
    for curr_list in self.rates.values():
        all_currencies.update(curr_list.keys())

    for intermediate in all_currencies:
        rate1 = self._get_direct_rate(from_curr, intermediate)
        rate2 = self._get_direct_rate(intermediate, to_curr)

        if rate1 is not None and rate2 is not None:
            return rate1 * rate2

    return None

def _get_direct_rate(self, from_curr, to_curr):
    """Get direct or reverse rate, returns None if not found."""
    if from_curr == to_curr:
        return 1.0
    if from_curr in self.rates and to_curr in self.rates[from_curr]:
        return self.rates[from_curr][to_curr]
    if to_curr in self.rates and from_curr in self.rates[to_curr]:
        return 1.0 / self.rates[to_curr][from_curr]
    return None
Solution for Phase 3
Strategy:

Think of currencies as a graph. Rates are the edges.
Use BFS or DFS to explore paths.
Store both the normal rate and the reverse rate (1/rate) in the graph.
As you traverse, calculate the total rate. Keep track of the highest one.
Graph Setup:

Use an adjacency list.
Add edges for both directions.
Time Complexity: O(V + E) using BFS (Nodes + Edges).

Code:

from collections import defaultdict

def __init__(self, rate_string):
    self.graph = defaultdict(list)  # currency -> [(neighbor, rate), ...]
    self._parse_rates(rate_string)

def _parse_rates(self, rate_string):
    if not rate_string:
        return

    for entry in rate_string.split(","):
        parts = entry.split(":")
        from_curr, to_curr, rate = parts[0], parts[1], float(parts[2])

        # Store both directions
        self.graph[from_curr].append((to_curr, rate))
        self.graph[to_curr].append((from_curr, 1.0 / rate))

def getRate(self, from_curr, to_curr):
    if from_curr == to_curr:
        return 1.0

    best_rate = None
    # BFS with (current_currency, accumulated_rate, visited_set)
    queue = [(from_curr, 1.0, {from_curr})]

    while queue:
        current, rate, visited = queue.pop(0)

        for neighbor, edge_rate in self.graph[current]:
            if neighbor == to_curr:
                new_rate = rate * edge_rate
                if best_rate is None or new_rate > best_rate:
                    best_rate = new_rate
            elif neighbor not in visited:
                new_visited = visited | {neighbor}
                queue.append((neighbor, rate * edge_rate, new_visited))

    return best_rate
Solution for Phase 4
Strategy:

Use DFS (Depth First Search) to go deep into the graph.
Use a "visited" set to prevent loops (cycles).
Keep multiplying rates as you go deeper.
When you reach the target currency, check if this new total rate is better than the previous best.
Time Complexity: Depends on graph structure. Worst case is factorial, but cycle detection makes it much faster.

Code:

def getRate(self, from_curr, to_curr):
    if from_curr == to_curr:
        return 1.0

    if from_curr not in self.graph:
        return None

    best_rate = [None]  # Use list to allow modification in nested function

    def dfs(current, accumulated_rate, visited):
        if current == to_curr:
            if best_rate[0] is None or accumulated_rate > best_rate[0]:
                best_rate[0] = accumulated_rate
            return

        for neighbor, edge_rate in self.graph[current]:
            if neighbor not in visited:
                visited.add(neighbor)
                dfs(neighbor, accumulated_rate * edge_rate, visited)
                visited.remove(neighbor)  # Backtrack

    dfs(from_curr, 1.0, {from_curr})
    return best_rate[0]
Advanced Tip: Using Logarithms

To solve this efficiently, you can use math tricks. Instead of multiplying rates, you can add their logarithms.

log(a * b) = log(a) + log(b)
This turns the problem into a "Shortest Path" problem (or Longest Path).
You can then use standard algorithms like Bellman-Ford.
Bonus Interview Questions
Note: These are extra questions the interviewer might ask to test your depth of knowledge.

Arbitrage (Free Money Loops)
Question: What if a cycle of trades results in a rate greater than 1? (e.g., you start with $1 and end up with $1.05). Answer: This is called arbitrage. You can detect this using Bellman-Ford if you use the logarithm trick mentioned above (looking for "negative cycles").

Precision Issues
Question: Floating point numbers (like 0.1 + 0.2) are not always exact. How do you fix this? Answer: Use the Decimal class in Python or store rates as integers (multiply everything by 10,000) to keep math exact.

Rate Updates
Question: What if the rates change every second? Answer: Add timestamps to the data. If a rate is too old, don't use it (Time-To-Live). You will need to clear your cache frequently.

Scaling Up
Question: How does this handle millions of requests? Answer:

Cache the most popular conversions (like USD to EUR).
Pre-calculate common paths so you don't run BFS every time.