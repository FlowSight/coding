Web API for Article Voting System
Problem Description
You need to build a voting system like Reddit or StackOverflow. Users can vote "up" or "down" on articles. You must track the votes and rank the articles.

This class handles the core logic in memory. Imagine a web API calls these functions.

Function Requirements
You need to write a class with these methods:

class ArticleVotingSystem:
    def add_article(self, article_name: str) -> int:
        """
        Creates a new article.
        Returns a unique article_id.
        """
        pass

    def up_vote_article(self, article_id: int, user_id: int) -> None:
        """
        User votes UP (+1 score).
        - If they already voted UP: Do nothing.
        - If they voted DOWN before: Change it to UP (this is a "flip").
        """
        pass

    def down_vote_article(self, article_id: int, user_id: int) -> None:
        """
        User votes DOWN (-1 score).
        - If they already voted DOWN: Do nothing.
        - If they voted UP before: Change it to DOWN (this is a "flip").
        """
        pass

    def get_most_recent_k_flips(self, user_id: int, k: int) -> list[int]:
        """
        Get the last k articles where the user changed their mind ("flipped").
        A flip happens when you go Up -> Down OR Down -> Up.
        
        ⚠️ IMPORTANT: This must run in O(k) time, not O(total_flips).
        """
        pass

    def get_top_k(self, k: int) -> list[int]:
        """
        Get the top k articles based on score (upvotes minus downvotes).
        The list should start with the highest score.
        """
        pass
Rules and Details
Duplicate Votes: If a user votes "up" twice on the same article, ignore the second vote.
What is a Flip?: A flip happens only when a user changes their vote type:
Up → Down = Flip
Down → Up = Flip
Up → Up = Not a flip
Speed Rule (O(k)): The function get_most_recent_k_flips must be very fast. You should only look at the last k items. Do not read the whole history list.
IDs: Article IDs are unique numbers (integers).
How it Works (Example)
system = ArticleVotingSystem()

# Make articles
a1 = system.add_article("Python Tips")      # ID: 1
a2 = system.add_article("Java Guide")       # ID: 2
a3 = system.add_article("Go Patterns")      # ID: 3
a4 = system.add_article("Rust Basics")      # ID: 4

# User 100 votes
system.up_vote_article(a1, user_id=100)     # User 100: upvote 1
system.up_vote_article(a2, user_id=100)     # User 100: upvote 2
system.down_vote_article(a1, user_id=100)   # User 100: FLIP on 1 (up -> down)
system.up_vote_article(a3, user_id=100)     # User 100: upvote 3
system.down_vote_article(a2, user_id=100)   # User 100: FLIP on 2 (up -> down)
system.up_vote_article(a2, user_id=100)     # User 100: FLIP on 2 (down -> up)

# User 100's flip history: [article_1, article_2, article_2]
# (Article 2 was flipped twice)

system.get_most_recent_k_flips(user_id=100, k=3)
# Returns: [2, 2, 1] (Newest first)

system.get_most_recent_k_flips(user_id=100, k=2)
# Returns: [2, 2]

# Scores:
# Article 1: -1 (upvoted then downvoted)
# Article 2: +1 (up, then down, then up)
# Article 3: +1 (upvoted once)
# Article 4: 0 (no votes)

system.get_top_k(2)  # Returns: [2, 3] or [3, 2] (both have score +1)
Solution Approach
Choosing Data Structures
To make this fast, we need specific data structures for each task:

| Requirement | Data Structure | Why | | --- | --- | --- | | Check user's vote | Nested Dictionary {user: {article: vote}} | Fast O(1) lookups. | | Flip history | Dictionary with List {user: [article_id]} | Easy to add to the end and read the end (O(k)). | | Article scores | Dictionary {article: score} | Fast O(1) updates. | | Top K articles | Heap or Sorting | Good for finding highest numbers. |

Python Solution
from collections import defaultdict
import heapq

class ArticleVotingSystem:
    def __init__(self):
        self.next_article_id = 1
        self.articles = {}  # article_id -> article_name

        # user_id -> {article_id -> vote} where vote is 1 (up) or -1 (down)
        self.user_votes: dict[int, dict[int, int]] = defaultdict(dict)

        # user_id -> list of article_ids where flips occurred (append-only)
        self.user_flips: dict[int, list[int]] = defaultdict(list)

        # article_id -> score (upvotes - downvotes)
        self.article_scores: dict[int, int] = defaultdict(int)

    def add_article(self, article_name: str) -> int:
        """Create article and return ID."""
        article_id = self.next_article_id
        self.next_article_id += 1
        self.articles[article_id] = article_name
        return article_id

    def _vote(self, article_id: int, user_id: int, new_vote: int) -> None:
        """
        Helper function for voting.
        new_vote: 1 is up, -1 is down.
        """
        if article_id not in self.articles:
            return  # Article does not exist

        current_vote = self.user_votes[user_id].get(article_id)

        if current_vote == new_vote:
            # Same vote as before - do nothing
            return

        if current_vote is not None:
            # User is changing vote - this is a FLIP
            self.user_flips[user_id].append(article_id)
            # Remove old vote value from score
            self.article_scores[article_id] -= current_vote

        # Add new vote value
        self.user_votes[user_id][article_id] = new_vote
        self.article_scores[article_id] += new_vote

    def up_vote_article(self, article_id: int, user_id: int) -> None:
        """Vote up (+1)."""
        self._vote(article_id, user_id, 1)

    def down_vote_article(self, article_id: int, user_id: int) -> None:
        """Vote down (-1)."""
        self._vote(article_id, user_id, -1)

    def get_most_recent_k_flips(self, user_id: int, k: int) -> list[int]:
        """
        Get last k flips.
        
        Time Complexity: O(min(k, flips)) - we slice only the end.
        """
        flips = self.user_flips[user_id]
        # Get last k items in reverse (newest first)
        return flips[-1:-k-1:-1] if flips else []

    def get_top_k(self, k: int) -> list[int]:
        """
        Get top k articles by score.
        
        Time Complexity: O(n log k) using a heap.
        """
        # Use a min-heap to keep the top k scores
        heap = []

        for article_id in self.articles:
            score = self.article_scores[article_id]
            if len(heap) < k:
                heapq.heappush(heap, (score, article_id))
            elif score > heap[0][0]:
                heapq.heapreplace(heap, (score, article_id))

        # Take items out (they come out smallest first, so we reverse)
        result = []
        while heap:
            score, article_id = heapq.heappop(heap)
            result.append(article_id)
        return result[::-1]
