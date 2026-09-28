1. Study the code base
2. Decompose work and plan :
   1. Ask interviewer if can use AI to plan
      1. if ans is no: plan manually
      2. else ask ai, while talking about ur fallback plan
   2. If AI plan: fix a few things (even if minor). Show authority, dont accept directy.Even if almost all is good.
   3. 3-5 strictly
   4. manual  : data model, class details, dataflow
   5. core func before edge case
3. State the plan to interviewer
   1. interviewer can guide u if he is good and ur misdirected
   2. If 1-2 critical methods are there, add a manual comment on it with header : "human comment, strictly to be followed and not be edited". then ask ai to implement that method
   3. make sure to use existing structs and objects already in place, dont let ai reinvent same thing in a new way which will lead to chaos later.
4. Start execution
   1. Prompt to solve each subtask, directed, crisp, restricted prompt
   2. check whether AI reply actually implemented what you asked for. AI models will sometimes swap your chosen algorithm for a different one, or add unnecessary abstractions you didn't ask for. Catch these deviations early and course-correct before building on top of them.
   3. Replan when needed:
      1. data model maybe is more complex
      2. new hint from interviewer
      3. new perf constraint

Tips

1. A short "be concise" or "minimal comments" in your prompt goes a long way.
2. Your prompts should reference the actual codebase. Use the class names, method signatures, and data structures you learned during orientation : It produces better AI output, and it signals to the interviewer that you actually
3. small fixes/changes that human doing time is < AI prompting+doing time : do those urself
4. Manually Handle the parts where the approach itself is the hard part, where choosing the wrong data structure or missing an edge case would cost you significant time later.
5. Run the code after every meaningful AI generation.
6. "almost right" trap: When AI output is 90% correct, there's a strong temptation to manually patch the remaining 10% line by line. This is slower than reprompting with a clearer request, and it produces messy code that's half AI-generated and half hand-edited. If the output missed the mark, ask again properly rather than surgically fixing what you got.
7. Reprompting with more specificity or just writing it yourself is almost always faster than switching context to a different model mid-interview.
8. nerfed AI : interview AI feeling noticeably worse than state of the art models, giving nudges rather than solutions, might not point out bugs directly, give cryptic or incomplete responses, or refuse to help with certain types of requests.
9. for open ended** tests, write tests fitst : TDD.**
10. type check : each language has a type checker , use it. Run it after every meaningful change. make sure AI doesnt false-fix e.g any in ts, catch exp.
11. NEVER SKIP TESTING
12. *For heuristic-based search (A), ask the AI to generate a harness to validate the heuristic.*\* The AI is much better at writing heuristics than verifying them. A small adversarial test set is a high-leverage prompt.
13. Graph qs :
    1. verify urself the data structure, problem , possible solution in mind. Prompt AI with the data structure adheration, optionally with the algorithm
    2. print a small graph during construction. ensure input is correctly formed
