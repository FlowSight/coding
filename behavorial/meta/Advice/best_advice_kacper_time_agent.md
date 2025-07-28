
**Question:** *Can you give an example of a valuable piece of feedback that you have received?*

---

### **SITUATION**

During an org restructure at Microsoft, my new manager (M2) started introductory 1:1s with team leads. In our first meeting, I asked him how he envisioned our module — which had the highest MAU in our org — evolving in the context of the company's AI-first direction. His response stuck with me.

He said:

> *“For AI to become what leadership envisions, the tools of AI must be optimal. There might be a push to go all-in on AI, but if a problem feels more fundamental — like a user bottleneck — speak up. Don’t be afraid to challenge stakeholders if something seems misaligned.”*

---

### **TASK**

This feedback gave me permission to act boldly on a concern our team had kept under the rug for a while: **our agent had an average latency of 2 minutes per user**. This hadn’t been a blocker during our early, small-scale deployments, but I realized that when a large enterprise with 10K users adopts it, it translates to **\~13 days of total user wait time**. This was completely unacceptable — especially when leadership was envisioning an **agentic AI future** where responses are AI-first and user nudge to AI is minimal, with little to none user-system involvement.

I made it my goal to **reprioritize performance work** and **drive this scale bottleneck into the roadmap**, even if it meant challenging our agreed-upon plan.

---

### **ACTION**

I first brought it up with my direct manager in a 1:1. He was hesitant, citing both feasibility and the risk of going off-plan and risk of convincing leadership. Next, I spoke to our PM — he was more receptive but unsure about deprioritizing our next set of AI feature experiments.

I then arranged a 3-way discussion with our M2, PM, and my manager. I presented the problem, its long-term implications, and how it could derail adoption at scale. M2 immediately recognized the risk and agreed — but with a caveat: we’d postpone AI A/B experimentation **only if I could build a quick POC** to demonstrate feasibility.

I took full ownership — within a week, I had built a functional prototype myself that brought median latency down drastically. I delegated dashboard and metrics work to an SDE2 from my team to help support the narrative.

After the successful demo, M2 took the proposal to our CVP and got buy-in. This officially became our next roadmap item.

---

### **RESULT**

We designed and implemented the fix in full — with cross-team sign-off from the architect. The final solution brought **latency down from 2 minutes to 15 seconds per user**, enabling even large customers (like 10K-user orgs) to complete full workflows in \~2 days instead of 13.

The performance win was **called out by leadership**, and our PMs used it as a **proof point to re-engage large enterprise customers** who had been hesitant. As of now, **two large orgs have adopted the agent citing this enhancement**.

This experience taught me the value of **combining technical initiative with principled escalation** — and that good feedback, when acted upon, can multiply impact.

