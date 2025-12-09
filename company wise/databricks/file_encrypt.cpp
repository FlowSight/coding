// Given a directory, implement a method that returns the count of encrypted and unencrypted files under the input directory.
// FOLLOW-UP:

// There are two external APIs provided:

// EncryptFile(filePath) encrypts a file
// EncryptDirectoy(directoryPath) encrypts every file under that directory recursively.
// Let's say, requestTime is the time taken to make a request and fileEncryptTime is time taken to encrypt a file. So, total time to encrypt a file is essentially, requestTime + fileEncryptTime.

// N = number of files (both unencrypted and encrypted)
// So, total time to encrypt a directory is requestTime + N * fileEncryptTime.

// Implement GetMinimumEncryptTime(requestTime, fileEncryptTime) which gives the least amount of time needed to encrypt all files in a directory.

// Example:

// /
// -- dir1
// ------ file1 => True
// ------ file2 => False
// -- dir2
// ------ file1 => False
// ------ file2 => True
// Test 1: requestTime = 3, fileEncryptTime = 1
// Encrypting directory here is cheap.
// - encrypt("/") => requestTime + (4 x fileEncryptTime) = 7
// - total = 7

// Test 2: requestTime = 2, fileEncryptTime = 2
// Encrypting files here is cheap
// - encrypt("/dir1/file2") => requestTime + (1 x fileEncryptTime) = 4
// - encrypt("/dir2/file1") => requestTime + (1 x fileEncryptTime) = 4
// - total = 8

// encrypt("/") would have been costlier for Test 2, i.e. 2 + (2 * 4) = 10