Three kinds of threads share access to a singly-linked list:
searchers, inserters and deleters. 
- Searchers merely examine the list;
hence they can execute concurrently with each other. 
- Inserters add new items to the end of the list; 
insertions must be mutually ex-clusive to preclude two inserters
 from inserting new items at about the same time.
 However, one insert can proceed in parallel with
any number of searches. 
- Finally, deleters remove items from any-where in the list.
 At most one deleter process can access the list at
a time, and deletion must also be mutually exclusive with searches and insertions.


search
shared lock on mtxlist
ll

insert
shared lock on mtxlist
ll

delete
lock on mtxlist
ll

mutex mtxlist