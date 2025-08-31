### **SITUATION**
***Give time entry team context with top 3 highest MAU***
- we host an app in play store. Every release cycle google external tester team had to test it by logging into an env shared by us.
- our internal security policy enforced mfa for logging into all internal tenant after crowdstrike incident. 
- The enforcement trickled down to orgs simultaneously, every org created process around testing and accessing environments.
- Google team was blocked to due to being external user lacking mfa setup. We were met with a deadline risking app removal.
- App has MAU of 200k with some significant customers contributung to millions in revenue.
- There is no policy in our entire org to account for external user tester scenario
- 

### **TASK**

- Have to navigate a way around temporarily while making leadership aware of the situation
- Have a permanent process creation which can be used by other teams as we are the first team facing it unfortunately.

### **ACTION**
- Have 3 choices : request extension from google v/s let org security team establish process for testing env access v/s me finding a quick,middle ground solution and enable us.
- i decided to anyway ask for extension from google to buy time, which I did after discussing with manager and stakeholder.
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
- Witin 3 months at least 5 teams faced the same blocker from google where they leveraged my framework to whitelist their app which saved 30M in combined potential revenue loss.

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