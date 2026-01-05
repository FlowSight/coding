- alternate prompt : "Describe a technical mistake you have made recently?"

- talk about lenovo sev2, but need a diff wording




question : tell me about the hardest problem you had solved
    OR
    tell me about your biggest failure
--
Prompt : tell me about the hardest problem you had solved

__

**Situation**
***Give time entry COPILOT context with top 3 highest MAU***
- After public preview phase of complete roll out on 250+ enterprise customers across 7 geos, 1000+ tenants and 400+ orgs, exactly and only one of our **largest enterprise clients** raised a **Sev2**. 
- Thousands of employees of the customer were **unable to submit time**, disrupting **payroll processing**, **billing**, and **regulatory reporting**. An estimated **\$1.2M per day business losss was quoted by customer in potential downstream impact**, and leadership was deeply involved due to the visibility of the unwanted blockage. There was a real possibility of entire business loss with the particular customer.
- Team could not replicate this in internal env. We cant solve what we cant replicate. The generic logs were not at all indicative of the true reason.
- We missed adding logs for audit scenario
- we missed to accomodate for rollback as there was no rollback mechanism for our product group.
- handling over to on-call cross geo team was not an option because we build a lot of context while investigating things . 


**Task**
- I had to introspect on why 100+ customers have not faced with this exact same build, figure out the RCA, and retrospect on how this went uncaught in multiple testing, int test etc. 
- Do all these ASAP as more delay indicates customer quoting more business value loss which could make conversations harder among leadership.


**ACtion**
- After a day of unsolved sev2, I had to jump on it to help the team . 
- As I could not replicate the issue in any flavour of our internal systems, but was reproducible in shadow.
- This led me into thinking if any org setting was differing. 
- Compared and figured out audit trail was enabled org wide which was overriding table and column level settings. This was against usual recommendation from microsoft to customers. 
- Still I could not relate how enabling audit impacted time workflow as we didnt introduce any change related to audit.
- I used git bisect across all 40ish commits for the feature, deployed and figured the culprit commit. I took the teams help to scale this.
- It was **schema metadata mismatch** introduced in a PR by my peer with schema name being a__b instead of a_b, and a audit check must be failing here which was ignored by me as our documentation doesnt mention any restriction in schema naming.
- I took complete ownership by communicating to leadership that it was a test miss.
-  I further realized our teams or our product teams system does not have a check to prevent incorrect table schema metadata, but upstream data modelling team does, which does not have any documentation exposed to us, 1p teams.
- I realized the fix FOR THIS ISSUE has to lie in the data modelling teams' codebase.
- It was weekend and transferring of ownership was an option, but it would only increase the customer pain time.
- After reading codebase, I found there is a check to convert each column unique name to smallcase, and a lookup in all columns physicalname for a exact match.
- So, I introduced a unorthodox fix where I introduced a reversed incorrect column name in our codebase with a__b physical name and a_b schema name. This fix worked.

**Result**

- Customer concern was resolved within 1 business day as I delivered the fix on saturday.
- I requested architects for a more product level rolout mechanism. It did not meet with assurance or certainity of timeline citing necessity or bandwith crunch.
- I decided to squeeze out my module into a separate solution and have a rollback for my module only, so that no DAG/topological sort needs to be calculated.
- - I ensured ALL product paths have telemetry coverage for audit scenario, but creating and managing a task among teammates.
- The same customer had many open performance related incidents across multiple teams but it was never highlighted that the audit was on globally. With this finding immediate resolution was received in at least 8 incidents by turning off auditing.
- customer publicly acked and appreciated the response time. Before next relase, they proceeded to purchase more $200k worth of licenses for agent adoption.

- I realized during the post mortem review:
1. It **was** our failure not to account for the dependency. 
2. We normally overlook simple things like naming, but if the area lies with another team, we need written contracts and agreements to follow without assuming that there is no implication. we should look at dependency points and establish contracts with a rationale.
3. PR reviews can overlook mistakes. this can only be solved by automated code-coverage, which needs to be worked upon at scale, as this could be any other 1p team instead of us. For which, a larger initiative needs to be taken to avoid this across our codebase which involves 8 teams.


======end====

- learning
- story : lenovo sev2

-


