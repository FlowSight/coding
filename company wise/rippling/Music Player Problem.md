Design and implement a basic music player application. The player should support the following features:

Play and pause music.
Skip to the next or previous song.
Play a specific song based on the input song ID.
Input:

Initialize the player with a list of songs, each with a unique ID and song name.
Implement the following methods:

play(): Play the current song.
pause(): Pause the currently playing song.
next_song(): Skip to the next song.
previous_song(): Return to the previous song.
play_song(song_id): Play a specific song based on the given song ID.
Example:

# Initialize the player
player = MusicPlayer([{ 'id': 1, 'name': 'Song A' }, { 'id': 2, 'name': 'Song B' }, { 'id': 3, 'name': 'Song C' }])

# Play the music
player.play()  # Playing Song A

# Skip to the next song
player.next_song()  # Playing Song B

# Pause the music
player.pause()  # Paused Song B

# Play a specific song
player.play_song(3)  # Playing Song C
Example
Input
player = MusicPlayer([{ 'id': 1, 'name': 'Song A' },{ 'id': 2, 'name': 'Song B' },{ 'id': 3, 'name': 'Song C' }]); player.play(); player.next_song(); player.pause(); player.play_song(3)