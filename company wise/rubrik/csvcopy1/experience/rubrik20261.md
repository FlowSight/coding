1. interviewer pasted this qs
2. i got confused while reading, why write has header and footer?
3. I asked about writes getting mixed up, he said its thread safe, mix up wont happen
4. i forgot to ask about read thread safety
5. he pointed me ; canyou relate it to a known problem, i said reader writer
6. he said yes, but here how many reader -writer? i said many-many. I dont remember his response to that.
7. I said each reader can read, dump to queue, each writer can pull from queue and write ( i missed asking is ordering needs to be maintained after copying)
8. i also said, each writer can have their own queue. he said whats the downside? I could not figure out fast. he said, if one row is too big, then one writer is skewed. 
9. i said we can chunk it, read in chunks, push into queue in chunks
10. he said ok, lets code it
11. i coded assuming read is possible in chunks, without worrying about row ending/beginning etc. i wrote the writer logic correctly IIRC.
12. later he said can you walk me through it, i did.he said exit condiion is wrong, i fixed it.