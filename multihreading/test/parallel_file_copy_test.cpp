#include<iostream>
#include<thread>
#include <fcntl.h> 
#include <unistd.h>
#include<sys/stat.h>
#include<atomic>

using namespace std;
const size_t CHUNKSIZE = 1024;
vector<vector<size_t>> chunks;

class ParallelFileCopier {
    public:
    explicit ParallelFileCopier (int _numworkers, int _srcFd, int _dstFd) {
        numworkers = _numworkers;
        srcFd = _srcFd;
        dstFd = _dstFd;
        for(auto i=0;i<numworkers;i++){
            workers.emplace_back(&ParallelFileCopier::copyChunk,this,i);
        }
    }

    int getResult(){
        for(auto &th : workers ) {
            if(th.joinable()) th.join();
        }
        return failed.load();
    }

    private:
    void copyChunk(int idx){
        int curidx = idx;
        while (curidx < (int)chunks.size())
        {
            if(failed.load()) return;
            auto curChunk = chunks[curidx];
            vector<char> buf(curChunk[1]);
            ssize_t readLen = pread(srcFd,buf.data(),curChunk[1],curChunk[0]);
            if(readLen < 0 || (size_t)readLen != curChunk[1]) {
                failed.store(1);
                cout<<"Failed to read offset: "<<curChunk[0] <<" length : "<<curChunk[1]<<endl;
                return;
            }
            ssize_t writeLen = pwrite(dstFd,buf.data(),readLen,curChunk[0]);
            if(writeLen < 0 || writeLen != readLen) {
                cout<<"Failed to write offset: "<<curChunk[0] <<" length : "<<curChunk[1]<<endl;
                failed.store(1);
                return;
            }
            curidx+=numworkers;
        }
    }
    int numworkers, srcFd, dstFd;
    atomic<int> failed{0};
    vector<thread> workers;
};

off_t getFileSize(int fd) {
    struct stat st;
    if(fstat(fd,&st) < 0) return -1;
    return st.st_size;
}


void copyFile(const string& srcfile, const string& dstFile, int numTh){
    int fdSrc = open(srcfile.c_str(),O_RDONLY);
    if(fdSrc < 0) {
        cout<<"srcfile does not exist";
        return;
    }
    off_t size = getFileSize(fdSrc);
    if(size  <=0) {
        close(fdSrc);
        return;
    }

    int fdDst = open(dstFile.c_str(),O_WRONLY|O_TRUNC|O_CREAT, 0777);
    if(fdDst < 0) {
        cout<<"dst could not be created";
        return;
    }
    ftruncate(fdDst,size);

    chunks.clear();
    size_t numChunks = size/CHUNKSIZE + (size%CHUNKSIZE !=0);
    for(size_t i = 0, offset = 0; i<numChunks; i++){
        size_t cursize = min(CHUNKSIZE, (size_t) size - offset);
        chunks.push_back({offset, cursize});
        offset += cursize;
    }
    ParallelFileCopier pfc(numTh,fdSrc,fdDst);
    int res = pfc.getResult();
    close(fdSrc);
    close(fdDst);
    if(res) cout<<"failed to copy file"<<endl;
    else cout<<"successfully copied file"<<endl;
}
void createFile(const string& filename, size_t size = 1024 * 1024){
    int fd = open(filename.c_str(),O_WRONLY|O_CREAT|O_TRUNC, 0644);
    vector<char> data(size);
    for(auto i=0;i<size;i++){
        data[i] = rand()%26+'a';
    }
    write(fd,data.data(),size);
    close(fd);
    cout<<"created file: "<<filename<<" of size "<<size<<endl;
}

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

int main() {
    const string srcFile = "source_file.dat";
    const string dstFile = "dest_file.dat";
    createFile(srcFile);
    copyFile(srcFile,dstFile,4);
    verify(srcFile, dstFile);
    return 0;
}