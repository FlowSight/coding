

--- Prompt : "Can you give an example of a valuable piece of feedback that you have received" -----

### **SITUATION**
***Give time entry agent context with top 3 highest MAU***
- During our first 2 phase of agent rollouts it became evident to me that the floor agent execution latency per user is 1 min. 
- This stemmed from a design gap. As we were moving fast,stakeholders decided to address the latency when busines demand arises.  
- While helping to onboard a customer, I learnt that they had interest to purchase upto 50k user licenses.
- I resurfaced the concern with my M1 where our current infra does not meet a potential customer scale. He sugegested to discuss further with M2.
- I raised it in a 1:1 M2 , citing a potential instant demand for scale-up(after decision with my M1).
- M2 suggested to figure out a possibility to quickly pivot via a poc if a more scalable solution is achievable.
- his words were in the lines of : 'For AI to become what leadership envisions, the tools of AI must be optimal'

### **TASK**
- I echoed with his view and made rearrangement of my next priorities with M1. 
- My goal was clear :  benchmark, establish chokepoints, hypothize and build poc to demonstrate measurable difference in performance per agent execution.

<!-- I made it my goal to **reprioritize performance work** and **drive this scale bottleneck into the roadmap**, even if it meant challenging our agreed-upon plan. --> very bad impression (NONONO)
---

### **ACTION**
- I estimated for a org of 50k users it would take 35 days for the agent to complete execution for a weeks data, unacceptable.
- Agent execution per user is in 3 parts : 
    1. per user config read from table
    2. invoke agent with current week start and end date
    3. AGENT as RAG had 5 steps to do with 5 tools, each tool is a PAF.
    4. at the end of it, optionally return the summary and notify user.
- I mocked with 500 users concentrated in single org. Profiled key kpis like per user runtime in each tool, total RAG runtime, total flow runtime
- I observed : 5 tool execution together contributed to avg 45 secs. these tools read from same db but different tables.
- I identified agent RAG was wasting e2e service calls across 5 tools, 5 db connection setup, 5 transactions. But I had to keep the RAG in place as mandate from leadership.
-  As our workflow steps was predictable, I moved away from over relying on the RAG into creating a set of required db crud ops before RAG invocation from inside power automate flow.
- Instead of exposing 5 tools, I merged them into one tool which executed the initially evaluted setof ops by creating one db connection and in one transaction.
- This saved : 4 round trip calls from agent to application per user + 4 db connection setups + 12 db calls, per user.
- I further removed, replaced pessimistic locking with occ with retry. I benchmarked around 20% cases contention causes retry which results in peak latency of 10sec, which still overall yielded a much better result.
- I timed it using telemetry and sql blocking tree to find for a org of 5k user in same geo+same org with 30% concentration in same project would yield worst case 5s wait time per transaction.
- Within a week, I had built above functional prototype single handedly that brought median latency down drastically to 8secs per user. 
- I delegated the key kpis dashboard to a junior peer.

### **RESULT**
- I benchmarked 5000 mock users in A/B testing and demonstrated with extrapolation that for 50k users and 10k users, it would take agents total runtime of 5 days and 1 day respectively, giving a 85% SLA improvement as opposed to 35 days and 7 days. 
-  After a successful demo among same audience plus some peer architects, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item.
- I led the team to design and implement the fix in full — with cross-team sign-off from architects. 
- This gained confidence in our critical setof enterprise customers having 10k+ users, which resulted in thousands of ai license purchases pivoting time agent.
- The performance win was **called out by leadership in next newsletter**, and our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs with 10k MAU have adopted the agent citing this enhancement**.

This experience taught me the value of
1. It helps to think from a product owner perspective and combining it with technical tools at disposal, I can really make a difference.
2. sometimes taking the longer, seemingly harder path is better for long term stability by sacrificing short term gain.


!-- //////////// -->
**Prompt:** *Describe the most impactful project you had worked on?*
- best project you have worked on
-Mistake 
-

