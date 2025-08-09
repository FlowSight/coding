

--- Prompt : "Can you give an example of a valuable piece of feedback that you have received" -----

### **SITUATION**
- I lead the AI first feature called Time agent, of my teams module called Time entry, which had among top 3 highest MAU modules in the org.
- After an org restructure at Microsoft, at the introductory 1:1 with my new M2 I asked him how he envisioned our module  evolving in the context of the company's AI-first direction. His response stuck with me.
- He said:
> *“For AI to become what leadership envisions, the tools of AI must be optimal. There might be a push to go all-in on AI, but if a problem feels more fundamental - speak up. Don’t be afraid to challenge stakeholders if something seems misaligned.”*

---

### **TASK**

- This feedback gave me permission re-initiate the conversation on a known concern that was deprioritized for a while: **our agent had an average latency of 2 minutes per user**. 
- This hadn’t been a blocker during our early, small-scale deployments of upto 1k MAU org, but I called out earlier that for our few large enterprise customers with 10k+ MAU, it translates to **\~13 days of total user wait time** - rendering it unacceptable, especially when leadership was envisioning an **agentic AI future**. 
- I decided to resurface the conversation within the team in the light of my recent conversation with the M2.

<!-- I made it my goal to **reprioritize performance work** and **drive this scale bottleneck into the roadmap**, even if it meant challenging our agreed-upon plan. --> very bad impression (NONONO)
---

### **ACTION**
- I first re-initiated the conversation within team between manager and PM, citing concerns of M2. 
- Next, I organized a 3 way meeting between M2,M1 and PM. 
-Shared the context of problem and let PM share the rationale for deprioritization. 
- M2 immediately recognized the risk and raised concern on evaluating priorities. Asked to repriortize ONLY if quick, scalable POC is achieved after validating the hypothesis with architects.
- I discussed with my manager to slightly postpone my competing priority items in order to make room for the POC temporarily, time bounded by a sprint.
- I modified the existing 5 e2e db connection setup + call framework into creating  a set of required transactions in the beginning of the execution path while handling them in one-shot instead of 5 diff back-n-forth inter service calls
- This saved :
(4 round trip calls from agent to application per user + 4 db connection setups + 12 db calls) per user.
- Additionally, removed explicit 1min sleep time post per user invocation by letting db queue up the reqs and starve each req using pessimistic locking which was in fact much lower than 1min per user.
- Within a week, I had built this functional prototype single handedly, (as I had the design lingering in mind for sometime) that brought median latency down drastically to 12secs per user. 
- I delegated dashboard and metrics work to an SDE2 from my team to help support the narrative with numbers.
- I demoed it across among same audience, M2 was super happy and  took the proposal to our CVP and got buy-in. This officially became our next roadmap item.
- 
 
---

### **RESULT**

- PM and stakeholder discussed with the team to announce the repriortization
- I led the team to design and implement the fix in full, — with cross-team sign-off from architects. 
- This change made it possible for our largest enterprises having 10k+ MAUs complete full workflows in \~2 days instead of 13 giving a 85% SLA improvement.
-  The performance win was **called out by leadership in next newsletter**,
- our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs with 10k MAU have adopted the agent citing this enhancement** resulting in copilot license revenue touching a million.

This experience taught me the value of
- Had we not have large enterprise customer in scope, the design would be not useful, so its very critical to think as a product owner and communicate any gap to leadership so that we can align early before executing.
-  good feedback, when acted upon, can multiply impact.



<!-- //////////// -->
**Prompt:** *Describe the most impactful project you had worked on?*
- best project you have worked on

### **SITUATION**

- I lead time entry module which has one of top 3 MAUs in the org. 
-The Latest feature I led and was responsible for was time entry agent
-In the kickoff 1:1 with my new M2 after a org restructure, I asked them "how do they envision our module with leadership's AI-first vision ", the crux of their response was :

> *“For AI to become what leadership envisions, the tools of AI must be optimal. Do push back in these early times if the fundamentals seem off or if something seems misaligned.”*

### **TASK**
- Our time agent had a significant weakness :  **average latency of 2 minutes per user**. 
- I knew although the largest enterprise customers were to be onboarded after 2 more phases of release, and PMs are leading the conversations, eventually the ENG will have to overcome this bottleneck as no enterprise would wait for 13 days for agent to finish its run to generate timesheet when timesheets are relevant for a week.
- If we could get rid of the bottleneck early, the conversation and adoption might become smoother.
- I decided to resurface the conversation with my manager and PM in context of my discussion with M2


### **ACTION**
- After discussing internally I organized a 3 way meeting between M2,M1 and PM. 
- I presented the context of problem and let M1 and PM share the rationale for deprioritization. 
- M2 immediately recognized the risk and raised concern on evaluating priorities. Asked to repriortize ONLY if quick, scalable POC is achieved after validating the hypothesis with architects.
- I discussed with my manager to slightly postpone my competing priority items in order to make room for the POC while keeping it time bound to a sprint
- I identified agent RAG was wasting e2e service calls across 5 tools, 5 db connection setup, 5 transactions. But I had to keep the RAG in place as mandate from leadership.
-  As our workflow was predictable, I moved away from over relying on the RAG into creating a set of required db crud ops before RAG invocation from inside power automate flow.
- Instead of exposing 5 tools, I merged them into one tool which executed the initially evaluted setof ops by creating one db connection and in one transaction.
- This saved : 4 round trip calls from agent to application per user + 4 db connection setups + 12 db calls, per user.
- I further removed, explicit 1min sleep time post per user invocation by letting db queue up the reqs and starve each req using pessimistic locking which was in fact much lower than 1min per user. 
- I timed it using telemetry and sql blocking tree to find for a org of 5k user in same geo+same org with 30% concentration in same project would yield worst case 5s wait time per transaction.
- Within a week, I had built above functional prototype single handedly that brought median latency down drastically to 12secs per user. 
- I delegated key kpis dashboard like per user runtime, e2e agent invoke time to an SDE2 from my team to help support the narrative with numbers.
- After a successful demo among same audience, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item.

---

### **RESULT**

- PM and stakeholders discussed with the team to announce the repriortization following my work.
- I led the team to design and implement the fix in full — with cross-team sign-off from architects. 
1. The final solution enabled large customers ( 10K-user orgs) complete full workflows in \~2 days instead of 13 giving a 85% SLA improvement.
2. The performance win was **called out by leadership in next newsletter**, and our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs with 10k MAU have adopted the agent citing this enhancement**.

This experience taught me the value of
1. It helps to think from a product owner perspective and combining it with technical tools at disposal, I can really make a difference.
2. sometimes taking the longer, seemingly harder path is better for long term stability by sacrificing short term gain.


feedback:
1. what is time entry? how does it look like
2. i made it priority : doesnt sound right.
3. exactly what technical changes




