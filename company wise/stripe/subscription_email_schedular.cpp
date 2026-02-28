Subscription Email Scheduler
Problem Summary
You need to build an automated email system for a subscription service. The system sends emails to users at specific times, like when they join or when their subscription is about to end.

This interview question has three parts:

Scheduling Basics: Send emails based on a timeline.
Changing Plans: Handle users switching plans (like Silver to Gold).
Renewals: Handle users extending their subscription time.
Main Requirements
Print email notifications in order by date.
Use a flexible schedule (rules can change).
Handle many users at the same time.
Keep track of the correct subscription status.
The main challenge is writing code that works for any schedule, without hardcoding specific numbers.

Part 1: Scheduling Basics
Problem Requirements
Write a function send_emails(user_accounts, send_schedule) to create email events.

The send_schedule tells you when to send emails:

"start": Send on the day the subscription begins.
"end": Send on the day the subscription expires.
Number keys: These are days relative to the end date. For example, -15 means "15 days before the end date."
Your code must be reusable. It should work with any number, not just -15. You need to check if a key is a specific word (like "start") or a number.

Input Data
User Accounts:

[
    {
        "name": "John",
        "plan": "Silver",
        "account_date": 0,
        "duration": 30
    },
    {
        "name": "Alice",
        "plan": "Gold",
        "account_date": 1,
        "duration": 15
    }
]
Send Schedule:

{
    "start": "Welcome",
    -15: "Upcoming expiration",  # 15 days before end
    "end": "Expired"
}
Expected Output
0: [Welcome] Subscription for John (Silver)
1: [Welcome] Subscription for Alice (Gold)
1: [Upcoming expiration] Subscription for Alice (Gold)
15: [Upcoming expiration] Subscription for John (Silver)
16: [Expired] Subscription for Alice (Gold)
30: [Expired] Subscription for John (Silver)
Formatting Rules
Group emails by day number (lowest to highest).
Format: {day}: [{message_type}] Subscription for {name} ({plan})
If multiple emails happen on the same day, use separate lines.
Do not print days with no emails.
Important Logic
Flexible Schedule: Do not write code specifically for -15. Detect number keys and do the math.
Active Time: If a subscription starts on day X and lasts D days, it ends on day X+D.
Math: For a number key like -15, the date is end_date + -15.
Questions to Ask the Interviewer
Will the schedule keys always be "start", "end", or a negative number?
What if the calculated date is before the user joined?
Does the order of emails on the same day matter?
Part 2: Changing Plans
Problem Requirements
Now, update the system to handle plan changes. Users can switch plans while their subscription is active.

Send a "Changed" email on the day of the change.
Update the plan name for all future emails.
The subscription end date stays the same.
New Input Data
Plan Changes:

[
    {
        "name": "John",
        "new_plan": "Gold",
        "change_date": 5
    }
]
Example Scenario
Input:

user_accounts = [
    {"name": "John", "plan": "Silver", "account_date": 0, "duration": 30},
    {"name": "Alice", "plan": "Gold", "account_date": 1, "duration": 15}
]

plan_changes = [
    {"name": "John", "new_plan": "Gold", "change_date": 5}
]

send_schedule = {
    "start": "Welcome",
    -15: "Upcoming expiration",
    "end": "Expired"
}
Output:

0: [Welcome] Subscription for John (Silver)
1: [Welcome] Subscription for Alice (Gold)
1: [Upcoming expiration] Subscription for Alice (Gold)
5: [Changed] Subscription for John (Gold)
15: [Upcoming expiration] Subscription for John (Gold)
16: [Expired] Subscription for Alice (Gold)
30: [Expired] Subscription for John (Gold)
What Changed?
On day 5, John switched to "Gold".
On day 15 and 30, John's emails now say "Gold" instead of "Silver".
Alice is not affected.
Logic Rules
Only change the plan name. Do not change the end date.
Process changes in date order.
Changes must happen while the subscription is active.
Part 3: Handling Renewals
Problem Requirements
Add support for renewals. A user can add more time to their subscription.

Send a "Renewed" email on the renewal date.
Add the extra time to the end date.
Recalculate all future emails because the end date changed.
Note: The extra time starts after the original expiration date, not on the day they click renew.

New Input Data
The changes list can now have plan changes AND renewals.

Plan Change:

{"name": "John", "new_plan": "Gold", "change_date": 5}
Renewal:

{"name": "Alice", "extension": 15, "change_date": 3}
Example Scenario
Input:

user_accounts = [
    {"name": "John", "plan": "Silver", "account_date": 0, "duration": 30},
    {"name": "Alice", "plan": "Gold", "account_date": 1, "duration": 15}
]

changes = [
    {"name": "John", "new_plan": "Gold", "change_date": 5},
    {"name": "Alice", "extension": 15, "change_date": 3}
]

send_schedule = {
    "start": "Welcome",
    -15: "Upcoming expiration",
    "end": "Expired"
}
Output:

0: [Welcome] Subscription for John (Silver)
1: [Welcome] Subscription for Alice (Gold)
1: [Upcoming expiration] Subscription for Alice (Gold)
3: [Renewed] Subscription for Alice (Gold)
5: [Changed] Subscription for John (Gold)
15: [Upcoming expiration] Subscription for John (Gold)
16: [Upcoming expiration] Subscription for Alice (Gold)
30: [Expired] Subscription for John (Gold)
31: [Expired] Subscription for Alice (Gold)
Understanding Renewal Logic
Let's look at Alice:

Before renewal (Day 0-2):

Ends on Day 16.
"Upcoming expiration" is calculated for Day 1 (16 - 15).
"Expired" is calculated for Day 16.
On renewal (Day 3):

She adds 15 days.
New end date: 16 + 15 = 31.
Send "Renewed".
Recalculate:
Delete the pending "Expired" email on Day 16.
Create a NEW "Upcoming expiration" for Day 16 (31 - 15).
Create a NEW "Expired" for Day 31.
Result: Alice gets an "Upcoming expiration" email twice: once for the old date (Day 1) and once for the new date (Day 16).

Logic Rules
Check if the change has a new_plan (Plan Change) or extension (Renewal).
Renewals use the current plan name.
Delete old future emails that are no longer correct.
Calculate new emails based on the new end date.
Solution Strategy
Part 1: Scheduling Basics
The Plan:

Create a Dictionary (map) to hold lists of emails for each day.
Loop through every user.
Calculate their end date (account_date + duration).
Loop through the send_schedule.
If key is "start", date is account_date.
If key is "end", date is end_date.
If key is a number, date is end_date + number.
Sort the days and print.
Handling Number Keys: Do not write if key == -15. Instead, check the type or use simple logic:

for key, message_type in send_schedule.items():
    if key == "start":
        notification_date = account_date
    elif key == "end":
        notification_date = end_date
    else:
        # It is a number
        offset = int(key)
        notification_date = end_date + offset
Time Complexity: O(U × S + D log D) (U=Users, S=Schedule items, D=Days with emails). Space Complexity: O(D × E) (E=Emails per day).

Code Example:

def send_emails(user_accounts, send_schedule):
    # Map days to a list of email objects
    emails_by_day = {}

    for user in user_accounts:
        name = user["name"]
        plan = user["plan"]
        account_date = user["account_date"]
        duration = user["duration"]
        end_date = account_date + duration

        for key, message_type in send_schedule.items():
            if key == "start":
                notification_date = account_date
            elif key == "end":
                notification_date = end_date
            else:
                # Handle number keys (like -15)
                offset = int(key)
                notification_date = end_date + offset

            if notification_date not in emails_by_day:
                emails_by_day[notification_date] = []

            emails_by_day[notification_date].append({
                "name": name,
                "plan": plan,
                "message_type": message_type
            })

    # Sort by day and print
    for day in sorted(emails_by_day.keys()):
        for email in emails_by_day[day]:
            print(f"{day}: [{email['message_type']}] Subscription for {email['name']} ({email['plan']})")
Part 2: Changing Plans Solution
The Plan:

Create a map to look up plan changes quickly: (user, date) -> new_plan.
Keep track of every user's current plan.
Put ALL events (emails and plan changes) into one big list.
Sort the list by date.
Loop through the sorted list:
If it is a Plan Change: update the user's current plan.
If it is an Email: print it using the user's current plan.
Code Example:

def send_emails(user_accounts, send_schedule, plan_changes=[]):
    # Create lookup map: (user_name, date) -> new_plan
    plan_change_map = {}
    for change in plan_changes:
        key = (change["name"], change["change_date"])
        plan_change_map[key] = change["new_plan"]

    # Track current plan for each user
    user_plans = {user["name"]: user["plan"] for user in user_accounts}

    # List to hold all events
    all_events = []

    for user in user_accounts:
        name = user["name"]
        account_date = user["account_date"]
        duration = user["duration"]
        end_date = account_date + duration

        for key, message_type in send_schedule.items():
            # Calculate date (same logic as Part 1)
            if key == "start":
                notification_date = account_date
            elif key == "end":
                notification_date = end_date
            else:
                notification_date = end_date + int(key)

            all_events.append({
                "date": notification_date,
                "name": name,
                "message_type": message_type,
                "event_type": "notification"
            })

    # Add plan change events to the list
    for change in plan_changes:
        all_events.append({
            "date": change["change_date"],
            "name": change["name"],
            "new_plan": change["new_plan"],
            "event_type": "plan_change"
        })

    # Sort by date. If dates are equal, process plan changes first.
    all_events.sort(key=lambda e: (e["date"], e["event_type"] != "plan_change"))

    # Process events in order
    for event in all_events:
        if event["event_type"] == "plan_change":
            user_plans[event["name"]] = event["new_plan"]
            print(f"{event['date']}: [Changed] Subscription for {event['name']} ({event['new_plan']})")
        else:
            current_plan = user_plans[event["name"]]
            print(f"{event['date']}: [{event['message_type']}] Subscription for {event['name']} ({current_plan})")
Time Complexity: O(N log N) where N is the total number of events.

Part 3: Handling Renewals Solution
The Plan:

