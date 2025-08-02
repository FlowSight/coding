1. **“Tell me about a time you disagreed with a technical direction.”** ✅ Best fit
2. “Tell me about a time you took initiative on a project.”
3. “Tell me about a time when you had to work across teams.”


### **SITUATION**

At Microsoft, an internal security system flagged **hardcoded endpoint URLs** in our codebase as vulnerabilities. A virtual team was formed across three peer teams, each represented by a lead — including myself — to remove these hardcoded URLs.

Early on, one of the other leads, person W, proposed and built a framework that the group quickly aligned on. While I agreed to move forward, I had **serious concerns**. Based on my understanding of our deployment models, I had a **strong hunch** that the framework would break in sandboxed environments where local file system access is restricted.

Unfortunately, I was proven right — when I encountered such a case, **the framework failed**, and we were stuck without a fallback.

---

### **TASK**

By this time, we had already missed the original security remediation deadline and were working under a short extension.

I realized that the group had gone into **circular discussions** — without a resolution path — and the extension was also on the verge of being missed.

My goal became clear:

* **Unblock the situation** with a practical, working solution.
* **Own my team’s changes**, and
* Step in to **help cover for another team** whose lead had gone on leave.

---

### **ACTION**

I started by consulting an architect and proposed a more **pragmatic, short-term solution** using environment variables — which would work across all environments, including sandboxed ones.

I quickly implemented this across my team’s code. Around the same time, another lead went on extended leave, so I **volunteered to take over their portion of the remediation** as well — ensuring consistency and speed.

During code review, a principal engineer raised concerns about using a static data-driven approach and asked if we could go further.

Instead of debating, I proposed a **two-step plan**:

1. Immediately mitigate the security issue using my current implementation.
2. Follow up with a more robust, dynamic config model as a long-term fix — which I scoped as a \~1-week effort post-deadline.

He agreed, and we moved forward.

---

### **RESULT**

* We successfully met the revised deadline, unblocking a major security concern.
* I added a **pre-merge PR check** that now prevents hardcoded URLs from being introduced in future commits.
* The longer-term architectural fix is now part of the backlog and scoped.

This experience reinforced for me the value of **balancing pragmatism and technical ideals** — and the importance of **stepping in with clarity when group consensus stalls.**

