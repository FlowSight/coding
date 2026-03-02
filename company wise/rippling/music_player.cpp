Music Player
Task Overview
You need to build a music player system like Spotify. The system needs to track when songs are added and played. It also needs to show data about user listening habits.

You will build this in three steps. Each step adds new features to the code.

Important Rules
Speed: Make the code fast. The interviewer will ask about Time Complexity (Big O) for every function.
Data Structures: Use the right tools (like HashMaps or Lists) to look up data quickly.
Edge Cases: Handle tricky situations. For example, what if a user plays the same song twice? What if a song does not exist?
Part 1: Basic Setup
Requirements
Create a MusicPlayer class with these methods:

class MusicPlayer:
    def add_song(self, song_title: str) -> int:
        """
        Add a song to the library.

        Args:
            song_title: Name of the song

        Returns:
            A unique song_id (integer) for this song
        """
        pass

    def play_song(self, song_id: int, user_id: str) -> None:
        """
        Record that a user played a song.

        Args:
            song_id: The ID of the song
            user_id: The ID of the user
        """
        pass

    def print_analytics_summary(self) -> None:
        """
        Print a list of songs and how many unique people listened to them.

        Format: "song_title: N unique listeners"
        Order: Print in the order the songs were added.
        """
        pass
How it Works
player = MusicPlayer()

# Add songs
song1 = player.add_song("Bohemian Rhapsody")  # Returns 1
song2 = player.add_song("Stairway to Heaven")  # Returns 2
song3 = player.add_song("Hotel California")    # Returns 3

# Simulate plays
player.play_song(1, "alice")
player.play_song(1, "bob")
player.play_song(1, "alice")  # Alice plays it again (duplicate)
player.play_song(2, "alice")
player.play_song(2, "charlie")
player.play_song(3, "alice")

# Print results
player.print_analytics_summary()
Result
Bohemian Rhapsody: 2 unique listeners
Stairway to Heaven: 2 unique listeners
Hotel California: 1 unique listener
Note: Alice played "Bohemian Rhapsody" twice. However, she only counts as 1 unique listener.

Solution for Part 1
class MusicPlayer:
    def __init__(self):
        self.next_song_id = 1
        self.songs = {}              # song_id -> song_title
        self.song_order = []         # Keeps track of order for printing
        self.song_listeners = {}     # song_id -> set of user_ids

    def add_song(self, song_title: str) -> int:
        """Time: O(1)"""
        song_id = self.next_song_id
        self.next_song_id += 1

        self.songs[song_id] = song_title
        self.song_order.append(song_id)
        self.song_listeners[song_id] = set()

        return song_id

    def play_song(self, song_id: int, user_id: str) -> None:
        """Time: O(1)"""
        if song_id not in self.songs:
            return  # Or raise error if asked

        self.song_listeners[song_id].add(user_id)

    def print_analytics_summary(self) -> None:
        """Time: O(S) where S is number of songs."""
        for song_id in self.song_order:
            title = self.songs[song_id]
            count = len(self.song_listeners[song_id])
            print(f"{title}: {count} unique listener{'s' if count != 1 else ''}")
Performance Summary:

| Method | Time | Space | | --- | --- | --- | | add_song | O(1) | O(1) per song | | play_song | O(1) | O(1) per unique pair | | print_analytics_summary | O(S) | O(1) extra space |

S = number of songs

Part 2: User History
New Requirement
Interviewer: "We need to track history. Write a function to get the last 3 unique songs a user played."

Add this method:

def last_three_played_song_titles(self, user_id: str) -> list[str]:
    """
    Get the last 3 unique songs played by a user.

    Args:
        user_id: The ID of the user

    Returns:
        List of song titles (newest first).
        If less than 3, return all of them.
        If no history, return empty list.
    """
    pass
Rules for History
Unique Songs Only: If a user plays the same song again, do not list it twice.
Newest First: The most recent song goes at the top.
Memory Limit: Only store 3 songs per user.
Replay Updates Position: If a user plays a song that is already in their history, move that song to the front.
How it Works
player = MusicPlayer()

song1 = player.add_song("Song A")  # ID: 1
song2 = player.add_song("Song B")  # ID: 2
song3 = player.add_song("Song C")  # ID: 3
song4 = player.add_song("Song D")  # ID: 4

# User plays songs
player.play_song(1, "alice")  # History: [A]
player.play_song(2, "alice")  # History: [B, A]
player.play_song(3, "alice")  # History: [C, B, A]
player.play_song(4, "alice")  # History: [D, C, B] - A is removed

print(player.last_three_played_song_titles("alice"))  # ["Song D", "Song C", "Song B"]

