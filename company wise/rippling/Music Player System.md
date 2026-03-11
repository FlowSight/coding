Design a music player system with the following functionalities:

Part I
add_song(song_title): Allows users to add a song, with the song's title as the parameter.

play_song(song_ID, user_ID): Users can play a specific song. Parameters are the song ID and user ID.

print_analytics_summary(): Prints the usage analytics summary of all users and songs.

Part II
last_three_played_song_titles(user_ID): Returns the last three played song titles for a specified user.
Part III
print_top_k_analytics_summary(): Print the top K most played songs, requiring an algorithm with better complexity than O(nlogn).
Implement the code logic for each function, ensuring they can be tested with a set of inputs and outputs.

Example
Input
add_song(Song 1); add_song(Song 2); play_song(0,user1); play_song(1,user1); print_analytics_summary(); last_three_played_song_titles(user1); print_top_k_analytics_summary(1)