Given a root directory, implement a program to print the directory tree in the following format:

dir
  subdir1
    file1.ext
    subsubdir1
  subdir2
    subsubdir2
      file2.ext
Requirements:

Handle arbitrary depth of nesting.
Only print the directory structure; no need to read from actual filesystem.
Assume the input data is correctly formatted with directories and files.
Input: A multi-line string representing the directory structure, where each line is a directory or file, with levels indicated by tabs.

Output: Print the directory tree in the specified format.

Example
Input
dir
	subdir1
		file1.ext
		subsubdir1
	subdir2
		subsubdir2
			file2.ext