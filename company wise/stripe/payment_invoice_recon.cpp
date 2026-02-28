Payment Invoice Reconciliation
The Challenge
You need to build a system that matches incoming payments to unpaid invoices. When a customer sends money, you must figure out which invoice they are paying. The logic gets harder in three steps:

Match by ID: Look for a specific invoice ID written in the payment note.
Match by Amount: If there is no ID, look for an invoice with the exact same money amount.
Fuzzy Match: If the exact amount isnt found, look for an amount that is close (to handle bank fees).
Data Format
Payment (a single string of text):

"payment-id, amount, memo"
payment-id: A unique ID for the payment.
amount: The money amount (integer, in cents).
memo: A note about the payment. It might contain an invoice ID.
Invoices (a list of strings):

[
  "invoice-id, due-date, amount",
  "invoice-id, due-date, amount",
  ...
]
invoice-id: A unique ID for the invoice.
due-date: The date the bill is due (YYYY-MM-DD).
amount: The invoice amount (integer, in cents).
Expected Output
Return a text string that says which payment matched which invoice:

"Payment {payment-id} paid {amount} for invoice {invoice-id} due on {date}"
If you cannot find a match, return this:

"Payment {payment-id} could not be matched to any invoice"
Step 1: Match by ID
The Task
Write a function called reconcile_payment(payment, invoices). This function should match a payment to an invoice when the payment note specifically lists an invoice ID.

The note will contain text like "paying for: invoice-id" or "Paying off: invoice-id". It can be upper or lower case. You need to find this ID and match it to the list of invoices.

Example
Input:

payment = "payment-001, 1000, Paying off: inv-123"

invoices = [
    "inv-123, 2024-03-15, 1000",
    "inv-456, 2024-03-20, 1000",
    "inv-789, 2024-02-10, 500"
]
Output:

"Payment payment-001 paid 1000 for invoice inv-123 due on 2024-03-15"
Rules
Read the payment string to get the ID, amount, and note.
Look inside the note for an invoice ID (look for "paying for: ...").
Find the invoice in the list that matches that ID.
Return the final result string.
Handle cases where the ID in the note does not exist in your list.
Edge Cases
The ID in the note is not in the invoice list.
There are many invoices, but only one correct ID.
The text has different capital letters (like "Paying" vs "paying").
The payment string is missing data.
Step 2: Match by Amount
The Task
Update your code to handle payments that do not have an invoice ID. If the note does not contain an ID, look for an invoice that has the exact same amount.

If multiple invoices have the same amount, pick the one with the earliest due date.

Important: Always try the ID match from Step 1 first. Only use the amount match if the ID match fails.

Example
Input:

payment = "payment-002, 500, Monthly subscription"

invoices = [
    "inv-001, 2024-03-22, 1000",
    "inv-002, 2024-02-05, 500",
    "inv-003, 2024-03-01, 500",
    "inv-004, 2024-01-15, 500"
]
Output:

"Payment payment-002 paid 500 for invoice inv-004 due on 2024-01-15"
Note: inv-004 is chosen because it has the earliest date among the invoices worth 500.

Rules
Check for an invoice ID in the note first (Step 1 logic).
If no ID is found, search for invoices that match the payment amount.
If you find multiple invoices with the same amount, pick the oldest one.
Read the dates correctly to see which is older.
Return "could not be matched" if no match is found.
Questions to Ask the Interviewer
If we match by ID, does the money amount also need to match?
What if two invoices have the same amount and the exact same date?
What date format are we using?
Do we need to handle negative numbers or zero?
Step 3: Match with "Forgiveness" (Fuzzy Match)
The Task
Sometimes banks charge fees or round numbers differently. A customer might owe 100butthebanktakesa100 but the bank takes a 2 fee, so you only get $98. You need to handle these small differences.

Add a third rule: fuzzy matching with forgiveness. If you cannot find an exact amount match, look for invoices where the amount is "close enough." The difference must be within the forgiveness limit. If multiple invoices are close enough, pick the one with the earliest date.

Order of Operations:

ID Match (Step 1) - Highest priority.
Exact Amount Match (Step 2) - Medium priority.
Fuzzy Match (Step 3) - Lowest priority (only if the others fail).
Example
Input:

payment = "payment-003, 98, Customer payment"

invoices = [
    "inv-100, 2024-03-15, 100",
    "inv-200, 2024-02-20, 98",
    "inv-300, 2024-01-10, 102"
]

forgiveness = 5
Output:

"Payment payment-003 paid 98 for invoice inv-200 due on 2024-02-20"
Note: inv-200 matches the amount exactly, so we pick it over inv-100 (which is close enough).

Another Example:

payment = "payment-004, 95, Customer payment"

invoices = [
    "inv-100, 2024-03-15, 100",
    "inv-300, 2024-01-10, 97"
]

forgiveness = 5
Output:

