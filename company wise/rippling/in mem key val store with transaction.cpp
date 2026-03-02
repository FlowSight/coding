In-Memory Key-Value Store with Transactions
The Challenge
You need to build a Key-Value Store that runs in memory. It needs to support standard operations (Create, Read, Update, Delete) and Transactions. This is a popular interview question because it tests if you understand data structures and how to manage temporary data states.

Important Goals
Accuracy: Changes made inside a transaction must be isolated. If you don't save (commit) them, they shouldn't change the main data.
Data Management: You need a smart way to track temporary changes so you can cancel (rollback) them easily.
Growth: The design should work for one transaction, but also be able to handle transactions inside other transactions (nested).
Part 1: The Basic Store
Requirements
First, build a simple store with these commands:

class Database:
    def set(self, key: str, value: str) -> None:
        """Save a value for a key."""
        pass

    def get(self, key: str) -> str | None:
        """Find the value for a key. Return None if not found."""
        pass

    def delete(self, key: str) -> bool:
        """Remove a key. Return True if it was there, False if not."""
        pass
How to Use It
db = Database()
db.set("key1", "val1")
print(db.get("key1"))    # Output: val1
print(db.get("key2"))    # Output: None
db.delete("key1")
print(db.get("key1"))    # Output: None
Solution for Part 1
The easiest way to do this is using a standard dictionary (HashMap). This makes every operation very fast (O(1)).

class Database:
    def __init__(self):
        self._store: dict[str, str] = {}

    def set(self, key: str, value: str) -> None:
        """Save a value for a key."""
        self._store[key] = value

    def get(self, key: str) -> str | None:
        """Find the value for a key. Return None if not found."""
        return self._store.get(key)

    def delete(self, key: str) -> bool:
        """Remove a key. Return True if it was there, False if not."""
        if key in self._store:
            del self._store[key]
            return True
        return False
Performance:

| Operation | Time | Space | | --- | --- | --- | | set | O(1) | O(1) | | get | O(1) | O(1) | | delete | O(1) | O(1) | | Overall | - | O(n) where n is the number of keys |

Part 2: Adding Basic Transactions
New Requirements
Interviewer: "Now, let's add transactions. We need begin(), commit(), and rollback()."

You need to add these rules:

begin(): Start a temporary workspace (transaction).
commit(): Save all changes from the workspace to the real database.
rollback(): Throw away all changes in the workspace.
When you read data inside a transaction, you should see your temporary changes.
Example 1: Saving Changes (Commit)
db = Database()
db.set("key0", "val0")
print(db.get("key0"))    # Output: val0 (saved in real DB)

db.begin()
print(db.get("key0"))    # Output: val0 (can see real DB data)
db.set("key1", "val1")
print(db.get("key1"))    # Output: val1 (visible inside transaction)
db.commit()

print(db.get("key1"))    # Output: val1 (saved permanently)
Example 2: Canceling Changes (Rollback)
db = Database()
db.begin()
db.set("key2", "val2")
print(db.get("key2"))    # Output: val2 (visible inside transaction)
db.rollback()

print(db.get("key2"))    # Output: None (changes were thrown away)
Thinking About the Design
Before coding, think about these problems:

How do we keep changes separate?
Option A: Copy the whole database when begin() starts. (Too slow if the database is big).
Option B: Use a separate temporary map for new changes. (Much faster).
How do we read data?
Look in the temporary map first. If it's not there, look in the real database.
How do we handle deletes?
If you delete a key in a transaction, you can't just remove it from the temporary map. You need a special "marker" that says "this key is deleted here."
Solution for Part 2
The best idea is to use a Transaction Layer. This layer only holds the changes made since begin() was called.

