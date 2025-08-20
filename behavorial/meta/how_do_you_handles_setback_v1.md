- The blockers can be of Unpredictable external or Unpredictable internal.
- My  order of line of defence is as below:
    - did any other team face this earlier
    - Can we buy time? have this blocker and still move around to reach our goal and come back?
    - aboe two solves >70%. If I cant buy time, and its a totally unforseen problem I start evaluating the unknowns. 
        - If its my teams area, I ask few qs to myself
            1. Why did this happen?
            2. How could I stop this from happening.
            3. What can I do to stop this from happening in future.
        - Else, I recognize its a dependency issue. I do following:
            - Take help of SMEs
            - Recognize this dependency failure and improve our teams learning bank to stop repeatable failure.

    - ****Give time mobile app blocking example****
    -   
======end====

- focus on learnings
- show resilience
- signals
    - Resilience — you don’t panic.

    - Leadership — you organize a response, not just your own work.

    - Learning mindset — you don’t just patch and move on.

    - Transparency 

- talk about below :

- 4 types of blockers
    - predictable External:
        - find pattern
        - e.g.
            - pipeline failure
            - testing infra issue
        - SOLUTION:
            - parallelize testing multiple hypothesis 
            - expect a blocker always, have preprovision systems earlier, lock them
                , use feature branch dont merge from master as master can become buggy
    Unpredictable External:
        - icm/bug spike
        - reprioritization from leadership
        - compliance blockers
        - SOLTION:
            - same solution as above,
            - except when a piece can not be worked on completely, pick a future piece to make progress there, maybe from next release items.
    predicatable internal:
        - bugs missed in PR
        - ETA for item usually takes 30% extra time
        - SOLUTION:
            - estimate judiciously and levergae more eyes + AI in code reviews.
    Unpredictable internal:
        - unknown PR comment
        - sudden capacity lacking of teammates