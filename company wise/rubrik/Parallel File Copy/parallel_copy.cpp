
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <fcntl.h>      // open()
#include <unistd.h>     // pread(), pwrite(), close(), ftruncate()
#include <sys/stat.h>   // fstat()

using namespace std;

const int NUM_THREADS = 4;
const size_t CHUNK_SIZE = 4096;   // 4KB per chunk

// ─── Get file size ───
off_t getFileSize(int fd) {
    struct stat st;
    if (fstat(fd, &st) < 0) return -1;
    return st.st_size;
}

void copyChunk(int srcFd, int dstFd, off_t offset, size_t len) {
    vector<char> buf(len);

    // Read chunk from source
    ssize_t bytesRead = pread(srcFd, buf.data(), len, offset);
    if (bytesRead < 0) {
        cerr << "pread failed at offset " << offset << ": " << strerror(errno) << "\n";
        return;
    }

    // Write chunk to destination
    ssize_t bytesWritten = pwrite(dstFd, buf.data(), bytesRead, offset);
    if (bytesWritten < 0) {
        cerr << "pwrite failed at offset " << offset << ": " << strerror(errno) << "\n";
        return;
    }

    // Handle partial writes (rare but possible)
    while (bytesWritten < bytesRead) {
        ssize_t n = pwrite(dstFd, buf.data() + bytesWritten,
                           bytesRead - bytesWritten,
                           offset + bytesWritten);
        if (n < 0) {
            cerr << "pwrite retry failed: " << strerror(errno) << "\n";
            return;
        }
        bytesWritten += n;
    }
}

// ─── Main copy function ───
int copy(const string& dst, const string& src) {
    // Open source (read-only)
    int srcFd = open(src.c_str(), O_RDONLY);
    if (srcFd < 0) {
        cerr << "Cannot open source: " << strerror(errno) << "\n";
        return -1;
    }

    // Get file size
    off_t fileSize = getFileSize(srcFd);
    if (fileSize < 0) {
        cerr << "Cannot get file size\n";
        close(srcFd);
        return -1;
    }

    // Open/create destination (write, create, truncate)
    int dstFd = open(dst.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dstFd < 0) {
        cerr << "Cannot open destination: " << strerror(errno) << "\n";
        close(srcFd);
        return -1;
    }

    // Pre-allocate destination file to the correct size
    // (so parallel pwrite at any offset works)
    ftruncate(dstFd, fileSize);

    size_t numChunks = (fileSize + CHUNK_SIZE - 1) / CHUNK_SIZE;

    vector<thread> threads;

    for (int t = 0; t < NUM_THREADS; t++) {
        threads.emplace_back([=] {
            for (size_t c = t; c < numChunks; c += NUM_THREADS) {
                off_t offset = c * CHUNK_SIZE;
                size_t len = min((size_t)CHUNK_SIZE, (size_t)(fileSize - offset));
                copyChunk(srcFd, dstFd, offset, len);
            }
        });
    }

    // Wait for all threads
    for (auto& th : threads) th.join();

    // Close files
    close(srcFd);
    close(dstFd);

    cout << "Copied " << fileSize << " bytes (" << numChunks
         << " chunks, " << NUM_THREADS << " threads)\n";
    return 0;
}

// ─── Create a test source file ───
void createTestFile(const string& path, size_t totalSize) {
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    vector<char> data(totalSize);
    for (size_t i = 0; i < totalSize; i++) {
        data[i] = 'A' + (i % 26);   // repeating A-Z pattern
    }
    write(fd, data.data(), totalSize);
    close(fd);
    cout << "Created source file: " << totalSize << " bytes\n";
}

// ─── Verify: compare two files byte-by-byte ───
bool verify(const string& file1, const string& file2) {
    int fd1 = open(file1.c_str(), O_RDONLY);
    int fd2 = open(file2.c_str(), O_RDONLY);

    off_t size1 = getFileSize(fd1);
    off_t size2 = getFileSize(fd2);

    if (size1 != size2) {
        cerr << "FAIL: size mismatch! " << size1 << " vs " << size2 << "\n";
        close(fd1);
        close(fd2);
        return false;
    }

    vector<char> buf1(size1), buf2(size2);
    read(fd1, buf1.data(), size1);
    read(fd2, buf2.data(), size2);

    close(fd1);
    close(fd2);

    if (buf1 == buf2) {
        cout << "PASS: files are identical!\n";
        return true;
    }
    cerr << "FAIL: content mismatch!\n";
    return false;
}

// ─── Test ───
int main() {
    const string srcFile = "test_source.dat";
    const string dstFile = "test_dest.dat";

    createTestFile(srcFile, 1024 * 1024);  // 1MB

    if (copy(dstFile, srcFile) != 0) {
        cerr << "Copy failed!\n";
        return 1;
    }

    verify(srcFile, dstFile);

    // Cleanup
    unlink(srcFile.c_str());
    unlink(dstFile.c_str());

    return 0;
}
