mutex: a "SYNCHORNIZATION" object
     does not know which thread has locked it
     locks part of code 
     has lock, unlock method

always do unique lock on mutex, as it guarantees to call unlock if object destroyes
or scope ends..
std::unique_lock<std::mutex> lk(mtxQueue_) 
- std::lock_guard will be locked only once on construction and unlocked on destruction.
- In contrast to std::lock_guard, std::unique_lock can be:
  + created without immediately locking : unique_lock<mutex> lk(mtx, defer_lock);
  + unlocked at any point in its existence.

**use condition_variable to stop busy waiting..cv.notify_one() to notify

thread always should be moved when accessing, or access with & (if not removed later)


if (false == mut.try_lock()) {
        return; // non blocking mutex
}

notify_all when a task incoming : is correct but wasteful, all other threads will
wake up -> see no work availble -> sleep again

cv.wait(ul,..) rekeases the lock while sleeping/waiting
barrier is multi use, latch is one time 
barrier : all theead wait at arrive_and_wait, latch : threads decrease and leave
