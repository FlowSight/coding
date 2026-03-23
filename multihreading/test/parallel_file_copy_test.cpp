#include <iostream>
#include <thread>
#include <vector>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>


using namespace std;

class FileManager {
    public:
    explicit FileManager() = default;
    explicit FileManager(int _copierthcnt) {
        copierthcnt = _copierthcnt;
        for(auto i=0;i<_copierthcnt;i++)workers.emplace_back(&FileManager::copychunk,this);
    }
    int create(string path, size_t size, bool writecontent = true){
        int fd = open(path.c_str() ,O_CREAT | O_RDWR | O_TRUNC ,0644);
        if(fd<0) {
            throw runtime_error("file create failed");
        }
        ftruncate(fd,size);
        if(writecontent){
            vector<char> arr(size);
            for(auto i=0;i<size;i++)arr[i] = (rand()%26+'a');
            write(fd,&arr,size);
        }

        return fd;
    }

    void copy(int __srcfd, int _dstfd) {
        srcfd = __srcfd;
        dstfd = _dstfd;
        size_t size = getFileSize(srcfd);
        size_t offset = 0;
        {
            unique_lock<mutex> ul(mtxchunks);
            while(offset < size){
                size_t curchunk = min(chunksize,size-offset);
                chunks.push({offset,curchunk});
                cout<<srcfd <<" "<<dstfd<<" "<< offset<<" "<<curchunk<<endl;
                offset += curchunk;
            }
            cout<<"chunked"<<endl;
            cvchunks.notify_all();
         }

    }
    void stop(){
        stopped = true;
        cvchunks.notify_all();
        for(auto &th : workers){
            if(th.joinable()) th.join();
        }
    }
    
    bool verify(int srcfd, int dstfd){
        size_t szsrc = getFileSize(srcfd), szdst = getFileSize(dstfd);
        if(szdst != szsrc) return false;
        vector<char> arr(szsrc), arrdst(szsrc);
        pread(srcfd,arr.data(),szsrc,0);
        pread(srcfd,arrdst.data(),szsrc,0);
        for(auto i=0;i<szsrc;i++){
            if(arr[i] != arrdst[i]) return false;
        }
        return true;
    }



    private:

    void copychunk(){
        vector<size_t> chunk;
        while(true){
            {       
                unique_lock<mutex> ul(mtxchunks);
                cvchunks.wait(ul,[this]{
                    return  stopped || !chunks.empty();
                });
                if(stopped) return;
                chunk = move(chunks.front());
                chunks.pop();
                cout<<"picked chunk "<<chunk[0]<<" "<<chunk[1]<<endl;
                cvchunks.notify_all();
            }
            copychunkhelper(srcfd,dstfd,chunk[0],chunk[1]);
        }
    }

    void copychunkhelper(int srcfd, int dstfd, off_t offset, size_t len){
        vector<char> buf(len);
        size_t sz =  pread(srcfd,buf.data(),len,offset);
        if((sz <0 )|| (sz<len)){
            throw runtime_error("file copy read failed at offset : "+to_string(offset));
        }
        sz =  pwrite(dstfd,buf.data(),len,offset);
        if(sz < len){
             throw runtime_error("file copy write  failed at offset : "+to_string(offset));
        }
        copied += len;
        cout<<"file copy done at offset :"<<offset<<" len: "<<copied<<endl;
    }
    int copierthcnt;
    size_t chunksize = 1024*2;
    size_t getFileSize(int fd){
        struct stat st;
        if(fstat(fd,&st) < 0) return -1;
        return st.st_size;
    }
    queue<vector<size_t>> chunks;
    mutex mtxchunks;
    condition_variable cvchunks;
    int srcfd, dstfd;
    atomic<bool> stopped{false};
    atomic<int> copied;

    vector<thread> workers;

};


void testmethod(){
    string srcfile = "./source_file.dat" ,
        dstfile = "./dst_file.dat";
    size_t size = 1024*1024;

    FileManager fm(3);
    int srcfd = fm.create(srcfile,size); // create + write
    int dstfd = fm.create(dstfile,size,false); 
    fm.copy(srcfd,dstfd);
    this_thread::sleep_for(chrono::milliseconds(10000));
    fm.stop();
    cout<<fm.verify(srcfd,dstfd)<<endl;
}

int main(){
    testmethod();
    return 0;
}