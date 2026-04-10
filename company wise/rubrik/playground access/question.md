# Playground Access (Team-Exclusive, Bounded Concurrency)

## Problem
There is a playground that can be accessed by only one team at a time, with a maximum of **10 players** allowed concurrently. Multiple players from different teams may attempt to access the playground simultaneously.

Design a system to assign players to the playground while enforcing these constraints.

## Constraints
1. **Team-exclusive**: Only one team can occupy the playground at any time (no mixing)
2. **Bounded capacity**: At most 10 players inside at once
3. **Concurrent arrivals**: Players from different teams arrive in parallel
4. **No starvation**: Every player eventually gets access (follow-up focus)

## Key Discussion Points / Approaches

### Approach 1: Mutex + CV (basic, can starve)
- Track `currentTeam` and `currentCount`
- Players check: if playground empty or same team and count < 10 → enter, else wait on CV
- **Problem**: A steady stream of Team A players can indefinitely block Team B (starvation)

### Approach 2: FIFO Queue (fair, avoids starvation)
- Maintain a **FIFO wait-queue** of arriving players
- Only admit the next batch of same-team players from the head of the queue
- When playground empties, admit the next group from the front
- **Prevents starvation** since arrival order is preserved
- Trade-off: slightly lower throughput since you can't skip ahead

### Approach 3: Turn-based / Round-Robin Teams
- Alternate turns between teams: Team A gets a turn → drains → Team B gets a turn → drains
- Simple but unfair if one team has far more players

### Approach 4: Timed Lease / Max-Occupancy-Time
- Let each team hold the playground for at most T seconds (or K player-turns)
- After the lease expires, force a team switch even if more players are waiting
- Combines throughput with bounded wait times

## Follow-up Questions They May Ask
- How do you handle a new team C arriving while A is playing and B is waiting?
- What if a player crashes inside — how do you reclaim the slot?
- Can you use a semaphore instead of a CV for the capacity bound?
- How would you unit-test starvation freedom?

## Similar Problem in This Repo
- [political bathroom](../political%20bathroom/question.md) — same pattern (party-exclusive bathroom, capacity 3)
