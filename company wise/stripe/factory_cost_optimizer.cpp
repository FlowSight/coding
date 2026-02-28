Factory Cost Optimizer
The Problem
You need to build a system to find the cheapest way to make a product. The product is made in steps (stages). For each step, you can choose from several factories. Each factory has:

A building cost.
A location (position) on a railway line.
Your goal is to pick exactly one factory for each step. You want to make the total cost as low as possible.

Total cost includes:

The cost to build at the factory.
The cost to move goods between factories (transportation).
The interview has four parts:

Simple Selection: Find the lowest cost if moving goods is free.
Adding Moving Costs: Add costs based on distance between factories.
Many Stages: Make the code work for any number of steps (N stages).
Skip a Step: Find the lowest cost if you must skip exactly one stage.
How the Input Looks
You get a list of production stages. Each stage is a list of factory choices.

# Each choice: [building_cost, position]
stages = [
    [[10, 0], [20, 5], [35, 2]],   # Stage 0: 3 choices
    [[35, 1], [50, 3], [25, 0]],   # Stage 1: 3 choices
    [[30, 4], [5, 2], [40, 0]]     # Stage 2: 3 choices
]
How to Calculate Cost
Total Cost = (Sum of building costs) + (Sum of transportation costs)

Transportation cost is the distance between two stages. Formula: |position_current - position_next|

Part 1: Simple Selection (No Moving Cost)
The Task
Write a function find_minimum_cost(stages). Assume all factories are at the same place. This means transportation cost is zero. You only care about building costs.

Example
Input:

stages = [
    [[10, 0], [20, 0], [35, 0]],   # Stage 0
    [[35, 0], [50, 0], [25, 0]],   # Stage 1
    [[30, 0], [5, 0], [40, 0]]     # Stage 2
]
Output:

find_minimum_cost(stages) == 40
# Math:
# Stage 0: Lowest is 10
# Stage 1: Lowest is 25
# Stage 2: Lowest is 5
# Total: 10 + 25 + 5 = 40
Goal
Pick one factory from each stage.
Find the lowest total building cost.
The code should work for any number of choices per stage.
Part 2: Adding Moving Costs
The Task
Now, include transportation costs. Factories are at different places. Moving goods from stage i to stage i+1 costs money equal to the distance between them.

Example
Input:

stages = [
    [[100, 2], [50, 0], [30, 1]],    # Stage 0
    [[100, 1], [20, 2], [10, 5]],    # Stage 1
    [[10, 1], [12, 1], [5, 3]]       # Stage 2
]
Output:

find_minimum_cost(stages) == 51
# Best choice:
# Stage 0: [30, 1] - cost: 30, pos: 1
# Stage 1: [10, 5] - cost: 10, pos: 5
# Stage 2: [5, 3]  - cost: 5,  pos: 3
# Build cost: 30 + 10 + 5 = 45
# Move cost: |1-5| + |5-3| = 4 + 2 = 6
# Total: 45 + 6 = 51
Goal
Total Cost = building cost + moving cost.
Moving cost = |position_1 - position_2|.
Find the mix of factories that gives the lowest total.
Questions to Ask the Interviewer
Are positions always positive numbers?
Can two factories be at the same spot?
Is there a limit to how many factories are in one stage?
Part 3: Handling Many Stages
The Task
Make your solution work for any number of stages. You cannot write fixed loops (like one loop for stage 0, one for stage 1, etc.) because you don't know how many stages there will be.

Example
Input:

# 5 production stages
stages = [
    [[10, 0], [20, 2]],
    [[15, 1], [25, 3], [35, 0]],
    [[30, 2], [40, 1]],
    [[5, 0], [15, 2]],
    [[20, 1], [10, 3], [25, 0]]
]
Output:

find_minimum_cost(stages)  # Returns the lowest total cost
Goal
Handle N stages (not just 3).
Handle different numbers of factories per stage.
Keep the code fast enough to run reasonably well.
Part 4: Skipping a Step
The Task
New rule: You must skip exactly one stage. When you skip a stage, calculate the moving cost between the stage before the gap and the stage after the gap.

Example
Input:

stages = [
    [[10, 0], [20, 2]],    # Stage 0
    [[100, 5]],            # Stage 1 - very expensive, maybe skip this?
    [[15, 1], [25, 3]],    # Stage 2
    [[5, 2], [15, 0]]      # Stage 3
]
Output:

find_minimum_cost_skip_one(stages) == 32
# Best Plan: Skip Stage 1
# Pick: [10, 0] -> skip -> [15, 1] -> [5, 2]
# Build cost: 10 + 15 + 5 = 30
# Move cost: |0-1| + |1-2| = 1 + 1 = 2
# Total: 32
Goal
Skip exactly one stage.
Calculate distance across the gap.
Try skipping every possible stage to find the best option.
Questions to Ask the Interviewer
Can I skip the very first or very last stage? (Usually yes).
What if there are only 2 stages? (If you skip one, there is only one left, so moving cost is 0).
How to Solve It
Part 1 Solution: Greedy Approach
Plan: For every stage, find the cheapest factory. Add all those cheap costs together. Since there is no moving cost, picking the cheapest local option is always the best global option.

Time Complexity: O(N × M) (N is stages, M is factories per stage). Space Complexity: O(1).

Code:

def find_minimum_cost(stages):
    total = 0
    for stage in stages:
        min_cost = float('inf')
        for factory in stage:
            building_cost = factory[0]
            # Find the lowest cost in this stage
            min_cost = min(min_cost, building_cost)
        total += min_cost
    return total
Things to Watch Out For:

The list of stages is empty.
A stage has only one factory.
All factories cost the same.
Part 2 Solution: Nested Loops
Plan: Use loops to check every possible combination of factories. Calculate the cost for each combination. Keep track of the lowest one.

Time Complexity: O(M^3) (for 3 stages). Space Complexity: O(1).

Code:

def find_minimum_cost(stages):
    min_total = float('inf')

    # check all combinations (3 stages)
    for f0 in stages[0]:
        for f1 in stages[1]:
            for f2 in stages[2]:
                # Add building costs
                building = f0[0] + f1[0] + f2[0]

                # Add moving costs
                transport = abs(f0[1] - f1[1]) + abs(f1[1] - f2[1])

                total = building + transport
                min_total = min(min_total, total)

    return min_total
Speed Tip: If the building cost alone is already higher than your best total so far, stop checking that combination.

Part 3 Solution: Recursion or DP
Plan: Use Backtracking (recursion). This lets you handle any number of stages. You pick a factory, then call the function for the next stage, passing along the current cost and position.

Time Complexity: O(M^N). Space Complexity: O(N) (for recursion memory).

Code (Backtracking):

def find_minimum_cost(stages):
    n = len(stages)
    min_cost = [float('inf')]

    def backtrack(stage_idx, current_cost, prev_position):
        # Base case: we finished all stages
        if stage_idx == n:
            min_cost[0] = min(min_cost[0], current_cost)
            return

        # Stop early if cost is already too high
        if current_cost >= min_cost[0]:
            return

        # Try every factory in the current stage
        for factory in stages[stage_idx]:
            building_cost, position = factory[0], factory[1]

            # Calculate move cost (0 for the first stage)
            if stage_idx == 0:
                transport = 0
            else:
                transport = abs(position - prev_position)

            new_cost = current_cost + building_cost + transport
            backtrack(stage_idx + 1, new_cost, position)

    backtrack(0, 0, 0)
    return min_cost[0]
Alternative: Dynamic Programming (DP)

DP is faster for large inputs. dp[i][j] = the lowest cost to finish stage i using factory j.

Code (DP):

def find_minimum_cost_dp(stages):
    n = len(stages)
    if n == 0:
        return 0

    # Start with the costs of the first stage
    prev_dp = {}
    for j, factory in enumerate(stages[0]):
        prev_dp[(0, j)] = factory[0]

    # Go through the rest of the stages
    for i in range(1, n):
        curr_dp = {}
        for j, curr_factory in enumerate(stages[i]):
            curr_cost, curr_pos = curr_factory[0], curr_factory[1]
            min_cost = float('inf')

            # Check paths from the previous stage to this one
            for k, prev_factory in enumerate(stages[i-1]):
                prev_pos = prev_factory[1]
                transport = abs(curr_pos - prev_pos)
                total = prev_dp[(i-1, k)] + curr_cost + transport
                min_cost = min(min_cost, total)

            curr_dp[(i, j)] = min_cost
        prev_dp = curr_dp

    # The answer is the lowest cost in the final stage
    return min(prev_dp.values())
Time Complexity (DP): O(N × M^2). This is much better than backtracking.

Part 4 Solution: Try All Skips
Plan: Loop through the stages. For each loop, temporarily remove one stage. Calculate the minimum cost for the remaining list (using the logic from Part 3). Pick the skip that results in the lowest overall cost.

Time Complexity: O(N × M^(N-1)). Space Complexity: O(N).

Code:

def find_minimum_cost_skip_one(stages):
    n = len(stages)
    if n <= 1:
        return 0  # Nothing to skip

    def compute_min_cost(active_stages):
        """Find min cost for a specific list of stages."""
        if not active_stages:
            return 0

        min_cost = [float('inf')]

        def backtrack(idx, current_cost, prev_position):
            if idx == len(active_stages):
                min_cost[0] = min(min_cost[0], current_cost)
                return

            if current_cost >= min_cost[0]:
                return

            for factory in active_stages[idx]:
                building_cost, position = factory[0], factory[1]
                # If idx is 0, transport is 0. Else, calc distance.
                transport = 0 if idx == 0 else abs(position - prev_position)
                backtrack(idx + 1, current_cost + building_cost + transport, position)

        backtrack(0, 0, 0)
        return min_cost[0]

    global_min = float('inf')

    # Try skipping each stage one by one
    for skip_idx in range(n):
        # Make a new list without the skipped stage
        active_stages = stages[:skip_idx] + stages[skip_idx + 1:]
        cost = compute_min_cost(active_stages)
        global_min = min(global_min, cost)

    return global_min
Speed Tip: Instead of calculating from scratch every time, you can pre-calculate costs from the start (prefix) and costs from the end (suffix). Then you just combine them.

Extra Discussion
Can Part 1 be faster than O(N × M)?
Question: Is there a way to solve Part 1 without checking every single factory?

Answer:

No. You have to look at every number to know which one is the smallest. O(N × M) is the best possible speed.
Sorting doesn't help because sorting takes O(M log M), which is slower than just looking at them once O(M).
This is a good topic to show you understand "Time Complexity".