Understanding the O(k) Rule
The get_most_recent_k_flips function is the tricky part.

def get_most_recent_k_flips(self, user_id: int, k: int) -> list[int]:
    flips = self.user_flips[user_id]
    # Python slicing with negative numbers is O(k), not O(n)!
    return flips[-1:-k-1:-1]
Common Mistakes:

❌ Reversing the whole list first. This is slow: O(n).
❌ Copying the whole list. This is slow: O(n).
❌ Reading from the start of the list. This is slow: O(n).
Why our code is fast:

flips[-1:-k-1:-1] tells Python to grab exactly k items starting from the end.
It does not touch the beginning of the list.
This meets the requirement: O(k) Time and O(k) Space.
Using a Deque (Alternative)
If you prefer a different data structure, you can use a deque. It is optimized for adding and removing from the ends.

from collections import deque

class ArticleVotingSystemDeque:
    def __init__(self):
        # ... same setup ...
        # Deque is fast for ends
        self.user_flips: dict[int, deque] = defaultdict(deque)

    def get_most_recent_k_flips(self, user_id: int, k: int) -> list[int]:
        flips = self.user_flips[user_id]
        result = []
        # Look at the right end (most recent)
        for i in range(min(k, len(flips))):
            result.append(flips[-(i+1)])
        return result
Making Top K Faster
If we call get_top_k very often, the heap approach might be too slow. We can keep a sorted list updated all the time.

Optimized Solution (SortedList)
from sortedcontainers import SortedList

class ArticleVotingSystemOptimized:
    def __init__(self):
        # ... same fields ...
        # SortedList keeps items sorted automatically
        self.sorted_articles = SortedList()

    def _vote(self, article_id: int, user_id: int, new_vote: int) -> None:
        if article_id not in self.articles:
            return

        current_vote = self.user_votes[user_id].get(article_id)
        if current_vote == new_vote:
            return

        old_score = self.article_scores[article_id]

        # 1. Remove old score from sorted list (O(log n))
        if (-old_score, article_id) in self.sorted_articles:
            self.sorted_articles.discard((-old_score, article_id))

        # Update the score logic
        if current_vote is not None:
            self.user_flips[user_id].append(article_id)
            self.article_scores[article_id] -= current_vote

        self.user_votes[user_id][article_id] = new_vote
        self.article_scores[article_id] += new_vote
        new_score = self.article_scores[article_id]

        # 2. Add new score to sorted list (O(log n))
        self.sorted_articles.add((-new_score, article_id))

    def get_top_k(self, k: int) -> list[int]:
        """O(k) - We just grab the first k items."""
        return [article_id for _, article_id in self.sorted_articles[:k]]
Note: SortedList is an external Python library. In an interview, tell the interviewer you would use a Balanced Binary Search Tree (BST).

Comparison
| Method | Vote Speed | Top-K Speed | Best For... | | --- | --- | --- | --- | | Heap | O(1) | O(n log k) | Rare Top-K checks | | SortedList | O(log n) | O(k) | Frequent Top-K checks |

Extra Interview Questions
1. Deleting Votes
"What if a user wants to remove their vote completely?"

You can add a remove_vote function:

def remove_vote(self, article_id: int, user_id: int) -> None:
    if article_id not in self.articles:
        return

    current_vote = self.user_votes[user_id].get(article_id)
    if current_vote is None:
        return  # They haven't voted

    # Adjust the score
    self.article_scores[article_id] -= current_vote
    del self.user_votes[user_id][article_id]
    # Note: Removing a vote is usually NOT a flip.
2. Handling Ties
"What if two articles have the same score?"

You need a tie-breaker rule. Options:

Oldest article first.
Lowest ID first.
Alphabetical name.
def get_top_k(self, k: int) -> list[int]:
    # Tie-break: if scores match, use ID (lower ID wins)
    scored = [(self.article_scores[aid], -aid, aid) for aid in self.articles]
    scored.sort(reverse=True)
    return [aid for _, _, aid in scored[:k]]
3. Many Users at Once (Concurrency)
"What happens if 1,000 users vote at the exact same time?"

Locks: Use locks so only one person changes an article's score at a time.
Database: In a real app, the database handles this consistency.
Time and Space Complexity
| Operation | Time Complexity | Space Complexity | | --- | --- | --- | | add_article | O(1) | O(1) | | up_vote_article | O(1) | O(1) | | down_vote_article | O(1) | O(1) | | get_most_recent_k_flips | O(min(k, F)) | O(k) | | get_top_k (Heap) | O(n log k) | O(k) | | get_top_k (SortedList) | O(k) | O(1) |

Total Space Needed:

You store every article.
You store every vote.
You store the list of flips.