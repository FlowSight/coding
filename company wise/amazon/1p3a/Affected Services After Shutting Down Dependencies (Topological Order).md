Problem: Affected Services After Shutting Down Dependencies (Dependency Graph)
Amazon has many services. There are dependency relationships among services. When some services are shut down, any service that depends on a shut-down service becomes affected (cannot function), and the impact propagates along dependency chains.

Given the service dependency graph and a list of shut-down services, return the set of all affected services.

Input
A directed dependency representation deps:
Use HashMap<String, List<String>>
deps[x] is the list of services that depend on service x (i.e., an edge x -> y means y depends on x; if x is down, y is affected).
A list down of shut-down service names (strings)
Output
Return a set/list containing all affected service names.
The input is guaranteed to be valid (no cycles).
Constraints
Number of services: 1 <= N <= 2 * 10^5
Number of edges: 0 <= M <= 2 * 10^5
Target time complexity close to O(N + M)
Example
deps = {
  "auth": ["orders", "payments"],
  "orders": ["recommendation"],
  "payments": [],
  "recommendation": []
}

down = ["auth"]
Output:

{ "auth", "orders", "payments", "recommendation" }
Notes
You may define the input/output format (the hashmap + list above is acceptable).
Consider multiple shut-down services and isolated nodes.
Example
Input
auth: orders payments
orders: recommendation
payments:
recommendation:
DOWN auth
Output
auth orders payments recommendation