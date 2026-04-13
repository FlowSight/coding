/*
Given a source of data and a sink of data, you need to create an effective data transfer solution  which will take data from the source and write it to the sink. 

There are some considerations to take into account:
1. The reads are very fast as compared to the writes to the destination. 
2. You can only have one reader reading data from the source.
3. You can use multiple writers to write data to the destination.
4. The data to be read is a continuous stream of bytes with delimiters (\n) placed randomly in between. The data between two delimiters is called a row.

5. The writes to the destination should contain complete rows . This means that all the writes to the destination should contain complete rows. The order of the rows doesn’t matter.

6. Every writer must write a header to the destination first and end with a footer. You can refer to the example below to see what a logically complete write looks like. Each writer establishes an independent session and the ordering across them is not required.

Example with 1 writer:
Input file:ROW1\nROW2\nROW3\nROW4\n

Output:
-------------HEADER----------------
ROW1\nROW2\nROW3\nROW4\n
-------------FOOTER----------------

Example with 2 writers
Input: ROW1\nROW2\nROW3\nROW4\nROW5\nROW6\nROW7\nROW8\n

WRITER 1:
-------------HEADER----------------
ROW1\nROW4\nROW5\nROW7\n
-------------FOOTER----------------
Writer 2:
-------------HEADER----------------
ROW2\nROW3\nROW6\nROW8\n
-------------FOOTER----------------

7. Assume the file contains atleast one newline character (on row).


8. Interfaces provided
a. In order to read from the source, you can use the API below, assuming that file open/close is already handled and you don’t need to implement it:
ReadData(offset int64, size int64, file *File) ([]byte, error)

b. In order to write data to the sink, you can use the API below (You can assume the initialisation and closure is handled):
WriteData([]byte) (int64, error)

c. In order to fetch the header, you can use the API below:
GetHeader() ([]byte)
d. In order to fetch the footer, you can use the API below:
GetFooter() ([]byte)
Feel free to request any additional APIs is required.
*/