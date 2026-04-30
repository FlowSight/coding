# Airbnb — Technical Front Screen (Coding)
**Date**: April 29, 2025  
**Role**: Senior Software Engineer  
**Interviewer**: Anshu Sharma  
**Duration**: ~45 min  
**Format**: 1 problem + follow-ups (stated upfront by interviewer), then Q&A  
**Status**: Waiting  
**Confidence**: 8.5/10

---

## Problem: Maximum Value from Non-Overlapping Experiences

Given a list of experiences, each with a start time, end time, and value. Pick a subset of experiences such that no two overlap and the total value is maximized.

> Rewording of LC 1235 — Maximum Profit in Job Scheduling

### Clarifying Questions Asked
- Can one experience ending at time T and another starting at time T be both picked? → Yes
- Are values integers? → Yes

---

## Approach

- Explained sweep-line / DP approach (sort by time, track max profit at each time point)
- Interviewer had trouble understanding initially — went back and forth
- Did a dry run / simulation with the given example after ~20 min → interviewer understood
- Shared time and space complexity

---

## Coding

- Got consent to code after explanation
- Wrote the solution, ran it against the provided example — output matched
- Interviewer provided 2 more test cases — both passed
- Asked if I should come up with my own corner cases / test cases — they said it's OK

---

## Follow-up 1: int → double

**Q**: What if the integer values (start, end, profit) are changed to float/double?

**My answer**:
- Change every field to double — start, end, profit
- All DP state arrays and the ordered set should be double
- Only the vector of indices stays as integer
- Time and space complexity do not change

**Q**: Will time/space complexity change?

**My answer**: No, stays the same.

---

## Follow-up 2: Optimization

**Q**: Is it possible to optimize the time and space complexity?

**My answer**:
- Can sort the array directly instead of using a sorted set → eliminates the `set` overhead
- But sorting is still O(n log n), so time complexity asymptotically unchanged
- Space still needed for the index array and DP array → space asymptotically unchanged either
- Could not think of further optimization beyond that

Interviewer said: "That is all I had, all the best, we had a good discussion."

---

## Reflection

- **What went well**: Clarifying questions, dry run convinced interviewer, code ran correctly on all test cases, handled follow-ups cleanly
- **What could improve**: ~20 min from problem shared to explanation accepted (including clarifications, back-and-forth, dry run) — reasonable for a DP problem, but could try leading with dry run earlier to speed up buy-in
- **Missed opportunity**: Could have mentioned that replacing `unordered_map` with sort + binary search is more cache-friendly (constant factor improvement), even if asymptotic complexity is same
