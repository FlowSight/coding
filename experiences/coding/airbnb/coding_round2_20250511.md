# Airbnb — Coding Round 2 (Onsite)
**Date**: May 8, 2025  
**Role**: Senior Software Engineer  
**Duration**: ~45 min  
**Format**: 1 problem + optimization ask  
**Status**: Waiting  
**Confidence**: 4/10  

---

## Problem: Shortest Unique Identifier of Each String

Given a list of strings, find the identifier of each string. The identifier is the shortest substring that is unique to that string and not present in any other strings.

---

## Approach 1: Brute Force (Proposed First)

- Try all substrings of length 1 across all strings, check uniqueness
- Then length 2, length 3, ..., up to length n
- For each string, the first length where a unique substring is found becomes its identifier

### Interviewer Response
- Asked: "Should I optimize it?"
- She said: "No, it's OK, let's code it."

---

## Coding (Brute Force)

- Coded the brute force solution
- Finished at ~30 min mark
- She did NOT ask to run the brute force
- Interviewer asked: "What's the time complexity? How is it working?"
- Explained the approach
- She said it's a bit suboptimal, try to optimize
- Directly asked me to code the optimized version and run that instead

---

## Approach 2: Trie-Based (Attempted Optimization)

- Proposed putting all words in a trie
- When we see a mismatch while searching for a word, calculate a substring from there that's absent in other strings
- Interviewer said: "OK, let's code it."
- Coded it, but this was NOT the right optimization

### What Happened
- Almost ran out of time
- Interviewer gave 2 extra minutes to fix runtime bugs
- Ran it — got a runtime error immediately
- She said: "OK, I think we are done. Do you have any questions?"
- Did not run on any test case, did not verify output, no follow-up

---

## What the Right Answer Was

**Generalized Suffix Trie / Suffix Tree**

The correct optimization is to:
1. Insert all **suffixes** of every string into a trie, tagging each node with which string index it belongs to
2. For each string, walk the trie — the first node where only that string's index is marked gives the shortest unique substring
3. Time: O(n × L²) build, O(L²) per query — much better than the brute force which rechecks all strings repeatedly

The key insight missed: it's not about inserting whole words into a trie, it's about inserting **all suffixes** so every possible substring is represented in the trie.

---

## Pipeline Status

| Round | Type | Status |
|-------|------|--------|
| 1 | Coding (Technical Screen) | ✅ Hire |
| 2 | Coding (Onsite) | ❌ No Hire (likely) |
| 3 | System Design | ✅ Solid Hire |
| 4 | Project Discussion / Cross-functional | Upcoming |

---

## Reflection

- **What went well**: Proposed a working brute force quickly, coded it within 30 min
- **What went wrong**: 
  - Could not identify the suffix trie optimization under pressure
  - The trie approach I proposed (whole words, not suffixes) was incorrect
  - Runtime error on the attempted optimization code with no time to debug
  - No test cases were verified
- **Key lesson**: When the problem involves finding substrings across multiple strings, immediately think **Generalized Suffix Tree / Suffix Trie** — insert all suffixes, tag with source string index
- **No hints given**: Interviewer did not provide hints toward the suffix trie direction
- **Concern**: This round may be a negative signal given runtime error and incorrect optimization. Previous coding round was positive, so it depends on how much weight this carries vs. the remaining rounds.
