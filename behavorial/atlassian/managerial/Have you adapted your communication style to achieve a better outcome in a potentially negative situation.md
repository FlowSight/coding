-alternate prompts

 - What's your approach when having difficult conversations
 - How have you resolved conflict in the past

**Gist**
- time copilot phase 3 == time agent phase 0
- A peer architect had reviewed design of a feature earlier.
- A major PR for a piece of the feature was reverted by the architect citing a design concern + escalated to M2 to delay the feature release.
- That piece was a critical multi-team sharing feature .
- I had to run several cohorts of experiments to help us align at a acceptable state.


**SITUATION**



***Give time entry COPILOT context with top 3 highest MAU***
- time entry COPILOT GA was on verge of eng complete deadline.
- The e2e feature included a piece where we were introducing a framework to distinguish between Human edited fields vs AI edited fields using stringified json. 
- The feature including the framework was designed entirely by me, signed off by 3 architects and other peer agent teams relied on it.
- This particular piece was worded in design doc was ' we can follow either  a stringified json or enum lookup'.
- Exactly a week before deadline, on a friday, one architect M (who had signed off the design) directly reverted the already merged PR introducing the framework with a single comment : "We should not use stringified json in table column".  He further escalated to my manager and M2 about reconsideration of the feature delivery.
- the feature was committed by stakeholders to customers  months back. Without the concerned piece, the bigger feature could not be shipped. Also, other teams features has to be stopped.
- Manager asked me to address the concerns ASAP.
-  Being a flagship feature, it had a potential to draw millions of dollars in AI subscripton revenue.


TASK:
- I needed to understand the concern quickly, find a middle ground to possibly navigate this.
-  But I didnt have enough time to redo the entire framework. Even if I did, there is no way dependent works can be REDONE
<!-- - Parallely I was continuously reflecting on what consideration did I make to not take the alternate path during design. -->

ACTION:
- I had a sync with him to understand the concern.
- The concern was on two-fold, 
    1. Regarding load-unload time of stringified json, suggestion was to use another table to caputre the last editor per column. OR
    2. change the non-cluster index to full-text index on the string column.
- I retrospected this during design and moved away from the exact concerns as they deemed to be overengineering at that time, given stakeholders stated there was no plan for expansion beyond tracking 3 columns and lack of specificity in design doc.
- The concern could be real, the feedback might be stemming from a real experience, which I absolutely need to evaluate before roll out. 
- To emphasize 'data over debates', I decided to carry out a quick experiment 
- Due to time crunch, I took up evaluating option 1 and option 2 across myself and other teammates.
- We were tracking update for 3 columns, I extended it to track all 20 columns and measured a max size of 600 bytes in string column.

- in average  agent scenario path, a user can have at most 80 time entries logged, 8 hour logged resulting in maximum 80 ser-deser ops per invocation. 
<!-- each time entry minimum 0.5 hour, and 2 update per time entry, for 5 days,  -->
- I took that extreme distribution and becnhmarked avg record create+update latency around 200ms with stringified json path
- I tested the parallel hypothesis which M suggested in option 1 to track the editor per column via a different table along with the extreme distribution. 
- It turned out that 2 new table lookup(one for editor, one for enum) infact resulted 100ms-200ms worse latency than existing approach which means at worst 8sec added latency per user runtime.
- On option 2, my peer and I benchmarked non-clustered index with full-text index even with 3 tracked columns, to my surprise the latter resulted at least 100ms faster on avg.
- Given no major improvement proven by experiment with option 1, I called up a larger forum with M1, M2 , stakeholders and the architect M. 
- Presented our finding with numbers, let the forum decide. I had put my recommendation i.e keeping current change with option 2, as that will have no impact on the work done by all 4 teams.
- Forum agreed, which I established over email. Un-reverted the commit with added change of full-text index.
- In that final PR the comments from M were iterative, first set of comments followed by next set of comments, which further delayed conclusion.
- I had to ask for 1 week extension for feature release from stakeholders via a email.
- Requested M for the final set of comments via same email. Organized a second call to understand the remaining set of concerns AT ONCE.
<!-- - Our current requirements involved only point lookup based on last editor. To get further conviction, I checked with PM if theres any plan
to extend this to range query, he said yes.
- with some indexing space overhead, I was already seeing significant latency improvement combined with possibility of range query, I decided to move to full-text index. -->


RESULT:
<!-- - Although initially not convinced, when demoed with data driven findings, M aigned with finding, recognized the priority and provided sign-off. -->
- M approved in the last week after extension. We were able to merge.

I realized a crucial mistake:
- During initial review, had I specified the exact way to acheive this, perhaps the conflict would be resolved there.
- I made a unconsicous bias of choosing a more simpler solution. I took a judgement call, instead of data-driven call. I was lucky to be on the right side partially this time, but my methodology was not right.
- I lacked a more future look-ahead mindset. I could not contemplate that business requirement might change and our design need to extensible from start.