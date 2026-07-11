---
name: scaffold-module
description: "Scaffold a new module with boilerplate files for the correct tech stack. Use when: scaffold module, create new module, bootstrap component, add new service, new feature skeleton, generate boilerplate."
---

# Scaffold Module

Generate boilerplate files for a new module in the correct stack.

## Input
- Module name
- Layer: `cpp`, `node`, or `angular`

## Steps

### 1. Determine layer
Ask the user or infer from context which layer this module belongs to.

### 2. Generate files

**C++ module:**
```
src/<module>/
  <module>.h          # Class declaration with Doxygen header
  <module>.cpp        # Implementation stub
  <module>_test.cpp   # Google Test fixture stub
  CMakeLists.txt      # Target definition
```

**Node.js module:**
```
src/<module>/
  <module>.service.ts       # Service class with interface
  <module>.controller.ts    # Route handler stub
  <module>.model.ts         # Data model / types
  <module>.spec.ts          # Jest test stub
  index.ts                  # Barrel export
```

**Angular module:**
```
src/app/features/<module>/
  <module>.component.ts      # Standalone component with OnPush
  <module>.component.html    # Template
  <module>.component.scss    # Scoped styles
  <module>.component.spec.ts # Test stub
  <module>.service.ts        # Feature service
  <module>.routes.ts         # Lazy route definition
```

### 3. Wire up
- C++: add `add_subdirectory(<module>)` to parent CMakeLists.txt
- Node: add export to nearest barrel `index.ts`
- Angular: add route to app routes

### 4. Verify
- Run build to confirm no compilation errors.
