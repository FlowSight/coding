# AI Coding Interview — Ready-to-Use Agent Templates

Copy-paste one of these at the start of your interview depending on your tool.

---

## Option A: VS Code Copilot — `.github/copilot-instructions.md`

```markdown
# Project Instructions

## Stack
- Python 3.11+ with FastAPI
- pytest for testing
- structlog for structured JSON logging
- Pydantic for validation
- uvicorn as ASGI server

## Code Standards
- Type hints on all functions
- Async endpoints where I/O is involved
- Input validation via Pydantic models
- Proper HTTP status codes (201 for create, 404 for not found, 422 for validation)
- Dependency injection for services

## Architecture
- Clean layered architecture: routes → services → repositories
- Each module in its own file
- Config via environment variables (pydantic-settings)

## Testing
- pytest with fixtures
- One test file per module (test_<module>.py)
- Cover happy path + edge cases + error cases
- Use httpx.AsyncClient for API tests

## Logging & Monitoring
- structlog JSON logging on every endpoint entry/exit
- Log request_id, method, path, status_code, duration_ms
- Add correlation IDs via middleware

## Error Handling
- Custom exception classes
- Global exception handler middleware
- Never expose stack traces to client
```

---

## Option B: Cursor — `.cursorrules`

```
You are a senior backend engineer helping me build a production service.

Stack: Python 3.11+, FastAPI, pytest, structlog, Pydantic, uvicorn.

Architecture rules:
- Clean layers: routes → services → repositories
- Async where I/O is involved
- Type hints everywhere
- Pydantic models for all request/response schemas
- Dependency injection for testability

Testing rules:
- Write pytest tests alongside every implementation
- One test file per module: test_<name>.py
- Test happy path, edge cases, and error paths
- Use httpx.AsyncClient for endpoint tests

Logging rules:
- structlog with JSON output
- Log entry/exit of every endpoint with: request_id, method, path, duration_ms, status
- Correlation ID middleware

Error handling:
- Custom exceptions with HTTP status mapping
- Global exception handler — never leak stack traces
- Return structured error responses: {"error": str, "detail": str}

When I ask you to implement something:
1. First confirm the approach in 2-3 sentences
2. Then implement with full code
3. Then write tests
4. Then add logging
```

---

## Option C: Reusable Prompt (any tool) — paste at start of session

```
I'm building a production backend service from scratch. Here's my setup:

Stack: Python 3.11, FastAPI, pytest, structlog, Pydantic
Architecture: routes → services → repositories (clean layers)
Testing: pytest with httpx.AsyncClient, fixtures, edge cases
Logging: structured JSON via structlog, correlation IDs, request tracing
Error handling: custom exceptions, global handler, no stack trace leaks

For every feature I ask you to build:
1. Implement the code with type hints and async
2. Add structured logging
3. Write comprehensive tests
4. Make it production-ready

Start by scaffolding the project structure.
```

---

## Interview Flow Script

**What to say when you create the file (narrate to interviewer):**

> "Before I start coding, I'm going to set up my AI assistant with project-level instructions. This ensures consistent code style, testing patterns, and logging across everything it generates. It's like giving the AI a style guide so I don't have to repeat myself."

**Then after creating it:**

> "Now my AI will automatically follow these patterns. Let me start by designing the solution at a high level, then I'll use the AI to scaffold and implement each layer."

---

## Quick Scaffold Prompt (use after setup)

```
Create the project structure:
- src/
  - main.py (FastAPI app with health check, CORS, logging middleware)
  - config.py (pydantic-settings for env vars)
  - models/ (Pydantic schemas)
  - routes/ (API endpoints)
  - services/ (business logic)
  - repositories/ (data access)
  - middleware/ (logging, correlation ID, error handler)
- tests/
  - conftest.py (fixtures, test client)
  - test_health.py
- requirements.txt
- Dockerfile
- .env.example
```

---

## Debugging/Refactoring Prompts (keep handy)

```
# When AI generates bad code:
"This has a bug — [describe issue]. Fix it and explain what went wrong."

# When you need tests fast:
"Write pytest tests for this function covering: happy path, empty input, invalid input, and boundary cases."

# When you need logging added:
"Add structured logging to this endpoint: log entry with request params, exit with response status and duration."

# When you need to refactor:
"Extract the business logic from this route into a service class with dependency injection."
```
