For Google

The loop has four to six rounds covering coding, system design, and behavioral. After the loop, a hiring committee reviews all scorecards and makes the decision. A weak round can cancel out strong ones so every round has to be solid.

 

Coding Rounds
Each coding round is 45 minutes. Most problems have a working first solution and a harder optimized one. Interviewers usually ask for both. Getting only to the naive solution is often not enough for a hire recommendation. Come prepared to optimize.

Many problems include a Part 2 that adds a new constraint or asks you to handle a harder version of the same problem. If you finish Part 1 early, start thinking about where the next constraint might come from. You can get questions like:

- Cheapest Common Ancestor in a Tree: Each node has a price. Given two nodes, find the shared ancestor with the lowest price.

- Shortest Path via BFS: Given a graph as an adjacency list and two nodes, return the shortest path between them.

- Task Scheduling, Minimum CPUs: Given tasks with start times and a fixed length, find the minimum CPUs needed to minimize total end time.

- Shortest Distance to Taxi, Multi-Source BFS: Given a grid with multiple taxi locations, find the minimum steps for a person to reach any taxi.

 

 If you are stuck, say what you know and what you are trying to figure it out.

 System Design
The system design round runs 45 to 60 minutes. Google asks about the kinds of systems they build and operate. Interviewers go deep on consistency models, replication strategies, failure handling, and how the system behaves under load. A high-level diagram is a starting point. You need to be able to discuss the tradeoffs in your choices.think questions like these:

- How would you design Google's web indexing database?

- How would you design Google Docs, specifically real-time collaborative editing?

- How would you design Google Search?

- How would you design a task scheduling system for jobs running on a rack of machines?

- How would you design a system that counts YouTube video clicks in real time?

 

For each of these, be ready to discuss data partitioning, write contention, consistency guarantees, and failure recovery. Senior level roles go deeper on all of these. Have a point of view on each tradeoff.

System Design
ByteByteGo by Alex Xu is the most practical starting point. The YouTube channel is free and covers most of the question types Google asks in a visual format. The System Design Primer on GitHub is more comprehensive and worth reading as a foundation before moving to company-specific prep.

Once you have the basics, read Google's engineering research and blog. They have published papers and write-ups on Spanner, Bigtable, MapReduce, Chubby, and Borg. Interviewers reference these systems directly in design questions. Knowing how Google has actually solved these problems at scale gives you a much stronger vocabulary for discussing tradeoffs than studying abstract patterns alone.

 
Behavioral
Write your stories out before the interview and practice them out loud. Prepare answers that cover the main themes: conflict, missed goals, helping others, and handling ambiguity. For each story, know the situation in enough detail that you can answer follow up questions without stumbling.

The behavioral round is scored the same way as coding. Candidates who are strong in technical rounds but walk into behavioral unprepared do not always get offers. Treat it as a prepared round.

Mock Interviews
For mock interviews, use Apex Interviewer. It runs full AI-powered sessions using verified Google questions across all rounds. The AI asks follow-up questions the way interviewers do, scores you using Google-specific rubrics, and gives you feedback grounded in your actual transcript. The point is repetition. Once you are consistently performing well on Apex, do one session with a senior SWE through any platform. By that point you know the format. You are using the human session to confirm you are ready.

Question Banks
Gotham Loop has the most current Google question bank available. Their Google section covers the full range of difficulty and gives a clearer picture of what to expect. Going through the full list before your loop is worth the time. Their database is updated regularly, so what you are reading reflects what is being asked now.