SITUATION:
- I was leading and was at the verge of finishing public preview stage of a feature called Time Entry Agent. 
- Post dev and testing, during the final stage of code merge , a architect of a peer team raised concern.
- The concerned piece involved usage of stringifed json  to differentiate between Human edited fields vs AI edited fields of a time entry. 
- The suggestion was to use another table or columns in same table to caputre the last editor.
- The e2e feature including this piece was designed by me and other peer agent teams relied on it.
-  This concern could deepen the risk for 3 other partner teams' agents as well, as some of them had already merged their entire feature.
- Other items in the feature were built on top of this piece. Also, the feature was committed to customers by stakeholders months back. Being a flagship feature, it had a potential to draw millions of dollars in AI subscripton revenue.


TASK:
- I needed to understand the concern quickly, find a middle ground to possibly navigate this. 
- Parallely I was continuously reflecting on what consideration did I make to not take the alternate path during design.

ACTION:
- Had a discussion with the architect, lets call him M, to understand the view. 
- The concern was : string serialize and deserialize is costly, in average  agent scenario path, there could be as much as 80 ser-deser ops per invocation. Plus, in future if there is expansion to more columns tracking, it will only be worse
- The concern was real, however it was considered during design but deprioritized as business requirement was strictly 2 columns and no plan for expansion.
- I thought only way the argument can settle is by data with a quick experimentation.
- I raised a parallel PR rewriting a portion of the feature using new table to track column editor. 
- Used time to Create, update and read per time entry as KPI and added telemetry around it.
- It turned out that 2 new table lookup(one for editor, one for enum) infact resulted 100ms-500ms worse latency than existing approach which means at least 8sec added latency per user context. This would multiply for more fields.


RESULT:
- M was happy and surprised that this was the case. Aligned with the idea and provided sign-off.
I realized a crucial mistake:
- Had I involved him along with other architects, during initial review, clarity would have much earlier
- When I decided against the table based approach, I took a judgement call, instead of data-driven call. I was lucky to be on the right side this time, but my methodology was not right.

This led me to a deeper insight that M's POV help me uncover : there are sql views across our system which are serving different forms by doing multiple table joins. 
I discussed with M and another architect (lets call him E) about their thought on considering stringified json or denormalization in deep nested joins. 
We created exploration feature in our roadmap where we (me, M and E) are investigating different sql views and evaluating points eligible for optimization. Its a ongoing effort and we are planning to conclude by few months.

