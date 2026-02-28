Account Balance Manager
Challenge Summary
You need to build a system to manage bank accounts. This system will track money moving between accounts. It must also follow specific rules about keeping balances positive and handling empty accounts.

The challenge has three steps:

Calculating Totals: Add up transactions to find the final money count.
Stopping Overdrafts: Stop a transaction if an account runs out of money.
Covering Shortfalls: Use a main bank account to pay if a user does not have enough money.
Input Format
You get a list of transactions. Each item has:

account_id: The ID name of the account.
amount: The money involved. Positive numbers are deposits. Negative numbers are withdrawals.
transactions = [
    {"account_id": "account_A", "amount": 100},
    {"account_id": "account_B", "amount": 50},
    {"account_id": "account_A", "amount": -30},
    {"account_id": "account_B", "amount": -80}
]
Step 1: Calculating Totals
Goal
Write a function called get_account_balances(transactions). It should go through all transactions and calculate the final total for each account. Only return accounts that have money left (positive balance).

Example
Input:

transactions = [
    {"account_id": "account_A", "amount": 100},
    {"account_id": "account_B", "amount": 50},
    {"account_id": "account_A", "amount": -30},
    {"account_id": "account_C", "amount": 200},
    {"account_id": "account_B", "amount": -50}
]
Output:

get_account_balances(transactions)
# Returns: {"account_A": 70, "account_C": 200}
#
# Math:
# account_A: 100 - 30 = 70 (Positive, keep it)
# account_B: 50 - 50 = 0 (Zero, remove it)
# account_C: 200 (Positive, keep it)
Requirements
Process the list in order.
Group the money totals by account ID.
Only return accounts with a balance greater than 0.
Return a dictionary.
Step 2: Stopping Overdrafts
Goal
Update your code to check the balance before making a change. If a withdrawal makes the balance negative, reject it. Return two things: the final balances and a list of the rejected transactions.

Function name: process_transactions(transactions).

Example
Input:

transactions = [
    {"account_id": "account_A", "amount": 100},
    {"account_id": "account_A", "amount": -150},  # Result is -50
    {"account_id": "account_B", "amount": 50},
    {"account_id": "account_A", "amount": -80},   # Valid: 100 - 80 = 20
    {"account_id": "account_B", "amount": -100}   # Result is -50
]
Output:

process_transactions(transactions)
# Returns: (
#     {"account_A": 20, "account_B": 50},
#     [
#         {"account_id": "account_A", "amount": -150},
#         {"account_id": "account_B", "amount": -100}
#     ]
# )
#
# Steps:
# 1. account_A +100 → balance: 100 (OK)
# 2. account_A -150 → makes balance -50 (REJECT)
# 3. account_B +50 → balance: 50 (OK)
# 4. account_A -80 → balance: 20 (OK)
# 5. account_B -100 → makes balance -50 (REJECT)
Requirements
Check items in order.
Do not allow a transaction if the result is negative.
Deposits (adding money) are always allowed.
Keep a list of rejected items in the correct order.
Include accounts with zero balance in the final list.
Step 3: Covering Negative Balances
Goal
Now, the bank will help users. If a transaction makes the balance negative, do not reject it. Instead, take money from a special "platform account" to fill the gap. The user's account should end up at exactly zero.

Write process_with_coverage(transactions, platform_account_id). Return the total amount of money the platform account had to pay.

Example
Input:

transactions = [
    {"account_id": "platform", "amount": 1000},
    {"account_id": "account_A", "amount": 100},
    {"account_id": "account_A", "amount": -150},  # Needs 50 from bank
    {"account_id": "account_B", "amount": 50},
    {"account_id": "account_B", "amount": -100},  # Needs 50 from bank
    {"account_id": "account_A", "amount": -30}    # Needs 30 from bank
]

platform_account_id = "platform"
Output:

process_with_coverage(transactions, "platform")
# Returns: 130
#
# Steps:
# 1. platform +1000 → platform has 1000
# 2. account_A +100 → account_A has 100
# 3. account_A -150 → result -50. Bank pays 50.
#    account_A is now 0. Platform is 950. Total paid: 50.
# 4. account_B +50 → account_B has 50
# 5. account_B -100 → result -50. Bank pays 50.
#    account_B is now 0. Platform is 900. Total paid: 100.
# 6. account_A -30 → result -30. Bank pays 30.
#    account_A is now 0. Platform is 870. Total paid: 130.
Requirements
The function takes an extra input for the platform account ID.
If a balance goes negative, transfer enough money to make it zero.
The transaction still happens (the user balance becomes 0).
Return the total money paid by the platform.
Assume the platform account has enough money.
How to Solve It
Solution for Step 1
The Plan:

Use a dictionary to keep track of money for each user.
Loop through the transactions and add the numbers to the dictionary.
Remove any accounts that have zero or negative money at the end.
Time Complexity: O(n) (where n is the number of transactions)

Space Complexity: O(k) (where k is the number of unique accounts)

Code:

def get_account_balances(transactions):
    balances = {}

    for txn in transactions:
        account_id = txn["account_id"]
        amount = txn["amount"]
        balances[account_id] = balances.get(account_id, 0) + amount

    # Keep only positive balances
    return {acc: bal for acc, bal in balances.items() if bal > 0}
What to watch out for:

An empty list of transactions.
All accounts having zero balance.
Solution for Step 2
The Plan:

Keep track of the current balance for each account.
Before subtracting money, calculate what the new balance would be.
If the new number is negative, add the transaction to a rejected list.
If it is positive (or zero), update the balance dictionary.
Time Complexity: O(n)

Space Complexity: O(k + r) (k is accounts, r is rejected items)

Code:

def process_transactions(transactions):
    balances = {}
    rejected = []

    for txn in transactions:
        account_id = txn["account_id"]
        amount = txn["amount"]
        current_balance = balances.get(account_id, 0)

        new_balance = current_balance + amount

        if new_balance < 0:
            # Reject transaction
            rejected.append(txn)
        else:
            # Accept transaction
            balances[account_id] = new_balance

    return (balances, rejected)
Key Notes:

Adding money is always safe.
You must check the math before changing the dictionary.
The order of the rejected list matters.
Solution for Step 3
The Plan:

Loop through transactions like normal.
If a transaction makes the balance negative:
Figure out the missing amount (the shortfall).
Subtract that amount from the platform account.
Add that amount to your total_coverage counter.
Set the user's account balance to exactly 0.
Return the total coverage number.
Time Complexity: O(n)

Space Complexity: O(k)

Code:

def process_with_coverage(transactions, platform_account_id):
    balances = {}
    total_coverage = 0

    for txn in transactions:
        account_id = txn["account_id"]
        amount = txn["amount"]
        current_balance = balances.get(account_id, 0)

        new_balance = current_balance + amount

        if new_balance < 0 and account_id != platform_account_id:
            # Calculate coverage needed
            coverage_needed = -new_balance  # Turn negative to positive

            # Deduct from platform account
            balances[platform_account_id] = balances.get(platform_account_id, 0) - coverage_needed

            # Add to total coverage
            total_coverage += coverage_needed

            # Set account balance to 0
            balances[account_id] = 0
        else:
            balances[account_id] = new_balance

    return total_coverage
Key Notes:

The platform account behaves like a normal account for its own transactions.
Only cover regular users, not the platform itself.
If the balance would be -50, you need 50 coverage.
Ask the interviewer: Should we track the platform account balance? (This code does).