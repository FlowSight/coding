---
applyTo: "**/*.cpp,**/*.h,**/*.hpp"
description: "C++ coding conventions for backend systems code. Use when writing, reviewing, or modifying C++ source files."
---

# C++ Conventions

## Standard & Compilation
- Use C++17 unless the feature explicitly requires C++20.
- All code must compile with `-Wall -Wextra -Werror`.
- Prefer `constexpr` and `const` wherever possible.

## Style
- Naming: `snake_case` for functions/variables, `PascalCase` for types/classes, `UPPER_SNAKE` for constants.
- Use RAII for resource management. No raw `new`/`delete` — use `std::unique_ptr` or `std::shared_ptr`.
- Prefer `std::string_view` over `const std::string&` for read-only string parameters.
- Use `enum class` over plain `enum`.

## Structure
- One class per header/source pair.
- Headers use `#pragma once`.
- Separate interface (`.h`) from implementation (`.cpp`). Inline only trivial getters.

## Error Handling
- Use exceptions for unrecoverable errors, `std::optional` or `std::expected` (C++23) for expected failures.
- Never catch `(...)` silently.

## Dependencies
- Prefer STL over third-party libraries when equivalent.
- Third-party deps managed via CMake `FetchContent` or vcpkg.
