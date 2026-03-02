Building an Expense Rules Engine
The Challenge
You need to build a flexible rules engine for a company expense system. Companies give employees credit cards for work. Managers need to set rules to make sure employees do not spend too much money or buy the wrong things.

Your goal is to build a tool that checks expense data against a list of rules. It should flag any expense that breaks a rule.

Design Goals
Before you start solving the problem, keep these goals in mind:

Flexibility: The system must handle many different types of rules. New rules will be added later using an API.
Stateless Design: Do not write specific code for every rule. The rules should be treated as data.
Extensibility: It should be easy to add new rule types without changing the main code.
The Data
The input data is a list of dictionaries. Each dictionary represents one expense.

expenses = [
    {
        "expense_id": "001",
        "trip_id": "001",
        "amount_usd": "49.99",
        "expense_type": "supplies",
        "vendor_type": "restaurant",
        "vendor_name": "Outback Roadhouse"
    },
    {
        "expense_id": "002",
        "trip_id": "001",
        "amount_usd": "125.00",
        "expense_type": "supplies",
        "vendor_type": "retailer",
        "vendor_name": "Staples"
    },
    {
        "expense_id": "003",
        "trip_id": "002",
        "amount_usd": "153.00",
        "expense_type": "meals",
        "vendor_type": "restaurant",
        "vendor_name": "Olive Yurt"
    },
    {
        "expense_id": "004",
        "trip_id": "002",
        "amount_usd": "1996.00",
        "expense_type": "airfare",
        "vendor_type": "transportation",
        "vendor_name": "Southeast Airlines"
    },
    {
        "expense_id": "005",
        "trip_id": "002",
        "amount_usd": "34.68",
        "expense_type": "meals",
        "vendor_type": "restaurant",
        "vendor_name": "The Great Grill"
    },
    {
        "expense_id": "006",
        "trip_id": "002",
        "amount_usd": "22.40",
        "expense_type": "meals",
        "vendor_type": "restaurant",
        "vendor_name": "The Great Grill"
    },
    {
        "expense_id": "007",
        "trip_id": "003",
        "amount_usd": "59.50",
        "expense_type": "entertainment",
        "vendor_type": "theater",
        "vendor_name": "Silver Screen"
    }
]
Part 1: Basic Rules
Problem Requirements
Write a function to check expenses against a list of rules. Start with these four rules:

Restaurant expenses cannot cost more than $75.
No airfare expenses allowed.
No entertainment expenses allowed.
No expense of any kind can cost more than $250.
You need to fill in this function:

def evaluate_rules(rules: list, expenses: list) -> ???:
    """
    Check expenses against a list of rules.

    Args:
        rules: List of rules (you define the structure)
        expenses: List of expense data

    Returns:
        Decide on the return type with your interviewer
    """
    pass
Expected Results
Based on the data above, your code should flag these items:

Expense "003": Flagged. It is a restaurant meal costing $153 (Limit is $75).
Expense "004": Flagged. It is airfare (not allowed), and it is over $250.
Expense "007": Flagged. It is entertainment (not allowed).
Things to Discuss
Before writing code, talk to your interviewer about these points:

Return Type: What should the function give back?
A list of IDs?
A dictionary of errors?
Detailed objects explaining the error?
Rule Structure: How should we save the rules?
Different classes for every rule? (Usually a bad idea).
Data objects that a generic engine reads?
Something like SQL filters?
Wrong Approach: Hardcoding
The interviewer does not want you to do this:

# ❌ Don't do this - it is hard to change later
def check_restaurant_75(expense):
    return expense.get("vendor_type") == "restaurant" and float(expense.get("amount_usd", 0)) > 75

def check_no_airfare(expense):
    return expense.get("expense_type") == "airfare"
Why this is bad:

You must change the code to add a rule.
You cannot add rules using an API.
It breaks the Open/Closed Principle.
It is hard to manage if you have 100 rules.
Solution: Data-Driven Rules
The Idea: Treat rules as data. Build one generic engine that reads the rule settings and checks the data.

