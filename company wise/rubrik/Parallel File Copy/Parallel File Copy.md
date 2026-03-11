<!-- Given low-level APIs:
pread(buffer, size, file)
pwrite(buffer, size, file)
Task: Copy data from one file to another in parallel using multiple threads. Had to design chunking, coordination, and thread safety manually.


Given:
// open a file descriptor for a named file
open(name string) (fd int, err error)

// pread will read len(buf) bytes, returning the number of bytes read
// if a read would exceed the end of a file, pread will return EOF
pread(int fd, buf []byte, offset int64) (int, error)  //int -> how many actual bytes were read.
                                                  	// any error occured.
                                                  	//in our case -> only int works (-ve -> error)

// pwrite will write len(buf) bytes to a file, returning an error if not all
// bytes could be successfully written
pwrite(int fd, buf []byte, offset int64) error // filled buffer of data

// close a file, flushing any outstanding writes
close(fd int) error


Please Implement:

// copy the contents of file src to file dst.
copy(dst string, src string) error -->