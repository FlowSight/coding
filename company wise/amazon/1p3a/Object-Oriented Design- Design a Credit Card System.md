Design a simplified credit card system (OOD). Propose the core classes/interfaces and describe the main workflows.

Support at least:

Card/account lifecycle (create, status Active/Frozen/Closed)
Credit limit and available credit
Transactions: charge (authorize/capture simplified) and refund
Billing: generate periodic statements; payments that update balance/used credit
Basic validations (status, insufficient credit, optional duplicate detection)
Constraints:

No real payment-network integration; in-memory storage is fine.
Provide key method signatures (e.g., authorize/charge/refund/generateStatement/makePayment).
Explain responsibilities and relationships.
Cover:

Class design (fields/methods)
Sequence for a charge and for statement+payment
One extensibility idea (multi-currency/installments/fraud detection).