from typing import Any
from dataclasses import dataclass
from enum import Enum

class Operator(Enum):
    EQUALS = "=="
    NOT_EQUALS = "!="
    GREATER_THAN = ">"
    LESS_THAN = "<"
    GREATER_THAN_OR_EQUAL = ">="
    LESS_THAN_OR_EQUAL = "<="

@dataclass
class Condition:
    """Checks a single field in an expense."""
    field: str           # Field to check (e.g., "expense_type")
    operator: Operator   # Comparison operator
    value: Any           # Value to compare against

    def matches(self, expense: dict) -> bool:
        """Returns True if the expense matches this condition."""
        expense_value = expense.get(self.field)
        if expense_value is None:
            return False

        # Handle numeric comparisons
        if self.operator in (Operator.GREATER_THAN, Operator.LESS_THAN,
                            Operator.GREATER_THAN_OR_EQUAL, Operator.LESS_THAN_OR_EQUAL):
            try:
                expense_value = float(expense_value)
                compare_value = float(self.value)
            except (ValueError, TypeError):
                return False
        else:
            compare_value = self.value

        if self.operator == Operator.EQUALS:
            return expense_value == compare_value
        elif self.operator == Operator.NOT_EQUALS:
            return expense_value != compare_value
        elif self.operator == Operator.GREATER_THAN:
            return expense_value > compare_value
        elif self.operator == Operator.LESS_THAN:
            return expense_value < compare_value
        elif self.operator == Operator.GREATER_THAN_OR_EQUAL:
            return expense_value >= compare_value
        elif self.operator == Operator.LESS_THAN_OR_EQUAL:
            return expense_value <= compare_value
        return False

@dataclass
class Rule:
    """
    A rule has a list of conditions.
    All conditions must be TRUE for the rule to trigger (AND logic).
    """
    rule_id: str
    description: str
    conditions: list[Condition]

    def is_violated_by(self, expense: dict) -> bool:
        """Returns True if expense violates this rule (all conditions match)."""
        return all(condition.matches(expense) for condition in self.conditions)

@dataclass
class Violation:
    """Stores details about a broken rule."""
    expense_id: str
    rule_id: str
    rule_description: str

def evaluate_rules(rules: list[Rule], expenses: list[dict]) -> list[Violation]:
    """Check all expenses against all rules."""
    violations = []
    for expense in expenses:
        expense_id = expense.get("expense_id", "unknown")
        for rule in rules:
            if rule.is_violated_by(expense):
                violations.append(Violation(
                    expense_id=expense_id,
                    rule_id=rule.rule_id,
                    rule_description=rule.description
                ))
    return violations
Creating the Rules:

rules = [
    Rule(
        rule_id="R001",
        description="No expense at a restaurant can exceed $75",
        conditions=[
            Condition("vendor_type", Operator.EQUALS, "restaurant"),
            Condition("amount_usd", Operator.GREATER_THAN, 75)
        ]
    ),
    Rule(
        rule_id="R002",
        description="No airfare expenses",
        conditions=[
            Condition("expense_type", Operator.EQUALS, "airfare")
        ]
    ),
    Rule(
        rule_id="R003",
        description="No entertainment expenses",
        conditions=[
            Condition("expense_type", Operator.EQUALS, "entertainment")
        ]
    ),
    Rule(
        rule_id="R004",
        description="No expenses over $250",
        conditions=[
            Condition("amount_usd", Operator.GREATER_THAN, 250)
        ]
    )
]

violations = evaluate_rules(rules, expenses)
for v in violations:
    print(f"Expense {v.expense_id}: {v.rule_description}")
Output:

Expense 003: No expense at a restaurant can exceed $75
Expense 004: No airfare expenses
Expense 004: No expenses over $250
Expense 007: No entertainment expenses
Performance Analysis:

