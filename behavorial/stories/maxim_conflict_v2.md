SITUATION:
***Give time entry copilot context with top 3 highest MAU***
- was on verge of eng complete deadline of feature.
- - The e2e feature included a piece where we were introducing a framework to distinguish between Human edited fields vs AI edited fields using stringified json. 
- This framework was  was designed entirely by me and other peer agent teams relied on it.
- As per team agreement, requested PR signoff from 3 diff architects. One of them, M, due to bandwidth was not able to review PRs during early stages.
- Post dev and testing, on the last week of code merge there was a concern raised by M referring to that piece of the feature. He further expressed concern to my manager about inital design and risk of delivery.
- Manager asked me to address with the concerns.
- the feature was committed by stakeholders to customers  months back. Without the concerned piece, the bigger feature could not be shipped.
-  Being a flagship feature, it had a potential to draw millions of dollars in AI subscripton revenue.
- This concern could deepen the risk for 3 other partner teams' agents as well, as some of them had already merged their entire feature.



TASK:
- I needed to understand the concern quickly, find a middle ground to possibly navigate this. 
- Parallely I was continuously reflecting on what consideration did I make to not take the alternate path during design.

ACTION:
- The concern was on two-fold, either
    1. load-unload time of stringified json, suggestion was to use another table to caputre the last editor per column.
    2. change the non-cluster index to full-text index on the string column.
- I retrospected this during design and moved away from the exact concerns as they deemed to be overengineering at that time, given stakeholders stated there was no plan for expansion beyond tracking 3 columns.
- The concern was real, the feedback might be stemming from a real experience, which I absolutely need to evaluate before roll out. 
- To emphasize 'data over discussions', I decided to carry out a quick experiment 
- We were tracking update for 3 columns, I extended it to track all 20 columns and measured a max size of 600 bytes in string column.
- in average  agent scenario path, a user can have 8 hour logged, each time entry minimum 0.5 hour, and 2 update per time entry, for 5 days, resulting in maximum 80 ser-deser ops per invocation. 
- I took that extreme distribution and becnhmarked avg record create+update latency around 200ms
- I tested a parallel hypothesis which M suggested to track the editor per column via a different table as suggested along with the extreme distribution. 
- It turned out that 2 new table lookup(one for editor, one for enum) infact resulted 100ms-200ms worse latency than existing approach which means at worst 8sec added latency per user context.
- On exploring the second option, when I benchmarked non-clustered index with full-text index even with 3 tracked columns, to my surprise the latter resulted at least 100ms faster on avg.
- Our current requirements involved only point lookup based on last editor. To get further conviction, I checked with PM if theres any plan
to extend this to range query, he said yes.
- with some indexing space overhead, I was already seeing significant latency improvement combined with possibility of range query, I decided to move to full-text index.


RESULT:
- Although initially not convinced, when demoed with data driven findings, M aigned with finding, recognized the priority and provided sign-off.

I realized a crucial mistake:
- During initial review, had I waited for his signoff along with other architects , clarity would have come much earlier
- I made a unconsicous bias of choosing a more simpler solution. I took a judgement call, instead of data-driven call. I was lucky to be on the right side partially this time, but my methodology was not right.
- I lacked a more future look-ahead mindset. I could not contemplate that business requirement might change and our design need to extensible from start.

======end=======
<!-- This led me to a deeper insight that M's POV help me uncover : there are sql views across our system which are serving different forms by doing multiple table joins. 
I discussed with M and another architect (lets call him E) about their thought on considering stringified json or denormalization in deep nested joins. 

We created exploration feature in our roadmap where we (me, M and E) are investigating different sql views and evaluating points eligible for optimization. Its a ongoing effort and we are planning to conclude by few months. -->


<!-- *Interviewer feedback : USe terms like "data over debates" , did performace benchmarking and came back with data .make it more conflicting( as in differnce in opinion ) but not rude. * -->

<!-- *Sumita's comments: the architect blocked the PR and spoke to your manager regarding the design flow according to him. As this was an urgent change : manager wanted to push the architects suggestion . Also I was not able to explain him why my suggestion might work as good as the architect for this problem . 
So I did proof of concept and replicated the condition to check his points will not reduce the time significantly. 

Due to lack of time : I decided to explain both manager and the architect. About my thoughts and provided data to support my points. They were convinced. I was able to get the approval and push the change on time *

*Can you describe a situation where you had to work with a decision that you didn't agree with* -->

-questions
    - *Question : Not agreeing to point 2* in task


