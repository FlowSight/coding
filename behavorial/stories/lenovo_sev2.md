question : tell me about the hardest problem you had solved
    OR
    tell me about your biggest failure
--
Prompt : tell me about the hardest problem you had solved

__

**Situation**
I designed ,led, orchestrated implementation with a team of 4 and was responsible for success of  a CVP level visible product called Time entry copilot which lets service based enterprises enable their employees log,submit and approve their time entries automatically.
After complete roll out, exactly and only one of our **largest enterprise clients** raised a **Sev2**. Thousands of employees were **unable to submit time**, disrupting **payroll processing**, **billing**, and **regulatory reporting**. An estimated **\$1.2M per day business losss was quoted by customer in potential downstream impact**, and leadership was deeply involved due to the visibility of the unwanted blockage. There was a real possibility of entire business loss with the customer.

*Question: Please explain what this time entry copilot does. how many enterprises was it deployed.*
**Task**
After a day of unsolved sev2, I had to jump on it to help the team . I had to introspect, figure out the RCA, and retrospect on how this went uncaught in multiple testing, int test etc. Do all these ASAP as more delay indicates customer quoting more business value loss which could make conversations harder among leadership.


*Question: Can we add it was working for most of the customer except one.*
**ACtion**
As I could not replicate the issue in any flavour of our internal systems, but was reproducible in shadow.
- This led me into thinking if any org setting was differing. 
- Compared and figured out audit trail was enabled org wide which was overriding table and column level settings. This was against usual recommendation from microsoft to customers. 
- Still I could not relate how enabling audit impacted time workflow as we didnt introduce any change related to audit.
- I used git bisect across all 40ish commits for the feature, deployed and figured the culprit commit. I took the teams help to scale this.
- It was **schema metadata mismatch** introduced in a PR by my peer with schema name being a__b instead of a_b, and a audit check must be failing here which was overlooked by me as our documentation doesnt mention any restriction in schema naming.
- I took complete ownership by communicating to leadership that it was a test miss.
-  I further realized our or our product teams system does not have a check to prevent incorrect table schema metadata, but upstream data modelling team does, which does not have any documentation exposed to us, 1p teams.
- I realized the fix has to lie in the data modelling teams' codebase.
- It was weekend and transferring of ownership was an option, but it would only increase the customer pain time.
- After reading codebase, I found there is a check to convert each column unique name to smallcase, and a lookup in all columns physicalname for a exact match.
- So, I introduced a unorthodox fix where I introduced a reversed incorrect column name in our codebase with a__b physical name and a_b schema name. This fix worked.

**Result**

- Customer concern was resolved within 1 business day as I delivered the fix on saturday.
- The same customer had many open performance related incidents across multiple teams but it was never highlighted that the audit was on globally. With this finding immediate resolution was received in at least 8 incidents by turning off auditing.
- customer publicly acked appreciated the response time. Before next relase, they proceeded to purchase more $200k worth of licenses for copilot adoption.

- I realized during the post mortem review:
1. It **was** our failure not to account for the dependency. 
2. We normally overlook simple things like naming, but if the area lies with another team, we need written contracts and agreements to follow without assuming that there is no implication. we should look at dependency points and establish contracts with a rationale.
3. PR reviews can overlook mistakes. this can only be solved by automated code-coverage, which needs to be worked upon at scale, as this could be any other 1p team instead of us. For which, a larger initiative needs to be taken to avoid this across our codebase which involves 8 teams.

-  I immediately consulted peer architects and introduced few changes
1. Stopgap solution in our system to block incorrect schema in PR build/release pipeline.
2. Documentation on new learning including a case study of the customer issue
3. Introduce automated UI check to include this in release sign-off testing.
4. Start a office hours between data modelling group and our product group, to make us aware of any change being introduced in upstream. Im working to improve the participation in this forum.

It taught me that while failures are inevitable, **how you respond defines your impact**.







##### ***chatgpt***

Sure. One of the biggest failures I’ve faced—and also one of the most valuable growth moments—happened during the launch of a high-impact product I was leading called **Time Entry Copilot**. It’s designed to help enterprise users automate time logging, submission, and approval flows.

Initially, I tried a few debugging approaches, but nothing surfaced the root cause. Realizing time was slipping and stakes were rising, I took a step back and shifted to a **structured elimination approach**. Eventually, I traced the issue to a **schema metadata mismatch**. Our system lacked validation for certain table schema changes—an assumption we had mistakenly made about upstream data hygiene.

What made this tough was that the validation logic existed—but in a **different team’s system**. It wasn’t our bug, but it **was** our failure to account for the dependency.

I quickly dived into the upstream team’s codebase, figured out their schema handling logic, and implemented a **temporary but robust fix** within our system that validated metadata before processing. It was an unorthodox approach—technically outside our ownership boundary—but it worked. The client was **fully unblocked within 6 hours**.

But what I’m most proud of is what followed.

I led the **post-incident review** with multiple teams and drove a long-term solution: a **shared schema validation contract** between systems, along with CI-level enforcement to block schema-breaking changes from reaching production.

We didn’t just recover from the failure—we turned it into an opportunity to improve engineering quality across orgs. The client was not only satisfied—they **publicly acknowledged our speed and ownership** in the next QBR, and chose to **accelerate** their rollout to two additional regions ahead of schedule.

Leadership later highlighted this incident as a **model example of customer obsession, cross-team collaboration, and high-ownership engineering**.

It taught me that while failures are inevitable, **how you respond defines your impact**. I now design every system I lead with an **assume-nothing, validate-everything mindset**, especially for flows that affect external customers.


- i designed,were working with 4 teams, made a mistake of not considering schema naming due to lack of process documents from peer team
- teammate pushed changes
- when issue occurred, i took ownership