Time: O(E × R × C). E is expenses, R is rules, C is conditions.
Space: O(V). V is the number of violations found.
Part 2: Group Rules
Problem Requirements
Interviewer: "That works well for single items. Now managers want to check entire trips. How do you handle that?"

You need to add support for rules like:

A total trip cannot cost more than $2000.
Total meal costs cannot be more than $200 per trip.
In our data, trip "002" breaks both rules:

Trip total is $2206.08 (Limit is $2000).
Meal total is $210.08 (Limit is $200).
How to Reuse Code
The big question is: Can we use the code from Part 1, or do we start over?

Good news: We can reuse the Condition class! The main differences are:

| Feature | Single Rule | Group Rule | | --- | --- | --- | | Scope | Checks one item | Checks a group of items | | Filter | Match conditions | Optional filter to pick items | | Check | Value vs Limit | Total Sum vs Limit |

Solution: Checking Groups
We use the Condition class to filter the list, and then we add up the numbers.

from collections import defaultdict
from dataclasses import dataclass, field
from typing import Optional

@dataclass
class GroupRule:
    """
    A rule that applies to a group of expenses.
    Reuses Condition from Part 1 for filtering!
    """
    rule_id: str
    description: str
    group_by: str                          # Field to group by (e.g., "trip_id")
    aggregate_field: str                   # Field to sum (e.g., "amount_usd")
    threshold: float                       # Maximum allowed sum
    filter_condition: Optional[Condition] = None  # Reuses Part 1's Condition!

@dataclass
class GroupViolation:
    """Result of a group rule violation."""
    group_id: str
    rule_id: str
    rule_description: str
    actual_value: float
    threshold: float
    expense_ids: list[str] = field(default_factory=list)

def evaluate_group_rules(
    group_rules: list[GroupRule],
    expenses: list[dict]
) -> list[GroupViolation]:
    """Evaluate group-level rules."""
    violations = []

    for rule in group_rules:
        # Step 1: Group expenses by the specified field
        groups: dict[str, list[dict]] = defaultdict(list)
        for expense in expenses:
            group_key = expense.get(rule.group_by)
            if group_key:
                groups[group_key].append(expense)

        # Step 2: Evaluate each group
        for group_id, group_expenses in groups.items():
            # Apply filter using Part 1's Condition.matches()!
            if rule.filter_condition:
                filtered = [e for e in group_expenses
                           if rule.filter_condition.matches(e)]
            else:
                filtered = group_expenses

            # Step 3: Calculate aggregate
            total = 0.0
            expense_ids = []
            for expense in filtered:
                try:
                    total += float(expense.get(rule.aggregate_field, 0))
                    expense_ids.append(expense.get("expense_id", "unknown"))
                except (ValueError, TypeError):
                    pass

            # Step 4: Check threshold
            if total > rule.threshold:
                violations.append(GroupViolation(
                    group_id=group_id,
                    rule_id=rule.rule_id,
                    rule_description=rule.description,
                    actual_value=total,
                    threshold=rule.threshold,
                    expense_ids=expense_ids
                ))

    return violations
Defining Group Rules:

group_rules = [
    GroupRule(
        rule_id="G001",
        description="Trip total cannot exceed $2000",
        group_by="trip_id",
        aggregate_field="amount_usd",
        threshold=2000.0,
        filter_condition=None  # All expenses in trip
    ),
    GroupRule(
        rule_id="G002",
        description="Total meal expenses cannot exceed $200 per trip",
        group_by="trip_id",
        aggregate_field="amount_usd",
        threshold=200.0,
        # REUSING Condition from Part 1!
        filter_condition=Condition("expense_type", Operator.EQUALS, "meals")
    )
]

group_violations = evaluate_group_rules(group_rules, expenses)
for v in group_violations:
    print(f"Trip {v.group_id}: {v.rule_description}")
    print(f"  Actual: ${v.actual_value:.2f}, Threshold: ${v.threshold:.2f}")
Output:

