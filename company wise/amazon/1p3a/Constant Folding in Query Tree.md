Implement a constant folding algorithm. Design an algorithm to simplify a query tree that traverses the tree, folds safe nodes, and recursively converts queries into subqueries. The query tree includes the following three components: 1) projection list; 2) predicate list; 3) nested subquery list.

Input
A JSON object describing a query tree, which includes a projection list, a predicate list, and a nested subquery list.

Output
Return the simplified query tree.

Example
Input
{
  "projections": ["col1", "col2 * 2"],
  "predicates": ["col3 > 5"],
  "subqueries": [
    {
      "projections": [],
      "predicates": ["col4 < 10"],
      "subqueries": []
    }
  ]
}
Output
{
  "projections": ["col1", "4"],
  "predicates": ["true"],
  "subqueries": []
}
Example
Input
{"projections": ["col1", "col2 * 2"], "predicates": ["col3 > 5"], "subqueries": [{"projections": [], "predicates": ["col4 < 10"], "subqueries": []}]}