class Database:
    # A unique marker to represent deleted keys
    _DELETED = object()

    def __init__(self):
        self._store: dict[str, str] = {}
        self._transaction: dict[str, str | object] | None = None

    def set(self, key: str, value: str) -> None:
        """Set key to value."""
        if self._transaction is not None:
            self._transaction[key] = value
        else:
            self._store[key] = value

    def get(self, key: str) -> str | None:
        """Get value for key. Returns None if key doesn't exist."""
        if self._transaction is not None:
            if key in self._transaction:
                value = self._transaction[key]
                # Check if this key was marked as deleted
                if value is self._DELETED:
                    return None
                return value
        # Look in the main store if not in transaction
        return self._store.get(key)

    def delete(self, key: str) -> bool:
        """Delete key. Returns True if key existed, False otherwise."""
        # Check if key exists (looking at both transaction and main store)
        exists = self.get(key) is not None

        if self._transaction is not None:
            # Mark as deleted in the transaction
            self._transaction[key] = self._DELETED
        else:
            if key in self._store:
                del self._store[key]

        return exists

    def begin(self) -> None:
        """Start a new transaction."""
        self._transaction = {}

    def commit(self) -> None:
        """Save changes from the transaction."""
        if self._transaction is None:
            raise RuntimeError("No active transaction")

        # Move all changes to the main store
        for key, value in self._transaction.items():
            if value is self._DELETED:
                self._store.pop(key, None)
            else:
                self._store[key] = value

        self._transaction = None

    def rollback(self) -> None:
        """Cancel the current transaction."""
        if self._transaction is None:
            raise RuntimeError("No active transaction")

        # Just throw away the transaction map
        self._transaction = None
Why we did this:

Special Delete Marker: We created _DELETED = object(). This is a unique item that acts as a flag. It tells us "this key was deleted in this transaction."
Lazy Copying: We don't copy the whole database. We only track keys that change.
Read Logic: Always check the active transaction first. This ensures you see your own latest updates.
Performance:

| Operation | Time | Space | | --- | --- | --- | | begin | O(1) | O(1) | | commit | O(t) | O(1) | | rollback | O(1) | O(1) | | set/get/delete | O(1) | O(1) |

Note: t = number of keys changed in the transaction.

Part 3: Nested Transactions
New Requirements
Interviewer: "Great! Now make it work for nested transactions. This means you can start a transaction inside another one."

Here are the rules for nesting:

A child (inner) transaction can see changes from its parent.
If a child commits, its changes are sent to the parent, not the real database.
If a child rollbacks, its changes are gone. The parent is not changed.
Changes only go to the real database (global store) when the main (outermost) transaction commits.
Example: How Nesting Works
db = Database()
db.begin()                  # Transaction 1 (Parent)
db.set("key1", "val1")
db.set("key2", "val2")

db.begin()                  # Transaction 2 (Child)
print(db.get("key1"))       # Output: val1 (Seen from parent)
db.set("key1", "val1_child")
db.commit()                 # Child commits -> updates Parent

print(db.get("key1"))       # Output: val1_child (Parent is updated)
print(db.get("key2"))       # Output: val2 (Parent still has this)
db.commit()                 # Parent commits -> updates Real Database

print(db.get("key1"))       # Output: val1_child (Saved globally)
Designing the Solution
Think of this as a Stack of Cards.

