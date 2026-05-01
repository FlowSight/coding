Given a JSON input with a list of strings, e.g.,
    {
        'text': 'first word',
        'text': 'my second sentence',        
        'text': 'now it's third',
    }
, the task is to print it out in this format (the formatting is a bit messed up, but you can get the gist; the left and right spacing is based on the longest string)
: +-----------------------+
|first word |
+-----------------------+
|my second sentence|
+-----------------------+
|now it's third |
+-----------------------+
After a brief discussion with the interviewer, I solved it instantly.
Then the guy gave a follow-up, saying to add a width parameter to the input JSON, requiring the left and right spacing to be based on that width, with left indentation. The printout would look something like this:
+----------------+
|first word |
+----------------+
|my second |
|sentence |
+----------------+
|now it's third |
+----------------+

That was great!
Then the guy exclaimed, "Oh my god!" But there was another follow-up. This time you don't need to write code, just briefly explain your idea: the input JSON is a list of lists, with first-level lists representing a row, and second-level lists representing a column within each row. Each column has a specified width (equivalent to each string having its own width). The printout would look something like this:
+--------------+----------+
|first word |my |
| |second |
| |sentence|
+--------------+----------+
|now it's third |
+--------------------------+
