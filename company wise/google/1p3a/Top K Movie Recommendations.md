The problem is about recommending the top K movies. Assume you have a database of movies with ratings and user preferences. Write an algorithm to recommend the top K suitable movies, optimizing for performance with BFS and heaps.

Input:

A list of movie ratings, each containing a movie ID, rating, and genre.
A list of user-preferred genres.
An integer K indicating the number of movies to return.
Output:

A list containing only the top K recommended movie IDs.
Constraints:

If multiple movies have the same rating, any order of return is fine.
The dataset may contain up to 10^6 movies.
Test case:

recommend_movies([{'id': 1, 'rating': 9.0, 'genre': 'action'}, {'id': 2, 'rating': 8.5, 'genre': 'action'}, {'id': 3, 'rating': 8.5, 'genre': 'comedy'}], ['action', 'comedy'], 2)
# Output: [1, 2] or [2, 1]
Example
Input
[{'id': 1, 'rating': 9.0, 'genre': 'action'}, {'id': 2, 'rating': 8.5, 'genre': 'action'}, {'id': 3, 'rating': 8.5, 'genre': 'comedy'}]
['action', 'comedy']
2