The bottom card is the Real Database.
When you call begin(), you place a new blank card (layer) on top.
Reading: Look at the top card. If the value isn't there, look at the card below it, and so on.
Writing: Always write on the top card.
Commit: Take the changes from the top card and copy them to the card directly below it. Then throw the top card away.
Rollback: Just throw the top card away.
┌─────────────────────┐
│ Transaction 3 (Top) │  <- We write here
├─────────────────────┤
│ Transaction 2       │
├─────────────────────┤
│ Transaction 1       │
├─────────────────────┤
│ Global Store        │  <- Bottom Layer
└─────────────────────┘
Final Solution Code
class Database:
    _DELETED = object()

    def __init__(self):
        self._store: dict[str, str] = {}
        self._transaction_stack: list[dict[str, str | object]] = []

    def _current_transaction(self) -> dict[str, str | object] | None:
        """Get the current (top) transaction layer, or None."""
        return self._transaction_stack[-1] if self._transaction_stack else None

    def set(self, key: str, value: str) -> None:
        """Set key to value in the current transaction or global store."""
        current = self._current_transaction()
        if current is not None:
            current[key] = value
        else:
            self._store[key] = value

    def get(self, key: str) -> str | None:
        """
        Find value by looking from the top transaction down to the store.
        """
        # Search stack from top (newest) to bottom (oldest)
        for transaction in reversed(self._transaction_stack):
            if key in transaction:
                value = transaction[key]
                if value is self._DELETED:
                    return None
                return value

        # Look in the main store last
        return self._store.get(key)

    def delete(self, key: str) -> bool:
        """Delete key in the current transaction."""
        exists = self.get(key) is not None

        current = self._current_transaction()
        if current is not None:
            current[key] = self._DELETED
        else:
            if key in self._store:
                del self._store[key]

        return exists

    def begin(self) -> None:
        """Start a new nested transaction."""
        self._transaction_stack.append({})

    def commit(self) -> None:
        """
        Commit the current transaction.
        - If nested: merge changes into the parent.
        - If outermost: save changes to global store.
        """
        if not self._transaction_stack:
            raise RuntimeError("No active transaction")

        current = self._transaction_stack.pop()

        if self._transaction_stack:
            # Merge into the parent transaction
            parent = self._transaction_stack[-1]
            for key, value in current.items():
                parent[key] = value
        else:
            # Save to the main store
            for key, value in current.items():
                if value is self._DELETED:
                    self._store.pop(key, None)
                else:
                    self._store[key] = value

    def rollback(self) -> None:
        """Cancel the current transaction."""
        if not self._transaction_stack:
            raise RuntimeError("No active transaction")

        # Simply remove the top layer
        self._transaction_stack.pop()
Step-by-Step Example
Let's trace what happens in the stack:

Start: Stack is empty [].
set("key1", "A"): Written to global store.
begin(): Stack is [{}].
set("key1", "B"): Top layer is [{"key1": "B"}].
begin(): Stack is [{"key1": "B"}, {}].
set("key1", "C"): Top layer is {"key1": "C"}. Stack: [{"key1": "B"}, {"key1": "C"}].
get('key1'): Look at top layer -> finds "C".
commit(): Pop top layer. Merge "C" into layer below. Stack: [{"key1": "C"}].
commit(): Pop top layer. Save "C" to global store. Stack is empty [].
Performance
| Operation | Time | Space | | --- | --- | --- | | begin | O(1) | O(1) | | commit | O(t) | O(1) | | rollback | O(1) | O(1) | | get | O(d) | O(1) | | set/delete | O(1) | O(1) |

t = number of changes in the transaction.
d = depth of the stack (how many nested transactions there are).
Other Ways to Solve This
Method 1: Full Copy
Every time you call begin(), you copy the entire database to a new map.

Pros: Reading is very fast because you only look at one map.
Cons: Very slow and uses too much memory if you have a lot of data. O(n) for every begin().
Method 2: Undo Log
Instead of storing the new value, you store instructions on how to undo your change.

Pros: Changes happen immediately to the main data.
Cons: Rolling back is slow because you have to reverse every single action one by one. It is also harder to code correctly.
Tricky Situations
Commit without Begin: The code should raise an error.
Deleting Missing Keys: It should return False but not crash.
Resurrecting Keys: If you delete "key1" and then set "key1" again in the same transaction, it should act like a normal set operation.
Deep Nesting: The code should handle many layers of begin() calls without breaking (until memory runs out).
Doing Nothing: Calling begin() then immediately commit() is valid. It just does nothing.
Bonus Interview Questions
1. Can multiple threads use this?
Interviewer: "Is this thread-safe?"

Locking: You could use a "Global Lock" (Mutex). This means only one thread can do anything at a time. It is safe but slow.
Isolation: A better way is giving every thread its own separate transaction object.
2. How do we save to disk?
Interviewer: "What if the power goes out?"

WAL (Write-Ahead Log): Before updating memory, write the command to a file on disk. If the power fails, you can replay the file to get the data back.
3. What if we run out of memory?
Interviewer: "What if the data is too big for RAM?"

Eviction: Delete old data that hasn't been used in a while (LRU Cache).
Disk Storage: Store the main data on the hard drive and only keep frequently used data in memory.
4. What about stuck transactions?
Interviewer: "What if a user calls begin() but never calls commit()?"

Timeout: Add a timer. If a transaction takes too long, the system automatically calls rollback() to clean up memory.