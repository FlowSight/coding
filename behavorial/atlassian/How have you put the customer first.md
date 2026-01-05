prompt : 
    how have you put the customer first?
    What trade-off(s) did you make to do this?
Ans:
hce part 1

### **SITUATION**

- Recently at Microsoft,  during adoption of time entry agent by a airline customer, I learned that their internal security system runs codescan, which reported violations in microsoft 1p codebase shipped by us. 
- the violations were from hardcoded urls in code.
- This took me by shock and being blocked by this meant failure for a customer onboarding and a revenue loss of a almost secure deal of thousands of dollars.

### **TASK**
- Although 
        -there was a peer security team who is specialized for these incidents, they were having bandwidth issue.
        - as my feature was used as a entry point for customer adoption, 
    - I realized I should do some due diligence and ensure further work is clearer and customer experiences a quick turnaround time.
- Customer codescan required urls to be moved to a json or xml, but I needed to ensure other customers stay compatible with new change.

### **Action**
- I needed to gather information of all existing customers codescan like system.
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
- I realized a central place for constants and artifacts is a much decoupled and better practice and im looking for more instances of scattered artifacts across our codebase as candidates for sanitization.



===============
===============