"Payment payment-004 paid 95 for invoice inv-300 due on 2024-01-10"
Note: Both invoices are close to 95 (within 5). We pick inv-300 because it is older.

Rules
Add forgiveness as a new input.
Follow the priority order: ID → Exact Amount → Fuzzy Amount.
For fuzzy matching, the invoice amount must be inside the range: [payment - forgiveness, payment + forgiveness].
Always pick the earliest date if there is a tie within the same step.
Always prefer an exact match over a fuzzy match, even if the fuzzy match has an older date.
Testing Tips
When testing your code, check these things:

Make sure the priority order works.
An ID match should win even if the amount is wrong.
An exact amount match should win over a fuzzy match.
Fuzzy match should only happen if there is no exact match.
Test the edge of the range (e.g., if the difference is exactly 5).
Make sure the earliest date logic works for all steps.
How to Solve It
Step 1 Solution: ID Matching
Plan:

Break the payment string into pieces.
Look inside the note for "paying for:" or "paying off:".
Get the ID from the note and look for it in the invoice list.
Return the result string.
Code:

def reconcile_payment(payment, invoices):
    # Parse payment
    parts = payment.split(", ")
    payment_id = parts[0]
    payment_amount = int(parts[1])
    memo = ", ".join(parts[2:])  # Memo may contain commas

    # Try to extract invoice ID from memo (case-insensitive search)
    invoice_id = None
    memo_lower = memo.lower()
    if "paying for:" in memo_lower:
        # Find position in lowercase, extract from original to preserve case
        pos = memo_lower.find("paying for:") + len("paying for:")
        invoice_id = memo[pos:].strip()
    elif "paying off:" in memo_lower:
        pos = memo_lower.find("paying off:") + len("paying off:")
        invoice_id = memo[pos:].strip()

    # Find matching invoice
    if invoice_id:
        for invoice in invoices:
            inv_parts = invoice.split(", ")
            inv_id = inv_parts[0]
            if inv_id == invoice_id:
                inv_date = inv_parts[1]
                inv_amount = inv_parts[2]
                return f"Payment {payment_id} paid {payment_amount} for invoice {inv_id} due on {inv_date}"

    return f"Payment {payment_id} could not be matched to any invoice"
Time Complexity: O(n) - We look through the list once.

Space Complexity: O(1) - We only store a few variables.

Step 2 Solution: Amount Matching
Plan:

First, try the ID match from Step 1.
If that fails, loop through the invoices to find one with the exact same amount.
If you find multiple matches, keep track of the one with the earliest date.
Return the result.
Details:

You can compare dates as strings (YYYY-MM-DD) because they sort alphabetically.
Only do the amount search if the ID search found nothing.
def reconcile_payment(payment, invoices):
    # Parse payment
    parts = payment.split(", ")
    payment_id = parts[0]
    payment_amount = int(parts[1])
    memo = ", ".join(parts[2:])

    # Try ID-based matching first
    invoice_id = extract_invoice_id_from_memo(memo)
    if invoice_id:
        match = find_invoice_by_id(invoice_id, invoices)
        if match:
            return format_result(payment_id, payment_amount, match)

    # Try amount-based matching
    best_match = None
    earliest_date = None

    for invoice in invoices:
        inv_id, inv_date, inv_amount = parse_invoice(invoice)

        if int(inv_amount) == payment_amount:
            if earliest_date is None or inv_date < earliest_date:
                earliest_date = inv_date
                best_match = (inv_id, inv_date, inv_amount)

    if best_match:
        return format_result(payment_id, payment_amount, best_match)

    return f"Payment {payment_id} could not be matched to any invoice"

def parse_invoice(invoice):
    """Parse invoice string into components."""
    parts = invoice.split(", ")
    return parts[0], parts[1], parts[2]

def format_result(payment_id, payment_amount, invoice_match):
    """Format the reconciliation result."""
    inv_id, inv_date, inv_amount = invoice_match
    return f"Payment {payment_id} paid {payment_amount} for invoice {inv_id} due on {inv_date}"
Time Complexity: O(n) - We loop through the list once for the amount check.

Step 3 Solution: All Three Rules Combined
Plan:

Try ID match first (Priority 1).
Try Exact Amount match second (Priority 2).
Try Fuzzy Amount match last (Priority 3).
In every step, if there are multiple matches, pick the oldest date.
Code Structure:

def reconcile_payment(payment, invoices, forgiveness=0):
    # Parse payment
    payment_id, payment_amount, memo = parse_payment(payment)

    # Tier 1: ID-based matching
    invoice_id = extract_invoice_id_from_memo(memo)
    if invoice_id:
        match = find_invoice_by_id(invoice_id, invoices)
        if match:
            return format_result(payment_id, payment_amount, match)

    # Tier 2: Exact amount matching
    exact_match = find_best_amount_match(
        invoices,
        payment_amount,
        exact_only=True
    )
    if exact_match:
        return format_result(payment_id, payment_amount, exact_match)

    # Tier 3: Fuzzy amount matching
    if forgiveness > 0:
        fuzzy_match = find_best_fuzzy_match(
            invoices,
            payment_amount,
            forgiveness
        )
        if fuzzy_match:
            return format_result(payment_id, payment_amount, fuzzy_match)

    return f"Payment {payment_id} could not be matched to any invoice"

