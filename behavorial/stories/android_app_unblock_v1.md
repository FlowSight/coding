### **SITUATION**
***Give time entry team context with top 3 highest MAU***
- we host an app in play store. Every release cycle google external tester team had to test it by logging into an env shared by us.
- our internal security policy enforced mfa for logging into all internal tenant after crowdstrike incident. 
- The enforcement trickled down to orgs simultaneously, every org created process around testing and accessing environments.
- Google team was blocked to due to being external user lacking mfa setup. We were met with a deadline risking app removal.
- There is no policy in our entire org to account for external user tester scenario

### **TASK**

- Have to navigate a way around temporarily by making leadership aware of the situation
- Have a permanent process creation which can be used by other teams as we are the first team facing it unfortunately.

### **ACTION**
- Have 3 choices : request extension from google v/s let org security team establish process for testing env access v/s me finding a quick,middle ground solution and enable us.




- extended deadline, reached out to other teams, no help
- existing compliance was restrictive, didnt consider external tester scenario
- discussed with azure ad team
- 3 way discuss with architect
- established temporary solution by enabling signing for ext users for a week,
- i established contract with google, got sign off
- created wiki, 2 peer teams got signoff following same wiki : scm and HR.


- key point :
    - influence cross team
    - 