RBAC Role Resolver
Problem Definition
You need to build a Role-Based Access Control (RBAC) system. This system manages user roles across a structure of accounts. The accounts are organized like a tree (hierarchy).

You have two inputs:

Accounts: A list showing how accounts are connected (parents and children).
User Role Assignments: A list showing which users have which roles on specific accounts.
accounts = [
    {"accountId": "org_1", "parent": None},
    {"accountId": "wksp_1", "parent": "org_1"},
    {"accountId": "wksp_2", "parent": "org_1"},
    {"accountId": "team_1", "parent": "wksp_1"}
]

user_role_assignments = [
    {"userId": "usr_1", "accountId": "org_1", "role": "admin"},
    {"userId": "usr_2", "accountId": "wksp_1", "role": "editor"},
    {"userId": "usr_3", "accountId": "wksp_1", "role": "viewer"},
    {"userId": "usr_1", "accountId": "wksp_2", "role": "editor"}
]
The Rules
An account has only one parent.
There are no loops.
The tree is small (max 3 levels deep: Organization → Workspace → Team).
Inheritance: If a user has a role at a parent account, they automatically have that role on all child accounts.
Example Logic
# usr_1 is an admin at org_1
# If we ask for usr_1's roles at wksp_1 (a child of org_1):
# - usr_1 inherits "admin" from org_1

rbac = RBACRoleResolver(accounts, user_role_assignments)
rbac.getUserRoles("usr_1", "org_1")   # Returns: ["admin"]
rbac.getUserRoles("usr_1", "wksp_1")  # Returns: ["admin"] (inherited)
rbac.getUserRoles("usr_1", "wksp_2")  # Returns: ["admin", "editor"]
rbac.getUserRoles("usr_2", "wksp_1")  # Returns: ["editor"]
rbac.getUserRoles("usr_2", "org_1")   # Returns: [] (no role at the top level)
Phase 1: Direct Role Lookup
Task Requirements
Write a class that finds roles assigned directly to a user for a specific account. Do not worry about inheritance yet.

class RBACRoleResolver:
    def __init__(self, accounts: list[dict], user_role_assignments: list[dict]):
        """
        Setup the resolver with accounts and assignments.

        Args:
            accounts: List of account objects
            user_role_assignments: List of who has what role where
        """
        pass

    def getUserRoles(self, userId: str, accountId: str) -> list[str]:
        """
        Get roles directly assigned to the user for this account.

        Returns:
            List of role names (e.g., ["admin", "editor"])
        """
        pass
Usage Example
rbac = RBACRoleResolver(accounts, user_role_assignments)
rbac.getUserRoles("usr_1", "org_1")   # Returns: ["admin"]
rbac.getUserRoles("usr_1", "wksp_2")  # Returns: ["editor"]
rbac.getUserRoles("usr_2", "wksp_1")  # Returns: ["editor"]
rbac.getUserRoles("usr_3", "org_1")   # Returns: []
Questions to Ask
does the order of the roles matter?
Can a user have more than one role on one account?
Are role names case-sensitive?
What should happen if the user or account does not exist?
Phase 2: Adding Inheritance
Task Requirements
Update your code to handle inheritance. When you check a user's roles for an account, you must also include roles from all ancestor accounts (parent, grandparent, etc.).

def getUserRoles(self, userId: str, accountId: str) -> list[str]:
    """
    Get all roles for the user, including inherited ones.

    If a user is an admin at the Organization level, they are
    also an admin at all Workspaces and Teams below it.

    Returns:
        List of role names (direct + inherited)
    """
    pass
Usage Example
accounts = [
    {"accountId": "org_1", "parent": None},
    {"accountId": "wksp_1", "parent": "org_1"},
    {"accountId": "team_1", "parent": "wksp_1"}
]

user_role_assignments = [
    {"userId": "usr_1", "accountId": "org_1", "role": "admin"},
    {"userId": "usr_1", "accountId": "wksp_1", "role": "editor"},
    {"userId": "usr_2", "accountId": "wksp_1", "role": "viewer"}
]

