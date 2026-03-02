Maximize Amount After Two Days of Conversions
Problem Overview
You are given a string called initialCurrency. You begin with 1.0 unit of this currency.

You also receive four arrays (lists) that define possible currency trades and their exchange rates for two different days:

Day 1: pairs1[i] shows a trade from startCurrency to targetCurrency. The exchange rate for this trade is rates1[i].
Day 2: pairs2[i] shows a trade from startCurrency to targetCurrency. The exchange rate for this trade is rates2[i].
Note: You can always convert a currency to itself at a rate of 1.0.

Goal: Find the maximum amount of initialCurrency you can end up with. You must perform trades using Day 1 rates first, followed by trades using Day 2 rates.

Sample Cases
Example 1

Input:
initialCurrency = "EUR"
pairs1 = [["EUR","USD"],["USD","JPY"]], rates1 = [2.0,3.0]
pairs2 = [["JPY","USD"],["USD","CHF"],["CHF","EUR"]], rates2 = [4.0,5.0,6.0]
Output: 720.00000
Explanation: You can get 720.0 EUR by following this path:
Start with 1.0 EUR.
Day 1: Convert EUR → USD (rate 2.0), then USD → JPY (rate 3.0). You now have 6.0 JPY.
Day 2: Convert JPY → USD (rate 4.0), then USD → CHF (rate 5.0), and finally CHF → EUR (rate 6.0).
The total is 1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0 = 720.0.
Example 2

Input:
initialCurrency = "NGN"
pairs1 = [["NGN","EUR"]], rates1 = [9.0]
pairs2 = [["NGN","EUR"]], rates2 = [6.0]
Output: 1.50000
Explanation: Trade NGN for EUR on Day 1 (Rate 9.0). Then, trade EUR back to NGN on Day 2. This results in a value of 1.5.
Example 3

Input:
initialCurrency = "USD"
pairs1 = [["USD","EUR"]], rates1 = [1.0]
pairs2 = [["EUR","JPY"]], rates2 = [10.0]
Output: 1.00000
Explanation: There is no valid path to convert the money back to USD. Therefore, the maximum amount remains 1.0.
Input Limits
The length of initialCurrency is between 1 and 3.
initialCurrency uses only uppercase English letters.
The number of pairs for Day 1 (n) and Day 2 (m) is between 1 and 10.
Currency names in the pairs use only uppercase English letters and have a length between 1 and 3.
The size of the rates arrays matches the size of the pairs arrays.
All rates are between 1.0 and 10.0.
The input contains no contradictions or circular dependencies within a single day's graph.