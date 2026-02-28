Feature Flag SDK
The Challenge
You need to build an SDK that internal services will use to handle feature flags. Feature flags (or feature toggles) let teams turn features on or off without adding new code. This helps teams launch updates safely, run A/B tests, and fix issues quickly.

Your SDK must be easy to use. It needs to do two main things:

Basic lookup: Check if a feature is enabled by looking at its name.
Context lookup: Check if a feature is enabled based on specific details (like a user ID, country, or other data).
Basic Code Interface
// Check if a flag is on or off
boolean get(String featureKey)

// Check flag using specific context
boolean get(String featureKey, String jsonContext)
// Example context: {"userId": "abc123", "country": "US", "plan": "enterprise"}
Important Design Goals
Performance: How do you keep Latency low? Services might call this SDK thousands of times every second.
Consistency: When you change a flag, how does that update reach every instance of the SDK?
Reliability: If the main flag service goes down, what should the SDK do?
Targeting rules: How do you handle complex logic? For example: "Enable this for 10% of users in the US."
Topics for Deep Discussion
The interviewer will likely ask harder questions about specific parts of your design:

Caching Strategy: Should the SDK save flag values locally? How do you remove old data (cache invalidation)?
Update Propagation: How do updates reach the SDK? Should the SDK ask for updates (pull), or should the server send them (push)?
Evaluation Logic: How do you calculate percentage rollouts? How do you make sure a specific user always sees the same result?
Failure Modes: What is the default action if the backend is unreachable? Should flags default to open or closed?
Storage Backend: Where do you save the flag settings? How do you handle high read traffic?
SDK Initialization: How does the SDK start up? What happens if it fails to start?
Audit & Observability: How do you track who checked a flag and when?
Helpful Links
This is a common system design problem. These resources explain how to build it:

Design a Feature Flag System - Dwarves Foundation - A complete guide to feature flag architecture.
Designing a Feature Flag System - Ray Mathew - A detailed guide for interview preparation.
How to Build Feature Flags - Statsig - Practical advice from a real feature flag platform.
What to Expect in the Interview
This interview is very fast (only 45 minutes). Candidates suggest you skip the basic approach and go straight to an optimized solution. You will not have enough time to improve a slow design later.

Using a structured system design framework will help you stay organized and cover all the important parts quickly.