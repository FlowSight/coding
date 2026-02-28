Ledger System Design
What We Need to Build
We need to design a ledger service for a payment platform. This service tracks money for merchants (online business owners). When a platform processes payments, it needs a trustworthy system to write down every time money moves. This allows the system to calculate balances correctly.

Think about a standard online store. The store uses a payment platform to collect money from shoppers. The platform takes payments all day and pays the merchant later. The ledger is the "source of truth" for this money. It allows the platform to:

Record financial events: Note down when money is collected from customers or paid out to merchants.
Query account balances: figure out how much money a merchant has at any specific time.
Required Functions
At a minimum, your system needs to support these operations:

// Save a financial transaction for a merchant
void recordTransaction(String merchantId, Transaction transaction)

// Find out the current balance for a merchant
Balance getBalance(String merchantId)

// Example of how to use it:
ledger.recordTransaction("merchant_123", new Transaction(
    "txn_abc",           // unique ID for this transaction
    5000,                // money amount (in cents)
    "payment_received",  // type of transaction
    Instant.now()        // time it happened
));

Balance balance = ledger.getBalance("merchant_123");
// Returns: { available: 5000, pending: 0 }
Important Design Topics
Consistency: Financial data must be accurate. How do you make sure transactions are never lost and never counted twice?
Immutability: Usually, you only add to a ledger; you never change old entries. This helps with auditing. How does this rule change your data model?
Scalability: A big platform might handle millions of transactions a day. How do you handle this much traffic while keeping the system fast?
Balance calculation: Do you calculate the balance from scratch every time? Or do you keep a running total stored somewhere? What are the pros and cons of each?
Questions the Interviewer Might Ask
Be ready for the interviewer to ask harder questions about specific parts of your design:

Double-entry bookkeeping: How do you handle credits and debits? Should every transaction create an entry in two different accounts?
Idempotency: How do you handle it if a transaction is sent twice by mistake? What unique ID do you use to ensure it is processed exactly once?
Historical queries: How do you find out what the balance was at a specific time in the past?
Reconciliation: How do you double-check that your ledger matches external systems, like bank accounts?
Concurrency: How do you handle the situation where two transactions try to update the same merchant account at the exact same time?
Partitioning: How do you split up (Sharding) the data as the system gets bigger? Does this make it harder to search across different merchants?
Audit trail: How do you keep records to meet legal rules for financial data?
Error handling: What happens if a transaction fails halfway through? How do you fix errors or reverse a transaction?
Helpful Study Materials
This is a very common System Design problem in financial technology (fintech). Here are some resources to help you learn the architecture:

Design Payment System - YouTube - A very common interview question at companies like OpenAI and Stripe.
Banking Ledger: System Design Interview - YouTube - A walkthrough of the design with a senior engineer.
What to Expect in the Interview
Candidates have reported seeing this question in virtual onsite interviews for Software Engineer jobs. The interview usually starts with designing the APIs (the code structure). After that, you discuss how to build the actual system.

You should be ready to talk about:

How to model data for financial transactions.
How to ensure data Consistency.
How to handle the high Scale of a large payment platform.