def find_best_fuzzy_match(invoices, payment_amount, forgiveness):
    """Find earliest invoice within forgiveness range."""
    best_match = None
    earliest_date = None

    min_amount = payment_amount - forgiveness
    max_amount = payment_amount + forgiveness

    for invoice in invoices:
        inv_id, inv_date, inv_amount = parse_invoice(invoice)
        inv_amount_int = int(inv_amount)

        # Check if within forgiveness range (but not exact match)
        if (min_amount <= inv_amount_int <= max_amount
            and inv_amount_int != payment_amount):

            if earliest_date is None or inv_date < earliest_date:
                earliest_date = inv_date
                best_match = (inv_id, inv_date, inv_amount)

    return best_match
Time Complexity: O(n) - In the worst case, we loop through the invoices three times (once for each rule).

Testing and Discussion
How to Test the Code
Question: How do you prove that the priority rules (ID > Exact > Fuzzy) work correctly?

Key Ideas:

Don't break old features: Step 2 tests should still work for Step 1 cases.
Prove the Priority:
High Priority: An ID match should happen even if the amount is wrong.
Medium Priority: An exact amount match should happen even if a fuzzy match is available.
Low Priority: Fuzzy match only happens if nothing else matches.
Example Test Cases:

def test_id_match_takes_precedence_over_amount():
    """Verify ID matching ignores amount-based matching."""
    payment = "pay-001, 500, Paying for: inv-100"
    invoices = [
        "inv-100, 2024-03-15, 1000",  # ID matches but amount differs
        "inv-200, 2024-02-10, 500"    # Amount matches but no ID match
    ]
    # Should match inv-100 via ID, not inv-200 via amount
    result = reconcile_payment(payment, invoices)
    assert "inv-100" in result

def test_exact_amount_takes_precedence_over_fuzzy():
    """Verify exact amount match beats fuzzy match."""
    payment = "pay-002, 100, Payment"
    invoices = [
        "inv-100, 2024-03-15, 100",   # Exact match
        "inv-200, 2024-01-10, 98"     # Fuzzy match (within forgiveness)
    ]
    forgiveness = 5
    # Should match inv-100 (exact), not inv-200 (fuzzy)
    result = reconcile_payment(payment, invoices, forgiveness)
    assert "inv-100" in result

def test_fuzzy_match_only_when_no_exact_match():
    """Verify fuzzy matching only activates when needed."""
    payment = "pay-003, 97, Payment"
    invoices = [
        "inv-100, 2024-03-15, 100",   # Within forgiveness range
        "inv-200, 2024-02-10, 200"    # Outside range
    ]
    forgiveness = 5
    # Should match inv-100 via fuzzy logic
    result = reconcile_payment(payment, invoices, forgiveness)
    assert "inv-100" in result

def test_earliest_date_selection_within_same_tier():
    """Verify earliest date selection applies within each matching tier."""
    payment = "pay-004, 500, Payment"
    invoices = [
        "inv-100, 2024-03-15, 500",
        "inv-200, 2024-01-10, 500",   # Earliest date
        "inv-300, 2024-02-20, 500"
    ]
    # Should match inv-200 (earliest among exact amount matches)
    result = reconcile_payment(payment, invoices)
    assert "inv-200" in result

def test_all_parts_work_together():
    """Comprehensive test ensuring all matching strategies coexist."""
    # Test 1: ID match (Part 1)
    assert "inv-100" in reconcile_payment(
        "pay-001, 999, Paying for: inv-100",
        ["inv-100, 2024-01-01, 1000", "inv-200, 2024-01-01, 999"]
    )

    # Test 2: Exact amount match (Part 2)
    assert "inv-200" in reconcile_payment(
        "pay-002, 500, Payment",
        ["inv-100, 2024-03-01, 600", "inv-200, 2024-02-01, 500"]
    )

    # Test 3: Fuzzy match (Part 3)
    assert "inv-300" in reconcile_payment(
        "pay-003, 495, Payment",
        ["inv-300, 2024-01-01, 500", "inv-400, 2024-01-01, 600"],
        forgiveness=10
    )
Testing Strategy Summary:

Always test the order: ID first, then Exact Amount, then Fuzzy Amount.
Make sure a high-priority match stops the code from looking for lower-priority matches.
Check that you always pick the earliest date when there is a tie.
Test edge cases, like being exactly on the limit of the forgiveness range.