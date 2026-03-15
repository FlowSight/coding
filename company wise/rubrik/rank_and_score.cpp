// The thing with such games is there are a lot of players playing in parallel and the scores are getting updated each second. Basically the rank list is changing very quickly. Now, we have to come up with a data structure which can efficiently handle such a rank list. Assume that the score of each player is distinct at any given point and players are identified by their unique ids. Expected operations:

// We should be able to quickly get the RANK(not score) of any given player(so that we can display it to him and update it every 1 second or so). Technically, given any player id, give me his rank in O(1) or O(log N) time.

// We should be able to know the player with any given rank so that we can display ranks on the dashboard. Technically, given any rank, give me the player with that rank at that point of time in O(1) or O(log N) time.

// Editing/Updating score of a player - most important operation for us. Technically, given any player id and his score to update, update his score(which should be reflected in ranks of other people) in O(1) or O(log N) time.

// Adding and deleting players(we obviously add both player ids and his score(initialized to zero) in O(1) or O(log N) time.