rbac = RBACRoleResolver(accounts, user_role_assignments)
rbac.getUserRoles("usr_1", "org_1")   # Returns: ["admin"]
rbac.getUserRoles("usr_1", "wksp_1")  # Returns: ["admin", "editor"]
rbac.getUserRoles("usr_1", "team_1")  # Returns: ["admin", "editor"] (inherited)
rbac.getUserRoles("usr_2", "team_1")  # Returns: ["viewer"] (inherited from wksp_1)
rbac.getUserRoles("usr_2", "org_1")   # Returns: []
Interview Questions
What is the Time Complexity of your function?
How would you speed this up if we call it many times?
Why did you choose these data structures?
Phase 3: Finding Users with Access
Task Requirements
Write a function to find all users who have access to a specific account. This includes:

Users assigned directly to this account.
Users assigned to any parent account (because they inherit access).
def getUsersForAccount(self, accountId: str) -> list[str]:
    """
    Get all users who have any role on this account.

    Includes:
    - Direct assignments
    - Inherited access from ancestors

    Returns:
        List of user IDs
    """
    pass
Usage Example
accounts = [
    {"accountId": "org_1", "parent": None},
    {"accountId": "wksp_1", "parent": "org_1"},
    {"accountId": "wksp_2", "parent": "org_1"}
]

user_role_assignments = [
    {"userId": "usr_1", "accountId": "org_1", "role": "admin"},
    {"userId": "usr_2", "accountId": "wksp_1", "role": "editor"},
    {"userId": "usr_3", "accountId": "wksp_1", "role": "viewer"}
]

rbac = RBACRoleResolver(accounts, user_role_assignments)
rbac.getUsersForAccount("org_1")   # Returns: ["usr_1"]
rbac.getUsersForAccount("wksp_1")  # Returns: ["usr_1", "usr_2", "usr_3"]
rbac.getUsersForAccount("wksp_2")  # Returns: ["usr_1"]
Interview Questions
How do you make sure a user isn't listed twice?
What is the Time Complexity?
How would you optimize this for frequent use?
Phase 4: Filtering Users by Role
Task Requirements
Update the previous function to filter the users. Only return users who have ALL the required roles (either directly or inherited).

def getUsersForAccountWithFilter(self, accountId: str, roleFilters: list[str]) -> list[str]:
    """
    Get users who have ALL specified roles on the account.

    Args:
        accountId: The account to check
        roleFilters: List of roles they must have. If empty, return everyone.

    Returns:
        List of user IDs
    """
    pass
Usage Example
accounts = [
    {"accountId": "org_1", "parent": None},
    {"accountId": "wksp_1", "parent": "org_1"}
]

user_role_assignments = [
    {"userId": "usr_1", "accountId": "org_1", "role": "admin"},
    {"userId": "usr_1", "accountId": "wksp_1", "role": "editor"},
    {"userId": "usr_2", "accountId": "wksp_1", "role": "editor"},
    {"userId": "usr_3", "accountId": "wksp_1", "role": "viewer"}
]

rbac = RBACRoleResolver(accounts, user_role_assignments)

# No filter - return everyone
rbac.getUsersForAccountWithFilter("wksp_1", [])
# Returns: ["usr_1", "usr_2", "usr_3"]

# Filter: Must be "admin"
rbac.getUsersForAccountWithFilter("wksp_1", ["admin"])
# Returns: ["usr_1"] (inherited from org_1)

# Filter: Must be "editor"
rbac.getUsersForAccountWithFilter("wksp_1", ["editor"])
# Returns: ["usr_1", "usr_2"]

# Filter: Must be "admin" AND "editor"
rbac.getUsersForAccountWithFilter("wksp_1", ["admin", "editor"])
# Returns: ["usr_1"]

# Filter: Must be "superadmin" (nobody has this)
rbac.getUsersForAccountWithFilter("wksp_1", ["superadmin"])
# Returns: []
Solution Details
Phase 1: Direct Lookup Strategy
Plan:

Create a map (Dictionary).
The key is (userId, accountId).
The value is a set of roles.
This allows O(1) access time.
from collections import defaultdict

