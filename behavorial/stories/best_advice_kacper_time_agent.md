

--- Prompt : "Can you give an example of a valuable piece of feedback that you have received" -----

### **SITUATION**

During an org restructure at Microsoft, my new manager (M2) started introductory 1:1s with team leads. In our first meeting, I asked him how he envisioned our module — which had the highest MAU in our org — evolving in the context of the company's AI-first direction. His response stuck with me.

He said:

> *“For AI to become what leadership envisions, the tools of AI must be optimal. There might be a push to go all-in on AI, but if a problem feels more fundamental — like a user bottleneck — speak up. Don’t be afraid to challenge stakeholders if something seems misaligned.”*

---

### **TASK**

This feedback gave me permission re-initiate the conversation on a concern our team had kept under the rug for a while: **our agent had an average latency of 2 minutes per user**. This hadn’t been a blocker during our early, small-scale deployments, but I realized that when a large enterprise with 10K users adopts it, it translates to **\~13 days of total user wait time**. This was completely unacceptable — especially when leadership was envisioning an **agentic AI future**. 

<!-- I made it my goal to **reprioritize performance work** and **drive this scale bottleneck into the roadmap**, even if it meant challenging our agreed-upon plan. --> very bad impression (NONONO)
---

### **ACTION**
I first re-initiated the conversation within team between manager and PM, citing concerns of M2. 
Next, I organized a 3 way meeting between M2,M1 and PM. 
Shared the context of problem and let PM share the rationale for deprioritization. 
M2 immediately recognized the risk and raised concern on evaluating priorities. Asked to repriortize ONLY if quick, scalable POC is achieved after validating the hypothesis with architects.
I discussed with my manager to slightly postpone my competing priority items in order to make room for the POC. 

I modified the existing 5 e2e db connection setup + call framework into creating  a set of required transactions in the beginning of the execution path while handling them in one-shot instead of 5 diff back-n-forth inter service calls
This saved :
(4 round trip calls from agent to application per user + 4 db connection setups + 12 db calls) per user.
Additionally, removed explicit 1min sleep time post per user invocation by letting db queue up the reqs and starve each req using pessimistic locking which was in fact much lower than 1min per user.

Within a week, I had built above functional prototype single handedly that brought median latency down drastically to 12secs per user. 

I delegated dashboard and metrics work to an SDE2 from my team to help support the narrative with numbers.

After a successful demo among same audience, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item.

---

### **RESULT**

I led the team to design and implement the fix in full — with cross-team sign-off from architects. 
1. The final solution enabled large customers ( 10K-user orgs) complete full workflows in \~2 days instead of 13 giving a 85% SLA improvement.
2. The performance win was **called out by leadership**, and our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs with 10k MAU have adopted the agent citing this enhancement**.
This experience taught me the value of
1. **combining technical initiative with principled escalation** — and that good feedback, when acted upon, can multiply impact.
2. Rely on instincts, if fundamentals are off, raise the concern with leadership before executing.




//// Prompt : most impactful work ////
**Question:** *Describe the most impactful project you had worked on?*
- best project you have worked on

### **SITUATION**

As a part of enterprise ERP solution org, I lead time entry module which carried the highest MAU in the org. The Latest feature I led and was responsible for was time entry agent, which helped  organization users create time entries asynchronously and timely to minimize meta-work and delayed invoicing cost.
In the kickoff 1:1 with my new M2 after a org restructure, I asked them "how do they envision our module with leadership's AI-first vision ", their crux of their response was :

> *“For AI to become what leadership envisions, the tools of AI must be optimal. Do push back in these early times if the fundamentals seem off or if something seems misaligned.”*

---

### **TASK**

This feedback gave me permission re-initiate the conversation on a concern our team had kept under the rug for a while: **our agent had an average latency of 2 minutes per user**. This hadn’t been a blocker during our early, small-scale deployments, but I realized that when a large enterprise with 10K users adopts it, it translates to **\~13 days of total user wait time**. This was completely unacceptable — especially when leadership was envisioning an **agentic AI future**. 

<!-- I made it my goal to **reprioritize performance work** and **drive this scale bottleneck into the roadmap**, even if it meant challenging our agreed-upon plan. --> very bad impression (NONONO)
---

### **ACTION**
I first re-initiated the conversation within team between manager and PM, citing concerns of M2. 
Next, I organized a 3 way meeting between M2,M1 and PM. 
Shared the context of problem and let PM share the rationale for deprioritization. 
M2 immediately recognized the risk and raised concern on evaluating priorities. Asked to repriortize ONLY if quick, scalable POC is achieved after validating the hypothesis with architects.
I discussed with my manager to slightly postpone my competing priority items in order to make room for the POC. 

I modified the existing 5 e2e db connection setup + call framework into creating  a set of required transactions in the beginning of the execution path while handling them in one-shot instead of 5 diff back-n-forth inter service calls
This saved :
(4 round trip calls from agent to application per user + 4 db connection setups + 12 db calls) per user.
Additionally, removed explicit 1min sleep time post per user invocation by letting db queue up the reqs and starve each req using pessimistic locking which was in fact much lower than 1min per user.

Within a week, I had built above functional prototype single handedly that brought median latency down drastically to 12secs per user. 

I delegated dashboard and metrics work to an SDE2 from my team to help support the narrative with numbers.

After a successful demo among same audience, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item.

---

### **RESULT**

I led the team to design and implement the fix in full — with cross-team sign-off from architects. 
1. The final solution enabled large customers ( 10K-user orgs) complete full workflows in \~2 days instead of 13 giving a 85% SLA improvement.
2. The performance win was **called out by leadership**, and our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs with 10k MAU have adopted the agent citing this enhancement**.
This experience taught me the value of
1. **combining technical initiative with principled escalation** — and that good feedback, when acted upon, can multiply impact.
2. Rely on instincts, if fundamentals are off, raise the concern with leadership before executing.


feedback:
1. what is time entry? how does it look like
2. i made it priority : doesnt sound right.
3. exactly what technical changes