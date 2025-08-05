SITUATION:
- Led a team working on a feature to differentiate between human-edited and AI-generated content
- Feature was a key commitment made to customers by Principal PM and Group Engineering Manager
- Project had been on the roadmap for several months
- Had approximately one month for complete implementation. Feature was considered a 'low hanging fruit' prioritized for end of wave delivery
- Designed a solution using stringified JSON in SQL column for storing edited details
- Used feature branch approach, work by indiviuduals were merged into feature branch. Then later feature to master.
- When merging to master, peer team architect blocked PR.

TASK:
- Needed to navigate through the archiect and leadership to ensure a timely delivery. Atleast a conclusion on path forward

ACTION:
- Had discussion with architect, my manager, explained rationale: limited fields (3-5), non-customizable nature, and conscious choice to avoid over-engineering. He still didnt seem inclined.
-  When initial discussions failed, escalated to leadership with full context via email
- Proposed maintaining existing design with possibility for future redesign using version field for backward compatibility
- Reached out to other architects, and product owner to get consensus. 2 other architects aligned, and leadership strongly aligned as it was a committed feature.

RESULT:
- Successfully got PR unblocked with leadership support
- Delivered feature within committed timeline
- Implemented process improvement: including architects from peer teams in design discussions even when its our team specific feature
- Maintained good cross-team relationships while being direct about priorities
- Successfully balanced immediate delivery needs with technical considerations


///////////////REFIINED VERSON///////

maps to 
“Tell me about a time you had to influence a decision without having full authority.” ✅

“Tell me about a time you faced a technical disagreement with a stakeholder.”

“Tell me about a time you had to deliver something on a tight timeline despite resistance.”


### **SITUATION**
I was leading the engineering effort for a feature that distinguishes between human-edited and AI-generated content — a key commitment made to customers by our Principal PM and Group Engineering Manager. The project had been on the roadmap for months, but was prioritized late as a “low-hanging fruit” for end-of-wave delivery. We had just about a month to implement it.

To move fast, I designed a simple solution using a stringified JSON column in SQL to capture edited metadata — we had only 3–5 fields, and this avoided unnecessary over-engineering. We followed a feature branch model, and when the work was merged to main, a peer team architect blocked the PR citing concerns about storing JSON in SQL.

### **TASK**
I needed to influence multiple stakeholders — including the architect who didn’t report to me — to move forward without delaying delivery, while preserving technical integrity. At the very least, I had to reach a concrete decision path quickly.

### **ACTION**
I started by engaging directly with the blocking architect and my manager to explain the rationale: the limited scope, fixed schema, and our conscious tradeoff given the delivery timeline. Despite this, the architect remained unconvinced.

Seeing the risk of slipping a committed customer promise, I escalated with full context to leadership via email — including tradeoffs, alternative paths, and the customer impact. I also proactively reached out to two neutral architects from other peer teams to validate the design. Both aligned with our approach, and leadership strongly backed moving forward, citing the importance of the commitment.

To ensure we kept long-term maintainability open, I proposed tagging this design with a version field, so we could migrate schema later without breaking changes.

### RESULT: ###
The PR was unblocked with leadership backing. We delivered the feature on time.

Importantly, we introduced a new practice: even for team-specific features, we now include architects from other teams in early design discussions — this helped reduce friction for future work. **I was able to maintain strong cross-team relationships by staying direct but respectful about priorities**, and balancing near-term delivery with a scalable long-term path.
