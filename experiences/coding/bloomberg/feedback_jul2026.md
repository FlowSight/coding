# Bloomberg — Interview Feedback (July 2026)

## Format
- Round 1: Resume project discussion → High-level design → Design document review
- Round 2: (details TBD)

## Feedback Summary

### ✅ What went well
- **Project discussion**: Explained resume project nicely and in detail

### ❌ What went wrong

**High-Level Design:**
- Jumped too deep into implementation without first gathering requirements
- Should have spent more time on: scope, constraints, use cases, traffic estimates BEFORE proposing architecture

**Design Document Review:**
- Pointed out some nice/important details (individual issues)
- BUT failed to challenge the design at a holistic level
- Should NOT have accepted the design as-is and then drilled into specifics
- Should have stepped back and asked: "Does this design even solve the right problem? Is the architecture fundamentally sound?"
- The expectation was to critique the design itself — not just find bugs within it

## Key Takeaways

1. **Requirements first, always.** Even in system design, spend 5+ min clarifying scope, scale, and constraints before drawing boxes.
2. **Design review ≠ code review.** Don't pattern-match to "find bugs". Instead:
   - Does the design meet the stated requirements?
   - Are there missing components?
   - Is the decomposition sensible?
   - Are there better alternatives?
3. **Challenge top-down, not bottom-up.** Start with "why this architecture?" before "this component has issue X."

## Action Items
- [ ] Practice design critique: take existing designs and challenge their fundamentals
- [ ] Build a "design review checklist" (requirements coverage → architecture fit → component design → edge cases)
- [ ] In HLD practice, set a timer: first 5 min = requirements only, no architecture
