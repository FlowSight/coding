-- candiadates
    - hce part 2
    - android app unblock


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