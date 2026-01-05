-- candiadates
    - android app unblock
    - hce part 2


### **SITUATION**
***Give time entry team context with top 3 highest MAU***
- we host an app in play store. Every release cycle google external tester team had to test it by logging into an env shared by us.
- our internal security policy enforced mfa for logging into all internal tenant after crowdstrike incident. 
- The enforcement trickled down to orgs simultaneously, every org created process around testing and accessing environments.
- Google team was blocked to due to being external user lacking mfa setup. We were met with a deadline risking app removal.
- App has MAU of 500k with some significant customers contributung to millions in revenue.
- There is no policy in our entire org to account for external user tester scenario

### **TASK**

- Have to navigate a way around temporarily while making leadership aware of the situation
- Have a permanent process created which can be used by other teams as we are the first team facing it unfortunately.

### **ACTION**
- Have 3 choices : request extension from google v/s let org security team establish process for testing env access v/s me finding a quick,middle ground solution and enable us.
- After a few back and forth google tesing team on collaboration request plus discussing with other internal app teams, security council, it was apparent that conversations were going in circles.
- In the last week of deadline, I decided to anyway ask for extension from google to buy time, which I did after discussing with manager and stakeholder.
- I reached out to Azure AD team for guidence instead of reading into a foreign team repo due to lack of time.
- I learnt there is a way to pause the MFA temporarily with a feature setting which can be set via jarvis, but its meant for internal users.
- I proposed a solution using ephemeral tenant which is isolated to internal and production tenants and combining the new found learning.
- I discussed with M2, Pm and M1, who agreed and asked to get leadership approval.
- I asked for approval to CTO , CVP and security council, cititing the concern, urgency. We received approval.

### Result
- I provided google with test env. Our app was signed off by google.
- As this was bound to be faced by to other app teams sooner or later, I decided to create a framework.
- After discussing with security council, it was agreed to follow the process I followed earlier 
- I created script and wiki for teams to follow.
- Witin 3 months at least 5 teams faced the same blocker from google where they leveraged my framework to whitelist their app which saved 10M in combined potential revenue loss and 2Mil MAU.

=====end======




- extended deadline, reached out to other teams, no help
- existing compliance was restrictive, didnt consider external tester scenario
- discussed with azure ad team
- 3 way discuss with architect
- established temporary solution by enabling signing for ext users for a week,
- i established contract with google, got sign off
- created wiki, 2 peer teams got signoff following same wiki : scm and HR.


- key point :
    - influence cross team
    - create structure/work in ambiguity
    - difficult decision



===============
ANS 2
============
---- version from hce part 2

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