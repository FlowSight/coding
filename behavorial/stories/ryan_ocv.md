


- Tell me about a time you had to work in an ambiguous or unstructured environment.”*
* *“Tell me about a time you influenced others without direct authority.”*
* *“Tell me about a time you led a cross-team initiative.”*
* *“Tell me about a time you took initiative to solve a problem no one owned.”*



### **SITUATION**

At Microsoft, we had a mandate to **onboard all agents into a company-wide feedback system called OCV**. This included four different agents: Time, Expense, Approvals, and Sales.

The problem was — **the requirement was vague**, documentation was inconsistent, and **there were multiple competing PoCs floating around**. There was no clear technical owner, no PM actively driving it, the one who did had just been laid off,  and the deadline was fixed. I reached out to engineers in the other agent teams, but they were just as unclear as I was.

---

### **TASK**

I realized that to succeed, I had to:

1. **Remove the ambiguity** for myself and others.
2. **Define a repeatable, robust integration framework** that could be reused by all agents.
3. **Ensure successful delivery for both my own agent and unblock the others** — even without having authority over them.

This meant stepping into a leadership gap and driving clarity and consistency **across teams** without waiting for PM direction.

---

### **ACTION**

I started by focusing on building the **foundational framework** for OCV integration. This involved:

* Iteratively prototyping how our app could be whitelisted into the host platform.
* Collaborating directly with the **architect of the external Azure app** that would issue the S2S token needed for the handshake.
* Validating testability and debugging paths for downstream teams.

Once the framework was stable, I:

* **Documented it clearly**, including usage patterns and edge cases.
* Published it internally and **shared it across the peer agent teams**.
* Built a **full-stack PoC for my own Time agent**, collaborating with our PM to ensure the final experience aligned with OCV standards.
* Held **weekly syncs** with the other agent teams to check on their progress and offer help, since I knew they didn’t have dedicated PMs driving this.

---

### **RESULT**

My agent — **Time** — successfully onboarded within the deadline. I also directly supported one other team who completed alongside us.

The remaining two teams were delayed but ended up **using the same framework and documentation** I had created and **successfully onboarded in the next release**.

What started as a vague requirement with no clear ownership turned into a **repeatable, cross-team solution** — and it taught me the value of **creating structure when none exists**.

