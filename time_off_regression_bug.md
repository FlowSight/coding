# Bug Report: Time Off Entry Regression

## What

During a [bug](https://dynamicscrm.visualstudio.com/OneCRM/_workitems/edit/5834568/) fix in a [PR](https://dynamicscrm.visualstudio.com/OneCRM/_git/CRM.Solutions.ProjectService/pullrequest/1489243), a regression was introduced where **time off entries** were incorrectly created (Case 1) or **not created at all** (Case 2) for Absence/Vacation Time Entry types.

---

## Examples

### Case 1 — No Time Entry Created

| Field | Value |
|---|---|
| **Time Entry** | Duration: 8hr, Type: Absence |
| **Work Hours Setup** | 9 AM – 5 PM |
| **Result** | ❌ No time entry created (as 8 AM < 9 AM) |
| **Expected** | ✅ A time off entry should be created **9 AM – 5 PM** |

### Case 2 — Incorrect Duration

| Field | Value |
|---|---|
| **Time Entry** | Duration: 10hr, Type: Vacation |
| **Work Hours Setup** | 9 AM – 5 PM |
| **Result** | ❌ Time entry created **9 AM – 10 AM** |
| **Expected** | ✅ A time off entry should be created **9 AM – 5 PM** (extra 2 hours should be pruned) |

---

## When

The change was part of **UR63**.

---

## Proposed Fix

> There are multiple parts of the data that are corrupted. The fix is split into three phases:

### Phase 1 — Already-Created Time Entries with Corrupted/Empty Time Off

- Deploy a **custom API/plugin** wrapped in a managed/unmanaged solution.
- The plugin will:
  - **Not** touch any existing time entry.
  - Pick absence/vacation time entries created/updated during the regression period.
  - Remove existing + create new **correct** time off entries.
  - Work for all time entries (**no recall/submit required**).
- ProMx can help deploy the solution onto customer orgs, **without needing it to be part of the next build/release**.

### Phase 2 — Time Entries Created by Users Until the Hotfix Goes In

- The above plugin can be **run daily** (or at another frequency).
- It will only pick time entries not yet processed.

### Phase 3 — Time Entries After the Proper Fix Goes In

- Make the fix part of **UR65 / UR64 / hotfix**.