# Alice replays Song B
player.play_song(2, "alice")  # History: [B, D, C] - B moves to front

print(player.last_three_played_song_titles("alice"))  # ["Song B", "Song D", "Song C"]
Common Mistakes
Ignoring Replay: Forgetting to move an old song to the front if played again.
Counting Errors: Keeping more than 3 songs or removing the wrong one.
New Users: Forgetting to create an empty list for a new user.
Solution for Part 2
The interviewer said "only 3 items." We do not need a complex cache. A simple list is fine.

class MusicPlayer:
    def __init__(self):
        self.next_song_id = 1
        self.songs = {}              # song_id -> song_title
        self.song_order = []         # Insertion order
        self.song_listeners = {}     # song_id -> set of user_ids
        self.user_history = {}       # user_id -> list of last 3 song_ids

    def add_song(self, song_title: str) -> int:
        """Time: O(1)"""
        song_id = self.next_song_id
        self.next_song_id += 1

        self.songs[song_id] = song_title
        self.song_order.append(song_id)
        self.song_listeners[song_id] = set()

        return song_id

    def play_song(self, song_id: int, user_id: str) -> None:
        """Time: O(1) - List operations are O(3) which counts as O(1)."""
        if song_id not in self.songs:
            return

        # Track unique listeners (Part 1)
        self.song_listeners[song_id].add(user_id)

        # Update user history (Part 2)
        if user_id not in self.user_history:
            self.user_history[user_id] = []

        history = self.user_history[user_id]

        # Remove song if it's already there (so we can add it to the front)
        if song_id in history:
            history.remove(song_id)  # O(3) = O(1)

        # Add to front
        history.insert(0, song_id)

        # Keep only 3 items
        if len(history) > 3:
            history.pop()

    def print_analytics_summary(self) -> None:
        """Time: O(S)"""
        for song_id in self.song_order:
            title = self.songs[song_id]
            count = len(self.song_listeners[song_id])
            print(f"{title}: {count} unique listener{'s' if count != 1 else ''}")

    def last_three_played_song_titles(self, user_id: str) -> list[str]:
        """Time: O(1)"""
        if user_id not in self.user_history:
            return []

        return [self.songs[song_id] for song_id in self.user_history[user_id]]
Why we don't use LRU Cache
Note: A full LRU Cache uses a Doubly-Linked List and a HashMap. That is overkill here.

Removing an item from a list of size 3 takes constant time O(1).
Adding an item to the front takes constant time O(1).
Simple lists are faster and easier to write when the size is very small.

Performance Summary:

| Method | Time | Space | | --- | --- | --- | | play_song | O(1) | O(1) per play | | last_three_played_song_titles | O(1) | O(1) |

Part 3: Top Songs Analysis
New Requirement
Interviewer: "We need to show the top K songs based on unique listeners. Make it faster than sorting the whole list (O(N log N))."

Add this method:

def print_top_k_analytics_summary(self, k: int) -> None:
    """
    Print the top K songs by unique listener count.

    Args:
        k: Number of songs to show

    Order: By listener count (high to low). If there is a tie, use song_id.
    Requirement: Faster than O(N log N).
    """
    pass
How it Works
player = MusicPlayer()

# Add songs
titles = ["Shape of You", "Blinding Lights", "Dance Monkey", "Someone Like You", "Bad Guy"]
for t in titles: player.add_song(t)

# Plays happen here...
# "Someone Like You" gets 4 listeners
# "Shape of You" gets 3 listeners
# "Dance Monkey" gets 2 listeners

# Get Top 3
player.print_top_k_analytics_summary(3)
Result
Someone Like You: 4 unique listeners
Shape of You: 3 unique listeners
Dance Monkey: 2 unique listeners
Solution for Part 3: Using a Min-Heap
The trick is to use a Min-Heap of size K. This is faster than sorting all N songs.

import heapq

class MusicPlayer:
    # ... previous init and methods ...

    def print_top_k_analytics_summary(self, k: int) -> None:
        """Time: O(N log K) using a min-heap."""
        if k <= 0:
            return

        # Min-heap stores tuples: (listener_count, -song_id, song_id)
        # We keep the heap size at K.
        # If the heap is full, we remove the smallest item (lowest count).
        min_heap = []

        for song_id in self.song_order:
            count = len(self.song_listeners[song_id])
            
            # Use -song_id for tie-breaking.
            # Python compares tuples item by item.
            entry = (count, -song_id, song_id)

            if len(min_heap) < k:
                heapq.heappush(min_heap, entry)
            elif entry > min_heap[0]:  # If current song is better than the worst in heap
                heapq.heapreplace(min_heap, entry)

        # The heap stores items with the smallest priority first.
        # We pop them out and reverse the list to get Highest -> Lowest.
        results = []
        while min_heap:
            count, neg_song_id, song_id = heapq.heappop(min_heap)
            results.append((song_id, count))

        results.reverse()

        # Print results
        for song_id, count in results:
            title = self.songs[song_id]
            print(f"{title}: {count} unique listener{'s' if count != 1 else ''}")
