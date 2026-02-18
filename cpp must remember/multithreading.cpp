mutex: a "SYNCHORNIZATION" object
     does not know which thread has locked it
     locks part of code 
     has lock, unlock method

always do unique lock on mutex, as it guarantees to call unlock if object destroyes
or scope ends..
std::unique_lock<std::mutex> lk(mtxQueue_) 

**use condition_variable to stop busy waiting..cv.notify_one() to notify