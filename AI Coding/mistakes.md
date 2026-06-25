1. Problem-solving and approach
   * Pasting the raw problem into AI without forming your own plan first, then building on whatever comes back
   * Following the AI into architectural decisions that should be yours to make
   * Chasing an AI-suggested rewrite when the model doesn't know the answer, which feels like momentum but is actually the model flailing
2. coontrol over AI
   1. Accepting AI architectural suggestions without evaluating them (it proposes a BaseProcessor superclass; you add it without asking whether it actually makes sense)
   2. Treating AI output as the solution rather than a draft to review and accept or reject
   3. Not redirecting when the AI drifts into a different approach than the one you planned
3. Verification
   * Not running code after each generation, then discovering cascading failures at the end with no time left to fix them
   * Skipping the line-by-line read because the generated code looked right at a glance
   * Skipping tests because of time pressure, which almost always costs more time than it saves
4. Communication
   * Going silent for long stretches while prompting, leaving the interviewer with nothing to evaluate
   * Narrating after the fact instead of before ("I just asked the AI to..." vs. "I'm going to ask the AI to...")
   * Not explaining when you pivot ("the AI suggested DFS so I'm using DFS now") without saying whether you actually agree with it