Because renewals change the dates of future emails, we cannot generate the whole list at the start. We must update the list dynamically.

Separate changes into "Plan Changes" and "Renewals".
Track the current state (Plan, End Date) for each user.
Process events day by day.
If a Renewal happens:
Update the user's end date.
Delete any emails scheduled for the future (because they used the old date).
Create new emails using the new end date.
Add these new emails to the main list and resort.
Code Example:

def send_emails(user_accounts, send_schedule, changes=[]):
    # Separate changes into two groups
    plan_changes = {}
    renewals = {}

    for change in changes:
        name = change["name"]
        date = change["change_date"]

        if "new_plan" in change:
            if name not in plan_changes:
                plan_changes[name] = []
            plan_changes[name].append({"date": date, "new_plan": change["new_plan"]})

        if "extension" in change:
            if name not in renewals:
                renewals[name] = []
            renewals[name].append({"date": date, "extension": change["extension"]})

    # Sort changes by date for each user
    for name in plan_changes:
        plan_changes[name].sort(key=lambda x: x["date"])
    for name in renewals:
        renewals[name].sort(key=lambda x: x["date"])

    # Track user state
    user_state = {}
    for user in user_accounts:
        name = user["name"]
        user_state[name] = {
            "plan": user["plan"],
            "account_date": user["account_date"],
            "end_date": user["account_date"] + user["duration"],
            "original_end": user["account_date"] + user["duration"]
        }

    # Helper function to make notification events
    def generate_notifications(name, send_schedule, state):
        events = []
        account_date = state["account_date"]
        end_date = state["end_date"]
        plan = state["plan"]

        for key, message_type in send_schedule.items():
            if key == "start":
                date = account_date
            elif key == "end":
                date = end_date
            else:
                date = end_date + int(key)

            events.append({
                "date": date,
                "name": name,
                "plan": plan,
                "message_type": message_type,
                "type": "notification"
            })

        return events

    # Build initial list of events
    all_events = []
    for name, state in user_state.items():
        all_events.extend(generate_notifications(name, send_schedule, state))

    # Add change events to list
    for name, changes_list in plan_changes.items():
        for change in changes_list:
            all_events.append({
                "date": change["date"],
                "name": name,
                "type": "plan_change",
                "new_plan": change["new_plan"]
            })

    for name, renewals_list in renewals.items():
        for renewal in renewals_list:
            all_events.append({
                "date": renewal["date"],
                "name": name,
                "type": "renewal",
                "extension": renewal["extension"]
            })

    # Sort all events
    all_events.sort(key=lambda e: (e["date"], _event_priority(e)))

    # Process events
    i = 0
    while i < len(all_events):
        event = all_events[i]

        if event["type"] == "plan_change":
            user_state[event["name"]]["plan"] = event["new_plan"]
            print(f"{event['date']}: [Changed] Subscription for {event['name']} ({event['new_plan']})")
            i += 1

        elif event["type"] == "renewal":
            name = event["name"]
            extension = event["extension"]
            user_state[name]["end_date"] += extension
            current_plan = user_state[name]["plan"]
            print(f"{event['date']}: [Renewed] Subscription for {name} ({current_plan})")

            # Remove future notifications for this user (they are now wrong)
            all_events = [e for e in all_events if not (
                e.get("type") == "notification" and
                e["name"] == name and
                e["date"] > event["date"]
            )]

            # Make new notifications based on new end date
            new_notifications = generate_notifications(name, send_schedule, user_state[name])
            
            # Only keep notifications that happen in the future
            new_notifications = [n for n in new_notifications if n["date"] > event["date"]]
            
            # Add new events and re-sort
            all_events.extend(new_notifications)
            all_events.sort(key=lambda e: (e["date"], _event_priority(e)))

            i += 1

        else:  # It is a notification
            current_plan = user_state[event["name"]]["plan"]
            print(f"{event['date']}: [{event['message_type']}] Subscription for {event['name']} ({current_plan})")
            i += 1

def _event_priority(event):
    """Order: Plan Change -> Renewal -> Notification"""
    priority_map = {"plan_change": 0, "renewal": 1, "notification": 2}
    return priority_map.get(event["type"], 3)
Key Details:

Recalculation: We delete old future emails and create new ones.
Dynamic Sorting: Because we add new events mid-loop, we have to re-sort or handle the list carefully.
Priority: Changes happen before emails on the same day.
Common Follow-Up Questions
What if the subscription is very short?
Question: What if a user has a 10-day subscription, but the schedule says to send an email "15 days before the end" (-15)? The calculated date would be Day -5 (before they joined).

Answer: You should ask the interviewer what to do. Usually, you have three options:

Skip it: Don't send the email.
Clamp it: Send it on Day 0 (start date).
Check Date: Only add the email if notification_date >= start_date.
if notification_date >= account_date:
    emails_by_day[notification_date].append(...)
Clarifying Renewal Dates
Remember: Renewals add time to the end of the current period. If a plan ends on Day 16, and you renew for 15 days on Day 3, the new end date is Day 31 (16 + 15). The user does not lose the days between Day 3 and Day 16.