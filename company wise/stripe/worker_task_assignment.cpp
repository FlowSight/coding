Assigning Tasks to Workers
Problem Summary
You need to build a system to give tasks to support workers. The rules for who gets which task change as we add more features.

The problem has four parts. Each part adds a new rule:

Balancing Workload: Give the task to the worker who is least busy.
Matching Skills: Only give tasks to workers who have the right skills.
Client History: Try to keep the same worker for the same client (Account Affinity).
Worker Availability: Handle situations where workers go offline.
Data Format
You will get a list of workers and a list of tasks.

Workers: A list of names (Part 1) or objects with details (Parts 2-4).

Tasks: A list of objects with details about the work.

# Part 1 Example
workers = ["alice", "bob", "charlie"]
tasks = [
    {"id": "task1", "duration": 5},
    {"id": "task2", "duration": 3},
    {"id": "task3", "duration": 7}
]
Expected Output
Return a list that shows which worker got which task:

[
    {"taskId": "task1", "worker": "alice"},
    {"taskId": "task2", "worker": "bob"},
    ...
]
Step 1: Balancing the Workload
The Goal
Write a function assign_tasks(workers, tasks). You must give each task to the worker who currently has the lowest total workload.

Rules:

Go through the tasks one by one, in order.
Give the task to the worker with the minimum total work time right now.
Tie-breaker: If two workers have the same workload, give it to the one who appears earlier in the workers list.
When a worker gets a task, add that task's duration to their total workload.
Example Case
Input:

workers = ["alice", "bob", "charlie"]
tasks = [
    {"id": "task1", "duration": 5},
    {"id": "task2", "duration": 3},
    {"id": "task3", "duration": 7},
    {"id": "task4", "duration": 2},
    {"id": "task5", "duration": 4}
]
Output:

[
    {"taskId": "task1", "worker": "alice"},    # everyone is at 0, alice is first
    {"taskId": "task2", "worker": "bob"},      # bob and charlie are at 0, bob is first
    {"taskId": "task3", "worker": "charlie"},  # charlie is at 0 (lowest)
    {"taskId": "task4", "worker": "bob"},      # bob is at 3 (lowest)
    {"taskId": "task5", "worker": "alice"}     # alice and bob are tied at 5, alice is first
]
What happened:

Start: Everyone has 0 workload. task1 goes to alice.
alice: 5, bob: 0, charlie: 0. task2 goes to bob.
alice: 5, bob: 3, charlie: 0. task3 goes to charlie.
alice: 5, bob: 3, charlie: 7. task4 goes to bob (3 is the minimum).
alice: 5, bob: 5, charlie: 7. task5 goes to alice (tied with bob, but she is first).
Key Requirements
Handle tasks one by one.
Keep track of total work time for each worker.
Use the list order to break ties.
Return the assignments in the same order as the tasks.
Step 2: Matching Skills
The Goal
Now, workers have specific skills (specialties). Tasks require specific skills. You can only give a task to a worker if they have the right skill.

First, look for workers who can do the job. Then, pick the one with the least workload (using the same tie-breaker rules as Step 1).

Example Case
Input:

workers = [
    {"name": "alice", "specialty": "billing"},
    {"name": "bob", "specialty": "technical"},
    {"name": "charlie", "specialty": "billing"},
    {"name": "diana", "specialty": "technical"}
]

tasks = [
    {"id": "task1", "duration": 5, "requiredSpecialties": ["billing"]},
    {"id": "task2", "duration": 3, "requiredSpecialties": ["technical"]},
    {"id": "task3", "duration": 7, "requiredSpecialties": ["billing", "technical"]},
    {"id": "task4", "duration": 2, "requiredSpecialties": ["billing"]},
    {"id": "task5", "duration": 4, "requiredSpecialties": ["technical"]}
]
Output:

[
    {"taskId": "task1", "worker": "alice"},    # billing group: alice(0), charlie(0) → alice is first
    {"taskId": "task2", "worker": "bob"},      # technical group: bob(0), diana(0) → bob is first
    {"taskId": "task3", "worker": "charlie"},  # both groups eligible: charlie(0) and diana(0) are lowest → charlie is first
    {"taskId": "task4", "worker": "alice"},    # billing group: alice(5), charlie(7) → alice is lower
    {"taskId": "task5", "worker": "diana"}     # technical group: bob(3), diana(0) → diana is lower
]
Key Requirements
Filter the list of workers to find only those with the right skill.
If no one matches the skill, skip the task.
Once you have the list of skilled workers, pick the one with the lowest workload.
Step 3: Client History (Affinity)
The Goal
We want to send tasks from the same client ("account") to the same worker. If a worker has helped a client before, they should get priority for new tasks from that client.

Priority Checklist:

First, find workers with the right skill.
From that group, look for workers who have helped this accountId before.
If you find them, pick the one with the least workload.
If no one has helped this client before, just pick the least busy worker from the skilled group.
Always use the list order as the final tie-breaker.
Example Case
Input:

workers = [
    {"name": "alice", "specialty": "billing"},
    {"name": "bob", "specialty": "billing"},
    {"name": "charlie", "specialty": "billing"}
]

tasks = [
    {"id": "task1", "duration": 5, "requiredSpecialties": ["billing"], "accountId": "acme"},
    {"id": "task2", "duration": 3, "requiredSpecialties": ["billing"], "accountId": "globex"},
    {"id": "task3", "duration": 7, "requiredSpecialties": ["billing"], "accountId": "acme"},
    {"id": "task4", "duration": 2, "requiredSpecialties": ["billing"], "accountId": "acme"},
    {"id": "task5", "duration": 4, "requiredSpecialties": ["billing"], "accountId": "globex"}
]
Output:

[
    {"taskId": "task1", "worker": "alice"},    # No history yet. All at 0. Alice is first.
    {"taskId": "task2", "worker": "bob"},      # No history for globex. Bob is next available at 0.
    {"taskId": "task3", "worker": "alice"},    # Alice helped "acme" before. She gets priority over empty workers.
    {"taskId": "task4", "worker": "alice"},    # Alice still has "acme" history.
    {"taskId": "task5", "worker": "bob"}       # Bob helped "globex" before.
]
What happened:

task1 (acme): No history. alice gets it because she is first in the list.
task2 (globex): No history. bob gets it (he is at 0, alice is busy).
task3 (acme): alice helped acme in task 1. Even though she is busy, she gets priority.
task4 (acme): alice keeps the acme account.
task5 (globex): bob helped globex in task 2. He gets priority.
Key Requirements
Remember which accounts each worker has helped.
Give priority to "affinity" (history) over "low workload".
If multiple people have history, pick the least busy one.
If no one has history, go back to the logic from Step 2.
Step 4: Handling Offline Workers
The Goal
Workers might stop working (go offline) at any time. The system must handle this.

New Data: You get a list called offlineEvents.

offlineEvents = [
    {"worker": "alice", "afterTaskIndex": 2}  # alice quits after task #2 is assigned
]
Rules:

If a worker is offline, they cannot take new tasks.
We still remember their history (in case they come back, though we don't need to implement them coming back right now).
You must give the work to the remaining available workers.
Example Case
Input:

workers = [
    {"name": "alice", "specialty": "billing"},
    {"name": "bob", "specialty": "billing"},
    {"name": "charlie", "specialty": "billing"}
]

tasks = [
    {"id": "task1", "duration": 5, "requiredSpecialties": ["billing"], "accountId": "acme"},
    {"id": "task2", "duration": 3, "requiredSpecialties": ["billing"], "accountId": "globex"},
    {"id": "task3", "duration": 7, "requiredSpecialties": ["billing"], "accountId": "acme"},
    {"id": "task4", "duration": 2, "requiredSpecialties": ["billing"], "accountId": "acme"},
    {"id": "task5", "duration": 4, "requiredSpecialties": ["billing"], "accountId": "globex"}
]

offlineEvents = [
    {"worker": "alice", "afterTaskIndex": 2}
]
Output:

[
    {"taskId": "task1", "worker": "alice"},    # alice gets acme (task index 0)
    {"taskId": "task2", "worker": "bob"},      # bob gets globex (task index 1)
    {"taskId": "task3", "worker": "alice"},    # alice has acme history (task index 2)
    # Alice goes offline here!
    {"taskId": "task4", "worker": "charlie"},  # Alice is gone. Charlie is the best remaining option.
    {"taskId": "task5", "worker": "bob"}       # Bob has globex history.
]
Key Requirements
Track who is online and who is offline.
Process the "offline events" right after the specific task index is finished.
Skip offline workers when choosing someone for a task.
How to Solve It
Solution for Step 1 (Load Balancing)
Strategy:

Create a dictionary to store the current workload for every worker.
Loop through every task.
Inside the loop, check every worker to see who has the lowest number in the dictionary.
If there is a tie, pick the one who appeared first in the original list.
Add the task time to that worker's total.
Time Complexity: O(t × w) — We check every worker for every task. Space Complexity: O(w) — To store the workload scores.

Code:

def assign_tasks(workers, tasks):
    workload = {worker: 0 for worker in workers}
    assignments = []

    for task in tasks:
        # Find worker with lowest workload (first in list breaks ties)
        min_worker = None
        min_load = float('inf')

        for worker in workers:
            if workload[worker] < min_load:
                min_load = workload[worker]
                min_worker = worker

        # Assign task and add time to workload
        assignments.append({"taskId": task["id"], "worker": min_worker})
        workload[min_worker] += task["duration"]

    return assignments
Faster Approach (Using a Heap): You can use a Min-Heap to find the lowest number faster.

import heapq

def assign_tasks(workers, tasks):
    # Heap stores: (workload, worker_index, worker_name)
    heap = [(0, i, worker) for i, worker in enumerate(workers)]
    heapq.heapify(heap)

    assignments = []

    for task in tasks:
        workload, idx, worker = heapq.heappop(heap)
        assignments.append({"taskId": task["id"], "worker": worker})
        heapq.heappush(heap, (workload + task["duration"], idx, worker))

    return assignments
Time Complexity with Heap: O(t × log w)

Solution for Step 2 (Skill Matching)
Strategy:

Group workers by their specialty so we can find them quickly.
For each task, look at the required specialties. Make a list of workers who match.
From that list, find the one with the lowest workload (using the Step 1 logic).
Data Structures:

workload: Dictionary to track time.
specialty_map: Dictionary where Key = Skill, Value = List of Workers.
worker_index: To remember the original order for tie-breaking.
Code:

def assign_tasks(workers, tasks):
    # Setup lookups
    workload = {w["name"]: 0 for w in workers}
    worker_index = {w["name"]: i for i, w in enumerate(workers)}
    specialty_map = {}

    for w in workers:
        specialty = w["specialty"]
        if specialty not in specialty_map:
            specialty_map[specialty] = []
        specialty_map[specialty].append(w["name"])

    assignments = []

    for task in tasks:
        # Find workers who have the right skill
        eligible = []
        for specialty in task["requiredSpecialties"]:
            if specialty in specialty_map:
                eligible.extend(specialty_map[specialty])
        eligible = list(set(eligible))  # Remove duplicates

        if not eligible:
            continue  # Nobody can do this task

        # Find the best worker among the eligible ones
        best_worker = min(
            eligible,
            key=lambda w: (workload[w], worker_index[w])
        )

        assignments.append({"taskId": task["id"], "worker": best_worker})
        workload[best_worker] += task["duration"]

    return assignments
Time Complexity: O(t × (s + w)) where s is the average number of skills per task.

Solution for Step 3 (Account History)
Strategy:

Add a new dictionary called account_history to track which accounts a worker has touched.
For each task, find the skilled workers.
Split those skilled workers into two groups:
Group A: Have helped this account before.
Group B: Have not helped this account.
If Group A has people, pick the best one from Group A. If Group A is empty, pick from Group B.
Code:

def assign_tasks(workers, tasks):
    workload = {w["name"]: 0 for w in workers}
    worker_index = {w["name"]: i for i, w in enumerate(workers)}
    specialty_map = {}
    account_history = {w["name"]: set() for w in workers}

    for w in workers:
        specialty = w["specialty"]
        if specialty not in specialty_map:
            specialty_map[specialty] = []
        specialty_map[specialty].append(w["name"])

    assignments = []

    for task in tasks:
        # Find skilled workers
        eligible = set()
        for specialty in task["requiredSpecialties"]:
            if specialty in specialty_map:
                eligible.update(specialty_map[specialty])

        if not eligible:
            continue

        account_id = task["accountId"]

        # Split into affinity group and non-affinity group
        with_affinity = [w for w in eligible if account_id in account_history[w]]
        without_affinity = [w for w in eligible if account_id not in account_history[w]]

        # Prefer affinity group
        candidates = with_affinity if with_affinity else without_affinity

        best_worker = min(
            candidates,
            key=lambda w: (workload[w], worker_index[w])
        )

        # Update data
        assignments.append({"taskId": task["id"], "worker": best_worker})
        workload[best_worker] += task["duration"]
        account_history[best_worker].add(account_id)

    return assignments
Time Complexity: O(t × w)

Solution for Step 4 (Offline Handling)
Strategy:

Keep a set of available workers.
Organize the offlineEvents so we know exactly which task index triggers a worker leaving.
Inside the loop, after assigning a task, check if anyone needs to be removed from the available set.
When finding eligible workers, check if they are in the available set.
Code:

def assign_tasks(workers, tasks, offlineEvents):
    workload = {w["name"]: 0 for w in workers}
    worker_index = {w["name"]: i for i, w in enumerate(workers)}
    specialty_map = {}
    account_history = {w["name"]: set() for w in workers}
    available = {w["name"] for w in workers}

    # Prepare offline events lookup
    offline_at = {}
    for event in offlineEvents:
        idx = event["afterTaskIndex"]
        if idx not in offline_at:
            offline_at[idx] = []
        offline_at[idx].append(event["worker"])

    for w in workers:
        specialty = w["specialty"]
        if specialty not in specialty_map:
            specialty_map[specialty] = []
        specialty_map[specialty].append(w["name"])

    assignments = []

    for task_idx, task in enumerate(tasks):
        # Find skilled AND available workers
        eligible = set()
        for specialty in task["requiredSpecialties"]:
            if specialty in specialty_map:
                for w in specialty_map[specialty]:
                    if w in available:
                        eligible.add(w)

        if not eligible:
            continue

        account_id = task["accountId"]

        # Split by affinity
        with_affinity = [w for w in eligible if account_id in account_history[w]]
        without_affinity = [w for w in eligible if account_id not in account_history[w]]

        candidates = with_affinity if with_affinity else without_affinity

        best_worker = min(
            candidates,
            key=lambda w: (workload[w], worker_index[w])
        )

        # Update data
        assignments.append({"taskId": task["id"], "worker": best_worker})
        workload[best_worker] += task["duration"]
        account_history[best_worker].add(account_id)

        # Remove workers who go offline after this task
        if task_idx in offline_at:
            for worker in offline_at[task_idx]:
                available.discard(worker)

    return assignments
Time Complexity: O(t × w + e) where e is the number of offline events.

Tricky Situations to Watch For
Empty Data: What if the worker list or task list is empty?
Solo Worker: If there is only one worker, they get everything.
Impossible Tasks: A task requires a skill that nobody has.
Total Shutdown: Everyone goes offline.
Duplicates: A worker lists the same skill twice.
Instant Tasks: Tasks with 0 duration (doesn't change workload).
Heavy Ties: Many workers have the exact same workload.
Affinity Conflict: You helped this account before, but you don't have the skill required for this specific task. (Rule: You must have the skill first).