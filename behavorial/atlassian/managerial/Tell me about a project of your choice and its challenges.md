- time agent perf


- crisp:
    There was other work item in line planned without scale problem solved.
    I did a poc and figured out which parts to improve which brought down latency
    I demoed that its giving 85% latency improvement which became our next long term project, 2/3 phases are delivered scaling time agent from 0 to 100k users.
- details:
   - It became next work item : in next release (for 3 months) I led, designed , implemented part of it except generate comment flow
   - In phase 2 for we are implementing the other part of it i.e. gen comment, thats gonna be completed now
    - There will be a phase 3 where we would use agent queue, oct-dec
    Each phase takes months as :
        phase 1: slight redesign on creating set of commands from inside tool instead of paf + implement + 
                + LLM call -> compliance review
        phase 2: LLM call -> compliance review
    At phase0(Jan-March) we estimated 0-50k license adoption (copilot phase3 collided with this)
    At phase1(April - June) we estimated 100k license adoption, but my changes got 700k
    At phase2(July-Sep) we estimated 300k-500k license adoption, again citing my change we are on track to get 1.8Mil
    At phase4 we estimated 1mil license adoption, future
    Mentioned at state of the mind article by CVP about phase1



### **SITUATION**
***Give time entry agent context with top 3 highest MAU*** 
- During our phase0 of agent rollouts it became evident to me that the floor agent execution latency per user is 1 min. 
- This stemmed from a design gap. As we were moving fast,stakeholders decided to address the latency when busines demand arises.  
- While helping to onboard a customer, I learnt that they had interest to purchase upto 50k user licenses.
- I resurfaced the concern with my M1 where our system does not meet a potential customer scale. He sugegested to discuss further with M2.
- I raised it in a forum with M1, M2 and PM, citing a potential instant demand for scale-up.
- M2 suggested to figure out a possibility to quickly pivot via a poc if a more scalable solution is achievable. Keeping our next priority on hold temporarily

### **TASK**
- I echoed with his view and made rearrangement of my next priorities with M1. 
- My goal was clear :  benchmark, establish chokepoints, hypothize and build poc to demonstrate measurable improvement in performance per agent execution.

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
- I benchmarked 5000 users in A/B testing and demonstrated with extrapolation that for 50k users and 10k users, it would take agents total runtime of 5 days and 1 day respectively, giving a 85% SLA improvement as opposed to 35 days and 7 days. 


### **RESULT**

-  After a successful demo among same audience plus some peer architects, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item instead of the other priority.
- - This gained confidence in our critical setof enterprise customers having 10k+ users, which resulted in thousands of ai license purchases pivoting time agent. PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant.
- I led the team to design and materialize the fix as a long term item. — with cross-team sign-off from architects. It was split into phases.
-  We finished phase1 in June with. Agent MAU touched 100k and agent license subscription touched 700k compared the projected 10k MAU and 100k revenue. This all pivoted around the massive improvement in agent performance.
- Latest phase i.e. phase2 is to be completed in Sep 25 where we have confirmed onboarding of more premium customers and projecting a subscription revenue of 1.8mil and MAU of close to 200k as opposed to originally estimated 500k revenue and 50k MAU.
- As of now, **8 large orgs with 10k+ users have adopted the agent citing this enhancement**.
- The performance win was **called out by CVP in next state of the mind newsletter**

This experience taught me the value of
1. It helps to think from a product owner perspective and combining it with technical tools at disposal, I can really make a difference.
2. sometimes taking the longer, seemingly harder path is better for long term stability by sacrificing short term gain.