class RBACRoleResolver:
    def __init__(self, accounts: list[dict], user_role_assignments: list[dict]):
        # Map account to its parent
        self.parent_map = {}
        for account in accounts:
            self.parent_map[account["accountId"]] = account["parent"]

        # Map (userId, accountId) -> set of roles
        self.role_map = defaultdict(set)
        for assignment in user_role_assignments:
            key = (assignment["userId"], assignment["accountId"])
            self.role_map[key].add(assignment["role"])

    def getUserRoles(self, userId: str, accountId: str) -> list[str]:
        return list(self.role_map.get((userId, accountId), set()))
Time Complexity: O(1) Space Complexity: O(A + R) (A = accounts, R = assignments)

Phase 2: Inheritance Strategy
Plan:

Start at the requested account.
Check for roles.
Move to the parent account.
Repeat until you reach the top (where parent is None).
def getUserRoles(self, userId: str, accountId: str) -> list[str]:
    """Get roles from this account and all parents."""
    roles = set()
    current_account = accountId

    while current_account is not None:
        key = (userId, current_account)
        if key in self.role_map:
            roles.update(self.role_map[key])
        current_account = self.parent_map.get(current_account)

    return list(roles)
Time Complexity: O(D) (D = depth of tree, usually small) Space Complexity: O(R)

Phase 3: Finding Users Strategy
Plan:

Find the list of all ancestors for the account.
Look at every user who has a role on any of those ancestors.
Collect them in a Set to avoid duplicates.
Optimization: When initializing the class, create a second index that maps accountId -> Set of Users.

def __init__(self, accounts: list[dict], user_role_assignments: list[dict]):
    # ... previous setup ...

    # Index: accountId -> set of userIds directly assigned
    self.users_by_account = defaultdict(set)
    for assignment in user_role_assignments:
        self.users_by_account[assignment["accountId"]].add(assignment["userId"])

def _getAncestors(self, accountId: str) -> list[str]:
    """Get list of account + all parents."""
    ancestors = []
    current = accountId
    while current is not None:
        ancestors.append(current)
        current = self.parent_map.get(current)
    return ancestors

def getUsersForAccount(self, accountId: str) -> list[str]:
    users = set()
    for ancestor in self._getAncestors(accountId):
        users.update(self.users_by_account.get(ancestor, set()))
    return list(users)
Time Complexity: O(D × U) (D = depth, U = users per account) Space Complexity: O(U)

Phase 4: Filtering Strategy
Plan:

Get all users who have access (using Phase 3).
For each user, calculate their full role list (using Phase 2).
Check if their roles include all the required roles.
def getUsersForAccountWithFilter(self, accountId: str, roleFilters: list[str]) -> list[str]:
    """Get users who match the role filter."""
    # Get everyone with access
    all_users = self.getUsersForAccount(accountId)

    # If no filter, return everyone
    if not roleFilters:
        return all_users

    required_roles = set(roleFilters)
    result = []

    for user_id in all_users:
        # Get full roles for this user
        user_roles = set(self.getUserRoles(user_id, accountId))

        # Check if they have all required roles
        if required_roles.issubset(user_roles):
            result.append(user_id)

    return result
Time Complexity: O(U × D × F) (U = users, D = depth, F = number of filters) Space Complexity: O(U)

Full Code Solution
from collections import defaultdict

