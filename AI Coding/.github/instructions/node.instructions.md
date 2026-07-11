---
applyTo: "**/*.ts,**/*.js,**/package.json,**/tsconfig.json"
description: "Node.js and TypeScript conventions for backend services. Use when writing, reviewing, or modifying server-side JS/TS files."
---

# Node.js / TypeScript Conventions

## Language
- TypeScript strict mode (`"strict": true` in tsconfig).
- Prefer `interface` over `type` for object shapes. Use `type` for unions/intersections.
- No `any`. Use `unknown` and narrow with type guards.

## Style
- Naming: `camelCase` for functions/variables, `PascalCase` for classes/interfaces, `UPPER_SNAKE` for constants.
- Use `async/await` over raw Promises. Never mix callbacks and promises.
- Prefer named exports over default exports.

## Structure
- Organize by feature, not by file type:
  ```
  src/
    feature-name/
      feature.controller.ts
      feature.service.ts
      feature.model.ts
      feature.spec.ts
  ```
- Entry point: `src/index.ts` or `src/main.ts`.
- Config via environment variables, loaded once in `src/config/`.

## Error Handling
- Custom error classes extending `Error` with `statusCode` and `code` fields.
- Global error handler middleware for Express/Fastify.
- Validate inputs at API boundary using zod or joi.

## Dependencies
- Pin exact versions in `package.json`.
- No unused dependencies — run `npx depcheck` before committing.
