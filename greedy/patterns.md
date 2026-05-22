# Greedy Patterns

## 1. Interval Scheduling
- Sort by end time, greedily pick non-overlapping intervals
- Variants: minimum intervals to cover range, merge overlapping intervals
- Use: meeting rooms, non-overlapping intervals, minimum platforms

## 2. Activity Selection / Sorting by Key
- Sort by some criterion, process greedily
- Proof technique: exchange argument — show swapping any element for greedy's choice doesn't improve
- Use: job scheduling, assign cookies, boats to save people

## 3. Huffman / Priority Queue Greedy
- Always process the minimum (or maximum) element first
- Use min-heap to efficiently get next smallest
- Use: Huffman coding, connect sticks (minimize cost), meeting rooms II

## 4. Two-Pointer Greedy
- Shrink/expand window based on local decisions
- Use: container with most water, trapping rain water, two-sum sorted

## 5. Jump Game Pattern
- Track farthest reachable position as you scan
- Greedily extend reach; count jumps when forced
- Use: jump game I/II, video stitching, minimum taps to water garden

## 6. Gas Station / Circular Greedy
- If total resource ≥ total cost, solution exists
- Track running deficit; reset start when deficit goes negative
- Use: gas station, circular tour

## 7. Task Scheduling with Deadlines
- Sort by deadline, use heap to drop lowest-profit task when overloaded
- Or sort by profit descending, assign to latest available slot
- Use: job sequencing, course schedule III, IPO

## 8. Digit Construction
- Build answer digit by digit (largest/smallest first)
- Monotone stack for "remove k digits" type problems
- Use: largest number, remove K digits, smallest subsequence

## When Greedy Works
- Optimal substructure + greedy choice property
- If local optimal → global optimal (prove via exchange argument)
- If not sure: check if DP gives same answer; if greedy fails on a counterexample, switch to DP
