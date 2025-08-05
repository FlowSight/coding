question : tell me about the hardest problem you had solved
    OR
    tell me about your biggest failure
--
Prompt : tell me about the hardest problem you had solved

__

**Situation**
I led a CVP level visible product called Time entry copilot which lets enterprises enable their employees log,submit and approve their time entries automatically. Immediately after deployment to a critical geo, one of our biggest enterprise user was blocked on existing critical business processes such as submitting time entries,which led them to create a sev2.
**Task**
I had to introspect, figure out the RCA, and retrospect on how this went uncaught in multiple testing, int test etc. Do all these ASAP as more delay indicates customer quoting more business value loss which could make conversations harder among leadership.
**ACtion**
I started by trial-and error approach. Failing to navigate further, I resorted to a elimination based approach. When issue was pinpointed I realized our team's system does not have a check to prevent incorrect table schema metadata, but upstream data modelling team does. After reading codebase of the peer teams, I gathered a unorthodox fix and which worked.
**Result**
