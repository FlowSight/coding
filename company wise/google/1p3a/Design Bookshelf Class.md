Design a Bookshelf class that supports adding, moving, and removing books. Implement the following methods:

add_book(title: str): Add a book with the given title.
remove_book(title: str): Remove a book with the given title. Do nothing if the book does not exist.
move_book(title: str, position: int): Move the book with the given title to the specified position. Do nothing if the book does not exist.
Assume the Bookshelf is initially empty and all books are stored in the order they are added. Provide at least three test cases after implementation.

Test Cases:
Initialize an empty bookshelf
Add books "A", "B", "C", then remove "B", and verify the order.
Add books "A", "B", "C", then move "A" to position 2, and verify the order.
The book titles are unique.