# Rubrik — Onsite Coding Round
**Date**: April 15, 2025  
**Role**: SSE  
**Interviewer**: Ashutosh Soni  
**Duration**: 50 min  
**Status**: Waiting for decision  
**Confidence**: 9/10

---

## Problem: Reader-Writer Lock

Implement `read()` and `write()` with standard reader-writer semantics:
- Multiple readers can access the critical section concurrently
- Only one writer can access the critical section — no other readers or writers allowed

### Base Solution
- 1 mutex, 1 condition_variable, 1 `isWriter` bool
- Readers: wait until `isWriter == false`, increment reader count, proceed
- Writers: wait until `isWriter == false && numReaders == 0`, set `isWriter = true`
- No hints needed

---

## Follow-up 1: Writer-priority drain

> If a write comes in while readers are active, make the readers drain first, then acknowledge the writer. After the write completes, flip back to allowing reads.

**Approach**: Added a `writerWaiting` bool.  
- When a writer arrives, set `writerWaiting = true` → new readers block
- Existing readers finish and drain out
- Once `numReaders == 0`, writer proceeds
- After writer finishes, reset `writerWaiting` → readers can enter again

---

## Follow-up 2: Batch writer-priority queue

> If multiple writes arrive, acknowledge **all** pending writes in batch (writer-prioritized queue). i.e., once a writer is waiting, queue up all subsequent writers and process them all before letting readers back in.

**Approach**: Changed `writerWaiting` from `bool` → `atomic<int>` (count of waiting writers).  
- Each arriving writer increments `writerWaiting`
- Readers block as long as `writerWaiting > 0`
- Writers execute one at a time, each decrementing `writerWaiting` on completion
- Only when `writerWaiting == 0` do readers get unblocked

---

## How It Went
- Very collaborative interviewer
- No hints needed — coded all three versions
- Finished with time to spare; interviewer said no more questions
- Clean round overall

---

## Related Code in Repo
- [basic reader_writer_lock](../../../company%20wise/rubrik/basic%20reader_writer_lock/test.cpp)
- [playground access](../../../company%20wise/rubrik/playground%20access/test.cpp)
