---
applyTo: "**/*.test.*,**/*.spec.*,**/test/**,**/tests/**,**/__tests__/**"
description: "Testing conventions for unit and integration tests across all stacks. Use when writing, reviewing, or modifying test files."
---

# Testing Conventions

## General
- Every public function/method must have at least one unit test.
- Test names describe behavior: `should_return_empty_when_input_is_null`, not `test1`.
- Arrange-Act-Assert (AAA) pattern for all tests.
- No test interdependencies — each test sets up and tears down its own state.

## Coverage Targets
| Type | Minimum |
|------|---------|
| Unit tests | 80% line coverage |
| Integration tests | Critical paths (API endpoints, DB operations, cross-service calls) |

## C++ (Google Test)
- Test file: `feature_test.cpp` alongside `feature.cpp`.
- Use `TEST_F` with fixtures for shared setup.
- Mock external dependencies with GMock.

## Node.js (Jest / Vitest)
- Test file: `feature.spec.ts` alongside `feature.ts`.
- Mock external services with `jest.mock()` or `vi.mock()`.
- Use `supertest` for HTTP integration tests.

## Angular (Jasmine + Karma / Jest)
- Test file: `feature.component.spec.ts` alongside component.
- Use `TestBed` for component tests, plain instantiation for service unit tests.
- Use `HttpClientTestingModule` for service HTTP tests.
- E2E: Playwright or Cypress for critical user flows.

## What NOT to Test
- Private methods (test via public interface).
- Framework internals (Angular lifecycle hooks unless custom logic).
- Trivial getters/setters.