Trip 002: Trip total cannot exceed $2000
  Actual: $2206.08, Threshold: $2000.00
Trip 002: Total meal expenses cannot exceed $200 per trip
  Actual: $210.08, Threshold: $200.00
Combining the Results
For a real system, you should combine both results into one report:

@dataclass
class EvaluationResult:
    """Complete evaluation result."""
    individual_violations: list[Violation]
    group_violations: list[GroupViolation]

    def to_response(self) -> dict:
        """Format as API response."""
        return {
            "flagged_expenses": [
                {"expense_id": v.expense_id, "rule_id": v.rule_id, "reason": v.rule_description}
                for v in self.individual_violations
            ],
            "flagged_groups": [
                {
                    "group_id": v.group_id,
                    "rule_id": v.rule_id,
                    "reason": v.rule_description,
                    "actual": v.actual_value,
                    "threshold": v.threshold,
                    "expense_ids": v.expense_ids
                }
                for v in self.group_violations
            ]
        }

def evaluate_all(
    individual_rules: list[Rule],
    group_rules: list[GroupRule],
    expenses: list[dict]
) -> EvaluationResult:
    """Evaluate both individual and group rules."""
    return EvaluationResult(
        individual_violations=evaluate_rules(individual_rules, expenses),
        group_violations=evaluate_group_rules(group_rules, expenses)
    )
Handling Conflicting Rules
Interviewer: "What if a single expense is fine, but the trip is too expensive?"

Example: A $20 meal is allowed (under $75), but the whole trip costs $3000 (over $2000).

The system should show:

The expense is valid on its own.
The trip is flagged as invalid.
This is why we return two separate lists. It lets the user see both the individual item status and the group status.

Another Way: SQL Style
Some interviewers like to think about rules like SQL queries. You can design it like this:

@dataclass
class SQLLikeRule:
    """
    Filter (SELECT): conditions that must match for this rule to apply.
    Validator: the actual violation check.
    """
    rule_id: str
    description: str
    filter_conditions: list[Condition]  # WHERE clause - which expenses this applies to
    violation_condition: Condition      # What makes it a violation

    def applies_to(self, expense: dict) -> bool:
        """Does this rule apply to this expense?"""
        return all(c.matches(expense) for c in self.filter_conditions)

    def is_violated_by(self, expense: dict) -> bool:
        """Check if expense violates this rule."""
        if not self.applies_to(expense):
            return False
        return self.violation_condition.matches(expense)
This method separates "does this rule apply?" from "did you break the rule?".

Extra Topics
Future Improvements
OR Logic: How do we handle "OR" conditions?
Add a LogicalOperator to combine conditions.
Allow groups of conditions nested inside each other.
API Design: How do we save these rules?
Use JSON to define rules.
Check if the rule is valid before saving it to the database.
Priorities: Some rules might be more important.
Add a priority number to the rule.
Stop checking if a high-priority rule is broken.
Performance Considerations
Many Expenses: How to handle millions of items?
Use database indexes.
Process items in batches (pagination).
Run checks in parallel.
Many Rules: How to handle 100+ rules?
Group rules by the fields they check (e.g., check all "amount" rules together).
Use decision trees.
Edge Cases
Missing Fields: What if the data is missing the amount_usd?
Bad Data: What if the amount is "ABC" instead of a number?
Empty Groups: What if a trip has no expenses?
Complexity Summary
Part 1: Individual Rules
| Operation | Time Complexity | Space Complexity | | --- | --- | --- | | Evaluate all | O(E × R × C) | O(V) | | Add new rule | O(1) | O(C) |

E = expenses
R = rules
C = conditions per rule
V = violations found
Part 2: Group Rules
| Operation | Time Complexity | Space Complexity | | --- | --- | --- | | Group expenses | O(E) | O(E) | | Evaluate groups | O(G × R × E_g) | O(G × V) |

G = number of groups (trips)
E_g = expenses inside a group
R = group rules