system Design
This interview was highly structured. The interviewer began talking a lot, and I started asking questions about what he was saying. He got a little confused or frustrated, and then he told me he will just paste the question. His English was also pretty bad.

Create a group chat
Create an inbox, load the top 10 group chats that have the most recent messages for the user
Send a message to the group chat
Show messages of a group chat
I asked a lot of questions like:

do we need to delete chats for users if they request account deletion?
Do we need to consider security or admin tooling for the chat
He told me not to worry about any of that and just answer the 4 questions.

He was very interested in my data schema.
Cassandra and similar databases are just a waste. You don't need the write throughput.

The main question is SQL vs Non-Relational. He said the traffic is about 1 million group chats per year, assume 20 messages per group chat. That's 5500 messages / day, which is 228 messages / hour.

SQL can definitely handle that. BUT you don't need the strong consistency. It's probably to have high availability and easier horizontal scalability, so I went with DynamoDB.

My interviewer had ABSOLUTELY NO IDEA how DynamoDB worked. He didn't know about partition keys, sort keys, or secondary indices. I basically wrote my data schema AS IF it were SQL, which felt strange.

He asked me to walk through what happens in my system for each of the 4 workflows.

Group chat - easy.
Just create an entry in your group_chat table and corresponding entries in your chat_user table.

Create an inbox and load the top 10 group chats.
Simple - when the user logs in, you just query the top 10 most recently updated chats.

Consider this schema

group_chat
id: INT PK
created_at: datetime
last_modified_at: datetime (idx)
[Can also use a DB trigger to update last_modified_at.]

chat_user
id: INT PK
user_id: INT (idx, FK references user.id, ON UPDATE CASCADE, ON DELETE CASCADE)
group_chat_id: INT (idx, FK references group_chat.id, ON UPDATE CASCADE, ON DELETE CASCADE)
created_at: datetime

message
id: INT PK
sender_id: INT (idx, FK references user.id, ON UPDATE CASCADE, ON DELETE CASCADE)
message: varchar(500)
created_at: datetime

Whenever you write a message, you should use a producer-consumer model. The consumer should update the last_modified_at timestamp when you write a message in that group chat.

Send a message in the group chat.
I asked him whether we expect to send the message to the users who are online, or whether it should just show up next time the user refreshes their page. He said we want to push it.
Simple - I immediately said there were two paths:

Saving the message in the database and making it ready to load for the people who were NOT CURRENTLY ONLINE.
Pushing the message to active users.

He told me to ignore the second path. It was strange, because that one is pretty important.
For #1, do the following

User ----message----> [Chat Server] ---message---> Kafka ---message---> Consumer
The consumer (1) Writes the message to the message table, (2) Updates the group_chat table, and (3) delivers the message to the other online users (he said to ignore this) using at-least-once-delivery.

Show messages of a group chat
This is an easy query when you click a group chat. It just loads the most recent messages.

Follow up:

What if we want to create groups of users and refer back to the existing groups whenever the same group makes another reservation?

Simple.
New Tables:

Group:
Id INT PK
signature: text (idx)
created_at: datetime

group_member:
Id INT PK
user_id INT (idx) fk references ...
group_id: INT (idx), fk references group.id
created_at: datetime

Sort the user_ids and make a key out of the concatenated user_ids. This will be the Group.signature

E.g. if users 1, 2, 8 are in the group, then the key is "1,2,8"
If you want to see if users 2, 8, 1 have ever formed a group before, then you look for the key
"1,2,8"

Then change the chat_member table to reference groups instead of users.

Follow Up 2:
How do you deliver the messages to users who are actively online.

Go look at any system design for WhatsApp. Just use Redis + chat servers + messaging queues.

Follow Up 3:
How do you scale the system if you're creating 1,000,000 group chats per day?
DynamoDB horizontally scales REALLY WELL. Etc. etc.