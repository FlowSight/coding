Implement a Trie (Prefix Tree) with two methods: \n\n1. void addWord(String word): Adds a word to the Trie. \n2. boolean search(String word): Searches the Trie for a word that matches with the given string where '.' can match any character. \n\nThese operations should be efficiently supported.\n\nThe number of words provided is up to 10^5, and each word's length is up to 100.\n\nExample:\n\n\naddWord('bad')\naddWord('dad')\naddWord('mad')\nsearch('pad') -> false\nsearch('bad') -> true\nsearch('.ad') -> true\nsearch('b..') -> true\n

Example
Input
{'operations': ['addWord', 'addWord', 'addWord', 'search', 'search', 'search', 'search'], 'args': [['bad'], ['dad'], ['mad'], ['pad'], ['bad'], ['.ad'], ['b..']]}