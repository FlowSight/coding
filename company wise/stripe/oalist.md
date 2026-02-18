3. Catch Me If You Can — Fraud Detection
Problem Statement:
You are given a list of transactions with the following fields:

user_id, timestamp, amount, ip_address.
A transaction is considered fraudulent if:

The same user makes multiple transactions from different IP addresses within 10 minutes.
The total transaction amount from a user in any 1-hour window exceeds $5000.
Return the list of fraudulent transaction IDs in ascending order.

4. Store Closing Time Penalty
Problem Statement:
A store closes at a specific time T. Customers arrive with orders at different times. If an order is accepted after closing time , a penalty is incurred. Each order has a processing time and a penalty value.

Find the optimal schedule of processing orders that minimizes the total penalty.

(Hint: This is a variation of scheduling with deadlines and penalties, solvable with DP or greedy approaches.)

5. Subscription Notification Scheduler
Problem Statement:
You are given a list of subscriptions, each defined by:

start_time, interval(in days), and count.
You must simulate the notification system and output the exact timestamps of all notifications that need to be sent. The notifications should be ordered by time, and if two notifications happen at the same time, order them by subscription ID.

6. Accept-Language Header Parser
Problem Statement:
You are given an HTTP header string in the format:

Accept-Language: en-US,en;q=0.8,fr;q=0.9,de;q=0.7
Parse the string and return the list of languages ​​ordered by their quality value ( q). If qis missing, it defaults to 1.0. Ties should be broken by the order of appearance.

Output for the above example should be:

["en-US", "fr", "en", "de"]
