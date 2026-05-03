# Time Copilot — Q&A

## Technical Questions

**Q: How does the copilot orchestration work?**
A: TODO — shared framework with Project Copilot team

**Q: How do you handle multi-language support? What changed for non-English?**
A: TODO (DSB review process, language-specific considerations)

**Q: What LLM model? How are parameters tuned?**
A: TODO

**Q: How do you handle ambiguous user instructions?**
A: TODO

**Q: What's the latency like? How do you keep it conversational?**
A: TODO

---

## Design Questions

**Q: How did you share the orchestration framework with Project Copilot team?**
A: TODO (this ties to maxim_conflict story)

**Q: How do you handle model version upgrades without breaking both teams?**
A: TODO

**Q: What happens when copilot gives wrong suggestion?**
A: TODO

---

## Impact Questions

**Q: What was the adoption rate?**
A: TODO

**Q: How did you measure copilot quality?**
A: TODO

**Q: Biggest challenge during GA launch?**
A: TODO (ties to sobhan_conflict — vacation overlap during critical sprint)

---

## Fundamentals

**Q: What is an Adaptive Card?**
A:
- A **platform-agnostic, JSON-defined UI card** that renders natively in Microsoft hosts (Teams, Outlook, Windows, Copilot).
- Pure JSON — no HTML, CSS, or JavaScript. The host app renders it in its own native style.
- Supports interactive elements: buttons, dropdowns, text inputs, toggles. Button clicks send a payload back to your bot/agent for server-side handling.
- Same JSON renders across Teams (desktop/mobile), Outlook, Windows notifications, Copilot — cross-platform by design.
- **Analogy**: If HTML is a full webpage, an Adaptive Card is a structured post-it note with buttons — lightweight, declarative, rendered by the host.
