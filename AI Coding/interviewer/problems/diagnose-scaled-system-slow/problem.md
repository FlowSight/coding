# Diagnose Why a Scaled System Became Slow

## Base problem

A service became slower after horizontal scaling. The starter analyzes a
telemetry snapshot containing request latency, resource saturation, dependency
latency, cache behavior, and per-instance measurements. Use evidence rather than
guesswork: distinguish symptoms from causes and make assumptions explicit.

## Follow-up 1: Preserve Hot-Shard Evidence

The current analyzer reports the fleet as healthy even when one instance is a
severe hotspot.

Acceptance criteria:

- Diagnose and fix the aggregation defect without hard-coding the sample.
- Preserve instance-level evidence when computing fleet health.
- The regression case with one hot instance passes.
- Missing or malformed measurements fail explicitly.

## Follow-up 2: Rank Diagnostic Hypotheses

Implement ranked diagnostic hypotheses.

Acceptance criteria:

- Return at least a category, evidence, and confidence for each hypothesis.
- Rank stronger evidence ahead of weaker evidence deterministically.
- Cover compute, memory, I/O, network, cache, and database signals when present.
- Do not claim a root cause unsupported by the supplied telemetry.

## Follow-up 3: Recommend the Next Observability Probe

Recommend the next observability probe.

Acceptance criteria:

- Select a probe that can distinguish the top competing hypotheses.
- Explain the expected confirming and disconfirming observations.
- Avoid recommending a measurement already present and conclusive.
- Return a clear insufficient-evidence result when appropriate.

Use the build and test command in the selected starter's README.
