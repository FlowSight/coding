


- Tell me about a time you had to work in an ambiguous or unstructured environment.”*
* *“Tell me about a time you influenced others without direct authority.”*
* *“Tell me about a time you led a cross-team initiative.”*
* *“Tell me about a time you took initiative to solve a problem no one owned.”*


### **SITUATION**
- At Microsoft, we had a mandate to **onboard all agents into a company-wide feedback system called OCV**. This included four different agents: Time agent which I designed and led, Expense, Approvals, and Sales agents which were owned by diff teams in our product group.
- The problem was — **the requirement such as what metadata to be sent to ocv, any reference PR, were missing**, documentation was talking about multiple ocv sdk version and different deprecated fields.
-  There was no clear technical owner, no PM actively driving it, the one who did had just been laid off,  and the deadline was fixed within 3 weeks. 
- I reached out to peer teams and other architects and learned that they were just as unclear as I was.

### **TASK**
I realized that to succeed, I had to:
1. **Refine the spec and define the scope** for myself and others.
2. **Create a extensible, robust framework** that could be reused by all agents, along with my other feature priorities.
3. **Ensure successful delivery for both my own teams agent and other agents as we must have uniform onboarding onto ocv across agents inside our product group** —  without having direct authority over other teams.
This meant stepping into a leadership gap and driving clarity and consistency **across teams** without waiting for PM direction.

### **ACTION**

- I started by focusing on building the **foundational framework** for OCV integration. It was a 2 step process : creating a framework for reading tenant settings and creating a interface for ocv data ingestion.
- First, I had to onboard our app onto another service provider team called BAP RP to get s2s token for certain cruds in tenant scoped tables.
- I Collaborated directly with the **architect of  BAP RP team** to onboard our app, Validated testability and debugging paths.
- The onboarding faced challenges due to pipeline failure, I parallelized developing part2 keeping the tenant values as a placeholder so that I could finish both piece together
- As no PM involved directly, I started engaging principal lead pm to iteratively agree on the ingestion metadata.
- When phase1 onboarding was unblocked, I raised a sample PR,created wiki, announced the framework to other teams to build on.
- I estimated their work would be limited to 50-100 lines of code with at max 2 days effort.
- I gathered from other teams managers who will be involved in eng effort for this, setup regular sync with them in the last week to understand the progress and help them unblock as I knew there would be questions and unclarity on whys and hows due to lack of context.
---

### **RESULT**

- I had to co-dev on one other teams agent. My own teams time agent, expense and sales agent were onboarded to ocv on time.
- Approval agent teams bandwith was limited due to bandwidth and competing priorities, so I had asked for code complete deadline extension from our leadership.
- Within next 1 week I, my teams peer and approval teams peer co-deved together to complete the merge.

- I realized first hand how challenging a managing and naviagting across multiple stakeholders can be. 
- The key is **creating structure when none exists, establishing scope, having scalable framework that makes repeatable actions smoother**.

