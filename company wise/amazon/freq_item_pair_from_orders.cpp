Given a list of order strings like:

["B03 B06 B08", "B06 B08", "B12 B06"]

Each string contains product IDs bought together.

Task:
Generate all unique unordered pairs of products bought together.

If an order has exactly 2 items → that pair itself counts.

If more than 2 items → generate all combinations of size 2.

Count frequency of each pair.

Return the pair with highest frequency.

If multiple pairs have same frequency → return lexicographically smallest pair.

Example:
"B03 B06 B08" → (B03,B06), (B03,B08), (B06,B08)