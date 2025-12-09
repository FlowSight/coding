prompt: “Tell me about a time you took initiative on a project.”

## gist##
- time agent phase 0
- 
### **SITUATION**

- Recently at Microsoft,  during adoption of time entry agent by a airline customer, I learned that their internal security system runs codescan, which reported violations in microsoft 1p codebase shipped by us. 
- the violations were from hardcoded urls in code.
- This took me by shock and being blocked by this meant failure for a customer onboarding and a revenue loss of a almost secure deal of thousands of dollars.

### **TASK**
- Although there was a peer security team who is specialized for these incidents, as my feature was used as a entry point for customer adoption, I realized I should do some due diligence and ensure further work is clearer.
- Customer codescan required urls to be moved to a json or xml, but I needed to ensure other customers stay compatible with new change.

### **Action**
- I needed to gather information of all customer codescan like system.
- We have 250+ enterprises onboarded. Figuring out each customers security practice by manually reaching out via PM path is not scalable and infeasible within 2 weeks of sla
- I examined telemetry and filtered 180 customers who had no customization layer.
- for the rest of them I engaged via PM and partners and learned there is no customer who is so far implementing this.
- I created a poc of migration of urls into json only for our module.
- I started larger discussion with product owner, 360 team, 3 architects on the priority and feasibility of the solution. I presented our current finding, my solution and its extensibility by other 7 teams.
- But the other teams raised concern on competing priorities, tight deadline.  Seeing this, the product owner decided to pursue the customer to disable their codescan temporarily.
- I suggested a long term solution of adopting the learning from customer to move our urls across codebase.

### **Result**
- the customer had temporarily disabled their codescan and onboarded my feature and our product.
- My suggestion for long term solution was backed by architect and product owners.
- Although, my work was undone temporarily, I finished sanitization of our codebase fast and created a feature which ive led across  7 teams and concluded in 3 sprints
I realized a central place for constants and artifacts is a much decoupled and better practice and im looking for more instances of scattered artifacts across our codebase as candidates for sanitization.

======= end====
*Interviewer feedback : sound little immature : instead can use that my work was undone temporarily, I finished sanitization of our codebase first* 


==== start======
#####
Prompt: tell me about a time where you had to work with a decision that you didn't agree with


### **SITUATION**

- Recently at Microsoft,  during adoption of time entry agent by a airline customer, I learned that their internal codescan reported violations due to hardcoded urls in code shipped by us.
- After discussion with Architects, it was decided to dump urls into a json and follow it cross the 8 teams touching the codebase. 
- I was responsible for  creation of the framework which other peer teams would use.
- I had a hunch json dump approach will not be a one size fits all solution, but I didnt have a data point to prove it.
- I went along the agreement and started poc.

### **TASK**
- I needed to quickly determine a framework with a poc where the design fits all, not only my teams codebase but also others
- ALTHOUGH NOT CALLED OUT, I needed to evaluate whether the serialize/deserialize nature of json is costlier than other approach like db read or env variable.

### **Action**
- I built the framework poc for json dump, lets call it solution 1.
- I built a parallel poc using feature control settings for my hypothesis of reading from table, solution 2.
- I conduncted these parallel POCs by consuming both the frameworks from different codepaths to proof the flexibility of the solution

*Interview feedback : POC from multiple different code paths to proof the flexibility of the solution * 

- There were around 200 different hardcoded urls across 80 files. I grouped the consumers by their nature and tested each group.
- I benchmarked the url load time for both framework.
- when i carried out e2e test, it appeared that, sandbox apis fail to use json approach as they are prohibited from filesystem access.
-  db reads had cold start of around 500ms, json load had 700ms cold start using newtonsoft, but both can be solved by adding caching, so my hypothesis was not really accurate on load time, but I had a new finding which i didnt account for.
- I brought this insight to our next sync
- I suggested a dual solution using db read for sandbox apis and json dump for test framework and non-critical codepath + benchmark the latency.

### **Result**
- Architects appreciated the findings and inclined on the approach.
- the co-dev by peer teams started and finished within a sprint by moving 120 urls to db
and remaining to single json dump. 
- This json dump resulted our test pipeline having a added latency ~10 mins which is negligible compared to the total 4hr runtime. 
- I addeed this latency callout to our modules performance painpoint wiki under low impact zone.
- This change affected enitre 500+ customers and 2Mil MAUs
- I realized data always is the final truth, personal believes, hypothesis should always be validated before committing onto something.


*Interviewer feedback : make more data driven *














/////////dont read below/////////


- airline customer..newly adopted product
- early adopter of time entry agent, which I led
- I was interacting with customer to help them onboard,when  they reported a security issue to me as their system's codescan failed.
- after digging i figured it was due to hardcoded urls in our codebase
- our entire codebase touches 8 teams, 
- sla of 1 week, 500k loss
- consulted architects, all 8 team leads, on how to mitigate as well as keeping the change backward compatible (T)
- an architect proposed a solution involving dumping all urls into a json in shared solution folder.
- I carried out the POC where I figured for sandbox apis it would fail.I introduced a Feature control setting based solution, finished the poc and proposed it to the team.
- Received consensus from the team on above approach
- I decided to test incrementally by first deploying a component solution in customer UAT.
- With minor , independent bugs I was able to ship the fix within a week. 
- This resulted in a key insight to maintain code hygiene in our codebase, following which I implemented a code scanner check to prevent hardcoded urls to get checked in via pull requests.

