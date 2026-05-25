# ICMs — Anirban Mitra

> Team: Time (owningTeamId: 73138, owningServiceId: 27831)
> Filter: mitigatedBy or resolvedBy or commented = mitraanirban
> Date range: Nov 1, 2025 onward

## Legend
- **Role**: M = Mitigated, R = Resolved, C = Commented/Worked on
- **Portal**: ROW = portal.microsofticm.com, EU = euportal.microsofticm.com

## ROW Portal Incidents

| # | ICM ID | Sev | State | Created | Title | Role |
|---|--------|-----|-------|---------|-------|------|
| 1 | [21000000771959](https://portal.microsofticm.com/imp/v5/incidents/details/21000000771959/summary) | 3 | RESOLVED | 2025-11-07 | Script execution in Production - Cannot post hour journals not timesheets for specific resource | M+R |
| 2 | [21000000790928](https://portal.microsofticm.com/imp/v5/incidents/details/21000000790928/summary) | 3 | RESOLVED | 2025-11-21 | [Strategic] Invalid Timesheet Hours Index Error on Update | M |
| 3 | [21000000789706](https://portal.microsofticm.com/imp/v5/incidents/details/21000000789706/summary) | 3 | RESOLVED | 2025-11-20 | [Strategic] Multiple crashes due to Out of memory exceptions | C |
| 4 | [51000000796063](https://portal.microsofticm.com/imp/v5/incidents/details/51000000796063/summary) | 4 | RESOLVED | 2025-11-28 | $psaJQuery Not Initialized on First Time Entry Submit in project operations | C |
| 5 | [21000000806661](https://portal.microsofticm.com/imp/v5/incidents/details/21000000806661/summary) | 3 | RESOLVED | 2025-12-08 | [Premier] Unit Price Discrepancy on Time Entries for July 11 | M |
| 6 | [21000000811451](https://portal.microsofticm.com/imp/v5/incidents/details/21000000811451/summary) | 3 | RESOLVED | 2025-12-10 | [Strategic] Counter error when creating a timesheet or expense report | M |
| 7 | [51000000849698](https://portal.microsofticm.com/imp/v5/incidents/details/51000000849698/summary) | 3 | RESOLVED | 2026-01-09 | Project Timesheet transaction voucher posted with wrong date | M+R |
| 8 | [51000000921041](https://portal.microsofticm.com/imp/v5/incidents/details/51000000921041/summary) | 4 | RESOLVED | 2026-02-27 | System allows changing project on multiple time entries | M+R |
| 9 | [21000000974923](https://portal.microsofticm.com/imp/v5/incidents/details/21000000974923/summary) | 4 | RESOLVED | 2026-04-07 | Performance issue on ASE report with a database timeout error | M |

## EU Portal Incidents

| # | ICM ID | Sev | State | Created | Title | Role |
|---|--------|-----|-------|---------|-------|------|
| 1 | [1716530](https://euportal.microsofticm.com/imp/v5/incidents/details/1716530/summary) | — | — | — | — | C |
| 2 | [21000000005582](https://euportal.microsofticm.com/imp/v5/incidents/details/21000000005582/summary) | — | — | — | — | C |
| 3 | [21000000006262](https://euportal.microsofticm.com/imp/v5/incidents/details/21000000006262/summary) | — | — | — | — | C |
| 4 | [51000000007214](https://euportal.microsofticm.com/imp/v5/incidents/details/51000000007214/summary) | — | — | — | — | C |
| 5 | [21000000010313](https://euportal.microsofticm.com/imp/v5/incidents/details/21000000010313/summary) | — | — | — | — | C |
| 6 | [21000001012078](https://portal.microsofticm.com/imp/v5/incidents/details/21000001012078/summary) | — | — | — | Error when entering time entries in project operations | C |

## Additional Context

| ICM ID | Notes |
|--------|-------|
| 21000000790928 | Long-running. Authored novel script to fix corrupted periodId caused by manual data corruption by customer. Unseen issue class — no prior mitigation pattern existed. |
| 21000000789706 | 54+ days running. Proved a loop creating temp variables was causing OOM. Cross-team collab with Shreedhar (AX Runtime – Memory/CPU). Created tech debt to rewrite batch posting logic. |
| 1716530 | 100+ days running. New script for intercompany scenario to clear transactions. Problem statement changed throughout ICM lifetime. Multiple iterations of mitigation. |
| Siemens (Sev 2) | Sev 2. Regression by teammate corrupting customer prod data. Partnered with Sutanu to deliver full feature over 3 weeks: (1) stop new corrupted TEs, (2) batch-correct existing. Cross-team with Vinay (Budget mgr), Sudhanshu (Release), Naushad (PMRM mgr). Learned LongRunningJob framework. 5–8 test rounds with PM (Mohit). Saved 500+ TE records. |

> EU Portal details pending — need EU MCP endpoint to fetch titles/dates.

---
*Last updated: 2026-05-25*