class RBACRoleResolver:
    def __init__(self, accounts: list[dict], user_role_assignments: list[dict]):
        # Map account to parent
        self.parent_map = {}
        for account in accounts:
            self.parent_map[account["accountId"]] = account["parent"]

        # Map: (userId, accountId) -> set of roles
        self.role_map = defaultdict(set)
        for assignment in user_role_assignments:
            key = (assignment["userId"], assignment["accountId"])
            self.role_map[key].add(assignment["role"])

        # Index: accountId -> set of userIds
        self.users_by_account = defaultdict(set)
        for assignment in user_role_assignments:
            self.users_by_account[assignment["accountId"]].add(assignment["userId"])

    def _getAncestors(self, accountId: str) -> list[str]:
        """Helper: Get account and all parents."""
        ancestors = []
        current = accountId
        while current is not None:
            ancestors.append(current)
            current = self.parent_map.get(current)
        return ancestors

    def getUserRoles(self, userId: str, accountId: str) -> list[str]:
        """Get all roles including inherited ones."""
        roles = set()
        for ancestor in self._getAncestors(accountId):
            key = (userId, ancestor)
            if key in self.role_map:
                roles.update(self.role_map[key])
        return list(roles)

    def getUsersForAccount(self, accountId: str) -> list[str]:
        """Get all users with any role on this account."""
        users = set()
        for ancestor in self._getAncestors(accountId):
            users.update(self.users_by_account.get(ancestor, set()))
        return list(users)

    def getUsersForAccountWithFilter(self, accountId: str, roleFilters: list[str]) -> list[str]:
        """Get users who have all specified roles."""
        all_users = self.getUsersForAccount(accountId)

        if not roleFilters:
            return all_users

        required_roles = set(roleFilters)
        return [
            user_id for user_id in all_users
            if required_roles.issubset(set(self.getUserRoles(user_id, accountId)))
        ]

# Test Execution
if __name__ == "__main__":
    accounts = [
        {"accountId": "org_1", "parent": None},
        {"accountId": "wksp_1", "parent": "org_1"},
        {"accountId": "wksp_2", "parent": "org_1"}
    ]

    user_role_assignments = [
        {"userId": "usr_1", "accountId": "org_1", "role": "admin"},
        {"userId": "usr_1", "accountId": "wksp_1", "role": "editor"},
        {"userId": "usr_2", "accountId": "wksp_1", "role": "editor"},
        {"userId": "usr_3", "accountId": "wksp_1", "role": "viewer"}
    ]

    rbac = RBACRoleResolver(accounts, user_role_assignments)

    # Phase 1 & 2: Get roles
    print("getUserRoles('usr_1', 'org_1'):", rbac.getUserRoles("usr_1", "org_1"))
    print("getUserRoles('usr_1', 'wksp_1'):", rbac.getUserRoles("usr_1", "wksp_1"))

    # Phase 3: Get users
    print("getUsersForAccount('wksp_1'):", rbac.getUsersForAccount("wksp_1"))

    # Phase 4: Filter users
    print("getUsersForAccountWithFilter('wksp_1', []):",
          rbac.getUsersForAccountWithFilter("wksp_1", []))
    print("getUsersForAccountWithFilter('wksp_1', ['admin']):",
          rbac.getUsersForAccountWithFilter("wksp_1", ["admin"]))
    print("getUsersForAccountWithFilter('wksp_1', ['admin', 'editor']):",
          rbac.getUsersForAccountWithFilter("wksp_1", ["admin", "editor"]))
Optimization and Scaling
Caching
Problem: Asking for the same user roles repeatedly is slow.

Solution: Use caching (Memoization). Store the result so you don't have to calculate it again.

from functools import lru_cache

@lru_cache(maxsize=1000)
def getUserRoles(self, userId: str, accountId: str) -> tuple[str, ...]:
    # Return tuple because lists cannot be hashed/cached
    roles = set()
    for ancestor in self._getAncestors(accountId):
        key = (userId, ancestor)
        if key in self.role_map:
            roles.update(self.role_map[key])
    return tuple(sorted(roles))
Handling Updates
Problem: What if a role is added while the system is running?

Solution: You must clear the cache.

Update the role_map.
Invalidate (clear) the specific cache entries.
In a distributed system, you might need an event system to tell other servers to clear their cache.
def addRoleAssignment(self, userId: str, accountId: str, role: str):
    """Add a role and clear cache."""
    key = (userId, accountId)
    self.role_map[key].add(role)
    self.users_by_account[accountId].add(userId)
    # Clear the cache because data changed
    self.getUserRoles.cache_clear()
Scaling Challenges
| Challenge | Impact | Solution | | --- | --- | --- | | Deep Hierarchy | Traversal takes too long | Pre-calculate ancestor lists. | | Many Users | Too many users per account | Use Sharding (split data by account). | | High Read Load | Too many queries | Use Redis as a caching layer. | | Real-time Updates | Data becomes stale | Use event-driven updates. |