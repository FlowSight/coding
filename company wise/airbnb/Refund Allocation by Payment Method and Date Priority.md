You need to write a program for a refund system. Refunds should be issued in full for one payment before considering the next payment. The refund priority among different payment methods is: CREDIT, CREDIT_CARD, PAYPAL. Refunds should be prioritized for the most recent payment. Given payment records and a refund amount, calculate the refund allocation scheme.

Input
Transaction: A list of payment records, including type, date, and amount.
Refund amount: Total amount to be refunded.
Example
Example 1
Transactions:
Payment1: Credit, 2023-01-10, $40
Payment2: Paypal, 2023-01-15, $60
Refund amount: $50
Expected refund scheme:

Refund a: linked to Payment1, Credit, $30
Example 2
Transactions:
Payment1: Credit, 2023-01-15, $40
Payment2: Paypal, 2023-01-10, $60
Payment3: Paypal, 2023-01-20, $40
Refund1: linked to Payment1, $20
Refund amount: $50

Expected refund scheme:

Refund a: linked to Payment1, Credit, $40
Refund b: linked to Payment2, Paypal, $10
Example
Input
Credit,2023-01-10,40|Paypal,2023-01-15,60|50