Design a music player's scheduling strategy.

The system continuously receives new user records {userId, songs[]}.

The player must decide the next song to play under these rules:

Always prefer the globally most frequent song.
Within the same round, once a song has been played, it cannot be played again.
A new round can start only after every song that has appeared so far has been played at least once in the current round; once a new round starts, all songs become playable again.
Implement a data structure/class with operations (you may add necessary APIs):

addUserSongs(userId, songs[]): add a user and update global song frequencies.
nextSong() -> songId: return the next song to play and mark it as played in the current round.
Notes:

Songs are identified by integer songId.
Frequency is the total number of occurrences of songId across all added users' song lists.
If nextSong() is called when no songs exist, you may return null or throw.
If multiple songs tie in frequency, you may define a deterministic tie-breaker (e.g., smaller songId first).
Provide time/space complexity.
Suggested constraints:

Up to 2e5 total operations
Up to 2e5 distinct songIds
Example
Input
add 1 3
1 10 20 20
next
next
next
next
Output
20
10
(空/异常)
20