How the Heap Works
We store a tuple: (count, -song_id, song_id).

A Min-Heap removes the smallest item.
We want to keep high listener counts, so we remove low counts.
If counts are equal, we look at -song_id.
Easier Way: heapq.nlargest
Python has a built-in function that does exactly this.

def print_top_k_analytics_summary(self, k: int) -> None:
    """Time: O(N log K) using heapq.nlargest."""
    if k <= 0:
        return

    # Create a list of stats for all songs
    song_stats = [
        (len(self.song_listeners[sid]), -sid, sid)
        for sid in self.song_order
    ]

    # Get the top K largest items
    top_k = heapq.nlargest(k, song_stats)

    for count, neg_song_id, song_id in top_k:
        title = self.songs[song_id]
        print(f"{title}: {count} unique listener{'s' if count != 1 else ''}")
Performance Summary:

| Approach | Time | Space | | --- | --- | --- | | Sorting everything | O(N log N) | O(N) | | Min-heap (Size K) | O(N log K) | O(K) | | heapq.nlargest | O(N log K) | O(K) |

Full Code
import heapq

class MusicPlayer:
    def __init__(self):
        self.next_song_id = 1
        self.songs = {}              # song_id -> song_title
        self.song_order = []         # Insertion order
        self.song_listeners = {}     # song_id -> set of user_ids
        self.user_history = {}       # user_id -> list of last 3 song_ids

    # ===== Part 1 =====
    def add_song(self, song_title: str) -> int:
        """Time: O(1)"""
        song_id = self.next_song_id
        self.next_song_id += 1
        self.songs[song_id] = song_title
        self.song_order.append(song_id)
        self.song_listeners[song_id] = set()
        return song_id

    def play_song(self, song_id: int, user_id: str) -> None:
        """Time: O(1)"""
        if song_id not in self.songs:
            return

        # Part 1: Track unique listeners
        self.song_listeners[song_id].add(user_id)

        # Part 2: Update user history (Limit 3)
        if user_id not in self.user_history:
            self.user_history[user_id] = []

        history = self.user_history[user_id]
        if song_id in history:
            history.remove(song_id)
        history.insert(0, song_id)
        if len(history) > 3:
            history.pop()

    def print_analytics_summary(self) -> None:
        """Time: O(S) where S = number of songs"""
        for song_id in self.song_order:
            title = self.songs[song_id]
            count = len(self.song_listeners[song_id])
            print(f"{title}: {count} unique listener{'s' if count != 1 else ''}")

    # ===== Part 2 =====
    def last_three_played_song_titles(self, user_id: str) -> list[str]:
        """Time: O(1)"""
        if user_id not in self.user_history:
            return []
        return [self.songs[song_id] for song_id in self.user_history[user_id]]

    # ===== Part 3 =====
    def print_top_k_analytics_summary(self, k: int) -> None:
        """Time: O(N log K) where N = number of songs"""
        if k <= 0:
            return

        song_stats = [
            (len(self.song_listeners[sid]), -sid, sid)
            for sid in self.song_order
        ]

        top_k = heapq.nlargest(k, song_stats)

        for count, neg_song_id, song_id in top_k:
            title = self.songs[song_id]
            print(f"{title}: {count} unique listener{'s' if count != 1 else ''}")
Questions the Interviewer Might Ask
Time Complexity: Be ready to explain why play_song is O(1) and why the heap approach is O(N log K).
Space: What if the history limit was 1,000 songs instead of 3? (Answer: You would need a real LRU Cache with a Doubly-Linked List).
Concurrency: How would you handle two people playing songs at the exact same time? (Answer: You need locks or thread-safe data structures).
Extensions:
Time-Based: "Get unique listeners in the last 24 hours." (Answer: Store timestamps).
Leaderboard: "Update the top K list instantly after every play." (Answer: Use a balanced tree or skip list).
Performance Summary
| Method | Time | Space | | --- | --- | --- | | add_song | O(1) | O(1) per song | | play_song | O(1) | O(1) per play | | print_analytics_summary | O(S) | O(1) | | last_three_played_song_titles | O(1) | O(1) | | print_top_k_analytics_summary | O(S log K) | O(K) |

S = number of songs, K = number of top songs wanted