### **SITUATION**
***Give time entry agent context with top 3 highest MAU***
- During our first 2 phase of agent rollouts it became evident to me that the floor agent execution latency per user is 1 min. 
- This stemmed from a design gap. As we were moving fast,stakeholders decided to address the latency when busines demand arises.  
- While helping to onboard a customer, I learnt that they had interest to purchase upto 50k user licenses.
- I resurfaced the concern with my M1 where our system does not meet a potential customer scale. He sugegested to discuss further with M2.
- I raised it in a forum with M1, M2 and PM, citing a potential instant demand for scale-up.
- M2 suggested to figure out a possibility to quickly pivot via a poc if a more scalable solution is achievable.

### **TASK**
- I echoed with his view and made rearrangement of my next priorities with M1. 
- My goal was clear :  benchmark, establish chokepoints, hypothize and build poc to demonstrate measurable difference in performance per agent execution.

<!-- I made it my goal to **reprioritize performance work** and **drive this scale bottleneck into the roadmap**, even if it meant challenging our agreed-upon plan. --> very bad impression (NONONO)
---

### **ACTION**
- I estimated for a org of 50k users it would take 34 days for the agent to complete execution for a weeks data, unacceptable.
- Agent execution per user is in 3 parts : 
    1. per user config read from table
    2. invoke agent with current week start and end date
    3. AGENT as RAG had 5 steps to do with 5 tools, each tool is a PAF.
    4. at the end of it, optionally return the summary and notify user.
- I mocked with 500 users concentrated in single org. Profiled key kpis like per user runtime in each tool, total RAG runtime, total flow runtime
- I observed : 5 tool execution together contributed to avg 45 secs. these tools read from same db but different tables.
- I identified agent RAG was wasting e2e service calls across 5 tools, 5 db connection setup, 5 transactions. But I had to keep the RAG in place as mandate from leadership.
-  As our workflow steps was predictable, I moved away from over relying on the RAG into creating a set of required db crud ops before RAG invocation from inside power automate flow.
- Instead of exposing 5 tools, I merged them into one tool which executed the initially evaluted setof ops by creating one db connection and in one transaction.
- This saved : 4 round trip calls from agent to application per user + 4 db connection setups + 12 db calls, per user.
- I further removed, replaced pessimistic locking with occ with retry. I benchmarked around 20% cases contention causes retry which results in peak latency of 10sec, which still overall yielded a much better result.
- I timed it using telemetry and sql blocking tree to find for a org of 5k user in same geo+same org with 30% concentration in same project would yield worst case 5s wait time per transaction.
- Within a week, I had built above functional prototype single handedly that brought median latency down drastically to 8secs per user. 
- I delegated the key kpis dashboard to a junior peer.

### **RESULT**
- I benchmarked 5000 users in A/B testing and demonstrated with extrapolation that for 50k users and 10k users, it would take agents total runtime of 5 days and 1 day respectively, giving a 85% SLA improvement as opposed to 35 days and 7 days. 


-  After a successful demo among same audience plus some peer architects, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item.
- I led the team to design and implement the fix in full — with cross-team sign-off from architects. 
- This gained confidence in our critical setof enterprise customers having 10k+ users, which resulted in thousands of ai license purchases pivoting time agent.
- The performance win was **called out by leadership in next newsletter**, and our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs with 10k MAU have adopted the agent citing this enhancement**.

This experience taught me the value of
1. It helps to think from a product owner perspective and combining it with technical tools at disposal, I can really make a difference.
2. sometimes taking the longer, seemingly harder path is better for long term stability by sacrificing short term gain.






feedback:
1. what is time entry? how does it look like (indian interviewer)
2. i made it priority : doesnt sound right.(indian interviewer)
3. exactly what technical changes (indian interviewer)
4. *Question: can we talk about did you convinced everyone with the data and comparison with two env.* (sumita)
5. *Question : can we talk more about the feature. what it actually does. *(sumita)
*what is the lag. why is the lag and how did you fix it *(sumita)
6. *Question: share the context and give understanding of the risk. What was the existing thing. What did you change and why did you change*(sumita)
*multiple redundant db calls . 
7. *Question: Can you say you did you with your team member/junior . not mentioning the role*(sumita)

